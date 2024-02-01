/**
 * @file        student.cpp
 * @author      Ladislav Mosner, VUT FIT Brno, imosner@fit.vutbr.cz
 * @author      Petr Kleparnik, VUT FIT Brno, ikleparnik@fit.vutbr.cz
 * @author      Kamil Behun, VUT FIT Brno, ibehun@fit.vutbr.cz
 * @date        11.03.2018
 *
 * @brief       Deklarace funkci studentu. DOPLNUJI STUDENTI
 *
 */

#include "base.h"
#include "student.h"
#include "globals.h"
#include <math.h>

/**
 * @brief Vraci barvu pixelu z pozice [x, y]
 * @param[in] x X souradnice pixelu
 * @param[in] y Y souradnice pixelu
 * @return Barva pixelu na pozici [x, y] ve formatu RGBA
 */
RGBA getPixel(int x, int y)
{
    if (x >= width || y >= height || x < 0 || y < 0) {
        IZG_ERROR("Pristup do framebufferu mimo hranice okna\n");
    }
    return framebuffer[y * width + x];
}

/**
 * @brief Nastavi barvu pixelu na pozici [x, y]
 * @param[in] x X souradnice pixelu
 * @param[in] y Y souradnice pixelu
 * @param[in] color Barva pixelu ve formatu RGBA
 */
void putPixel(int x, int y, RGBA color)
{
    if (x >= width || y >= height || x < 0 || y < 0) {
        IZG_ERROR("Pristup do framebufferu mimo hranice okna\n");
    }
    framebuffer[y * width + x] = color;
}

/**
 * @brief Vykresli usecku se souradnicemi [x1, y1] a [x2, y2]
 * @param[in] x1 X souradnice 1. bodu usecky
 * @param[in] y1 Y souradnice 1. bodu usecky
 * @param[in] x2 X souradnice 2. bodu usecky
 * @param[in] y2 Y souradnice 2. bodu usecky
 * @param[in] color Barva pixelu usecky ve formatu RGBA
 * @param[in] arrow Priznak pro vykresleni sipky (orientace hrany)
 */
void drawLine(int x1, int y1, int x2, int y2, RGBA color, bool arrow = false)
{

    if (arrow) {
        // Sipka na konci hrany
        double vx1 = x2 - x1;
        double vy1 = y2 - y1;
        double length = sqrt(vx1 * vx1 + vy1 * vy1);
        double vx1N = vx1 / length;
        double vy1N = vy1 / length;
        double vx1NN = -vy1N;
        double vy1NN = vx1N;
        int w = 3;
        int h = 10;
        int xT = (int) (x2 + w * vx1NN - h * vx1N);
        int yT = (int) (y2 + w * vy1NN - h * vy1N);
        int xB = (int) (x2 - w * vx1NN - h * vx1N);
        int yB = (int) (y2 - w * vy1NN - h * vy1N);
        pinedaTriangle(Point(x2, y2), Point(xT, yT), Point(xB, yB), color, color, false);
    }

    bool steep = abs(y2 - y1) > abs(x2 - x1);

    if (steep) {
        SWAP(x1, y1);
        SWAP(x2, y2);
    }

    if (x1 > x2) {
        SWAP(x1, x2);
        SWAP(y1, y2);
    }

    const int dx = x2 - x1, dy = abs(y2 - y1);
    const int P1 = 2 * dy, P2 = P1 - 2 * dx;
    int P = 2 * dy - dx;
    int y = y1;
    int ystep = 1;
    if (y1 > y2) ystep = -1;

    for (int x = x1; x <= x2; x++) {
        if (steep) {
            if (y >= 0 && y < width && x >= 0 && x < height) {
                putPixel(y, x, color);
            }
        } else {
            if (x >= 0 && x < width && y >= 0 && y < height) {
                putPixel(x, y, color);
            }
        }

        if (P >= 0) {
            P += P2;
            y += ystep;
        } else {
            P += P1;
        }
    }
}

