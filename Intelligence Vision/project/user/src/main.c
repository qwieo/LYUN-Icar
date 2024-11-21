/*********************************************************************************************************************
* RT1064DVL6A Opensourec Library 即（RT1064DVL6A 开源库）是一个基于官方 SDK 接口的第三方开源库
* Copyright (c) 2022 SEEKFREE 逐飞科技
* 
* 本文件是 RT1064DVL6A 开源库的一部分
* 
* RT1064DVL6A 开源库 是免费软件
* 您可以根据自由软件基金会发布的 GPL（GNU General Public License，即 GNU通用公共许可证）的条款
* 即 GPL 的第3版（即 GPL3.0）或（您选择的）任何后来的版本，重新发布和/或修改它
* 
* 本开源库的发布是希望它能发挥作用，但并未对其作任何的保证
* 甚至没有隐含的适销性或适合特定用途的保证
* 更多细节请参见 GPL
* 
* 您应该在收到本开源库的同时收到一份 GPL 的副本
* 如果没有，请参阅<https://www.gnu.org/licenses/>
* 
* 额外注明：
* 本开源库使用 GPL3.0 开源许可证协议 以上许可申明为译文版本
* 许可申明英文版在 libraries/doc 文件夹下的 GPL3_permission_statement.txt 文件中
* 许可证副本在 libraries 文件夹下 即该文件夹下的 LICENSE 文件
* 欢迎各位使用并传播本程序 但修改内容时必须保留逐飞科技的版权声明（即本声明）
* 
* 文件名称          main
* 公司名称          成都逐飞科技有限公司
* 版本信息          查看 libraries/doc 文件夹内 version 文件 版本说明
* 开发环境          IAR 8.32.4 or MDK 5.33
* 适用平台          RT1064DVL6A
* 店铺链接          https://seekfree.taobao.com/
* 
* 修改记录
* 日期              作者                备注
* 2022-09-21        SeekFree            first version
********************************************************************************************************************/
#include "para_space.h"
// 本例程是开源库移植用空工程
/*      每日一拜 好过省赛             天天参拜 稳过国赛        */
/* \\ \\ \\ \\ \\ \\ \\ || || || || || || // // // // // // // //
\\ \\ \\ \\ \\ \\ \\        _ooOoo_          // // // // // // //
\\ \\ \\ \\ \\ \\          o8888888o            // // // // // //
\\ \\ \\ \\ \\             88" . "88               // // // // //
\\ \\ \\ \\                (| -_- |)                  // // // //
\\ \\ \\                   O\  =  /O                     // // //
\\ \\                   ____/`---'\____                     // //
\\                    .'  \\|     |//  `.                      //
==                   /  \\|||  :  |||//  \                     ==
==                  /  _||||| -:- |||||-  \                    ==
==                  |   | \\\  -  /// |   |                    ==
==                  | \_|  ''\---/''  |   |                    ==
==                  \  .-\__  `-`  ___/-. /                    ==
==                ___`. .'  /--.--\  `. . ___                  ==
==              ."" '<  `.___\_<|>_/___.'  >'"".               ==
==            | | :  `- \`.;`\ _ /`;.`/ - ` : | |              \\
//            \  \ `-.   \_ __\ /__ _/   .-` /  /              \\
//      ========`-.____`-.___\_____/___.-`____.-'========      \\
//                           `=---='                           \\
// //   ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^  \\ \\
// // //      佛祖保佑      永无BUG      永不修改          \\ \\ \\
// // // // // // || || || || || || || || || || \\ \\ \\ \\ \\ */
float ta,L2_gyro_z,L_gyro_z,new_gyro_z;

