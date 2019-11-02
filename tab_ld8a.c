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

#include "typedef.h"
#include "ld8a.h"


 /*----------------------------------------------------------------------------
  * tab_ld8a - defines ROM tables (constants  declared as externals in functions
  *----------------------------------------------------------------------------
  */
/* Hamming_cos window for LPC analysis.           */

/*   Create with function ham_cos(window,200,40)  */
FLOAT hamwindow[L_WINDOW] = {        /* hamming-cosine window */
(F)0.08000000,
(F)0.08005703,
(F)0.08022812,
(F)0.08051321,
(F)0.08091225,
(F)0.08142514,
(F)0.08205172,
(F)0.08279188,
(F)0.08364540,
(F)0.08461212,
(F)0.08569173,
(F)0.08688401,
(F)0.08818865,
(F)0.08960532,
(F)0.09113365,
(F)0.09277334,
(F)0.09452391,
(F)0.09638494,
(F)0.09835598,
(F)0.10043652,
(F)0.10262608,
(F)0.10492408,
(F)0.10732999,
(F)0.10984316,
(F)0.11246302,
(F)0.11518890,
(F)0.11802010,
(F)0.12095598,
(F)0.12399574,
(F)0.12713866,
(F)0.13038395,
(F)0.13373083,
(F)0.13717847,
(F)0.14072597,
(F)0.14437246,
(F)0.14811710,
(F)0.15195890,
(F)0.15589692,
(F)0.15993017,
(F)0.16405767,
(F)0.16827843,
(F)0.17259133,
(F)0.17699537,
(F)0.18148938,
(F)0.18607232,
(F)0.19074300,
(F)0.19550033,
(F)0.20034306,
(F)0.20527001,
(F)0.21027996,
(F)0.21537170,
(F)0.22054392,
(F)0.22579536,
(F)0.23112471,
(F)0.23653066,
(F)0.24201185,
(F)0.24756692,
(F)0.25319457,
(F)0.25889328,
(F)0.26466170,
(F)0.27049842,
(F)0.27640197,
(F)0.28237087,
(F)0.28840363,
(F)0.29449883,
(F)0.30065489,
(F)0.30687031,
(F)0.31314352,
(F)0.31947297,
(F)0.32585713,
(F)0.33229437,
(F)0.33878314,
(F)0.34532180,
(F)0.35190874,
(F)0.35854232,
(F)0.36522087,
(F)0.37194279,
(F)0.37870640,
(F)0.38550997,
(F)0.39235184,
(F)0.39923036,
(F)0.40614375,
(F)0.41309035,
(F)0.42006844,
(F)0.42707625,
(F)0.43411207,
(F)0.44117412,
(F)0.44826069,
(F)0.45537004,
(F)0.46250033,
(F)0.46964988,
(F)0.47681686,
(F)0.48399949,
(F)0.49119604,
(F)0.49840465,
(F)0.50562358,
(F)0.51285106,
(F)0.52008528,
(F)0.52732444,
(F)0.53456670,
(F)0.54181033,
(F)0.54905349,
(F)0.55629444,
(F)0.56353134,
(F)0.57076240,
(F)0.57798582,
(F)0.58519983,
(F)0.59240264,
(F)0.59959245,
(F)0.60676748,
(F)0.61392599,
(F)0.62106609,
(F)0.62818617,
(F)0.63528436,
(F)0.64235890,
(F)0.64940804,
(F)0.65643007,
(F)0.66342324,
(F)0.67038584,
(F)0.67731601,
(F)0.68421221,
(F)0.69107264,
(F)0.69789559,
(F)0.70467937,
(F)0.71142232,
(F)0.71812278,
(F)0.72477907,
(F)0.73138952,
(F)0.73795253,
(F)0.74446648,
(F)0.75092971,
(F)0.75734061,
(F)0.76369762,
(F)0.76999915,
(F)0.77624369,
(F)0.78242958,
(F)0.78855544,
(F)0.79461962,
(F)0.80062068,
(F)0.80655706,
(F)0.81242740,
(F)0.81823015,
(F)0.82396388,
(F)0.82962728,
(F)0.83521879,
(F)0.84073710,
(F)0.84618086,
(F)0.85154873,
(F)0.85683930,
(F)0.86205131,
(F)0.86718345,
(F)0.87223446,
(F)0.87720311,
(F)0.88208807,
(F)0.88688827,
(F)0.89160240,
(F)0.89622939,
(F)0.90076804,
(F)0.90521723,
(F)0.90957582,
(F)0.91384280,
(F)0.91801709,
(F)0.92209762,
(F)0.92608339,
(F)0.92997342,
(F)0.93376678,
(F)0.93746245,
(F)0.94105959,
(F)0.94455731,
(F)0.94795465,
(F)0.95125085,
(F)0.95444512,
(F)0.95753652,
(F)0.96052444,
(F)0.96340811,
(F)0.96618676,
(F)0.96885973,
(F)0.97142631,
(F)0.97388595,
(F)0.97623801,
(F)0.97848189,
(F)0.98061699,
(F)0.98264289,
(F)0.98455900,
(F)0.98636484,
(F)0.98806006,
(F)0.98964417,
(F)0.99111670,
(F)0.99247742,
(F)0.99372596,
(F)0.99486196,
(F)0.99588519,
(F)0.99679530,
(F)0.99759221,
(F)0.99827564,
(F)0.99884540,
(F)0.99930143,
(F)0.99964350,
(F)0.99987161,
(F)0.99998569,
(F)1.00000000,
(F)0.99921930,
(F)0.99687845,
(F)0.99298108,
(F)0.98753333,
(F)0.98054361,
(F)0.97202289,
(F)0.96198452,
(F)0.95044410,
(F)0.93741965,
(F)0.92293155,
(F)0.90700239,
(F)0.88965708,
(F)0.87092263,
(F)0.85082841,
(F)0.82940567,
(F)0.80668795,
(F)0.78271067,
(F)0.75751126,
(F)0.73112911,
(F)0.70360541,
(F)0.67498308,
(F)0.64530689,
(F)0.61462307,
(F)0.58297962,
(F)0.55042595,
(F)0.51701277,
(F)0.48279238,
(F)0.44781810,
(F)0.41214463,
(F)0.37582767,
(F)0.33892387,
(F)0.30149087,
(F)0.26358715,
(F)0.22527184,
(F)0.18660481,
(F)0.14764643,
(F)0.10845750,
(F)0.06909923,
(F)0.02963307
};

/*-----------------------------------------------------*

 | Table of lag_window for autocorrelation.            |

 | Bandwidth expansion = 60 Hz                         |

 -----------------------------------------------------*/

FLOAT lwindow[MP1] = {          /* lag window for correlations */
WNC,
(F)0.99889028,
(F)0.99556851,
(F)0.99005681,
(F)0.98239160,
(F)0.97262347,
(F)0.96081644,
(F)0.94704735,
(F)0.93140495,
(F)0.91398895,
(F)0.89490914
};

