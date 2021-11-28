#include "g15_defs.h"
#include <ctype.h>

UNIT g15_at1_unit[] =
{
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
    units:       g15_at1_unit,
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
    sim_cancel(&g15_at1_unit[0]);
    return SCPE_OK;
}

t_stat g15_at1_svc(UNIT *uptr)
{
    return SCPE_OK;
}

t_stat g15_at1_cmd(short cmd)
{
    g15_util_trace_enter(__FUNCTION__);
    g15_util_trace_leave();
    return SCPE_OK;
}
