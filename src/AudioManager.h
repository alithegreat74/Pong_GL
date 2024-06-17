#include <irrKlang/irrKlang.h>
#include <string>

namespace Audio {

	extern irrklang::ISoundEngine* engine;

	void PlayAudio(std::string name,bool loop);
	void Cleanup();
}