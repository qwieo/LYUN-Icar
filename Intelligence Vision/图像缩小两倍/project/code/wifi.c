#include "zf_common_headfile.h"
//ѡ��Э��,��ѡһ������Ȼû�취ͨ��
//#define UTP
#define UDP
#define WIFI_SSID  "LYUN"
#define WIFI_PASSWORD NULL
uint8 wifi_spi_test_buffer[] = "��ʼ���ɹ�\n";
uint8 wifi_spi_get_data_buffer[256];
uint32 data_length = 0;

extern uint8_t show0[100][114] ;


/*  @wifi��ʼ������
 *  @˵����������ɿ��޸Ķ���
 *  @���ߣ�����
 *  @ʱ�䣺2024��3��7��
 * */
void my_spi_wifi_init(void)
{
    while(wifi_spi_init(WIFI_SSID, WIFI_PASSWORD))
    {
        printf("\r\n connect wifi failed. \r\n");
        system_delay_ms(100);                                                   // ��ʼ��ʧ�� �ȴ� 100ms
    }
    printf("\r\n module version:%s",wifi_spi_version);                          // ģ��̼��汾
    printf("\r\n module mac    :%s",wifi_spi_mac_addr);                         // ģ�� MAC ��Ϣ
    printf("\r\n module ip     :%snn",wifi_spi_ip_addr_port);                     // ģ�� IP ��ַ
 
    // zf_device_wifi_spi.h �ļ��ڵĺ궨����Ը���ģ������(����) WIFI ֮���Ƿ��Զ����� TCP ������������ UDP ����
    if(0 == WIFI_SPI_AUTO_CONNECT)                                              // ���û�п����Զ����� ����Ҫ�ֶ�����Ŀ�� IP
    {
        while(wifi_spi_socket_connect("UDP","10.200.68.76","8080","6060"))                                               // ָ�������Ķ˿ں�
        {
            printf("\r\n Connect UDP/TCP Servers error, try again.");                                             // ��������ʧ�� �ȴ� 100ms
        }
    }
    // ���Ͳ���������������
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

/*  @wifi���պ���
 *  @˵����������ɿ��޸Ķ���
 *  @���ߣ�����
 *  @����ֵ��uint32���ͣ����ؽ��յ�������
 *  @ʱ�䣺2024��3��7��
 * */
uint32 my_spi_wifi_rece(void)
{
    data_length = wifi_spi_read_buffer(wifi_spi_get_data_buffer, sizeof(wifi_spi_get_data_buffer));
    if(data_length)                                                         // ������յ����� ��������������ж�
    {
        printf("\r\n Get data: <%s>.", wifi_spi_get_data_buffer);
        if(!wifi_spi_send_buffer(wifi_spi_get_data_buffer, data_length))
        {
            wifi_spi_udp_send_now();
            printf("\r\n send success.");
            memset(wifi_spi_get_data_buffer, 0, data_length);          // ���ݷ������ �������
        }
        else
        {
            printf("\r\n %ld bytes data send failed.", data_length);
            return data_length;
        }
    }
 
 
}
/*  @ͼ���ͺ�����ʼ��
 *  @˵����������ɿ��޸Ķ���
 *  @���ߣ�����
 *  @ʱ�䣺2024��3��7��
 * */
void my_spi_wifi_image_init(void)
{
    //��ʼ�������λ�����֣��Ƽ�������ͷ��ʼ����
    // ������ֳ�ʼ�� ���ݴ���ʹ�ø���WIFI SPI
    seekfree_assistant_interface_init(SEEKFREE_ASSISTANT_WIFI_SPI);
    //����ͼ������
    // ���������ͼ����Ϣ(������ԭʼͼ����Ϣ)
   seekfree_assistant_camera_information_config(SEEKFREE_ASSISTANT_MT9V03X, mt9v03x_image[0], MT9V03X_W, MT9V03X_H);
 
}

void my_spi_wifi_image_send(void)
{
    seekfree_assistant_camera_send();
#ifdef UDP
    wifi_spi_udp_send_now();
#endif
}
