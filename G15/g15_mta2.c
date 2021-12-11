#include "g15_defs.h"
#include "sim_tape.h"

#define IS_ONLINE(u) (((u)->flags & (UNIT_ATT|UNIT_DIS)) == UNIT_ATT)

t_stat g15_mta2_reset(DEVICE *dptr);

static UNIT g15_mta2_unit[] =
{
    { UDATA (&g15_mta2_svc, UNIT_ATTABLE | UNIT_ROABLE | UNIT_DISABLE, 0) },
    { UDATA (&g15_mta2_svc, UNIT_ATTABLE | UNIT_ROABLE | UNIT_DISABLE, 0) },
    { UDATA (&g15_mta2_svc, UNIT_ATTABLE | UNIT_ROABLE | UNIT_DISABLE, 0) },
    { UDATA (&g15_mta2_svc, UNIT_ATTABLE | UNIT_ROABLE | UNIT_DISABLE, 0) }
};

#if 0
static UNIT g15_mta2_unit =
{
    next:            NULL,
    action:          &g15_mta2_svc,
    filename:        NULL,
    fileref:         NULL,
    filebuf:         NULL,
    hwmark:          0,
    time:            0,
    flags:           UNIT_ATTABLE | UNIT_SEQ | UNIT_DISABLE,
    dynflags:        0,
    capac:           0,
    pos:             0,
    io_flush:        NULL,
    iostarttime:     0,
    buf:             0,
    wait:            0,
    u3:              0,
    u4:              0,
    u5:              0,
    u6:              0,
    up7:             NULL,
    up8:             NULL,
    us9:             0,
    us10:            0,
    disk_type:       0,
    tmxr:            NULL,
    recsize:         0,
    tape_eom:        0,
    cancel:          NULL,
    usecs_remaining: 0,
    uname:           NULL,
    dptr:            NULL,
    dctrl:           0
};
#endif

REG g15_mta2_reg[] =
{
};

MTAB g15_mta2_mod[] =
{
};

DEVICE g15_mta2_dev =
{
    "MTA-2",
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
    NULL,
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

t_stat g15_mta2_cmd(uint16_t unit, uint16_t cmd)
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
    if ((uptr->flags & UNIT_ATT) == 0)
        return SCPE_UNATT;
    return SCPE_OK;
}

t_stat g15_mta2_reset(DEVICE *dptr)
{
    for (size_t i = 0; i < DIM(g15_mta2_unit); i++)
    {
        UNIT *uptr = &g15_mta2_unit[i];
        uptr->buf = 0;
        sim_tape_reset(uptr);
        sim_cancel(uptr);
    }
    return SCPE_OK;
}

t_stat g15_mta2_attach(UNIT *uptr, CONST char *cptr)
{
    return sim_tape_attach(uptr, cptr);
}

t_stat g15_mta2_detach(UNIT *uptr)
{
    return sim_tape_detach(uptr, cptr);
}

t_stat g15_mta2_help(FILE *st, DEVICE *dptr, UNIT *uptr, int32 flag, const char *cptr)
{
    return SCPE_OK;
}

const char *g15_mta2_desc(DEVICE *dptr)
{
    return "MTA-2 Magnetic Tape Units";
}