FLOAT lspcb1[NC0][M] = {
{(F)0.1814,
(F)0.2647,
(F)0.4580,
(F)1.1077,
(F)1.4813,
(F)1.7022,
(F)2.1953,
(F)2.3405,
(F)2.5867,
(F)2.6636},

{(F)0.2113,
(F)0.3223,
(F)0.4212,
(F)0.5946,
(F)0.7479,
(F)0.9615,
(F)1.9097,
(F)2.1750,
(F)2.4773,
(F)2.6737},

{(F)0.1915,
(F)0.2755,
(F)0.3770,
(F)0.5950,
(F)1.3505,
(F)1.6349,
(F)2.2348,
(F)2.3552,
(F)2.5768,
(F)2.6540},

{(F)0.2116,
(F)0.3067,
(F)0.4099,
(F)0.5748,
(F)0.8518,
(F)1.2569,
(F)2.0782,
(F)2.1920,
(F)2.3371,
(F)2.4842},

{(F)0.2129,
(F)0.2974,
(F)0.4039,
(F)1.0659,
(F)1.2735,
(F)1.4658,
(F)1.9061,
(F)2.0312,
(F)2.6074,
(F)2.6750},

{(F)0.2181,
(F)0.2893,
(F)0.4117,
(F)0.5519,
(F)0.8295,
(F)1.5825,
(F)2.1575,
(F)2.3179,
(F)2.5458,
(F)2.6417},

{(F)0.1991,
(F)0.2971,
(F)0.4104,
(F)0.7725,
(F)1.3073,
(F)1.4665,
(F)1.6208,
(F)1.6973,
(F)2.3732,
(F)2.5743},

{(F)0.1818,
(F)0.2886,
(F)0.4018,
(F)0.7630,
(F)1.1264,
(F)1.2699,
(F)1.6899,
(F)1.8650,
(F)2.1633,
(F)2.6186},

{(F)0.2282,
(F)0.3093,
(F)0.4243,
(F)0.5329,
(F)1.1173,
(F)1.7717,
(F)1.9420,
(F)2.0780,
(F)2.5160,
(F)2.6137},

{(F)0.2528,
(F)0.3693,
(F)0.5290,
(F)0.7146,
(F)0.9528,
(F)1.1269,
(F)1.2936,
(F)1.9589,
(F)2.4548,
(F)2.6653},

{(F)0.2332,
(F)0.3263,
(F)0.4174,
(F)0.5202,
(F)1.3633,
(F)1.8447,
(F)2.0236,
(F)2.1474,
(F)2.3572,
(F)2.4738},

{(F)0.1393,
(F)0.2216,
(F)0.3204,
(F)0.5644,
(F)0.7929,
(F)1.1705,
(F)1.7051,
(F)2.0054,
(F)2.3623,
(F)2.5985},

{(F)0.2677,
(F)0.3871,
(F)0.5746,
(F)0.7091,
(F)1.3311,
(F)1.5260,
(F)1.7288,
(F)1.9122,
(F)2.5787,
(F)2.6598},

{(F)0.1570,
(F)0.2328,
(F)0.3111,
(F)0.4216,
(F)1.1688,
(F)1.4605,
(F)1.9505,
(F)2.1173,
(F)2.4038,
(F)2.7460},

{(F)0.2346,
(F)0.3321,
(F)0.5621,
(F)0.8160,
(F)1.4042,
(F)1.5860,
(F)1.7518,
(F)1.8631,
(F)2.0749,
(F)2.5380},

{(F)0.2505,
(F)0.3368,
(F)0.4758,
(F)0.6405,
(F)0.8104,
(F)1.2533,
(F)1.9329,
(F)2.0526,
(F)2.2155,
(F)2.6459},

{(F)0.2196,
(F)0.3049,
(F)0.6857,
(F)1.3976,
(F)1.6100,
(F)1.7958,
(F)2.0813,
(F)2.2211,
(F)2.4789,
(F)2.5857},

{(F)0.1232,
(F)0.2011,
(F)0.3527,
(F)0.6969,
(F)1.1647,
(F)1.5081,
(F)1.8593,
(F)2.2576,
(F)2.5594,
(F)2.6896},

{(F)0.3682,
(F)0.4632,
(F)0.6600,
(F)0.9118,
(F)1.5245,
(F)1.7071,
(F)1.8712,
(F)1.9939,
(F)2.4356,
(F)2.5380},

{(F)0.2690,
(F)0.3711,
(F)0.4635,
(F)0.6644,
(F)1.4633,
(F)1.6495,
(F)1.8227,
(F)1.9983,
(F)2.1797,
(F)2.2954},

{(F)0.3555,
(F)0.5240,
(F)0.9751,
(F)1.1685,
(F)1.4114,
(F)1.6168,
(F)1.7769,
(F)2.0178,
(F)2.4420,
(F)2.5724},

{(F)0.3493,
(F)0.4404,
(F)0.7231,
(F)0.8587,
(F)1.1272,
(F)1.4715,
(F)1.6760,
(F)2.2042,
(F)2.4735,
(F)2.5604},

{(F)0.3747,
(F)0.5263,
(F)0.7284,
(F)0.8994,
(F)1.4017,
(F)1.5502,
(F)1.7468,
(F)1.9816,
(F)2.2380,
(F)2.3404},

{(F)0.2972,
(F)0.4470,
(F)0.5941,
(F)0.7078,
(F)1.2675,
(F)1.4310,
(F)1.5930,
(F)1.9126,
(F)2.3026,
(F)2.4208},

{(F)0.2467,
(F)0.3180,
(F)0.4712,
(F)1.1281,
(F)1.6206,
(F)1.7876,
(F)1.9544,
(F)2.0873,
(F)2.3521,
(F)2.4721},

{(F)0.2292,
(F)0.3430,
(F)0.4383,
(F)0.5747,
(F)1.3497,
(F)1.5187,
(F)1.9070,
(F)2.0958,
(F)2.2902,
(F)2.4301},

{(F)0.2573,
(F)0.3508,
(F)0.4484,
(F)0.7079,
(F)1.6577,
(F)1.7929,
(F)1.9456,
(F)2.0847,
(F)2.3060,
(F)2.4208},

{(F)0.1968,
(F)0.2789,
(F)0.3594,
(F)0.4361,
(F)1.0034,
(F)1.7040,
(F)1.9439,
(F)2.1044,
(F)2.2696,
(F)2.4558},

{(F)0.2955,
(F)0.3853,
(F)0.7986,
(F)1.2470,
(F)1.4723,
(F)1.6522,
(F)1.8684,
(F)2.0084,
(F)2.2849,
(F)2.4268},

{(F)0.2036,
(F)0.3189,
(F)0.4314,
(F)0.6393,
(F)1.2834,
(F)1.4278,
(F)1.5796,
(F)2.0506,
(F)2.2044,
(F)2.3656},

{(F)0.2916,
(F)0.3684,
(F)0.5907,
(F)1.1394,
(F)1.3933,
(F)1.5540,
(F)1.8341,
(F)1.9835,
(F)2.1301,
(F)2.2800},

{(F)0.2289,
(F)0.3402,
(F)0.5166,
(F)0.7716,
(F)1.0614,
(F)1.2389,
(F)1.4386,
(F)2.0769,
(F)2.2715,
(F)2.4366},

{(F)0.0829,
(F)0.1723,
(F)0.5682,
(F)0.9773,
(F)1.3973,
(F)1.6174,
(F)1.9242,
(F)2.2128,
(F)2.4855,
(F)2.6327},

{(F)0.2244,
(F)0.3169,
(F)0.4368,
(F)0.5625,
(F)0.6897,
(F)1.3763,
(F)1.7524,
(F)1.9393,
(F)2.5121,
(F)2.6556},

{(F)0.1591,
(F)0.2387,
(F)0.2924,
(F)0.4056,
(F)1.4677,
(F)1.6802,
(F)1.9389,
(F)2.2067,
(F)2.4635,
(F)2.5919},

{(F)0.1756,
(F)0.2566,
(F)0.3251,
(F)0.4227,
(F)1.0167,
(F)1.2649,
(F)1.6801,
(F)2.1055,
(F)2.4088,
(F)2.7276},

{(F)0.1050,
(F)0.2325,
(F)0.7445,
(F)0.9491,
(F)1.1982,
(F)1.4658,
(F)1.8093,
(F)2.0397,
(F)2.4155,
(F)2.5797},

{(F)0.2043,
(F)0.3324,
(F)0.4522,
(F)0.7477,
(F)0.9361,
(F)1.1533,
(F)1.6703,
(F)1.7631,
(F)2.5071,
(F)2.6528},

{(F)0.1522,
(F)0.2258,
(F)0.3543,
(F)0.5504,
(F)0.8815,
(F)1.5516,
(F)1.8110,
(F)1.9915,
(F)2.3603,
(F)2.7735},

{(F)0.1862,
(F)0.2759,
(F)0.4715,
(F)0.6908,
(F)0.8963,
(F)1.4341,
(F)1.6322,
(F)1.7630,
(F)2.2027,
(F)2.6043},

{(F)0.1460,
(F)0.2254,
(F)0.3790,
(F)0.8622,
(F)1.3394,
(F)1.5754,
(F)1.8084,
(F)2.0798,
(F)2.4319,
(F)2.7632},

{(F)0.2621,
(F)0.3792,
(F)0.5463,
(F)0.7948,
(F)1.0043,
(F)1.1921,
(F)1.3409,
(F)1.4845,
(F)2.3159,
(F)2.6002},

{(F)0.1935,
(F)0.2937,
(F)0.3656,
(F)0.4927,
(F)1.4015,
(F)1.6086,
(F)1.7724,
(F)1.8837,
(F)2.4374,
(F)2.5971},

{(F)0.2171,
(F)0.3282,
(F)0.4412,
(F)0.5713,
(F)1.1554,
(F)1.3506,
(F)1.5227,
(F)1.9923,
(F)2.4100,
(F)2.5391},

{(F)0.2274,
(F)0.3157,
(F)0.4263,
(F)0.8202,
(F)1.4293,
(F)1.5884,
(F)1.7535,
(F)1.9688,
(F)2.3939,
(F)2.4934},

{(F)0.1704,
(F)0.2633,
(F)0.3259,
(F)0.4134,
(F)1.2948,
(F)1.4802,
(F)1.6619,
(F)2.0393,
(F)2.3165,
(F)2.6083},

{(F)0.1763,
(F)0.2585,
(F)0.4012,
(F)0.7609,
(F)1.1503,
(F)1.5847,
(F)1.8309,
(F)1.9352,
(F)2.0982,
(F)2.6681},

{(F)0.2447,
(F)0.3535,
(F)0.4618,
(F)0.5979,
(F)0.7530,
(F)0.8908,
(F)1.5393,
(F)2.0075,
(F)2.3557,
(F)2.6203},

{(F)0.1826,
(F)0.3496,
(F)0.7764,
(F)0.9888,
(F)1.3915,
(F)1.7421,
(F)1.9412,
(F)2.1620,
(F)2.4999,
(F)2.6931},

{(F)0.3033,
(F)0.3802,
(F)0.6981,
(F)0.8664,
(F)1.0254,
(F)1.5401,
(F)1.7180,
(F)1.8124,
(F)2.5068,
(F)2.6119},

{(F)0.2960,
(F)0.4001,
(F)0.6465,
(F)0.7672,
(F)1.3782,
(F)1.5751,
(F)1.9559,
(F)2.1373,
(F)2.3601,
(F)2.4760},

{(F)0.3132,
(F)0.4613,
(F)0.6544,
(F)0.8532,
(F)1.0721,
(F)1.2730,
(F)1.7566,
(F)1.9217,
(F)2.1693,
(F)2.6531},

{(F)0.3329,
(F)0.4131,
(F)0.8073,
(F)1.1297,
(F)1.2869,
(F)1.4937,
(F)1.7885,
(F)1.9150,
(F)2.4505,
(F)2.5760},

{(F)0.2340,
(F)0.3605,
(F)0.7659,
(F)0.9874,
(F)1.1854,
(F)1.3337,
(F)1.5128,
(F)2.0062,
(F)2.4427,
(F)2.5859},

{(F)0.4131,
(F)0.5330,
(F)0.6530,
(F)0.9360,
(F)1.3648,
(F)1.5388,
(F)1.6994,
(F)1.8707,
(F)2.4294,
(F)2.5335},

{(F)0.3754,
(F)0.5229,
(F)0.7265,
(F)0.9301,
(F)1.1724,
(F)1.3440,
(F)1.5118,
(F)1.7098,
(F)2.5218,
(F)2.6242},

{(F)0.2138,
(F)0.2998,
(F)0.6283,
(F)1.2166,
(F)1.4187,
(F)1.6084,
(F)1.7992,
(F)2.0106,
(F)2.5377,
(F)2.6558},

{(F)0.1761,
(F)0.2672,
(F)0.4065,
(F)0.8317,
(F)1.0900,
(F)1.4814,
(F)1.7672,
(F)1.8685,
(F)2.3969,
(F)2.5079},

{(F)0.2801,
(F)0.3535,
(F)0.4969,
(F)0.9809,
(F)1.4934,
(F)1.6378,
(F)1.8021,
(F)2.1200,
(F)2.3135,
(F)2.4034},

{(F)0.2365,
(F)0.3246,
(F)0.5618,
(F)0.8176,
(F)1.1073,
(F)1.5702,
(F)1.7331,
(F)1.8592,
(F)1.9589,
(F)2.3044},

{(F)0.2529,
(F)0.3251,
(F)0.5147,
(F)1.1530,
(F)1.3291,
(F)1.5005,
(F)1.7028,
(F)1.8200,
(F)2.3482,
(F)2.4831},

{(F)0.2125,
(F)0.3041,
(F)0.4259,
(F)0.9935,
(F)1.1788,
(F)1.3615,
(F)1.6121,
(F)1.7930,
(F)2.5509,
(F)2.6742},

{(F)0.2685,
(F)0.3518,
(F)0.5707,
(F)1.0410,
(F)1.2270,
(F)1.3927,
(F)1.7622,
(F)1.8876,
(F)2.0985,
(F)2.5144},

{(F)0.2373,
(F)0.3648,
(F)0.5099,
(F)0.7373,
(F)0.9129,
(F)1.0421,
(F)1.7312,
(F)1.8984,
(F)2.1512,
(F)2.6342},

{(F)0.2229,
(F)0.3876,
(F)0.8621,
(F)1.1986,
(F)1.5655,
(F)1.8861,
(F)2.2376,
(F)2.4239,
(F)2.6648,
(F)2.7359},

{(F)0.3009,
(F)0.3719,
(F)0.5887,
(F)0.7297,
(F)0.9395,
(F)1.8797,
(F)2.0423,
(F)2.1541,
(F)2.5132,
(F)2.6026},

{(F)0.3114,
(F)0.4142,
(F)0.6476,
(F)0.8448,
(F)1.2495,
(F)1.7192,
(F)2.2148,
(F)2.3432,
(F)2.5246,
(F)2.6046},

{(F)0.3666,
(F)0.4638,
(F)0.6496,
(F)0.7858,
(F)0.9667,
(F)1.4213,
(F)1.9300,
(F)2.0564,
(F)2.2119,
(F)2.3170},

{(F)0.4218,
(F)0.5075,
(F)0.8348,
(F)1.0009,
(F)1.2057,
(F)1.5032,
(F)1.9416,
(F)2.0540,
(F)2.4352,
(F)2.5504},

{(F)0.3726,
(F)0.4602,
(F)0.5971,
(F)0.7093,
(F)0.8517,
(F)1.2361,
(F)1.8052,
(F)1.9520,
(F)2.4137,
(F)2.5518},

{(F)0.4482,
(F)0.5318,
(F)0.7114,
(F)0.8542,
(F)1.0328,
(F)1.4751,
(F)1.7278,
(F)1.8237,
(F)2.3496,
(F)2.4931},

{(F)0.3316,
(F)0.4498,
(F)0.6404,
(F)0.8162,
(F)1.0332,
(F)1.2209,
(F)1.5130,
(F)1.7250,
(F)1.9715,
(F)2.4141},

{(F)0.2375,
(F)0.3221,
(F)0.5042,
(F)0.9760,
(F)1.7503,
(F)1.9014,
(F)2.0822,
(F)2.2225,
(F)2.4689,
(F)2.5632},

{(F)0.2813,
(F)0.3575,
(F)0.5032,
(F)0.5889,
(F)0.6885,
(F)1.6040,
(F)1.9318,
(F)2.0677,
(F)2.4546,
(F)2.5701},

{(F)0.2198,
(F)0.3072,
(F)0.4090,
(F)0.6371,
(F)1.6365,
(F)1.9468,
(F)2.1507,
(F)2.2633,
(F)2.5063,
(F)2.5943},

{(F)0.1754,
(F)0.2716,
(F)0.3361,
(F)0.5550,
(F)1.1789,
(F)1.3728,
(F)1.8527,
(F)1.9919,
(F)2.1349,
(F)2.3359},

{(F)0.2832,
(F)0.3540,
(F)0.6080,
(F)0.8467,
(F)1.0259,
(F)1.6467,
(F)1.8987,
(F)1.9875,
(F)2.4744,
(F)2.5527},

{(F)0.2670,
(F)0.3564,
(F)0.5628,
(F)0.7172,
(F)0.9021,
(F)1.5328,
(F)1.7131,
(F)2.0501,
(F)2.5633,
(F)2.6574},

{(F)0.2729,
(F)0.3569,
(F)0.6252,
(F)0.7641,
(F)0.9887,
(F)1.6589,
(F)1.8726,
(F)1.9947,
(F)2.1884,
(F)2.4609},

{(F)0.2155,
(F)0.3221,
(F)0.4580,
(F)0.6995,
(F)0.9623,
(F)1.2339,
(F)1.6642,
(F)1.8823,
(F)2.0518,
(F)2.2674},

{(F)0.4224,
(F)0.7009,
(F)1.1714,
(F)1.4334,
(F)1.7595,
(F)1.9629,
(F)2.2185,
(F)2.3304,
(F)2.5446,
(F)2.6369},

{(F)0.4560,
(F)0.5403,
(F)0.7568,
(F)0.8989,
(F)1.1292,
(F)1.7687,
(F)1.9575,
(F)2.0784,
(F)2.4260,
(F)2.5484},

{(F)0.4299,
(F)0.5833,
(F)0.8408,
(F)1.0596,
(F)1.5524,
(F)1.7484,
(F)1.9471,
(F)2.2034,
(F)2.4617,
(F)2.5812},

{(F)0.2614,
(F)0.3624,
(F)0.8381,
(F)0.9829,
(F)1.2220,
(F)1.6064,
(F)1.8083,
(F)1.9362,
(F)2.1397,
(F)2.2773},

{(F)0.5064,
(F)0.7481,
(F)1.1021,
(F)1.3271,
(F)1.5486,
(F)1.7096,
(F)1.9503,
(F)2.1006,
(F)2.3911,
(F)2.5141},

{(F)0.5375,
(F)0.6552,
(F)0.8099,
(F)1.0219,
(F)1.2407,
(F)1.4160,
(F)1.8266,
(F)1.9936,
(F)2.1951,
(F)2.2911},

{(F)0.4994,
(F)0.6575,
(F)0.8365,
(F)1.0706,
(F)1.4116,
(F)1.6224,
(F)1.9200,
(F)2.0667,
(F)2.3262,
(F)2.4539},

{(F)0.3353,
(F)0.4426,
(F)0.6469,
(F)0.9161,
(F)1.2528,
(F)1.3956,
(F)1.6080,
(F)1.8909,
(F)2.0600,
(F)2.1380},

{(F)0.2745,
(F)0.4341,
(F)1.0424,
(F)1.2928,
(F)1.5461,
(F)1.7940,
(F)2.0161,
(F)2.1758,
(F)2.4742,
(F)2.5937},

{(F)0.1562,
(F)0.2393,
(F)0.4786,
(F)0.9513,
(F)1.2395,
(F)1.8010,
(F)2.0320,
(F)2.2143,
(F)2.5243,
(F)2.6204},

{(F)0.2979,
(F)0.4242,
(F)0.8224,
(F)1.0564,
(F)1.4881,
(F)1.7808,
(F)2.0898,
(F)2.1882,
(F)2.3328,
(F)2.4389},

{(F)0.2294,
(F)0.3070,
(F)0.5490,
(F)0.9244,
(F)1.2229,
(F)1.8248,
(F)1.9704,
(F)2.0627,
(F)2.2458,
(F)2.3653},

{(F)0.3423,
(F)0.4502,
(F)0.9144,
(F)1.2313,
(F)1.3694,
(F)1.5517,
(F)1.9907,
(F)2.1326,
(F)2.4509,
(F)2.5789},

{(F)0.2470,
(F)0.3275,
(F)0.4729,
(F)1.0093,
(F)1.2519,
(F)1.4216,
(F)1.8540,
(F)2.0877,
(F)2.3151,
(F)2.4156},

{(F)0.3447,
(F)0.4401,
(F)0.7099,
(F)1.0493,
(F)1.2312,
(F)1.4001,
(F)2.0225,
(F)2.1317,
(F)2.2894,
(F)2.4263},

{(F)0.3481,
(F)0.4494,
(F)0.6446,
(F)0.9336,
(F)1.1198,
(F)1.2620,
(F)1.8264,
(F)1.9712,
(F)2.1435,
(F)2.2552},

{(F)0.1646,
(F)0.3229,
(F)0.7112,
(F)1.0725,
(F)1.2964,
(F)1.5663,
(F)1.9843,
(F)2.2363,
(F)2.5798,
(F)2.7572},

{(F)0.2614,
(F)0.3707,
(F)0.5241,
(F)0.7425,
(F)0.9269,
(F)1.2976,
(F)2.0945,
(F)2.2014,
(F)2.6204,
(F)2.6959},

{(F)0.1963,
(F)0.2900,
(F)0.4131,
(F)0.8397,
(F)1.2171,
(F)1.3705,
(F)2.0665,
(F)2.1546,
(F)2.4640,
(F)2.5782},

{(F)0.3387,
(F)0.4415,
(F)0.6121,
(F)0.8005,
(F)0.9507,
(F)1.0937,
(F)2.0836,
(F)2.2342,
(F)2.3849,
(F)2.5076},

{(F)0.2362,
(F)0.5876,
(F)0.7574,
(F)0.8804,
(F)1.0961,
(F)1.4240,
(F)1.9519,
(F)2.1742,
(F)2.4935,
(F)2.6493},

{(F)0.2793,
(F)0.4282,
(F)0.6149,
(F)0.8352,
(F)1.0106,
(F)1.1766,
(F)1.8392,
(F)2.0119,
(F)2.6433,
(F)2.7117},

{(F)0.3603,
(F)0.4604,
(F)0.5955,
(F)0.9251,
(F)1.1006,
(F)1.2572,
(F)1.7688,
(F)1.8607,
(F)2.4687,
(F)2.5623},

{(F)0.3975,
(F)0.5849,
(F)0.8059,
(F)0.9182,
(F)1.0552,
(F)1.1850,
(F)1.6356,
(F)1.9627,
(F)2.3318,
(F)2.4719},

{(F)0.2231,
(F)0.3192,
(F)0.4256,
(F)0.7373,
(F)1.4831,
(F)1.6874,
(F)1.9765,
(F)2.1097,
(F)2.6152,
(F)2.6906},

{(F)0.1221,
(F)0.2081,
(F)0.3665,
(F)0.7734,
(F)1.0341,
(F)1.2818,
(F)1.8162,
(F)2.0727,
(F)2.4446,
(F)2.7377},

{(F)0.2010,
(F)0.2791,
(F)0.3796,
(F)0.8845,
(F)1.4030,
(F)1.5615,
(F)2.0538,
(F)2.1567,
(F)2.3171,
(F)2.4686},

{(F)0.2086,
(F)0.3053,
(F)0.4047,
(F)0.8224,
(F)1.0656,
(F)1.2115,
(F)1.9641,
(F)2.0871,
(F)2.2430,
(F)2.4313},

{(F)0.3203,
(F)0.4285,
(F)0.5467,
(F)0.6891,
(F)1.2039,
(F)1.3569,
(F)1.8578,
(F)2.2055,
(F)2.3906,
(F)2.4881},

{(F)0.3074,
(F)0.4192,
(F)0.5772,
(F)0.7799,
(F)0.9866,
(F)1.1335,
(F)1.6068,
(F)2.2441,
(F)2.4194,
(F)2.5089},

{(F)0.2108,
(F)0.2910,
(F)0.4993,
(F)0.7695,
(F)0.9528,
(F)1.5681,
(F)1.7838,
(F)2.1495,
(F)2.3522,
(F)2.4636},

{(F)0.3492,
(F)0.4560,
(F)0.5906,
(F)0.7379,
(F)0.8855,
(F)1.0257,
(F)1.7128,
(F)1.9997,
(F)2.2019,
(F)2.3694},

{(F)0.5185,
(F)0.7316,
(F)0.9708,
(F)1.1954,
(F)1.5066,
(F)1.7887,
(F)2.1396,
(F)2.2918,
(F)2.5429,
(F)2.6489},

{(F)0.4276,
(F)0.4946,
(F)0.6934,
(F)0.8308,
(F)0.9944,
(F)1.4582,
(F)2.0324,
(F)2.1294,
(F)2.4891,
(F)2.6324},

{(F)0.3847,
(F)0.5973,
(F)0.7202,
(F)0.8787,
(F)1.3938,
(F)1.5959,
(F)1.8463,
(F)2.1574,
(F)2.5050,
(F)2.6687},

{(F)0.4835,
(F)0.5919,
(F)0.7235,
(F)0.8862,
(F)1.0756,
(F)1.2853,
(F)1.9118,
(F)2.0215,
(F)2.2213,
(F)2.4638},

{(F)0.5492,
(F)0.8062,
(F)0.9810,
(F)1.1293,
(F)1.3189,
(F)1.5415,
(F)1.9385,
(F)2.1378,
(F)2.4439,
(F)2.5691},

{(F)0.5190,
(F)0.6764,
(F)0.8123,
(F)1.0154,
(F)1.2085,
(F)1.4266,
(F)1.8433,
(F)2.0866,
(F)2.5113,
(F)2.6474},

{(F)0.4602,
(F)0.6503,
(F)0.9602,
(F)1.1427,
(F)1.3043,
(F)1.4427,
(F)1.6676,
(F)1.8758,
(F)2.2868,
(F)2.4271},

{(F)0.3764,
(F)0.4845,
(F)0.7627,
(F)0.9914,
(F)1.1961,
(F)1.3421,
(F)1.5129,
(F)1.6707,
(F)2.1836,
(F)2.3322},

{(F)0.3334,
(F)0.5701,
(F)0.8622,
(F)1.1232,
(F)1.3851,
(F)1.6767,
(F)2.0600,
(F)2.2946,
(F)2.5375,
(F)2.7295},

{(F)0.1449,
(F)0.2719,
(F)0.5783,
(F)0.8807,
(F)1.1746,
(F)1.5422,
(F)1.8804,
(F)2.1934,
(F)2.4734,
(F)2.8728},

{(F)0.2333,
(F)0.3024,
(F)0.4780,
(F)1.2327,
(F)1.4180,
(F)1.5815,
(F)1.9804,
(F)2.0921,
(F)2.3524,
(F)2.5304},

{(F)0.2154,
(F)0.3075,
(F)0.4746,
(F)0.8477,
(F)1.1170,
(F)1.5369,
(F)1.9847,
(F)2.0733,
(F)2.1880,
(F)2.2504},

{(F)0.1709,
(F)0.4486,
(F)0.8705,
(F)1.0643,
(F)1.3047,
(F)1.5269,
(F)1.9175,
(F)2.1621,
(F)2.4073,
(F)2.5718},

{(F)0.2835,
(F)0.3752,
(F)0.5234,
(F)0.9898,
(F)1.1484,
(F)1.2974,
(F)1.9363,
(F)2.0378,
(F)2.4065,
(F)2.6214},

{(F)0.3211,
(F)0.4077,
(F)0.5809,
(F)1.0206,
(F)1.2542,
(F)1.3835,
(F)1.5723,
(F)2.1209,
(F)2.3464,
(F)2.4336},

{(F)0.2101,
(F)0.3146,
(F)0.6779,
(F)0.8783,
(F)1.0561,
(F)1.3045,
(F)1.8395,
(F)2.0695,
(F)2.2831,
(F)2.4328}
};

