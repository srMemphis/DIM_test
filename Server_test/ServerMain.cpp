#include <iostream>
#include "dim/dim.h"

#include "TestServer.h"


int main()
{
	// get local node name 
	char dnsNodeName[132];
	get_node_name(dnsNodeName);
	std::cout << "Local DNS node name = " << dnsNodeName << std::endl;

	//create service
	int iServiceValue = 1;
	DimService intService("TEST/INT", iServiceValue);

	// start server and register all services
	TestServer::Init("TEST", dnsNodeName);

	while (true)
	{
		Sleep(1000);
		iServiceValue++;
		intService.updateService();
		std::cout << "Service updated with value " << iServiceValue << std::endl;
		TestServer::GetInstance()->HandleCommands();
	}

	return 0;
}
