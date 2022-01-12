#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include "g15_defs.h"

const char *g15_cpu_desc(DEVICE *dptr);
t_stat g15_cpu_reset(DEVICE *dptr);
t_stat g15_cpu_deposit(t_value val, t_addr addr, UNIT *uptr, int32 sw);
t_stat g15_cpu_examine(t_value *vptr, t_addr addr, UNIT *uptr, int32 sw);
t_stat g15_cpu_help(FILE *st, DEVICE *dptr, UNIT *uptr, int32 flag, const char *cptr);


#define PC_MAKE(ln,wd) (((ln) << 16) | ((wd) << 0))
#define PC_LINE(pc)    (((pc) & 0xffff0000) >> 16)
#define PC_WORD(pc)    (((pc) & 0x0000ffff) >>  0)

typedef struct
{
    void (*exec)(G15_CNTX * cntx, G15_INST inst);
    void (*dasm)(G15_CNTX * cntx, G15_INST inst, char * buff);

} G15_OPCODE;

static G15_CNTX g15_cpu_cntx =
{
    state:  G15_STATE_WAIT_NEXT_COMMAND,
    reason: SCPE_OK,
    halt:   false,
    PC:     PC_MAKE(1, 0),
    AR:     0,
    ID:     0,
    MQ:     0,
    PN:     0,
    IP:     0,
    IO:     0,
    OV:     0
};

// ============================================================
// tbd :
// ============================================================

static void tbd_exec(G15_CNTX * cntx, G15_INST inst)
{
    g15_util_trace_enter(__FUNCTION__);
    cntx->reason = SCPE_UNK;
    g15_util_trace_leave();
}

static void tbd_dasm(G15_CNTX * cntx, G15_INST inst)
{
}

static G15_OPCODE tbd =
{
    exec: tbd_exec,
    dasm: tbd_dasm
};

// ============================================================
// aar :
// ============================================================

static void aar_exec(G15_CNTX * cntx, G15_INST inst)
{
    g15_util_trace_enter(__FUNCTION__);
    switch (G15_INST_PCHR(inst))
    {
        // Add to AR
        case 1:
            cntx->AR += g15_drum_rd(inst.L, inst.S);
            break;
        // Add absolute value to AR
        case 2:
            cntx->AR += abs(g15_drum_rd(inst.L, inst.S));
            break;
        // Subtract from AR
        case 3:
            cntx->AR -= g15_drum_rd(inst.L, inst.S);
            break;
    }
    g15_util_trace_leave();
}

static void aar_dasm(G15_CNTX * cntx, G15_INST inst)
{
}

static G15_OPCODE aar =
{
    exec: aar_exec,
    dasm: aar_dasm
};

// ============================================================
// add : Add
// ============================================================

static void add_exec(G15_CNTX * cntx, G15_INST inst)
{
    g15_util_trace_enter(__FUNCTION__);
    switch (G15_INST_PCHR(inst))
    {
        // Clear and add to AR
        case 1:
            cntx->AR = 0;
            cntx->AR += g15_drum_rd(inst.L, inst.S);
            break;
        // Clear and add absolute value to AR
        case 2:
            cntx->AR = 0;
            cntx->AR += abs(g15_drum_rd(inst.L, inst.S));
            break;
        // Clear and subtract from AR
        case 3:
            cntx->AR = 0;
            cntx->AR -= g15_drum_rd(inst.L, inst.S);
            break;
        case 4:
            break;
        case 5:
            break;
    }
    g15_util_trace_leave();
}

static void add_dasm(G15_CNTX * cntx, G15_INST inst)
{
}

static G15_OPCODE add =
{
    exec: add_exec,
    dasm: add_dasm
};

// ============================================================
// clr : Clear multiplication and division registers
// ============================================================

static void clr_exec(G15_CNTX * cntx, G15_INST inst)
{
    g15_util_trace_enter(__FUNCTION__);
    cntx->ID = 0;
    cntx->MQ = 0;
    cntx->PN = 0;
    cntx->IP = 0;
    g15_util_trace_leave();
}

static void clr_dasm(G15_CNTX * cntx, G15_INST inst)
{
}

static G15_OPCODE clr =
{
    exec: clr_exec,
    dasm: clr_dasm
};

// ============================================================
// cpy : Copy
// ============================================================

static void cpy_exec(G15_CNTX * cntx, G15_INST inst)
{
    g15_util_trace_enter(__FUNCTION__);
    switch (G15_INST_PCHR(inst))
    {
        // Transfer word between addresses
        case 0:
            g15_drum_wr(inst.L, inst.D, g15_drum_rd(inst.L, inst.S));
            break;
        // Transfer to or from two-word register
        case 1:
            break;
    }
    g15_util_trace_leave();
}

static void cpy_dasm(G15_CNTX * cntx, G15_INST inst)
{
}

static G15_OPCODE cpy =
{
    exec: cpy_exec,
    dasm: cpy_dasm
};

// ============================================================
// dvd : Divide
// ============================================================

