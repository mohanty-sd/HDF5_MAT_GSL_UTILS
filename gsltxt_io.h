#if !defined(GSL2TXTFILE)
#define GSL2TXTFILE

#include <gsl/gsl_vector.h>
#include <gsl/gsl_matrix.h>
#include <stdio.h>

//Soumya D. Mohanty, 2016

//Write out a gsl_vector into a file
void gslvector2file(FILE *, const gsl_vector *, char *);
//Write out a gsl_matrix into a file
void gslmatrix2file(FILE *, const gsl_matrix *, char *);

#endif
