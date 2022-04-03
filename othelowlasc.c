#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef enum { czarny, bialy } bool;//czarny to 0, bialy to 1

typedef struct plansza
{
    char* wartosci;
    bool czyj_ruch;

} plansza;


plansza utworz(int x)
{
    struct plansza p = { calloc(x * x, sizeof(char)), 0 };
    return p;
}

int oceny(plansza* p)
{
    int czarne = 0, biale = 0;
    for (int i = 0; i <= 7; i++)
    {
        for (int j = 0; j <= 7; j++)
        {
            if (p->wartosci[i * 8 + j] == 'X') czarne++;
            if (p->wartosci[i * 8 + j] == 'O') biale++;
        }
    }
    if (czarne + biale == 64 && biale > czarne) return -1;
    if (czarne + biale == 64 && biale < czarne) return  1;
    else return 0;

}

plansza ustawienie_poczatkowe()
{
    plansza ustawienie_poczatkowe = utworz(8);
    for (int i = 0; i <= 7; i++)
    {
        for (int j = 0; j <= 7; j++)
        {
            ustawienie_poczatkowe.wartosci[i * 8 + j] = '-';
        }
    }

    ustawienie_poczatkowe.wartosci[27] = 'O';
    ustawienie_poczatkowe.wartosci[28] = 'X';
    ustawienie_poczatkowe.wartosci[35] = 'X';
    ustawienie_poczatkowe.wartosci[36] = 'O';

    return ustawienie_poczatkowe;
}

void wypisz(plansza* plansza)
{
    printf("     A | B | C | D | E | F | G | H |\n");
    for (int i = 0; i <= 7; i++)
    {
        printf("  %d  ", i + 1);
        for (int j = 0; j <= 7; j++)
        {
            printf("%c   ", plansza->wartosci[i * 8 + j]);
        }
        printf("\n\n");
    }
}

void zwolnij_pamiec(struct plansza p)
{
    free(p.wartosci);
}


int* mozliwe_ruchy(plansza* p)
{
    int* tablica_pol_dozwolonych = calloc(64, sizeof(int));
    char znak1, znak2;
    if (p->czyj_ruch == 0)
    {
        znak1 = 'X';
        znak2 = 'O';
    }
    else
    {
        znak1 = 'O';
        znak2 = 'X';
    }
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {

            if (p->wartosci[i * 8 + j] == znak1)
            {
                if (p->wartosci[i * 8 + j + 1] == znak2)//prawo
                {
                    for (int k = 2; k < 8 - j; k++)
                    {
                        if (p->wartosci[i * 8 + j + k] == '-')
                        {
                            tablica_pol_dozwolonych[i * 8 + j + k] = 1;
                            break;
                        }
                        else if (p->wartosci[i * 8 + j + k] == znak1)
                        {
                            break;
                        }
                        else if (p->wartosci[i * 8 + j + k] == znak2)
                            continue;
                    }
                }

                if (p->wartosci[i * 8 + j - 1] == znak2)//lewo
                {
                    for (int k = 2; k <= j; k++)
                    {
                        if (p->wartosci[i * 8 + j - k] == '-')
                        {
                            tablica_pol_dozwolonych[i * 8 + j - k] = 1;
                            break;
                        }
                        else if (p->wartosci[i * 8 + j - k] == znak1)
                        {
                            break;
                        }
                        else if (p->wartosci[i * 8 + j - k] == znak2)
                            continue;
                    }
                }

                if (p->wartosci[(i - 1) * 8 + j] == znak2)//góra
                {
                    for (int k = 2; k <= i; k++)
                    {
                        if (p->wartosci[(i - k) * 8 + j] == '-')
                        {
                            tablica_pol_dozwolonych[(i - k) * 8 + j] = 1;
                            break;
                        }
                        else if (p->wartosci[(i - k) * 8 + j] == znak1)
                        {
                            break;
                        }
                        else if (p->wartosci[(i - k) * 8 + j] == znak2)
                            continue;
                    }
                }

                if (p->wartosci[(i + 1) * 8 + j] == znak2)//dół
                {
                    for (int k = 2; k < 8 - i; k++)
                    {
                        if (p->wartosci[(i + k) * 8 + j] == '-')
                        {
                            tablica_pol_dozwolonych[(i + k) * 8 + j] = 1;
                            break;
                        }
                        else if (p->wartosci[(i + k) * 8 + j] == znak1)
                        {
                            break;
                        }
                        else if (p->wartosci[(i + k) * 8 + j] == znak2)
                            continue;
                    }
                }

                if (p->wartosci[(i - 1) * 8 + j + 1] == znak2)//prawo góra + -
                {
                    for (int k = 2; k <= i && k < 8 - j; k++)
                    {
                        if (p->wartosci[(i - k) * 8 + j + k] == '-')
                        {
                            tablica_pol_dozwolonych[(i - k) * 8 + j + k] = 1;
                            break;
                        }
                        else if (p->wartosci[(i - k) * 8 + j + k] == znak1)
                        {
                            break;
                        }
                        else if (p->wartosci[(i - k) * 8 + j + k] == znak2)
                            continue;
                    }
                }

                if (p->wartosci[(i + 1) * 8 + j + 1] == znak2)//prawo dół + +
                {
                    for (int k = 2; k < 8 - i && k < 8 - j; k++)
                    {
                        if (p->wartosci[(i + k) * 8 + j + k] == '-')
                        {
                            tablica_pol_dozwolonych[(i + k) * 8 + j + k] = 1;
                            break;
                        }
                        else if (p->wartosci[(i + k) * 8 + j + k] == znak1)
                        {
                            break;
                        }
                        else if (p->wartosci[(i + k) * 8 + j + k] == znak2)
                            continue;
                    }
                }

                if (p->wartosci[(i + 1) * 8 + j - 1] == znak2)//lewo dół - +
                {
                    for (int k = 2; k < 8 - i && k <= j; k++)
                    {
                        if (p->wartosci[(i + k) * 8 + j - k] == '-')
                        {
                            tablica_pol_dozwolonych[(i + k) * 8 + j - k] = 1;
                            break;
                        }
                        else if (p->wartosci[(i + k) * 8 + j - k] == znak1)
                        {
                            break;
                        }
                        else if (p->wartosci[(i + k) * 8 + j - k] == znak2)
                            continue;
                    }
                }

                if (p->wartosci[(i - 1) * 8 + j - 1] == znak2)//lewo góra - -
                {
                    for (int k = 2; k <= i && k <= j; k++)
                    {
                        if (p->wartosci[(i - k) * 8 + j - k] == '-')
                        {
                            tablica_pol_dozwolonych[(i - k) * 8 + j - k] = 1;
                            break;
                        }
                        else if (p->wartosci[(i - k) * 8 + j - k] == znak1)
                        {
                            break;
                        }
                        else if (p->wartosci[(i - k) * 8 + j - k] == znak2)
                            continue;
                    }
                }
            }
        }
    }
    return tablica_pol_dozwolonych;
}

