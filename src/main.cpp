#include <iostream>
#include "muxer.hpp"
#include "playback.hpp"
#include <SDL2/SDL.h>

using namespace std;

int main (int argc, char* argv[])
{
  atexit(SDL_Quit); // Automatically Quit SDL on Program Exit
  cout << "Spectrum Analyzer" << endl;
  char* pcFilename = NULL;
  for (int i = 0; i < argc; i++) {
    char* arg = argv[i];
    char firstc = *arg;
    if (firstc == '-') {
      if ((*(arg + 1) == 'i') && ((i+1) < argc)) {
        pcFilename = argv[i+1];
      }
    }
  }
  if (pcFilename == NULL){
    cout << "No Filename given! Please specify input file with -i" << endl;
    return 0;
  }
  short* wave = NULL;
  WAVEFORMAT format;
  long bytelenght;
  if (fDemuxWav(&wave, pcFilename, &format, &bytelenght))
  {
    cout << "Encountered Read Error! :-(" << endl;
    return 1;
  }
  long samplecount = bytelenght/format.wBlockAlign;
  cout << "Channels   : " << format.wChannels << endl;
  cout << "Sample Rate: " << format.dwSamplesPerSec << endl;
  cout << "Bitrate    : " << format.dwAvgBytesPerSec << endl;
  cout << "Block Align: " << format.wBlockAlign << endl;
  cout << "Bits/Sample: " << format.wBitsPerSample << endl;
  cout << "Num Blocks : " << samplecount << endl;
  int seconds = samplecount/format.dwSamplesPerSec;
  int minutes = seconds/60;
  seconds = seconds%60;
  cout << "Duration   : " << minutes << ":" << seconds << endl;

  if (SDL_Init(SDL_INIT_EVENTS | SDL_INIT_AUDIO))
  {
    cout << "SDL_Init failed! " << SDL_GetError() << endl;
    return 1;
  }

	fPlayback(wave, format, bytelenght);

  delete[] wave;
  wave = NULL;
  return 0;
}
