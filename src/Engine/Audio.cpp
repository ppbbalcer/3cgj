#include "Audio.h"

AudioSound::AudioSound(const char *file) {
	s = Mix_LoadWAV(file);
}

AudioSound::~AudioSound() {
	if (s) {
		Mix_FreeChunk(s);
	}
}

void AudioSound::play() {
	if (s) {
		Mix_PlayChannel(-1, s, 0);
	}
}

AudioMusic::AudioMusic(const char *file) {
	m = Mix_LoadMUS(file);
}

AudioMusic::~AudioMusic() {
	if (m) {
		Mix_FreeMusic(m);
	}
}

void AudioMusic::play() {
	Mix_PlayMusic(m, -1);
}

void AudioMusic::pause() {
	Mix_PauseMusic();
}

void AudioMusic::stop() {
	Mix_HaltMusic();
}

AudioEngine::AudioEngine() {
	init = Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0;
}

AudioEngine::~AudioEngine() {
	if (init)
		Mix_CloseAudio();

	for (size_t i = 0; i < musics.size(); ++i) {
		delete musics[i];
	}
	for (size_t i = 0; i < sounds.size(); ++i) {
		delete sounds[i];
	}
	Mix_Quit();
}

AudioMusic *AudioEngine::loadMusic(const char *file) {
	if (!init)
		return NULL;

	AudioMusic *m = new AudioMusic(file);
	musics.push_back(m);
}

AudioSound *AudioEngine::loadSound(const char *file) {
	if (!init)
		return NULL;

	AudioSound *s = new AudioSound(file);
	sounds.push_back(s);
}
