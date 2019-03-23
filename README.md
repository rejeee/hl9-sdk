# hl9-sdk

#目录结构

app: 公用应用程序文件
bsp：主板驱动支持文件
kernel：内核相关文件
libs：通用库文件
net：网络MAC协议相关
projects: 工程相关文件

#开发环境
例程采用IAR的ARM版本编译环境，版本需要7.7及以上版本，以便支持对应MCU的相关历程及配置。相关软件请自行在官网下载和安装：https://www.iar.com/iar-embedded-workbench。
仿真器可采用J-Link仿真或IAR支持的相关仿真器，采用SWD接口。

#调式说明
本评估板使用MCU仿真的话，需要注意两点。
1.MCU深度休眠时无法使用SWD调式，需要复位芯片以恢复SWD调式口功能进行程序仿真。
2.MCU启动支持BOOT选择开关，对应的端口是PD03，PD03低电平则为运行模式（可仿真调试），高电平为ISP烧录模式。

#工程说明
例程经过很好的代码封装，模块化耦合度低，main文件为主程序入口。

上述代码中：
采用RTX系统多任务处理，除主任务外，分别AT Task（app_at.c）和Mac Task(app_mac.c)分别处理AT指令和无线收发。
platform为HL9相关外设操作。

#二次开发参考
SDK包中集成了AT指令集，AT模式软硬件切换方式、LoRa无线自动收发操作，休眠唤醒、低功耗串口等，提供RTOS系统接口方便进行任务管理，用户可以根据需要增删功能。
具体AT操作，请参考 Rejeee AT指令手册。
