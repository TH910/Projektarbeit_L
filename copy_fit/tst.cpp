/* Test Marker-Trafo-Routinen; 
 */

#include "stdafx.h"

#include <stdio.h>

#include "track3d_local.h"

static double points1[5][3] = 
{
	{ 32.386000, 69.939000, -57.133000 },
	{ 130.678000, -14.227000, 9.166000 },
	{ 15.720000, -90.239000, 80.873000 },
	{ -95.576000, -0.255000, 10.583000 },
	{ 4.689000, 12.854000, 33.470000 }
};

static double points2[5][3] = 
{
	{ 92.309000, 34.537000, -30.215000 },
	{ 92.181000, -76.373000, 64.079000 },
	{ -62.933000, -70.767000, 68.728000 },
	{ -67.499000, 50.858000, -34.326000 },
	{ 3.248000, 14.541000, 32.188000 }
};



int main(int argc, char** argv)
{
	int i;
	double trf[4][4], res;

	// Erst grobe Trafo aus drei beliebigen Punkten bestimmen:

	if(trafo3d_3trafo(trf, points1, points2)){
		printf("cannot trafo3d_3trafo\n");
		return -1;
	}

	// Dann Trafo mit allen Punkten optimieren:

	if(trafo3d_opttrafo(trf, points1, points2, 5, &res)){
		printf("cannot trafo3d_opttrafo\n");
		return -1;
	}

	// trf transformiert jetzt:  points1 = trf * points2

	for(i=0; i<4; i++){
		printf("trafo %d : %.3f %.3f %.3f  %.3f\n",
			i, trf[i][0], trf[i][1], trf[i][2], trf[i][3]);
	}
	printf("residual : %.3f\n", res);

	return 0;
}


