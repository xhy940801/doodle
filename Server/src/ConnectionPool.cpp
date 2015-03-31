#include "ConnectionPool.h"
ConnectionPool::ConnectionPool(int maxSize,string url="tcp:127.0.0.1:3306",string username="root",string password="password")
{
	this->maxSize = maxSize;
	this->url = url;
	this->username = username;
	this->password = password;

}
void ConnectionPool::workFunction(void * argv)
{
	printf("%d\n",(int *)argv);
	printf("this is %u \n",(unsigned int)pthread_self());
	//deal with the request and response

	return NULL;
}
/*-------public interface------*/
ConnectionPool * ConnectionPool::getInstance()
{
	if(connectionPool==NULL)
		{
			connectionPool = new ConnectionPool(10);
		}
	return connectionPool;
	
}
void ConnectionPool::RunWork(BlockingQueue * request,BlockingQueue * response)
{
	this->request = request;
	this->response = response;
	for(int i = 0 ; i < this->maxSize ; i++) 
	{
		pthread_t thread_id = 0;
		int error = pthread_create(&thread_id,NULL,(void*)workFunction,(void*)&this);
		if(error!=0)
			printf("fail to create thread\n");
	}
}