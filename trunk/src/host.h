#include "standard.h"

class host_c
{
	public:
		pcc_t	Hostname;
		in_addr	IPAddress;
		bool	HostIsIP;
		int		Port;
		int		Type;
		
		pcc_t	IPAddressString();
		int		GetConnectInfoString(pcc_t str);
		int		GetSuccessfulConnectionString(pcc_t str, double time);

		static	pcc_t	GetIPAddressAsString(in_addr ipAddress);
		static	pcc_t	GetFriendlyTypeName(int type);
};