FLOAT lspcb2[NC1][M] = {
{(F)-0.0532,
(F)-0.0995,
(F)-0.0906,
(F)0.1261,
(F)-0.0633,
(F)0.0711,
(F)-0.1467,
(F)0.1012,
(F)0.0106,
(F)0.0470},

{(F)-0.1017,
(F)-0.1088,
(F)0.0566,
(F)-0.0010,
(F)-0.1528,
(F)0.1771,
(F)0.0089,
(F)-0.0282,
(F)0.1055,
(F)0.0808},

{(F)-0.1247,
(F)0.0283,
(F)-0.0374,
(F)0.0393,
(F)-0.0269,
(F)-0.0200,
(F)-0.0643,
(F)-0.0921,
(F)-0.1994,
(F)0.0327},

{(F)0.0070,
(F)-0.0242,
(F)-0.0415,
(F)-0.0041,
(F)-0.1793,
(F)0.0700,
(F)0.0972,
(F)-0.0207,
(F)-0.0771,
(F)0.0997},

{(F)0.0209,
(F)-0.0428,
(F)0.0359,
(F)0.2027,
(F)0.0554,
(F)0.0634,
(F)0.0356,
(F)0.0195,
(F)-0.0782,
(F)-0.1583},

{(F)-0.0856,
(F)-0.1028,
(F)-0.0071,
(F)0.1160,
(F)0.1089,
(F)0.1892,
(F)0.0874,
(F)0.0644,
(F)-0.0872,
(F)-0.0236},

{(F)0.0713,
(F)0.0039,
(F)-0.0353,
(F)0.0435,
(F)-0.0407,
(F)-0.0558,
(F)0.0748,
(F)-0.0346,
(F)-0.1686,
(F)-0.0905},

{(F)-0.0134,
(F)-0.0987,
(F)0.0283,
(F)0.0095,
(F)-0.0107,
(F)-0.0420,
(F)0.1638,
(F)0.1328,
(F)-0.0799,
(F)-0.0695},

{(F)-0.1049,
(F)0.1510,
(F)0.0672,
(F)0.1043,
(F)0.0872,
(F)-0.0663,
(F)-0.2139,
(F)-0.0239,
(F)-0.0120,
(F)-0.0338},

{(F)-0.1071,
(F)-0.1165,
(F)-0.1524,
(F)-0.0365,
(F)0.0260,
(F)-0.0288,
(F)-0.0889,
(F)0.1159,
(F)0.1852,
(F)0.1093},

{(F)-0.0094,
(F)0.0420,
(F)-0.0758,
(F)0.0932,
(F)0.0505,
(F)0.0614,
(F)-0.0443,
(F)-0.1172,
(F)-0.0590,
(F)0.1693},

{(F)-0.0384,
(F)-0.0375,
(F)-0.0313,
(F)-0.1539,
(F)-0.0524,
(F)0.0550,
(F)-0.0569,
(F)-0.0133,
(F)0.1233,
(F)0.2714},

{(F)0.0869,
(F)0.0847,
(F)0.0637,
(F)0.0794,
(F)0.1594,
(F)-0.0035,
(F)-0.0462,
(F)0.0909,
(F)-0.1227,
(F)0.0294},

{(F)-0.0137,
(F)-0.0332,
(F)-0.0611,
(F)0.1156,
(F)0.2116,
(F)0.0332,
(F)-0.0019,
(F)0.1110,
(F)-0.0317,
(F)0.2061},

{(F)0.0703,
(F)-0.0013,
(F)-0.0572,
(F)-0.0243,
(F)0.1345,
(F)-0.1235,
(F)0.0710,
(F)-0.0065,
(F)-0.0912,
(F)0.1072},

{(F)0.0178,
(F)-0.0349,
(F)-0.1563,
(F)-0.0487,
(F)0.0044,
(F)-0.0609,
(F)-0.1682,
(F)0.0023,
(F)-0.0542,
(F)0.1811},

{(F)-0.1384,
(F)-0.1020,
(F)0.1649,
(F)0.1568,
(F)-0.0116,
(F)0.1240,
(F)-0.0271,
(F)0.0541,
(F)0.0455,
(F)-0.0433},

{(F)-0.1782,
(F)-0.1511,
(F)0.0509,
(F)-0.0261,
(F)0.0570,
(F)0.0817,
(F)0.0805,
(F)0.2003,
(F)0.1138,
(F)0.0653},

{(F)-0.0019,
(F)0.0081,
(F)0.0572,
(F)0.1245,
(F)-0.0914,
(F)0.1691,
(F)-0.0223,
(F)-0.1108,
(F)-0.0881,
(F)-0.0320},

{(F)-0.0413,
(F)0.0181,
(F)0.1764,
(F)0.0092,
(F)-0.0928,
(F)0.0695,
(F)0.1523,
(F)0.0412,
(F)0.0508,
(F)-0.0148},

{(F)0.0476,
(F)0.0292,
(F)0.1915,
(F)0.1198,
(F)0.0139,
(F)0.0451,
(F)-0.1225,
(F)-0.0619,
(F)-0.0717,
(F)-0.1104},

{(F)-0.0382,
(F)-0.0120,
(F)0.1159,
(F)0.0039,
(F)0.1348,
(F)0.0088,
(F)-0.0173,
(F)0.1789,
(F)0.0078,
(F)-0.0959},

{(F)0.1376,
(F)0.0713,
(F)0.1020,
(F)0.0339,
(F)-0.1415,
(F)0.0254,
(F)0.0368,
(F)-0.1077,
(F)0.0143,
(F)-0.0494},

{(F)0.0658,
(F)-0.0140,
(F)0.1046,
(F)-0.0603,
(F)0.0273,
(F)-0.1114,
(F)0.0761,
(F)-0.0093,
(F)0.0338,
(F)-0.0538},

{(F)0.2683,
(F)0.2853,
(F)0.1549,
(F)0.0819,
(F)0.0372,
(F)-0.0327,
(F)-0.0642,
(F)0.0172,
(F)0.1077,
(F)-0.0170},

{(F)-0.1949,
(F)0.0672,
(F)0.0978,
(F)-0.0557,
(F)-0.0069,
(F)-0.0851,
(F)0.1057,
(F)0.1294,
(F)0.0505,
(F)0.0545},

{(F)0.1409,
(F)0.0724,
(F)-0.0094,
(F)0.1511,
(F)-0.0039,
(F)0.0710,
(F)-0.1266,
(F)-0.1093,
(F)0.0817,
(F)0.0363},

{(F)0.0485,
(F)0.0682,
(F)0.0248,
(F)-0.0974,
(F)-0.1122,
(F)0.0004,
(F)0.0845,
(F)-0.0357,
(F)0.1282,
(F)0.0955},

{(F)0.0408,
(F)0.1801,
(F)0.0772,
(F)-0.0098,
(F)0.0059,
(F)-0.1296,
(F)-0.0591,
(F)0.0443,
(F)-0.0729,
(F)-0.1041},

{(F)-0.0666,
(F)-0.0403,
(F)-0.0524,
(F)-0.0831,
(F)0.1384,
(F)-0.1443,
(F)-0.0909,
(F)0.1636,
(F)0.0320,
(F)0.0077},

{(F)0.1612,
(F)0.1010,
(F)-0.0486,
(F)-0.0704,
(F)0.0417,
(F)-0.0945,
(F)-0.0590,
(F)-0.1523,
(F)-0.0086,
(F)0.0120},

{(F)-0.0199,
(F)0.0823,
(F)-0.0014,
(F)-0.1082,
(F)0.0649,
(F)-0.1374,
(F)-0.0324,
(F)-0.0296,
(F)0.0885,
(F)0.1141}
};