static void dvd_exec(G15_CNTX * cntx, G15_INST inst)
{
    g15_util_trace_enter(__FUNCTION__);
    g15_util_trace_leave();
}

static void dvd_dasm(G15_CNTX * cntx, G15_INST inst)
{
}

static G15_OPCODE dvd =
{
    exec: dvd_exec,
    dasm: dvd_dasm
};

// ============================================================
// fsr :
// ============================================================

static void fsr_exec(G15_CNTX * cntx, G15_INST inst)
{
    g15_util_trace_enter(__FUNCTION__);
    g15_util_trace_leave();
}

static void fsr_dasm(G15_CNTX * cntx, G15_INST inst)
{
}

static G15_OPCODE fsr =
{
    exec: fsr_exec,
    dasm: fsr_dasm
};

// ============================================================
// hlt : Halt
// ============================================================

static void hlt_exec(G15_CNTX * cntx, G15_INST inst)
{
    g15_util_trace_enter(__FUNCTION__);
    cntx->halt = true;
    g15_util_trace_leave();
}

static void hlt_dasm(G15_CNTX * cntx, G15_INST inst)
{
}

static G15_OPCODE hlt =
{
    exec: hlt_exec,
    dasm: hlt_dasm
};

// ============================================================
// ldl : Load to shift left
// ============================================================

static void ldl_exec(G15_CNTX * cntx, G15_INST inst)
{
    g15_util_trace_enter(__FUNCTION__);
    g15_util_trace_leave();
}

static void ldl_dasm(G15_CNTX * cntx, G15_INST inst)
{
}

static G15_OPCODE ldl =
{
    exec: ldl_exec,
    dasm: ldl_dasm
};

// ============================================================
// ldn : Load numerator
// ============================================================

static void ldn_exec(G15_CNTX * cntx, G15_INST inst)
{
    g15_util_trace_enter(__FUNCTION__);
    g15_util_trace_leave();
}

static void ldn_dasm(G15_CNTX * cntx, G15_INST inst)
{
}

static G15_OPCODE ldn =
{
    exec: ldn_exec,
    dasm: ldn_dasm
};

// ============================================================
// ldr : Load to shift right
// ============================================================

static void ldr_exec(G15_CNTX * cntx, G15_INST inst)
{
    g15_util_trace_enter(__FUNCTION__);
    g15_util_trace_leave();
}

static void ldr_dasm(G15_CNTX * cntx, G15_INST inst)
{
}

static G15_OPCODE ldr =
{
    exec: ldr_exec,
    dasm: ldr_dasm
};

// ============================================================
// mfc : Write file code on magnetic tape
// ============================================================

static void mfc_exec(G15_CNTX * cntx, G15_INST inst)
{
    g15_util_trace_enter(__FUNCTION__);
    g15_mta2_cmd(inst.C, G15_MTA2_CMD_FILECODE);
    g15_util_trace_leave();
}

static void mfc_dasm(G15_CNTX * cntx, G15_INST inst)
{
}

static G15_OPCODE mfc =
{
    exec: mfc_exec,
    dasm: mfc_dasm
};

// ============================================================
// mrd : Read magnetic tape
// ============================================================

static void mrd_exec(G15_CNTX * cntx, G15_INST inst)
{
    g15_util_trace_enter(__FUNCTION__);
    g15_mta2_cmd(inst.C, G15_MTA2_CMD_READ);
    g15_util_trace_leave();
}

static void mrd_dasm(G15_CNTX * cntx, G15_INST inst)
{
}

static G15_OPCODE mrd =
{
    exec: mrd_exec,
    dasm: mrd_dasm
};

// ============================================================
// mrk : Select command line and mark
// ============================================================

static void mrk_exec(G15_CNTX * cntx, G15_INST inst)
{
    g15_util_trace_enter(__FUNCTION__);
    g15_util_trace_leave();
}

static void mrk_dasm(G15_CNTX * cntx, G15_INST inst)
{
}

static G15_OPCODE mrk =
{
    exec: mrk_exec,
    dasm: mrk_dasm
};

// ============================================================
// msf : Search magnetic tape, forward
// ============================================================

static void msf_exec(G15_CNTX * cntx, G15_INST inst)
{
    g15_util_trace_enter(__FUNCTION__);
    g15_mta2_cmd(inst.C, G15_MTA2_CMD_FORWARD);
    g15_util_trace_leave();
}

static void msf_dasm(G15_CNTX * cntx, G15_INST inst)
{
}

static G15_OPCODE msf =
{
    exec: msf_exec,
    dasm: msf_dasm
};

// ============================================================
// msr : Search magnetic tape, reverse
// ============================================================

static void msr_exec(G15_CNTX * cntx, G15_INST inst)
{
    g15_util_trace_enter(__FUNCTION__);
    g15_mta2_cmd(inst.C, G15_MTA2_CMD_REVERSE);
    g15_util_trace_leave();
}

static void msr_dasm(G15_CNTX * cntx, G15_INST inst)
{
}

static G15_OPCODE msr =
{
    exec: msr_exec,
    dasm: msr_dasm
};

