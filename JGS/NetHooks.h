#pragma once

#include "Inventory.h"
#include <fstream>

namespace Beacons
{
	bool bSetupCharPartArray = false;
	bool bSetupFloorLoot = false;

	AOnlineBeaconHost* Beacon;

	bool (*InitHost)(AOnlineBeaconHost*);
	__int64(*WelcomePlayer)(UWorld* This, UNetConnection* NetConnection);
	APlayerController* (*SpawnPlayActor)(UWorld* a1, UPlayer* a2, ENetRole a3, FURL a4, void* a5, FString& Src, uint8_t a7);
	void(*UWorld_NotifyControlMessage)(UWorld* World, UNetConnection* NetConnection, uint8_t a3, void* a4);

	void (*TickFlush)(UNetDriver*, float DeltaSeconds);
	void (*NotifyActorDestroyed)(UNetDriver*, AActor*, bool);
	bool (*DestroyActor)(UWorld*, AActor*, bool, bool);

	static void SpawnFloorLoot()
	{
		TArray<AActor*> OutActors;
		Globals::GPS->STATIC_GetAllActorsOfClass(Globals::World, UObject::FindClass("BlueprintGeneratedClass Tiered_Athena_FloorLoot_01.Tiered_Athena_FloorLoot_01_C"), &OutActors);

		for (int i = 0; i < OutActors.Num(); i++)
		{
			bool bShouldSpawn = Globals::MathLib->STATIC_RandomBoolWithWeight(0.6f);
			bool bIsConsumable = !Globals::MathLib->STATIC_RandomBoolWithWeight(0.2f);

			auto Actor = OutActors[i];

			if (Actor && bShouldSpawn)
			{
				auto SpawnLoc = Actor->K2_GetActorLocation();

				auto NewFortPickup = reinterpret_cast<AFortPickupAthena*>(Util::SpawnActor(AFortPickupAthena::StaticClass(), SpawnLoc, FRotator()));

				NewFortPickup->PrimaryPickupItemEntry.Count = 1;
				if (bIsConsumable)
				{
					if (Globals::bSTWMode)
					{
						NewFortPickup->PrimaryPickupItemEntry.ItemDefinition = Globals::STWWeapons[rand() % Globals::STWWeapons.size()];
						NewFortPickup->PrimaryPickupItemEntry.Durability = 1000000;
					}
					else {
						NewFortPickup->PrimaryPickupItemEntry.ItemDefinition = Globals::RangedWeapons[rand() % Globals::RangedWeapons.size()];
					}
				}
				else {
					NewFortPickup->PrimaryPickupItemEntry.ItemDefinition = Globals::Consumables[rand() % Globals::Consumables.size()];
				}
				NewFortPickup->OnRep_PrimaryPickupItemEntry();
				NewFortPickup->TossPickup(SpawnLoc, nullptr, 1);

				auto AmmoDefintion = ((UFortWorldItemDefinition*)NewFortPickup->PrimaryPickupItemEntry.ItemDefinition)->GetAmmoWorldItemDefinition_BP();
				auto AmmoPickup = reinterpret_cast<AFortPickupAthena*>(Util::SpawnActor(AFortPickupAthena::StaticClass(), NewFortPickup->K2_GetActorLocation(), {}));
				AmmoPickup->PrimaryPickupItemEntry.Count = 30;
				AmmoPickup->OnRep_PrimaryPickupItemEntry();
				AmmoPickup->TossPickup(NewFortPickup->K2_GetActorLocation(), nullptr, 999);

				Actor->K2_DestroyActor();
				//LOG("Spawned Pickup: " << NewFortPickup->GetName() << " With weapon definition: " << NewFortPickup->PrimaryPickupItemEntry.ItemDefinition->GetName());
			}
		}
	}

	FVector GetPlayerStart()
	{
		TArray<AActor*> OutActors;
		Globals::GPS->STATIC_GetAllActorsOfClass(Globals::World, APlayerStart::StaticClass(), &OutActors);
		return OutActors[rand() % OutActors.Num()]->K2_GetActorLocation();
	}

	void __fastcall AOnlineBeaconHost_NotifyControlMessageHook(AOnlineBeaconHost* BeaconHost, UNetConnection* NetConnection, uint8_t a3, void* a4)
	{
		if (std::to_string(a3) == "4") {
			NetConnection->CurrentNetSpeed = 30000;
			return;
		}

		LOG("AOnlineBeaconHost::NotifyControlMessage Called! " << std::to_string(a3).c_str());
		LOG("Channel Count " << std::to_string(NetConnection->OpenChannels.Num()).c_str());
		return UWorld_NotifyControlMessage(Globals::World, NetConnection, a3, a4);
	}

