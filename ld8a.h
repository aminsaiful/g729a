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


#include <stdio.h>
#include <stdlib.h>

#ifdef PI
#undef PI
#endif
#ifdef PI2
#undef PI2
#endif
#define PI              (F)3.141592654
#define PI2             (F)6.283185307
#define FLT_MAX_G729    (F)1.0e38    /* largest floating point number      */
#define FLT_MIN_G729    (F)-1.0e38   /* largest floating point number      */

/*--------------------------------------------------------------------------*
 *       Codec constant parameters (coder, decoder, and postfilter)         *
 *--------------------------------------------------------------------------*/

#define L_TOTAL         240     /* Total size of speech buffer              */
#define L_WINDOW        240     /* LPC analysis window size                 */
#define L_NEXT          40      /* Samples of next frame needed for LPC ana.*/
#define L_FRAME         80      /* LPC update frame size                    */
#define L_SUBFR         40      /* Sub-frame size                           */

#define PIT_MIN         20      /* Minimum pitch lag in samples             */
#define PIT_MAX         143     /* Maximum pitch lag in samples             */
#define L_INTERPOL      (10+1)  /* Length of filter for interpolation.      */
#define GAMMA1       (F)0.75    /* Bandwitdh expansion for W(z)             */


/*--------------------------------------------------------------------------*
 * constants for lpc analysis and lsp quantizer                             *
 *--------------------------------------------------------------------------*/

#define M               10      /* LPC order                                */
#define MP1             (M+1)   /* LPC order+1                              */
#define NC              (M/2)   /* LPC order / 2                            */
#define WNC          (F)1.0001  /* white noise correction factor            */
#define GRID_POINTS      50     /* resolution of lsp search                 */

#define MA_NP           4       /* MA prediction order for LSP              */
#define MODE            2       /* number of modes for MA prediction        */
#define NC0_B           7       /* number of bits in first stage            */
#define NC0          (1<<NC0_B) /* number of entries in first stage         */
#define NC1_B           5       /* number of bits in second stage           */
#define NC1          (1<<NC1_B) /* number of entries in second stage        */

#define L_LIMIT         (F)0.005   /*  */
#define M_LIMIT         (F)3.135   /*  */
#define GAP1            (F)0.0012  /*  */
#define GAP2            (F)0.0006  /*  */
#define GAP3            (F)0.0392  /*  */
#define PI04            PI*(F)0.04   /* pi*0.04 */
#define PI92            PI*(F)0.92   /* pi*0.92 */
#define CONST12         (F)1.2

/*------------------------------------------------------------------*
 *  Constants for long-term predictor                               *
 *------------------------------------------------------------------*/

#define  SHARPMAX       (F)0.7945  /* Maximum value of pitch sharpening */
#define  SHARPMIN       (F)0.2     /* Minimum value of pitch sharpening */
#define  GAIN_PIT_MAX   (F)1.2     /* Maximum adaptive codebook gain    */

#define  UP_SAMP         3         /* Resolution of fractional delays   */
#define  L_INTER10       10        /* Length for pitch interpolation    */
#define  FIR_SIZE_SYN    (UP_SAMP*L_INTER10+1)

/*-----------------------*
 * Innovative codebook.  *
 *-----------------------*/

#define DIM_RR  616 /* size of correlation matrix                            */
#define NB_POS  8   /* Number of positions for each pulse                    */
#define STEP    5   /* Step betweem position of the same pulse.              */
#define MSIZE   64  /* Size of vectors for cross-correlation between 2 pulses*/

/*------------------------------------------------------------------*
 *  gain quantizer                                                  *
 *------------------------------------------------------------------*/

#define MEAN_ENER     (F)36.0   /* Average innovation energy */
#define NCODE1           8      /* Codebook 1 size */
#define NCODE2           16     /* Codebook 2 size */
#define NCAN1            4      /* Pre-selecting order for #1 */
#define NCAN2            8      /* Pre-selecting order for #2 */
#define INV_COEF      (F)-0.032623