// ============================================================
// mul : Multiply
// ============================================================

static void mul_exec(G15_CNTX * cntx, G15_INST inst)
{
    g15_util_trace_enter(__FUNCTION__);
    g15_util_trace_leave();
}

static void mul_dasm(G15_CNTX * cntx, G15_INST inst)
{
}

static G15_OPCODE mul =
{
    exec: mul_exec,
    dasm: mul_dasm
};

// ============================================================
// mwr : Write on magnetic tape
// ============================================================

static void mwr_exec(G15_CNTX * cntx, G15_INST inst)
{
    g15_util_trace_enter(__FUNCTION__);
    g15_mta2_cmd(inst.C, G15_MTA2_CMD_WRITE);
    g15_util_trace_leave();
}

static void mwr_dasm(G15_CNTX * cntx, G15_INST inst)
{
}

static G15_OPCODE mwr =
{
    exec: mwr_exec,
    dasm: mwr_dasm
};

// ============================================================
// nmq : Normalize MQ
// ============================================================

static void nmq_exec(G15_CNTX * cntx, G15_INST inst)
{
    g15_util_trace_enter(__FUNCTION__);
    g15_util_trace_leave();
}

static void nmq_dasm(G15_CNTX * cntx, G15_INST inst)
{
}

static G15_OPCODE nmq =
{
    exec: nmq_exec,
    dasm: nmq_dasm
};

// ============================================================
// par : Print AR
// ============================================================

static void par_exec(G15_CNTX * cntx, G15_INST inst)
{
    g15_util_trace_enter(__FUNCTION__);
    switch (G15_INST_PCHR(inst))
    {
        // Print AR in numeric mode
        case 0:
            g15_an1_cmd(G15_AN1_CMD_PRINT_AR_N);
            break;
        // Print AR in alphanumeric mode
        case 4:
            g15_an1_cmd(G15_AN1_CMD_PRINT_AR_A);
            break;
    }
    g15_util_trace_leave();
}

static void par_dasm(G15_CNTX * cntx, G15_INST inst)
{
}

static G15_OPCODE par =
{
    exec: par_exec,
    dasm: par_dasm
};

// ============================================================
// pcr : Read punched cards
// ============================================================

static void pcr_exec(G15_CNTX * cntx, G15_INST inst)
{
    g15_util_trace_enter(__FUNCTION__);
    g15_ca1_cmd(G15_CA1_CMD_READ);
    g15_util_trace_leave();
}

static void pcr_dasm(G15_CNTX * cntx, G15_INST inst)
{
}

static G15_OPCODE pcr =
{
    exec: pcr_exec,
    dasm: pcr_dasm
};

// ============================================================
// pcw : Write punched cards
// ============================================================

static void pcw_exec(G15_CNTX * cntx, G15_INST inst)
{
}

static void pcw_exec(G15_CNTX * cntx, G15_INST inst)
{
    g15_util_trace_enter(__FUNCTION__);
    g15_ca1_cmd(G15_CA1_CMD_WRITE);
    g15_util_trace_leave();
}

static G15_OPCODE pcw =
{
    exec: pcw_exec,
    dasm: pcw_dasm
};

// ============================================================
// ppn : Prepare product for addition in PN
// ============================================================

static void ppn_exec(G15_CNTX * cntx, G15_INST inst)
{
    g15_util_trace_enter(__FUNCTION__);
    g15_util_trace_leave();
}

static void ppn_dasm(G15_CNTX * cntx, G15_INST inst)
{
}

static G15_OPCODE ppn =
{
    exec: ppn_exec,
    dasm: ppn_dasm
};

// ============================================================
// pr9 : Print line 19
// ============================================================

static void pr9_exec(G15_CNTX * cntx, G15_INST inst)
{
    g15_util_trace_enter(__FUNCTION__);
    switch (G15_INST_PCHR(inst))
    {
        // Print line 19 in numeric mode
        case 0:
            g15_an1_cmd(G15_AN1_CMD_PRINT_19_N);
            break;
        // Print line 19 in alphanumeric mode
        case 4:
            g15_an1_cmd(G15_AN1_CMD_PRINT_19_A);
            break;
    }
    g15_util_trace_leave();
}

static void pr9_dasm(G15_CNTX * cntx, G15_INST inst)
{
}

static G15_OPCODE pr9 =
{
    exec: pr9_exec,
    dasm: pr9_dasm
};

// ============================================================
// prm : Permit type-in
// ============================================================

static void prm_exec(G15_CNTX * cntx, G15_INST inst)
{
    g15_util_trace_enter(__FUNCTION__);
    switch (G15_INST_PCHR(inst))
    {
        // Permit numeric type-in
        case 0:
            g15_an1_cmd(G15_AN1_CMD_TYPE_IN_N);
            break;
        // Permit alphanumeric type-in
        case 4:
            g15_an1_cmd(G15_AN1_CMD_TYPE_IN_A);
            break;
    }
    g15_util_trace_leave();
}

