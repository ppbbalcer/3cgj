#ifndef __AUDIO_H__
#define __AUDIO_H__

#include <vector>
#include <SDL_mixer.h>

class AudioSound {
public:
	AudioSound(const char *file);
	~AudioSound();
	void play();
private:
	Mix_Chunk *s;
};

class AudioMusic {
public:
	AudioMusic(const char *file);
	~AudioMusic();
	void play();
	void pause();
	void stop();
private:
	Mix_Music *m;
};

class AudioEngine {
public:
	AudioEngine();
	~AudioEngine();
	AudioMusic *loadMusic(const char *file);
	AudioSound *loadSound(const char *file);
private:
	std::vector<AudioMusic*> musics;
	std::vector<AudioSound*> sounds;
	bool init;
};

#endif