/*------------------------------------------------------------------*
 *  Constant for postfilter                                         *
 *------------------------------------------------------------------*/

#define  GAMMA2_PST  (F)0.55       /* Formant postfilt factor (numerator)   */
#define  GAMMA1_PST  (F)0.70       /* Formant postfilt factor (denominator) */
#define  GAMMAP      (F)0.50       /* Harmonic postfilt factor              */
#define  INV_GAMMAP  ((F)1.0/((F)1.0+GAMMAP))
#define  GAMMAP_2    (GAMMAP/((F)1.0+GAMMAP))

#define  MU          (F)0.8        /* Factor for tilt compensation filter   */
#define  AGC_FAC     (F)0.9        /* Factor for automatic gain control     */
#define  AGC_FAC1     ((F)1.-AGC_FAC)
#define  L_H 22   /* size of truncated impulse response of A(z/g1)/A(z/g2) */

/*--------------------------------------------------------------------------*
 * Constants for taming procedure.                           *
 *--------------------------------------------------------------------------*/

#define GPCLIP      (F)0.95     /* Maximum pitch gain if taming is needed */
#define GPCLIP2     (F)0.94     /* Maximum pitch gain if taming is needed */
#define GP0999      (F)0.9999   /* Maximum pitch gain if taming is needed    */
#define THRESH_ERR  (F)60000.   /* Error threshold taming    */
#define INV_L_SUBFR (FLOAT) ((F)1./(FLOAT)L_SUBFR) /* =0.025 */

/*-----------------------*
 * Bitstream constants   *
 *-----------------------*/

#define BIT_0     (INT16)0x007f /* definition of zero-bit in bit-stream     */
#define BIT_1     (INT16)0x0081 /* definition of one-bit in bit-stream      */
#define SYNC_WORD (INT16)0x6b21 /* definition of frame erasure flag         */
#define PRM_SIZE        11      /* number of parameters per 10 ms frame     */
#define SERIAL_SIZE     82      /* bits per frame                           */
#define SIZE_WORD (INT16)80     /* number of speech bits                     */

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

/*--------------------------------------------------------------------------*
 *       VAD                                                                *
 *--------------------------------------------------------------------------*/
#define EPSI            (F)1.0e-38   /* very small positive floating point number      */


/*-------------------------------*
 * context                       *
 *-------------------------------*/
typedef struct filter
{
  FLOAT x0, x1;		/* high-pass fir memory          */
  FLOAT y1, y2;		/* high-pass fir memory          */
} filter;


typedef struct lsp_dec
{
  FLOAT freq_prev[MA_NP][M];    /* previous LSP vector       */
/* memory for frame erase operation */
  int prev_ma;                  /* previous MA prediction coef.*/
  FLOAT prev_lsp[M];            /* previous LSP vector         */
} lsp_dec;

typedef struct lsp_enc
{
  FLOAT freq_prev[MA_NP][M];    /* previous LSP vector       */
} lsp_enc;


typedef struct post_filter_state
{
        /* inverse filtered synthesis (with A(z/GAMMA2_PST))   */
  FLOAT res2_buf[PIT_MAX+L_SUBFR];
  FLOAT *res2;

        /* memory of filter 1/A(z/GAMMA1_PST) */
  FLOAT mem_syn_pst[M];
  FLOAT mem_pre;
  FLOAT past_gain;
} post_filter_state;

typedef struct dec_cng_state
{
  /* dec_sid.c */
  FLOAT cur_gain;
  FLOAT lspSid[M];
  FLOAT sid_gain;

  /* timing.c */
  FLOAT exc_err[4];

  /* tab_dtx.c */
  FLOAT noise_fg[MODE][MA_NP][M];
} dec_cng_state;

