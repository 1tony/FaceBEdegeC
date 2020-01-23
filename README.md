# FaceBEdegeC.v1.0(beta)
A face recognition system based on edge computing
  边缘设备(如摄像头)与云端建立连接后，云端根据边缘设备的类型，向边缘设备传递相应的数据处理程序，并将采集的数据信息返回云端，云端获取数据后进行处理分析。（目前只支持单个边缘设备的连接）


## 环境要求
### 服务器端
  ·  Ubuntu16.04   
  ·  qt5   
  ·  opencv3.4.0   
  ·  shell
### 边缘设备端
  · Linux环境
  · opencv3.4.0  
## 安装步骤
   整个系统是基于局域网的环境下搭建，所以需要根据使用场景下的网络环境在代码中进行修改，即可运行
   ### 服务器端 
   安装需要的shell环境
   `sudo  apt install openssh-client;
   sudo apt install openssh-server;
   sudo aptt install expect`
   设置服务器监听的端口和ip地址，用于监听等待边缘设备的连接
```cpp
Listen::Listen()
{
	listenfd.client.sin_port = htons(8888);
	listenfd.client.sin_addr.s_addr = htonl(INADDR_ANY);
}
```
 设置数据处理程序与边缘设备的连接（数据的接收，另外创建一个传输链路）
```cpp
//该函数在Soc类中
bool Network_client(struct Soc_info *temp)
{
	sld.client.sin_port = htons(9999);
    sld.client.sin_addr.s_addr = htonl(INADDR_ANY);
}
```
设置服务器端程序需要将编译好的程序（利用写好的脚本）
```cpp
//该函数在Soc类中
void *Proce(void *arg)
{
	system("expect /home/wlm/code/test.sh");
}
```
### 客户端
设置边缘设备需要连接的服务器的ip地址、端口
```cpp
SocKet::SocKet()
{
	sld.server.sin_addr.s_addr = inet_addr("192.168.1.105");
    sld.server.sin_port = htons(8888);
}
```
边缘设备设置数据传输的链路的配置
```cpp
bool Network_client()
{
	sld.server.sin_addr.s_addr = inet_addr("192.168.1.105");
    sld.server.sin_port = htons(9999);
}
```
## 模块
### server
server运行在服务器端，负责等待边缘设备的连接，并根据设备信息向边缘设备传输相应的处理程序。

### Face_Win
基于Qt5搭建的一个窗口，获取由边缘端发来的图像并进行人脸识别
### client_edge
client_edge运行在边缘设备，与云端建立连接后，接收并运行云端传输的处理程序
### carema
由云端传送至边缘设备，与云端建立单独通信链路，读取摄像头数据传输至云端

## 联系方式
If you'd like to contact us, please create a GitHub issue or email ljffuture@163.com. Thank you!
