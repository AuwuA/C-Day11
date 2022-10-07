#include <stdio.h>
#include <string.h>

void test01()
{
    fclose(stdout);
    printf("hello world\n");
}

// 文件指针和普通指针的区别
// 硬盘上的数据不能直接访问必须要加载到内存中才能访问

// 文件的打开和关闭
void test02()
{
    FILE *fp = fopen("./txt", "w");
    if(NULL == fp) {
        perror("fopen err:");
        return;
    }


    fclose(fp);
}

// fputc
void test03()
{
    FILE *fp = fopen("test03.txt", "w");
    if(NULL == fp) {
        perror("fopen err:");
        return;
    }
    int ret = fputc('A', fp);
    if (-1 == ret) {
        perror("fputc err:");
        return;
    }
    fclose(fp);
}

// fputc写入文件26个英文字母
void test04()
{
    FILE *fp = fopen("test04.txt", "w");
    if(NULL == fp) {
        perror("fopen err:");
        return;
    }
    char ch = 'A';
    while(ch <= 'Z') {
        int ret = fputc(ch, fp);
        if (-1 == ret) {
            perror("fputc err:");
            return;
        }
        ch++;
    }
    fclose(fp);
}

void write_file(const char *fileName)
{
    FILE *pf = fopen(fileName, "w");
    if (NULL == pf) {
        perror("fopen err:\n");
        return;
    }
    fputc('a', pf);
    fputc('b', pf);
    fputc(-1, pf);
    fputc('c', pf);
    fputc('d', pf);
    fputc('\n', pf);
    fclose(pf);
}

void read_file(const char *fileName)
{
    FILE *pf = fopen(fileName, "r");
    if (NULL == pf) {
        perror("fopen err:\n");
        return;
    }
    char ch = fgetc(pf);
//    while(ch != EOF) {
//        printf("%c\n", ch);
//        ch = fgetc(pf);
//    }
    while(!feof(pf)) {
        printf("%c\n", ch);
        ch = fgetc(pf);
    }
    printf("%d\n", ch);
    fclose(pf);
}

void test05()
{
    write_file("./test05.txt");
    read_file("./test05.txt");
}

// feof函数用于二进制文件,必须在调用该函数前读取文件内容
void test06()
{
    write_file("./test06.txt");
    read_file("./test06.txt");
}

// fgets
void test07()
{
    char buf[10] = {0};
    fgets(buf, sizeof(buf), stdin);
    printf("%s", buf);
    fputs(buf, stdout);
}

// 练习
void test08()
{
    FILE *fp = fopen("test08.txt", "w");
    if (NULL == fp) {
        perror("fopen err:\n");
        return;
    }
    char buf[1024] = {0};
    fgets(buf, sizeof(buf), stdin);
    while(0 != strcmp(buf, ":wq\n")) {
        int ret = fputs(buf, fp);
        if (-1 == ret) {
            perror("fputs err:\n");
            return;
        }
        memset(buf, 0, sizeof(buf));
        fgets(buf, sizeof(buf), stdin);
    }
    fclose(fp);
}

// 文件版四则运算
int getResult(int optNum1, char optType, int optNum2)
{
    switch(optType) {
    case '+' :
        return optNum1 + optNum2;
        break;
    case '-' :
        return optNum1 - optNum2;
        break;
    case '*' :
        return optNum1 * optNum2;
        break;
    default:
        return optNum1 / optNum2;
    }
}

void test09()
{
    FILE *frp = fopen("./test09.txt", "r");
    FILE *fwp = fopen("./test09tmp.txt", "w");
    if (NULL == frp || NULL == fwp) {
        perror("fopen err:\n");
        return;
    }
    while(!feof(frp))
    {
        int optNum1= 0;
        int optNum2= 0;
        char optType = 0;
        fscanf(frp, "%d%c%d", &optNum1, &optType, &optNum2);
        //char buf[1024] = {0};
        fprintf(fwp,  "%d%c%d=%d\n", optNum1, optType, optNum2, getResult(optNum1, optType, optNum2));
        //sprintf(buf, "%d%c%d=%d\n", optNum1, optType, optNum2, getResult(optNum1, optType, optNum2));
        //fputs(buf, fwp);
    }
    fclose(frp);
    fclose(fwp);
    remove("./test09.txt");
    rename("./test09tmp.txt", "./test09.txt");
}


void test10()
{
    FILE *fp = fopen("./test10.txt", "r+");
    if (NULL == fp) {
        perror("fopen err:\n");
        return;
    }
    while(1)
    {
        int optNum1= 0;
        int optNum2= 0;
        char optType = 0;
        fscanf(fp, "%d%c%d", &optNum1, &optType, &optNum2);
        if (0 == optType) {
            break;
        }
//        if (!feof(fp)) {
//            fseek(fp, -2, SEEK_CUR);
//        } else {
//            fseek(fp, -1, SEEK_CUR);
//        }
        fprintf(fp, "%d", getResult(optNum1, optType, optNum2));
        fseek(fp, 2, SEEK_CUR);
    }
    fclose(fp);
}

int main()
{
//    test01();
//    test02();
//    test03();
//    test04();
//    test05();
//    test06();
//    test07();
//    test08();
//    test09();
    test10();

    return 0;
}
