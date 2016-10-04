/* sf45r.f -- translated by f2c (version 20000817).
   You must link the resulting object file with the libraries:
        -lf2c -lm   (in that order)
*/

// Fortran function for Fresnel integral calculation
// from MSU library. Translated to C by t2c.
// For conveniance I made a wrapper.

#include "math.h"
#include <complex>
#include "f2c.h"

/* Subroutine */ int sf45r_c(real *x, real *c__, real *s)
{
    /* Initialized data */

    static real a[52] = { 1e-11f,-3.66e-10f,1.0898e-8f,-2.67681e-7f,
            5.27608e-6f,-8.105684e-5f,9.339901e-4f,-.007651297f,.0411409f,
            -.1271339f,.1743607f,-.0808111f,.5479103f,4e-12f,-1.28e-10f,
            4.206e-9f,-1.1507e-7f,2.562196e-6f,-4.532192e-5f,6.174202e-4f,
            -.006220184f,.0438681f,-.2007174f,.5386666f,-.7996168f,1.053859f,
            1e-12f,-4e-12f,1.4e-11f,-5.4e-11f,2.39e-10f,-1.176e-9f,6.545e-9f,
            -4.2829e-8f,3.47441e-7f,-3.810219e-6f,6.627508e-5f,-.002617529f,
            .9945488f,2e-12f,-6e-12f,1.8e-11f,-7.2e-11f,2.98e-10f,-1.346e-9f,
            6.798e-9f,-3.9518e-8f,2.75996e-7f,-2.475448e-6f,3.202967e-5f,
            -7.552029e-4f,.0608819f };
    static real sys035 = .3989422f;

    /* Builtin functions */
    double sqrt(doublereal), sin(doublereal), cos(doublereal);

    /* Local variables */
    static real b, d__, e, f, h__;
    static integer i__, k, l;
    static real r__, t, y, z__, rk[13], rl[13];

    z__ = abs(*x);
    if (z__ - 8.f >= 0.f) {
        goto L2;
    } else {
        goto L1;
    }
L1:
    h__ = z__ / 8.f;
    k = 0;
    goto L3;
L2:
    h__ = 8.f / z__;
    k = 26;
L3:
    l = k + 13;
    y = h__ * 4.f * h__ - 2.f;
    rk[0] = a[k];
    rk[1] = y * rk[0] + a[k + 1];
    rl[0] = a[l];
    rl[1] = y * rl[0] + a[l + 1];
    for (i__ = 3; i__ <= 13; ++i__) {
        rk[i__ - 1] = y * rk[i__ - 2] - rk[i__ - 3] + a[i__ + k - 1];
        rl[i__ - 1] = y * rl[i__ - 2] - rl[i__ - 3] + a[i__ + l - 1];
/* L4: */
    }
    f = sys035;
    d__ = f * rk[12];
    e = f * rl[12] * h__;
    b = (real)sqrt(z__);
    if (z__ - 8.f >= 0.f) {
        goto L6;
    } else {
        goto L5;
    }
L5:
    *c__ = d__ * b;
    *s = e * b;
    goto L7;
L6:
    r__ = (real)sin(z__);
    t = (real)cos(z__);
    *c__ = (d__ * r__ - e * t) / b + .5f;
    *s = .5f - (e * r__ + d__ * t) / b;
L7:
    return 0;
} /* sf45r_c */




std::complex<double> fresnel (double x)
{
// A wrapper function for Fresnel integral.

    float c,s,sqrx;

    sqrx = x*x;
    sf45r_c (&sqrx, &s, &c);

    std::complex<double> integral = std::complex<double>(s,c) * sqrt(M_PI/2);

    if (x<0)                  //   it's the strange behavior of sf45r.
        integral = -integral;         //   it makes f(x)=f(-x) though it must be f(-x)=-f(x)

    return integral;
}

