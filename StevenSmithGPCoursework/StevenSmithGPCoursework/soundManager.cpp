#include "soundManager.h"
//Set instance to NULL
soundManager* soundManager::pInstance = NULL;

//Call create context
soundManager::soundManager()
{
	createContext();
}
//Create an instance
soundManager* soundManager::getInstance()
{
	if (pInstance == NULL)
	{
		pInstance = new soundManager();
	}
	return soundManager::pInstance;
}

void soundManager::release()
{
	delete pInstance;
	pInstance = NULL;
}

void soundManager::createContext()
{
	m_OALDevice = alcOpenDevice(NULL);
	if (m_OALDevice)
	{
		//Create a context
		m_OALContext = alcCreateContext(m_OALDevice, NULL);

		//Set active context
		alcMakeContextCurrent(m_OALContext);
	}
}
//Save a sound
void soundManager::add(LPCSTR sndName, LPCSTR filename)
{
	if (!getSnd(sndName))
	{
		sound * newSnd = new sound();
		newSnd->loadWAVFile(filename);
		gameSnds.insert(make_pair(sndName, newSnd));
	}
}
//Play a sound
sound* soundManager::getSnd(LPCSTR sndName)
{
	map<LPCSTR, sound*>::iterator snd = gameSnds.find(sndName);
	if (snd != gameSnds.end())
	{
		return snd->second;
	}
	else
	{
		return NULL;
	}
}
//Attempt to stop audio (not working)
void soundManager::deleteSnd()
{
	sound stopAudio();
}


soundManager::~soundManager()
{
	m_OALContext = alcGetCurrentContext();

	//Get device for active context
	m_OALDevice = alcGetContextsDevice(m_OALContext);

	//Release context(s)
	alcDestroyContext(m_OALContext);

	//Close device
	alcCloseDevice(m_OALDevice);
}
