# FaceBEdegeC.v1.0(beta)
A face recognition system based on edge computing
  边缘设备(如摄像头)与云端建立连接后，云端根据边缘设备的类型，向边缘设备传递对应的数据处理程序，并将采集的数据信息返回云端，云端再对数据进行处理分析。（目前只支持单个缘设备的连接）
该项目

# 环境要求
  1、Linux系统环境
  2、qt5
  3、opencv3.4.0
  4、shell
 
# 运行步骤
   整个小系统是基于局域网的环境下搭建，所以需要根据使用场景下的网络环境在代码中进行修改，即可运行
   ## 服务器端
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
## 客户端
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
  
  
