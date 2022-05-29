#pragma once

// Fortnite (4.1) SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// Class AudioMixer.SynthComponent
// 0x03C0 (0x0650 - 0x0290)
class USynthComponent : public USceneComponent
{
public:
	unsigned char                                      bAutoDestroy : 1;                                         // 0x0290(0x0001)
	unsigned char                                      bStopWhenOwnerDestroyed : 1;                              // 0x0290(0x0001)
	unsigned char                                      bAllowSpatialization : 1;                                 // 0x0290(0x0001) (Edit, BlueprintVisible)
	unsigned char                                      bOverrideAttenuation : 1;                                 // 0x0290(0x0001) (Edit, BlueprintVisible)
	unsigned char                                      UnknownData00[0x7];                                       // 0x0291(0x0007) MISSED OFFSET
	class USoundAttenuation*                           AttenuationSettings;                                      // 0x0298(0x0008) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	struct FSoundAttenuationSettings                   AttenuationOverrides;                                     // 0x02A0(0x02A8) (Edit, BlueprintVisible)
	class USoundConcurrency*                           ConcurrencySettings;                                      // 0x0548(0x0008) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	class USoundClass*                                 SoundClass;                                               // 0x0550(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
	class USoundEffectSourcePresetChain*               SourceEffectChain;                                        // 0x0558(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
	class USoundSubmix*                                SoundSubmix;                                              // 0x0560(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
	TArray<struct FSoundSubmixSendInfo>                SoundSubmixSends;                                         // 0x0568(0x0010) (Edit, BlueprintVisible, ZeroConstructor)
	unsigned char                                      bIsUISound : 1;                                           // 0x0578(0x0001) (Edit, BlueprintVisible)
	unsigned char                                      UnknownData01[0x3];                                       // 0x0579(0x0003) MISSED OFFSET
	int                                                EnvelopeFollowerAttackTime;                               // 0x057C(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	int                                                EnvelopeFollowerReleaseTime;                              // 0x0580(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData02[0x4];                                       // 0x0584(0x0004) MISSED OFFSET
	struct FScriptMulticastDelegate                    OnAudioEnvelopeValue;                                     // 0x0588(0x0010) (ZeroConstructor, InstancedReference, BlueprintAssignable)
	unsigned char                                      UnknownData03[0x80];                                      // 0x0598(0x0080) MISSED OFFSET
	class USynthSound*                                 Synth;                                                    // 0x0618(0x0008) (ZeroConstructor, Transient, IsPlainOldData)
	class UAudioComponent*                             AudioComponent;                                           // 0x0620(0x0008) (ExportObject, ZeroConstructor, Transient, InstancedReference, IsPlainOldData)
	unsigned char                                      UnknownData04[0x28];                                      // 0x0628(0x0028) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class AudioMixer.SynthComponent");
		return ptr;
	}


	void Stop();
	void Start();
	void SetVolumeMultiplier(float VolumeMultiplier);
	void SetSubmixSend(class USoundSubmix* Submix, float SendLevel);
	bool IsPlaying();
};


// Class AudioMixer.AudioMixerBlueprintLibrary
// 0x0000 (0x0028 - 0x0028)
class UAudioMixerBlueprintLibrary : public UBlueprintFunctionLibrary
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class AudioMixer.AudioMixerBlueprintLibrary");
		return ptr;
	}


	void STATIC_SetBypassSourceEffectChainEntry(class UObject* WorldContextObject, class USoundEffectSourcePresetChain* PresetChain, int EntryIndex, bool bBypassed);
	void STATIC_RemoveSourceEffectFromPresetChain(class UObject* WorldContextObject, class USoundEffectSourcePresetChain* PresetChain, int EntryIndex);
	void STATIC_RemoveMasterSubmixEffect(class UObject* WorldContextObject, class USoundEffectSubmixPreset* SubmixEffectPreset);
	int STATIC_GetNumberOfEntriesInSourceEffectChain(class UObject* WorldContextObject, class USoundEffectSourcePresetChain* PresetChain);
	void STATIC_ClearMasterSubmixEffects(class UObject* WorldContextObject);
	void STATIC_AddSourceEffectToPresetChain(class UObject* WorldContextObject, class USoundEffectSourcePresetChain* PresetChain, const struct FSourceEffectChainEntry& Entry);
	void STATIC_AddMasterSubmixEffect(class UObject* WorldContextObject, class USoundEffectSubmixPreset* SubmixEffectPreset);
};


// Class AudioMixer.SubmixEffectDynamicsProcessorPreset
// 0x0078 (0x00B8 - 0x0040)
class USubmixEffectDynamicsProcessorPreset : public USoundEffectSubmixPreset
{
public:
	unsigned char                                      UnknownData00[0x50];                                      // 0x0040(0x0050) MISSED OFFSET
	struct FSubmixEffectDynamicsProcessorSettings      Settings;                                                 // 0x0090(0x0028) (Edit, BlueprintVisible)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class AudioMixer.SubmixEffectDynamicsProcessorPreset");
		return ptr;
	}


	void SetSettings(const struct FSubmixEffectDynamicsProcessorSettings& InSettings);
};


// Class AudioMixer.SubmixEffectSubmixEQPreset
// 0x0048 (0x0088 - 0x0040)
class USubmixEffectSubmixEQPreset : public USoundEffectSubmixPreset
{
public:
	unsigned char                                      UnknownData00[0x38];                                      // 0x0040(0x0038) MISSED OFFSET
	struct FSubmixEffectSubmixEQSettings               Settings;                                                 // 0x0078(0x0010) (Edit, BlueprintVisible)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class AudioMixer.SubmixEffectSubmixEQPreset");
		return ptr;
	}


	void SetSettings(const struct FSubmixEffectSubmixEQSettings& InSettings);
};


// Class AudioMixer.SubmixEffectReverbPreset
// 0x0088 (0x00C8 - 0x0040)
class USubmixEffectReverbPreset : public USoundEffectSubmixPreset
{
public:
	unsigned char                                      UnknownData00[0x58];                                      // 0x0040(0x0058) MISSED OFFSET
	struct FSubmixEffectReverbSettings                 Settings;                                                 // 0x0098(0x0030) (Edit, BlueprintVisible)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class AudioMixer.SubmixEffectReverbPreset");
		return ptr;
	}


	void SetSettingsWithReverbEffect(class UReverbEffect* InReverbEffect, float WetLevel);
	void SetSettings(const struct FSubmixEffectReverbSettings& InSettings);
};


// Class AudioMixer.SynthSound
// 0x0020 (0x02B0 - 0x0290)
class USynthSound : public USoundWaveProcedural
{
public:
	unsigned char                                      UnknownData00[0x20];                                      // 0x0290(0x0020) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class AudioMixer.SynthSound");
		return ptr;
	}

};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
