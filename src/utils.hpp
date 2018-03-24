#ifndef INC_UTILS
#define INC_UTILS

enum EResult {
  ER_S_OK = 0,
  ER_E_GENERAL = 1,
  ER_E_IO = 2,
  ER_E_MATH = 3,
  ER_E_NULLPNTR = 4,
  ER_E_INVALIDFILE = 5,
  ER_E_MAKESNOSENSE = 42
};

struct WAVEFORMAT {
  uint16_t wFormatTag;
  uint16_t wChannels;
  uint32_t dwSamplesPerSec;
  uint32_t dwAvgBytesPerSec;
  uint16_t wBlockAlign;
  uint16_t wBitsPerSample;
};

#endif
