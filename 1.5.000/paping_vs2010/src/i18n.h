#include "standard.h"

#define	STRING_USAGE					1000
#define	STRING_CONNECT_INFO_FULL		1001
#define	STRING_CONNECT_INFO_IP			1002
#define	STRING_CONNECT_SUCCESS			1003
#define STRING_STATS					1004

class i18n_c
{
	public:
		static pcc_t GetString(int id);
};
