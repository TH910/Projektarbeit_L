/* track3d (system_art): Trafos zwischen 2 Sets von 3D-Daten; 
 * Gemeinsamer Code fuer Linux- und NT-Systeme
 *
 * Versionen:
 * v0.6.7 (30.11.02, KA): aus trafo3d.c (fit3ddata v0.2.0)
 *   p9 (9.5.03, KA): Trafo aus mehr als 3 Punktpaaren (aus fit3ddata v0.2.0)
 *
 * TODO:
 *   - Trafo aus 3 Punkten immer auch mit Fit-Rechnung?
 *   - Berechnung Jacobi-Matrix optimierbar (Elementardrehungen nur einmal rechnen)
 */
/*! \file
 * Routinen zur Berechnung von affinen Trafos zwischen zwei Saetzen von 3D-Punkten.
 *   - 3D-Punkte muessen sortiert vorliegen, mit gleicher Punktzahl.
 */

//#define DEBUG

//#include "stdafx.h"

#include <stdio.h>
#include <math.h>

#include "log.h"

#include "track3d.h"
#include "track3d_local.h"
#include "linear_lsq.h"


// Parameter der nicht-linearen Ausgleichsrechnung: Bestimmung der Jacobi-Matrix

#define CT_CHANGEROTMAT 0.01       // Einheit Aenderung Rotation (Winkel in rad)
#define CT_CHANGETRANS  0.5        // Einheit Aenderung Translation (in mm)

// Parameter der nicht-linearen Ausgleichsrechnung: Steuerung Iterationen

#define CFT_MAX_ITERATIONS   20    // max. Zahl Iterationen fuer nichtlinearen Fit
#define CFT_CHANGE_RESIDUAL  0.001 // max. Aenderung Residual fuer Iterationsabbruch
#define CFT_MAX_LSQAPPLIC    20    // max. Zahl Iterationen fuer Anwendung des LSQ-Ergebnisses


static int change_trafo(double trfout[4][4], double trfin[4][4], double s[7]);
static double calc_residual(double c1[TRACK3D_TARGET_MAXMARKER][3],
                            double c2[TRACK3D_TARGET_MAXMARKER][3], int nc);

static void copy_trafo(double trfto[4][4], double trffrom[4][4]);
static inline double vecnorm(double x, double y, double z);


// ------------------------------------------------------------------------------
// Anwendung von Trafo

//! Punkte transformieren mit 4x4-Trafo.
/*!
 * Berechnet Trafo trf fuer die Beziehung: co = trf * ci
 *
 * \param  co (o): Punkte (Ausgabe)
 * \param  trf (i): affine Trafo (4x4)
 * \param  ci (i): Punkte (Eingabe)
 * \param  nc (i): Anzahl Punkte
 * \return Rueckgabe (o): 0 ok, Fehler sonst
 */

void trafo3d_perform(double co[TRACK3D_MAXMARKER][3], double trf[4][4],
                     double ci[TRACK3D_MAXMARKER][3], int nc)
{
	int i, j, k;
	double s;

	for(i=0; i<nc; i++){
		for(j=0; j<3; j++){
			s = 0;
			for(k=0; k<3; k++){
				s += trf[j][k] * ci[i][k];
			}
			co[i][j] = s + trf[j][3];
		}
	}
}


// ------------------------------------------------------------------------------
// Bestimmung von Transformationsmatrizen

//! Transformationsmatrix bestimmen aus drei Punktpaaren.
/*!
 * Berechnet Trafo trf fuer die Beziehung: c1 = trf * c2
 *   - 3D-Punkte muessen sortiert vorliegen, mit gleicher Punktzahl.
 *
 * \param  trf (o): affine Trafo (4x4)
 * \param  c1 (i): drei Punkte
 * \param  c2 (i): drei Punkte
 * \return Rueckgabe (o): 0 ok, Fehler sonst
 */
/* - Trafo in zwei Schritten ueber ein zwischengeschaltetes Koordinatensystem:
 *   Nullpunkt in Punkt 1, Punkt 2 definiert x-Achse, Punkt 3 die x-y-Ebene
 * - Vorgehen:
 *   1. Trafo von Zwischen-KS (t) in die beiden Ausgangskoordinatensysteme
 *      berechnen: x1 = R1 * xt + t1, x2 = R2 * xt + t2
 *   2. daraus Trafo von KS2 nach KS1:
 *      x1 = R1 * (R2^T * (x2 - t2)) + t1  ->  R = R1 * R2^T, t = t1 - R * t2
 */

