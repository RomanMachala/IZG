/******************************************************************************
 * Laborator 02 - Zaklady pocitacove grafiky - IZG
 * isolony@fit.vutbr.cz
 *
 * Popis: Hlavicky funkci pro funkce studentu
 *
 * Opravy a modifikace:
 * ivasko@fit.vutbr.cz
 * ipolasek@fit.vutbr.cz
 * ivelas@fit.vutbr.cz
 * itomesek@fit.vutbr.cz
 */

#include "student.h"
#include "globals.h"

// Header standardni knihovny obsahujici funci swap.
#include <memory>
// Zjednoduseni zapisu, napr. std::swap -> swap.
using namespace std;

/**
 * Provede vykresleni pixelu na dane pozici ve vystupnim rasteru. Pokud je
 * souradnice mimo hranice rasteru, potom tato funkce neprovede zadnou zmenu.
 */
S_RGBA getPixelColor(int x, int y)
{
    if (x >= 0 && y >= 0 && x < gWidth && y < gHeight)
    { return gFrameBuffer[y * gWidth + x]; }
    else
    { return makeBlackColor(); }
}

/** 
 * Vycte barvu pixelu na dane pozici ve vystupnim rasteru. Pokud je souradnice
 * mimo hranice rasteru, potom funkce vraci barvu (0, 0, 0, 0).
 */
void setPixelColor(int x, int y, S_RGBA color)
{
    if (x >= 0 && y >= 0 && x < gWidth && y < gHeight)
    { gFrameBuffer[y * gWidth + x] = color; }
}


////////////////////////////////////////////////////////////////////////////////
// Ukol za 2b
////////////////////////////////////////////////////////////////////////////////
#define FRAC_BITS 8
/* Vykresli usecku od [x1, y1] po [x2, y2] vcetne koncovych bodu */
void rasterizeLine(int x1, int y1, int x2, int y2, S_RGBA color)
{
    /*
     * Doplnte do funkce na oznacena mista (#) kod tak, aby po stisku klavesy
     * T aplikace spravne vykreslila cely testovaci vzor se vsemi kvadranty: 
     *
     *   ╲  ┃  ╱
     *    ╲ ┃ ╱
     *  ━━━━╋━━━━
     *    ╱ ┃ ╲ 
     *   ╱  ┃  ╲ 
     */

    // Namisto "int dx = x2 - x1", lze v modernim c++ pouzit: 
    
    //auto dx{ x2 - x1 };
    //auto dy{ y2 - y1 };
	int change = 0;
	int dx = (x2-x1);
	int dy = (y2-y1);


	//kdyz je |dy|>|dx| je treba zamenit osy.
	if (ABS(dy) > ABS(dx))
	{
		SWAP(x1, y1);
		SWAP(x2, y2);
		SWAP(dx, dy);	//Kdyz prohodim hodnoty x1 a y1, spolecne s x2 a y2, tak dx a dy budou taky prohozeny.
		

		change = 1;
	}
	//Zamena bodu, pokud zacatecni bod bude vpravo od leveho
	//Z toho duvodu, ze delame x++ a ne x--
	if (x1 > x2)
	{
		SWAP(x1, x2);
		SWAP(y1, y2);
	}
	//Zacatek a konec ve stejnem bode=NEPLATNA USECKA.
	if (dx == 0 && dy == 0)
	{
		setPixelColor(x1, y1, color);
		//Musime dat return, aby nam program nepokracoval dale
		//V tomto pripade by mohlo dochazet k deleni 0 pri vypoctu smernice k.
		return;
	}
    // #1 : Doplnte kod pro kontrolu vstupu a upravu koordinatu pro ruzne kvadranty.
    
    // Pre riešenie môžete využiť funkcie: 
    //   -- swap(..., ....)  [ https://en.cppreference.com/w/cpp/algorithm/swap ]
    //   -- abs(...)  [ https://en.cppreference.com/w/cpp/numeric/math/fabs
    //                  https://en.cppreference.com/w/cpp/numeric/math/abs ]

	//Prepocet v pripade ze dojde k nejake zamene.

	//Prepocet nemusi byt, pokud dojde k zamnene os, prohodi se i dx a dy.
	//Pokud dojde k jine zamene, obe hodnoty dx a dy budou zaporne,
	//Pokud je jmenovatel a citatel zlomku zaporny dostaneme kladne cislo.
			//dx = (x2 - x1);
			//dy = (y2 - y1);

    auto y{ y1 << FRAC_BITS };
    auto k{ (dy << FRAC_BITS) / dx };
    for (int x = x1; x <= x2; ++x)
    {
		//Pokud dojde ke zmene osy.
		if (change)
		{
			//musime prohodit hodnoty x a y, >> FRAC_BITS zustava u y.
			setPixelColor(y >> FRAC_BITS, x, color);
			//Inkrementace o smernici usecky.
			y += k;
		}
		else
		{
			//Obarveni daneho pixelu, pokud jim dany vektor prochazi.
			setPixelColor(x, y >> FRAC_BITS, color);
			//Inkrementace o smernici usecky.
			y += k;
		}
        // #2 : Doplnte kod pro upravu koordinatu pro ruzne kvadranty, pripadne upravte i setPixelColor(...).
        
    }
}

////////////////////////////////////////////////////////////////////////////////
// Ukol za 1b
////////////////////////////////////////////////////////////////////////////////
void put8PixelsOfCircle(int x, int y, int sx, int sy, S_RGBA color)
{
    /*
     * Doplnte do funkce kod tak, aby po stisku klavesy T aplikace spravne
     * vykreslila testovaci vzor s kruznici ve vsech kvadrantech: 
     *
     * ╭────┳────╮
     * │    ┃    │
     * │    ┃    │
     * ┣━━━━╋━━━━┫
     * │    ┃    │
     * │    ┃    │
     * ╰────┻────╯
     * Využite funkciu setPixelColor(...).
     */

	//8 variant pro 4 kvadranty (kazdy kvadrant ma 2 poloviny, 2*4=8).
	//stred kruznice=[sx, sy];
	
	setPixelColor(sx-x, sy+y, color);
	setPixelColor(sx-y, sy+x, color);
	setPixelColor(sx-y, sy-x, color);
	setPixelColor(sx-x, sy-y, color);
	setPixelColor(sx+x, sy-y, color);
	setPixelColor(sx+y, sy-x, color);
	setPixelColor(sx+y, sy+x, color);
	setPixelColor(sx+x, sy+y, color);
}

/* Vykresli kruznici se stredem v [s1, s2] o polomeru radius */
void rasterizeCircle(int s1, int s2, float radius, S_RGBA color)
{
    const auto r{ static_cast<int>(radius) };

    /* Zaciname na pozici [r, 0] a iterujeme pres nejmensi zmenu, tedy y! */
    auto x{ r };
    auto y{ 0 };

    auto P{ 1 - r };
    auto X2{ 2 - 2 * r };
    auto Y2{ 3 };

    while (x >= y) 
    {
        put8PixelsOfCircle(x, y, s1, s2, color);

        if (P >= 0) 
        {
            P += X2;
            X2 += 2;
            --x;
        }

        P += Y2;
        Y2 += 2;
        ++y;
    }
}

/*****************************************************************************/
/*****************************************************************************/