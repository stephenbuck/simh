#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include "g15_defs.h"

typedef void (*G15_FUNC)(G15_CNTX * cntx, G15_INST inst);

static void tbd(G15_CNTX * cntx, G15_INST inst)
{
    g15_util_trace_enter(__FUNCTION__);
    g15_util_trace_leave();
}

static void aar(G15_CNTX * cntx, G15_INST inst)
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

static void add(G15_CNTX * cntx, G15_INST inst)
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

// Clear multiplication and division registers
static void clr(G15_CNTX * cntx, G15_INST inst)
{
    g15_util_trace_enter(__FUNCTION__);
    cntx->ID = 0;
    cntx->MQ = 0;
    cntx->PN = 0;
    cntx->IP = 0;
    g15_util_trace_leave();
}

// Transfer
static void cpy(G15_CNTX * cntx, G15_INST inst)
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

// Divide
static void dvd(G15_CNTX * cntx, G15_INST inst)
{
    g15_util_trace_enter(__FUNCTION__);
    g15_util_trace_leave();
}

// FSR
static void fsr(G15_CNTX * cntx, G15_INST inst)
{
    g15_util_trace_enter(__FUNCTION__);
    g15_util_trace_leave();
}

// Halt
static void hlt(G15_CNTX * cntx, G15_INST inst)
{
    g15_util_trace_enter(__FUNCTION__);
    cntx->halt = true;
    g15_util_trace_leave();
}

// Load to shift left
static void ldl(G15_CNTX * cntx, G15_INST inst)
{
    g15_util_trace_enter(__FUNCTION__);
    g15_util_trace_leave();
}

// Load numerator
static void ldn(G15_CNTX * cntx, G15_INST inst)
{
    g15_util_trace_enter(__FUNCTION__);
    g15_util_trace_leave();
}

// Load to shift right
static void ldr(G15_CNTX * cntx, G15_INST inst)
{
    g15_util_trace_enter(__FUNCTION__);
    g15_util_trace_leave();
}

// Write file code on magnetic tape
static void mfc(G15_CNTX * cntx, G15_INST inst)
{
    g15_util_trace_enter(__FUNCTION__);
    g15_mta2_cmd(inst.C, G15_MTA2_CMD_FILECODE);
    g15_util_trace_leave();
}

// Read magnetic tape
static void mrd(G15_CNTX * cntx, G15_INST inst)
{
    g15_util_trace_enter(__FUNCTION__);
    g15_mta2_cmd(inst.C, G15_MTA2_CMD_READ);
    g15_util_trace_leave();
}

// Select command line and mark
static void mrk(G15_CNTX * cntx, G15_INST inst)
{
    g15_util_trace_enter(__FUNCTION__);
    g15_util_trace_leave();
}

// Search magnetic tape, forward
static void msf(G15_CNTX * cntx, G15_INST inst)
{
    g15_util_trace_enter(__FUNCTION__);
    g15_mta2_cmd(inst.C, G15_MTA2_CMD_FORWARD);
    g15_util_trace_leave();
}

// Search magnetic tape, reverse
static void msr(G15_CNTX * cntx, G15_INST inst)
{
    g15_util_trace_enter(__FUNCTION__);
    g15_mta2_cmd(inst.C, G15_MTA2_CMD_REVERSE);
    g15_util_trace_leave();
}

// Multiply
static void mul(G15_CNTX * cntx, G15_INST inst)
{
    g15_util_trace_enter(__FUNCTION__);
    g15_util_trace_leave();
}

// Write on magnetic tape
static void mwr(G15_CNTX * cntx, G15_INST inst)
{
    g15_util_trace_enter(__FUNCTION__);
    g15_mta2_cmd(inst.C, G15_MTA2_CMD_WRITE);
    g15_util_trace_leave();
}

// Normalize MQ
static void nmq(G15_CNTX * cntx, G15_INST inst)
{
    g15_util_trace_enter(__FUNCTION__);
    g15_util_trace_leave();
}

