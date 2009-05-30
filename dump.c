
#include "decs.h"

void dump(FILE *fp)
{
	int i,j,k,l ;
	double divb,b2_calc(double *pr) ;
	void primtoU(double *pr, double *U) ;
	double vrchar(double *pr) ;
	double vhchar(double *pr) ;
	double U[NPR] ;

	fprintf(fp,"%d %d %10.5g %10.5g %10.5g\n",NR,NH,Rin,Rout,t) ;

	/*
	ZSLOOP(-2,NR+1,-2,NR+1) {
	*/
	ZSLOOP(0,NR-1,0,NR-1) {

		fprintf(fp,"%15.7g %15.7g",Rin + (i + 0.5)*dr,(j+0.5)*dh) ;
		PLOOP fprintf(fp,"%15.7g ",p[i][j][k]) ;

                /* flux-ct defn; corner-centered.  Use
		   only interior corners */
		if(i > 0 && j > 0 && i < NR && j < NH) {
			divb = fabs( 0.5*(
				p[i][j][BR]*gdet[i][j][CENT]
				+ p[i][j-1][BR]*gdet[i][j-1][CENT]
				- p[i-1][j][BR]*gdet[i-1][j][CENT]
				- p[i-1][j-1][BR]*gdet[i-1][j-1][CENT]
				)/dr +
				0.5*(
				p[i][j][BH]*gdet[i][j][CENT]
				+ p[i-1][j][BH]*gdet[i-1][j][CENT]
				- p[i][j-1][BH]*gdet[i][j-1][CENT]
				- p[i-1][j-1][BH]*gdet[i-1][j-1][CENT]
				)/dh) ;
		}
		else divb = 0. ;

		fprintf(fp,"%15.7g ",divb) ;

		fprintf(fp,"%15.7g ",b2_calc(p[i][j])) ;

		primtoU(p[i][j],U) ;
		PLOOP fprintf(fp,"%15.7g ", U[k]) ;

		/*
		GSET(i,j,CENT)
		fprintf(fp,"%15.7g %15.7g ",vrchar(p[i][j]),vhchar(p[i][j])) ;

		for(k=0;k<NDIM;k++)
		for(l=0;l<NDIM;l++) fprintf(fp,"%15.7g ",Tetr_con[k][l]) ;
		*/
                
		fprintf(fp,"\n") ;
	}
}
