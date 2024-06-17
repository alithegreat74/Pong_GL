#include <irrKlang/irrKlang.h>
#include <string>

/// <summary>
/// In this section of the project we manage an play audios using the irrklang library
/// we create a sound engine and play pretty much anything we want with that sound engine
/// once the application is closed, we clean up the sound engine pointer so we won't have memory problems(this part is not needed but seemed like the right way to do it)
/// </summary>

namespace Audio {

	extern irrklang::ISoundEngine* engine;

	void PlayAudio(std::string name,bool loop);
	void Cleanup();
}