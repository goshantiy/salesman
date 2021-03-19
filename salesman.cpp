#include <iostream>
#include <time.h>
//Алгоритм полного перебора :
//• строим(генерируем, перечисляем) все возможные
//гамильтоновы циклы,
//• для каждого цикла подсчитываем стоимость
//и выбираем цикл наименьшей стоимости.
//Задача коммивояжера
//Перестановка – последовательность номеров вершин

int** RandomMatrix(int size, int min, int max)//случайная матрица размера size на отрезке[min:max]
{
	srand(time(0));
	int** Mat = NULL;
	if (size > 0)
	{
		Mat = new int* [size];
		if (Mat)
		{
			for (int i = 0; i < size; i++)
			{
				Mat[i] = new int[size];
				for (int j = 0; Mat[i][j] && j < size; j++)
				{
					Mat[i][j] = min + rand() % (max - min + 1);
					std::cout << Mat[i][j]<<' ';
				}
				std::cout << std::endl;
			}
		}
	}
	std::cout << std::endl;
	return Mat;
}
bool Pnext(int* hamilton, int n)//Алгоритм Дейкстры построения очередной перестановки
{

	for (int i = n - 2; i > 0; i--)
	{
		if (hamilton[i] < hamilton[i + 1])//находим i
		{
			int k = i + 1;
			for (int j = i + 1; j < n; j++)//находим j
			{
				if (hamilton[i] < hamilton[j] && hamilton[j] < hamilton[k])
					k = j;
			}

			hamilton[i] = hamilton[i] ^ hamilton[k];//меняем местами
			hamilton[k] = hamilton[i] ^ hamilton[k];
			hamilton[i] = hamilton[i] ^ hamilton[k];

			for (int ii = n - 1, kk = i + 1; ii > kk; ii--, kk++)//меняем порядок
			{
				hamilton[ii] = hamilton[ii] ^ hamilton[kk];
				hamilton[kk] = hamilton[ii] ^ hamilton[kk];
				hamilton[ii] = hamilton[ii] ^ hamilton[kk];
			}

			return true;
		}
	}
	return false;
}
bool Solution(int size, int startC, int** Matrix)
{
	if (size > 0) 
	{
		std::cout << "start from city: ";//начальный город
		std::cin >> startC;
		int* result = NULL;
		FILE* F = nullptr;
		int doPrint = 0;
		doPrint = fopen_s(&F, "result1.txt", "w");
		int i = 0;
		int distance = 0;
		int minDistance = 0;
		int* P = NULL;
		bool notEND = true;
		P = new int[size];//массив с номерами ячеек
		result = new int[size];//результирующий массив с номерами ячеек кратчайшего пути
		if (P && result)
		{
			P[0] = startC;//начальный город
			P[size] = startC;
			for (i = 1; i < size; i++)//заполняем начальный путь
			{
				P[i] = i;
				if (i >= startC)
					P[i]++;
			}
			while (notEND)
			{
				for (i = 0; i <= size; i++)
					doPrint = fprintf_s(F, "%d ", P[i]);//выводим очередной путь
				for (i = 0, distance = 0; i < size; i++)
				{
					distance = distance + Matrix[P[i] - 1][P[i + 1] - 1];//считаем дистанцию
				}
				if (minDistance == 0)
					minDistance = distance;
				doPrint = fprintf_s(F, ";	distance = %d \n", distance);
				if (minDistance >= distance)//устанавливаем минимальную дистанцию
				{
					minDistance = distance;
					for (i = 0; i <= size; i++)
						result[i] = P[i];//заполняем результирующий массив
				}
				notEND = Pnext(P, size);//перестановки
			}
			doPrint = fprintf_s(F, "\n\nMin distance = %d \n", minDistance);
			for (i = 0; i <= size; i++)
				doPrint = fprintf_s(F, "%d ", result[i]);//выводим минимальную дистанцию
		}
		return true;
	}
	return false;
}
int main()
{
	int size = 0, min = 0, max = 0;
	std::cout << "size: ";
	std::cin >> size;
	std::cout << "min: ";
	std::cin >> min;
	std::cout << "max: ";
	std::cin >> max;
	int** Matrix = NULL;
	Matrix = RandomMatrix(size, min, max);//создаем матрицу
	int startC = 0;
	Solution(size, startC, Matrix);
	delete[] Matrix;
}