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

static UNIT g15_drum_unit =
{
    next:            NULL,
    action:          &g15_drum_svc,
    filename:        NULL,
    fileref:         NULL,
    filebuf:         NULL,
    hwmark:          0,
    time:            0,
    flags:           UNIT_FIX,
    dynflags:        0,
    capac:           0,
    pos:             0,
    io_flush:        NULL,
    iostarttime:     0,
    buf:             0,
    wait:            0,
    u3:              0,
    u4:              0,
    u5:              0,
    u6:              0,
    up7:             NULL,
    up8:             NULL,
    us9:             0,
    us10:            0,
    disk_type:       0,
    tmxr:            NULL,
    recsize:         0,
    tape_eom:        0,
    cancel:          NULL,
    usecs_remaining: 0,
    uname:           NULL,
    dptr:            NULL,
    dctrl:           0};

REG g15_drum_reg[] =
{
};

MTAB g15_drum_mod[] =
{
};

DEVICE g15_drum_dev =
{
    name:        "Drum",
    units:       &g15_drum_unit,
    registers:   g15_drum_reg,
    modifiers:   g15_drum_mod,
    numunits:    1,
};

const char *g15_drum_desc(DEVICE *dptr)
{
    return "drum";
}

t_stat g15_drum_svc(UNIT *uptr)
{
    return SCPE_OK;
}

t_stat g15_drum_reset(DEVICE *dptr)
{
    sim_cancel(&g15_drum_unit);
    return SCPE_OK;
}

t_stat g15_drum_cmd(uint16_t cmd)
{
    g15_util_trace_enter(__FUNCTION__);
    switch (cmd)
    {
        default:
            break;
    }
    g15_util_trace_leave();
    return SCPE_OK;
}

uint32_t g15_drum_rd(uint8_t line, uint8_t word)
{
    return g15_drum[line][word];
}

void g15_drum_wr(uint8_t line, uint8_t word, uint32_t data)
{
    g15_drum[line][word] = data;
}
