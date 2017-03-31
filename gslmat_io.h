#if !defined(GSL2MXARRHDR)
#define GSL2MXARRHDR

#include <gsl/gsl_vector.h>
#include <gsl/gsl_matrix.h>
#include "matrix.h"
#include "mat.h"
#include <stdio.h>

//Author: Soumya D. Mohanty

//load mxArray into GSL vector
gsl_vector * mxarray2gslvector(mxArray *);
//load mxArray into GSL matrix
gsl_matrix * mxarray2gslmatrix(mxArray *);
//load gsl_matrix onto suitably sized mxArray
mxArray * gslmatrix2mxarray(const gsl_matrix *);
//load gsl_vector onto suitably sized mxArray (row vector)
mxArray * gslvector2mxarray(const gsl_vector *);
//Write out gsl_vector as a variable in a .mat file
void gslvector2matfile(MATFile *, char *, const gsl_vector *);
//Write out gsl_matrix as a variable in a .mat file
void gslmatrix2matfile(MATFile *, char *, const gsl_matrix *);
//Read data from mat file into gsl_vector
gsl_vector * matfile2gslvector(MATFile *, char *);
//Read data from mat file into gsl_matrix
gsl_matrix * matfile2gslmatrix(MATFile *, char *);
//Read data from mat file into scalar
double matfile2dscalar(MATFile *, char *);
//Double scalar to matfile
void dscalar2matfile(MATFile *, char *, double);
#endif