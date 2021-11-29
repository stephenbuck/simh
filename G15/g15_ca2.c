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
<<<<<<< HEAD
    name:        "CA-2",
=======
    name:        "CA1",
>>>>>>> 5a6897ef325f6dfe1487cbfe81f715e6a457a04b
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

<<<<<<< HEAD
t_stat g15_ca2_svc(UNIT *uptr)
=======
t_stat g15_ca2_svc(UINT *uptr)
>>>>>>> 5a6897ef325f6dfe1487cbfe81f715e6a457a04b
{
    return SCPE_OK;
}

t_stat g15_ca2_cmd(short cmd)
{
    g15_util_trace_enter(__FUNCTION__);
    g15_util_trace_leave();
    return SCPE_OK;
}
