#pragma once
#include "dim/dis.hxx"

// Server class
// singleton pattern
 class TestServer final : private DimServer
{
public:
	// deleting copy constructor
	TestServer(const TestServer& obj) = delete;

	virtual ~TestServer();
	static TestServer* GetInstance();

	static bool Init(const char* name, const char* dnsNode);
	void HandleCommands();


private:
	void exitHandler(int code) override;
	void errorHandler(int severity, int errorCode, char* errorMsg) override;

	// commands 
	DimCommand* m_runTypeCmd = nullptr;

private:
	// singleton instanse
	static TestServer* s_Instanse;
	TestServer();
};