typedef struct decoder_state
{
        /* Excitation vector */
  FLOAT old_exc[L_FRAME+PIT_MAX+L_INTERPOL];
  FLOAT *exc;

        /* Lsp (Line spectral pairs) */
  FLOAT lsp_old[M];

  FLOAT mem_syn[M];       /* Synthesis filter's memory          */
  FLOAT sharp;            /* pitch sharpening of previous frame */
  int old_T0;             /* integer delay of previous frame    */
  FLOAT gain_code;        /* Code gain                          */
  FLOAT gain_pitch;       /* Pitch gain                         */

  /* for G.729B */
  INT16 seed_fer;
  /* CNG variables */
  int past_ftyp;
  INT16 seed;
  FLOAT sid_sav;

  int bad_lsf;		/* bad LSF indicator   */
/*
   This variable should be always set to zero unless transmission errors
   in LSP indices are detected.
   This variable is useful if the channel coding designer decides to
   perform error checking on these important parameters. If an error is
   detected on the  LSP indices, the corresponding flag is
   set to 1 signalling to the decoder to perform parameter substitution.
   (The flags should be set back to 0 for correct transmission).
*/

  lsp_dec lsp_state;
  dec_cng_state cng_state;
  FLOAT past_qua_en[4];
  filter post_process;
  post_filter_state post_filter_state;
  FLOAT  synth_buf[L_FRAME+M];     /* Synthesis                  */
  FLOAT  *synth;
} decoder_state;

typedef struct enc_cng_state
{
  FLOAT lspSid_q[M] ;
  FLOAT pastCoeff[MP1];
  FLOAT RCoeff[MP1];
  FLOAT Acf[SIZ_ACF];
  FLOAT sumAcf[SIZ_SUMACF];
  FLOAT ener[NB_GAIN];
  int fr_cur;
  FLOAT cur_gain;
  int nb_ener;
  FLOAT sid_gain;
  int flag_chang;
  FLOAT prev_energy;
  int count_fr0;

  /* timing.c */
  FLOAT exc_err[4];

  /* tab_dtx.c */
  FLOAT noise_fg[MODE][MA_NP][M];
} enc_cng_state;

typedef struct vad_state
{
  FLOAT MeanLSF[M];
  FLOAT Min_buffer[16];
  FLOAT Prev_Min, Next_Min, Min;
  FLOAT MeanE, MeanSE, MeanSLE, MeanSZC;
  FLOAT prev_energy;
  int count_sil, count_update, count_ext;
  int flag, v_flag, less_count;
} vad_state;

typedef struct encoder_state
{
        /* Speech vector */
  FLOAT old_speech[L_TOTAL];
  FLOAT *speech, *p_window;
  FLOAT *new_speech;                    /* Global variable */
					/* Pointer to new speech data   */

        /* Weighted speech vector */
  FLOAT old_wsp[L_FRAME+PIT_MAX];
  FLOAT *wsp;

        /* Excitation vector */
  FLOAT old_exc[L_FRAME+PIT_MAX+L_INTERPOL];
  FLOAT *exc;

        /* LSP Line spectral frequencies */
  FLOAT lsp_old[M];
  FLOAT lsp_old_q[M];

        /* Filter's memory */
  FLOAT  mem_w0[M], mem_w[M], mem_zero[M];
  FLOAT  sharp;

	/* Last A(z) for case of unstable filter */
  FLOAT old_A[M+1];
  FLOAT old_rc[2];

  /* For G.729B */
  /* DTX variables */
  int pastVad;
  int ppastVad;
  INT16 seed;

  lsp_enc lsp_state;

  enc_cng_state cng_state;
  vad_state vad_state;

  FLOAT past_qua_en[4];
  filter pre_process;

  int frame;
  int dtx_enable;
} encoder_state;

/*-------------------------------*
 * Pre and post-process functions*
 *-------------------------------*/
void init_post_process(filter *state
);

void post_process(filter *state,
   FLOAT signal[],      /* (i/o)  : signal           */
   int lg               /* (i)    : lenght of signal */
);

void init_pre_process(filter *state
);

