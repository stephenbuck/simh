#include <ctype.h>
#include "g15_defs.h"

#include "sim_video.h"

static UNIT g15_bell_unit =
{
    next:            NULL,
    action:          &g15_bell_svc,
    filename:        NULL,
    fileref:         NULL,
    filebuf:         NULL,
    hwmark:          0,
    time:            0,
    flags:           UNIT_RO | UNIT_SEQ | UNIT_DISABLE,
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

REG g15_bell_reg[] =
{
};

MTAB g15_bell_mod[] =
{
};

DEVICE g15_bell_dev =
{
    name:        "Bell",
    units:       &g15_bell_unit,
    registers:   g15_bell_reg,
    modifiers:   g15_bell_mod,
    numunits:    1,
};

const char *g15_bell_desc(DEVICE *dptr)
{
    return "Bell";
}

t_stat g15_bell_svc(UNIT *uptr)
{
    return SCPE_OK;
}

t_stat g15_bell_reset(DEVICE *dptr)
{
    sim_cancel(&g15_bell_unit);
    return SCPE_OK;
}

t_stat g15_bell_cmd(uint16_t cmd)
{
    g15_util_trace_enter(__FUNCTION__);
    switch (cmd)
    {
        case G15_BELL_CMD_RING:
                vid_beep();
                break;
        default:
            break;
    }
    g15_util_trace_leave();
    return SCPE_OK;
}
