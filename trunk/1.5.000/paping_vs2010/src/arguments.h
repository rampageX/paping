#include "standard.h"


class arguments_c
{
	public:
		pcc_t	Destination;
		int		Port;
		int		Type;
		int		Timeout;
		int		Count;
		bool	Continous;
		bool	UseColor;

		static	void	PrintBanner();
		static	void	PrintUsage();

		static	int		Process(int argc, pc_t argv[], arguments_c &arguments);
	private:
		static	int		match(int pos, int total, pc_t argv[], pcc_t shortName, pcc_t longName, bool expectedValue, int &value, bool &anyMatch);
};