// Print AR
static void par(G15_CNTX * cntx, G15_INST inst)
{
    g15_util_trace_enter(__FUNCTION__);
    switch (G15_INST_PCHR(inst))
    {
        // Print AR in numeric mode
        case 0:
            break;
        // Print AR in alphanumeric mode
        case 4:
            break;
    }
    g15_util_trace_leave();
}

// Read punched cards
static void pcr(G15_CNTX * cntx, G15_INST inst)
{
    g15_util_trace_enter(__FUNCTION__);
    g15_ca1_cmd(G15_CA1_CMD_TBD);
    g15_util_trace_leave();
}

// Write punched cards
static void pcw(G15_CNTX * cntx, G15_INST inst)
{
    g15_util_trace_enter(__FUNCTION__);
    g15_ca1_cmd(G15_CA1_CMD_TBD);
    g15_util_trace_leave();
}

// Prepare product for addition in PN
static void ppn(G15_CNTX * cntx, G15_INST inst)
{
    g15_util_trace_enter(__FUNCTION__);
    g15_util_trace_leave();
}

// Print line 19
static void pr9(G15_CNTX * cntx, G15_INST inst)
{
    g15_util_trace_enter(__FUNCTION__);
    switch (G15_INST_PCHR(inst))
    {
        // Print line 19 in numeric mode
        case 0:
            break;
        // Print line 19 in alphanumeric mode
        case 4:
            break;
    }
    g15_util_trace_leave();
}

// Permit type-in
static void prm(G15_CNTX * cntx, G15_INST inst)
{
    g15_util_trace_enter(__FUNCTION__);
    switch (G15_INST_PCHR(inst))
    {
        // Permit numeric type-in
        case 0:
            break;
        // Permit alphanumeric type-in
        case 4:
            break;
    }
    g15_util_trace_leave();
}

// Punch line 19 on tape
static void pt9(G15_CNTX * cntx, G15_INST inst)
{
    g15_util_trace_enter(__FUNCTION__);
    g15_util_trace_leave();
}

// TBD
static void ptb(G15_CNTX * cntx, G15_INST inst)
{
    g15_util_trace_enter(__FUNCTION__);
    g15_util_trace_leave();
}

// Reverse punched tape
static void ptr(G15_CNTX * cntx, G15_INST inst)
{
    g15_util_trace_enter(__FUNCTION__);
    g15_util_trace_leave();
}

// Select command line and return
static void ret(G15_CNTX * cntx, G15_INST inst)
{
    g15_util_trace_enter(__FUNCTION__);
    g15_util_trace_leave();
}

// Shift MQ
static void smq(G15_CNTX * cntx, G15_INST inst)
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

// Special
static void spc(G15_CNTX * cntx, G15_INST inst)
{
    g15_util_trace_enter(__FUNCTION__);
    switch (G15_INST_PCHR(inst))
    {
        // Halt
        case 16:
            break;
        // Ring bell
        case 17:
            break;
    }
    g15_util_trace_leave();
}

// Store sum or difference from AR
static void sta(G15_CNTX * cntx, G15_INST inst)
{
    g15_util_trace_enter(__FUNCTION__);
    g15_drum_wr(inst.L, inst.D, cntx->AR);
    g15_util_trace_leave();
}

// Store product
static void stp(G15_CNTX * cntx, G15_INST inst)
{
    g15_util_trace_enter(__FUNCTION__);
    g15_util_trace_leave();
}

// Store quotient
static void stq(G15_CNTX * cntx, G15_INST inst)
{
    g15_util_trace_enter(__FUNCTION__);
    g15_util_trace_leave();
}

// Test if sign of AR negative
static void tng(G15_CNTX * cntx, G15_INST inst)
{
    g15_util_trace_enter(__FUNCTION__);
    if (cntx->AR < 0) cntx->next = inst.N + 1;
    g15_util_trace_leave();
}

static void z02(G15_CNTX * cntx, G15_INST inst)
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

static void z03(G15_CNTX * cntx, G15_INST inst)
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

// Test for non-zero
static void tnz(G15_CNTX * cntx, G15_INST inst)
{
    g15_util_trace_enter(__FUNCTION__);
    if (cntx->AR != 0) cntx->next = inst.N + 1;
    g15_util_trace_leave();
}

