#include <stdio.h>
#include <stdlib.h>


struct zespolona
{
	float dane_re;
	float dane_im;
};

struct element
{
	struct zespolona nowa_zespolona;
	struct element *poprzedni;
};

struct element *pierwszy(struct element *gora);
void push(struct element **gora, struct zespolona nowa_zespolona);
void pop(struct element **gora, struct zespolona *bufor);
void wyswietl_stos(struct element *gora);
void wartosci_stosu(struct element *gora);
void dodawanie(struct element **gora);
void odejmowanie(struct element **gora);
void mnozenie(struct element **gora);
void dzielenie(struct element **gora); 
struct element *wyczysc_stos(struct element **gora);
int czy_pusty(struct element *gora);

int main()
{
	struct element *gora = NULL;
	struct zespolona liczba;
	char tablica_pomocnicza[10];
	char znak = 0;
	float wynik_re, wynik_im;
	gora = pierwszy(gora);
	int test = 0;               //zmienna pomocnicza do sprawdzenia czy jest wystarczajaco liczb aby wykonac obliczenia

	do
	{
		system("cls");
		printf("Kalkulator liczb zespolonych\nProsze wprowadzic czesc rzeczywista, a po spacji czesc urojona liczby zespolonej.\nMinimalna ilosc liczb do wprowadzenia to 2.\nLiczby i operatory wprowadzaj osobno i zatwierdzaj enterem. \nWpisanie znaku 'C' spowoduje wyczyszczenie stosu, a 'X' zakonczy dzialanie programu.\n");
		wyswietl_stos(gora);
		gets(tablica_pomocnicza);

		if (sscanf(tablica_pomocnicza, "%f %f", &liczba.dane_re, &liczba.dane_im) == 2) // poprawnie wczytane dwa float sugeruja wczytanie liczby zespolonej
		{
			push(&gora, liczba);
			test++;
		}
		else
		{
			if (sscanf(tablica_pomocnicza, "%f %f", &liczba.dane_re, &liczba.dane_im) == 1) // wczytanie liczby zespolonej bez czesci urojonej
			{
				liczba.dane_im = 0;
				push(&gora, liczba);
				test++;
			}
			else // nie wczytanie float'a czyli wczytanie operatora lub blad lub koniec programu
			{
				sscanf(tablica_pomocnicza, "%c", &znak);
				if (znak == 'C')
				{
					wyczysc_stos(&gora);
					test = 0;
				}
				if (znak == 'E')
				{
					if (czy_pusty(gora) == 2)
					{
						wyczysc_stos(&gora);       //zwolnij pamiec gdy stos pelny
					}
					exit(0);
				}

				if (test >= 2)
				{
					if (znak == '+') // + '+'
					{
						dodawanie(&gora);
						test--;
					}
					if (znak == 45) // '-'
					{
						odejmowanie(&gora);
						test--;
					}
					if (znak == 42) // '*'
					{
						mnozenie(&gora);
						test--;
					}
					if (znak == 47 || znak == 92) // '/' lub '\'
					{
						dzielenie(&gora);
						test--;
					}
				}
			}
		}
	} while (znak != 'X');
}

struct element *pierwszy(struct element *gora)        // definicja pierwszego elementu stosu
{
	gora = malloc(sizeof(struct element));
	gora->poprzedni = NULL;
	return gora;
}

void push(struct element **gora, struct zespolona liczba)
{
	struct element *nowy_element;
	nowy_element = (struct element*)malloc(1 * sizeof(struct element));

	(*nowy_element).nowa_zespolona.dane_re = liczba.dane_re;
	(*nowy_element).nowa_zespolona.dane_im = liczba.dane_im;

	(*nowy_element).poprzedni = *gora;
	*gora = nowy_element;
}

void pop(struct element **gora, struct zespolona *bufor)
{
	struct element *tymczasowy;
	bufor->dane_re = (*gora)->nowa_zespolona.dane_re;
	bufor->dane_im = (*gora)->nowa_zespolona.dane_im;
	//*bufor = (*gora)->nowa_zespolona;
	if ((*gora)->poprzedni != NULL);
	tymczasowy = (*gora)->poprzedni;
	free(*gora);
	*gora = tymczasowy;
}

