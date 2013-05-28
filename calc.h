/*=================================================================*/
/*=   calc.h                                                      =*/
/*=   header file for calculation routines for treekin            =*/
/*=   ---------------------------------------------------------   =*/
/*=   Last changed Time-stamp: <2006-11-27 13:08:56 mtw>          =*/
/*=   $Id: calc.h,v 1.16 2006/11/27 13:50:08 mtw Exp $            =*/
/*=   ---------------------------------------------------------   =*/
/*=     (c) Michael Thomas Wolfinger, W. Andreas Svrcek-Seiler    =*/
/*=                  {mtw,svrci}@tbi.univie.ac.at                 =*/
/*=                             treekin                           =*/
/*=================================================================*/


#ifndef _CALC_H_
#define _CALC_H_
#include "barparser.h"
#include "globals.h"

void    MxInit (int d);
void    MxGetSpace(double **p8);
double *MxBar2Matrix (BarData *Data, double *);
void    MxEqDistr (BarData *Data, double **p8);
void    MxEqDistrFULL (SubInfo *E, double *p8);
void    MxDiagonalize (double *U, double **_S, double *PI);
void    MxRecover(double **_S, double *P8);
void    MxStartVec (double **p0) ;
void    MxIterate (double *p0, double *p8, double *S);
void    MxMemoryCleanUp (void);
void    MxExponent(double *p0, double *p8, double *U);

void    MxFPT(double *U, double *p8, FILE *out);
void    MxEqDistrFromLinSys(double *U, double **p8);
void    MxEqDistrFromLocalBalance(double *U, double **p8);
void    MxFPTSimple(double *U);
double *MxFPTOneState(double *U, int state);

// matrix shortening routine (when nstates specified)
void MxRShorten(double *tmp_rates, double **shortened, int my_dim, int dim);

// not used! (just for past testing)
double  MxFPTRandom(double *P, double *U, int src, int dst, int packets);
void    MxFPTRnd(double *U, int packets);

void    PrintDummy(double *line);

#endif

/* End of file */
