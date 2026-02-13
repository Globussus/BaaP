#pragma once

const int MAX_STRING_SIZE = 255;

typedef union Rating {
    char letter_mark[MAX_STRING_SIZE];
    int percentage;
} rating;

typedef struct Library {
    int registration_number;
    char author[MAX_STRING_SIZE];
    int publishing_year;
    char title[MAX_STRING_SIZE];
    char publisher[MAX_STRING_SIZE];
    int pages_quantity;
    rating mark;
    char mark_type;
} library_t;

bool IsEmptyString(char* string);

bool IsNullObject(library_t book);

library_t Initialisation();

library_t* ResizeArray(library_t* array, int &length, int new_length);

library_t* FillArray(int &length);

void ShowBook(library_t object, int index);

void ShowBookshelve(library_t* array, int length);

library_t* AddBook(library_t* array, library_t book, int &length);

bool CompareBooks(library_t book, library_t other_book);

int FindBookIndex(library_t* array, int length, std::string title);

library_t* DeleteBook(library_t* array, library_t book, int &length);

void Sort(library_t* array, int length);

void PrintBookList(library_t* array, int &length, int year);

std::string ChangeString(char* string, char sign, char new_sign);

void Save(library_t* array, int length);

void Read(library_t* &array, int &length);

void Change(library_t* array, int length, std::string name);