#include "g15_defs.h"
#include <ctype.h>

UNIT g15_an1_unit[] =
{
};

REG g15_an1_reg[] =
{
};

MTAB g15_an1_mod[] =
{
};

DEVICE g15_an1_dev =
{
    name:        "AN-1",
    units:       g15_an1_unit,
    registers:   g15_an1_reg,
    modifiers:   g15_an1_mod,
    numunits:    1,
};

const char *g15_an1_desc(DEVICE *dptr)
{
    return "Alphanumeric Terminal";
}

t_stat g15_an1_reset(DEVICE *dptr)
{
    sim_cancel(&g15_an1_unit[0]);
    return SCPE_OK;
}

t_stat g15_an1_svc(UNIT *uptr)
{
    return SCPE_OK;
}

t_stat g15_an1_cmd(uint16_t cmd)
{
    g15_util_trace_enter(__FUNCTION__);
    g15_util_trace_leave();
    return SCPE_OK;
}
