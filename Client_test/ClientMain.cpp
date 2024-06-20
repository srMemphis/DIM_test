#include <iostream>
#include "TestClient.h"
#include "dim/dim.h"


class IntInfo : public DimInfo
{
public:
	IntInfo(const char* name, int noLinkValue)
		: DimInfo(name, noLinkValue)
	{
	}

	virtual ~IntInfo()
	{
	}

private:
	// async info handler 
	void infoHandler()  override
	{
		std::cout << "Server send " << getInt() << std::endl;
	}
};

int main()
{
	// get local node name 
	char node_name[132];
	get_node_name(node_name);

	std::cout << "DNS local node name = " << node_name << std::endl;

	// set dns to local node
	TestClient::setDnsNode(node_name);

	// browse dns
	char* server, * ptr, * ptr1;
	DimBrowser br;
	int type, n, pid;

	n = br.getServices("*");
	std::cout << "found " << n << " services" << std::endl;

	while ((type = br.getNextService(ptr, ptr1)) != 0)
	{
		std::cout << "type = " << type << " - " << ptr << " " << ptr1 << std::endl;
	}

	br.getServers();
	while (br.getNextServer(server, ptr1, pid))
	{
		std::cout << server << " @ " << ptr1 << ", pid = " << pid << std::endl;
	}

	br.getServerClients("DIS_DNS");
	while (br.getNextServerClient(ptr, ptr1))
	{
		std::cout << ptr << " @ " << ptr1 << std::endl;
	}

	// recieve service info 
	int noLinkInfo = 0;
	IntInfo intInfo("TEST/INT", noLinkInfo);

	while (true)
	{
		Sleep(3000);

		// send non blocking command
		TestClient::sendCommandNB("TEST/RUNTYPECMD", (char*)"TESTRUN");
	}

	return 0;
}
