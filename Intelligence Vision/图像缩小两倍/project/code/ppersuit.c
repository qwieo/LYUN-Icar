#include "zf_common_headfile.h"
#include "Image_process.h"
#define PREANCHOR0 40 //27 //
#define PREANCHOR1 40//27 //
extern float rptss0[POINTS_MAX_LEN][2];
extern float rptss1[POINTS_MAX_LEN][2];

float * aim0=rptss0[PREANCHOR0];
float * aim1=rptss1[PREANCHOR1];

float calculator(float * aim)
{
	float ld=sqrt((aim[0]-57)*(aim[0]-57)+aim[1]*aim[1]);
	float sina=(aim[0]-57)/ld;
	float delta=atan(0.4*sina/(ld/100));
	return delta;
}
