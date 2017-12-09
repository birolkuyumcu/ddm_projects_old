#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "SamFL.h"

#define LEFT  0
#define CENTER 1
#define RIGHT  2

#define BIGLEFT  0
#define ALEFT  1
#define ACENTER 2
#define ARIGHT  3
#define BIGRIGHT  4

double DeltaPNow[3];
double DeltaPNext[3];
double Angle[5];
double angle_maxima[] = { -30.0 , -25.0 , 0.0 , 25.0 , 30.0 };
int widths[] = { 80, 80, 100, 100};               // widths for each column
