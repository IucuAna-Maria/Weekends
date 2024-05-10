#include <stdio.h>
#include <stdbool.h>

FILE* f;

typedef enum zi_saptamana
{
	Luni,
	Marti,
	Miercuri,
	Joi,
	Vineri,
	Sambata,
	Duminica,
}zi_saptamana;

typedef enum luna_an
{
	Ianuarie,
	Februarie,
	Martie,
	Aprilie,
	Mai,
	Iunie,
	Iulie,
	August,
	Septembrie,
	Octombrie,
	Noiembrie,
	Decembrie
}luna_an;

typedef struct
{
	zi_saptamana zi_saptamana;
	unsigned int zi_luna;
	luna_an luna;
	unsigned int an;
}data_calendar;

/* functia bool returneaza true cand anul este bisect si false cand anul nu este bisect */
bool este_an_bisect(unsigned int an)
{
	if (an % 400 == 0)
	{
		return true;
	}
	else
	{
		if (an % 4 == 0)
		{
			if (an % 100 == 0)
			{
				return false;
			}
			else
			{
				return true;
			}
		}
		else
		{
			return false;
		}
	}
}

/* scriem fiecare luna cate zile are */
unsigned int numar_zile_luna(luna_an luna, unsigned int an)
{
	switch (luna)
	{
	case Aprilie:
	case Iunie:
	case Septembrie:
	case Noiembrie:
		return 30;
	case Februarie:
		if (este_an_bisect(an)) /*daca este an bisect februarie va avea 29 de zile, altfel va avea 28 de zile */
		{
			return 29;
		}
		else
		{
			return 28;
		}
	default:
		return 31;
	}
}

/* functia se foloseste pentru a creste ziua atunci cand se cauta nr de weekend-uri */
void incrementeaza_zi_saptamana(zi_saptamana* zi)
{
	if (*zi == Duminica)
	{
		*zi = Luni;
	}
	else
	{
		++(*zi);
	}
}

/* functia se foloseste pentru a creste luna atunci cand se cauta nr de weekend-uri */
void incrementeaza_luna(luna_an* luna)
{
	if (*luna == Decembrie)
	{
		*luna = Ianuarie;
	}
	else
	{
		++(*luna);
	}
}

/* functia se foloseste pentru a creste anul atunci cand se cauta nr de weekend-uri */
void incrementeaza_data(data_calendar* data)
{
	if (data->zi_luna == numar_zile_luna(data->luna, data->an))
	{
		data->zi_luna = 1;

		if (data->luna == Decembrie)
		{
			++(data->an);
		}

		incrementeaza_luna(&(data->luna));
	}
	else
	{
		++(data->zi_luna);
	}

	incrementeaza_zi_saptamana(&(data->zi_saptamana));
}

/* cu ajutorul acestei functii se vor compara doua date */
int data_cmp(const data_calendar* lhs, const data_calendar* rhs)
{
	if (lhs->an != rhs->an)
	{
		if (lhs->an < rhs->an)
		{
			return -1;
		}
		else
		{
			return 1;
		}
	}
	else
	{
		if (lhs->luna != rhs->luna)
		{
			if (lhs->luna < rhs->luna)
			{
				return -1;
			}
			else
			{
				return 1;
			}
		}
		else
		{
			if (lhs->zi_luna != rhs->zi_luna)
			{
				if (lhs->zi_luna < rhs->zi_luna)
				{
					return -1;
				}
				else
				{
					return 1;
				}
			}
			else
			{
				return 0;
			}
		}
	}
}

/* functia ziua_saptamanii calculeaza in ce zi a saptamanii (luni, marti, ... , duminica) pica data citita */
int ziua_saptamanii(int d, int m, int y)
{
	static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
	y -= m < 3;
	return (y + y / 4 - y / 100 + y / 400 + t[m - 1] + d) % 7;
}

/* citim data din fisier */
data_calendar citeste_input()
{
	data_calendar data;
	int aux;

	fscanf(f, "%u", &data.zi_luna);
	fscanf(f, "%u", &aux);
	data.luna = aux - 1;
	fscanf(f, "%u", &data.an);
	aux = ziua_saptamanii(data.zi_luna, data.luna + 1, data.an);
	data.zi_saptamana = aux - 1;

	return data;
}

int main()
{
	f = fopen("in.txt", "rt");

	if (f == NULL)
	{
		printf("Fisierul nu se poate deschide!");
		exit(0);
	}

	const data_calendar data_1 = citeste_input(); //citeste prima data

	const data_calendar data_2 = citeste_input(); //citeste a doua data
	fclose(f);

	data_calendar it = data_1;
	data_calendar aux;
	unsigned int weekend_counter = 0;

	bool inceput_weekend = false;

	/* cautam toate weekend-urile intre cele doua date */
	while (data_cmp(&it, &data_2) < 1)
	{
		/* daca se gaseste sambata urmata de duminica se va considera un weekend, iar counter-ul va creste */
		if (it.zi_saptamana == Sambata)
		{
			inceput_weekend = true;
			aux = it;
		}
		if (it.zi_saptamana == Duminica && inceput_weekend)
		{
			inceput_weekend = false;
			++weekend_counter;
		}
		incrementeaza_data(&it);
	}

	f = fopen("out.txt", "wt");

	if (f == NULL)
	{
		printf("Fisierul nu a putut fi creat");
		exit(0);
	}

	fprintf(f, "%u", weekend_counter); /* la final afisam in fisier numarul de weekend-uri */

	printf("Datele au fost scrise cu succes in fisierul out.txt!\n");

	fclose(f);
	return 0;
}