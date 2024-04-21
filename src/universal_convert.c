#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct RomanNumeral {
    char alphabet[4];
    int arabic;
} RomanNumeral;

RomanNumeral romanNumerals[] = {{"MMM", 3000}, {"MM", 2000}, {"M", 1000}, {"CM", 900},  {"DCCC", 800},
                                {"DCC", 700},  {"DC", 600},  {"D", 500},  {"CD", 400},  {"CCC", 300},
                                {"CC", 200},   {"C", 100},   {"XC", 90},  {"LXXX", 80}, {"LXX", 70},
                                {"LX", 60},    {"L", 50},    {"XL", 40},  {"XXX", 30},  {"XX", 20},
                                {"X", 10},     {"IX", 9},    {"VIII", 8}, {"VII", 7},   {"VI", 6},
                                {"V", 5},      {"IV", 4},    {"III", 3},  {"II", 2},    {"I", 1}};

int isValidRoman(char* roman) {
    int len = strlen(roman);
    for (int i = 0; i < len; i++) {
        if (i < len - 1 && roman[i] == roman[i + 1]) {
            if (roman[i] == 'V' || roman[i] == 'L' || roman[i] == 'D') {
                return 0;  // V, L, D не могут повторяться подряд
            }
            if (i < len - 2 && roman[i] == roman[i + 2]) {
                if (i < len - 3 && roman[i] == roman[i + 3]) {
                    return 0;  // I, X, C, M не могут повторяться более трех раз подряд
                }
            }
        }
    }
    return 1;
}

int romanToArabic(char* roman) {
    if (strcmp(roman, "nulla") == 0 || strcmp(roman, "nihil") == 0 || strcmp(roman, "N") == 0) {
        return 0;
    }
    if (!isValidRoman(roman)) {
        return -1;  // Возвращаем -1, если римское число некорректно
    }

    int result = 0;
    int len = strlen(roman);

    for (int i = 0; i < len; i++) {
        for (size_t j = 0; j < sizeof(romanNumerals) / sizeof(romanNumerals[0]); j++) {
            if (strncmp(roman + i, romanNumerals[j].alphabet, strlen(romanNumerals[j].alphabet)) == 0) {
                result += romanNumerals[j].arabic;
                i += strlen(romanNumerals[j].alphabet) - 1;
                break;
            }
        }
    }

    return result;
}

char* arabicToRoman(int arabicNum) {
    char* result = calloc(16, sizeof(char));

    if (arabicNum == 0) {
        strcat(result, "nulla");
        return result;
    }

    int thousands = arabicNum / 1000;
    int hundreds = (arabicNum % 1000) / 100;
    int tens = (arabicNum % 100) / 10;
    int units = arabicNum % 10;

    if (thousands == 1) strcat(result, "M");
    if (thousands == 2) strcat(result, "MM");
    if (thousands == 3) strcat(result, "MMM");

    if (hundreds == 1) strcat(result, "C");
    if (hundreds == 2) strcat(result, "CC");
    if (hundreds == 3) strcat(result, "CCC");
    if (hundreds == 4) strcat(result, "CD");
    if (hundreds == 5) strcat(result, "D");
    if (hundreds == 6) strcat(result, "DC");
    if (hundreds == 7) strcat(result, "DCC");
    if (hundreds == 8) strcat(result, "DCCC");
    if (hundreds == 9) strcat(result, "CM");

    if (tens == 1) strcat(result, "X");
    if (tens == 2) strcat(result, "XX");
    if (tens == 3) strcat(result, "XXX");
    if (tens == 4) strcat(result, "XL");
    if (tens == 5) strcat(result, "L");
    if (tens == 6) strcat(result, "LX");
    if (tens == 7) strcat(result, "LXX");
    if (tens == 8) strcat(result, "LXXX");
    if (tens == 9) strcat(result, "XC");

    if (units == 1) strcat(result, "I");
    if (units == 2) strcat(result, "II");
    if (units == 3) strcat(result, "III");
    if (units == 4) strcat(result, "IV");
    if (units == 5) strcat(result, "V");
    if (units == 6) strcat(result, "VI");
    if (units == 7) strcat(result, "VII");
    if (units == 8) strcat(result, "VIII");
    if (units == 9) strcat(result, "IX");

    return result;
}
// char * arabicToRoman(int arabicNum){
//     char * result = calloc(16, sizeof(char)); // Убедитесь, что выделено достаточно памяти для хранения
//     результата

//     // Массивы для тысяч, сотен, десятков и единиц
//     const char * thousands[] = {"", "M", "MM", "MMM"};
//     const char * hundreds[] = {"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"};
//     const char * tens[] = {"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"};
//     const char * units[] = {"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"};

//     // Вычисляем количество тысяч, сотен, десятков и единиц
//     int numThousands = arabicNum / 1000;
//     int numHundreds = (arabicNum % 1000) / 100;
//     int numTens = (arabicNum % 100) / 10;
//     int numUnits = arabicNum % 10;

//     // Конкатенируем соответствующие строки из массивов
//     strcat(result, thousands[numThousands]);
//     strcat(result, hundreds[numHundreds]);
//     strcat(result, tens[numTens]);
//     strcat(result, units[numUnits]);

//     return result;
// }
// УБИРАТЬ НЕ СТАЛ, НО ЭТОТ ВАРИАНТ ФУНКЦИИ БОЛЕЕ КРАСИВЫЙ И КОМПАКТНЫЙ, ОН НЕ МОЙ:)

int main() {
    int choice = 0;
    scanf("%d", &choice);

    if (choice == 1) {
        char romanNumber[100];
        scanf("%s", romanNumber);

        if (strlen(romanNumber) > 15) {
            fprintf(stderr, "Puck you, Verter");  //слишком длинное число
            return 1;
        }

        int arabicNumber = romanToArabic(romanNumber);
        if (arabicNumber == -1) {
            fprintf(stderr, "Puck you, Verter");  //некорректное римское число
            return 1;
        }
        printf("%d", arabicNumber);

    } else if (choice == 2) {
        int arabic = 0;
        scanf("%d", &arabic);
        if (arabic > 3999) {
            fprintf(stderr, "Puck you, Verter");  //меньше число нужно арабское
            return 1;
        }
        char* roman = arabicToRoman(arabic);

        printf("%s", roman);

        free(roman);

    } else {
        fprintf(stderr, "Puck you, Verter");  //неверный пункт меню
        return 1;
    }

    return 0;
}