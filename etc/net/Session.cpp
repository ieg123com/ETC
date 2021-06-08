#include "Session.h"
#include "Service.h"


void Session::Destroy()
{

}

void Session::OnRead(const char* data, const size_t len)
{

}

void Session::Send(const char* data, const size_t len)
{
	__service->Send(Fd, data, len);
}