// dz_strings2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

// forward declaration
int num_of_numbers(char* str);                         // ф-ия, кол-во цифр в тексте
void change_word
(char* str, char* strnew, size_t BUFF_SIZE, int* px);  // ф-ия, замена слова
void start_sentence(char* str);                        // ф-ия, предложение с большой буквы
void num_of_let
(char* str, char* alphabet, int p, size_t LETTER);     // ф-ия, кол-во всех букв в тексте

int main()
{
    /*
    Завдання 1. Є деякий текст. Використовуючи стандартні
    рядкові функції з бібліотеки мови C:
    ■ Знайдіть і замініть входження деякого слова на задане
    користувачем слово;
    ■ Змініть текст так, щоб кожне речення починалося з
    великої літери;
    ■ Порахуйте, скільки разів кожна літера трапляється
    в тексті;
    ■ Порахуйте, скільки разів цифри трапляються в тексті.
*/
    const size_t BUF_SIZE = 200;           // указание памяти под массив символов
    char* str = new char[BUF_SIZE];        // указатель на массив символов str 
    strcpy(str,                            // заполнение массива символов str
        "underneath my outside face(1).\n" 
        "there's a face that none can see(2)\n");
    printf("Initial text:\n");
    printf(str);                           // вывод на экран массива символов str

    const size_t LETTER = 26;              // указание памяти для массива букв alphabet 
    char* alphabet = new char[LETTER];     // указатель на массив символов (букв) alphabet
    int first_letter = 97;                 // первая буква алфавита со значением 97 по таблицу ASCII
    for (size_t i = 0; i < LETTER; i++) {  // цикл по всем буквам
        alphabet[i] = char(first_letter);  // преобразование значения int к char
        first_letter++;
    }

    int p = 0;     // вводим переменную для размера нового массива (ф-ия замены слов)
    int* px = &p;  // указатель px получает адрес переменной p
    char* strnew = new char[BUF_SIZE];

    printf("\nText with changed words:\n");
    change_word(str, strnew, BUF_SIZE, px);
    
    printf("\nText where sentences begin with a capital letter:\n");
    start_sentence(str);

    printf("\nThe number of digits in the text:\n");
    num_of_numbers(str);

    printf("\nThe number of each letter in the text:\n");
    num_of_let(str, alphabet, p, LETTER);
   
    return 0;
}

void change_word(char* str, char *strnew, size_t BUFF_SIZE, int *px) {
    if (str == NULL || strnew == NULL) {
        printf("Error");
    }
    size_t length = strlen(str);  // длина строки 

    char* str1 = new char[20];    //  указатель на массив - слово под замену
    puts("Enter the word that should be replaced: ");
    std::cin.getline(str1, 20);   // пользователь вводит слово под замену
    size_t len1 = strlen(str1);   // длина слова под замены

    char* str2 = new char[20];    // указатель на массив - слово на замену
    puts("The word you want to insert: ");
    std::cin.getline(str2, 20);   // пользователь вводит слово на замену
    size_t len2 = strlen(str2);   // длина слова на замену
    
    char* place;                  // вводим новый указатель 
    place = strstr(str, str1);    // указатель на 1ое совпадение для замены
    size_t index = 0;

    if (place != NULL) {               // если есть совпадение   
        for (size_t i = 0; i < length; i++) {
            index = place - str;
            if (i != index) {
                strnew[*px] = str[i];  // запись в новый массив
                *px = *px + 1;
            }
            else {
                for (size_t x = 0; x < len2; x++) {
                    strnew[*px] = str2[x];
                    *px = *px + 1;
                }
                i = i + len1 - 1;
                place = strstr(place + 1, str1);
            }
        }
    }
    for (size_t i = 0; i < *px; i++) {
        std::cout << strnew[i];
    }   
}

void start_sentence(char* str) {  // ф-ия, изменение букв на заглавные в начале предложения
    size_t length = strlen(str);  // длина строки
    for (size_t i = 0; i < length; i++)
    {
        if (str[0] >= 97 && str[0] <= 122) {  // если 0(1ый) сомвол массива - мал.буква
            str[0] -= 32;                     // заменяем на большую
        }      
        if (str[i] == 33 || str[i] == 63 || str[i] == 46) {  // если есть символ ! или ? или .
            str[i + 2] -= 32;                                // символ через один (новое предложение 
        }                                                    //  после пробела) заменяем на большую букву
    }
    printf(str);
}

int num_of_numbers(char* str) {              // ф-ия, кол-во цифр в тексте
    if (str == NULL) {
        return -1;
    }
    int count = 0;                           // накопительная переменная
    size_t length = strlen(str);             // определяем длину строки
    for (size_t i = 0; i < length; i++)      // цикл по массиву str
    {
        if (str[i] >= 48 && str[i] <= 57) {  // цифра по таблице ASCII      
                count += 1;           
        }
    }
    std::cout << count << "\n";
    return count;
}

void num_of_let                            // ф-ия, кол-во букв в тексте
(char* str, char* alphabet, int p, size_t LETTER) {
    if (str == NULL || alphabet == NULL) {
        printf("Error");
    }
    int count;                             // накопительная переменная для кол-ва букв
    for (size_t i = 0; i < LETTER; i++) {  // цикл по массиву алфавита
        count = 0;
        for (size_t j = 0; j < p; j++) {   // цикл по новому массиву       
            if (int(alphabet[i]) == int(str[j])
                || int(alphabet[i]) 
                == int(str[j]) + 32) {     // 32 - разница между большими и мал.буквами
                count++;   
            }
        }      
        std::cout << alphabet[i] << " = " << count << ' ';       
    }
}