bool dupa;
int wybor_pola(plansza* p, int* sprawdzenie)//poruszanie - w a s d , zatwierdzenie wyboru-  r (uzylem kodu ascii)
{
    int i = 4, j = 4;//zaczynasz z punktu E5
    char tymczasowa = p->wartosci[i * 8 + j];// tu moga byc bledy logiczne
    char x;
    do
    {
        x = getchar();
        switch (x)
        {
        case 119: //gora
            p->wartosci[i * 8 + j] = tymczasowa;
            tymczasowa = p->wartosci[(i - 1) * 8 + j];
            p->wartosci[(i - 1) * 8 + j] = '@';
            i--;
            system("cls");
            wypisz(p);
            break;

        case 115: //dol
            p->wartosci[i * 8 + j] = tymczasowa;
            tymczasowa = p->wartosci[(i + 1) * 8 + j];
            p->wartosci[(i + 1) * 8 + j] = '@';
            i++;
            system("cls");
            wypisz(p);
            break;

        case 100: //prawo
            p->wartosci[i * 8 + j] = tymczasowa;
            tymczasowa = p->wartosci[i * 8 + j + 1];
            p->wartosci[i * 8 + j + 1] = '@';
            j++;
            system("cls");
            wypisz(p);
            break;

        case 97: //lewo
            p->wartosci[i * 8 + j] = tymczasowa;
            tymczasowa = p->wartosci[i * 8 + j - 1];
            p->wartosci[i * 8 + j - 1] = '@';
            j--;
            system("cls");
            wypisz(p);
            break;
        case 114: //r, czyli zatwierdzenie wyboru
            if (sprawdzenie[i * 8 + j] == 1)
            {
                if (p->czyj_ruch == 0)
                    p->wartosci[i * 8 + j] = 'X';
                else
                    p->wartosci[i * 8 + j] = 'O';
                dupa = 0;
                system("cls");
                //wypisz(p);
                break;
            }
            else
            {
                printf("ruch nie jest dozwolony \n");
                system("pause");
                p->wartosci[i * 8 + j] = tymczasowa;
                dupa = 1;
                //return -1;
                break;
            }
        }
    } while (x != 114);
    return i * 8 + j;
}