	void TickFlushHook(UNetDriver* NetDriver, float DeltaSeconds)
	{
		Replication::ReplicateActors(NetDriver);

		return TickFlush(NetDriver, DeltaSeconds);
	}

	__int64 KickPatch(__int64, __int64)
	{
		return 0;
	}

	__int64 __fastcall WelcomePlayerHook(UWorld*, UNetConnection* NetConnection)
	{
		LOG("Welcoming Player!");
		return WelcomePlayer(Globals::World, NetConnection);
	}

	void GrantGameplayAbilities(APlayerPawn_Athena_C* InPawn)
	{
		static auto AbilitySet = FindObjectFast<UFortAbilitySet>("/Game/Abilities/Player/Generic/Traits/DefaultPlayer/GAS_DefaultPlayer.GAS_DefaultPlayer");

		for (int i = 0; i < AbilitySet->GameplayAbilities.Num(); i++)
		{
			auto Ability = AbilitySet->GameplayAbilities[i];

			Abilities::GrantGameplayAbility(InPawn, Ability);
		}

		static auto ShootingAbility = FindObjectFast<UClass>("/Game/Abilities/Weapons/Ranged/GA_Ranged_GenericDamage.GA_Ranged_GenericDamage_C");
		if (ShootingAbility)
		{
			Abilities::GrantGameplayAbility(InPawn, ShootingAbility);
		}
	}

	APlayerController* SpawnPlayActorHook(UWorld*, UNetConnection* Connection, ENetRole NetRole, FURL a4, void* a5, FString& Src, uint8_t a7)
	{
		if (!bSetupCharPartArray)
		{
			LoadCharacterParts();
			bSetupCharPartArray = true;
		}

		if (!bSetupFloorLoot)
		{
			SpawnFloorLoot();
			bSetupFloorLoot = true;
		}

		auto PlayerController = (AFortPlayerControllerAthena*)SpawnPlayActor(Globals::World, Connection, NetRole, a4, a5, Src, a7);
		Connection->PlayerController = PlayerController;
		PlayerController->NetConnection = Connection;
		Connection->OwningActor = PlayerController;

		auto Pawn = (APlayerPawn_Athena_C*)(Util::SpawnActor(APlayerPawn_Athena_C::StaticClass(), GetPlayerStart(), {}));
		Pawn->bCanBeDamaged = false;
		Pawn->SetOwner(PlayerController);
		PlayerController->Possess(Pawn);

		Pawn->SetMaxHealth(100);
		Pawn->SetHealth(100);
		auto HealthSet = Pawn->HealthSet;
		HealthSet->CurrentShield.Minimum = 0;
		HealthSet->CurrentShield.Maximum = 100;
		HealthSet->CurrentShield.BaseValue = 0;
		HealthSet->Shield.Minimum = 0;
		HealthSet->Shield.Maximum = 100;
		HealthSet->Shield.BaseValue = 100;
		HealthSet->OnRep_Shield();
		HealthSet->OnRep_CurrentShield();

		PlayerController->ClientForceProfileQuery();

		auto RandomParts = Globals::CharacterParts[rand() % Globals::CharacterParts.size()];

		if (RandomParts.HeadPart)
		{
			Pawn->ServerChoosePart(EFortCustomPartType::Head, RandomParts.HeadPart);
		}

		if (RandomParts.BodyPart)
		{
			Pawn->ServerChoosePart(EFortCustomPartType::Body, RandomParts.BodyPart);
		}

		if (RandomParts.HatPart)
		{
			Pawn->ServerChoosePart(EFortCustomPartType::Hat, RandomParts.HatPart);
		}

		((AFortPlayerState*)Pawn->PlayerState)->OnRep_CharacterParts();

		Pawn->CharacterMovement->bReplicates = true;
		Pawn->SetReplicateMovement(true);
		Pawn->OnRep_ReplicatedBasedMovement();

		Pawn->OnRep_ReplicatedMovement();

		PlayerController->bHasServerFinishedLoading = true;
		PlayerController->OnRep_bHasServerFinishedLoading();

		auto PlayerState = (AFortPlayerStateAthena*)(PlayerController->PlayerState);

#ifdef SAME_TEAM
		PlayerState->TeamIndex = EFortTeam::HumanPvP_Team69;
#endif
		PlayerState->OnRep_TeamIndex();

		PlayerState->bHasFinishedLoading = true;
		PlayerState->bHasStartedPlaying = true;
		PlayerState->bIsGameSessionAdmin = true;
		PlayerState->bIsGameSessionOwner = true;
		PlayerState->bIsWorldDataOwner = true;
		PlayerState->bIsReadyToContinue = true;
		PlayerState->OnRep_bHasStartedPlaying();
		PlayerState->OnRep_CharacterParts();

		auto NewCheatManager = (UFortCheatManager*)(Globals::GPS->STATIC_SpawnObject(UFortCheatManager::StaticClass(), PlayerController));
		PlayerController->CheatManager = NewCheatManager;
		NewCheatManager->BackpackSetSize(5);

		auto NewInv = CreateInventoryForPlayerController(PlayerController);
		NewInv->SetupInventory();
		NewInv->UpdateInventory();

		PlayerState->OnRep_HeroType();
		PlayerState->OnRep_PlayerTeam();

		return PlayerController;
	}

