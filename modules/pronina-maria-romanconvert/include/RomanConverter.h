// Copyright 2016 Pronina Maria
#ifndef MODULES_PRONINA_MARIA_ROMANCONVERT_INCLUDE_ROMANCONVERTER_H_
#define MODULES_PRONINA_MARIA_ROMANCONVERT_INCLUDE_ROMANCONVERTER_H_
#include <vector>
#include <string>
using std::string;
using std::vector;
class RomanConverter {
 public:
    static bool CheckArabicNumber(int arabic);
    static bool CheckRomanNumber(const string& roman);
    static int ConvertRomanToArabic(const string& roman);
    static string ConvertArabicToRoman(int arabic);
 private:
    static vector<string> ParseRoman(const string& roman);
    static bool CheckNumeralsRepeats
                (const vector<string>& parsed_roman);
    static bool CheckNumeralsOrder
                (const vector<string>& parsed_roman);
    static bool CheckForInvalidSymbols
                (const vector<string>& parsed_roman);
    static bool CheckForInvalidNumerals
                (const vector<string>& parsed_roman);
};
#endif  // MODULES_PRONINA_MARIA_ROMANCONVERT_INCLUDE_ROMANCONVERTER_H_
