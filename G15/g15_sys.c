/* g15_sys.c: Bendix G15 simulator interface

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

#include "g15_defs.h"
#include <ctype.h>

extern DEVICE g15_cpu_dev;
extern REG    g15_cpu_reg[];
//extern DEVICE g15_an1_dev;
//extern DEVICE g15_at1_dev;
//extern DEVICE g15_ca1_dev;
//extern DEVICE g15_ca2_dev;
//extern DEVICE g15_ctl_dev;
//extern DEVICE g15_da1_dev;
//extern DEVICE g15_mta2_dev;
//extern DEVICE g15_pa3_dev;
//extern DEVICE g15_pr1_dev;
//extern DEVICE g15_pr2_dev;
//extern DEVICE g15_ptp1_dev;

/* SCP data structures and interface routines

   sim_name             simulator name string
   sim_PC               pointer to saved PC register descriptor
   sim_emax             maximum number of words for examine/deposit
   sim_devices          array of pointers to simulated devices
   sim_stop_messages    array of pointers to stop messages
   sim_load             binary loader
*/

char sim_name[] = "G15";

REG *sim_PC = &g15_cpu_reg[0];

int32 sim_emax = 1;

DEVICE *sim_devices[] =
{
    &g15_cpu_dev,
//    &g15_an1_dev,
//    &g15_at1_dev,
//    &g15_ca1_dev,
//    &g15_ca2_dev,
//    &g15_ctl_dev,
//    &g15_da1_dev,
//    &g15_mta2_dev,
//    &g15_pa3_dev,
//    &g15_pr1_dev,
//    &g15_pr2_dev,
//    &g15_ptp1_dev,
    NULL
};

const char *sim_stop_messages[SCPE_BASE] =
{
    "Unknown error",
    "STOP",
    "Breakpoint",
    "Arithmetic overflow"
};

t_stat sim_load(FILE *fi, CONST char *cptr, CONST char *fnam, int flag)
{
    return SCPE_OK;
}