float dangle,langle;
//
void process_image(void);
//
void find_corners(void);
//
void PIT_IRQHandler(void)
{
    if(pit_flag_get(PIT_CH3))
    {
      pit_flag_clear(PIT_CH3);
			get_encoder();
    }
		if(pit_flag_get(PIT_CH1))
    {
      pit_flag_clear(PIT_CH1);
			#if 1
			L2_gyro_z = L_gyro_z;
			L_gyro_z = new_gyro_z;
			imu963ra_get_gyro();
			new_gyro_z = imu963ra_gyro_transition(imu963ra_gyro_z);             
			ta = LowPass_gyro(new_gyro_z, L_gyro_z, L2_gyro_z)*0.002;
			if(fabs(ta)>0.02)
			anglez+=ta;
			#endif
    }
}
//
int main(void)
{
    clock_init(SYSTEM_CLOCK_600M);  // 不可删除
    debug_init();                  // 调试端口初始化
    // 此处编写用户代码 例如外设初始化代码等
		wireless_uart_init();
		system_delay_ms(300);
		my_spi_wifi_init();
		timer_init(GPT_TIM_1, TIMER_MS);
		interrupt_set_priority(PIT_IRQn, 0);
		interrupt_global_enable(0);
		imu963ra_init ();
		encoder_init();
		pit_ms_init(PIT_CH1,2);
		pit_ms_init(PIT_CH3,4);
			
		ips200_set_dir(IPS200_CROSSWISE_180);
		ips200_init(IPS200_TYPE_SPI);
	
		seekfree_assistant_interface_init(SEEKFREE_ASSISTANT_WIRELESS_UART);
	
		while(mt9v03x_init())
		{
			printf("camera Init error");
		}
    // 此处编写用户代码 例如外设初始化代码等
		//my_spi_wifi_image_init();
		ImagePerspective_Init();
		Motor_Init();
		my_spi_wifi_image_init();
		//gear();
		int cnt =0;
		int cnt1 =0;
		float aas=0;
    while(1)
    {
			
			 if(mt9v03x_finish_flag)
        {
					  timer_start(GPT_TIM_1);
					  /* copy image from discere pointer inverse perspective mapping*/
					#if 0
					  IPMcopy();
						blur(&img_raw,&img_AP,5);
						clone_image(&img_AP,&img_raw);
						//draw_rec();
						process_image();
						find_corners();

						/*******stop*****/
						
						if((ipts0_num==0&&ipts1_num==0)||cnt1>10)
						{
							cnt++;
							if(cnt>10||cnt1>10)
							{
								for(uint16_t i=0;i<25600;i++)
								{
								mecanum_basic(0,0);
								}
								Motor_Init();
								return 0;
							}
						}
						else
						{
							cnt=0;
						}
						/******************/
						int16 zv=(leftfront+leftrear+rightfront+rightrear)/40;
						float oa=calculator(rpts[10]);
						float a=calculator(aim0)+calculator(aim1);
						if(calculator(aim0)+calculator(aim1)!=calculator(aim0)+calculator(aim1)){break;cnt1++;}
						else cnt1=0;
						float fa=fabs(a);
						v=80-96*fa;
						{
							dangle= anglez-langle;
							mecanum_basic(v,PidLocCtrl(&Gangle,kalmanFilter(&KFP_angle,dangle),kalmanFilter(&KFP_height,-a)/PI*90.));
							langle= anglez;
						}
							

							
						

						/*******Service for vofa****************/

						#endif
						
						JF_Data.data[1]=kalmanFilter(&KFP_angle,ta);
						JF_Data.data[2]=ta;
						JF_Data.data[0]=anglez*4;
						//JustFloat_Send();
						
						//ips200_show_gray_image(0,0,show0[0],RESULT_COL,RESULT_ROW,RESULT_COL,RESULT_ROW,0);
						//ips200_show_gray_image(114,0,show1[0],RESULT_COL,RESULT_ROW,RESULT_COL,RESULT_ROW,0);
						seekfree_assistant_camera_send();
						timer_stop(GPT_TIM_1);
						//imu963ra_get_acc();
						//ips200_show_uint(1,1,imu963ra_acc_x,2);
						ips200_show_int(1,1,anglez,2);
						ips200_show_uint(200,200,timer_get(GPT_TIM_1),2);
						timer_clear(GPT_TIM_1);
						mt9v03x_finish_flag=0;		
					#if 0

						mt9v03x_finish_flag = 0;						
							// 在发送前将图像备份再进行发送，这样可以避免图像出现撕裂的问题
						memcpy(image_copy[0], show0[0], MT9V03X_IMAGE_SIZE);
						seekfree_assistant_camera_send();
						
					#endif
        }


        // 此处编写需要循环执行的代码
    }
		return 0;
}


void process_image(void) {
		
    int x1 = img_raw.width / 2 - begin_x, y1 = begin_y;
    ipts0_num = sizeof(ipts0) / sizeof(ipts0[0]);
    for (; x1 > 0; x1--) if (AT_IMAGE(&img_raw, x1 - 1, y1) < thres) break;
    if (AT_IMAGE(&img_raw, x1, y1) >= thres)
        findline_lefthand_adaptive(&img_raw, block_size, clip_value, x1, y1-1, ipts0, &ipts0_num);
    else ipts0_num=0;
		
    int x2 = img_raw.width / 2 + begin_x, y2 = begin_y;
    ipts1_num = sizeof(ipts1) / sizeof(ipts1[0]);
    for (; x2 < img_raw.width - 1; x2++) if (AT_IMAGE(&img_raw, x2 + 1, y2) < thres) break;
    if (AT_IMAGE(&img_raw, x2, y2) >= thres)
        findline_righthand_adaptive(&img_raw, block_size, clip_value, x2, y2, ipts1, &ipts1_num);
    else ipts1_num=0;
		
		blur_points(ipts0, ipts0_num, rpts0b, (int) round(line_blur_kernel));
    rpts0b_num = ipts0_num;
    blur_points(ipts1, ipts1_num, rpts1b, (int) round(line_blur_kernel));
    rpts1b_num = ipts1_num;
		
		rpts0s_num = sizeof(rpts0s) / sizeof(rpts0s[0]);
    resample_points(rpts0b, rpts0b_num, rpts0s, &rpts0s_num, sample_dist * pixel_per_meter);
    rpts1s_num = sizeof(rpts1s) / sizeof(rpts1s[0]);
    resample_points(rpts1b, rpts1b_num, rpts1s, &rpts1s_num, sample_dist * pixel_per_meter);
		
		
		
    local_angle_points(rpts0s, rpts0s_num, rpts0a, (int) round(angle_dist / sample_dist));
    rpts0a_num = rpts0s_num;
    local_angle_points(rpts1s, rpts1s_num, rpts1a, (int) round(angle_dist / sample_dist));
    rpts1a_num = rpts1s_num;

    
    nms_angle(rpts0a, rpts0a_num, rpts0an, (int) round(angle_dist / sample_dist) * 2 + 1);
    rpts0an_num = rpts0a_num;
    nms_angle(rpts1a, rpts1a_num, rpts1an, (int) round(angle_dist / sample_dist) * 2 + 1);
    rpts1an_num = rpts1a_num;
		
		
		track_leftline(rpts0s, rpts0s_num, rptsc0, (int) round(angle_dist / sample_dist), pixel_per_meter * ROAD_WIDTH / 2);
    rptsc0_num = rpts0s_num;
    track_rightline(rpts1s, rpts1s_num, rptsc1, (int) round(angle_dist / sample_dist), pixel_per_meter * ROAD_WIDTH / 2);
    rptsc1_num = rpts1s_num;
		
}

