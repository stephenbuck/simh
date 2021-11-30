#include "g15_defs.h"
#include <ctype.h>

UNIT g15_ptp1_unit[] =
{
};

REG g15_ptp1_reg[] =
{
};

MTAB g15_ptp1_mod[] =
{
};

DEVICE g15_ptp1_dev =
{
    name:        "PTP-1",
    units:       g15_ptp1_unit,
    registers:   g15_ptp1_reg,
    modifiers:   g15_ptp1_mod,
    numunits:    1,
};

const char *g15_ptp1_desc(DEVICE *dptr)
{
    return "PTP-1 Paper Tape Punch";
}

t_stat ptp1_reset(DEVICE *dptr)
{
    sim_cancel(&g15_ptp1_unit[0]);
    return SCPE_OK;
}

t_stat g15_ptp1_attach(UNIT *uptr, CONST char *cptr)
{
    return attach_unit(uptr, cptr);
}

t_stat g15_ptp1_detach(UNIT *uptr)
{
    return detach_unit(uptr);
}

t_stat g15_ptp1_svc(UNIT *uptr)
{
#if 0
if ((ptp_unit.flags & UNIT_ATT) == 0)                   /* attached? */
    return IORETURN (ptp_stopioe, SCPE_UNATT);
if (putc ((ptp_unit.buf & ((ptp_unit.flags & UNIT_8B)? 0377: 0177)), ptp_unit.fileref) == EOF) {
    sim_perror ("PTP I/O error");
    clearerr (ptp_unit.fileref);
    return SCPE_IOERR;
    }
++(ptp_unit.pos);
#endif
    return SCPE_OK;
}

t_stat g15_ptp1_cmd(uint16_t cmd)
{
    g15_util_trace_enter(__FUNCTION__);
    g15_util_trace_leave();
    return SCPE_OK;
}

