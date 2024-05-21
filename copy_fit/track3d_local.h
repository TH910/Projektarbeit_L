/* system_art: Punkt-basierte Rechen-Routinen (lokal); 
 * Gemeinsamer Code fuer Linux- und NT-Systeme
 *
 * Versionen:
 * v0.6.9 (9.5.03, KA): neu; Transformationsmatrix optimieren
 *
 */

#ifndef _ART_SYSTEM_ART_TRACK3D_LOCAL_H
#define _ART_SYSTEM_ART_TRACK3D_LOCAL_H

#include "track3d.h"

// ------------------------------------------------------------------------------
// Anwendung von Trafos (trafo3d.c)

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
                     double ci[TRACK3D_MAXMARKER][3], int nc);


// ------------------------------------------------------------------------------
// Bestimmung von Transformationsmatrizen (trafo3d.c)

//! Grobe Transformationsmatrix bestimmen aus drei Punktpaaren.
/*!
 * Berechnet Trafo trf fuer die Beziehung: c1 = trf * c2
 *   - 3D-Punkte muessen sortiert vorliegen, mit gleicher Punktzahl.
 *
 * \param  trf (o): affine Trafo (4x4)
 * \param  c1 (i): drei Punkte
 * \param  c2 (i): drei Punkte
 * \return Rueckgabe (o): 0 ok, Fehler sonst
 */

int trafo3d_3trafo(double trf[4][4], double c1[3][3], double c2[3][3]);


//! Transformationsmatrix optimieren, aus mindestens drei Punktpaaren.
/*!
 * Berechnet Trafo trf fuer die Beziehung: c1 = trf * c2
 *   - 3D-Punkte muessen sortiert vorliegen, mit gleicher Punktzahl.
 *
 * \param  trf (io): affine Trafo (4x4); (i) grober Startwert, (o) optimiertes Ergebnis
 * \param  c1 (i): Punkte
 * \param  c2 (i): Punkte
 * \param  nc (i): Anzahl Punkte
 * \param  res (o): Residual der optimierten Trafo (Wurzel des mittleren Abstandquadrats)
 * \return Rueckgabe (o): 0 ok, Fehler sonst
 */

int trafo3d_opttrafo(double trf[4][4], double c1[TRACK3D_TARGET_MAXMARKER][3],
                     double c2[TRACK3D_TARGET_MAXMARKER][3], int nc, double * residual);


#endif // _ART_SYSTEM_ART_TRACK3D_LOCAL_H

