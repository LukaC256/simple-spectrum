//#include "muxer.hpp"
#include <iostream>
#include <cstring>
#include <fstream>
#include <cmath>
#include "utils.hpp"
using namespace std;
EResult fDemuxWav(short** wave, char* cFilename, WAVEFORMAT* format, long* bytecount)
{
  ifstream iFile(cFilename, ios::binary);
  if (iFile.is_open() == false){
    cout << "File isn't found. Please check your Filename" << endl;
    return ER_E_IO;
  }
  char cFOURCC[4];
  iFile.read((char*) &cFOURCC, 4);
  if (strncmp(cFOURCC, "RIFF", 4))
  {
    cout << "No RIFF FOURCC found! This is not a WAVE File!" << endl;
    iFile.close();
    return ER_E_INVALIDFILE;
  }
  iFile.seekg(4, ios_base::cur);
  iFile.read((char*) &cFOURCC, 4);
  if (strncmp(cFOURCC, "WAVE", 4))
  {
    cout << "No WAVE FOURCC found! Make sure it's a Microsoft WAVE File!" << endl;
    iFile.close();
    return ER_E_INVALIDFILE;
  }

  iFile.read((char*) &cFOURCC, 4);
  if (strncmp(cFOURCC, "fmt ", 4)) {
    cout << "Format Chunk missing or not first Chunk" << endl;
    iFile.close();
    return ER_E_INVALIDFILE;
  }
  uint32_t dwChunkSize;
  iFile.read((char*) &dwChunkSize, 4);
  if (dwChunkSize != sizeof(WAVEFORMAT)) {
    cout << "Format Chunk has invalid size. The file is probably not PCM_S16LE encoded!" << endl;
    iFile.close();
    return ER_E_INVALIDFILE;
  }
  iFile.read((char*) format, sizeof(WAVEFORMAT));

  bool bFoundData = false;
  while (!iFile.eof()) {
    iFile.read((char*) &cFOURCC, 4);
    if (!strncmp(cFOURCC, "data", 4)) {
      cout << "Reading Data ...";
      iFile.read((char*) bytecount, 4);
      *wave = new short[*bytecount/2];
      iFile.read((char*) *wave, *bytecount);
      bFoundData = true;
      cout << "Done!" << endl;
      break;
    }
    else
    {
      long ChunkLenght;
      iFile.read((char*) &ChunkLenght, 4);
      iFile.seekg(ChunkLenght, ios_base::cur);
    }
  }
  if (!bFoundData)
  {
    cout << "Did not find Wave Data!";
    iFile.close();
    return ER_E_INVALIDFILE;
  }
  iFile.close();
  return ER_S_OK;
};