/**
 * @brief Vyplni a vykresli trojuhelnik
 * @param[in] v1 Prvni bod trojuhelniku
 * @param[in] v2 Druhy bod trojuhelniku
 * @param[in] v3 Treti bod trojuhelniku
 * @param[in] color1 Barva vyplne trojuhelniku
 * @param[in] color2 Barva hranice trojuhelniku
 * @param[in] arrow Priznak pro vykresleni sipky (orientace hrany)
 *
 * SPOLECNY UKOL. Doplnuji studenti se cvicicim.
 */
void pinedaTriangle(const Point &v1, const Point &v2, const Point &v3, const RGBA &color1, const RGBA &color2, bool arrow)
{
    // Nalezeni obalky (minX, maxX), (minY, maxY) trojuhleniku.
    //////// DOPLNTE KOD /////////
	
	//Nalezneme nejvetsi a nejmensi hodnoty pro x a y
	int minX = MIN(v1.x, MIN(v2.x, v3.x));
	int minY = MIN(v1.y, MIN(v2.y, v3.y));
	int maxX = MAX(v1.x, MAX(v2.x, v3.x));
	int maxY = MAX(v1.y, MAX(v2.y, v3.y));

	


    // Oriznuti obalky (minX, maxX, minY, maxY) trojuhleniku podle rozmeru okna.
    //////// DOPLNTE KOD /////////
	//Musime osetrit, pokud by nejaky bod zasahoval mimo nase okno.
	minY = MAX(0, minY);
	minX = MAX(0, minX);
	maxY = MIN(maxY, height);
	maxX = MIN(maxX, width);

    // Spocitani parametru hranove funkce (deltaX, deltaY) pro kazdou hranu.
	// Hodnoty deltaX, deltaY jsou souradnicemi vektoru, ktery ma pocatek
	// v prvnim vrcholu hrany, konec v druhem vrcholu.
	// Vypocet prvnotni hodnoty hranove funkce.
    //////// DOPLNTE KOD /////////

	//Vypocet deltX a deltY pro vsechy hrany trojuhelniku.
	int h1_y = v2.y - v1.y;
	int h1_x = v2.x - v1.x;
	int h2_y = v3.y - v2.y;
	int h2_x = v3.x - v2.x;
	int h3_y = v1.y - v3.y;
	int h3_x = v1.x - v3.x;

	int b1_y = minY - v1.y;
	int b1_x = minX - v1.x;
	int b2_y = minY - v2.y;
	int b2_x = minX - v2.x;
	int b3_y = minY - v3.y;
	int b3_x = minX - v3.x;

	//Vypocet jednotlivych hranovych funkci.
	int e1 = b1_y * h1_x - b1_x * h1_y;
	int e2 = b2_y * h2_x - b2_x * h2_y;
	int e3 = b3_y * h3_x - b3_x * h3_y;

	

    // Vyplnovani: Cyklus pres vsechny body (x, y) v obdelniku (minX, minY), (maxX, maxY).
    // Pro aktualizaci hodnot hranove funkce v bode P (x +/- 1, y) nebo P (x, y +/- 1)
    // vyuzijte hodnoty hranove funkce E (x, y) z bodu P (x, y). (e1, e2, e3 musi byt vetsi jak 0)
	

    //////// DOPLNTE KOD /////////
	for (int y = minY; y < maxY; ++y)
	{
		int t1 = e1;
		int t2 = e2;
		int t3 = e3;
		for (int x = minX; x < maxX; ++x)
		{
			if (0 <= t1 && 0 <= t2 && 0 <= t3)
				putPixel(x, y, color1);
			//Pokud jsou vsechny hodnoty t1,2,3 kladne nebo 0, znamena to, ze bod nam lezi v kladne polorovine
			t1 -= h1_y;
			t2 -= h2_y;
			t3 -= h3_y;

			//Vyuzivame vlastnosti, ze "pozice" sousedniho bodu se nam lisi od puvodniho o deltaX nebo deltaY
			//Zalezi jestli se pohybujeme ve smeru x souradnice nebo ve smeru y
			//Tim padem nemusime pocitat hranove funkce pro vsechny body
		}
		e1 += h1_x;
		e2 += h2_x;
		e3 += h3_x;
	}

    // Prekresleni hranic trojuhelniku barvou color2.
    drawLine(v1.x, v1.y, v2.x, v2.y, color2, arrow);
    drawLine(v2.x, v2.y, v3.x, v3.y, color2, arrow);
    drawLine(v3.x, v3.y, v1.x, v1.y, color2, arrow);
}