void find_corners() {
		Lpt0_found = Lpt1_found = false;
    is_straight0 = rpts0s_num > 1. / sample_dist;
    is_straight1 = rpts1s_num > 1. / sample_dist;
    for (int i = 0; i < rpts0s_num; i++) {
        if (rpts0an[i] == 0) continue;
        int im1 = clip(i - (int) round(angle_dist / sample_dist), 0, rpts0s_num - 1);
        int ip1 = clip(i + (int) round(angle_dist / sample_dist), 0, rpts0s_num - 1);
        float conf = fabs(rpts0a[i]) - (fabs(rpts0a[im1]) + fabs(rpts0a[ip1])) / 2;

        //L-corner
        if (Lpt0_found == false && 70. / 180. * PI < conf && conf < 140. / 180. * PI && i < 0.4 / sample_dist) {
            Lpt0_rpts0s_id = i;
            Lpt0_found = true;
        }
        //straight road 
        if (conf > 5. / 180. * PI && i < 1.0 / sample_dist) is_straight0 = false;
        if (Lpt0_found == true && is_straight0 == false) break;
    }
    for (int i = 0; i < rpts1s_num; i++) {
        if (rpts1an[i] == 0) continue;
        int im1 = clip(i - (int) round(angle_dist / sample_dist), 0, rpts1s_num - 1);
        int ip1 = clip(i + (int) round(angle_dist / sample_dist), 0, rpts1s_num - 1);
        float conf = fabs(rpts1a[i]) - (fabs(rpts1a[im1]) + fabs(rpts1a[ip1])) / 2;
       
        if (Lpt1_found == false && 60. / 180. * PI < conf && conf < 140. / 180. * PI && i < 0.4 / sample_dist) {
            Lpt1_rpts1s_id = i;
            Lpt1_found = true;
        }

        if (conf > 5. / 180. * PI && i < 1.0 / sample_dist) is_straight1 = false;

        if (Lpt1_found == true && is_straight1 == false) break;
    }

    if (1) {
        if (Lpt0_found && Lpt1_found) {
            float dx = rpts0s[Lpt0_rpts0s_id][0] - rpts1s[Lpt1_rpts1s_id][0];
            float dy = rpts0s[Lpt0_rpts0s_id][1] - rpts1s[Lpt1_rpts1s_id][1];
            float dn = sqrtf(dx * dx + dy * dy);
						JF_Data.data[0] =fabs(dn - 0.45 * pixel_per_meter);
            if (fabs(dn - 0.45 * pixel_per_meter) < 0.15 * pixel_per_meter) {
                float dwx = rpts0s[clip(Lpt0_rpts0s_id + 50, 0, rpts0s_num - 1)][0] -
                            rpts1s[clip(Lpt1_rpts1s_id + 50, 0, rpts1s_num - 1)][0];
                float dwy = rpts0s[clip(Lpt0_rpts0s_id + 50, 0, rpts0s_num - 1)][1] -
                            rpts1s[clip(Lpt1_rpts1s_id + 50, 0, rpts1s_num - 1)][1];
                float dwn = sqrtf(dwx * dwx + dwy * dwy);
                if (!(dwn > 0.7 * pixel_per_meter &&
                      rpts0s[clip(Lpt0_rpts0s_id + 50, 0, rpts0s_num - 1)][0] < rpts0s[Lpt0_rpts0s_id][0] &&
                      rpts1s[clip(Lpt1_rpts1s_id + 50, 0, rpts1s_num - 1)][0] > rpts1s[Lpt1_rpts1s_id][0])) {
                    Lpt0_found = Lpt1_found = false;
                }
            } else {
                Lpt0_found = Lpt1_found = false;
            }
        }
    }
}
