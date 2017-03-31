#include "gslmat_io.h"
#include "matrix.h"
#include "mat.h"
#include <gsl/gsl_vector.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_math.h>
#include <stdio.h>
#include <stdbool.h>

//Author: Soumya D. Mohanty

//load mxArray into GSL vector
gsl_vector * mxarray2gslvector(mxArray *matVec){
	if(!mxIsDouble(matVec)){
		printf("Warning: input mxArray is not double array\n");
		return NULL;
	}
	size_t nRows = mxGetM(matVec);
	size_t nCols = mxGetN(matVec);
	if(nRows > 1 && nCols > 1){
		printf("Warning: not a row or column vector\n");
		return NULL;
	}
	double *matVecPr = mxGetPr(matVec);
	
	size_t nDim;
	if (nRows > nCols){
		nDim = nRows;
	}
	else{
		nDim = nCols;
	}
	gsl_vector *gslVec = gsl_vector_alloc(nDim);
	size_t lpc;
	for (lpc = 0; lpc < nDim; lpc++){
		gsl_vector_set(gslVec,lpc,matVecPr[lpc]);
	}
	
	return gslVec;
}

//load mxArray into GSL matrix
gsl_matrix * mxarray2gslmatrix(mxArray *matVec){
	if(!mxIsDouble(matVec)){
		printf("Warning: input mxArray is not double array\n");
		return NULL;
	}
	size_t nRows = mxGetM(matVec);
	size_t nCols = mxGetN(matVec);
	if(nRows == 1 || nCols == 1){
		printf("Warning: mxArray is a vector\n");
		//return NULL;
	}
	double *matVecPr = mxGetPr(matVec);
	
	gsl_matrix *gslMat = gsl_matrix_alloc(nRows,nCols);
	size_t lprow, lpcol;
	for (lpcol = 0; lpcol < nCols; lpcol++){
		for(lprow = 0; lprow < nRows; lprow++){
			gsl_matrix_set(gslMat,lprow,lpcol,matVecPr[lprow+lpcol*nRows]);
		}
	}
	
	return gslMat;
}

//load gsl_matrix onto suitably sized mxArray
mxArray * gslmatrix2mxarray(const gsl_matrix *gslMat){
	mxArray *matlabMatrix;
	if (gslMat == NULL){
		matlabMatrix = NULL;
	}
	else{
		size_t nRows = gslMat->size1;
		size_t nCols = gslMat->size2;
		size_t lprow, lpcol;
		matlabMatrix = mxCreateDoubleMatrix(nRows, nCols, mxREAL);
		double *matlabMatrixPr = mxGetPr(matlabMatrix);
		//mxArray have column first storage
		for(lprow = 0; lprow < nRows; lprow++){
			for(lpcol = 0; lpcol < nCols; lpcol++){
			matlabMatrixPr[lprow + lpcol*nRows] = gsl_matrix_get(gslMat,lprow,lpcol);
			}
		}
	}
	
	return matlabMatrix;
};


//load gsl_vector onto suitably sized mxArray (row vector)
mxArray * gslvector2mxarray(const gsl_vector *gslVec){
	
	mxArray *matlabVec;
	if (gslVec == NULL){
		matlabVec = NULL;
	}
	else{
		size_t nSamples = gslVec->size;
		size_t lpc;
	
		matlabVec = mxCreateDoubleMatrix(1, nSamples, mxREAL);
		double *matlabVecPr = mxGetPr(matlabVec);
		for(lpc = 0; lpc < nSamples; lpc++){
			matlabVecPr[lpc] = gsl_vector_get(gslVec,lpc);
		}
	}

	return matlabVec;
}
//Write out a gsl_vector into a mat file
void gslvector2matfile(MATFile *outFile, char *varName, const gsl_vector *gslVec){
	
	if (outFile == NULL || gslVec == NULL){
		return;
	}
	else{
		mxArray *matlabVar = gslvector2mxarray(gslVec);
		matPutVariable(outFile,varName,matlabVar);
		mxDestroyArray(matlabVar);
	}
}
//Write out a gsl_matrix into a mat file
void gslmatrix2matfile(MATFile *outFile, char *varName, const gsl_matrix *gslMat){
	
	if (outFile == NULL || gslMat == NULL){
		return;
	}
	else{
		mxArray *matlabVar = gslmatrix2mxarray(gslMat);
		matPutVariable(outFile,varName,matlabVar);
		mxDestroyArray(matlabVar);
	}
}

//Read data from mat file into gsl_vector
gsl_vector * matfile2gslvector(MATFile *inFile, char *varName){
	
	gsl_vector *gslVec;
	
	if (inFile == NULL){
		gslVec = NULL;
		return gslVec;
	}
	
	mxArray *var_mx = matGetVariable(inFile,varName);
	gslVec = mxarray2gslvector(var_mx);
	
	//Wrap up
	mxDestroyArray(var_mx);
	return gslVec;
}

//Read data from mat file into gsl_matrix
gsl_matrix * matfile2gslmatrix(MATFile *inFile, char *varName){
	
	gsl_matrix *gslMat;
	
	if (inFile == NULL){
		gslMat = NULL;
		return gslMat;
	}
	
	mxArray *var_mx = matGetVariable(inFile,varName);
	gslMat = mxarray2gslmatrix(var_mx);
	
	//Wrap up
	mxDestroyArray(var_mx);
	return gslMat;
}

//Read data from mat file into scalar
double matfile2dscalar(MATFile *inFile, char *varName){
	
	double data;
	
	if (inFile == NULL){
		return NAN;
	}
		
	mxArray *data_mx = matGetVariable(inFile,varName);
	if (data_mx == NULL){
		printf("matfile2dscalar: Error reading mat variable\n");
		return NAN;
	}
	
	data = mxGetScalar(data_mx);
	
	//Wrap up
	mxDestroyArray(data_mx);
	return data;
}

//Double scalar to matfile
void dscalar2matfile(MATFile *outFile, char *varName, double data){
	if (outFile == NULL){
		return;
	}
	else{
		mxArray *matlabVar = mxCreateDoubleScalar(data);
		matPutVariable(outFile,varName,matlabVar);
		mxDestroyArray(matlabVar);
	}
}

