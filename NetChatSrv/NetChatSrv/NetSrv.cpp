#include <WinSock2.h>
#include <iostream>
using namespace std;

int main()
{
	cout<<"NetSrv"<<endl;

	//�����׽��ֿ�
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

	//�����׽���
	SOCKET sockSrv=socket(AF_INET,SOCK_DGRAM,0);

	//�׽��ֵ�ַ
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr=htonl(INADDR_ANY);
	addrSrv.sin_family=AF_INET;
	addrSrv.sin_port=htons(6000);

	//��
	bind(sockSrv,(SOCKADDR*)&addrSrv,sizeof(SOCKADDR));

	//���ݻ���
	char recvBuf[100]={0};
	char sendBuf[100]={0};

	//�ͻ���
	SOCKADDR_IN addrClient;
	int len=sizeof(SOCKADDR);




	//ѭ�������뷢��
	//���� recvfrom ������TCP �е�recv
	//���� sendto ������TCP�е�send
	while(1)
	{
		recvfrom(sockSrv,recvBuf,100,0,(SOCKADDR*)&addrClient,&len);
		if ('q'==recvBuf[0]||'Q'==recvBuf[0])
		{
			sendto(sockSrv,"q",strlen("q")+1,0,(SOCKADDR*)&addrClient,len);
			cout<<"char end !"<<endl;
			break;
		}
		cout<<inet_ntoa(addrClient.sin_addr)<<" say : "<<recvBuf<<endl<<"input : ";
		cin.getline(sendBuf,100,'\n');
		sendto(sockSrv,sendBuf,strlen(sendBuf)+1,0,(SOCKADDR*)&addrClient,len);

		memset(recvBuf,0,100);
		memset(sendBuf,0,100);
	}

	//�ر��׽���
	closesocket(sockSrv);
	//�����׽��ֿ�
	WSACleanup();

	return 0;
}