FLOAT fg[2][MA_NP][M] = {
{{(F)0.2570,
(F)0.2780,
(F)0.2800,
(F)0.2736,
(F)0.2757,
(F)0.2764,
(F)0.2675,
(F)0.2678,
(F)0.2779,
(F)0.2647},

{(F)0.2142,
(F)0.2194,
(F)0.2331,
(F)0.2230,
(F)0.2272,
(F)0.2252,
(F)0.2148,
(F)0.2123,
(F)0.2115,
(F)0.2096},

{(F)0.1670,
(F)0.1523,
(F)0.1567,
(F)0.1580,
(F)0.1601,
(F)0.1569,
(F)0.1589,
(F)0.1555,
(F)0.1474,
(F)0.1571},

{(F)0.1238,
(F)0.0925,
(F)0.0798,
(F)0.0923,
(F)0.0890,
(F)0.0828,
(F)0.1010,
(F)0.0988,
(F)0.0872,
(F)0.1060},
},

{{(F)0.2360,
(F)0.2405,
(F)0.2499,
(F)0.2495,
(F)0.2517,
(F)0.2591,
(F)0.2636,
(F)0.2625,
(F)0.2551,
(F)0.2310},

{(F)0.1285,
(F)0.0925,
(F)0.0779,
(F)0.1060,
(F)0.1183,
(F)0.1176,
(F)0.1277,
(F)0.1268,
(F)0.1193,
(F)0.1211},

{(F)0.0981,
(F)0.0589,
(F)0.0401,
(F)0.0654,
(F)0.0761,
(F)0.0728,
(F)0.0841,
(F)0.0826,
(F)0.0776,
(F)0.0891},

{(F)0.0923,
(F)0.0486,
(F)0.0287,
(F)0.0498,
(F)0.0526,
(F)0.0482,
(F)0.0621,
(F)0.0636,
(F)0.0584,
(F)0.0794}
}

};

