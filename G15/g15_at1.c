#include "g15_defs.h"
#include <ctype.h>

UNIT g15_at1_unit =
{
    next:            NULL,
    action:          &g15_at_svc,
    filename:        NULL,
    fileref:         NULL,
    filebuf:         NULL,
    hwmark:          0,
    time:            0,
    flags:           UNIT_SEQ | UNIT_DISABLE,
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
    dctrl:           0
};

REG g15_at1_reg[] =
{
};

MTAB g15_at1_mod[] =
{
};

DEVICE g15_at1_dev =
{
    name:        "AT-1",
    units:       &g15_at1_unit,
    registers:   g15_at1_reg,
    modifiers:   g15_at1_mod,
    numunits:    1,
};

const char *g15_at1_desc(DEVICE *dptr)
{
    return "Alphanumeric Typewriter";
}

t_stat g15_at1_reset(DEVICE *dptr)
{
    g15_at1_unit.buf = 0;
    sim_cancel(&g15_at1_unit);
    return SCPE_OK;
}

t_stat g15_at1_svc(UNIT *uptr)
{
    return SCPE_OK;
}

t_stat g15_at1_cmd(uint16_t cmd)
{
    g15_util_trace_enter(__FUNCTION__);
    switch (cmd)
    {
        case G15_AT1_CMD_PRINT_AR_N:
            break;
        case G15_AT1_CMD_PRINT_AR_A:
            break;
        case G15_AT1_CMD_PRINT_19_N:
            break;
        case G15_AT1_CMD_PRINT_19_A:
            break;
        case G15_AT1_CMD_TYPE_IN_N:
            break;
        case G15_AT1_CMD_TYPE_IN_A:
            break;
        default:
            break;
    }
    g15_util_trace_leave();
    return SCPE_OK;
}