int ocena_ruchu(plansza* p, int a)
{
    int i = a / 8;
    int j = a % 8;
    int y = 0;
    char znak1, znak2;
    if (p->czyj_ruch == 0)
    {
        znak1 = 'X';
        znak2 = 'O';
    }
    else
    {
        znak1 = 'O';
        znak2 = 'X';
    }
    if (p->wartosci[i * 8 + j] == '-')
    {
        int rekordy[8] = { 0,0,0,0,0,0,0,0 };
        if (p->wartosci[(i * 8) + j + 1] == znak2)//prawo
        {
            for (int k = 2; k < 8 - j; k++)
            {
                if (p->wartosci[i * 8 + j + k] == '-')
                {
                    rekordy[0] = 0;
                    break;
                }
                else if (p->wartosci[i * 8 + j + k] == znak1)
                {
                    rekordy[0]++;
                    break;
                }
                else if (p->wartosci[i * 8 + j + k] == znak2)
                {
                    rekordy[0]++;
                    continue;
                }
            }
        }

        if (p->wartosci[(i * 8) + j - 1] == znak2)//lewo
        {
            for (int k = 2; k < j; k++)
            {
                if (p->wartosci[i * 8 + j - k] == '-')
                {
                    rekordy[1] = 0;
                    break;
                }
                else if (p->wartosci[i * 8 + j - k] == znak1)
                {
                    rekordy[1]++;
                    break;
                }
                else if (p->wartosci[i * 8 + j - k] == znak2)
                {
                    rekordy[1]++;
                    continue;
                }
            }
        }

        if (p->wartosci[(i - 1) * 8  + j] == znak2)//góra
        {
            for (int k = 2; k < i; k++)
            {
                if (p->wartosci[((i - k) * 8) + j] == '-')
                {
                    rekordy[2] = 0;
                    break;
                }
                else if (p->wartosci[((i - k) * 8) + j] == znak1)
                {
                    rekordy[2]++;
                    break;
                }
                else if (p->wartosci[((i - k) * 8) + j] == znak2)
                {
                    rekordy[2]++;
                    continue;
                }
            }
        }

        if (p->wartosci[((i - 1) * 8) + j] == znak2)//dół
        {
            for (int k = 2; k < 8 - i; k++)
            {
                if (p->wartosci[((i + k) * 8) + j] == '-')
                {
                    rekordy[3] = 0;
                    break;
                }
                else if (p->wartosci[((i + k) * 8) + j] == znak1)
                {
                    rekordy[3]++;
                    break;
                }
                else if (p->wartosci[((i + k) * 8) + j] == znak2)
                {
                    rekordy[3]++;
                    continue;
                }
            }
        }

        if (p->wartosci[((i - 1) * 8) + j + 1] == znak2)//prawo góra + -
        {
            for (int k = 2; k < i && k < 8 - j; k++)
            {
                if (p->wartosci[((i - k) * 8) + j + k] == '-')
                {
                    rekordy[4] = 0;
                    break;
                }
                else if (p->wartosci[((i - k) * 8) + j + k] == znak1)
                {
                    rekordy[4]++;
                    break;
                }
                else if (p->wartosci[((i - k) * 8) + j + k] == znak2)
                {
                    rekordy[4]++;
                    continue;
                }
            }
        }

        if (p->wartosci[((i + 1) * 8) + j + 1] == znak2)//prawo dół + +
        {
            for (int k = 2; k < 8 - i && k < 8 - j; k++)
            {
                if (p->wartosci[((i + k) * 8) + j + k] == '-')
                {
                    rekordy[5] = 0;
                    break;
                }
                else if (p->wartosci[((i + k) * 8) + j + k] == znak1)
                {
                    rekordy[5]++;
                    break;
                }
                else if (p->wartosci[((i + k) * 8) + j + k] == znak2)
                {
                    rekordy[5]++;
                    continue;
                }
            }
        }

        if (p->wartosci[((i + 1) * 8) + j - 1] == znak2)//lewo dół - +
        {
            for (int k = 2; k < 8 - i && k < j; k++)
            {
                if (p->wartosci[((i + k) * 8) + j - k] == '-')
                {
                    rekordy[6] = 0;
                    break;
                }
                else if (p->wartosci[((i + k) * 8) + j - k] == znak1)
                {
                    rekordy[6]++;
                    break;
                }
                else if (p->wartosci[((i + k) * 8) + j - k] == znak2)
                {
                    rekordy[6]++;
                    continue;
                }
            }
        }

        if (p->wartosci[((i - 1) * 8) + j - 1] == znak2)//lewo góra - -
        {
            for (int k = 2; k < i && k < j; k++)
            {
                if (p->wartosci[((i - k) * 8) + j - k] == '-')
                {
                    rekordy[7] = 0;
                    break;
                }
                else if (p->wartosci[((i - k) * 8) + j - k] == znak1)
                {
                    rekordy[7]++;
                    break;
                }
                else if (p->wartosci[((i - k) * 8) + j - k] == znak2)
                {
                    rekordy[7]++;
                    continue;
                }
            }
        }
        for (int x = 0; x < 8; x++)  y = y + rekordy[x];
    }
    if (p->czyj_ruch == 0) return -y;
    else return y;
}


