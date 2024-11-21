#include "zf_common_headfile.h"

int16 leftfront,rightfront,leftrear,rightrear;

void encoder_init(void)
{
	encoder_dir_init(QTIMER1_ENCODER2,QTIMER1_ENCODER2_CH1_C2,QTIMER1_ENCODER2_CH2_C24);//leftfront
	encoder_dir_init(QTIMER1_ENCODER1, QTIMER1_ENCODER1_CH1_C0, QTIMER1_ENCODER1_CH2_C1);//rightfront
	encoder_dir_init(QTIMER3_ENCODER2,QTIMER3_ENCODER2_CH1_B18,QTIMER3_ENCODER2_CH2_B19);//rightgear
	encoder_dir_init(QTIMER2_ENCODER1,QTIMER2_ENCODER1_CH1_C3,QTIMER2_ENCODER1_CH2_C25);//leftgear
}
void get_encoder(void)
{
  leftfront=-encoder_get_count(QTIMER1_ENCODER2);
	encoder_clear_count(QTIMER1_ENCODER2);
	rightfront=encoder_get_count(QTIMER1_ENCODER1);
	encoder_clear_count(QTIMER1_ENCODER1);
	rightrear=encoder_get_count(QTIMER3_ENCODER2);
	encoder_clear_count(QTIMER3_ENCODER2);
	leftrear=-encoder_get_count(QTIMER2_ENCODER1);
	encoder_clear_count(QTIMER2_ENCODER1);
	
}
