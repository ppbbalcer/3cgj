#include "Audio.h"

AudioSound::AudioSound(const char *file) {
	s = Mix_LoadWAV(file);
	timer = 0;
	scheduled_channel = 0;
	base_delay = 0;
}

AudioSound::~AudioSound() {
	if (s) {
		Mix_FreeChunk(s);
	}
}

void AudioSound::play(int channel, int loop, int delay) {
	if (s) {
		if (delay) {
			base_delay = delay;
			scheduled_channel = channel;
		} else {
			Mix_PlayChannel(channel, s, loop);
		}
	}
}

void AudioSound::update(int time) {
	if (base_delay == 0)
		return;

	timer -= time;
	if (timer < 0) {
		Mix_PlayChannel(scheduled_channel, s, 0);
		timer = base_delay;
	}
}

void AudioSound::setDelay(int delay) {
	base_delay = delay;
}

void AudioSound::stop() {
	timer = 0;
	scheduled_channel = 0;
	base_delay = 0;	
}

void AudioSound::setVolume(float v) {
	Mix_VolumeChunk(s, (int)(v*MIX_MAX_VOLUME));
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
	init = Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == 0;
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
	return m;
}

AudioSound *AudioEngine::loadSound(const char *file) {
	if (!init)
		return NULL;

	AudioSound *s = new AudioSound(file);
	sounds.push_back(s);
	return s;
}
