#include "g15_defs.h"
#include <ctype.h>

#define G15_CTL_LAMP_HALT
#define G15_CTL_LAMP_OVERFLOW
#define G15_CTL_LAMP_DOUBLE
#define G15_CTL_LAMP_ACCCMD
#define G15_CTL_LAMP_CMDLINE
#define G15_CTL_LAMP_TEST

#define G15_CTL_LAMP_CHR_0
#define G15_CTL_LAMP_CHR_1

#define G15_CTL_LAMP_SRC_0
#define G15_CTL_LAMP_SRC_1
#define G15_CTL_LAMP_SRC_2
#define G15_CTL_LAMP_SRC_3
#define G15_CTL_LAMP_SRC_4

#define G15_CTL_LAMP_DST_0
#define G15_CTL_LAMP_DST_1
#define G15_CTL_LAMP_DST_2
#define G15_CTL_LAMP_DST_3
#define G15_CTL_LAMP_DST_4

#define G15_CTL_LAMP_IO_0
#define G15_CTL_LAMP_IO_1
#define G15_CTL_LAMP_IO_2
#define G15_CTL_LAMP_IO_3
#define G15_CTL_LAMP_IO_4
#define G15_CTL_LAMP_IO_5

static uint32_t g15_ctl_bits;

UNIT g15_ctl_unit[] =
{
};

REG g15_ctl_reg[] =
{
};

MTAB g15_ctl_mod[] =
{
};

DEVICE g15_ctl_dev =
{
    name:        "CTL",
    units:       g15_ctl_unit,
    registers:   g15_ctl_reg,
    modifiers:   g15_ctl_mod,
    numunits:    1,
};

const char *g15_ctl_desc(DEVICE *dptr)
{
    return "Control Panel";
}

t_stat g15_ctl_reset(DEVICE *dptr)
{
    sim_cancel(&g15_ctl_unit[0]);
    return SCPE_OK;
}

t_stat g15_ctl_svc(UINT *uptr)
{
    return SCPE_OK;
}
