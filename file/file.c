#include<stdio.h>
#include<string.h>

int main()
{
    // 使用同一个文件指针操作文件需要注意指针的位置
    // 需要用读写的方式打开，否则读的时候会出现问题
    FILE* fp = fopen("bite", "w+");
    char str[] = "linux so easy, hhh\n";
    fwrite(str, strlen(str), 1, fp);
    // 此时文件指针已指到文件为，需要fseek一下
    // 偏移量是从第三个参数开始算的，正往后偏移，负往前偏移
    fseek(fp, 0, SEEK_SET);
    char buffer[60];
    fread(buffer, strlen(str), 1, fp);
    printf("%s\n", buffer);
    fclose(fp);
    return 0;
}
//#include <stdio.h>
//#include <string.h>
 
//int main()
//{
//   FILE *fp;
//   char c[] = "This is runoob";
//   char buffer[20];
// 
//   /* 打开文件用于读写 */
//   fp = fopen("file.txt", "w+");
// 
//   /* 写入数据到文件 */
//   fwrite(c, strlen(c) + 1, 1, fp);
// 
//   /* 查找文件的开头 */
//   fseek(fp, 0, SEEK_SET);
// 
//   /* 读取并显示数据 */
//   fread(buffer, strlen(c)+1, 1, fp);
//   printf("%s\n", buffer);
//   fclose(fp);
//   
//   return(0);
//}