/**
 * @brief Vyplni a vykresli polygon
 * @param[in] points Pole bodu polygonu
 * @param[in] size Pocet bodu polygonu (velikost pole "points")
 * @param[in] color1 Barva vyplne polygonu
 * @param[in] color2 Barva hranice polygonu
 *
 * SAMOSTATNY BODOVANY UKOL. Doplnuji pouze studenti.
 */
void pinedaPolygon(const Point *points, const int size, const RGBA &color1, const RGBA &color2)
{
    // Pri praci muzete vyuzit pro vas predpripravene datove typy z base.h., napriklad:
    //
    //      Pro ukladani parametru hranovych funkci muzete vyuzit prichystany vektor parametru hranovych funkci "EdgeParams":
    //
	EdgeParams edgeParams(size);
    //          EdgeParams edgeParams(size)                         // Vytvorite vektor (pole) "edgeParams" parametru hranovych funkci o velikosti "size".
    //          edgeParams[i].deltaX, edgeParams[i].deltaY          // Pristup k parametrum (deltaX, deltaY) hranove funkce v poli "edgeParams" na indexu "i".
    //
    //      Pro ukladani hodnot hranovych funkci muzete vyuzit prichystany vektor hodnot hranovych funkci "EdgeFncValues":
    //
	EdgeFncValues edgeFncValues(size);
	//temp promennou mame inicializovanou pro konecny cyklus
	EdgeFncValues edgeFncValues_temp(size);
    //          EdgeFncValues edgeFncValues(size)                   // Vytvorite vektor (pole) "edgeFncValues" hodnot hranovych funkci o velikosti "size".
    //          edgeFncValues[i]                                    // Pristup k hodnote hranove funkce v poli "edgeFncValues" na indexu "i".
    //

    // Nalezeni obalky (minX, maxX), (minY, maxY) polygonu.
	
	int maxX, maxY, minX, minY;
	//Nastavime si do jednotlivych promennych temp hodnoty bodu z pozice 0
	//Z toho duvpdu, ze budeme nize vyuzovat cyklus for a dostupne funkce MIN a MAX a nechceme porovnavat neco s nicim.
	maxX = points[0].x;
	maxY = points[0].y;
	minX = points[0].x;
	minY = points[0].y;

	//V cyklu for porovnavame jeden bod za druhym a vzdy se nam vybere ten nejvetsi/nejmensi pomoci fnc MAX/MIN
	for (int i = 0; i < size; i++)
	{
		maxX = MAX(maxX, points[i].x);
		maxY = MAX(maxY, points[i].y);
		minX = MIN(minX, points[i].x);
		minY = MIN(minY, points[i].y);
	}
	


    // Oriznuti obalky (minX, maxX), (minY, maxY) polygonu podle rozmeru okna
	
	//Stejne jako v predchozim pripadu musime zajistit oriznuti obalky, pokud by nam nejaky bod zasahoval mimo platno
	minX = MAX(0, minX);
	minY = MAX(0, minY);
	maxX = MIN(maxX, width - 1);
	maxY = MIN(maxY, height - 1);

  


    // Spocitani parametru (deltaX, deltaY) hranove funkce pro kazdou hranu.
	// Hodnoty deltaX, deltaY jsou souradnicemi vektoru, ktery ma pocatek
	// v prvnim vrcholu hrany, konec v druhem vrcholu.
	// Vypocet prvnotnich hodnot hranovych funkci pro jednotlive hrany.



	//Vypocitavame hranove funkce podobnym zpusobem jako v uloze predtim.
	for (int i = 0; i < size; i++) 
	{
		//Pomocna promenna index se pouziva pro naleznuti dalsiho bodu
		//Dejme tomu, ze budeme mit size 5, aktualni hodnota bude i=4, prvni bod y bude na indexu=4
		//Druhy bod y bude na indexu=((4+1) % 5=0. To znamena, ze posledni bod se nam spoji s prvnim bodem na indexu 0
		//Dalsi pripad: i=2, prvni bod je na indexu 2, druhy na indexu 3 % 5 = 3, znovu se jedna o nasledujici bod.

		//Diky operaci modulo jsme schopni dopocitat deltaX a deltaY (pri "narazeni na" posledni bod) jeho rozdil s prvnim bodem v poli.
		int index = (i + 1) % size;
		//Spocitame deltaX a deltaY
		edgeParams[i].deltaY = points[i].y - points[index].y;
		edgeParams[i].deltaX = points[index].x - points[i].x;
		//Do temp promenne ukladame 
		auto params_temp = points[i].x * points[index].y - points[index].x * points[i].y;

		//Do edgeFncValues ukladame finalni hodnotu hranove funkce
		edgeFncValues[i] = edgeParams[i].deltaY * minX + edgeParams[i].deltaX * minY + params_temp;
	}
	

   


    // Test konvexnosti polygonu    

    //////// DOPLNTE KOD /////////


    // Vyplnovani: Cyklus pres vsechny body (x, y) v obdelniku (minX, minY), (maxX, maxY).
    // Pro aktualizaci hodnot hranove funkce v bode P (x +/- 1, y) nebo P (x, y +/- 1)
    // vyuzijte hodnoty hranove funkce E (x, y) z bodu P (x, y) */
	

	//////// DOPLNTE KOD /////////
	

	//Vyplnujeme vsechny vyhovujici body v obdelniku o rozmerech minX-maxX a minY a maxY.
	for (int y = minY; y <= maxY; y++)
	{
			//do temp si hodime vsechny hodnoty hranovych funkci.
			edgeFncValues_temp = edgeFncValues;

		for (int x = minX; x <= maxX; x++)
		{
			//Pri kazdem prejiti do cyklu for pro x, se nam eval nastavi na true
			bool eval = true;
	
			for (int i = 0; i < size; i++)
			{
				//Zjistime, zda vsechny aktualni hranove funkce jsou v kladne polorovine
				if (edgeFncValues_temp[i] < 0)
				{
					//Pri zjisteni, ze jedna hodnota je zaporna, je eval nastaveny na false
					eval = false;

				}
			}
			//Pokud jsme zjistili, ze vsechny hodnoty hranovych funkci jsou kladne (=eval je true)
			//Vykreslime dany bod.
			if (eval)
			{
				putPixel(x, y, color1);
			}
				
			
			for (int i = 0; i < size; i++)
			{
				edgeFncValues_temp[i] += edgeParams[i].deltaY;
			}
			//V teto casti vyuzivame vlastnosti, ze hodnota hranove funkce sousedniho bodu se lisi o deltaX/deltaY
			//Nicmene musime pricist tuto hodnotu vsem hodnotam, proto cykly for dokud i < size (size je pocet hran polygonu)
		}
		for (int i = 0; i < size; i++)
		{
			edgeFncValues[i] += edgeParams[i].deltaX;
		}
			
	}
    


    // Prekresleni hranic polygonu barvou color2.
    for (int i = 0; i < size; i++) {
        drawLine(points[i].x, points[i].y, points[(i + 1) % size].x, points[(i + 1) % size].y, color2/*, true*/);
    }
}
