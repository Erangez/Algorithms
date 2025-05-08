#include <iostream>
#include <Windows.h>
#include <time.h>
#include <vector>
using namespace std;
vector<int> generate_array(int range, int key) {
	/*
	0. - Случайная генерация
	1. - Генерация с сортировкой по возрастанию
	2. - Генерация с сортировкой по убыванию
	*/
	vector<int> arr(range);
	srand(time(NULL));
	switch (key) {
		case 0:
			for (int i = 0; i < range; i++) {
				arr[i] = -50000 + rand() % (50000 + 50000 + 1);
			}
			break;
		case 1:
			arr[0] = -50000;
			for (int i = 1; i < range; i++) {
				arr[i] = arr[i - 1] + (0 + rand() % (10 - 0 + 1));
			}
			break;
		case 2:
			arr[0] = 50000;
			for (int i = 1; i < range; i++) {
				arr[i] = arr[i - 1] - (0 + rand() % (10 - 0 + 1));
			}
			break;
		default:
			cout << "Неправильно задан ключ генерации.\n";
			break;
	}
	return arr;
}
void show(vector<int> arr) {
	for (int i = 0; i < size(arr); i++) {
		cout << arr[i] << " ";
	}
}
float task_one(vector<int>& arr, int key) {
	switch (key) {
	case 0:
		cout << "1) Сортировка вставками. 0 - Обычный случай.\n\n";
		break;
	case 1:
		cout << "1) Сортировка вставками. 1 - Наилучший случай.\n\n";
		break;
	case 2:
		cout << "1) Сортировка вставками. 2 - Худший случай.\n\n";
		break;
	}
	
	//show(arr);
	cout << "\nМассив завершился.\n";
	cout << "\n-----Сортировка-----\n";
	clock_t start = clock();
	int value, j;
	for (int i = 1; i < size(arr); i++) {
		value = arr[i];
		j = i - 1;
		while (j >= 0 && arr[j] > value) {
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = value;
	}
	clock_t end = clock();
	float time = (float)(end - start) / CLOCKS_PER_SEC;
	cout << "Отсортированный массив:\n";
	//show(arr);
	cout << "\nВремя сортировки: " << time << " с\n";
	return time;
}
void heap(vector<int>& arr, int len, int i) {
	int root_id = i;
	int left_id = 2 * i + 1;
	int right_id = 2 * i + 2;
	if (left_id < len && arr[left_id] > arr[root_id]) {
		root_id = left_id;
	}
	if (right_id < len && arr[right_id] > arr[root_id]) {
		root_id = right_id;
	}
	if (root_id != i) {
		swap(arr[i], arr[root_id]);
		heap(arr, len, root_id);
	}
}
float task_two(vector<int>& arr, int key) {
	switch (key) {
	case 0:
		cout << "2) Пирамидальная сортировка. 0 - Обычный случай.\n\n";
		break;
	case 1:
		cout << "2) Пирамидальная сортировка. 1 - Наилучший случай.\n\n";
		break;
	case 2:
		cout << "2) Пирамидальная сортировка. 2 - Худший случай.\n\n";
		break;
	}
	//show(arr);
	cout << "\nМассив завершился.\n";
	cout << "\n-----Сортировка-----\n";
	clock_t start = clock();
	int len = size(arr);
	for (int i = len / 2 - 1; i >= 0; i--) {
		heap(arr, len, i);
	}
	for (int i = len - 1; i > 0; i--) {
		swap(arr[i], arr[0]);
		heap(arr, i, 0);
	}
	clock_t end = clock();
	float time = (float)(end - start) / CLOCKS_PER_SEC;
	cout << "Отсортированный массив:\n";
	//show(arr);
	cout << "\nВремя сортировки: " << time << " с\n";
	return time;
}
float task_three(vector<int>& arr, int key) {
	switch (key) {
	case 0:
		cout << "3) Сортировка обменом. 0 - Обычный случай.\n\n";
		break;
	case 1:
		cout << "3) Сортировка обменом. 1 - Наилучший случай.\n\n";
		break;
	case 2:
		cout << "3) Сортировка обменом. 2 - Худший случай.\n\n";
		break;
	}
	//show(arr);
	cout << "\nМассив завершился.\n";
	cout << "\n-----Сортировка-----\n";
	clock_t start = clock();
	for (int i = 0; i < size(arr) - 1; i++) {
		for (int j = 0; j < size(arr) - 1 - i; j++) {
			if (arr[j] > arr[j + 1]) {
				swap(arr[j], arr[j + 1]);
			}
		}
	}
	clock_t end = clock();
	float time = (float)(end - start) / CLOCKS_PER_SEC;
	cout << "Отсортированный массив:\n";
	//show(arr);
	cout << "\nВремя сортировки: " << time << " с\n";
	return time;
}
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	cout << "На данном этапе сгенерируется 3 массива, " <<
		"заполненными нормальным, наилучшим и наихудим способами.\n";
	cout << "Введите размер массивов:\n";
	int range;
	cout << ">> ";
	cin >> range;
	
	float times_1[3]{};
	float times_2[3]{};
	float times_3[3]{};

	vector<int> arr_0(generate_array(range, 0));
	vector<int> arr_1(generate_array(range, 1));
	vector<int> arr_2(generate_array(range, 2));

	times_1[0] = task_one(arr_0, 0);
	times_1[1] = task_one(arr_1, 1);
	times_1[2] = task_one(arr_2, 2);
	
	times_2[0] = task_two(arr_0, 0);
	times_2[1] = task_two(arr_1, 1);
	times_2[2] = task_two(arr_2, 2);

	times_3[0] = task_three(arr_0, 0);
	times_3[1] = task_three(arr_1, 1);
	times_3[2] = task_three(arr_2, 2);
	cout << "\n----------Статистика----------\n";
	cout << "\t" << "Нормальный \t" << "Лучший \t" << "Худший \n";
	cout << "1. Алг\t" << times_1[0] << "\t\t" << times_1[1] << "\t" << times_1[2] << "\n";
	cout << "2. Алг\t" << times_2[0] << "\t\t" << times_2[1] << "\t" << times_2[2] << "\n";
	cout << "3. Алг\t" << times_3[0] << "\t\t" << times_3[1] << "\t" << times_3[2] << "\n";
	return 0;
}