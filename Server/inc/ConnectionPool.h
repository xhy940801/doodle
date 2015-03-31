#include <iostream>
#include <stdio.h>
#include <sstream>
#include <memory>
#include <string>
#include <stdexcept>
#include <mysql_connection.h>
#include <mysql_driver.h>
#include <cppconn/driver.h>
#include <cppconn/connection.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <pthread.h>
#include "BlockingQueue.h"
using namespace std;

class ConnectionPool{
private:
	int maxSize;
	string url;
	string username;
	string password;
	BlockingQueue * request;
	BlockingQueue * response;
	ConnectionPool(int maxSize,string url,string username,string password);
	static ConnectionPool * connectionPool;
	static void workFunction(void * argv);
public:
	static ConnectionPool * getInstance();//single pattern
	void RunWork(BlockingQueue * request,BlockingQueue * response);
};