static void prm_dasm(G15_CNTX * cntx, G15_INST inst)
{
}

static G15_OPCODE prm =
{
    exec: prm_exec,
    dasm: prm_dasm
};

// ============================================================
// pt9 : Punch line 19 on tape
// ============================================================

static void pt9_exec(G15_CNTX * cntx, G15_INST inst)
{
    g15_util_trace_enter(__FUNCTION__);
    g15_ptp1_cmd(G15_PTP1_CMD_PUNCH_19);
    g15_util_trace_leave();
}

static void pt9_dasm(G15_CNTX * cntx, G15_INST inst)
{
}

static G15_OPCODE pt9 =
{
    exec: pt9_exec,
    dasm: pt9_dasm
};

// ============================================================
// ptb :
// ============================================================

static void ptb_exec(G15_CNTX * cntx, G15_INST inst)
{
    g15_util_trace_enter(__FUNCTION__);
    g15_util_trace_leave();
}

static void ptb_dasm(G15_CNTX * cntx, G15_INST inst)
{
}

static G15_OPCODE ptb =
{
    exec: ptb_exec,
    dasm: ptb_dasm
};

// ============================================================
// ptr : Reverse punched tape
// ============================================================

static void ptr_exec(G15_CNTX * cntx, G15_INST inst)
{
    g15_util_trace_enter(__FUNCTION__);
    g15_pr1_cmd(G15_PR1_CMD_REVERSE);
    g15_util_trace_leave();
}

static void ptr_dasm(G15_CNTX * cntx, G15_INST inst)
{
}

static G15_OPCODE ptr =
{
    exec: ptr_exec,
    dasm: ptr_dasm
};

// ============================================================
// ret : Select command line and return
// ============================================================

static void ret_exec(G15_CNTX * cntx, G15_INST inst)
{
    g15_util_trace_enter(__FUNCTION__);
    g15_util_trace_leave();
}

static void ret_dasm(G15_CNTX * cntx, G15_INST inst)
{
}

static G15_OPCODE ret =
{
    exec: ret_exec,
    dasm: ret_dasm
};

// ============================================================
// smq : Shift MQ
// ============================================================

static void smq_exec(G15_CNTX * cntx, G15_INST inst)
{
    g15_util_trace_enter(__FUNCTION__);
    switch (G15_INST_PCHR(inst))
    {
        // Shift MQ left and ID right under control of AR
        case 0:
           break;
        // Shift MQ left and ID right under control of command
        case 1:
           break;
    }
    g15_util_trace_leave();
}

static void smq_dasm(G15_CNTX * cntx, G15_INST inst)
{
}

static G15_OPCODE smq =
{
    exec: smq_exec,
    dasm: smq_dasm
};

// ============================================================
// spc : Special
// ============================================================

static void spc_exec(G15_CNTX * cntx, G15_INST inst)
{
    g15_util_trace_enter(__FUNCTION__);
    switch (G15_INST_PCHR(inst))
    {
        // Halt
        case 16:
            hlt(cntx, inst);
            break;
        // Ring bell
        case 17:
            g15_bell_cmd(G15_BELL_CMD_RING);
            break;
    }
    g15_util_trace_leave();
}

static void spc_dasm(G15_CNTX * cntx, G15_INST inst)
{
}

static G15_OPCODE spc =
{
    exec: spc_exec,
    dasm: spc_dasm
};

// ============================================================
// sta : Store sum or difference from AR
// ============================================================

static void sta_exec(G15_CNTX * cntx, G15_INST inst)
{
    g15_util_trace_enter(__FUNCTION__);
    g15_drum_wr(inst.L, inst.D, cntx->AR);
    g15_util_trace_leave();
}

static void sta_dasm(G15_CNTX * cntx, G15_INST inst)
{
}

static G15_OPCODE sta =
{
    exec: sta_exec,
    dasm: sta_dasm
};

// ============================================================
// stp : Store product
// ============================================================

static void stp_exec(G15_CNTX * cntx, G15_INST inst)
{
    g15_util_trace_enter(__FUNCTION__);
    g15_util_trace_leave();
}

static void stp_dasm(G15_CNTX * cntx, G15_INST inst)
{
}

static G15_OPCODE stp =
{
    exec: stp_exec,
    dasm: stp_dasm
};

// ============================================================
// stq : Store quotient
// ============================================================

static void stq_exec(G15_CNTX * cntx, G15_INST inst)
{
    g15_util_trace_enter(__FUNCTION__);
    g15_util_trace_leave();
}

static void stq_dasm(G15_CNTX * cntx, G15_INST inst)
{
}

static G15_OPCODE stq =
{
    exec: stq_exec,
    dasm: stq_dasm
};

// ============================================================
// tng : Test if sign of AR negative
// ============================================================

static void tng_exec(G15_CNTX * cntx, G15_INST inst)
{
    g15_util_trace_enter(__FUNCTION__);
    if (cntx->AR < 0) cntx->PC = PC_MAKE(PC_LINE(cntx->PC), inst.N + 1);
    g15_util_trace_leave();
}

