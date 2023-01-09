#include "../../Library.h"

#define POSUNy   2
#define POSUNx   7

void xy(int x, int y)		     // xy(x, y);
{
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

bool spusteno = false;

void TvorbaTabulky() {
    if (!spusteno) {
        cout << "Grade |Weight|\n";
        spusteno = true;
    }
    cout << "      |      |\n";
    cout << "------|------|-\n";
}


class TGrade {
public:
    int vaha;
    int znamka;
    TGrade(float vaha, int znamka) {
        this->vaha = int(vaha * 100);
        this->znamka = znamka;
    }
};

float ZaokrouhlitF(float x) {
    return roundf(x * 100.0f)/100.0f;
}

int main()
{
    float suma = 0.0f;
    float sumaZnamky = 0.0f;
    int pomI;
    float pomF;
    int pocetZnamek = 0;
    int poziceZapisu = 0;
    cout << "Pro pridani nove znamky CAPS | pro ukonceni a spocitani BACK\n\n";
    
    do {
        while (GetAsyncKeyState(VK_CAPITAL)) {
            Sleep(100);
            
            TvorbaTabulky();

            xy(1 + POSUNx * poziceZapisu, 3 + POSUNy * pocetZnamek);
            cin >> pomI;
            poziceZapisu++;
            xy(1 + POSUNx * poziceZapisu, 3 + POSUNy * pocetZnamek);
            cin >> pomF;
            pocetZnamek++;
            TGrade* Znamka = new TGrade(pomF, pomI);
            poziceZapisu = 0;
            suma += float(Znamka->vaha / 25 * Znamka->znamka);
            sumaZnamky += float(Znamka->vaha / 25);
            delete Znamka;
            xy(POSUNx * poziceZapisu, 3 + POSUNy * pocetZnamek);
        }
    } while (!GetAsyncKeyState(VK_BACK));

    if (sumaZnamky == 0.0f) {
        return 0;
    }
    float vysledek = suma / sumaZnamky;
    vysledek = ZaokrouhlitF(vysledek);
    xy(19+POSUNx * poziceZapisu, 3 + POSUNy * pocetZnamek);
    cout << vysledek;
}