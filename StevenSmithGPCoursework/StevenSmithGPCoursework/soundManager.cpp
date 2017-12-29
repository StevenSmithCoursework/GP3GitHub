#include "soundManager.h"

soundManager* soundManager::pInstance = NULL;


soundManager::soundManager()
{
	createContext();
}

soundManager* soundManager::getInstance()
{
	if (pInstance == NULL)
	{
		pInstance = new soundManager();
	}
	return soundManager::pInstance;
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

void soundManager::add(LPCSTR sndName, LPCSTR filename)
{
	if (!getSnd(sndName))
	{
		sound * newSnd = new sound();
		newSnd->loadWAVFile(filename);
		gameSnds.insert(make_pair(sndName, newSnd));
	}
}

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

void soundManager::deleteSnd()
{
	for (map<LPCSTR, sound*>::iterator snd = gameSnds.begin(); snd != gameSnds.end(); ++snd)
	{
		delete snd->second;
	}
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