void pre_process(filter *state,
   FLOAT signal[],      /* (i/o)  : signal           */
   int lg               /* (i)    : lenght of signal */
);

/*----------------------------------*
 * Main coder and decoder functions *
 *----------------------------------*/
void  init_coder_ld8a(encoder_state *state);

void  coder_ld8a(encoder_state *state,
 int ana[],              /* output: analysis parameters */
 int frame,              /* input : frame counter */
 int dtx_enable          /* input : DTX enable flag */
);

void  init_decod_ld8a(decoder_state *state);

void  decod_ld8a(decoder_state *state,
  int parm[],          /* (i)   : vector of synthesis parameters
                                  parm[0] = bad frame indicator (bfi)  */
  FLOAT   synth[],     /* (o)   : synthesis speech                     */
  FLOAT   A_t[],       /* (o)   : decoded LP filter in 2 subframes     */
  int *T2,             /* (o)   : decoded pitch lag in 2 subframes     */
  int    *Vad          /* (o)   : decoded frame type                   */
);

/*-------------------------------*
 * LPC analysis and filtering.   *
 *-------------------------------*/
void  autocorr(FLOAT *x, int m, FLOAT *r);

void  lag_window(int m, FLOAT r[]);

FLOAT levinson(FLOAT *a, FLOAT *r, FLOAT *r_c, FLOAT *old_A, FLOAT *old_rc);

void  az_lsp(FLOAT *a, FLOAT *lsp, FLOAT *old_lsp);

void  int_qlpc(FLOAT lsp_new[], FLOAT lsp_old[], FLOAT a[]);

void  weight_az(FLOAT *a,  FLOAT gamma, int m,  FLOAT *ap);

void lsf_lsp(FLOAT *lsf, FLOAT *lsp, int m);

void lsp_lsf(FLOAT *lsp, FLOAT *lsf, int m);

void residu(    /* filter A(z)                                       */
 FLOAT *a,      /* input : prediction coefficients a[0:m+1], a[0]=1. */
 FLOAT *x,      /* input : input signal x[0:l-1], x[-1:m] are needed */
 FLOAT *y,      /* output: output signal y[0:l-1] NOTE: x[] and y[]
                            cannot point to same array               */
 int l          /* input : dimension of x and y                      */
);

void syn_filt(
 FLOAT a[],     /* input : predictor coefficients a[0:m]    */
 FLOAT x[],     /* input : excitation signal                */
 FLOAT y[],     /* output: filtered output signal           */
 int l,         /* input : vector dimension                 */
 FLOAT mem[],   /* in/out: filter memory                    */
 int update_m   /* input : 0 = no memory update, 1 = update */
);

void convolve(
 FLOAT x[],             /* input : input vector x[0:l]                     */
 FLOAT h[],             /* input : impulse response or second input h[0:l] */
 FLOAT y[],             /* output: x convolved with h , y[0:l]             */
 int l                  /* input : dimension of all vectors                */
);

/*-------------------------------------------------------------*
 * Prototypes of pitch functions                               *
 *-------------------------------------------------------------*/

int pitch_ol_fast(  /* output: open loop pitch lag                        */
   FLOAT signal[],  /* input : signal used to compute the open loop pitch */
                    /*     signal[-pit_max] to signal[-1] should be known */
   int L_frame      /* input : length of frame to compute pitch           */
);

int pitch_fr3_fast(     /* output: integer part of pitch period */
 FLOAT exc[],           /* input : excitation buffer            */
 FLOAT xn[],            /* input : target vector                */
 FLOAT h[],             /* input : impulse response.            */
 int L_subfr,           /* input : Length of subframe           */
 int t0_min,            /* input : minimum value in the searched range */
 int t0_max,            /* input : maximum value in the searched range */
 int i_subfr,           /* input : indicator for first subframe        */
 int *pit_frac          /* output: chosen fraction                     */
);

FLOAT g_pitch(FLOAT xn[], FLOAT y1[], FLOAT g_coeff[], int l);

