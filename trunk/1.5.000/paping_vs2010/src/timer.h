#include "standard.h"

class timer_c
{
		public:
			void	Start();
			double	Stop();

		private:
			bool	hasValue_;
			timeval	start_;
			timeval	stop_;
};
