#include <iostream>
#include <chrono>
#include <thread>
#include <string>
#include <format>
#include <random>

#include "dim/dic.hxx"
#include "dim/dis.hxx"

#define HardcodeDNS 0
#if(HardcodeDNS != 0)
	#include "dim/dim.h"
#endif

int main()
{

#if(HardcodeDNS != 0)
	// get local node name 
	char dnsNodeName[132];
	get_node_name(dnsNodeName);
	std::cout << "Local DNS node name = " << dnsNodeName << std::endl;
	DimServer::setDnsNode(dnsNodeName);
	DimClient::setDnsNode(dnsNodeName);
#endif

	// subdetector state service 
	std::string state;
	state.reserve(80);
	DimService stateService("MPD_DCS_State/TestSubdetector", (char*)state.c_str());

	// subdetector initialization command
	DimCommand iniCommand("MPD_DCS_IniCmd/TestSubdetector", "C");

	// subdetector additional info services
	//
	auto startTime = std::chrono::high_resolution_clock::now();
	std::string uptime;
	uptime.reserve(80);
	DimService uptimeService("MPD_DCS_State/TestSubdetector/Uptime", (char*)uptime.c_str());

	//
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> rndDist(1, 100);
	int randInt = rndDist(rng);
	DimService intService("MPD_DCS_State/TestSubdetector/Random_Number", randInt);

	// start server and register all services
	DimServer::start("TestSubdetector");

	// say hello to DCS
	DimClient::sendCommand("MPD_DCS_Message", "0 Hello from TestSubdetector");

	// update services
	while (true)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		
		// update uptime 
		auto curTime = std::chrono::high_resolution_clock::now();
		std::chrono::duration<float> time = curTime - startTime;
		auto ms_time = std::chrono::duration_cast<std::chrono::milliseconds>(time).count();
		int h = ms_time / 3600000;
		int m = (ms_time % 3600000) / 60000;
		int s = ((ms_time % 3600000) % 60000) / 1000;
		uptime = std::format("{}h:{}m:{}s",h,m,s);
		uptimeService.updateService((char*)uptime.c_str());
		
		// update int 
		randInt = rndDist(rng);
		intService.updateService();

		// treat command 
		while (iniCommand.getNext())
		{
			char* cmnd = iniCommand.getString();
			std::cout << "Received command: " << cmnd << std::endl;
		}

		// update state
		state = "1 Stand_by";
		stateService.updateService((char*)state.c_str());
	}

	return 0;
}