static void tng_dasm(G15_CNTX * cntx, G15_INST inst)
{
}

static G15_OPCODE tng =
{
    exec: tng_exec,
    dasm: tng_dasm
};

// ============================================================
// z02 :
// ============================================================

static void z02_exec(G15_CNTX * cntx, G15_INST inst)
{
    g15_util_trace_enter(__FUNCTION__);
    switch (G15_INST_PCHR(inst))
    {
        // TNG
        case 0:
            break;
        // Test CA-2 format selector
        case 1:
            break;
        // Test CA-2 ready
        case 2:
            break;
        // Test CA-2 processing position
        case 3:
            break;
        // Turn off CA-2 format selector
        case 5:
            break;
        // Turn on CA-2 format selector
        case 6:
            break;
        // Halt CA-2
        case 7:
            break;
    }
    g15_util_trace_leave();
}

static void z02_dasm(G15_CNTX * cntx, G15_INST inst)
{
}

static G15_OPCODE z02 =
{
    exec: z02_exec,
    dasm: z02_dasm
};

// ============================================================
// z03 :
// ============================================================

static void z03_exec(G15_CNTX * cntx, G15_INST inst)
{
    g15_util_trace_enter(__FUNCTION__);
    switch (G15_INST_PCHR(inst))
    {
        // Start CA-2
        case 0:
            break;
        // Reset and halt CA-2
        case 1:
            break;
        // Start CA-2
        case 2:
            break;
        // Start CA-2
        case 3:
            break;
    }
    g15_util_trace_leave();
}

static void z03_dasm(G15_CNTX * cntx, G15_INST inst)
{
}

static G15_OPCODE z03 =
{
    exec: z03_exec,
    dasm: z03_dasm
};

// ============================================================
// tnz : Test for non-zero
// ============================================================

static void tnz_exec(G15_CNTX * cntx, G15_INST inst)
{
    g15_util_trace_enter(__FUNCTION__);
    if (cntx->AR != 0) cntx->PC = PC_MAKE(PC_LINE(cntx->PC), inst.N + 1);
    g15_util_trace_leave();
}

static void tnz_dasm(G15_CNTX * cntx, G15_INST inst)
{
}

static G15_OPCODE tnz =
{
    exec: tnz_exec,
    dasm: tnz_dasm
};

// ============================================================
// tov : Test for overflow
// ============================================================

static void tov_exec(G15_CNTX * cntx, G15_INST inst)
{
    g15_util_trace_enter(__FUNCTION__);
    if (cntx->OV != 0) cntx->PC = PC_MAKE(PC_LINE(cntx->PC), inst.N + 1);
    g15_util_trace_leave();
}

static void tov_dasm(G15_CNTX * cntx, G15_INST inst)
{
}

static G15_OPCODE tov =
{
    exec: tov_exec,
    dasm: tov_dasm
};

// ============================================================
// try : Test "ready" state of input/output
// ============================================================

static void try_exec(G15_CNTX * cntx, G15_INST inst)
{
    g15_util_trace_enter(__FUNCTION__);
    if (cntx->IO != 0) cntx->PC = PC_MAKE(PC_LINE(cntx->PC), inst.N + 1);
    g15_util_trace_leave();
}

static void try_dasm(G15_CNTX * cntx, G15_INST inst)
{
}

static G15_OPCODE try =
{
    exec: try_exec,
    dasm: try_dasm
};

// ============================================================
// tsr :
// ============================================================

static void tsr_exec(G15_CNTX * cntx, G15_INST inst)
{
    g15_util_trace_enter(__FUNCTION__);
    g15_util_trace_leave();
}

static void tsr_dasm(G15_CNTX * cntx, G15_INST inst)
{
}

static G15_OPCODE tsr =
{
    exec: tsr_exec,
    dasm: tsr_dasm
};

// ============================================================
// xt0 :
// ============================================================

static void xt0_exec(G15_CNTX * cntx, G15_INST inst)
{
    g15_util_trace_enter(__FUNCTION__);
    g15_util_trace_leave();
}

static void xt0_dasm(G15_CNTX * cntx, G15_INST inst)
{
}

static G15_OPCODE xt0 =
{
    exec: xt0_exec,
    dasm: xt0_dasm
};

// ============================================================
// xt1 :
// ============================================================

static void xt1_exec(G15_CNTX * cntx, G15_INST inst)
{
    g15_util_trace_enter(__FUNCTION__);
    g15_util_trace_leave();
}

static void xt1_dasm(G15_CNTX * cntx, G15_INST inst)
{
}

static G15_OPCODE xt1 =
{
    exec: xt1_exec,
    dasm: xt1_dasm
};

// ============================================================
// z00 : Special 00
// ============================================================

static void z00_exec(G15_CNTX * cntx, G15_INST inst)
{
    g15_util_trace_enter(__FUNCTION__);
    switch (G15_INST_PCHR(inst))
    {
        // Take next command from AR
        case 0:
            cntx->PC = PC_MAKE(PC_LINE(cntx->PC), cntx->AR); // BOZO
            break;
        // Copy number track into line 18
        case 1:
            break;
    }
    g15_util_trace_leave();
}

