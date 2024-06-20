#include <iostream>
#include <chrono>
#include <thread>

#include "TestServer.h"

#include "dim/dim.h"

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
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		iServiceValue++;
		intService.updateService();
		std::cout << "Service updated with value " << iServiceValue << std::endl;
		TestServer::GetInstance()->HandleCommands();
	}

	return 0;
}
