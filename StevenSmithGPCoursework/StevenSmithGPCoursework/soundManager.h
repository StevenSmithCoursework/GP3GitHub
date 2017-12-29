#pragma once

#include "sound.h"

using namespace std;

class soundManager
{
public:
	void add(LPCSTR sndName, LPCSTR fileName);
	sound* getSnd(LPCSTR sndName);
	void deleteSnd();
	static soundManager* getInstance();

protected:
	soundManager();
	~soundManager();
	map <LPCSTR, sound*> gameSnds;
	void createContext();

private:
	static soundManager* pInstance;
	ALCcontext *m_OALContext;
	ALCdevice *m_OALDevice;
};

