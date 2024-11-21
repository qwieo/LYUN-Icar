#include "zf_common_headfile.h"
//选择协议,必选一个，不然没办法通信
//#define UTP
#define UDP
#define WIFI_SSID  "LYUN"
#define WIFI_PASSWORD NULL
uint8 wifi_spi_test_buffer[] = "初始化成功\n";
uint8 wifi_spi_get_data_buffer[256];
uint32 data_length = 0;

extern uint8_t show0[100][114] ;


/*  @wifi初始化函数
 *  @说明：根据逐飞库修改而来
 *  @作者：吴广金
 *  @时间：2024年3月7日
 * */
void my_spi_wifi_init(void)
{
    while(wifi_spi_init(WIFI_SSID, WIFI_PASSWORD))
    {
        printf("\r\n connect wifi failed. \r\n");
        system_delay_ms(100);                                                   // 初始化失败 等待 100ms
    }
    printf("\r\n module version:%s",wifi_spi_version);                          // 模块固件版本
    printf("\r\n module mac    :%s",wifi_spi_mac_addr);                         // 模块 MAC 信息
    printf("\r\n module ip     :%snn",wifi_spi_ip_addr_port);                     // 模块 IP 地址
 
    // zf_device_wifi_spi.h 文件内的宏定义可以更改模块连接(建立) WIFI 之后，是否自动连接 TCP 服务器、创建 UDP 连接
    if(0 == WIFI_SPI_AUTO_CONNECT)                                              // 如果没有开启自动连接 就需要手动连接目标 IP
    {
        while(wifi_spi_socket_connect("UDP","10.200.68.76","8080","6060"))                                               // 指定本机的端口号
        {
            printf("\r\n Connect UDP/TCP Servers error, try again.");                                             // 建立连接失败 等待 100ms
        }
    }
    // 发送测试数据至服务器
    data_length = wifi_spi_send_buffer(wifi_spi_test_buffer, sizeof(wifi_spi_test_buffer));
    wifi_spi_udp_send_now();
    if(!data_length)
    {
        printf("\r\n send success.");
    }
    else
    {
        printf("\r\n %ld bytes data send failed.", data_length);
    }
 
 
}

/*  @wifi接收函数
 *  @说明：根据逐飞库修改而来
 *  @作者：吴广金
 *  @返回值：uint32类型，返回接收到的数据
 *  @时间：2024年3月7日
 * */
uint32 my_spi_wifi_rece(void)
{
    data_length = wifi_spi_read_buffer(wifi_spi_get_data_buffer, sizeof(wifi_spi_get_data_buffer));
    if(data_length)                                                         // 如果接收到数据 则进行数据类型判断
    {
        printf("\r\n Get data: <%s>.", wifi_spi_get_data_buffer);
        if(!wifi_spi_send_buffer(wifi_spi_get_data_buffer, data_length))
        {
            wifi_spi_udp_send_now();
            printf("\r\n send success.");
            memset(wifi_spi_get_data_buffer, 0, data_length);          // 数据发送完成 清空数据
        }
        else
        {
            printf("\r\n %ld bytes data send failed.", data_length);
            return data_length;
        }
    }
 
 
}
/*  @图像发送函数初始化
 *  @说明：根据逐飞库修改而来
 *  @作者：吴广金
 *  @时间：2024年3月7日
 * */
void my_spi_wifi_image_init(void)
{
    //初始化逐飞上位机助手，推荐在摄像头初始化后
    // 逐飞助手初始化 数据传输使用高速WIFI SPI
    seekfree_assistant_interface_init(SEEKFREE_ASSISTANT_WIFI_SPI);
    //配置图传参数
    // 发送总钻风图像信息(仅包含原始图像信息)
   seekfree_assistant_camera_information_config(SEEKFREE_ASSISTANT_MT9V03X, mt9v03x_image[0], MT9V03X_W, MT9V03X_H);
 
}

void my_spi_wifi_image_send(void)
{
    seekfree_assistant_camera_send();
#ifdef UDP
    wifi_spi_udp_send_now();
#endif
}
