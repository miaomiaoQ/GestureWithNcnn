//
// File: ADist.cpp
//
// MATLAB Coder version            : 3.3
// C/C++ source code generated on  : 25-Jul-2017 17:12:03
//

// Include Files
#include "rt_nonfinite.h"
#include "ADist.h"

// Function Declarations
static void b_abs(const double x[64], double y[64]);
static void ifft(const creal_T x[64], creal_T y[64]);

// Function Definitions

//
// Arguments    : const double x[64]
//                double y[64]
// Return Type  : void
//
static void b_abs(const double x[64], double y[64])
{
  int k;
  for (k = 0; k < 64; k++) {
    y[k] = std::abs(x[k]);
  }
}

//
// Arguments    : const creal_T x[64]
//                creal_T y[64]
// Return Type  : void
//
static void ifft(const creal_T x[64], creal_T y[64])
{
  int ix;
  int ju;
  int iy;
  int i;
  creal_T b_y1[64];
  boolean_T tst;
  double temp_re;
  double temp_im;
  int iheight;
  int istart;
  int j;
  double twid_re;
  static const double dv2[33] = { 1.0, 0.99518472667219693, 0.98078528040323043,
    0.95694033573220882, 0.92387953251128674, 0.881921264348355,
    0.83146961230254524, 0.773010453362737, 0.70710678118654757,
    0.63439328416364549, 0.55557023301960218, 0.47139673682599764,
    0.38268343236508978, 0.29028467725446233, 0.19509032201612825,
    0.0980171403295606, 0.0, -0.0980171403295606, -0.19509032201612825,
    -0.29028467725446233, -0.38268343236508978, -0.47139673682599764,
    -0.55557023301960218, -0.63439328416364549, -0.70710678118654757,
    -0.773010453362737, -0.83146961230254524, -0.881921264348355,
    -0.92387953251128674, -0.95694033573220882, -0.98078528040323043,
    -0.99518472667219693, -1.0 };

  double twid_im;
  static const double dv3[33] = { 0.0, 0.0980171403295606, 0.19509032201612825,
    0.29028467725446233, 0.38268343236508978, 0.47139673682599764,
    0.55557023301960218, 0.63439328416364549, 0.70710678118654757,
    0.773010453362737, 0.83146961230254524, 0.881921264348355,
    0.92387953251128674, 0.95694033573220882, 0.98078528040323043,
    0.99518472667219693, 1.0, 0.99518472667219693, 0.98078528040323043,
    0.95694033573220882, 0.92387953251128674, 0.881921264348355,
    0.83146961230254524, 0.773010453362737, 0.70710678118654757,
    0.63439328416364549, 0.55557023301960218, 0.47139673682599764,
    0.38268343236508978, 0.29028467725446233, 0.19509032201612825,
    0.0980171403295606, 0.0 };

  int ihi;
  ix = 0;
  ju = 0;
  iy = 0;
  for (i = 0; i < 63; i++) {
    b_y1[iy] = x[ix];
    iy = 64;
    tst = true;
    while (tst) {
      iy >>= 1;
      ju ^= iy;
      tst = ((ju & iy) == 0);
    }

    iy = ju;
    ix++;
  }

  b_y1[iy] = x[ix];
  for (i = 0; i <= 63; i += 2) {
    temp_re = b_y1[i + 1].re;
    temp_im = b_y1[i + 1].im;
    b_y1[i + 1].re = b_y1[i].re - b_y1[i + 1].re;
    b_y1[i + 1].im = b_y1[i].im - b_y1[i + 1].im;
    b_y1[i].re += temp_re;
    b_y1[i].im += temp_im;
  }

  iy = 2;
  ix = 4;
  ju = 16;
  iheight = 61;
  while (ju > 0) {
    for (i = 0; i < iheight; i += ix) {
      temp_re = b_y1[i + iy].re;
      temp_im = b_y1[i + iy].im;
      b_y1[i + iy].re = b_y1[i].re - temp_re;
      b_y1[i + iy].im = b_y1[i].im - temp_im;
      b_y1[i].re += temp_re;
      b_y1[i].im += temp_im;
    }

    istart = 1;
    for (j = ju; j < 32; j += ju) {
      twid_re = dv2[j];
      twid_im = dv3[j];
      i = istart;
      ihi = istart + iheight;
      while (i < ihi) {
        temp_re = twid_re * b_y1[i + iy].re - twid_im * b_y1[i + iy].im;
        temp_im = twid_re * b_y1[i + iy].im + twid_im * b_y1[i + iy].re;
        b_y1[i + iy].re = b_y1[i].re - temp_re;
        b_y1[i + iy].im = b_y1[i].im - temp_im;
        b_y1[i].re += temp_re;
        b_y1[i].im += temp_im;
        i += ix;
      }

      istart++;
    }

    ju /= 2;
    iy = ix;
    ix += ix;
    iheight -= iy;
  }

  for (iy = 0; iy < 64; iy++) {
    b_y1[iy].re *= 0.015625;
    b_y1[iy].im *= 0.015625;
    y[iy] = b_y1[iy];
  }
}

//
// Arguments    : const double inC[880]
//                const double inS[880]
//                double RE[7040]
// Return Type  : void
//
void ADist(const double inC[880], const double inS[880], double RE[7040])
{
  creal_T Complex[7040];
  int j;
  int i0;
  creal_T b_Complex[64];
  creal_T dcv0[64];
  double dv0[64];
  double dv1[64];
  memset(&Complex[0], 0, 7040U * sizeof(creal_T));
  for (j = 0; j < 8; j++) {
    for (i0 = 0; i0 < 110; i0++) {
      Complex[i0 + 110 * j].re = inC[i0 + 110 * j] + inS[i0 + 110 * j] * 0.0;
      Complex[i0 + 110 * j].im = inS[i0 + 110 * j];
    }
  }

  for (j = 0; j < 56; j++) {
    memset(&Complex[j * 110 + 880], 0, 110U * sizeof(creal_T));
  }

  for (j = 0; j < 110; j++) {
    for (i0 = 0; i0 < 64; i0++) {
      b_Complex[i0] = Complex[j + 110 * i0];
    }

    ifft(b_Complex, dcv0);    //dcv0  length = 64
    for (i0 = 0; i0 < 64; i0++) {
      dv0[i0] = dcv0[i0].re;
    }

    b_abs(dv0, dv1);
    for (i0 = 0; i0 < 64; i0++) {
      RE[j + 110 * i0] = dv1[i0];
    }
  }
}

//
// Arguments    : void
// Return Type  : void
//
void ADist_initialize()
{
  rt_InitInfAndNaN(8U);
}

//
// Arguments    : void
// Return Type  : void
//
void ADist_terminate()
{
  // (no terminate code required)
}

//
// File trailer for ADist.cpp
//
// [EOF]
//
