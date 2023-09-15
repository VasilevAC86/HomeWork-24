# include <iostream>
#include<cstdlib>
#include<ctime>

void exam_Size(short& size); // Процедура проверки размера массива и, в случае некорректного ввода, замена его значения
void filling_Array(int darr[], short length); // Процедура заполнения массива (вручную или рандомно)
void print_Array(int darr[], short length); // Процедура вывода массива в консоль
void resize_Arr(int*& darr, short length, short n); // Процедура изменения длины массива

int main() {

	// Задача 1. Объединение двух динамических массивов		
	std::cout << "\033[91mTask 1. Merging two dynamic arrays\033[0m\n\nEnter the size of the first array -> ";
	short sizeA, sizeB;
	std::cin >> sizeA;
	exam_Size(sizeA);	
	std::cout << std::endl << "Enter the size of the second array -> ";
	std::cin >> sizeB;
	exam_Size(sizeB);
	int* darrA = new int[sizeA]; // Выделяем область динамической памяти размером sizeA типа int под указатель * darrA
	int* darrB = new int[sizeB]; // Выделяем область динамической памяти размером sizeB типа int под указатель * darrB
	std::cout << "\n\033[93mFilling the first array\033[0m";
	filling_Array(darrA, sizeA);
	std::cout << "\n\033[93mFilling the second array\033[0m";
	filling_Array(darrB, sizeB);
	std::cout << "\n\033[93mFirst array is: \033[0m";
	print_Array(darrA, sizeA);
	std::cout << "\n\033[93mSecond array is: \033[0m";
	print_Array(darrB, sizeB);
	int* darrC = new int[sizeA + sizeB]; // Выделяем область динамической памяти под указатель * darrC
	for (short i = 0; i < sizeA; i++) // Цикл заполнения массива С элемнетами массива А
		darrC[i] = darrA[i];
	for (short i = 0; i < sizeB; i++) // Цикл заполнения массива С элемнетами массива В
		darrC[i + sizeA] = darrB[i];
	std::cout << std::endl << "\033[92mFinal array is: \033[0m";
	print_Array(darrC, sizeA + sizeB);
	std::cout << std::endl;
	delete[] darrA; // Чистим динамическую память от массива A
	darrA = nullptr; // Указалель darrA перенаправляем на нейтральный статус
	delete[] darrB; // Чистим динамическую память от массива В
	darrB = nullptr; // Указалель darrB перенаправляем на нейтральный статус

	// Задача 2. Изменение размера массива
	std::cout << "\033[91mTask 2. Changing the array's size\033[0m\n\nEnter the size of array -> ";
	short size;
	std::cin >> size;
	exam_Size(size);
	int* darr = new int[size]; // Выделяем область динамической памяти размером size типа int под указатель * darr
	filling_Array(darr, size);
	std::cout << "\n\033[93mSource array is: \033[0m";
	print_Array(darr, size);
	std::cout << "\nEnter the number by which you want to resize the array -> ";
	short n;
	std::cin >> n;
	if (n<0)
		while (abs(n) >= size) {
			std::cout << "Input error! Array's size can't be negative or zero!\nEnter the number by which you want to resize the array -> ";
			std::cin >> n;
		}
	resize_Arr(darr, size, n);
	std::cout << "\n\033[92mFinal array is: \033[0m";
	print_Array(darr, size + n);	

	return 0;
}

void exam_Size(short& size) {
	while (size <= 0) {
		std::cout << "Input errro! The array's size must be greater than zero!\nEnter the size of the array -> ";
		std::cin >> size;
	}
}

void filling_Array(int darr[], short length) {
	char my_Choise;
	std::cout << "\nChoose how array will filling: press '0' to enter array elements manually \033[4m\033[94mor\033[0m press any other key to random filling.\nYour choise -> ";
	std::cin >> my_Choise;
	switch (my_Choise) {
	case '0':
		for (short i = 0; i < length; i++) {
			std::cout << "Enter array's element N " << i + 1 << " = ";
			std::cin >> darr[i];
		}
		break;
	default:
		int start, end; // Переменные для хранения начала и конца диапазона
		std::cout << "Enter the range of randon numbers:\nenter the start of the range = ";
		std::cin >> start;
		std::cout << "Enter the end of the range = ";
		std::cin >> end;
		while (end <= start) {
			std::cout << "Input error! The end of the the range can't be less when the start!\nEnter the start of the range = ";
			std::cin >> start;
			std::cout << "Enter the end of the range = ";
			std::cin >> end;
		}
		srand(time(NULL));
		for (short i = 0; i < length; i++)
			darr[i] = rand() % (end - start) + start;
	}
}

void print_Array(int darr[], short length) {
	std::cout << "{ ";
	for (short i = 0; i < length; i++)
		std::cout << darr[i] << ", ";
	std::cout << "\b\b }\n";
}

void resize_Arr(int*& darr, short length, short n) {
	short size = length + n; // Длина нового массива
	int* dtmp = new int[size]{}; // Выделяем область динамической памяти размером size типа int под указатель * dtmp, заполняем ячейки памяти 0
	for (short i = 0; i < size; i++) // Цикл перезаписи массива dtmp соответствующими значениями массива arr или 0, если length <= size
		if (i < length)
			dtmp[i] = darr[i];
		else
			dtmp[i] = 0;
	delete[] darr; // Чистим область памяти, в которой хранится исходный массив arr[]
	darr = dtmp; // Перенапраляем указатель arr с уже пустой области памяти на область памяти, в которой хранится массив dtmp
	dtmp = nullptr; // Указатель dtmp перенаправляем на нейтральный статус, хотя он будет уничтожен после выхода из процедуры
}