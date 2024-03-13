#include <stdio.h>
#include <cstring>
#include <stdlib.h>
#include<sstream>
#include<fstream>
#include<cmath>
#include<iostream>
#include <unistd.h>
#include <cstdlib>

#include "Ti5MOVE.h"
#include "Ti5BASIC.h"
#include "Ti5LOGIC.h"
#include "communication.h"
#include "mathfunc.h"
#include "tool.h"
#include "clamping_jaw.h"

#include "example.h"

#include <csignal>
//#include <conio.h>

// 定义颜色转义序列
#define RESET   "\033[0m"
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */

/*例如：
std::cout << RED << "红色字体" << RESET << std::endl;
std::cout << GREEN << "绿色字体" << RESET << std::endl;
std::cout << YELLOW << "黄色字体" << RESET << std::endl;
std::cout << BLUE << "蓝色字体" << RESET << std::endl;
std::cout << MAGENTA << "品红色字体" << RESET << std::endl;
std::cout << CYAN << "青色字体" << RESET << std::endl;

std::string text = "Hello, World!";
std::cout << GREEN << text << RESET << std::endl;
*/

using namespace std;

string filename ;
// string device_485_name;
char device[] = "/dev/ttyUSB0"; 

void signalHandler(int signum)
{
    
    char aaa;
    cout << "Interrupt signal (" << signum << ") received.\n";
    // aaa = scanKeyboard();
    brake();  
    cout << "stop!!" << endl;
    // switch (aaa)
    // {
    //     case 'b':
    //     {
    //         brake();  
    //         cout << "stop!!" << endl;
    //         break;
    //     }
    // }
    inspect_brake();

    // 清理并关闭
    // 终止程序  
    logout();
    exit(signum);

 
}




