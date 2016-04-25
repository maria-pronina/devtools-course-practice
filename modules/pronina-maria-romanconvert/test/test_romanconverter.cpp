// Copyright 2016 Pronina Maria
#include <gtest/gtest.h>
#include <string>
#include "include/RomanConverter.h"
TEST(RomanConverter_Tests, Can_Validate_Arabic) {
     // Arrange
     int arabic = 5;
     // Act
     bool isValid = RomanConverter::CheckArabicNumber(arabic);

     // Assert
     EXPECT_TRUE(isValid);
}
TEST(RomanConverter_Tests, Is_Negative_Arabic_Invalid) {
     // Arrange
     int arabic = -5;
     // Act
     bool is_valid = RomanConverter::CheckArabicNumber(arabic);

     // Assert
     EXPECT_FALSE(is_valid);
}

TEST(RomanConverter_Tests, Is_Zero_Arabic_Invalid) {
     // Arrange
     int arabic = 0;
     // Act
     bool is_valid = RomanConverter::CheckArabicNumber(arabic);

     // Assert
     EXPECT_FALSE(is_valid);
}
TEST(RomanConverter_Tests, Is_Greater_Than_Max_arabic_Invalid) {
     // Arrange
     int arabic = 4000;
     // Act
     bool is_valid = RomanConverter::CheckArabicNumber(arabic);

     // Assert
     EXPECT_FALSE(is_valid);
}
TEST(RomanConverter_Tests, Can_Validate_Roman) {
     // Arrange
     string roman = "XCV";
     // Act
     bool is_valid = RomanConverter::CheckRomanNumber(roman);

     // Assert
     EXPECT_TRUE(is_valid);
}
TEST(RomanConverter_Tests, Is_Empty_Roman_Invalid) {
     // Arrange
     string roman = "";
     // Act
     bool is_valid = RomanConverter::CheckRomanNumber(roman);

     // Assert
     EXPECT_FALSE(is_valid);
}
TEST(RomanConverter_Tests, Is_Roman_With_Four_Repeats_Invalid) {
     // Arrange
     string roman = "IIII";
     // Act
     bool is_valid = RomanConverter::CheckRomanNumber(roman);

     // Assert
     EXPECT_FALSE(is_valid);
}
TEST(RomanConverter_Tests, Is_Roman_IC_Invalid) {
    // Arrange
    string roman = "CDCMICI";
    // Act
    bool is_valid = RomanConverter::CheckRomanNumber(roman);

    // Assert
    EXPECT_FALSE(is_valid);
}
TEST(RomanConverter_Tests, Is_Roman_Without_Four_Repeats_Valid) {
     // Arrange
     string roman = "MMMDCCLXXXVIII";
     // Act
     bool is_valid = RomanConverter::CheckRomanNumber(roman);
     // Assert
     EXPECT_TRUE(is_valid);
}
TEST(RomanConverter_Tests,
    Is_Roman_With_Incorrect_Combination_Of_IXIV_Invalid) {
     // Arrange
     string roman = "XLIXIV";
     // Act
     bool is_valid = RomanConverter::CheckRomanNumber(roman);
     // Assert
     EXPECT_FALSE(is_valid);
}
TEST(RomanConverter_Tests, Is_Roman_With_Other_Symbols_Invalid) {
     // Arrange
     string roman = "Ia";
     // Act
     bool is_valid = RomanConverter::CheckRomanNumber(roman);

     // Assert
     EXPECT_FALSE(is_valid);
}
TEST(RomanConverter_Tests, Is_Simple_Roman_With_Incorrect_Order_Invalid) {
     // Arrange
     string roman = "VL";
     // Act
     bool is_valid = RomanConverter::CheckRomanNumber(roman);

     // Assert
     EXPECT_FALSE(is_valid);
}
TEST(RomanConverter_Tests, Is_Roman_With_End_Symbol_From_XCI_Valid) {
     // Arrange
     string roman = "X";
     // Act
     bool is_valid = RomanConverter::CheckRomanNumber(roman);

     // Assert
     EXPECT_TRUE(is_valid);
}
TEST(RomanConverter_Tests,
    Is_Roman_With_End_Symbol_And_Repeats_From_XCI_Valid) {
     // Arrange
     string roman = "CXXXII";
     // Act
     bool is_valid = RomanConverter::CheckRomanNumber(roman);

     // Assert
     EXPECT_TRUE(is_valid);
}
TEST(RomanConverter_Tests, Is_Roman_With_Incorrect_Numerals_Use_Invalid) {
     // Arrange
     string roman = "XLXLI";
     // Act
     bool is_valid = RomanConverter::CheckRomanNumber(roman);

     // Assert
     EXPECT_FALSE(is_valid);
}
TEST(RomanConverter_Tests,
     Is_Roman_With_Subs_Numerals_And_Incorrect_Order_Invalid) {
     // Arrange
     string roman = "XIIV";
     // Act
     bool is_valid = RomanConverter::CheckRomanNumber(roman);

     // Assert
     EXPECT_FALSE(is_valid);
}
TEST(RomanConverter_Tests, Is_Roman_With_All_Type_Of_Errors_Invalid) {
     // Arrange
     string roman = "IIIIIVa";
     // Act
     bool is_valid = RomanConverter::CheckRomanNumber(roman);

     // Assert
     EXPECT_FALSE(is_valid);
}
TEST(RomanConverter_Tests, Can_Convert_Arabic) {
     // Arrange
     int arabic = 2009;
     // Act
     string actual = RomanConverter::ConvertArabicToRoman(arabic);

     // Assert
     string expected = "MMIX";
     EXPECT_EQ(expected, actual);
}