	PVOID(*CollectGarbageInternal)(uint32_t, bool) = nullptr;
	PVOID CollectGarbageInternalHook(uint32_t KeepFlags, bool bPerformFullPurge)
	{
		return NULL;
	}

	void InitHooks()
	{
		Replication::InitOffsets();

		auto BaseAddr = Util::BaseAddress();

		UWorld_NotifyControlMessage = decltype(UWorld_NotifyControlMessage)(BaseAddr + Offsets::WorldNotifyControlMessage);

		auto AOnlineBeaconHost_NotifyControlMessageAddr = BaseAddr + Offsets::BeaconNotifyControlMessage;

		auto WelcomePlayerAddr = BaseAddr + Offsets::WelcomePlayer;
		auto SpawnPlayActorAddr = BaseAddr + Offsets::SpawnPlayActor;
		auto TickFlushAddr = BaseAddr + Offsets::TickFlush;

		InitHost = decltype(InitHost)(BaseAddr + Offsets::InitHost);
		TickFlush = decltype(TickFlush)(TickFlushAddr);
		SpawnPlayActor = decltype(SpawnPlayActor)(SpawnPlayActorAddr);
		NotifyActorDestroyed = decltype(NotifyActorDestroyed)(BaseAddr + Offsets::NotifyActorDestroyed);

		MH_CreateHook((void*)(AOnlineBeaconHost_NotifyControlMessageAddr), AOnlineBeaconHost_NotifyControlMessageHook, nullptr);
		MH_EnableHook((void*)(AOnlineBeaconHost_NotifyControlMessageAddr));
		MH_CreateHook((void*)(WelcomePlayerAddr), WelcomePlayerHook, (void**)(&WelcomePlayer));
		MH_EnableHook((void*)(WelcomePlayerAddr));
		MH_CreateHook((void*)(SpawnPlayActorAddr), SpawnPlayActorHook, (void**)(&SpawnPlayActor));
		MH_EnableHook((void*)(SpawnPlayActorAddr));
		MH_CreateHook((void*)(BaseAddr + Offsets::KickPatch), KickPatch, nullptr);
		MH_EnableHook((void*)(BaseAddr + Offsets::KickPatch));

		auto pCollectGarbageInternalAddress = Util::FindPattern("\x48\x8B\xC4\x48\x89\x58\x08\x88\x50\x10", "xxxxxxxxxx");
		MH_CreateHook(static_cast<LPVOID>(pCollectGarbageInternalAddress), CollectGarbageInternalHook, reinterpret_cast<LPVOID*>(&CollectGarbageInternal));
		MH_EnableHook(static_cast<LPVOID>(pCollectGarbageInternalAddress));

		Beacon = (AOnlineBeaconHost*)(Util::SpawnActor(AOnlineBeaconHost::StaticClass(), {}, {}));
		Beacon->ListenPort = 7777;
		if (InitHost(Beacon))
		{
			Beacon->NetDriver->World = Globals::World;
			Globals::World->LevelCollections[0].NetDriver = Beacon->NetDriver;
			Globals::World->LevelCollections[1].NetDriver = Beacon->NetDriver;

			((AOnlineBeacon*)Beacon)->BeaconState = 0;

			MH_CreateHook((void*)(TickFlushAddr), TickFlushHook, (void**)(&TickFlush));
			MH_EnableHook((void*)(TickFlushAddr));

			LOG("Server is now listening!");
		}
	}
}