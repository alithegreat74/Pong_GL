#include "AudioManager.h"

//defining the external variables
irrklang::ISoundEngine* Audio::engine;

//play an audio from file
void Audio::PlayAudio(std::string name, bool loop)
{
	if (Audio::engine == NULL) {
		Audio::engine = irrklang::createIrrKlangDevice();
	}
	engine->play2D(name.c_str(), loop);
}
void Audio::Cleanup()
{
	engine->drop();
}

