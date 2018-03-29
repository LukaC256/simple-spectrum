#include <iostream>
#include "muxer.hpp"

using namespace std;

int main (int argc, char* argv[])
{
  cout << "WINAE ADPCM encoder" << endl;
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
  cout << "Num Samples: " << samplecount << endl;


  delete[] wave;
  wave = NULL;
  return 0;
}
