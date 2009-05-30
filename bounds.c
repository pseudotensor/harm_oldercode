
#include "decs.h"

/* bound array containing entire set of primitive variables */

void bound_prim( double prim[][NH+4][NPR] )
{
	void bound_var( double var[][NH+4][NPR], int k, int r_in_bc, int r_out_bc,
		int th_in_bc, int th_out_bc) ;

	bound_var(prim, RHO, OUTFLOW, OUTFLOW, SYMM,  SYMM) ;
	bound_var(prim, UU,  OUTFLOW, OUTFLOW, SYMM,  SYMM) ;
 
	bound_var(prim, UR,  OUTFLOW, OUTFLOW, SYMM,  SYMM) ;
	bound_var(prim, UH,  OUTFLOW, OUTFLOW, ASYMM, ASYMM) ;
	bound_var(prim, UP,  OUTFLOW, OUTFLOW, SYMM,  SYMM) ;

	/* still unclear what BCs for B should be-- */
	bound_var(prim, BR,  OUTFLOW, OUTFLOW, SYMM,  SYMM) ;
	bound_var(prim, BH,  OUTFLOW, OUTFLOW, ASYMM, ASYMM) ;
	bound_var(prim, BP,  OUTFLOW, OUTFLOW, SYMM,  SYMM) ;
}

#define UNK_BC	{fprintf(stderr,"unknown BC\n") ; exit(1) ;}

/* bound individual primitive variable */

void bound_var( double var[][NH+4][NPR], int k, 
	int r_in_bc, int r_out_bc,
	int th_in_bc, int th_out_bc
	)
{
	int i,j ;

	/* inner r boundary condition */
	if(r_in_bc == OUTFLOW) {
		for(j=0;j<NH;j++) {
			if(k == UR && var[0][j][UR] > 0.) {
				var[-1][j][k] = 0. ;
				var[-2][j][k] = 0. ;
			}
			else {
				var[-1][j][k] = var[0][j][k] ;
				var[-2][j][k] = var[0][j][k] ;
			}
		}
	}
	else UNK_BC ;

	/* outer r BC */
	if(r_out_bc == OUTFLOW) {
		for(j=0;j<NH;j++) {
			if(k == UR && var[NR-1][j][UR] < 0.) {
				var[NR][j][k] = 0. ;
				var[NR+1][j][k] = 0. ;
			}
			else {
				var[NR][j][k] = var[NR-1][j][k] ;
				var[NR+1][j][k] = var[NR-1][j][k] ;
			}
		}
	}
	else UNK_BC ;

	/* north pole BC */
	if(th_in_bc == SYMM) {
		for(i=-2;i<=NR+1;i++) {
			var[i][-1][k] = var[i][0][k] ;
			var[i][-2][k] = var[i][1][k] ;
		}
	}
	else if(th_in_bc == ASYMM) {
		for(i=-2;i<=NR+1;i++) {
			var[i][-1][k] = -var[i][0][k] ;
			var[i][-2][k] = -var[i][1][k] ;
		}
	}
	else UNK_BC ;

	/* south pole BC */
	if(th_out_bc == SYMM) {
		for(i=-2;i<=NR+1;i++) {
			var[i][NH][k] = var[i][NH-1][k] ;
			var[i][NH+1][k] = var[i][NH-2][k] ;
		}
	}
	else if(th_out_bc == ASYMM) {
		for(i=-2;i<=NR+1;i++) {
			var[i][NH][k] = -var[i][NH-1][k] ;
			var[i][NH+1][k] = -var[i][NH-2][k] ;
		}
	}
	else UNK_BC ;

}