static void z00_dasm(G15_CNTX * cntx, G15_INST inst)
{
}

static G15_OPCODE z00 =
{
    exec: z00_exec,
    dasm: z00_dasm
};

// ============================================================
// z01 : Special 01
// ============================================================

static void z01_exec(G15_CNTX * cntx, G15_INST inst)
{
    g15_util_trace_enter(__FUNCTION__);
    switch (G15_INST_PCHR(inst))
    {
        // Ring bell
        case 0:
            g15_bell_cmd(G15_BELL_CMD_RING);
            break;
        // Test for punch switch on
        case 1:
            g15_ptp1_cmd(G15_PTP1_CMD_TEST_SW);
            break;
    }
    g15_util_trace_leave();
}

static void z01_dasm(G15_CNTX * cntx, G15_INST inst)
{
}

static G15_OPCODE z01 =
{
    exec: z01_exec,
    dasm: z01_dasm
};




#if 0
static void clr_dasm(FILE *of, t_addr addr, t_value *val, UNIT *uptr, int32 sw)
{
    fprintf(of, "Clear multiplication and division registers");
}

static void cpy_dasm(FILE *of, t_addr addr, t_value *val, UNIT *uptr, int32 sw)
{
    fprintf(of, "Transfer %s to %s", "TBD", "TBD");
}

static void hlt_dasm(FILE *of, t_addr addr, t_value *val, UNIT *uptr, int32 sw)
{
    fprintf(of, "Halt");
}

static void ret_dasm(FILE *of, t_addr addr, t_value *val, UNIT *uptr, int32 sw)
{
    fprintf(of, "Select command line and return");
}

static void tbd_dasm(FILE *of, t_addr addr, t_value *val, UNIT *uptr, int32 sw)
{
    fprintf(of, "TBD");
}

static void tnz_dasm(FILE *of, t_addr addr, t_value *val, UNIT *uptr, int32 sw)
{
    fprintf(of, "Test for non-zero");
}
#endif