FLOAT fg_sum[2][M] = {
{(F)0.2380000054836,
(F)0.2578000128269,
(F)0.2504000067711,
(F)0.2531000375748,
(F)0.2480000108480,
(F)0.2587000429630,
(F)0.2577999532223,
(F)0.2656000256538,
(F)0.2760000228882,
(F)0.2625999450684},

{(F)0.4451000094414,
(F)0.5595000386238,
(F)0.6034000515938,
(F)0.5292999744415,
(F)0.5012999176979,
(F)0.5023000240326,
(F)0.4625000357628,
(F)0.4645000100136,
(F)0.4895999729633,
(F)0.4793999791145}
};

FLOAT fg_sum_inv[2][M] = {
{(F)4.2016806602478,
(F)3.8789758682251,
(F)3.9936101436615,
(F)3.9510068893433,
(F)4.0322580337524,
(F)3.8654806613922,
(F)3.8789765834808,
(F)3.7650599479675,
(F)3.6231880187988,
(F)3.8080739974976},

{(F)2.2466859817505,
(F)1.7873100042343,
(F)1.6572753190994,
(F)1.8892878293991,
(F)1.9948137998581,
(F)1.9908419847488,
(F)2.1621620655060,
(F)2.1528525352478,
(F)2.0424838066101,
(F)2.0859408378601}
};

