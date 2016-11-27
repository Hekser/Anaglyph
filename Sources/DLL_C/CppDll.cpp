#include "CppDll.h"

void generate(unsigned char *leftPic, unsigned char *rightPic, int width, int height)
{
	unsigned char pad = 0;		// padding of bmp
	int pos = 0;				// pos - index of data array
	
	double r = 0.0;
	double g = 0.0;
	double b = 0.0;

	if ((width * 3) % 4 != 0)
	{
		pad = 4 - ((width * 3) % 4);
	}

	for (int j = 0; j < height; ++j)
	{
		for (int i = 0; i < width; ++i)
		{

			r = 0.4561 * leftPic[pos + 2] + 0.500484 * leftPic[pos + 1] + 0.176381 * leftPic[pos] - 0.0434706 * rightPic[pos + 2] - 0.0879388 * rightPic[pos + 1] - 0.00155529 * rightPic[pos];
			g = -0.0400822 * leftPic[pos + 2] - 0.0378246 * leftPic[pos + 1] - 0.0157589 * leftPic[pos] + 0.378476 * rightPic[pos + 2] + 0.73364 * rightPic[pos + 1] - 0.0184503 * rightPic[pos];
			b = -0.0152161 * leftPic[pos + 2] - 0.0205971 * leftPic[pos + 1] - 0.00546856 * leftPic[pos] - 0.0721527 * rightPic[pos + 2] - 0.112961 * rightPic[pos + 1] + 1.2264 * rightPic[pos];

			if (r > 255.0)
			{
				r = 255.0;
			}
			if (r < 0.0)
			{
				r = 0.0;
			}

			if (g > 255.0)
			{
				g = 255.0;
			}
			if (g < 0.0)
			{
				g = 0.0;
			}

			if (b > 255.0)
			{
				b = 255.0;
			}
			if (b < 0.0)
			{
				b = 0.0;
			}

			leftPic[pos] = (unsigned char)b;			//blue
			leftPic[pos + 1] = (unsigned char)g;		//green
			leftPic[pos + 2] = (unsigned char)r;		//red

			pos += 3;
		}
		pos += pad;
	}
}