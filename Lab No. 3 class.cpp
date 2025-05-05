#include <iostream>
#include <Windows.h>

using namespace std;

string generateVIN() {
	srand(time(NULL));
	char symbols[33]{ '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F','G','H','J','K','L','M','N','P','R','S','T','U','V','W','X','Y','Z' };
	string VIN = "";
	for (int i = 0; i < 17; i++) {
		VIN += symbols[0 + rand() % (32 - 0 + 1)];
	}
	return VIN;
}
class Car {
	int year_of_release;
	int price;
	int mileage;
	string brand;
	string vin;
	string color;
	string body_type;
	string gearbox;
public:
	// Конструкторы
	Car(int year_of_release, int price, int mileage, string brand, string vin, string color, string body_type, string gearbox);
	~Car();
	// Методы
	void show();
	void addMileage(int km);
	void changePrice(int new_price);
	void calculatePriceBasedOnMileage();
	// Методы доступа к закрытым данным-членам
	int getYear() { return year_of_release; }
	int getPrice() { return price; }
	int getMileage() { return mileage; }
	string getBrand() { return brand; }
	string getVIN() { return vin; }
	string getColor() { return color; }
	string getBodyType() { return body_type; }
	string getGearbox() { return gearbox; }
};
Car::Car(int year_of_release, int price, int mileage, string brand, string vin, string color, string body_type, string gearbox) {
	this->vin = vin;
	this->year_of_release = year_of_release;
	this->price = price;
	this->mileage = mileage;
	this->brand = brand;
	this->color = color;
	this->body_type = body_type;
	this->gearbox = gearbox;
	cout << this->brand << " " << "[" << this->vin << "] " << this->year_of_release << " года была привезена в салон.\n";
}
Car::~Car() {
	cout << this->brand << " " << "[" << this->vin << "] " << this->year_of_release << " года была куплена за " << price << " рублей.\n";
}
void Car::show() {
	cout << "\n------------------------------\n";
	cout << "            ИНФО\n";
	cout << "Бренд: " << brand << "\n";	
	cout << "VIN: " << vin << "\n";	
	cout << "Год: " << year_of_release << "\n";
	cout << "Цвет: " << color << "\n";	
	cout << "Тип кузова: " << body_type << "\n";	
	cout << "Коробка: " << gearbox << "\n";	
	cout << "Пробег: " << mileage << " км\n";	
	cout << "Цена: " << price << " рублей\n";	
	cout << "------------------------------\n\n";
}
void Car::addMileage(int km) {
	if (km > 0) {
		mileage += km;
		cout << "Пробег изменён с " << mileage - km << " км до " << mileage <<
			" км для " << brand << " " << "[" << vin << "] " << year_of_release << " года.\n";
	}
	else {
		cout << "Невозможно изменить пробег.\n";
		cout << "Проверьте введённые данные (скрутить пробег нельзя).\n";
	}
}
void Car::changePrice(int new_price) {
	if (new_price != price) {
		price = new_price;
		cout << "Для " << brand << " " << "[" << vin << "] " << year_of_release << " года была изменена цена.\n";
		cout << "Новая цена: " << price << "рублей.\n";
	}
	else {
		cout << "Невозможно изменить цену.\n";
		cout << "Вы ввели существующую цену.\n";
	}
}
void Car::calculatePriceBasedOnMileage() {
	const int fixed_penalty = 18000;
	int penalty = (mileage / 10000) * fixed_penalty;
	int penalted_price = price - penalty;
	if (penalted_price < price / 2) {
		penalted_price /= 2;
	}
	cout << "Рассматриваемый автомобиль: " << brand << " " << "[" << vin << "] " << year_of_release << " года с пробегом " << mileage << " км\n";
	cout << "Текущая цена: " << price << " рублей\n";
	cout << "Вычет: -" << penalty << " рублей (с учётом пробега)\n";
	cout << "Расчитанная цена: " << penalted_price << " рублей.\n";
}
int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	char req;
	int n;

	Car car_1(2006, 300000, 71568, "Lada", generateVIN(), "Индиго", "Седан", "Механическая");
	Car car_2(2019, 2250000, 57975, "Mazda", generateVIN(), "Серый", "Хэтчбек", "Автомат");
	car_1.show();
	cout << "Введите пробег, который хотите добавить: ";
	cin >> n;
	car_1.addMileage(n);
	car_1.calculatePriceBasedOnMileage();

	cout << "Желаете сменить цену?\n";
	cout << "Для подтверждения введите « y », в противном случае любой символ.\n";
	cin >> req;
	if (req == 'y') {
		cout << "Введите новую цену: ";
		cin >> n;
		car_1.changePrice(n);
	}
	car_2.show();
	cout << "Введите пробег, который хотите добавить: ";
	cin >> n;
	car_2.addMileage(n);
	car_2.calculatePriceBasedOnMileage();

	cout << "Желаете сменить цену?\n";
	cout << "Для подтверждения введите « y », в противном случае любой символ.\n";
	cin >> req;
	if (req == 'y') {
		int new_price;
		cout << "Введите новую цену: ";
		cin >> n;
		car_2.changePrice(n);
	}
	return 0;
}
