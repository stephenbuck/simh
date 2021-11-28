#include "g15_defs.h"
#include <ctype.h>

UNIT g15_da1_unit[] =
{
};

REG g15_da1_reg[] =
{
};

MTAB g15_da1_mod[] =
{
};

DEVICE g15_da1_dev =
{
    name:        "DA-1",
    units:       g15_da1_unit,
    registers:   g15_da1_reg,
    modifiers:   g15_da1_mod,
    numunits:    1,
};

const char *g15_da1_desc(DEVICE *dptr)
{
    return "DA-1 Digital Differential Analyzer";
}

t_stat g15_da1_reset(DEVICE *dptr)
{
    sim_cancel(&g15_da1_unit[0]);
    return SCPE_OK;
}

t_stat g15_da1_svc(UNIT *uptr)
{
    return SCPE_OK;
}

t_stat g15_da1_cmd(short cmd)
{
    g15_util_trace_enter(__FUNCTION__);
    g15_util_trace_leave();
    return SCPE_OK;
}
