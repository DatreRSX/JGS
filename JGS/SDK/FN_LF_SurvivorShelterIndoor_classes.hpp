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

// BlueprintGeneratedClass LF_SurvivorShelterIndoor.LF_SurvivorShelterIndoor_C
// 0x0000 (0x0F10 - 0x0F10)
class ALF_SurvivorShelterIndoor_C : public ABuildingFoundation5x5
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass LF_SurvivorShelterIndoor.LF_SurvivorShelterIndoor_C");
		return ptr;
	}

};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