int enc_lag3(     /* output: Return index of encoding */
  int T0,         /* input : Pitch delay              */
  int T0_frac,    /* input : Fractional pitch delay   */
  int *T0_min,    /* in/out: Minimum search delay     */
  int *T0_max,    /* in/out: Maximum search delay     */
  int pit_min,    /* input : Minimum pitch delay      */
  int pit_max,    /* input : Maximum pitch delay      */
  int pit_flag    /* input : Flag for 1st subframe    */
);

void dec_lag3(     /* Decode the pitch lag                   */
  int index,       /* input : received pitch index           */
  int pit_min,     /* input : minimum pitch lag              */
  int pit_max,     /* input : maximum pitch lag              */
  int i_subfr,     /* input : subframe flag                  */
  int *T0,         /* output: integer part of pitch lag      */
  int *T0_frac     /* output: fractional part of pitch lag   */
);

void pred_lt_3(       /* Compute adaptive codebook                       */
 FLOAT exc[],         /* in/out: excitation vector, exc[0:l_sub-1] = out */
 int t0,              /* input : pitch lag                               */
 int frac,            /* input : Fraction of pitch lag (-1, 0, 1)  / 3   */
 int l_sub            /* input : length of subframe.                     */
);

int parity_pitch(int pitch_i);

int check_parity_pitch(int pitch_i, int parity);

void cor_h_x(
     FLOAT h[],         /* (i) :Impulse response of filters      */
     FLOAT X[],         /* (i) :Target vector                    */
     FLOAT D[]          /* (o) :Correlations between h[] and D[] */
);

/*-----------------------*
 * Innovative codebook.  *
 *-----------------------*/

int ACELP_code_A(       /* (o) :index of pulses positions    */
  FLOAT x[],            /* (i) :Target vector                */
  FLOAT h[],            /* (i) :Inpulse response of filters  */
  int T0,               /* (i) :Pitch lag                    */
  FLOAT pitch_sharp,    /* (i) :Last quantized pitch gain    */
  FLOAT code[],         /* (o) :Innovative codebook          */
  FLOAT y[],            /* (o) :Filtered innovative codebook */
  int *sign             /* (o) :Signs of 4 pulses            */
);

void  decod_ACELP(int signs, int positions, FLOAT cod[]);

/*-----------------------------------------------------------*
 * Prototypes of LSP VQ functions                            *
 *-----------------------------------------------------------*/
void qua_lsp(
  lsp_enc *state,
  FLOAT lsp[],       /* (i) : Unquantized LSP            */
  FLOAT lsp_q[],     /* (o) : Quantized LSP              */
  int ana[]          /* (o) : indexes                    */
);

void lsp_encw_reset(lsp_enc *state);

void lsp_expand_1( FLOAT buf[], FLOAT c);

void lsp_expand_2( FLOAT buf[], FLOAT c);

void lsp_expand_1_2( FLOAT buf[], FLOAT c);

void lsp_get_quant(
  FLOAT lspcb1[][M],
  FLOAT lspcb2[][M],
  int code0,
  int code1,
  int code2,
  FLOAT fg[][M],
  FLOAT freq_prev[][M],
  FLOAT lspq[],
  FLOAT fg_sum[]
);

void d_lsp(
lsp_dec *state,
int index[],           /* input : indexes                 */
FLOAT lsp_new[],       /* output: decoded lsp             */
int bfi                /* input : frame erase information */
);

void lsp_decw_reset(lsp_dec *state);

void lsp_prev_extract(
  FLOAT lsp[M],
  FLOAT lsp_ele[M],
  FLOAT fg[MA_NP][M],
  FLOAT freq_prev[MA_NP][M],
  FLOAT fg_sum_inv[M]
);

void lsp_prev_update(
  FLOAT lsp_ele[M],
  FLOAT freq_prev[MA_NP][M]
);

void get_wegt( FLOAT flsp[], FLOAT wegt[] );

