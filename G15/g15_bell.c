#include "g15_defs.h"
#include "sim_video.h"

UNIT bell_unit =
{
    { NULL }
};

REG bell_reg =
{
    { NULL }
};

MTAB bell_mod =
{
    { NULL }
};

DEVICE bell_dev =
{
    name:        "BELL",
    units:       &bell_unit,
    registers:   bell_reg,
    modifiers:   bell_mod,
    numunits:    1,
};

// vid_beep();
const char *bell_desc(DEVICE *dptr)
{
    return "Bell";
}

t_stat bell_reset(DEVICE *dptr)
{
    sim_cancel(bell_unit);
    return SCPE_OK;
}

t_stat bell_svc(UINT *uptr)
{
    return SCPE_OK;
}
