#include <Windows.h>
#include <mysql.h>
#include <string>
#include <iostream>

using namespace std;

int main()
{

	const char user[] = "root";
	const char pswd[] = "1234";
	const char host[] = "localhost";
	const char dbase[] = "tick";
	unsigned int port = 3306;
	MYSQL myCont;
	MYSQL_RES *result = NULL;
	MYSQL_ROW sql_row;
	int res;
	mysql_init(&myCont);
	if (mysql_real_connect(&myCont, host, user, pswd, dbase, port, NULL, 0))
	{
		//mysql_query(&myCont, "SET NAMES GBK"); //设置编码格式
		res = mysql_query(&myCont, "select * from xauusd order by stamp desc limit 10");//查询
		if (!res)
		{
			result = mysql_store_result(&myCont);
			if (result)
			{
				while (sql_row = mysql_fetch_row(result))//获取具体的数据
				{
					cout << "Stamp: " << sql_row[1] << "\t";
					cout << "Ask: " << sql_row[2] << "\t";
					cout << "Bid: " << sql_row[3] << endl;
				}
			}
		}
		else
		{
			cout << "query sql failed!" << endl;
		}
	}
	else
	{
		cout << "connect failed!" << endl;
	}
	if (result != NULL)
		mysql_free_result(result);
	mysql_close(&myCont);
	system("pause");
	return 0;

}