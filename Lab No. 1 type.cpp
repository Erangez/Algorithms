#include <iostream>
#include <cstring>
#include <Windows.h>
using namespace std;
int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    //// #4
    // Создание типизированного файла с буквами.
    cout << "Задание №4\n";
    FILE* fw4;
    char letter[2];
    char f4_name[20];
    cout << "Введите имя файла: ";
    cin >> f4_name;
    fw4 = fopen(f4_name, "wb");
    if (!fw4) {
        cout << "Ошибка при создании файла.\n";
        return -1;
    }

    cout << "Введите букву: ";
    cin >> letter;
    while (letter[0] != '0') {
        fwrite(letter, sizeof(char), 2, fw4);
        cout << "Введите ещё букву (для отмены введите 0): ";
        cin >> letter;
    }
    cout << "Запись завершена.\n";
    fclose(fw4);

    // Решение задачи
    FILE* fr4;
    fr4 = fopen(f4_name, "rb");
    if (!fr4) {
        cout << "Ошибка при чтении файла.\n";
        return -1;
    }
    string word = "";
    while (!feof(fr4)) {
        if (fread(letter, sizeof(char), 2, fr4) == 2) {
            word += letter;
        }
    }
    cout << "Полученное слово: " << word << "\n";
    fclose(fr4);

    //// #5
    // Создание типизированного файла с числами.
    cout << "\nЗадание №5\n";
    FILE* fw5;
    char number[30];
    char f5_name[20];
    cout << "Введите имя файла: ";
    cin >> f5_name;
    fw5 = fopen(f5_name, "wb");
    if (!fw5) {
        cout << "Ошибка при создании файла.\n";
        return -1;
    }
    cout << "Введите число: ";
    cin >> number;
    while (number[0] != 'x') {
        fwrite(number, sizeof(char), 30, fw5);
        cout << "Введите ещё число (для отмены введите x): ";
        cin >> number;
    }
    cout << "Запись завершена.\n";
    fclose(fw5);

    // Решение задачи
    FILE* fr5;
    fr5 = fopen(f5_name, "rb");
    if (!fr5) {
        cout << "Ошибка при чтении файла.\n";
        return -1;
    }
    int n_max = INT32_MIN;
    while (!feof(fr5)) {
        fread(number, sizeof(char), 30, fr5);
        n_max = atoi(number) > n_max ? atoi(number) : n_max;
    }
    cout << "Максимальное число: " << n_max << "\n";
    fclose(fr5);

    //// #6
    // Создание типизированных файлов с числами.
    FILE* fw6, * fw62;
    char nums[30];
    char f6_name1[20];
    char f6_name2[20];
    cout << "Введите имя файла №1: ";
    cin >> f6_name1;
    fw6 = fopen(f6_name1, "wb");
    if (!fw6) {
        cout << "Ошибка при создании файла №1.\n";
        return -1;
    }
    cout << "Введите имя файла №2: ";
    cin >> f6_name2;
    fw62 = fopen(f6_name2, "wb");
    if (!fw62) {
        cout << "Ошибка при создании файла №2.\n";
        return -1;
    }
    // f №1
    cout << "Числа файла " << f6_name1 << ":\n";
    cout << "Введите число: ";
    cin >> nums;
    while (nums[0] != 'x') {
        fwrite(nums, sizeof(char), 30, fw6);
        cout << "Введите ещё число (для отмены введите x): ";
        cin >> nums;
    }
    cout << "Запись в файл " << f6_name1 << " завершена.\n";
    fclose(fw6);

    // f №2
    cout << "Числа файла " << f6_name2 << ":\n";
    cout << "Введите число: ";
    cin >> nums;
    while (nums[0] != 'x') {
        fwrite(nums, sizeof(char), 30, fw62);
        cout << "Введите ещё число (для отмены введите x): ";
        cin >> nums;
    }
    cout << "Запись в файл " << f6_name2 << " завершена.\n";
    fclose(fw62);

    // Решение задачи
    FILE* fw63, *fr6, *fr62;
    char f6_name3[20];
    cout << "Введите имя файла для записи: ";
    cin >> f6_name3;
    fw63 = fopen(f6_name3, "wb");
    if (!fw63) {
        cout << "Ошибка при создании файла " << f6_name3 << ".\n";
        return -1;
    }
    fr6 = fopen(f6_name1, "rb");
    if (!fr6) {
        cout << "Ошибка при чтении файла " << f6_name1 << ".\n";
        return -1;
    }
    fr62 = fopen(f6_name2, "rb");
    if (!fr62) {
        cout << "Ошибка при чтении файла " << f6_name2 << ".\n";
        return -1;
    }
    while (!feof(fr6)) {
        fread(nums, sizeof(char), 30, fr6);
        fwrite(nums, sizeof(char), 30, fw63);
    }
    while (!feof(fr62)) {
        fread(nums, sizeof(char), 30, fr62);
        fwrite(nums, sizeof(char), 30, fw63);
    }
    cout << "Запись закончена.\n";
    fclose(fw63);
    fclose(fr6);
    fclose(fr62);

    cout << "Вывод чисел из созданного файла " << f6_name3 << ":\n";
    FILE* fr63;
    fr63 = fopen(f6_name3, "rb");
    while (!feof(fr63)) {
        fread(nums, sizeof(char), 30, fr63);
        cout << nums << " ";
    }
    return 0;

}