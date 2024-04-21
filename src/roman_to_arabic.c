#include <stdio.h>
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

int main() {
    char romanNumber[100];
    scanf("%s", romanNumber);

    if (strlen(romanNumber) > 15) {
        printf("Puck you, Verter");  //слишком длинное число
        return 1;
    }

    int arabicNumber = romanToArabic(romanNumber);
    if (arabicNumber == -1) {
        printf("Puck you, Verter");  //некорректное римское число
        return 1;
    }
    printf("%d", arabicNumber);

    return 0;
}
