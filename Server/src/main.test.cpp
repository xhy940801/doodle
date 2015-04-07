#include <mysql/mysql.h>
#include <stdio.h>

void main(){
   MYSQL *mysql;
   MYSQL_RES *res;
   MYSQL_ROW row;
   char *query;
   int t,r;

   mysql_init(mysql);
   if (!mysql_real_connect(mysql,"localhost","root","password","test",0,NULL,0))
   {
       printf( "Error connecting to database: %s",mysql_error(mysql));
   }
   else printf("Connected...");
   mysql_close(mysql);
}