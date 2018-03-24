#ifndef INC_MUXER
#define INC_MUXER

#include <iostream>
#include <fstream>
#include <cstring>
#include "utils.hpp"

using namespace std;

EResult fDemuxWav(short** wave, char* cFilename, WAVEFORMAT* format, long* bytecount);

#endif