int trafo3d_3trafo(double trf[4][4], double c1[3][3], double c2[3][3])
{
	int i, j, k;
	double z1[2][3], z2[2][3];
	double rot1[3][3], rot2[3][3];
	double d1, d2;

	// Punkt 1 = Nullpunkt, Reduzieren auf zwei Punkte jeweils:

	for(k=0; k<2; k++){
		for(i=0; i<3; i++){
			z1[k][i] = c1[k+1][i] - c1[0][i];
			z2[k][i] = c2[k+1][i] - c2[0][i];
		}
	}

	// x-Basisvektoren fuer vermittelnde Trafos: Nullpunkt - Punkt 2

	d1 = vecnorm(z1[0][0], z1[0][1], z1[0][2]);
	d2 = vecnorm(z2[0][0], z2[0][1], z2[0][2]);
	
	if(d1 == 0 || d2 == 0){
		return -1;
	}
	
	for(j=0; j<3; j++){
		rot1[j][0] = z1[0][j] / d1;
		rot2[j][0] = z2[0][j] / d2;
	}

	#ifdef DEBUG
		log_printf("- trafo3d 3t: x1 %f %f %f\n", rot1[0][0], rot1[1][0], rot1[2][0]);
		log_printf("- trafo3d 3t: x2 %f %f %f\n", rot2[0][0], rot2[1][0], rot2[2][0]);
	#endif

	// z-Basisvektoren fuer vermittelnde Trafos: Senkrechte auf x - (Nullpunkt - Punkt 3)

	rot1[0][2] = z1[0][1] * z1[1][2] - z1[0][2] * z1[1][1];
	rot1[1][2] = z1[0][2] * z1[1][0] - z1[0][0] * z1[1][2];
	rot1[2][2] = z1[0][0] * z1[1][1] - z1[0][1] * z1[1][0];
	
	d1 = vecnorm(rot1[0][2], rot1[1][2], rot1[2][2]);
	
	rot2[0][2] = z2[0][1] * z2[1][2] - z2[0][2] * z2[1][1];
	rot2[1][2] = z2[0][2] * z2[1][0] - z2[0][0] * z2[1][2];
	rot2[2][2] = z2[0][0] * z2[1][1] - z2[0][1] * z2[1][0];
	
	d2 = vecnorm(rot2[0][2], rot2[1][2], rot2[2][2]);
	
	if(d1 == 0 || d2 == 0){
		return -1;
	}
	
	for(j=0; j<3; j++){
		rot1[j][2] /= d1;
		rot2[j][2] /= d2;
	}
	
	#ifdef DEBUG
		log_printf("- trafo3d 3t: z1 %f %f %f\n", rot1[0][2], rot1[1][2], rot1[2][2]);
		log_printf("- trafo3d 3t: z2 %f %f %f\n", rot2[0][2], rot2[1][2], rot2[2][2]);
	#endif

	// y-Basisvektoren fuer vermittelnde Trafos: Senkrechte auf x - z

	rot1[0][1] = rot1[1][2] * rot1[2][0] - rot1[2][2] * rot1[1][0];
	rot1[1][1] = rot1[2][2] * rot1[0][0] - rot1[0][2] * rot1[2][0];
	rot1[2][1] = rot1[0][2] * rot1[1][0] - rot1[1][2] * rot1[0][0];
	
	d1 = vecnorm(rot1[0][1], rot1[1][1], rot1[2][1]);
	
	rot2[0][1] = rot2[1][2] * rot2[2][0] - rot2[2][2] * rot2[1][0];
	rot2[1][1] = rot2[2][2] * rot2[0][0] - rot2[0][2] * rot2[2][0];
	rot2[2][1] = rot2[0][2] * rot2[1][0] - rot2[1][2] * rot2[0][0];
	
	d2 = vecnorm(rot2[0][1], rot2[1][1], rot2[2][1]);
	
	if(d1 == 0 || d2 == 0){
		return -1;
	}
	
	for(j=0; j<3; j++){
		rot1[j][1] /= d1;
		rot2[j][1] /= d2;
	}

	#ifdef DEBUG
		log_printf("- trafo3d 3t: y1 %f %f %f\n", rot1[0][1], rot1[1][1], rot1[2][1]);
		log_printf("- trafo3d 3t: y2 %f %f %f\n", rot2[0][1], rot2[1][1], rot2[2][1]);
	#endif

	// Affine Trafo: Rotation

	for(i=0; i<3; i++){
		for(j=0; j<3; j++){
			d1 = 0;
			for(k=0; k<3; k++){
				d1 += rot1[i][k] * rot2[j][k];
			}
			trf[i][j] = d1;
		}
	}

	// Affine Trafo: Translation

	for(j=0; j<3; j++){
		trf[3][j] = 0;
		d1 = 0;
		for(k=0; k<3; k++){
			d1 += trf[j][k] * c2[0][k];
		}
		trf[j][3] = c1[0][j] - d1;
	}
	trf[3][3] = 1;

	return 0;
}


