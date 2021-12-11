#include "g15_defs.h"
#include <ctype.h>

static UNIT g15_pa3_unit =
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
    units:       &g15_pa3_unit,
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
    g15_pa3_unit.buf = 0;
    sim_cancel(&g15_pa3_unit);
    return SCPE_OK;
}

t_stat g15_pa3_cmd(uint16_t cmd)
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
