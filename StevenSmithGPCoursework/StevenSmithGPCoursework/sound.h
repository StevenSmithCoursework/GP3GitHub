#pragma once

// Include files
#include "include\OpenAL\al.h"
#include "include\OpenAL\alc.h"
#include "include\OpenAL\alut.h"
#include <string>
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <map>

using namespace std;

class sound
{
public:
	sound();
	~sound();

	void loadWAVFile(LPCSTR filename);
	void playAudio(ALboolean sndLoop);
	void stopAudio();
	void cleanUp();

private:

	char*        m_OALData;           //data for the buffer
	ALenum       m_OALFormat;         //buffer format
	ALsizei      m_OALFrequency;      //frequency
	long         m_OALBufferLen;      //bit depth
	int			 m_OALChannels;		  // Channels
	int			 m_OALSize;			  // Size
	int			 m_OALBitRate;		  // Bit Rate
	float        m_OALLength;		  // Length
	ALboolean    m_OALLoop;           //loop
	unsigned int m_OALSource;         //source
	ALuint       m_OALBuffer;         // Buffer
	ALboolean    m_OALbEAX;			  // for EAX 2.0 support
	ALboolean    m_alLoop;			  //loop

	struct FMTCHUNK {
		short format;
		short channels;
		unsigned long srate;
		unsigned long bps;
		short balign;
		short samp;
	};

	void LoadWAVInfo(ifstream &filename, string &name, unsigned int &size);
};

