#include "g15_defs.h"

t_stat g15_pr2_rd(int32 *data, int32 PA, int32 access);
t_stat g15_pr2_wr(int32 data, int32 PA, int32 access);
t_stat g15_pr2_reset(DEVICE *dptr);
t_stat g15_pr2_attach(UNIT *uptr, CONST char *ptr);
t_stat g15_pr2_detach(UNIT *uptr);
t_stat g15_pr2_help(FILE *st, DEVICE *dptr, UNIT *uptr, int32 flag, const char *cptr);
const char *g15_pr2_desc(DEVICE *dptr);

UNIT g15_pr2_unit[] =
{
};

REG g15_pr2_reg[] =
{
};

MTAB g15_pr2_mod[] =
{
};

DEVICE g15_pr2_dev =
{
    name:        "PR-2",
    units:       g15_pr2_unit,
    registers:   g15_pr2_reg,
    modifiers:   g15_pr2_mod,
    numunits:    1,
    aradix:      10,
    awidth:      31,
    aincr:       1,
//    dradix:      DEV_RDX,
    dwidth:      8,
    examine:     NULL,
    deposit:     NULL,
    reset:       &g15_pr2_reset,
    boot:        NULL,
    attach:      &g15_pr2_attach,
    detach:      &g15_pr2_detach,
    ctxt:        NULL,
    flags:       DEV_DISABLE,
    dctrl:       0,
    debflags:    NULL,
//    memsize:     NULL,
    lname:       NULL,
    help:        &g15_pr2_help,
    attach_help: NULL,
    help_ctx:    NULL,
    description: &g15_pr2_desc,
    brk_types:   NULL,
    type_ctx:    NULL
};

t_stat g15_pr2_rd(int32 *data, int32 PA, int32 access)
{
    return SCPE_OK;
}

t_stat g15_pr2_wr(int32 data, int32 PA, int32 access)
{
    return SCPE_OK;
}

t_stat g15_pr2_svc(UNIT *uptr)
{
    return SCPE_OK;
}

t_stat g15_pr2_reset(DEVICE *dptr)
{
    sim_cancel(&g15_pr2_unit[0]);
    return SCPE_OK;
}

t_stat g15_pr2_attach(UNIT *uptr, CONST char *cptr)
{
    return attach_unit(uptr, cptr);
}

t_stat g15_pr2_detach(UNIT *uptr)
{
    return detach_unit(uptr);
}

t_stat g15_pr2_help(FILE *st, DEVICE *dptr, UNIT *uptr, int32 flag, const char *cptr)
{
    return SCPE_OK;
}

const char *g15_pr2_desc(DEVICE *dptr)
{
    return "PR-2 Multicode Paper Tape Reader";
}

t_stat g15_pr2_cmd(uint16_t cmd)
{
    g15_util_trace_enter(__FUNCTION__);
    g15_util_trace_leave();
    return SCPE_OK;
}