//! Transformationsmatrix optimieren, aus mindestens drei Punktpaaren.
/*!
 * Berechnet Trafo trf fuer die Beziehung: c1 = trf * c2
 *
 * \param  trf (io): affine Trafo (4x4); (i) grober Startwert, (o) optimiertes Ergebnis
 * \param  c1 (i): Punkte
 * \param  c2 (i): Punkte
 * \param  nc (i): Anzahl Punkte
 * \param  res (o): Residual der optimierten Trafo (Wurzel des mittleren Abstandquadrats)
 * \return Rueckgabe (o): 0 ok, Fehler sonst
 */
/*
 * - Nichtlineare Ausgleichsrechnung der affinen Trafo; 6 Freiheitsgrade:
 *   3 Translationen, 3 Rotationen um die Achsen
 * - Grobe Trafo als Startwert muss vorhanden sein
 * - Vorgehen: Iteration
 *     a. Berechnung aktuelles Rest-Residuum r
 *     b. Berechnung aktuelle Jacobi-Matrix J
 *     c. Bestimmung Korrektur s durch J * s = r (lineare Ausgleichsrechnung)
 *     d. Anwendung Korrektur, Ergebnis-Test
 */

int trafo3d_opttrafo(double trf[4][4], double c1[TRACK3D_TARGET_MAXMARKER][3],
                     double c2[TRACK3D_TARGET_MAXMARKER][3], int nc, double* residual)
{
	int i, k, err;
	int iter, idof, appiter;
	double akttrfc2[TRACK3D_TARGET_MAXMARKER][3], tmpc2[TRACK3D_TARGET_MAXMARKER][3];
	double akttrf[4][4], tmptrf[4][4];
	double res, res1;
	double lsqs[6];
	double lsqr[TRACK3D_TARGET_MAXMARKER * 3];
	double lsqm[TRACK3D_TARGET_MAXMARKER * 3 * 6];
	
   // Startwerte besetzen/berechnen:
	
	copy_trafo(akttrf, trf);

	trafo3d_perform(akttrfc2, akttrf, c2, nc);
	res = calc_residual(c1, akttrfc2, nc);

	// Iteration NLA:

	iter = 1;
	
	while(1){

		// Residuums-Vektor fuer NLA bestimmen:

		for(i=0; i<nc; i++){
			for(k=0; k<3; k++){
				lsqr[i*3 + k] = c1[i][k] - akttrfc2[i][k];  // Momentaner Residuum-Vektor
			}                                   // akttrfc2 enthaelt noch c2, transformiert mit akttrf
		}

		// Jacobi-Matrix fuer NLA bestimmen:

		for(idof=0; idof<6; idof++){
			for(i=0; i<6; i++){
				lsqs[i] = 0;
			}
			lsqs[idof] = 1;
	
			change_trafo(tmptrf, akttrf, lsqs);       // Trafo mit kleiner Aenderung
			trafo3d_perform(tmpc2, tmptrf, c2, nc);
	
			for(i=0; i<nc; i++){
				for(k=0; k<3; k++){
					lsqm[(i*3 + k) * 6 + idof] = tmpc2[i][k] - akttrfc2[i][k];
				}
			}
		}

		// LSQ rechnen:
		
		for(i=0; i<6; i++){
			lsqs[i] = 0;
		}

		if((err = linear_lsq_solve(lsqs, lsqr, lsqm, nc * 3, 6, &res1))){
			#ifdef DEBUG
				log_printf("- trafo3d ot: solver error %d\n", err);
			#endif
			
			return -1;
		}

		#ifdef DEBUG
			log_printf("- trafo3d ot: lsq solver %g %g %g %g %g %g res %g\n", 
				lsqs[0], lsqs[1], lsqs[2], lsqs[3], lsqs[4], lsqs[5], res1);
		#endif

		// Ergebnis anwenden (in Iteration):

		appiter = 1;

		while(1){
			change_trafo(tmptrf, akttrf, lsqs);     // Gefundene Veraenderungen anwenden
			trafo3d_perform(akttrfc2, tmptrf, c2, nc);
			res1 = calc_residual(c1, akttrfc2, nc);     // Residual daraus rechnen
			
			if(res1 < res || fabs(res - res1) < CFT_CHANGE_RESIDUAL){
				break;                               // Abbruch, falls Iteration mit Effekt
			}
			
			for(i=0; i<6; i++){                     // sonst Veraenderungen halbieren
				lsqs[i] /= 2;
			}
			
			if(appiter >= CFT_MAX_LSQAPPLIC){       // Abbruchkriterium Iterationszahl
				#ifdef DEBUG
					log_printf("- trafo3d ot: error application lsq, res %g %g\n", res1, res);
				#endif
				
				return -2;
			}
			
			appiter++;
		}

		// Nach Abbruch enthalten tmptrf, akttrfc2, res1 die aktuellen Werte fuer die
		// Trafo, die transformierten Punkte c2 und das Residual.

		#ifdef DEBUG
			log_printf("- trafo3d ot: iter %d res %g appiter %d dres %g\n",
			           iter, res1, appiter, res - res1);
		#endif
		
		// Ergebnis testen, Iteration evtl. abbrechen:

		if(fabs(res - res1) < CFT_CHANGE_RESIDUAL){
			copy_trafo(trf, tmptrf);
			*residual = res1;
			
			return 0;
		}

		if(iter >= CFT_MAX_ITERATIONS){
			#ifdef DEBUG
				log_printf("- trafo3d ot: iteration error, res %g %g\n", res1, res);
			#endif
				
			return -3;
		}

		iter ++;
		
		copy_trafo(akttrf, tmptrf);
		res = res1;
	}
}


