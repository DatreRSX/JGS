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

// BlueprintGeneratedClass ButtonStyle-HighlightEmphasized.ButtonStyle-HighlightEmphasized_C
// 0x0000 (0x0470 - 0x0470)
class UButtonStyle_HighlightEmphasized_C : public UButtonStyle_MediumTransparentNoCues_C
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass ButtonStyle-HighlightEmphasized.ButtonStyle-HighlightEmphasized_C");
		return ptr;
	}

};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