/*-------------------------------------------------------------*

 *  Table for az_lsf()                                         *

 *                                                             *

 * Vector grid[] is in Q15                                     *

 *                                                             *

 * grid[0] = 1.0;                                              *

 * grid[grid_points+1] = -1.0;                                 *

 * for (i = 1; i < grid_points; i++)                           *

 *   grid[i] = cos((6.283185307*i)/(2.0*grid_points));         *

 *                                                             *

 *-------------------------------------------------------------*/

/* Version 51 points */

FLOAT grid[GRID_POINTS+1] = { /* grid for evaluating  Chebychev polynomials */
(F)0.9997559,
(F)0.9980267,
(F)0.9921147,
(F)0.9822872,
(F)0.9685832,
(F)0.9510565,
(F)0.9297765,
(F)0.9048271,
(F)0.8763067,
(F)0.8443279,
(F)0.8090170,
(F)0.7705132,
(F)0.7289686,
(F)0.6845471,
(F)0.6374240,
(F)0.5877852,
(F)0.5358268,
(F)0.4817537,
(F)0.4257793,
(F)0.3681245,
(F)0.3090170,
(F)0.2486899,
(F)0.1873813,
(F)0.1253332,
(F)0.0627905,
(F)0.0000000,
(F)-0.0627905,
(F)-0.1253332,
(F)-0.1873813,
(F)-0.2486899,
(F)-0.3090170,
(F)-0.3681245,
(F)-0.4257793,
(F)-0.4817537,
(F)-0.5358268,
(F)-0.5877852,
(F)-0.6374240,
(F)-0.6845471,
(F)-0.7289686,
(F)-0.7705132,
(F)-0.8090170,
(F)-0.8443279,
(F)-0.8763067,
(F)-0.9048271,
(F)-0.9297765,
(F)-0.9510565,
(F)-0.9685832,
(F)-0.9822872,
(F)-0.9921147,
(F)-0.9980267,
(F)-0.9997559
};

