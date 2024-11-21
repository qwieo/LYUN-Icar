#ifndef __ImageProcess_H__
#define __ImageProcess_H__
#include "zf_common_headfile.h"
#define USER_SIZE_H    100
#define USER_SIZE_W    114
#define User_Image    ImageUsed
// ensure vist image safely and correctly
// AT==safe(img[x][y].
#define AT_IMAGE(img, x, y)          ((img)->data[(y)*(img)->step+(x)])
#define AT                  AT_IMAGE
#define AT_CLIP(img, x, y)  AT_IMAGE((img), clip((x), 0, (img)->width-1), clip((y), 0, (img)->height-1));

#define DEF_IMAGE(ptr, w, h)         {.data=ptr, .width=w, .height=h, .step=w}

#define POINTS_MAX_LEN 100
#define white 255
#define black 0
#define image_deal show0


typedef struct image {
    uint8_t *data;
    uint32_t width;
    uint32_t height;
    uint32_t step;
} image_t;
int clip(int x, int low, int up);
void draw_x(image_t *img, int x, int y, int len, uint8_t value);
void draw_o(image_t *img, int x, int y, int radius, uint8_t value);

void clone_image(image_t *img0, image_t *img1);

void clear_image(image_t *img);
//abandon
void adaptive_threshold
	(image_t *img0, image_t *img1, int block_size, int down_value, uint8_t low_value, uint8_t high_value);
// 3x3 expan,img0!=img1,the outermost pixel is not involved in the calculation
void dilate3(image_t *img0, image_t *img1);
// 3x3 erode,img0!=img1,The outermost pixel does not participate in the calculation
void erode3(image_t *img0, image_t *img1);
void draw(void);
void draw_rec(void);
//inverse perspective mapping
void IPMcopy(void);
//search for edge line 
void findline_lefthand_adaptive
	(image_t *img, int block_size, int clip_value, int x, int y, int pts[][2], int *num);
void findline_righthand_adaptive
	(image_t *img, int block_size, int clip_value, int x, int y, int pts[][2], int *num);
//edge line filter
void blur_points(int pts_in[][2], int num, float pts_out[][2], int kernel);
void resample_points(float pts_in[][2], int num1, float pts_out[][2], int *num2, float dist);
//persuit center descrete point of left and right edge
void track_leftline(float pts_in[][2], int num, float pts_out[][2], int approx_num, float dist);
void track_rightline(float pts_in[][2], int num, float pts_out[][2], int approx_num, float dist);
//local slope
void local_angle_points(float pts_in[][2], int num, float angle_out[], int dist);
//non-maximum inhibition after slope
void nms_angle(float angle_in[], int num, float angle_out[], int kernel);
#endif
