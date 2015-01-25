#ifndef __AUDIO_H__
#define __AUDIO_H__

#include <vector>
#include <SDL_mixer.h>

class AudioSound {
public:
	AudioSound(const char *file);
	~AudioSound();
	void play(int channel = -1, int loop = 0, int delay = 0);
	void stop();
	void setDelay(int delay);
	void setVolume(float v);
	void update(int time);
private:
	Mix_Chunk *s;
	int timer;
	int base_delay;
	int scheduled_channel;
};

class AudioMusic {
public:
	AudioMusic(const char *file);
	~AudioMusic();
	void play();
	void pause();
	void stop();
	void setVolume(float v);
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