FLOAT freq_prev_reset[M] = {  /* previous LSP vector(init) */
 (F)0.285599,  (F)0.571199,  (F)0.856798,  (F)1.142397,  (F)1.427997,
 (F)1.713596,  (F)1.999195,  (F)2.284795,  (F)2.570394,  (F)2.855993
};     /* PI*(float)(j+1)/(float)(M+1) */

/*-----------------------------------------------------*

 | Tables for pitch related routines .                 |

 -----------------------------------------------------*/

/*** LTP interpolation filter ****/
/* 1/3 resolution interpolation filter  (-3 dB at 3600 Hz) */
FLOAT inter_3l[FIR_SIZE_SYN] = {
(F)0.898517,
(F)0.769271,
(F)0.448635,
(F)0.095915,
(F)-0.134333,
(F)-0.178528,
(F)-0.084919,
(F)0.036952,
(F)0.095533,
(F)0.068936,
(F)-0.000000,
(F)-0.050404,
(F)-0.050835,
(F)-0.014169,
(F)0.023083,
(F)0.033543,
(F)0.016774,
(F)-0.007466,
(F)-0.019340,
(F)-0.013755,
(F)0.000000,
(F)0.009400,
(F)0.009029,
(F)0.002381,
(F)-0.003658,
(F)-0.005027,
(F)-0.002405,
(F)0.001050,
(F)0.002780,
(F)0.002145,
(F)0.000000
};