// ------------------------------------------------------------------------------
// ------------------------------------------------------------------------------
// Hilfsroutinen fuer Optimierung der Trafo:

//! Trafo veraendern (fuer Jacobi-Matrix und Anwendung der Korrektur).
/*!
 * \param  trfout (o): errechnete Trafo
 * \param  trfin (i): Ausgangs-Trafo
 * \param  s (i): Faktoren Aenderung (0..2 Winkel, 3..5 Ort) in def. Einheiten
 * \return Rueckgabe (o): 0 ok, Fehler sonst
 */
 
static int change_trafo(double trfout[4][4], double trfin[4][4], double s[6])
{
	int i, j, k;
	double srx, crx;
	double sry, cry;
	double srz, crz;
	double tmprot[3][3];
	double d;

	// Translation:

	for(i=0; i<3; i++){
		trfout[i][3] = trfin[i][3] + s[i + 3] * CT_CHANGETRANS;
	}

	for(i=0; i<4; i++){
		trfout[3][i] = trfin[3][i];
	}

	// Rotation:
	//   - Achtung: Weglassen des sin() aendert nur Betrag einer Elementar-Drehung!

	srx = s[0] * CT_CHANGEROTMAT;  // Annaeherung Rotation um x
	crx = sqrt(1.0 - srx * srx);
	
	sry = s[1] * CT_CHANGEROTMAT;  // Annaeherung Rotation um y
	cry = sqrt(1.0 - sry * sry);
	
	srz = s[2] * CT_CHANGEROTMAT;  // Annaeherung Rotation um z
	crz = sqrt(1.0 - srz * srz);

	tmprot[0][0] =   crz * cry;
	tmprot[1][0] =   srz * crx + crz * sry * srx;
	tmprot[2][0] =   srz * srx - crz * sry * crx;

	tmprot[0][1] = - srz * cry;
	tmprot[1][1] =   crz * crx - srz * sry * srx;
	tmprot[2][1] =   crz * srx + srz * sry * crx;

	tmprot[0][2] =   sry;
	tmprot[1][2] = - cry * srx;
	tmprot[2][2] =   cry * crx;

	for(i=0; i<3; i++){
		for(j=0; j<3; j++){
			d = 0;
			
			for(k=0; k<3; k++){
				d += tmprot[k][j] * trfin[i][k];
			}

			trfout[i][j] = d;
		}
	}

	// Nach-Normierung Rotationsmatrix: wohl nur notwendig bei sehr vielen Iterationen

	return 0;
}


//! Residual zwischen zwei Saetzen von 3D-Punkten rechnen.
/*!
 * \param  c1, c2 (i): Listen von Punkten
 * \param  nc (i): Anzahl Punkte
 * \return Rueckgabe (o): Residual (Wurzel des mittleren Abstandsquadrates)
 */

static double calc_residual(double c1[TRACK3D_TARGET_MAXMARKER][3],
                            double c2[TRACK3D_TARGET_MAXMARKER][3], int nc)
{
	int i, j;
	double res, s;

	res = 0;
	
	for(i=0; i<nc; i++){
		for(j=0; j<3; j++){
			s = c1[i][j] - c2[i][j];

			res += s * s;
		}
	}

	return sqrt(res / nc);
}


// ------------------------------------------------------------------------------
// ------------------------------------------------------------------------------
// Hilfsroutinen

//! Trafo kopieren.
/*!
 * \param  trfto (o): Kopie
 * \param  trffrom (i): Original
 */

static void copy_trafo(double trfto[4][4], double trffrom[4][4])
{
	int i, j;

	for(i=0; i<4; i++){
		for(j=0; j<4; j++){
			trfto[i][j] = trffrom[i][j];
		}
	}
}


//! Norm eines Vektors rechnen.
/*!
 * \param  x, y, z (i): Vektor-Koordinaten
 * \return Rueckgabe (o): Norm
 */

static inline double vecnorm(double x, double y, double z)
{

	return sqrt(x*x + y*y + z*z);
}


