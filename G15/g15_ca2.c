#include "g15_defs.h"
#include <ctype.h>

UNIT g15_ca2_unit[] =
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
    name:        "CA1",
    units:       g15_ca2_unit,
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
    sim_cancel(g15_ca2_unit);
    return SCPE_OK;
}

t_stat g15_ca2_svc(UINT *uptr)
{
    return SCPE_OK;
}

t_stat g15_ca2_cmd(short cmd)
{
    g15_util_trace_enter(__FUNCTION__);
    g15_util_trace_leave();
    return SCPE_OK;
}
