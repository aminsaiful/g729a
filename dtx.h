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

/*--------------------------------------------------------------------------*
 * Prototypes for DTX/CNG                                                   *
 *--------------------------------------------------------------------------*/

/* Encoder DTX/CNG functions */
void init_cod_cng(enc_cng_state *state);
void cod_cng(
  enc_cng_state *state,
  FLOAT *exc,          /* (i/o) : excitation array                     */
  int pastVad,         /* (i)   : previous VAD decision                */
  FLOAT *lsp_old_q,    /* (i/o) : previous quantized lsp               */
  FLOAT *Aq,           /* (o)   : set of interpolated LPC coefficients */
  int *ana,            /* (o)   : coded SID parameters                 */
  FLOAT freq_prev[MA_NP][M],
                       /* (i/o) : previous LPS for quantization        */
  INT16 *seed          /* (i/o) : random generator seed                */
);
void update_cng(
  enc_cng_state *state,
  FLOAT *r,         /* (i) :   frame autocorrelation               */
  int Vad           /* (i) :   current Vad decision                */
);

/* SID gain Quantization */
void qua_Sidgain(
  FLOAT *ener,     /* (i)   array of energies                   */
  int nb_ener,     /* (i)   number of energies or               */
  FLOAT *enerq,    /* (o)   decoded energies in dB              */
  int *idx         /* (o)   SID gain quantization index         */
);

/* CNG excitation generation */
void calc_exc_rand(
  FLOAT exc_err[4],
  FLOAT cur_gain,      /* (i)   :   target sample gain                 */
  FLOAT *exc,          /* (i/o) :   excitation array                   */
  INT16 *seed,         /* (i)   :   current Vad decision               */
  int flag_cod         /* (i)   :   encoder/decoder flag               */
);

/* SID LSP Quantization */
void get_freq_prev(lsp_enc *state, FLOAT x[MA_NP][M]);
void update_freq_prev(lsp_enc *state, FLOAT x[MA_NP][M]);
void get_decfreq_prev(lsp_dec *state, FLOAT x[MA_NP][M]);
void update_decfreq_prev(lsp_dec *state, FLOAT x[MA_NP][M]);

/* Decoder CNG generation */
void init_dec_cng(dec_cng_state *state);
void dec_cng(
  dec_cng_state *state,
  int past_ftyp,       /* (i)   : past frame type                      */
  FLOAT sid_sav,       /* (i)   : energy to recover SID gain           */
  int *parm,           /* (i)   : coded SID parameters                 */
  FLOAT *exc,          /* (i/o) : excitation array                     */
  FLOAT *lsp_old,      /* (i/o) : previous lsp                         */
  FLOAT *A_t,          /* (o)   : set of interpolated LPC coefficients */
  INT16 *seed,         /* (i/o) : random generator seed                */
  FLOAT freq_prev[MA_NP][M]
                        /* (i/o) : previous LPS for quantization        */
);

/*--------------------------------------------------------------------------*
 * Constants for DTX/CNG                                                    *
 *--------------------------------------------------------------------------*/

/* DTX constants */
#define FLAG_COD        1
#define FLAG_DEC        0
#define INIT_SEED       (INT16)11111
#define FR_SID_MIN      3
#define NB_SUMACF       3
#define NB_CURACF       2
#define NB_GAIN         2
#define THRESH1         (FLOAT)1.1481628
#define THRESH2         (FLOAT)1.0966466
#define A_GAIN0         (FLOAT)0.875

#define SIZ_SUMACF      (NB_SUMACF * MP1)
#define SIZ_ACF         (NB_CURACF * MP1)
#define A_GAIN1         ((FLOAT)1. - A_GAIN0)

#define MIN_ENER        (FLOAT)0.1588489319   /* <=> - 8 dB      */

/* CNG excitation generation constant */
                                           /* alpha = 0.5 */
#define NORM_GAUSS      (FLOAT)3.16227766  /* sqrt(40)xalpha */
#define K0              (FLOAT)3.          /* 4 x (1 - alpha ** 2) */
#define G_MAX           (FLOAT)5000.

