#include<stdio.h>
#include<string.h>

int main()
{
    FILE* pf = fopen("bite", "w+");
    char arr[] = "linux so easy\n";
    fwrite(arr, strlen(arr), 1, pf);
    char str[60];
    fread(str, strlen(arr), 1, pf);
    printf("%s\n", str);
    fclose(pf);
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
