#include "g15_defs.h"
#include <ctype.h>

static UNIT g15_ca2_unit =
{
};

REG g15_ca2_reg[] =
{
};

MTAB g15_ca2_mod[] =
{
};

DEVICE g15_ca2_dev =
{
    name:        "CA-2",
    units:       &g15_ca2_unit,
    registers:   g15_ca2_reg,
    modifiers:   g15_ca2_mod,
    numunits:    1,
};

const char *g15_ca2_desc(DEVICE *dptr)
{
    return "Card & Tabulator Coupler";
}

t_stat g15_ca2_reset(DEVICE *dptr)
{
    g15_ca2_unit.buf = 0;
    sim_cancel(&g15_ca2_unit);
    return SCPE_OK;
}

t_stat g15_ca2_svc(UNIT *uptr)
{
    if ((uptr->flags & UNIT_ATT) == 0)
        return SCPE_UNATT;
    return SCPE_OK;
}

t_stat g15_ca2_cmd(uint16_t cmd)
{
    g15_util_trace_enter(__FUNCTION__);
    switch (cmd)
    {
        case G15_CA2_CMD_READ:
            break;
        case G15_CA2_CMD_WRITE:
            break;
        default:
            break;
    }
    g15_util_trace_leave();
    return SCPE_OK;
}
