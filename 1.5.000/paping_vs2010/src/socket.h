#include "standard.h"

class socket_c
{
	public:
		static int Resolve(pcc_t hostname, host_c &host);
		static int SetPortAndType(int port, int type, host_c &host);

		static int Connect(host_c host, int timeout, double &time);

		static int GetSocketType(int type);
		static pcc_t GetFriendlyTypeName(int type);

};
