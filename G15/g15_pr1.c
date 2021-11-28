#include "g15_defs.h"

t_stat g15_pr1_rd(int32 *data, int32 PA, int32 access);
t_stat g15_pr1_wr(int32 data, int32 PA, int32 access);
t_stat g15_pr1_reset(DEVICE *dptr);
t_stat g15_pr1_attach(UNIT *uptr, CONST char *ptr);
t_stat g15_pr1_detach(UNIT *uptr);
t_stat g15_pr1_help(FILE *st, DEVICE *dptr, UNIT *uptr, int32 flag, const char *cptr);
const char *g15_pr1_desc(DEVICE *dptr);

UNIT g15_pr1_unit[] =
{
};

REG g15_pr1_reg[] =
{
};

MTAB g15_pr1_mod[] =
{
};

DEVICE g15_pr1_dev =
{
    name:        "PR-1",
    units:       g15_pr1_unit,
    registers:   g15_pr1_reg,
    modifiers:   g15_pr1_mod,
    numunits:    1,
    aradix:      10,
    awidth:      31,
    aincr:       1,
//    dradix:      DEV_RDX,
    dwidth:      8,
    examine:     NULL,
    deposit:     NULL,
    reset:       &g15_pr1_reset,
    boot:        NULL,
    attach:      &g15_pr1_attach,
    detach:      &g15_pr1_detach,
    ctxt:        NULL,
    flags:       DEV_DISABLE,
    dctrl:       0,
    debflags:    NULL,
//    memsize:     NULL,
    lname:       NULL,
    help:        &g15_pr1_help,
    attach_help: NULL,
    help_ctx:    NULL,
    description: &g15_pr1_desc,
    brk_types:   NULL,
    type_ctx:    NULL
};

t_stat g15_pr1_svc(UNIT *uptr)
{
#if 0
    if ((g15_pr1_unit[0].flags & UNIT_ATT) == 0)
        return IORETURN (pr1_stopioe, SCPE_UNATT);
int32   temp;
if ((temp = getc (pr1_unit.fileref)) == EOF) {
    if (feof (pr1_unit.fileref)) {
        if (pr1_stopioe)
            sim_printf ("PTR end of file\n");
        else return SCPE_OK;
        }
    else sim_perror ("PTR I/O error");
    clearerr (pr1_unit.fileref);
    return SCPE_IOERR;
    }
pr1_unit.buf = temp & ((pr1_unit.flags & UNIT_8B)? 0377: 0177);
#endif
    g15_pr1_unit[0].pos += 1;
    return SCPE_OK;
}

t_stat g15_pr1_reset(DEVICE *dptr)
{
    sim_cancel(&g15_pr1_unit[0]);
    return SCPE_OK;
}

t_stat g15_pr1_attach(UNIT *uptr, CONST char *cptr)
{
    return attach_unit(uptr, cptr);
}

t_stat g15_pr1_detach(UNIT *uptr)
{
    return detach_unit(uptr);
}

t_stat g15_pr1_help(FILE *st, DEVICE *dptr, UNIT *uptr, int32 flag, const char *cptr)
{
    return SCPE_OK;
}

const char *g15_pr1_desc(DEVICE *dptr)
{
    return "PR-1 Paper Tape Reader";
}

t_stat g15_pr1_cmd(short cmd)
{
    g15_util_trace_enter(__FUNCTION__);
    g15_util_trace_leave();
    return SCPE_OK;
}