static G15_OPCODE * g15_cpu_dec[32][32] =
{
    /*         DST                                     DST                                      DST                                     DST                                    */
    /* SRC     000, 001, 002, 003, 004, 005, 006, 007  008, 009, 010, 011, 012, 013, 014, 015   016, 017, 018, 019, 020, 021, 022, 023  024, 025, 026, 027, 028, 029, 030, 031 */
    /* 000 */{ cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy,  cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, ldl, ldr, ldn, tnz, add, aar, tbd, tbd },/* 000 */
    /* 001 */{ cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy,  cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, ldl, ldr, ldn, tnz, add, aar, tbd, mwr },/* 001 */
    /* 002 */{ cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy,  cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, ldl, ldr, ldn, tnz, add, aar, tbd, tbd },/* 002 */
    /* 003 */{ cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy,  cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, ldl, ldr, ldn, tnz, add, aar, tbd, tbd },/* 003 */
    /* 004 */{ cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy,  cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, ldl, ldr, ldn, tnz, add, aar, tbd, msr },/* 004 */
    /* 005 */{ cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy,  cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, ldl, ldr, ldn, tnz, add, aar, tbd, msf },/* 005 */
    /* 006 */{ cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy,  cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, ldl, ldr, ldn, tnz, add, aar, tbd, ptb },/* 006 */
    /* 007 */{ cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy,  cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, ldl, ldr, ldn, tnz, add, aar, tbd, tbd },/* 007 */
    /* 008 */{ cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy,  cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, ldl, ldr, ldn, tnz, add, aar, tbd, par },/* 008 */
    /* 009 */{ cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy,  cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, ldl, ldr, ldn, tnz, add, aar, tbd, pr9 },/* 009 */
    /* 010 */{ cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy,  cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, ldl, ldr, ldn, tnz, add, aar, tbd, pt9 },/* 010 */
    /* 011 */{ cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy,  cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, ldl, ldr, ldn, tnz, add, aar, tbd, pcw },/* 011 */
    /* 012 */{ cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy,  cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, ldl, ldr, ldn, tnz, add, aar, tbd, prm },/* 012 */
    /* 013 */{ cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy,  cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, ldl, ldr, ldn, tnz, add, aar, tbd, mrd },/* 013 */
    /* 014 */{ cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy,  cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, ldl, ldr, ldn, tnz, add, aar, tbd, pcr },/* 014 */
    /* 015 */{ cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy,  cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, ldl, ldr, ldn, tnz, add, aar, tbd, ptr },/* 015 */

    /* 016 */{ cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy,  cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, ldl, ldr, ldn, tnz, add, aar, spc, hlt },/* 016 */
    /* 017 */{ cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy,  cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, ldl, ldr, ldn, tnz, add, aar, spc, z01 },/* 017 */
    /* 018 */{ cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy,  cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, ldl, ldr, ldn, tnz, add, aar, tbd, tsr },/* 018 */
    /* 019 */{ cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy,  cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, ldl, ldr, ldn, tnz, add, aar, tbd, z03 },/* 019 */
    /* 020 */{ cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy,  cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, ldl, ldr, ldn, tnz, add, aar, tbd, ret },/* 020 */
    /* 021 */{ cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy,  cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, ldl, ldr, ldn, tnz, add, aar, tbd, mrk },/* 021 */
    /* 022 */{ cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy,  cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, ldl, ldr, ldn, tnz, add, aar, tbd, z02 },/* 022 */
    /* 023 */{ cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy,  cpy, cpy, cpy, cpy, cpy, cpy, cpy, cpy, ldl, ldr, ldn, tnz, add, aar, tbd, clr },/* 023 */
    /* 024 */{ stq, stq, stq, stq, stq, stq, stq, stq, stq, stq, stq, stq, stq, stq, stq, stq,  stq, stq, stq, stq, stq, stq, stq, stq, tbd, tbd, tbd, tbd, tbd, tbd, tbd, mul },/* 024 */
    /* 025 */{ tbd, tbd, tbd, tbd, tbd, tbd, tbd, tbd, tbd, tbd, tbd, tbd, tbd, tbd, tbd, tbd,  tbd, tbd, tbd, tbd, tbd, tbd, tbd, tbd, tbd, tbd, tbd, tbd, tbd, tbd, tbd, dvd },/* 025 */
    /* 026 */{ stp, stp, stp, stp, stp, stp, stp, stp, stp, stp, stp, stp, stp, stp, stp, stp,  stp, stp, stp, stp, stp, stp, stp, stp, tbd, tbd, ppn, tbd, tbd, tbd, tbd, smq },/* 026 */
    /* 027 */{ tbd, tbd, tbd, tbd, tbd, tbd, tbd, tbd, tbd, tbd, tbd, tbd, tbd, tbd, tbd, tbd,  tbd, tbd, tbd, tbd, tbd, tbd, tbd, tbd, tbd, tbd, tbd, tbd, tbd, tbd, tbd, nmq },/* 027 */
    /* 028 */{ sta, sta, sta, sta, sta, sta, sta, sta, sta, sta, sta, sta, sta, sta, sta, sta,  sta, sta, sta, sta, sta, sta, sta, sta, tbd, tbd, tbd, tbd, tbd, tbd, tbd, try },/* 028 */
    /* 029 */{ fsr, fsr, fsr, fsr, fsr, fsr, fsr, fsr, fsr, fsr, fsr, fsr, fsr, fsr, fsr, fsr,  fsr, fsr, fsr, fsr, fsr, fsr, fsr, fsr, tbd, tbd, tbd, tbd, tbd, tbd, tbd, tov },/* 029 */
    /* 030 */{ xt0, xt0, xt0, xt0, xt0, xt0, xt0, xt0, xt0, xt0, xt0, xt0, xt0, xt0, xt0, xt0,  xt0, xt0, xt0, xt0, xt0, xt0, xt0, xt0, tbd, tbd, tbd, tbd, tbd, tbd, tbd, mfc },/* 030 */
    /* 031 */{ xt1, xt1, xt1, xt1, xt1, xt1, xt1, xt1, xt1, xt1, xt1, xt1, xt1, xt1, xt1, xt1,  xt1, xt1, xt1, xt1, xt1, xt1, xt1, xt1, tbd, tbd, tbd, tbd, tbd, tbd, tbd, z00 },/* 031 */
    /* SRC     000, 001, 002, 003, 004, 005, 006, 007  008, 009, 010, 011, 012, 013, 014, 015   016, 017, 018, 019, 020, 021, 022, 023  024, 025, 026, 027, 028, 029, 030, 031 */
};

UNIT g15_cpu_unit[] =
{
    UDATA (NULL, 0, 8)
};

REG g15_cpu_reg[] =
{
    { HRDATAD (PC, g15_cpu_cntx.PC, 32, "PC Register") },
    { HRDATAD (AR, g15_cpu_cntx.AR, 32, "AR Register") },
    { HRDATAD (ID, g15_cpu_cntx.ID, 32, "ID Register") },
    { HRDATAD (MQ, g15_cpu_cntx.MQ, 32, "MQ Register") },
    { HRDATAD (PN, g15_cpu_cntx.PN, 32, "PN Register") },
    { HRDATAD (IP, g15_cpu_cntx.IP, 32, "IP Register") },
    { HRDATAD (OV, g15_cpu_cntx.OV, 32, "OV Register") },
    { HRDATAD (IO, g15_cpu_cntx.IO, 32, "IO Register") },
    { NULL },
};

MTAB g15_cpu_mod[] =
{
    { 0 }
};

