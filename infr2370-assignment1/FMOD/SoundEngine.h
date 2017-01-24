//Marc Tremblay 01/23/2017
//100555250

#pragma once
#pragma comment(lib, "FMOD/fmod_vc.lib") //can also be done in project settings

#include "fmod.hpp"
#include "fmod_errors.h"

#include <Windows.h>
#include <iostream> //cout

void CheckResult(FMOD_RESULT result);

class SoundEngine 
{
private:
	bool systemInit;
public:
	SoundEngine();
	~SoundEngine();

	bool Init();
	void Update();


	FMOD::System	*system;
	void			*driverData;

	//Listener
	FMOD_VECTOR listenerForward;
	FMOD_VECTOR listenerUp;
	FMOD_VECTOR listenerPos;
	FMOD_VECTOR listenerVel;
};

class Sound
{
public:
	Sound();
	~Sound();

	bool Load(char* filename);
	void Play();

	static void SystemUpdate();

	FMOD::Sound *sound;
	FMOD::Channel *channel;
	FMOD_VECTOR pos;
	FMOD_VECTOR vel;

	static SoundEngine sys;
};