#pragma once

const int MAX_STRING_SIZE = 255;

typedef union Characteristics {
    float weight;
    int volume;
} characteristics_t;

typedef struct Production {
    char name[MAX_STRING_SIZE];
    int quantity;
    int number;
    int id_code;
    characteristics_t atribute;
    char characteristic_type;
} production_t;

bool IsNullObject(production_t object);

production_t CreateObject();

production_t* ResizeArray(production_t* array, int &length, int new_length);

production_t* FillArray(int &length);

void ShowObject(production_t object, int index);

void ShowStructObjects(production_t* array, int length);

production_t* PutObjectToArray(production_t* array, production_t object, int &length);

bool CompareObjects(production_t object, production_t other_object);

int FindObjectIndex(production_t* array, int length, std::string name);

production_t* DeleteObject(production_t* array, production_t object, int &length);

void ChangeObject(production_t* array, int length, production_t &object, std::string name);

void ShakerSort(production_t* array, int length);

void ShowObjectsQuantity(production_t* array, int length);

void Save(production_t* array, int length);

void Read(production_t* &array, int &length);

void ChangeEntry(production_t* array, int length, std::string name);