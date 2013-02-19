#include <WinSock2.h>
#include <iostream>
using namespace std;

int main()
{
	cout<<"NetClient"<<endl;

	//加载套接字库
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	wVersionRequested = MAKEWORD(2, 2);

	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) { 
		printf("WSAStartup failed with error: %d\n", err);
		return 1;
	}
	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
		printf("Could not find a usable version of Winsock.dll\n");
		WSACleanup();
		return 1;
	}


	//创建套接字
	SOCKET sockClient=socket(AF_INET,SOCK_DGRAM,0);

	//无需绑定，直接广播发送

	//发送地址
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr=inet_addr("127.0.0.1");
	addrSrv.sin_family=AF_INET;
	addrSrv.sin_port=htons(6000);

	//数据缓存
		char recvBuf[100]={0};
	char sendBuf[100]={0};

	int len=sizeof(SOCKADDR);
	//循环接收和发送
	while(1)
	{
		cout<<"input : ";
		cin.getline(sendBuf,100,'\n');
		sendto(sockClient,sendBuf,strlen(sendBuf)+1,0,(SOCKADDR*)&addrSrv,len);
		recvfrom(sockClient,recvBuf,100,0,(SOCKADDR*)&addrSrv,&len);
		if ('q'==recvBuf[0]||'Q'==recvBuf[0])
		{
			sendto(sockClient,"q",strlen("q"+1),0,(SOCKADDR*)&addrSrv,len);
			cout<<"char end !"<<endl;
			break;
		}
		cout<<inet_ntoa(addrSrv.sin_addr)<<" say : "<<recvBuf<<endl;
		memset(recvBuf,0,100);
		memset(sendBuf,0,100);
	}
	//清楚套接字库
	WSACleanup();
	return 0;
}