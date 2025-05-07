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
	void addMileage(int km);
	void changePrice(int new_price);
	void calculatePriceBasedOnMileage();
	void calculatePriceBasedOnGearbox();
	// Методы доступа к закрытым данным-членам
	int getYear() const { return year_of_release; } // const после метода = константный метод (int const ...) = константное возвращ. значение
	int getPrice() const { return price; }
	int getMileage() const { return mileage; }
	string getBrand() const { return brand; }
	string getVIN() const { return vin; }
	string getColor() const { return color; }
	string getBodyType() const { return body_type; }
	string getGearbox()const { return gearbox; }
};
Car::Car(int year_of_release, int price, int mileage, string brand, string vin, string color, string body_type, string gearbox) :
	year_of_release{ year_of_release }, price{ price }, mileage{ mileage }, brand{ brand }, vin{ vin }, color{ color }, body_type{ body_type }, gearbox{ gearbox }
{
	cout << this->brand << " " << "[" << this->vin << "] " << this->year_of_release << " года была привезена в салон.\n";
}
Car::~Car() {
	cout << this->brand << " " << "[" << this->vin << "] " << this->year_of_release << " года была продана за " << price << " рублей.\n";
}
void Car::addMileage(int km) {
	if (km > 0) {
		mileage += km;
		cout << "Пробег изменён с " << mileage - km << " км до " << mileage <<
			" км для " << brand << " " << "[" << vin << "] " << year_of_release << " года.\n";
	}
	else if (km == 0) {
		cout << "Пробег не изменился.\n";
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
		cout << "Новая цена: " << price << " рублей.\n";
	}
	else {
		cout << "Невозможно изменить цену.\n";
		cout << "Вы ввели предыдущую цену.\n";
	}
}
void Car::calculatePriceBasedOnMileage() {
	const int fixed_penalty = 18000;
	int penalty = (mileage / 10000) * fixed_penalty;
	int penalted_price = price;
	if (price - penalty < price / 2) {
		penalted_price /= 2;
		cout << "Рассматриваемый автомобиль: " << brand << " " << "[" << vin << "] " << year_of_release << " года с пробегом " << mileage << " км\n";
		cout << "Текущая цена: " << price << " рублей\n";
		cout << "Вычет составил лишь половину от стоимости автомобиля (" << price / 2 << " рублей) из-за слишком большого пробега.\n";
		cout << "Расчитанная цена: " << penalted_price << " рублей.\n";
		price /= 2;
	}
	else {
		penalted_price = price - penalty;
		cout << "Рассматриваемый автомобиль: " << brand << " " << "[" << vin << "] " << year_of_release << " года с пробегом " << mileage << " км\n";
		cout << "Текущая цена: " << price << " рублей\n";
		cout << "Вычет: -" << penalty << " рублей (с учётом пробега).\n";
		cout << "Расчитанная цена: " << penalted_price << " рублей.\n";
		price -= penalty;
	}
}
void Car::calculatePriceBasedOnGearbox() {
	if (gearbox == "Механическая") {
		if (mileage > 135000) {
			price *= 0.70;
			cout << "С учётом пробега цена снижена на 30%.\n";
			cout << "Новая цена: " << price << " рублей\n";
		}
		else if (mileage < 135000 && mileage > 100000) {
			price *= 0.85;
			cout << "С учётом пробега цена снижена на 15%.\n";
			cout << "Новая цена: " << price << " рублей\n";
		}
		else {
			price *= 0.9;
			cout << "Цена снижена на 5% из-за типа коробки.\n";
			cout << "Новая цена: " << price << " рублей\n";
		}
	}
	else if (gearbox == "Автомат") {
		price *= 1.05;
		if (mileage > 125000) {
			price *= 0.75;
			cout << "С учётом пробега цена снижена на 25%.\n";
			cout << "Новая цена: " << price << " рублей\n";
		}
		else if (mileage < 125000 && mileage > 100000) {
			price *= 0.80;
			cout << "С учётом пробега цена снижена на 20%.\n";
			cout << "Новая цена: " << price << " рублей\n";
		}
		else {
			cout << "Цена увеличилась на 5% из-за типа коробки.\n";
			cout << "Новая цена: " << price << " рублей\n";
		}
	}
	else {
		cout << "Тип КПП не распознан.\n";
	}
}
int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	char req;
	int n;

	Car car_1(2006, 300000, 71568, "Lada", generateVIN(), "Индиго", "Седан", "Механическая");
	Car car_2(2019, 2250000, 57975, "Mazda", generateVIN(), "Серый", "Хэтчбек", "Автомат");
	Car car_3(2011, 1685000, 382000, "Audi", generateVIN(), "Чёрный", "Седан", "Автомат");

	cout << "\nАвтомобиль №1:";
	cout << "\n------------------------------\n";
	cout << "            ИНФО\n";
	cout << "Бренд: " << car_1.getBrand() << "\n";	
	cout << "VIN: " << car_1.getVIN() << "\n";
	cout << "Год: " << car_1.getYear() << "\n";
	cout << "Цвет: " << car_1.getColor() << "\n";
	cout << "Тип кузова: " << car_1.getBodyType() << "\n";
	cout << "Коробка: " << car_1.getGearbox() << "\n";
	cout << "Пробег: " << car_1.getMileage() << " км\n";
	cout << "Цена: " << car_1.getPrice() << " рублей\n";
	cout << "------------------------------\n\n";
	cout << "Метод для добавления пробега.\n"; 
	cout << "Введите пробег, который хотите добавить: ";
	cin >> n;
	car_1.addMileage(n);
	cout << "\n";
	cout << "Метод для расчёта цены автомобиля по пробегу.\n";
	car_1.calculatePriceBasedOnMileage();
	cout << "\n";
	cout << "Метод для расчёта цены автомобиля по типу КПП.\n";
	car_1.calculatePriceBasedOnGearbox();
	cout << "\n";
	cout << "Метод изменения цены.\n";
	cout << "Желаете ли сменить цену на свою?\n";
	cout << "Для подтверждения введите « y », в противном случае любой символ.\n";
	cin >> req;
	if (req == 'y') {
		cout << "Введите новую цену: ";
		cin >> n;
		car_1.changePrice(n);
	}
	cout << "\n";
	
	cout << "\nАвтомобиль №2:";
	cout << "\n------------------------------\n";
	cout << "            ИНФО\n";
	cout << "Бренд: " << car_2.getBrand() << "\n";
	cout << "VIN: " << car_2.getVIN() << "\n";
	cout << "Год: " << car_2.getYear() << "\n";
	cout << "Цвет: " << car_2.getColor() << "\n";
	cout << "Тип кузова: " << car_2.getBodyType() << "\n";
	cout << "Коробка: " << car_2.getGearbox() << "\n";
	cout << "Пробег: " << car_2.getMileage() << " км\n";
	cout << "Цена: " << car_2.getPrice() << " рублей\n";
	cout << "------------------------------\n\n";
	cout << "Метод для добавления пробега.\n";
	cout << "Введите пробег, который хотите добавить: ";
	cin >> n;
	car_2.addMileage(n);
	cout << "\n";
	cout << "Метод для расчёта цены автомобиля по пробегу.\n";
	car_2.calculatePriceBasedOnMileage();
	cout << "\n";
	cout << "Метод для расчёта цены автомобиля по типу КПП.\n";
	car_2.calculatePriceBasedOnGearbox();
	cout << "\n";
	cout << "Метод изменения цены.\n";
	cout << "Желаете ли сменить цену на свою?\n";
	cout << "Для подтверждения введите « y », в противном случае любой символ.\n";
	cin >> req;
	if (req == 'y') {
		cout << "Введите новую цену: ";
		cin >> n;
		car_2.changePrice(n);
	}
	cout << "\n";

	cout << "\nАвтомобиль №3:";
	cout << "\n------------------------------\n";
	cout << "            ИНФО\n";
	cout << "Бренд: " << car_3.getBrand() << "\n";
	cout << "VIN: " << car_3.getVIN() << "\n";
	cout << "Год: " << car_3.getYear() << "\n";
	cout << "Цвет: " << car_3.getColor() << "\n";
	cout << "Тип кузова: " << car_3.getBodyType() << "\n";
	cout << "Коробка: " << car_3.getGearbox() << "\n";
	cout << "Пробег: " << car_3.getMileage() << " км\n";
	cout << "Цена: " << car_3.getPrice() << " рублей\n";
	cout << "------------------------------\n\n";
	cout << "Метод для добавления пробега.\n";
	cout << "Введите пробег, который хотите добавить: ";
	cin >> n;
	car_3.addMileage(n);
	cout << "\n";
	cout << "Метод для расчёта цены автомобиля по пробегу.\n";
	car_3.calculatePriceBasedOnMileage();
	cout << "\n";
	cout << "Метод для расчёта цены автомобиля по типу КПП.\n";
	car_3.calculatePriceBasedOnGearbox();
	cout << "\n";
	cout << "Метод изменения цены.\n";
	cout << "Желаете ли сменить цену на свою?\n";
	cout << "Для подтверждения введите « y », в противном случае любой символ.\n";
	cin >> req;
	if (req == 'y') {
		cout << "Введите новую цену: ";
		cin >> n;
		car_3.changePrice(n);
	}
	cout << "\n";
	return 0;
}