int main()
{
    vector<string> productSerialNumbers = query_can();
    if (productSerialNumbers.empty()) {
        cout << RED<<"未找到任何 USB 设备，请插入设备后重试！" <<RESET << endl;
        exit(0);
    } else {
        cout <<CYAN<< "找到的 CAN 设备序列号：" <<RESET;
        for (const string& serialNumber : productSerialNumbers) {
            cout << CYAN <<serialNumber <<RESET << endl;
        }
    }
    // string qqq=query_can();
    // cout<<"qqq="<<qqq<<endl;
    string ip=ip_address();
    cout<<MAGENTA << "ip="<<ip<<RESET <<endl;
    
    cout<<"qweqwdsaradasd"<<endl;
    signal(SIGINT, signalHandler);
    login();
    cout<<"login success"<<endl;
    mechanical_arm_origin();
    sleep(3);
    show_value("pos:",TH.pos);
    cout<<endl;
    show_value("TH.j= ",TH.j);
    brake();
    // TH.pos[0]=4.5;TH.pos[1]= 316.30;TH.pos[2]=312.43;TH.pos[3]=2.08;TH.pos[4]=-1.27;TH.pos[5]=-1.98;
    move_to_pos(2);
    // TH.j[0]=2.22;
    // TH.j[1]=-0.68;
    // TH.j[2]=2.22;
    // TH.j[3]=1.48;
    // TH.j[4]=1.56;
    // TH.j[5]=1.32;
    // move_to_joint(2);
    // set_elc_info(AAA,1,MotorTypeHelper::REG_TARGET_CURRENT, 0);//设置1个电机为电流模式，并设置电流为0
    while (1)
    {
        char flag;
        cout << BLUE << "*********************************" << RESET << endl;
        cout << BLUE << "请选择模式：" << RESET << endl;
        cout << BLUE << "1.手动模式；" << RESET << endl;
        cout << BLUE << "2.加载作业模式；" << RESET << endl;
        cout << BLUE << "3.加载手动模式记录轨迹点角度值；" << RESET << endl;
        cout << BLUE << "4.倒水demo; " << RESET << endl;
        cout << BLUE << "5.直线运动demo; " << RESET << endl;
        cout << BLUE << "6.运行demo_1; " << RESET << endl;
        cout << BLUE << "7.运行demo_2; " << RESET << endl;
        cout << BLUE << "8.运行demo_3; " << RESET << endl;
        cout << BLUE << "9.运行demo_4; " << RESET << endl;
        cout << BLUE << "a.运行demo_5; " << RESET << endl;
        cout << BLUE << "b.运行demo_6; " << RESET << endl;
        cout << BLUE << "c.运行485串口通信获取坐标点; " << RESET << endl;
        cout << BLUE << "esc 退出；" << RESET << endl;
        cout << BLUE << "*********************************" << RESET << endl;
        flag = scanKeyboard();
        cout<<endl;
        // scanf("%d",&flag);
        // if (flag == '\n' || flag == '\r') { // 判断是否按下回车键
        switch (flag)
        {
            case '1':
                keyboard_controller();
                break;
            case '2':
                cout<<"请输入文件名";
                // filename = scanKeyboard();
                cin>>filename;
                cout<<endl;
                load_program(0,2,filename);
                break;
            case '3':
                keyboard_save_point();
                break;
            case '4':
                pour_water();
                break;
            case '5':
                linear_motion();
                break;
            case '6':
                demo_1();
                break;
            case '7':
                demo_2();
                break;
            case '8':
                demo_3();
                break;
            case '9':
                demo_4();
                break;
            case 'a':
                demo_5();
                break;
            case 'b':
                demo_6();
                break;
            case 'c':
                uart485_communication(device);
                break;
            // case '11':
            //     cout<<"测试"<<endl;
            //     break;
            default:
                cout << GREEN << "无效的选项，请重新选择。" << RESET << endl;
                break;
        }
        if (flag == 27)
		{
			brake();
            cout<<RED<<"程序已退出"<<RESET<<endl;
			break;
		}
    }
    // float a[6]={0, 100, 450, 0.049768, -3.13849,  0};
    // float b[6]={0,  110, 450, 0.049768,  -3.13849, 0};
    // float c[6]={0, 120, 450, 0.049768, -3.13849,  0};
    // float d[]={ 0,  130, 450,  0.049768,  -3.13849,  0};
    // float e[]={0,  140, 450,  0.049768,  -3.13849,  0};
    // float f[]={ 0,  150, 450, 0.049768,  -3.13849,  0};
    // float g[]={ 0,  160,  450, 0.049768, -3.13849,  0};
    // float h[]={ 0,  170,  450, 0.049768, -3.13849,  0};
    // float i[]={ 0,  180,  450, 0.049768, -3.13849,  0};
    // float j[]={ 0,  190,  450, 0.049768, -3.13849,  0};
    // float k[]={ 0,  200,  450, 0.049768, -3.13849,  0};
    // float l[]={ 0,  201,  450, 0.049768, -3.13849,  0};
    // float m[]={ 0,  202,  450, 0.049768, -3.13849,  0};
    // float n[]={ 0,  203,  450, 0.049768, -3.13849,  0};
    // float o[]={ 0,  204,  450, 0.049768, -3.13849,  0};
    // float p[]={ 0,  205,  450, 0.049768, -3.13849,  0};
    // float q[]={ 0,  206,  450, 0.049768, -3.13849,  0};
    // float r[]={ 0,  207,  450, 0.049768, -3.13849,  0};
    // float s[]={ 0,  208,  450, 0.049768, -3.13849,  0};
    // float t[]={ 0,  209,  450, 0.049768, -3.13849,  0};
    // float u[]={ 0,  300,  450, 0.049768, -3.13849,  0};
    // float u2[]={ 0,  301,  450, 0.049768, -3.13849,  0};
    // float u3[]={ 0,  302,  450, 0.049768, -3.13849,  0};
    // float u4[]={ 0,  305,  450, 0.049768, -3.13849,  0};
    // float u5[]={ 0,  309,  450, 0.049768, -3.13849,  0};
    // float u6[]={ 0,  400,  450, 0.049768, -3.13849,  0};
    // float u7[]={ 0,  405,  450, 0.049768, -3.13849,  0};
    // float u8[]={ 0,  500,  450, 0.049768, -3.13849,  0};
    // float u9[]={ 0,  505,  450, 0.049768, -3.13849,  0};
    // pos_movement(a);
    // sleep(3);
    // pos_movement(b);
    // pos_movement(c);
    // pos_movement(d);
    // pos_movement(e);
    // pos_movement(f);
    // pos_movement(g);
    // pos_movement(h);
    // pos_movement(i);
    // pos_movement(j);
    // pos_movement(k);
    // pos_movement(l);
    // pos_movement(m);
    // pos_movement(n);
    // pos_movement(o);
    // pos_movement(p);
    // pos_movement(q);
    // pos_movement(r);
    // pos_movement(s);
    // pos_movement(t);
    // pos_movement(u);
    // pos_movement(u2);
    // pos_movement(u3);
    // pos_movement(u4);
    // pos_movement(u5);
    // pos_movement(u6);
    // pos_movement(u7);
    // pos_movement(u8);
    // pos_movement(u9);
    // // brake();


    // while(1)
    // {   
    //     int a;
    //     cout<<"输入"<<endl;
    //     cin>>a;
    //     // keyboard_controller_j(a,0.025);
    //     keyboard_controller_pos(a,5,0.02);
    // }

    /*******************获取、设置电机参数*********************************/
    /*get_elc_info();
    set_elc_info(reg_position_kp,0,MotorTypeHelper::REG_POSITION_KP, 500);
    set_elc_info(reg_position_kp,1,MotorTypeHelper::REG_POSITION_KP, 700);
    set_elc_info(reg_position_kp,2,MotorTypeHelper::REG_POSITION_KP, 800);
    set_elc_info(reg_position_kp,3,MotorTypeHelper::REG_POSITION_KP, 900);
    set_elc_info(reg_position_kp,4,MotorTypeHelper::REG_POSITION_KP, 1000);
    set_elc_info(reg_position_kp,5,MotorTypeHelper::REG_POSITION_KP, 1100);
    get_elc_info();
    cout<<"sadsad:0=="<<reg_position_kp[0]<<endl;
    cout<<"sadsad:1=="<<reg_position_kp[1]<<endl;
    cout<<"sadsad:2=="<<reg_position_kp[2]<<endl;
    cout<<"sadsad:3=="<<reg_position_kp[3]<<endl;
    cout<<"sadsad:4=="<<reg_position_kp[4]<<endl;
    cout<<"sadsad:5=="<<reg_position_kp[5]<<endl;*/
    /*******************获取、设置电机参数*********************************/
    // get_elc_info();
    // set_elc_info(AAA,0,MotorTypeHelper::REG_TARGET_CURRENT,0);
    // set_elc_info(AAA,1,MotorTypeHelper::REG_TARGET_POSITION,0);
    // set_elc_info(AAA,2,MotorTypeHelper::REG_TARGET_POSITION,0);
    // set_elc_info(AAA,3,MotorTypeHelper::REG_TARGET_POSITION,0);
    // set_elc_info(AAA,4,MotorTypeHelper::REG_TARGET_POSITION,0);
    // set_elc_info(AAA,5,MotorTypeHelper::REG_TARGET_POSITION,0);
    // cout<<"1电机设置零电流成功"<<endl;
    // // get_elc_info();
    // sleep(50);
    
    /*if(get_electricity_status() != true)
    {
        cout <<"电机异常！"<<endl;
    }*/
    //  clock_t start, end;
    //     double duration;
    //     start=clock();
    // for(int num=0;num<20;num++)
    // {
       
    //     keyboard_controller_pos(1,1,0.02);
      
    // }
    //   end=clock();
    //     duration=(double)(end-start)/CLOCKS_PER_SEC;
    //     printf("函数运行时间：%f 秒\n", duration);
    brake();
    // uart485_communication("/dev/pts/4");
    // char* device = "/dev/pts/4";
 
    char device[] = "/dev/ttyUSB0"; 
    
    uart485_communication(device);
    // uart485_communication("/dev/ttyUSB0");
    logout();
    return 0;
}