void lsp_stability(FLOAT  buf[]);
void lsp_prev_compose(FLOAT lsp_ele[],FLOAT lsp[],FLOAT fg[][M],
            FLOAT freq_prev[][M], FLOAT fg_sum[]);

/*--------------------------------------------------------------------------*
 * gain VQ functions.                                                       *
 *--------------------------------------------------------------------------*/
int qua_gain(FLOAT past_qua_en[], FLOAT code[], FLOAT *coeff, int lcode, FLOAT *gain_pit,
        FLOAT *gain_code, int tameflag   );

void  dec_gain(FLOAT past_qua_en[], int indice, FLOAT code[], int lcode, int bfi, FLOAT *gain_pit,
               FLOAT *gain_code);

void gain_predict(
  FLOAT past_qua_en[],  /* input :Past quantized energies       */
  FLOAT code[],         /* input: Innovative vector.            */
  int l_subfr,          /* input : Subframe length.             */
  FLOAT *gcode0         /* output : Predicted codebook gain     */
);

void gain_update(
  FLOAT past_qua_en[], /* input/output :Past quantized energies  */
  FLOAT g_code         /* input        : quantized gain          */
);

void gain_update_erasure(FLOAT *past_qua_en);

void  corr_xy2(FLOAT xn[], FLOAT y1[], FLOAT y2[], FLOAT g_coeff[]);

/*-----------------------*
 * Bitstream function    *
 *-----------------------*/
#ifdef TEST_CONTROL
void prm2bits_ld8k(
 int  prm[],            /* input : encoded parameters  */
 INT16 bits[]           /* output: serial bits         */
);
void bits2prm_ld8k(
 INT16 bits[],          /* input : serial bits        */
 int  prm[]             /* output: decoded parameters */
);
#endif
void  prm2bits_ld8k_frame(int prm[], unsigned char * bits, int *frame_size);

void  bits2prm_ld8k_frame(unsigned char * bits, int prm[], int frame_size);

/*-----------------------------------------------------------*
 * Prototypes for the post filtering                         *
 *-----------------------------------------------------------*/

void init_post_filter(post_filter_state *state);

void post_filter(
  post_filter_state *state,
  FLOAT *syn,     /* in/out: synthesis speech (postfiltered is output)    */
  FLOAT *a_t,     /* input : interpolated LPC parameters in all subframes */
  int *T,         /* input : decoded pitch lags in all subframes          */
  int Vad         /* input : decoded frame type                    */
);

/*------------------------------------------------------------*
 * prototypes for taming procedure.                           *
 *------------------------------------------------------------*/

void   init_exc_err(FLOAT exc_err[4]);

void   update_exc_err(FLOAT exc_err[4], FLOAT gain_pit, int t0);

int test_err(FLOAT exc_err[4], int t0, int t0_frac);

/*-----------------------------------------------------------*
 * Prototypes for auxiliary functions                        *
 *-----------------------------------------------------------*/
#if 0
void set_zero(
  FLOAT  x[],           /* (o)  : vector to clear  */
  int L                 /* (i)  : length of vector */
);

void copy(
  FLOAT  x[],           /* (i)  : input vector   */
  FLOAT  y[],           /* (o)  : output vector  */
  int L                 /* (i)  : vector length  */
);
#else
#include <string.h>
#include <memory.h>
#define set_zero(dst,L) memset((dst),0, sizeof(FLOAT)*(L));
#define copy(src,dst,L) memcpy((dst),(src),sizeof(FLOAT)*(L));
#endif

INT16 random_g729(INT16 *seed);

void dvsub(FLOAT *in1, FLOAT *in2, FLOAT *out, int npts);
FLOAT dvdot(FLOAT *in1, FLOAT *in2, int npts);
void dvwadd(FLOAT *in1, FLOAT scalar1, FLOAT *in2, FLOAT scalar2,
             FLOAT *out, int npts);
void dvsmul(FLOAT *in, FLOAT scalar, FLOAT *out, int npts);