/*-----------------------------------------------------*

 | Tables for gain related routines .                  |

 -----------------------------------------------------*/

/**********************************************************************
  gain quantizer
 **********************************************************************/

FLOAT pred[4] = {               /* MA prediction coeff */
(F)0.68,
(F)0.58,
(F)0.34,
(F)0.19
};

FLOAT gbk1[NCODE1][2] = {
{(F)0.000010,
(F)0.185084},

{(F)0.094719,
(F)0.296035},

{(F)0.111779,
(F)0.613122},

{(F)0.003516,
(F)0.659780},

{(F)0.117258,
(F)1.134277},

{(F)0.197901,
(F)1.214512},

{(F)0.021772,
(F)1.801288},

{(F)0.163457,
(F)3.315700}
};

FLOAT gbk2[NCODE2][2] = {
{(F)0.050466,
(F)0.244769},

{(F)0.121711,
(F)0.000010},

{(F)0.313871,
(F)0.072357},

{(F)0.375977,
(F)0.292399},

{(F)0.493870,
(F)0.593410},

{(F)0.556641,
(F)0.064087},

{(F)0.645363,
(F)0.362118},

{(F)0.706138,
(F)0.146110},

{(F)0.809357,
(F)0.397579},

{(F)0.866379,
(F)0.199087},

{(F)0.923602,
(F)0.599938},

{(F)0.925376,
(F)1.742757},

{(F)0.942028,
(F)0.029027},

{(F)0.983459,
(F)0.414166},

{(F)1.055892,
(F)0.227186},

{(F)1.158039,
(F)0.724592}
};

int  map1[NCODE1] = {
 5, 1, 4, 7, 3, 0, 6, 2};

int  map2[NCODE2] = {
 4, 6, 0, 2,12,14, 8,10,15,11, 9,13, 7, 3, 1, 5};

FLOAT coef[2][2] = {
{(F)31.134575,
(F)1.612322},

{(F)0.481389,
(F)0.053056}
};

FLOAT thr1[NCODE1-NCAN1] = {
(F)0.659681,
(F)0.755274,
(F)1.207205,
(F)1.987740
};

FLOAT thr2[NCODE2-NCAN2] = {
(F)0.429912,
(F)0.494045,
(F)0.618737,
(F)0.650676,
(F)0.717949,
(F)0.770050,
(F)0.850628,
(F)0.932089
};

int  imap1[NCODE1] = {
 5, 1, 7, 4, 2, 0, 6, 3};

int  imap2[NCODE2] = {
 2,14, 3,13, 0,15, 1,12, 6,10, 7, 9, 4,11, 5, 8};


/*-----------------------------------------------------*

 | Tables for routines post_pro() & pre_proc().        |

 -----------------------------------------------------*/

/* filter coefficients (fc = 100 Hz ) */

FLOAT b100[3] = {(F)0.93980581E+00, (F)-0.18795834E+01,  (F)0.93980581E+00};
FLOAT a100[3] = {(F)1.00000000E+00,  (F)0.19330735E+01, (F)-0.93589199E+00};

/* filter coefficients (fc = 140 Hz)  */

FLOAT b140[3] = {(F)0.92727435E+00, (F)-0.18544941E+01, (F)0.92727435E+00};
FLOAT a140[3] = {(F)1.00000000E+00, (F)0.19059465E+01, (F)-0.91140240E+00};


/*-----------------------------------------------------*

 | Tables for routine bits().                          |

 -----------------------------------------------------*/

int  bitsno[PRM_SIZE] = {8,              /* MA + 1st stage */
                               10,             /* 2nd stage */
                               8,1,  13,4, 7,  /* first subframe  */
                               5,    13,4, 7}; /* second subframe */


        /* LSP Line spectral frequencies */

FLOAT lsp_old[M] =
     { (F)0.9595,  (F)0.8413,  (F)0.6549,  (F)0.4154,  (F)0.1423,
      (F)-0.1423, (F)-0.4154, (F)-0.6549, (F)-0.8413, (F)-0.9595};

FLOAT past_qua_en[4]={(F)-14.0,(F)-14.0,(F)-14.0,(F)-14.0};


