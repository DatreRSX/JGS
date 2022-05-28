#pragma once

// Fortnite (2.4.2) SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "../SDK.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass GCNL_GM_OnLowHealth_Berzerker.GCNL_GM_OnLowHealth_Berzerker_C
// 0x0008 (0x0498 - 0x0490)
class AGCNL_GM_OnLowHealth_Berzerker_C : public AFortGameplayCueNotify_Looping
{
public:
	class UParticleSystemComponent*                    BodyMistFX;                                               // 0x0490(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass GCNL_GM_OnLowHealth_Berzerker.GCNL_GM_OnLowHealth_Berzerker_C");
		return ptr;
	}


	bool OnRemove(class AActor** MyTarget, struct FGameplayCueParameters* Parameters);
	bool OnActive(class AActor** MyTarget, struct FGameplayCueParameters* Parameters);
	void UserConstructionScript();
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
