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

// BlueprintGeneratedClass GE_Constructor_SafetyProtocols.GE_Constructor_SafetyProtocols_C
// 0x0000 (0x0670 - 0x0670)
class UGE_Constructor_SafetyProtocols_C : public UGET_BuildDamageResist_C
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass GE_Constructor_SafetyProtocols.GE_Constructor_SafetyProtocols_C");
		return ptr;
	}

};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif