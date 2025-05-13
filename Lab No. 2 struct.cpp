#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <random>
#include <fstream>

using namespace std;
// Глобальные переменные
string brands[10] = { "Mazda", "Lada", "Honda", "Audi", "Toyota", "Hyundai", "BMW", "Renault", "Opel", "Volvo" };
string colors[7] = { "Красный", "Чёрный", "Белый", "Серый", "Синий", "Жёлтый", "Голубой" };
string body_types[5] = { "Седан", "Внедорожник","Хэтчбек", "Универсал", "Лифтбек" };
string gearboxes[4] = { "Механика", "Автомат", "Робот", "Вариатор" };

struct car {
	int year_of_release;
	int price;
	int mileage;
	string brand;
	string color;
	string body_type;
	string gearbox;

};

int random_number(int min_range, int max_range) {
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> distrib(min_range, max_range);
	return distrib(gen);
}
void base_fill(car &obj) {
	obj.year_of_release = random_number(2006, 2024);
	obj.price = random_number(650000, 4600000);
	obj.mileage = random_number(40000, 240000);
	obj.brand = brands[random_number(0, 9)];
	obj.color = colors[random_number(0, 6)];
	obj.body_type = body_types[random_number(0, 4)];
	obj.gearbox = gearboxes[random_number(0, 3)];
}


void show_data(car &obj) {
	cout << "Модель: " << obj.brand << "\tГод выпуска: " << obj.year_of_release << "\tЦвет: " << obj.color << "\tТип кузова : " << obj.body_type << "\n";
	cout << "Цена: " << obj.price << " RUB" << "\tПробег: " << obj.mileage << " км" << "\t" << "\tКоробка: " << obj.gearbox << "\n\n";
}
int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	const int car_amount = 80;
	const int MENU_1 = 49;
	const int MENU_2 = 50;
	const int MENU_3 = 51;
	const int MENU_4 = 52;
	const int MENU_5 = 53;
	const int MENU_6 = 54;
	const int MENU_7 = 55;
	const int MENU_8 = 56;
	const int MENU_EXIT = 27;

	car cars[car_amount];
	int req = 0;

	while (req != MENU_EXIT) {
		system("cls");
		cout << "------------------------------\n\n";
		cout << "1. Заполнить базу случайными данными.\n";
		cout << "2. Сохранить базу данных в файл.\n";
		cout << "3. Загрузить базу данных из файла.\n";
		cout << "4. Показать базу данных.\n";
		cout << "5. Посчитать количество брендов автомобилей.\n";
		cout << "6. Найти количество автомобилей ценой меньше чем n RUB.\n";
		cout << "7. Найти количество автомобилей ниже средней цены всех моделей с учётом выбора КПП.\n";
		cout << "\n------------------------------\n\n";
		cout << ">> ";
		req = _getch();

		switch (req) {
		case MENU_1: {
			system("cls");
			for (int i = 0; i < car_amount; i++) {
				base_fill(cars[i]);
			}
			cout << "База заполнена случайными значениями.\n";
			cout << "Для продолжения нажмите любую кнопку.\n";
			req = _getch();
			break;
		}
		case MENU_2: {
			system("cls");
			ofstream writeFile("database.bin", ios::binary);
			if (!writeFile) {
				cout << "Не удалось создать файл.\n";
				cout << "Для продолжения нажмите любую кнопку.\n";
				req = _getch();
				break;
			}
			writeFile.write(reinterpret_cast<char*>(&cars), sizeof(cars));
			writeFile.close();
			cout << "База данных сохранена в файл.\n";
			cout << "Для продолжения нажмите любую кнопку.\n";
			req = _getch();
			break;
		}
		case MENU_3: {
			system("cls");
			ifstream readFile("database.bin", ios::binary);
			if (!readFile) {
				cout << "Не удалось открыть файл.\n";
				cout << "Для продолжения нажмите любую кнопку.\n";
				req = _getch();
				break;
			}
			readFile.read(reinterpret_cast<char*>(&cars), sizeof(cars));
			readFile.close();
			cout << "База данных загружена из файла.\n";
			cout << "Для продолжения нажмите любую кнопку.\n";
			req = _getch();
			break;
		}
		case MENU_4: {
			system("cls");
			for (int i = 0; i < car_amount; i++) {
				show_data(cars[i]);
			}
			cout << "Для продолжения нажмите любую кнопку.\n";
			req = _getch();
			break;
		}
		case MENU_5: {
			system("cls");
			for (int brand_id = 0, res = 0; brand_id < sizeof(brands) / sizeof(brands[0]); brand_id++) {
				for (int car_id = 0; car_id < car_amount; car_id++) {
					cars[car_id].brand == brands[brand_id] ? res++ : res;
				}
				cout << brands[brand_id] << "\t- " << res << " шт.\n";
				res = 0;
			}
			cout << "Для продолжения нажмите любую кнопку.\n";
			req = _getch();
			break;
		}
		case MENU_6: {
			system("cls");
			int n, count = 0;
			bool flag = false;
			cout << "Введите желаемую цену в рублях: ";
			cin >> n;
			for (int car_id = 0; car_id < car_amount; car_id++) {
				if (cars[car_id].price < n) {
					cout << "ID машины: " << car_id << "\n";
					count++;
					show_data(cars[car_id]);
					flag = true;
				}
			}
			if (!flag) {
				cout << "Машин с ценой меньше n рублей не нашлось.\n";
			}
			else {
				cout << "Количество автомобилей меньше n рублей = " << count << "\n";
			}
			cout << "Для продолжения нажмите любую кнопку.\n";
			req = _getch();
			break;
		}
		case MENU_7: {
			string choice_gearbox = "";
			int mid_price = 0, count = 0;
			cout << "Механика\n";
			cout << "Автомат\n";
			cout << "Робот\n";
			cout << "Вариатор\n";
			cout << "Введите название кпп:\n";
			cin >> choice_gearbox;
			while (!(choice_gearbox == "Механика" || choice_gearbox == "Автомат" || choice_gearbox == "Робот" || choice_gearbox == "Вариатор")) {
				cout << "Неправильный ввод!\n";
				cin >> choice_gearbox;
			}
			for (int i = 0; i < car_amount; i++) {
				mid_price += cars[i].price;
			}
			mid_price /= car_amount;
			cout << "Общая средняя цена автомобилей: " << mid_price << " RUB.\n\n";
			for (int id = 0; id < car_amount; id++) {
				if (cars[id].price < mid_price && cars[id].gearbox == choice_gearbox) {
					show_data(cars[id]);
					count++;
				}
			}
			cout << "Количество автомобилей ниже средней цены с КПП: " << choice_gearbox << " = " << count << "\n";
			cout << "Для продолжения нажмите любую кнопку.\n";
			req = _getch();
			break;
		}
		}
	}
	return 0;
}