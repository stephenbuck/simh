#include "g15_defs.h"
#include <ctype.h>

#if 0
static G15_DRUM =
{
   lines =
   {
      { name:  "0", size: 108, flags: STD | CMD,      words: {0} },
      { name:  "1", size: 108, flags: STD | CMD,      words: {0} },
      { name:  "2", size: 108, flags: STD | CMD,      words: {0} },
      { name:  "3", size: 108, flags: STD | CMD,      words: {0} },
      { name:  "4", size: 108, flags: STD | CMD,      words: {0} },
      { name:  "5", size: 108, flags: STD | CMD,      words: {0} },
      { name:  "6", size: 108, flags: STD,            words: {0} },
      { name:  "7", size: 108, flags: STD,            words: {0} },
      { name:  "8", size: 108, flags: STD,            words: {0} },
      { name:  "9", size: 108, flags: STD,            words: {0} },
      { name: "10", size: 108, flags: STD,            words: {0} },
      { name: "11", size: 108, flags: STD,            words: {0} },
      { name: "12", size: 108, flags: STD,            words: {0} },
      { name: "13", size: 108, flags: STD,            words: {0} },
      { name: "14", size: 108, flags: STD,            words: {0} },
      { name: "15", size: 108, flags: STD,            words: {0} },
      { name: "16", size: 108, flags: STD,            words: {0} },
      { name: "17", size: 108, flags: STD,            words: {0} },
      { name: "18", size: 108, flags: STD,            words: {0} },
      { name: "19", size: 108, flags: STD | CMD | IO, words: {0} },
      { name: "20", size:   4, flags: STD,            words: {0} },
      { name: "21", size:   4, flags: STD,            words: {0} },
      { name: "22", size:   4, flags: STD,            words: {0} },
      { name: "23", size:   4, flags: STD | MTA,      words: {0} },
      { name: "ID", size:   2, flags: STD,            words: {0} },
      { name: "PN", size:   2, flags: STD,            words: {0} },
      { name: "MQ", size:   2, flags: STD,            words: {0} },
      { name: "AR", size:   1, flags: STD | CMD | IO, words: {0} },
      { name: "NT", size: 108, flags: NUM,            words: {0} }
   }
};
#endif

static uint32_t g15_drum[G15_DRUM_LINES][G15_DRUM_WORDS];

uint32_t g15_drum_rd(uint8_t line, uint8_t word)
{
    return g15_drum[line][word];
}

void g15_drum_wr(uint8_t line, uint8_t word, uint32_t data)
{
    g15_drum[line][word] = data;
}
