#include "gsltxt_io.h"
#include <gsl/gsl_vector.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_math.h>
#include <stdio.h>
#include <stdbool.h>



//Write out a gsl_vector into a file
void gslvector2file(FILE *outFile, const gsl_vector *gslVec, char *formatString){
	size_t nSamples = gslVec->size;
	size_t lpc;
	for (lpc = 0; lpc < nSamples; lpc++){
		fprintf(outFile,formatString,gsl_vector_get(gslVec,lpc));
	}
	fprintf(outFile,"\n");
}

//Write out a gsl_matrix into a file
void gslmatrix2file(FILE *outFile, const gsl_matrix *gslMat, char *formatString){
	size_t nRows = gslMat->size1;
	size_t nCols = gslMat->size2;
	size_t lpc1, lpc2;
	for (lpc1 = 0; lpc1 < nRows; lpc1++){
		for(lpc2 = 0; lpc2 < nCols; lpc2++){
			fprintf(outFile,formatString, gsl_matrix_get(gslMat,lpc1,lpc2));
		}
		fprintf(outFile,"\n");
	}
	fprintf(outFile,"\n");
}

