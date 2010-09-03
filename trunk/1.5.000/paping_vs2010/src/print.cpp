#include "standard.h"


using namespace std;


int print_c::initialColors_ = 0;


void print_c::FormattedPrint(int color, pcc_t data)
{
	slice_s		slices[8];
	pc_t		slice;
	int			length	= strlen(data);

	bool		began	= true;
	int			count	= 0;

	slice = new char[length + 1];

	if (slice == NULL)
	{
		cerr << "ERROR: OUT OF MEMORY" << endl;
		return;
	}

	slices[0].Begin = 0;

	for (int i=0; i < length; i++)
	{

		if (data[i] == '$')
		{
			if (!began)
			{
				slices[count].Begin = i;
			}
			else
			{
				slices[count++].End = i;
			}

			began = !began;
		}
	}

	slices[count++].End = length;

	for (int i = 0; i < count; i++)
	{
		int pos = 0;
		int j = 0;

		if (slices[i].Begin != 0) slices[i].Begin++;

		for (j = slices[i].Begin; j < slices[i].End; j++)
		{
			slice[pos++] = data[j];
		}

		slice[pos] = '\0';
		cout << slice;


		pos = 0;

		if (color != 0) print_c::SetColor(color);

		for (int j = slices[i].End + 1; j < slices[i+1].Begin; j++)
		{
			if (j < length)
				slice[pos++] = data[j];
		}

		slice[pos] = '\0';
		cout << slice;

		if (color != 0) print_c::ResetColor();
	}

	if (color != 0) print_c::ResetColor();

	delete[] slice;

	slice = NULL;
}



void print_c::SetColor(int color)
{
	#ifdef _WIN32
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

	if (print_c::initialColors_ == NULL)
	{
		CONSOLE_SCREEN_BUFFER_INFO *bufferInfo = new CONSOLE_SCREEN_BUFFER_INFO();
	
		GetConsoleScreenBufferInfo(console, bufferInfo);

		print_c::initialColors_ = bufferInfo->wAttributes;
	}

	SetConsoleTextAttribute(console, color);
	#else
	printf("\033[01;%dm", color);
	#endif
}


void  print_c::ResetColor()
{
	#ifdef _WIN32
	if (print_c::initialColors_ != NULL)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), print_c::initialColors_);
	}
	#else
	printf("\033[22;%dm", 0);
	#endif
}
