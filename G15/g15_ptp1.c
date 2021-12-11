#include "g15_defs.h"
#include <ctype.h>

#if 0
UNIT g15_ptp1_unit =
{
    UDATA (&ptp_svc, UNIT_SEQ+UNIT_ATTABLE, 0), SERIAL_OUT_WAIT
};
#endif

UNIT g15_ptp1_unit =
{
    next:            NULL,
    action:          &g15_ptp1_svc,
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
#ifdef SIM_ASYNCH_IO
    void                (*a_check_completion)(UNIT *);
    t_bool              (*a_is_active)(UNIT *);
    UNIT                *a_next;                        /* next asynch active */
    int32               a_event_time;
    ACTIVATE_API        a_activate_call;
    /* Asynchronous Polling control */
    /* These fields should only be referenced when holding the sim_tmxr_poll_lock */
    t_bool              a_polling_now;                  /* polling active flag */
    int32               a_poll_waiter_count;            /* count of polling threads */
                                                        /* waiting for this unit */
    /* Asynchronous Timer control */
    double              a_due_time;                     /* due time for timer event */
    double              a_due_gtime;                    /* due time (in instructions) for timer event */
    double              a_usec_delay;                   /* time delay for timer event */
#endif
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
    units:       &g15_ptp1_unit,
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
    g15_ptp1_unit.buf = 0;
    sim_cancel(&g15_ptp1_unit);
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
    if ((uptr->flags & UNIT_ATT) == 0)
        return SCPE_UNATT;
    if (putc(uptr->buf, uptr->fileref) == EOF)
    {
        sim_perror("PTP-1 I/O error");
        clearerr(uptr->fileref);
        return SCPE_IOERR;
    }
    uptr->pos = uptr->pos + 1;
    return SCPE_OK;
}

t_stat g15_ptp1_cmd(uint16_t cmd, uint8_t arg)
{
    g15_util_trace_enter(__FUNCTION__);
    switch (cmd)
    {
        case G15_PTP1_CMD_PUNCH:
            g15_ptp1_unit.buf = arg & 0x00ff;
            g15_ptp1_svc(&g15_ptp1_unit);
            break;
        case G15_PTP1_CMD_PUNCH_19:
            break;
        case G15_PTP1_CMD_TEST_SW:
            break;
        default:
            break;
    }
    g15_util_trace_leave();
    return SCPE_OK;
}