TEST(RomanConverter_Tests, Can_Not_Convert_Negative_Arabic) {
     // Arrange
     int arabic = -2009;
     // Act
     string actual = RomanConverter::ConvertArabicToRoman(arabic);

     // Assert
     string expected = "";
     EXPECT_EQ(expected, actual);
}

TEST(RomanConverter_Tests, Can_Not_Convert_Zero_Arabic) {
     // Arrange
     int arabic = 0;
     // Act
     string actual = RomanConverter::ConvertArabicToRoman(arabic);

     // Assert
     string expected = "";
     EXPECT_EQ(expected, actual);
}
TEST(RomanConverter_Tests, Can_Not_Convert_Greater_Than_Max_Arabic) {
     // Arrange
     int arabic = 58900;
     // Act
     string actual = RomanConverter::ConvertArabicToRoman(arabic);

     // Assert
     string expected = "";
     EXPECT_EQ(expected, actual);
}
TEST(RomanConverter_Tests, Can_Convert_Roman) {
     // Arrange
     string roman = "MMMDCCLXXXVIII";
     // Act
     int actual = RomanConverter::ConvertRomanToArabic(roman);

     // Assert
     int expected = 3788;
     EXPECT_EQ(expected, actual);
}
TEST(RomanConverter_Tests, Can_Not_Convert_Empty_Roman) {
     // Arrange
     string roman = "";
     // Act
     int actual = RomanConverter::ConvertRomanToArabic(roman);

     // Assert
     int expected = -1;
     EXPECT_EQ(expected, actual);
}
TEST(RomanConverter_Tests, Can_Not_Convert_Roman_With_Other_Symbols) {
     // Arrange
     string roman = "-1";
     // Act
     int actual = RomanConverter::ConvertRomanToArabic(roman);

     // Assert
     int expected = -1;
     EXPECT_EQ(expected, actual);
}
TEST(RomanConverter_Tests, Can_Not_Convert_Roman_Invalid_Order) {
     // Arrange
     string roman = "XXXVMMMDCCLIII";
     // Act
     int actual = RomanConverter::ConvertRomanToArabic(roman);

     // Assert
     int expected = -1;
     EXPECT_EQ(expected, actual);
}
TEST(RomanConverter_Tests, Is_CC_Valid) {
    // Arrange
    string roman = "CC";
    // Act
    bool is_valid = RomanConverter::CheckRomanNumber(roman);
    // Assert
    EXPECT_TRUE(is_valid);
}