plansza bicie(plansza* p, int iloczyn)
{
    char znak1, znak2;
    if (p->czyj_ruch == 0)
    {
        znak1 = 'X';
        znak2 = 'O';
    }
    else
    {
        znak1 = 'O';
        znak2 = 'X';
    }
    int i, j;
    i = iloczyn / 8;
    j = iloczyn % 8;
    if (p->wartosci[i * 8 + j] == znak1)
    {
        if (p->wartosci[i * 8 + j + 1] == znak2)//prawo
        {
            for (int k = 2; k < 8 - j; k++)
            {
                if (p->wartosci[i * 8 + j + k] == znak1)
                {
                    while (k > 0)
                    {
                        k--;
                        p->wartosci[i * 8 + j + k] = znak1;
                    }
                    break;
                }
                else if (p->wartosci[i * 8 + j + k] == '-')
                {
                    break;
                }
                else if (p->wartosci[i * 8 + j + k] == znak2)
                    continue;
            }
        }

        if (p->wartosci[i * 8 + j - 1] == znak2)//lewo
        {
            for (int k = 2; k < j; k++)
            {
                if (p->wartosci[i * 8 + j - k] == znak1)
                {
                    while (k > 0)
                    {
                        k--;
                        p->wartosci[i * 8 + j - k] = znak1;
                    }
                    break;
                }
                else if (p->wartosci[i * 8 + j - k] == '-')
                {
                    break;
                }
                else if (p->wartosci[i * 8 + j - k] == znak2)
                    continue;
            }
        }

        if (p->wartosci[(i - 1) * 8 + j] == znak2)//góra
        {
            for (int k = 2; k < i; k++)
            {
                if (p->wartosci[(i - k) * 8 + j] == znak1)
                {
                    while (k > 0)
                    {
                        k--;
                        p->wartosci[(i - k) * 8 + j] = znak1;
                    }
                    break;
                }
                else if (p->wartosci[(i - k) * 8 + j] == '-')
                {
                    break;
                }
                else if (p->wartosci[(i - k) * 8 + j] == znak2)
                    continue;
            }
        }

        if (p->wartosci[(i + 1) * 8 + j] == znak2)//dół
        {
            for (int k = 2; k < 8 - i; k++)
            {
                if (p->wartosci[(i + k) * 8 + j] == znak1)
                {
                    while (k > 0)
                    {
                        k--;
                        p->wartosci[(i + k) * 8 + j] = znak1;
                    }
                    break;
                }
                else if (p->wartosci[(i + k) * 8 + j] == '-')
                {
                    break;
                }
                else if (p->wartosci[(i + k) * 8 + j] == znak2)
                    continue;
            }
        }

        if (p->wartosci[(i - 1) * 8 + j + 1] == znak2)//prawo góra + -
        {
            for (int k = 2; k < i && k < 8 - j; k++)
            {
                if (p->wartosci[(i - k) * 8 + j + k] == znak1)
                {
                    while (k > 0)
                    {
                        k--;
                        p->wartosci[(i - k) * 8 + j + k] = znak1;
                    }
                    break;
                }
                else if (p->wartosci[(i - k) * 8 + j + k] == '-')
                {
                    break;
                }
                else if (p->wartosci[(i - k) * 8 + j + k] == znak2)
                    continue;
            }
        }

        if (p->wartosci[(i + 1) * 8 + j + 1] == znak2)//prawo dół + +
        {
            for (int k = 2; k < 8 - i && k < 8 - j; k++)
            {
                if (p->wartosci[(i + k) * 8 + j + k] == znak1)
                {
                    while (k > 0)
                    {
                        k--;
                        p->wartosci[(i + k) * 8 + j + k] = znak1;
                    }
                    break;
                }
                else if (p->wartosci[(i + k) * 8 + j + k] == '-')
                {
                    break;
                }
                else if (p->wartosci[(i + k) * 8 + j + k] == znak2)
                    continue;
            }
        }

        if (p->wartosci[(i + 1) * 8 + j - 1] == znak2)//lewo dół - +
        {
            for (int k = 2; k < 8 - i && k < j; k++)
            {
                if (p->wartosci[(i + k) * 8 + j - k] == znak1)
                {
                    while (k > 0)
                    {
                        k--;
                        p->wartosci[(i + k) * 8 + j - k] = znak1;
                    }
                    break;
                }
                else if (p->wartosci[(i + k) * 8 + j - k] == '-')
                {
                    break;
                }
                else if (p->wartosci[(i + k) * 8 + j - k] == znak2)
                    continue;
            }
        }

        if (p->wartosci[(i - 1) * 8 + j - 1] == znak2)//lewo góra - -
        {
            for (int k = 2; k < i && k < j; k++)
            {
                if (p->wartosci[(i - k) * 8 + j - k] == znak1)
                {
                    while (k > 0)
                    {
                        k--;
                        p->wartosci[(i - k) * 8 + j - k] = znak1;
                    }
                    break;
                }
                else if (p->wartosci[(i - k) * 8 + j - k] == '-')
                {
                    break;
                }
                else if (p->wartosci[(i - k) * 8 + j - k] == znak2)
                    continue;
            }
        }
    }

    return *p;
}

