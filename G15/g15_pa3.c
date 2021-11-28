#include "g15_defs.h"
#include <ctype.h>

UNIT g15_pa3_unit[] =
{
};

REG g15_pa3_reg[] =
{
};

MTAB g15_pa3_mod[] =
{
};

DEVICE g15_pa3_dev =
{
    name:        "PA-3",
    units:       g15_pa3_unit,
    registers:   g15_pa3_reg,
    modifiers:   g15_pa3_mod,
    numunits:    1,
};

const char *g15_pa3_desc(DEVICE *dptr)
{
    return "Graph Plotter";
}

t_stat g15_pa3_svc(UNIT *uptr)
{
    return SCPE_OK;
}

t_stat g15_pa3_reset(DEVICE *dptr)
{
    sim_cancel(&g15_pa3_unit[0]);
    return SCPE_OK;
}

t_stat g15_pa3_cmd(short cmd)
{
    g15_util_trace_enter(__FUNCTION__);
    g15_util_trace_leave();
    return SCPE_OK;
}
