// Copyright(c) 2022, NVIDIA CORPORATION. All rights reserved.
//
// NVIDIA CORPORATION and its licensors retain all intellectual property
// and proprietary rights in and to this software, related documentation
// and any modifications thereto.Any use, reproduction, disclosure or
// distribution of this software and related documentation without an express
// license agreement from NVIDIA CORPORATION is strictly prohibited.

#include "OmniverseAudioMixer.h"
#include "OmniverseMixerDevice.h"

void FOmniverseAudioMixerModule::SetPlatformInterface(Audio::IAudioMixerPlatformInterface* Interface)
{
	AudioMixerPlatformInterface = Interface;
}

FAudioDevice* FOmniverseAudioMixerModule::CreateAudioDevice()
{
	if (AudioMixerPlatformInterface)
	{
		return new Audio::FOmniverseMixerDevice(AudioMixerPlatformInterface, SampleRate);
	}

	return nullptr;
}

IMPLEMENT_MODULE(FOmniverseAudioMixerModule, OmniverseAudioMixer);