void ruch_bota(plansza p, int glebokosc)
{
    int a = plansze(p, glebokosc);
    p.czyj_ruch = !p.czyj_ruch;
    printf("%d ", a);
    p.wartosci[(a / 8) * 8 + a % 8] = 'O';
    bicie(&p, a);
    p.czyj_ruch = !p.czyj_ruch;
}

int plansze(plansza p, int glebokosc)
{
    if (glebokosc == 0) return 0;
    else
    {
        int najwyzsza_ocena = 0;
        int miejsce = 0;
        int ocena_galezi = 0;
        plansza plan;
        //memcpy(&plan, &p, sizeof(plansza));
        plan.wartosci = calloc(64, sizeof(char));
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                plan.wartosci[i * 8 + j] = p.wartosci[i * 8 + j];
            }
        }
        if (p.czyj_ruch == 0) plan.czyj_ruch = 1;
        else plan.czyj_ruch = 0;

        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if (ocena_ruchu(&plan, i * 8 + j) != 0)
                {
                    ocena_galezi += ocena_ruchu(&plan, i * 8 + j);
                    //printf("ocena ruchu: %d\n", ocena_ruchu(&plan, i * 8 + j));
                    if (plan.czyj_ruch == 0)
                    {
                        plan.wartosci[i * 8 + j] = 'X';
                        bicie(&plan, i * 8 + j);
                        ocena_galezi += plansze(plan, glebokosc - 1);
                        //wypisz(&plan);
                    }
                    if (plan.czyj_ruch == 1)
                    {
                        plan.wartosci[i * 8 + j] = 'O';
                        bicie(&plan, i * 8 + j);
                        ocena_galezi += plansze(plan, glebokosc - 1);
                        //wypisz(&plan);
                    }
                    for (int a = 0; a < 8; a++)
                    {
                        for (int b = 0; b < 8; b++)
                        {
                            plan.wartosci[a * 8 + b] = p.wartosci[a * 8 + b];
                        }
                    }
                    if (ocena_galezi > najwyzsza_ocena)
                    {
                        najwyzsza_ocena = ocena_galezi;
                        miejsce = i * 8 + j;
                    }
                    ocena_galezi = 0;
                }

            }
        }
        return miejsce;
    }
}

int main()
{
    plansza p = utworz(8);
    plansza ustawienie_pocz = ustawienie_poczatkowe();
    p = ustawienie_pocz;
    wypisz(&p);
    //int a;
    do
    {
        int* tablica = calloc(64, sizeof(int));
        tablica = mozliwe_ruchy(&p);
        //for (int i = 0; i < 8; i++)
        //{
        //    for (int j = 0; j < 8; j++)
        //    {
        //        printf(" %d ", *(tablica + i * 8 + j));
        //    }printf("\n");
        //}
        do
        {
            bicie(&p, wybor_pola(&p, tablica));
        } while (dupa == 1);
        //plansze(p, 5);
        //printf("%d", plansze(p, 1));
        ruch_bota(p, 1);
        free(tablica);
        system("cls");
        wypisz(&p);
        if (oceny(&p) == -1)
        {
            //system("cls");
            printf("komputer wygral leszczu");
            break;
        }
        else if (oceny(&p) == 1)
        {
            //system("cls");
            printf("jestes zwyciezca!");
            break;
        }
    } while (oceny(&p) == 0);
    zwolnij_pamiec(p);
    return 0;
}

