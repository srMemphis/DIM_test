#include "TestServer.h"
#include <iostream>

// singleton initialization
TestServer* TestServer::s_Instanse = nullptr;

TestServer::TestServer()
{
    TestServer::addErrorHandler(this);
    TestServer::addExitHandler(this);
}

TestServer::~TestServer()
{
    delete m_runTypeCmd;
}

TestServer* TestServer::GetInstance()
{
    return s_Instanse;
}

bool TestServer::Init(const char* name, const char* dnsNode)
{
    if (!s_Instanse)
    {
        s_Instanse = new TestServer();

        s_Instanse->m_runTypeCmd = new DimCommand("TEST/RUNTYPECMD", "C");

        TestServer::setDnsNode(dnsNode);
        TestServer::start(name);

        return true;
    }

    return false;
}

void TestServer::HandleCommands()
{
    // handle queued run type commands 
    while (m_runTypeCmd->getNext())
    {
        std::cout << "Recieved run type command with data: " << m_runTypeCmd->getString() << std::endl;
    }
}

void TestServer::exitHandler(int code)
{
    std::cout << "Exiting with code " << code << std::endl;
    exit(code);   
}

void TestServer::errorHandler(int severity, int errorCode, char* errorMsg)
{
    std::cout << severity << " " << errorMsg << std::endl;
}
