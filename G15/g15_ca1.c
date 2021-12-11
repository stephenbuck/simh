#include "g15_defs.h"
#include <ctype.h>

static UNIT g15_ca1_unit =
{
};

REG g15_ca1_reg[] =
{
};

MTAB g15_ca1_mod[] =
{
};

DEVICE g15_ca1_dev =
{
    name:        "CA-1",
    units:       &g15_ca1_unit,
    registers:   g15_ca1_reg,
    modifiers:   g15_ca1_mod,
    numunits:    1,
};

const char *g15_ca1_desc(DEVICE *dptr)
{
    return "Punched Card Coupler";
}

t_stat g15_ca1_reset(DEVICE *dptr)
{
    g15_ca1_unit.buf = 0;
    sim_cancel(&g15_ca1_unit);
    return SCPE_OK;
}

t_stat g15_ca1_svc(UNIT *uptr)
{
    if ((uptr->flags & UNIT_ATT) == 0)
        return SCPE_UNATT;
    return SCPE_OK;
}

t_stat g15_ca1_cmd(uint16_t cmd)
{
    g15_util_trace_enter(__FUNCTION__);
    switch (cmd)
    {
        case G15_CA1_CMD_READ:
            break;
        case G15_CA1_CMD_WRITE:
            break;
        default:
            break;
    }
    g15_util_trace_leave();
    return SCPE_OK;
}
