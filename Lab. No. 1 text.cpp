#include <iostream>
#include <cstring>
#include <Windows.h>
using namespace std;
int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    FILE* fp1;
    fp1 = fopen("files/info.txt", "r");
    if (!fp1) {
        cout << "Файл открыть не удалось.\n";
        return -1;
    }
    char str1[50];
    cout << "Содержимое файла info.txt: \n";
    while (!feof(fp1)) {
        if (fgets(str1, 50, fp1) != NULL) {
            cout << str1;
        }
        else {
            cout << "Ошибка при чтении файла. \n";
            return -1;
        }
    }

    //// #1
    cout << "\n\nЗадание №1";
    rewind(fp1);
    cout << "\nВывод первых пяти строк: \n";
    int counter = 0;
    while (!feof(fp1)) {
        if (fgets(str1, 50, fp1) != NULL) {
            if (counter > 4) { break; }
            cout << str1;
            counter++;
        }
        else {
            cout << "Ошибка при чтении файла. \n";
            return -1;
        }
    }

    //// #2
    cout << "\nЗадание №2\n";
    cout << "Количество строк, начинающихся с букв 'а' или 'А' в файле info.txt\n";
    rewind(fp1);
    int amount_of_str = 0;
    while (!feof(fp1)) {
        if (fgets(str1, 50, fp1) != NULL) {
            if (str1[0] == 'А' || str1[0] == 'а') {
                cout << str1;
            }
        }
        else {
            cout << "Ошибка при чтении файла. \n";
            return -1;
        }
    }
    fclose(fp1);

    //// #3
    cout << "\n\nЗадание №3\n";
    cout << "Дан текстовый файл:\n";
    FILE* fp3, * fp3_out;
    char str3[50];
    fp3 = fopen("files/info2.txt", "r");
    if (!fp3) {
        cout << "Файл не удалость открыть в режиме чтения.\n";
        return -1;
    }
    cout << "Содержимое файла info2.txt:\n";
    while (!feof(fp3)) {
        if (fgets(str3, 50, fp3)) {
            cout << str3;
        }
    }

    fp3_out = fopen("files/info2_out.txt", "w");
    char str3_out[50];
    if (!fp3_out) {
        cout << "Файл не удалость открыть в режиме записи.\n";
        return -1;
    }

    cout << "\nВведите файлы ch1 и ch2 для замены: \n";
    char ch1, ch2;
    cin >> ch1;
    cin >> ch2;

    rewind(fp3);
    while (!feof(fp3)) {
        if (fgets(str3, 50, fp3)) {
            for (int i = 0; i < 50; i++) {
                if (str3[i] == ch1) { str3_out[i] = ch2; }
                else if (str3[i] == ch2) { str3_out[i] = ch1; }
                else { str3_out[i] = str3[i]; }
            }
            if (fputs(str3_out, fp3_out) == EOF) {
                cout << "Ошибка при записи в файл.\n";
                return -1;
            }
        }
        else {
            cout << "Ошибка при чтении файла. \n";
            return -1;
        }
    }
    cout << "Замена ch1 на ch2 и наоборот завершена.\n";
    fclose(fp3);
    fclose(fp3_out);
    return 0;
}