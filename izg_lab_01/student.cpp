/**
 * IZG - Zaklady pocitacove grafiky - FIT VUT
 * Lab 01 - Redukce barevneho prostoru
 *
 * Copyright (c) 2022-23 by Michal Vlnas, ivlnas@fit.vutbr.cz
 *
 * Tato sablona slouzi vyhradne pro studijni ucely, sireni kodu je bez vedomi autora zakazano.
 */

#include "base.h"

/**
 * Converts image into grayscale.
 * Use empiric equation presented in lecture.
 */
void ImageTransform::grayscale()
{
	//Transform picture to grayscale
	//I=0.299*r+0.587*g+0.114*b
	//I=R=G=B

	for (uint32_t y = 0; y < cfg->h; y++)
	{
		for (uint32_t x = 0; x < cfg->w; x++)
		{
			auto p = getPixel(x, y);
			uint32_t I = 0.299 * p.r + 0.587 * p.g + 0.114 * p.b;
			p.r = I;				//Setiing each clr of pixel to same value (I).
			p.g = I;
			p.b = I;
			setPixel(x,y,p);		//Setting pixel to a shade of gray.
		}
	}
}

/**
 * Evaluate threshold value for further usage in thresholding,
 * has to be called after grayscale().
 *
 * Note: evaluation method will DIFFER for each group!
 *
 * @return threshold
 */
uint8_t ImageTransform::evaluateThreshold()
{
    uint8_t th = 128;
	uint32_t tmp = 0;	//Temporary threshold counter.
	
	//Evaluating threshold for the whole picture.
	//Counting only each second pixel.

	for (uint32_t y = 0; y < cfg->h; y++)
	{
		for (uint32_t x = 0; x < cfg->w; x++)
		{
			if (x % 2 == 0)
			{
				auto p = getPixel(x, y);	//getting info about each second pixel.
				tmp += p.r;	//Incrementation of tmp threshold.
			}
		}
	}

	tmp = tmp / ((cfg->w * cfg->h) / 2);	//Final threshold (has to be divided by 2, bcs we are ciunting only each second pxl).
	th = tmp;


    IZG_INFO("Evaluated threshold: " + std::to_string(th));
    return th;
}

/**
 * Evaluate threshold value for further usage in thresholding,
 * has to be called after grayscale().
 *
 * Note: evaluation method will DIFFER for each group!
 *
 * @param x Input pixel coordinate
 * @param y Input pixel coordinate
 * @return  threshold
 */
uint8_t ImageTransform::evaluateThreshold(int32_t x, int32_t y)
{
    (void)x;
    (void)y;

    uint8_t th = 128;

    // TODO: write code here or in evaluateThreshold()

    return th;
}

void ImageTransform::threshold()
{
	grayscale();		//Setting image to grayscale (each color of pixel has the value of pixel's threshold).
	uint32_t threshold = evaluateThreshold();	//Getting threshold limit.

	for (uint32_t y = 0; y < cfg->h; y++)
	{
		for (uint32_t x = 0; x < cfg->w; x++)
		{
			auto p = getPixel(x,y);
			if (p.r > threshold)
			{
				setPixel(x,y, COLOR_WHITE);
			}
			else
			{
				setPixel(x,y, COLOR_BLACK);
			}
		}
	}

}

void ImageTransform::randomDithering()
{
    grayscale();

    for (uint32_t y = 0; y < cfg->h; y++)
    {
        for (uint32_t x = 0; x < cfg->w; x++)
        {
            auto p = getPixel(x, y);
            uint8_t value = p.r > getRandom() ? 255 : 0;

            setPixel(x, y, RGB(value));
        }
    }
}

void ImageTransform::orderedDithering()
{
    static uint8_t matrix[m_side][m_side] =
    {
        { 0,   254, 51,  255 },
        { 68,  136, 187, 119 },
        { 34,  238, 17,  221 },
        { 170, 102, 153, 85  }
    };

    //Calling grayscale to know each pixel threshold.
	grayscale();
	for (uint32_t y = 0; y < cfg->h; y++)
	{
		for (uint32_t x = 0; x < cfg->w; x++)
		{
			auto p = getPixel(x,y); //Getting info about each pxl.
			if (p.r > matrix[y % 4][x % 4])	//This way the matrix num are always = {0,1,2,3}.
			{
				setPixel(x,y,COLOR_WHITE);
			}
			else
			{
				setPixel(x, y, COLOR_BLACK);
			}
		}
	}
}

void ImageTransform::updatePixelWithError(uint32_t x, uint32_t y, float err)
{
    (void)x;
    (void)y;
    (void)err;

    // TODO: write code here
}

void ImageTransform::errorDistribution()
{
    // TODO: write code here
}

