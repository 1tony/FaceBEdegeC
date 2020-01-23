
#include"Listen.h"
#include"Soc.h"
int main()
{
    Soc *soc_ket;//处理数据的套接字
    Listen lis_ten;//这里设定一个套接字
    //有时候，是用开辟内存还是直接变量的方式要斟酌，因为两者的存储地址是不同的

    struct Soc_info *temp;//用来存放接受的数据信息
    temp = new struct Soc_info();

    while(1)
    {
        //初始阶段先满足循环条件即可
       *temp = lis_ten.accept_1();
        //接收到信息后，就交给通信套接字类来进行处理
        soc_ket = new Soc(*temp);
        soc_ket->Soc_Proce();
    }
    delete temp;
    return 0;
}

