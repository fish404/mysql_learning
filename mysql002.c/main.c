#include <stdio.h>

#include <mysql.h>

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "Secur32.lib")
#pragma comment(lib, "mysqlclient.lib")
//#pragma comment(lib, "libmysql.lib")  ʹ��������ǻᱨ�� lnk1107 �ļ���Ч���𻵣��޷���0x348����ȡ

#define LOG(...)  fprintf(stderr, __VA_ARGS__)

int main(int argc, char* argv[])
{
    MYSQL* pmysql = mysql_init(NULL);
    if (pmysql == NULL)
    {
        LOG("��ʼ��mysql��ʧ��\n");
        return -1;
    }

    MYSQL* ret = mysql_real_connect(pmysql, "localhost","fish","imfish*","world",0,NULL,0);
    if (ret == NULL)
    {
        LOG("���ӵ����ݿ� %s:%s ʧ��\n","localhost","world");
        return -1;
    }

    int ret_query = mysql_query(pmysql,"SELECT * FROM world.city;");
    if (ret_query == 0)
    {
        MYSQL_RES * my_result = mysql_store_result(pmysql);

        int num = mysql_num_fields(my_result);
        int i;
        MYSQL_ROW row;
        while ((row = mysql_fetch_row(my_result)) != NULL)
        {
            for (i = 0; i < num; i++)
            {
                printf("%s\t", row[i]);
            }
            printf("\n");
        }

        // �ͷŻ�ȡ�Ľ��
        mysql_free_result(my_result);
    }

    mysql_close(pmysql);
    mysql_library_end();
    return 0;
}