// Test for overflow
static void tov(G15_CNTX * cntx, G15_INST inst)
{
    g15_util_trace_enter(__FUNCTION__);
    g15_util_trace_leave();
}

// Test "ready" state of input/output
static void try(G15_CNTX * cntx, G15_INST inst)
{
    g15_util_trace_enter(__FUNCTION__);
    g15_util_trace_leave();
}

// TBD
static void tsr(G15_CNTX * cntx, G15_INST inst)
{
    g15_util_trace_enter(__FUNCTION__);
    g15_util_trace_leave();
}

static void xt0(G15_CNTX * cntx, G15_INST inst)
{
    g15_util_trace_enter(__FUNCTION__);
    g15_util_trace_leave();
}

static void xt1(G15_CNTX * cntx, G15_INST inst)
{
    g15_util_trace_enter(__FUNCTION__);
    g15_util_trace_leave();
}

// Special 00
static void z00(G15_CNTX * cntx, G15_INST inst)
{
    g15_util_trace_enter(__FUNCTION__);
    switch (G15_INST_PCHR(inst))
    {
        // Take next command from AR
        case 0:
            cntx->next = cntx->AR; // BOZO
            break;
        // Copy number track into line 18
        case 1:
            break;
    }
    g15_util_trace_leave();
}

// Special 01
static void z01(G15_CNTX * cntx, G15_INST inst)
{
    g15_util_trace_enter(__FUNCTION__);
    switch (G15_INST_PCHR(inst))
    {
        // Ring bell
        case 0:
            break;
        // Test for punch switch on
        case 1:
            break;
    }
    g15_util_trace_leave();
}

static G15_FUNC g15_cpu_dec[32][32] =
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
};

REG g15_cpu_reg[] =
{
};

MTAB g15_cpu_mod[] =
{
};

DEVICE g15_cpu_dev =
{
    name:        "CPU",
    units:       g15_cpu_unit,
    registers:   g15_cpu_reg,
    modifiers:   g15_cpu_mod,
    numunits:    1,
};

const char *g15_cpu_desc(DEVICE *dptr)
{
    return "G15 CPU";
}

static G15_CNTX g15_cpu_cntx =
{
    halt:  false,
    line:  1,
    next:  0,
    AR:    0,
    ID:    0,
    MQ:    0,
    PN:    0,
    IP:    0
};

t_stat g15_cpu_reset(DEVICE *dptr)
{
    g15_cpu_cntx.halt = false;
    g15_cpu_cntx.line = 1;
    g15_cpu_cntx.next = 0;
    g15_cpu_cntx.AR   = 0;
    g15_cpu_cntx.ID   = 0;
    g15_cpu_cntx.MQ   = 0;
    g15_cpu_cntx.PN   = 0;
    g15_cpu_cntx.IP   = 0;

    sim_brk_types = sim_brk_dflt = SWMASK('M');
    
    return SCPE_OK;
}

t_stat sim_instr(void)
{
    t_stat reason = SCPE_OK;

    while (reason == SCPE_OK)
    {
#if 0
        // If there's a clock timeout, then break
        if (sim_interval <= 0)
        {
            if ((reason = sim_process_event()))
            {
                break;
            }
        }

        // If there's an execution breakpoint, then break
        if (sim_brk_summ && sim_brk_test(SC, SWMASK ('E')))
        {
            reason = STOP_IBKPT;
            break;
        }
#endif

        G15_CNTX * cntx = &g15_cpu_cntx;
        G15_INST inst = g15_util_w2i(g15_drum_rd(cntx->line, cntx->next));
        printf("cntx(line=%02u, next=%03u, AR=%04u), inst(P=%01u, L=%03u, C=%01u, S=%02u, D=%02u)\n", cntx->line, cntx->next, cntx->AR, inst.P, inst.L, inst.C, inst.S, inst.D);
        cntx->next = inst.N;
        (*g15_cpu_dec[inst.S][inst.D])(cntx, inst);

        if (cntx->halt)
        {
            reason = SCPE_STOP;
            break;
        }
    }

    return reason;
}

#if 0
void main()
{
    printf("G15\n");

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

    unsigned data[] =
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