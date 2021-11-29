#include "g15_defs.h"
#include "sim_tape.h"

t_stat g15_mta2_reset(DEVICE *dptr);
t_stat g15_mta2_boot(int32 unitno, DEVICE *dptr);
t_stat g15_mta2_map_status(t_stat st);
UNIT * g15_mta2_sel_unit(int32 unit);

UNIT g15_mta2_unit[] =
{
};

REG g15_mta2_reg[] =
{
};

MTAB g15_mta2_mod[] =
{
};

DEVICE g15_mta2_dev =
{
<<<<<<< HEAD
    "MTA-2",
=======
    "mta2-2",
>>>>>>> 5a6897ef325f6dfe1487cbfe81f715e6a457a04b
    g15_mta2_unit,
    g15_mta2_reg,
    g15_mta2_mod,
    4,
    10,
    31,
    1,
    8,
    8,
    NULL,
    NULL,
    &g15_mta2_reset,
    &g15_mta2_boot,
    &sim_tape_attach,
    &sim_tape_detach,
    NULL,
    DEV_DEBUG | DEV_TAPE
};

t_stat g15_mta2_rd(int32 *data, int32 PA, int32 access)
{
    return SCPE_OK;
}

t_stat g15_mta2_wr(int32 data, int32 PA, int32 access)
{
    return SCPE_OK;
}

t_stat g15_mta2_cmd(short unit, short cmd)
{
    g15_util_trace_enter(__FUNCTION__);
    switch (cmd)
    {
        case G15_MTA2_CMD_READ:
            break;
        case G15_MTA2_CMD_WRITE:
            break;
        case G15_MTA2_CMD_FILECODE:
            break;
        case G15_MTA2_CMD_FORWARD:
            break;
        case G15_MTA2_CMD_REVERSE:
            break;
        default:
            break;
    }
    g15_util_trace_leave();
    return SCPE_OK;
}

t_stat g15_mta2_svc(UNIT *uptr)
{
    return SCPE_OK;
}

t_stat g15_mta2_reset(DEVICE *dptr)
{
    sim_cancel(&g15_mta2_unit[0]);
    return SCPE_OK;
}

<<<<<<< HEAD
t_stat g15_mta2_boot(int32 unitno, DEVICE *dptr)
{
    return SCPE_OK;
}

=======
>>>>>>> 5a6897ef325f6dfe1487cbfe81f715e6a457a04b
t_stat g15_mta2_attach(UNIT *uptr, CONST char *cptr)
{
    return SCPE_OK;
}

t_stat g15_mta2_detach(UNIT *uptr)
{
    return SCPE_OK;
}

t_stat g15_mta2_help(FILE *st, DEVICE *dptr, UNIT *uptr, int32 flag, const char *cptr)
{
    return SCPE_OK;
}

const char *g15_mta2_desc(DEVICE *dptr)
{
<<<<<<< HEAD
    return "MTA-2 Magnetic Tape Units";
=======
    return "mta2-2 Magnetic Tape Units";
>>>>>>> 5a6897ef325f6dfe1487cbfe81f715e6a457a04b
}
