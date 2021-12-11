/* g15_defs.h: Bendix G15 simulator definitions 

   Copyright (c) 2021, Stephen E. Buck

   Permission is hereby granted, free of charge, to any person obtaining a
   copy of this software and associated documentation files (the "Software"),
   to deal in the Software without restriction, including without limitation
   the rights to use, copy, modify, merge, publish, distribute, sublicense,
   and/or sell copies of the Software, and to permit persons to whom the
   Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in
   all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
   ROBERT M SUPNIK BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
   IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
   CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

   Except as contained in this notice, the name of Stephen E. Buck shall not be
   be used in advertising or otherwise to promote the sale, use or other dealings
   in this Software without prior written authorization from Stephen E. Buck.
*/

#ifndef G15_DEFS_H_
#define G15_DEFS_H_    0

#include <stdbool.h>
#include "sim_defs.h"

#if defined(USE_INT64) || defined(USE_ADDR64)
#error "G15 does not support 64b values!"
#endif

#define STOP_RSRV       1      // Must be 1 
#define STOP_HALT       2      // Halt 
#define STOP_IBKPT      3      // Breakpoint 
#define STOP_INVINS     4      // Invalid Instruction

typedef enum {
    G15_STATE_READ_COMMAND,
    G15_STATE_WAIT_TO_EXECUTE,
    G15_STATE_EXECUTE,
    G15_STATE_WAIT_NEXT_COMMAND
} G15_STATE;

typedef enum {
   PC,
   AR,
   ID,
   PN,
   MQ
} G15_REGS;

/*
typedef struct {
    uint32_t ID:1;    // Immediate (0) or Deferred(1)
    uint32_t TL:7,    // Timing (Word or Duration)
    uint32_t BP:1,    // Breakpoint (1)
    uint32_t N:7,     // Next Command (Word)
    uint32_t C:2,     // Characteristic
    uint32_t S:5,     // Source
    uint32_t D:5,     // Destination
    uint32_t SD:1     // Single (0) or Double(1) Precision
} G15_CMND;
*/

#define DIM(a) (sizeof(a)/sizeof(a[0]))

typedef struct
{
    uint32_t P:1;
    uint32_t L:7;
    uint32_t N:7;
    uint32_t S:5;
    uint32_t C:2;
    uint32_t D:5;

} G15_INST;

uint32_t g15_util_i2w(G15_INST inst);
G15_INST g15_util_w2i(uint32_t word);
G15_INST g15_util_inst(uint8_t _P, uint16_t _L, uint16_t _N, uint8_t _C, uint16_t _S, uint16_t _D);

void g15_util_trace_enter(const char * context);
void g15_util_trace_leave(void);
void g15_util_trace_print(const char * message);

#define G15_INST_PCHR(inst) (((inst).P << 2) | (inst).C)

typedef struct
{
    G15_STATE state;
    t_stat    reason;
    bool      halt;
    uint32_t  PC;        // PC (line:word)
    uint32_t  AR;        // AR Register
    uint32_t  ID;        // ID Register
    uint32_t  MQ;        // MQ Register
    uint32_t  PN;        // PN Register
    uint32_t  IP;        // IP Register
    uint32_t  IO;        // I/O Ready
    uint32_t  OV;        // Overflow

} G15_CNTX;

#define G15_DRUM_RPM   1800
#define G15_DRUM_LINES 20
#define G15_DRUM_WORDS 108

typedef struct {
    uint8_t line;
    uint8_t word;
} G15_ADDR;

typedef struct {
   char *   name;
   size_t   size;
   uint32_t flags;
   uint32_t words[G15_DRUM_WORDS];
} G15_LINE;

typedef struct {
   G15_LINE lines[G15_DRUM_LINES];
} G15_DRUM;

uint32_t g15_drum_rd(uint8_t line, uint8_t word);
void     g15_drum_wr(uint8_t line, uint8_t word, uint32_t data);

#define G15_AN1_CMD_TBD        0
#define G15_AN1_CMD_PRINT_AR_N 1
#define G15_AN1_CMD_PRINT_AR_A 2
#define G15_AN1_CMD_PRINT_19_N 3
#define G15_AN1_CMD_PRINT_19_A 4
#define G15_AN1_CMD_TYPE_IN_A  5
#define G15_AN1_CMD_TYPE_IN_N  6

t_stat g15_an1_cmd(uint16_t cmd);

#define G15_AT1_CMD_TBD        0
#define G15_AT1_CMD_TBD        0
#define G15_AT1_CMD_PRINT_AR_N 1
#define G15_AT1_CMD_PRINT_AR_A 2
#define G15_AT1_CMD_PRINT_19_N 3
#define G15_AT1_CMD_PRINT_19_A 4
#define G15_AT1_CMD_TYPE_IN_A  5
#define G15_AT1_CMD_TYPE_IN_N  6

t_stat g15_at1_cmd(uint16_t cmd);

#define G15_BELL_CMD_RING      0

t_stat g15_bell_cmd(uint16_t cmd);

#define G15_CA1_CMD_TBD        0
#define G15_CA1_CMD_READ       1
#define G15_CA1_CMD_WRITE      2

t_stat g15_ca1_cmd(uint16_t cmd);

#define G15_CA2_CMD_TBD        0
#define G15_CA2_CMD_READ       1
#define G15_CA2_CMD_WRITE      2

t_stat g15_ca2_cmd(uint16_t cmd);

#define G15_CTL_CMD_TBD        0

t_stat g15_ctl_cmd(uint16_t cmd);

#define G15_DA1_CMD_TBD        0

t_stat g15_da1_cmd(uint16_t cmd);

#define G15_DRUM_CMD_TBD       0
#define G15_DRUM_CMD_TBD       1

t_stat g15_drum_cmd(uint16_t cmd);

#define G15_MTA2_CMD_READ      0
#define G15_MTA2_CMD_WRITE     1
#define G15_MTA2_CMD_FILECODE  2
#define G15_MTA2_CMD_FORWARD   3
#define G15_MTA2_CMD_REVERSE   4

t_stat g15_mta2_cmd(uint16_t unit, uint16_t cmd);

#define G15_PA3_CMD_TBD        0

t_stat g15_pa3_cmd(uint16_t cmd);

#define G15_PR1_CMD_READ       0
#define G15_PR1_CMD_REVERSE    1

t_stat g15_pr1_cmd(uint16_t cmd);

#define G15_PR2_CMD_READ       0
#define G15_PR2_CMD_REVERSE    1

t_stat g15_pr2_cmd(uint16_t cmd);

#define G15_PTP1_CMD_PUNCH     0
#define G15_PTP1_CMD_PUNCH_19  1
#define G15_PTP1_CMD_TEST_SW   2

t_stat g15_ptp1_cmd(uint16_t cmd, uint8_t arg);

#endif
