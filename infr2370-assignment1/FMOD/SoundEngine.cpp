//Marc Tremblay 01/23/2017
//100555250

#include "SoundEngine.h"

FMOD_RESULT result;

void CheckResult(FMOD_RESULT result)
{
	if (result != FMOD_OK)
	{
		std::string msg = FMOD_ErrorString(result);
	}
}

SoundEngine::SoundEngine()
{
	systemInit = false;

	system = NULL;
	driverData = NULL;

	listenerForward = { 0.0f, 0.0f,  1.0f };
	listenerUp		= { 0.0f, 1.0f,  0.0f };
	listenerPos		= { 0.0f, 0.0f,  0.0f };
	listenerVel		= { 0.0f, 0.0f,  0.0f };
}

SoundEngine::~SoundEngine()
{
	if (systemInit)
	{
		result = system->close();					CheckResult(result);
		result = system->release();					CheckResult(result);
	}
}

bool SoundEngine::Init()
{
	if (systemInit) return true;

	unsigned int version;
	result = FMOD::System_Create(&system);			CheckResult(result);
	result = system->getVersion(&version);			CheckResult(result);

	if (version < FMOD_VERSION)
	{
		std::cout << "FMOD lib version doesn't match header!" << std::endl;
		return false;
	}

	result = system->init(100, FMOD_INIT_NORMAL, driverData);					CheckResult(result);
	if (result != FMOD_OK)
	{
		std::cout << "FMOD Initialization Failed!" << std::endl;
		return false;
	}

	result = system->set3DSettings(1.0, 1.0f, 1.0f);							CheckResult(result);
	
	systemInit = true;
	return true;
}

void SoundEngine::Update()
{
	result = system->set3DListenerAttributes(0, &listenerPos, &listenerVel, &listenerForward, &listenerUp);
	CheckResult(result);

	result = system->update();						CheckResult(result);
}

SoundEngine Sound::sys;

Sound::Sound()
{
	sound = NULL;
	channel = NULL;
	pos = { 0.0f, 0.0f, 0.0f };
	vel = { 0.0f, 0.0f, 0.0f };
}

Sound::Sound(FMOD_VECTOR a_pos)
{
	sound = NULL;
	channel = NULL;
	pos = a_pos;
	vel = { 0.0f, 0.0f, 0.0f };
}

Sound::~Sound()
{
	result = sound->release();						CheckResult(result);
}

bool Sound::Load(char* filename)
{
	sys.Init();
	result = sys.system->createSound(filename, FMOD_3D, 0, &sound); 			CheckResult(result);

	if (result != FMOD_OK)
	{
		std::cout << " Failed to load file: " << filename << std::endl;
		return false;
	}

	result = sound->set3DMinMaxDistance(0.5f, 5000.0f); 						CheckResult(result);
	result = sound->setMode(FMOD_LOOP_NORMAL);									CheckResult(result);
	return true;
}
void Sound::Play()
{
	result = sys.system->playSound(sound, 0, true, &channel);					CheckResult(result);
	result = channel->set3DAttributes(&pos, &vel);								CheckResult(result);
	result = channel->setPaused(false);											CheckResult(result);
}

void Sound::SystemUpdate()
{
	sys.Update();
}