DEVICE g15_cpu_dev =
{
    name:        "CPU",
    units:       g15_cpu_unit,
    registers:   g15_cpu_reg,
    modifiers:   g15_cpu_mod,
    numunits:    1,
    aradix:      1,
    awidth:      31,
    aincr:       1,
    dradix:      1, // DEV_RDX,
    dwidth:      8,
    examine:     &g15_cpu_examine,
    deposit:     &g15_cpu_deposit,
    reset:       &g15_cpu_reset,
    boot:        NULL,
    attach:      NULL,
    detach:      NULL,
    ctxt:        NULL,
    flags:       0,
    dctrl:       0,
    debflags:    NULL,
    msize:       NULL,
    lname:       NULL,
    help:        &g15_cpu_help,
    attach_help: NULL,
    help_ctx:    NULL,
    description: &g15_cpu_desc,
    brk_types:   NULL,
    type_ctx:    NULL
};

const char *g15_cpu_desc(DEVICE *dptr)
{
    return "G15 CPU";
}

t_stat g15_cpu_reset(DEVICE *dptr)
{
    g15_cpu_cntx.state  = G15_STATE_WAIT_TO_EXECUTE;
    g15_cpu_cntx.reason = SCPE_OK;
    g15_cpu_cntx.halt   = false;
    g15_cpu_cntx.PC     = PC_MAKE(1, 0);
    g15_cpu_cntx.AR     = 0;
    g15_cpu_cntx.ID     = 0;
    g15_cpu_cntx.MQ     = 0;
    g15_cpu_cntx.PN     = 0;
    g15_cpu_cntx.IP     = 0;
    g15_cpu_cntx.IO     = 0;
    g15_cpu_cntx.OV     = 0;

    sim_brk_dflt  = SWMASK('E');
    sim_brk_types = sim_brk_dflt | SWMASK('M');
    
    return SCPE_OK;
}

t_stat g15_cpu_deposit(t_value val, t_addr addr, UNIT *uptr, int32 sw)
{
#if 0 
    if (addr >= MEMSIZE)
        return SCPE_NXM;
    M[addr] = val & DMASK;
    g15_drum_wr(line, word, val);
#endif
    return SCPE_OK;
}

t_stat g15_cpu_examine(t_value *vptr, t_addr addr, UNIT *uptr, int32 sw)
{
#if 0
    if (addr >= MEMSIZE)
        return SCPE_NXM;
    if (vptr != NULL)
        *vptr = M[addr] & DMASK;
    uin32_t val = g15_drum_rd(line, word);
    *vptr = val;
#endif
    return SCPE_OK;
}

t_stat g15_cpu_help(FILE *st, DEVICE *dptr, UNIT *uptr, int32 flag, const char *cptr)
{
    return SCPE_OK;
}

t_stat sim_instr(void)
{
    t_stat reason = SCPE_OK;

#if 0
    int32 PC = 0;

    while (reason == SCPE_OK)
    {
        // If there's a clock timeout, then break
        if (sim_interval <= 0)
        {
            if ((reason = sim_process_event()))
            {
                break;
            }
        }

        // If there's an execution breakpoint, then break
        if (sim_brk_summ && sim_brk_test(PC, SWMASK ('E')))
        {
            reason = STOP_IBKPT;
            break;
        }

        // If there's an I/O operation pending, then handle it
        if (false)
        {
            // TBD 
        }

        G15_CNTX * cntx = &g15_cpu_cntx;
        G15_INST inst = g15_util_w2i(g15_drum_rd(PC_LINE(cntx->PC), PC_WORD(cntx->PC)));
        sim_printf("cntx(line=%02u, next=%03u, AR=%04u), inst(P=%01u, L=%03u, C=%01u, S=%02u, D=%02u)\n", PC_LINE(cntx->PC), PC_WORD(cntx->PC), cntx->AR, inst.P, inst.L, inst.C, inst.S, inst.D);
        cntx->PC = PC_MAKE(PC_LINE(cntx->PC), inst.N);
        (*g15_cpu_dec[inst.S][inst.D])(cntx, inst);

    if (sim_step != 0) {
      if (--sim_step == 0)
        return SCPE_STEP;
    }

    if (halt)
      return STOP_HALT;

        if (cntx->halt)
        {
            reason = SCPE_STOP;
            break;
        }
    }
#endif

    return reason;
}

#if 0
void main()
{
    sim_printf("G15\n");

    G15_INST prog[] =
    {
        { P:0, L:000, N:001, C:1, S:00, D:28 }, // add 0:0
        { P:0, L:000, N:002, C:1, S:01, D:29 }, // add 0:1
        { P:0, L:000, N:003, C:0, S:00, D:24 }, // ldl
        { P:0, L:000, N:004, C:0, S:00, D:25 }, // ldr
        { P:0, L:000, N:000, C:0, S:16, D:31 }, // hlt
    };

    for (size_t i = 0; i < DIM(prog); i++)
    {
        g15_drum_wr(1, i, g15_util_i2w(prog[i]));
    }

    uint32_t data[] =
    {
        5,
        6
    };

    for (size_t i = 0; i < DIM(data); i++)
    {
        g15_drum_wr(0, i, data[i]);
    }

    g15_cpu_reset(&g15_cpu_dev);
    while (!g15_cpu_cntx.halt)
    {
        sim_instr();
    }
}
#endif
