/*
  ITU-T G.729A Speech Coder with Annex B    ANSI-C Source Code
*/

/*
----------------------------------------------------------------------
                    COPYRIGHT NOTICE
----------------------------------------------------------------------
   ITU-T G.729 Annex C ANSI C source code
   Copyright (C) 1998, AT&T, France Telecom, NTT, University of
   Sherbrooke.  All rights reserved.

----------------------------------------------------------------------
*/

#include <math.h>
#include "typedef.h"
#include "ld8a.h"
#include "tab_ld8a.h"

/* Prototype definitions of static functions */
static void lsp_iqua_cs(lsp_dec *state, int prm[], FLOAT lsp[], int erase);

/*----------------------------------------------------------------------------
 * Lsp_decw_reset -   set the previous LSP vectors
 *----------------------------------------------------------------------------
 */
void lsp_decw_reset(lsp_dec *state)
{
   int  i;

   for(i=0; i<MA_NP; i++)
     copy (freq_prev_reset, &state->freq_prev[i][0], M );

   state->prev_ma = 0;

   copy (freq_prev_reset, state->prev_lsp, M );

   return;
}


/*----------------------------------------------------------------------------
 * lsp_iqua_cs -  LSP main quantization routine
 *----------------------------------------------------------------------------
 */
static void lsp_iqua_cs(
 lsp_dec *state,
 int    prm[],          /* input : codes of the selected LSP */
 FLOAT  lsp_q[],        /* output: Quantized LSP parameters  */
 int    erase           /* input : frame erase information   */
)
{
   int  mode_index;
   int  code0;
   int  code1;
   int  code2;
   FLOAT buf[M];


   if(erase==0)                 /* Not frame erasure */
     {
        mode_index = (prm[0] >> NC0_B) & 1;
        code0 = prm[0] & (INT16)(NC0 - 1);
        code1 = (prm[1] >> NC1_B) & (INT16)(NC1 - 1);
        code2 = prm[1] & (INT16)(NC1 - 1);

        lsp_get_quant(lspcb1, lspcb2, code0, code1, code2, fg[mode_index],
              state->freq_prev, lsp_q, fg_sum[mode_index]);

        copy(lsp_q, state->prev_lsp, M );
        state->prev_ma = mode_index;
     }
   else                         /* Frame erased */
     {
       copy(state->prev_lsp, lsp_q, M );

        /* update freq_prev */
       lsp_prev_extract(state->prev_lsp, buf,
          fg[state->prev_ma], state->freq_prev, fg_sum_inv[state->prev_ma]);
       lsp_prev_update(buf, state->freq_prev);
     }
     return;
}
/*----------------------------------------------------------------------------
 * d_lsp - decode lsp parameters
 *----------------------------------------------------------------------------
 */
void d_lsp(lsp_dec *state,
    int     index[],    /* input : indexes                 */
    FLOAT   lsp_q[],    /* output: decoded lsp             */
    int     bfi         /* input : frame erase information */
)
{

   lsp_iqua_cs(state, index, lsp_q, bfi); /* decode quantized information */

   /* Convert LSFs to LSPs */

   lsf_lsp(lsp_q, lsp_q, M);

   return;
}

