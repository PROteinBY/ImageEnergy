#include <iostream>
#include <string>
#include <vector>

#include <SDKUtil.hpp>
#include <SDKBitMap.hpp>

using namespace std;
using namespace appsdk;

int main()
{
	string filename;
	vector<vector<unsigned char>> energyMap;

	cout << "Input file: ";
	cin >> filename;

	SDKBitMap bmp;
	bmp.load(filename.c_str());

	if (bmp.isLoaded())
	{

		energyMap.resize(bmp.getHeight(), vector<unsigned char>(bmp.getWidth(), 0));

		uchar4 *pixels = bmp.getPixels();

		for (int i = 0; i < bmp.getHeight(); i++)
		{
			for (int j = 0; j < bmp.getWidth(); j++)
			{
				energyMap[i][j] = 0;

				int count = 0,
					sum = 0;

				if (i != bmp.getHeight() - 1 && j != j != 0)
				{
					sum += abs(pixels[i * bmp.getWidth() + j].x - pixels[(i + 1) * bmp.getWidth() + (j - 1)].x) +
						abs(pixels[i * bmp.getWidth() + j].y - pixels[(i + 1) * bmp.getWidth() + (j - 1)].y) +
						abs(pixels[i * bmp.getWidth() + j].z - pixels[(i + 1) * bmp.getWidth() + (j - 1)].z);

					count += 3;
				}

				if (i != bmp.getHeight() - 1 && j != j != bmp.getWidth() - 1)
				{
					sum += abs(pixels[i * bmp.getWidth() + j].x - pixels[(i + 1) * bmp.getWidth() + (j + 1)].x) +
						abs(pixels[i * bmp.getWidth() + j].y - pixels[(i + 1) * bmp.getWidth() + (j + 1)].y) +
						abs(pixels[i * bmp.getWidth() + j].z - pixels[(i + 1) * bmp.getWidth() + (j + 1)].z);

					count += 3;
				}

				if (i != 0 && j != j != bmp.getWidth() - 1)
				{
					sum += abs(pixels[i * bmp.getWidth() + j].x - pixels[(i - 1) * bmp.getWidth() + (j + 1)].x) +
						abs(pixels[i * bmp.getWidth() + j].y - pixels[(i - 1) * bmp.getWidth() + (j + 1)].y) +
						abs(pixels[i * bmp.getWidth() + j].z - pixels[(i - 1) * bmp.getWidth() + (j + 1)].z);

					count += 3;
				}

				if (i != 0 && j != j != 0)
				{
					sum += abs(pixels[i * bmp.getWidth() + j].x - pixels[(i - 1) * bmp.getWidth() + (j - 1)].x) +
						abs(pixels[i * bmp.getWidth() + j].y - pixels[(i - 1) * bmp.getWidth() + (j - 1)].y) +
						abs(pixels[i * bmp.getWidth() + j].z - pixels[(i - 1) * bmp.getWidth() + (j - 1)].z);

					count += 3;
				}

				if (i != bmp.getHeight() - 1)
				{
					sum += abs(pixels[i * bmp.getWidth() + j].x - pixels[(i + 1) * bmp.getWidth() + j].x) +
						abs(pixels[i * bmp.getWidth() + j].y - pixels[(i + 1) * bmp.getWidth() + j].y) +
						abs(pixels[i * bmp.getWidth() + j].z - pixels[(i + 1) * bmp.getWidth() + j].z);

					count += 3;
				}

				if (j != 0)
				{
					sum += abs(pixels[i * bmp.getWidth() + j].x - pixels[i * bmp.getWidth() + (j - 1)].x) +
						abs(pixels[i * bmp.getWidth() + j].y - pixels[i * bmp.getWidth() + (j - 1)].y) +
						abs(pixels[i * bmp.getWidth() + j].z - pixels[i * bmp.getWidth() + (j - 1)].z);

					count += 3;
				}

				if (i != 0)
				{
					sum += abs(pixels[i * bmp.getWidth() + j].x - pixels[(i - 1) * bmp.getWidth() + j].x) +
						abs(pixels[i * bmp.getWidth() + j].y - pixels[(i - 1) * bmp.getWidth() + j].y) +
						abs(pixels[i * bmp.getWidth() + j].z - pixels[(i - 1) * bmp.getWidth() + j].z);

					count += 3;
				}

				if (j != bmp.getWidth() - 1)
				{
					sum += abs(pixels[i * bmp.getWidth() + j].x - pixels[i * bmp.getWidth() + (j + 1)].x) +
						abs(pixels[i * bmp.getWidth() + j].y - pixels[i * bmp.getWidth() + (j + 1)].y) +
						abs(pixels[i * bmp.getWidth() + j].z - pixels[i * bmp.getWidth() + (j + 1)].z);

					count += 3;
				}

				if (count != 0)
					energyMap[i][j] = sum / count;
			}
		}

		for (int i = 0; i < bmp.getHeight(); i++)
			for (int j = 0; j < bmp.getWidth(); j++)
				pixels[i * bmp.getWidth() + j].x = pixels[i * bmp.getWidth() + j].y = pixels[i * bmp.getWidth() + j].z = energyMap[i][j];

		filename += ".energy.bmp";

		bmp.write(filename.c_str());
	}
	else
		cout << "Bad file\n";

	return 0;
}