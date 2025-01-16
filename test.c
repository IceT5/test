#include<stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <securec.h>
int main()
{
    int s=0;
    char mybuffer[5000]={0};
    char records[5000]={0};
    int number=0;
    int i,index;
    int ret;
    recv(s,mybuffer,sizeof(mybuffer),0);                  //污染源：mybuffer为外部传入数据
    number=mybuffer[0]+mybuffer[1];                              //传播路径:将污染数据赋值给number
    ret= memset_s(records, 5000, 0, sizeof(records)*number);     //爆发点1：内存申请使用
    for(i=0;i<number;i++)                                 //爆发点2：循环上界使用
        ret=memcpy_s(records+i,5000, mybuffer+i+1,1);                 //传播路径:将污染数据赋值给records
    index=records[i]-1;                                   //传播路径：records[i]赋值给index后，index同样被污染
    records[index]=mybuffer[i];                           //爆发点3：index作为数组下标被使用
    records[number]=mybuffer[i+1];
    return 0;
    
}
