#include <SDL2/SDL.h>
#include <iostream>
#include "utils.hpp"

using namespace std;

EResult fPlayback(short* wave, WAVEFORMAT format, long bytecount)
{
  SDL_AudioSpec audiospec;
  audiospec.freq = format.dwSamplesPerSec;
  audiospec.format = AUDIO_S16LSB;
  audiospec.channels = format.wChannels;
  audiospec.samples = 4096;
	audiospec.callback = NULL;
	SDL_AudioDeviceID device = SDL_OpenAudioDevice(NULL, 0, &audiospec, NULL, 0);
	if (device == 0) {
		cout << "Failed to open Audio Device: " << SDL_GetError() << endl;
		return ER_E_GENERAL;
	}

	SDL_QueueAudio(device, (void*) wave, bytecount);
	SDL_PauseAudioDevice(device, 0);
	cout << "Currently Playing, type q to quit." << endl;
	char inchar = '\0';

	do {
		inchar = getchar();
	} while(inchar != 'q');

	SDL_CloseAudioDevice(device);
  return ER_S_OK;
}