void wyswietl_stos(struct element *gora)
{
	printf("\nTwoj aktualny stan stosu:\n");
	do
	{
		if (gora->poprzedni == NULL)
		{
			printf("Stos pusty\n");
			break;
		}
		else
		{
			wartosci_stosu(gora);
			gora = gora->poprzedni;
			printf("\n");
		}
	} while (gora->poprzedni != NULL);
	printf("\nWprowadz dane: ");
}

void wartosci_stosu(struct element *gora)
{
	if ((*gora).nowa_zespolona.dane_im == 0)
		printf("%g", (*gora).nowa_zespolona.dane_re);                  //drukowanie tylko rzeczywistej gdy brak im
	else
	{
		if ((*gora).nowa_zespolona.dane_re == 0)
			printf("%gi", (*gora).nowa_zespolona.dane_im);             //drukowanie tylko im gdy brak re
		else
		{
			if ((*gora).nowa_zespolona.dane_im < 0)
				printf("%g%gi", (*gora).nowa_zespolona.dane_re, (*gora).nowa_zespolona.dane_im);       //ujemna im
			else
				printf("%g+%gi", (*gora).nowa_zespolona.dane_re, (*gora).nowa_zespolona.dane_im);      //dodatnia im
		}
	}
}

void dodawanie(struct element **gora)
{
	struct zespolona bufor1;
	struct zespolona bufor2;
	struct zespolona liczba;
	float wynik_re = 0, wynik_im = 0;

	pop(gora, &bufor1);
	pop(gora, &bufor2);
	wynik_re = bufor1.dane_re + bufor2.dane_re;
	wynik_im = bufor1.dane_im + bufor2.dane_im;
	liczba.dane_re = wynik_re;
	liczba.dane_im = wynik_im;
	push(gora, liczba);
}

void odejmowanie(struct element **gora)
{
	struct zespolona bufor1;
	struct zespolona bufor2;
	struct zespolona liczba;
	float wynik_re = 0, wynik_im = 0;

	pop(gora, &bufor1);
	pop(gora, &bufor2);
	wynik_re = bufor2.dane_re - bufor1.dane_re;
	wynik_im = bufor2.dane_im - bufor1.dane_im;
	liczba.dane_re = wynik_re;
	liczba.dane_im = wynik_im;
	push(gora, liczba);
}

void mnozenie(struct element **gora)
{
	struct zespolona bufor1;
	struct zespolona bufor2;
	struct zespolona liczba;
	float wynik_re = 0, wynik_im = 0;

	pop(gora, &bufor1);
	pop(gora, &bufor2);
	wynik_re = (bufor2.dane_re*bufor1.dane_re)-(bufor2.dane_im*bufor1.dane_im);
	wynik_im = (bufor2.dane_re*bufor1.dane_im) + (bufor1.dane_re*bufor2.dane_im);
	liczba.dane_re = wynik_re;
	liczba.dane_im = wynik_im;
	push(gora, liczba);
}

void dzielenie(struct element **gora)
{
	struct zespolona bufor1;
	struct zespolona bufor2;
	struct zespolona liczba;
	float wynik_re = 0, wynik_im = 0;

	pop(gora, &bufor1);
	pop(gora, &bufor2);

	if (bufor1.dane_im == 0 && bufor1.dane_re == 0)
	{
		printf("Nie mozna podzielic przez 0.\n");
		push(gora, bufor2);
		push(gora, bufor1);
		system("PAUSE");
	}
	else
	{
		wynik_re = (((bufor2.dane_re*bufor1.dane_re) + (bufor2.dane_im*bufor1.dane_im)) / ((bufor1.dane_re*bufor1.dane_re) + (bufor1.dane_im)*(bufor1.dane_im)));
		wynik_im = (((bufor2.dane_im*bufor1.dane_re) - (bufor2.dane_re*bufor1.dane_im)) / ((bufor1.dane_re*bufor1.dane_re) + (bufor1.dane_im)*(bufor1.dane_im)));
		liczba.dane_re = wynik_re;
		liczba.dane_im = wynik_im;
		push(gora, liczba);
	}
}

struct element *wyczysc_stos(struct element **gora)
{
	struct element *tymczasowy;

	while ((*gora)->poprzedni != NULL)
	{
		tymczasowy = (*gora)->poprzedni;
		free(*gora);
		*gora = tymczasowy;
	}
	return *gora;
}

int czy_pusty(struct element *gora)
{
	if (gora->poprzedni == NULL)          // funkcja zwroci jeden gdy stos jest pusty lub dwa gdy pelny
	{
		return 1;
	}
	else
	{
		return 2;
	}
}
