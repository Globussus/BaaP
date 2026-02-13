#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include "../include/Production.h"
#include "../include/InputChecker.h"

bool IsEmptyString(char* string) {
    int index = 0;
    while (string[index] != '\0') {
        if (string[index] != ' ') {
            return false;
        }
    }
    return true;
}

bool IsNullObject(production_t object) {
    switch(object.characteristic_type) {
        case 'i':
            return (IsEmptyString(object.name) && object.number == 0 && object.id_code == 0 && object.quantity == 0 && object.atribute.weight == 0);
        case 'c':
            return (IsEmptyString(object.name) && object.number == 0 && object.id_code == 0 && object.quantity == 0 && object.atribute.volume == 0);
        default: 
            return false;
    }
}

production_t CreateObject() {
    std::string obj_name;
    int obj_quantity, obj_number, obj_id;
    char obj_char_type;
    std::cout << "Введите название товара: ";
    getline(std::cin, obj_name);
    if (obj_name.empty()) {
        return production_t();
    }
    std::cout << "Введите количество произведенных товаров: ";
    CheckIntInput(obj_quantity, "Введите количество произведенных товаров: ");
    std::cout << "Введите номер цеха: ";
    CheckIntInput(obj_number, "Введите номер цеха: ");
    std::cout << "Введите id-код товара: ";
    CheckIntInput(obj_id, "Введите id-код товара: ");
    std::cout << "Напишите, что будет использоваться для измерения размеров тела: масса (Введите w) или объем (Введите v): ";
    std::cin >> obj_char_type;
    CleanInput();
    switch(obj_char_type) {
        case 'w': {
            float weight;
            std::cout << "Введите вес (в килограммах) товара: ";
            CheckFloatInput(weight, "Введите вес (в килограммах) товара: ");
            production_t object;
            strcpy(object.name, obj_name.c_str());
            object.number = obj_number;
            object.id_code = obj_id;
            object.quantity = obj_quantity;
            object.atribute.weight = weight;
            object.characteristic_type = obj_char_type;
            return object;
        }
        case 'v': {
            int volume;
            std::cout << "Введите объем (в милилитрах) товара: ";
            CheckIntInput(volume, "Введите объем (в милилитрах) товара: ");
            production_t object;
            strcpy(object.name, obj_name.c_str());
            object.number = obj_number;
            object.id_code = obj_id;
            object.quantity = obj_quantity;
            object.atribute.volume = volume;
            object.characteristic_type = obj_char_type;
            return object;
        }
        default: {
            CleanInput();
            production_t object;
            strcpy(object.name, obj_name.c_str());
            object.number = obj_number;
            object.id_code = obj_id;
            object.quantity = obj_quantity;
            return object;
        }
    }
}

production_t* ResizeArray(production_t* array, int &length, int new_length) {
    production_t* new_array = new production_t[new_length];
    int elements_to_copy = (length < new_length) ? length : new_length;
    for (int i = 0; i < elements_to_copy; i++) {
        new_array[i] = array[i];
    }
    delete[] array;
    length = new_length;
    return new_array;
}

production_t* FillArray(int &length) {
    std::string flag;
    production_t* array = new production_t[length];
    for (int i = 0; i < length; i++) {
        std::cout << "Товар №" << i + 1 << ":" << std::endl;
        production_t new_object = CreateObject();
        if (IsNullObject(new_object)) {
            std::cout << "Ввод отменен. Завершение ввода" << std::endl;
            array = ResizeArray(array, length, i);
            break;
        }
        array[i] = new_object;
        if (i != length - 1) {
            std::cout << "Желаете ли продолжить ввод(y - если да/n - если нет)?: ";
            std::cin >> flag;
            CleanInput();
        }
        if (flag == "n" || flag == "N") {
            array = ResizeArray(array, length, i + 1);
            break;
        } 
        std::cout << std::endl;
    }
    std::cout << "Завершение ввода" << std::endl;
    return array;
}

void ShowObject(production_t object, int index) {
    if (IsNullObject(object)) {
        return;
    }
    std::cout << "Товар №" << index + 1 << ":" << std::endl;
    std::cout << "Название товара: " << object.name << std::endl;
    std::cout << "Количество произведенных товаров: " << object.quantity << std::endl;
    std::cout << "Номер цеха: " << object.number << std::endl;
    std::cout << "id-код товара: " << object.id_code << std::endl;
    switch (object.characteristic_type) {
        case 'w':
            std::cout << "Масса товара: " << object.atribute.weight << " кг." << std::endl;
            break;
        case 'v':
            std::cout << "Объем товара: " << object.atribute.volume << " мл." << std::endl;
            break;
        default:
            std::cout << "Ни масса, ни объем товара не указаны" << std::endl;
            break;
    }
}

void ShowStructObjects(production_t* array, int length) {
    if (length > 0) {
        int index = 0;
        std::cout << "======================Список товаров======================" << std::endl;
        while (index < length) {
            ShowObject(array[index], index);
            index++;
        }
        std::cout << "===========================================================" << std::endl;
    } else {
        std::cout << "Список товаров пуст" << std::endl;
    }
}

production_t* PutObjectToArray(production_t* array, production_t object, int &length) {
    if (!IsNullObject(object)) {
        int old_length = length;
        array = ResizeArray(array, length, old_length + 1);
        array[length - 1] = object;
    }
    return array;
}

bool CompareObjects(production_t object, production_t other_object) {
    if (object.characteristic_type != other_object.characteristic_type) {
        return false;
    }
    if (object.name != other_object.name || 
        object.number != other_object.number || 
        object.id_code != other_object.id_code ||
        object.quantity != other_object.quantity) {
        return false;
    }
    switch (object.characteristic_type) {
        case 'w':
            return object.atribute.weight == other_object.atribute.weight;
        case 'v':
            return object.atribute.volume == other_object.atribute.volume;
        default:
            return false;
    }
}

int FindObjectIndex(production_t* array, int length, std::string name) {
    int index = -1;
    for (int i = 0; i < length; i++) {
        if (array[i].name != nullptr && std::string(array[i].name) == name) {
            index = i;
            break;
        }
    }
    return index;
}

production_t* DeleteObject(production_t* array, production_t object, int &length) {
    if (length == 0) {
        std::cout << "Массив товаров пуст!";
        return array;
    }
    production_t* new_array = new production_t[length - 1];
    int current_index = 0;
    for (int i = 0; i < length; i++) {
        if (CompareObjects(object, array[i])) {
            continue;
        }
        new_array[current_index++] = array[i];
    }
    length -= 1;
    delete[] array;
    return new_array;
}

void ChangeObject(production_t* array, int length, production_t &object, std::string name) {
    int index = FindObjectIndex(array, length, object.name);
    if (index != -1) {
        std::cout << "Название товара было изменено:\n  Новое название - " << name << std::endl;
        strcpy(object.name, name.c_str());
    } else {
        std::cout << "Данный товар не был найден" << std::endl;
    }
}

void ShakerSort(production_t* array, int length) {
    int left = 0, right = length - 1;
    while (left <= right) {
        for (int i = right; i > left; i--) {
            if (array[i - 1].quantity < array[i].quantity) {
                std::swap(array[i - 1], array[i]);
            }
        }
        left++;
        for (int i = left; i < right; i++) {
            if (array[i].quantity < array[i + 1].quantity) {
                std::swap(array[i], array[i + 1]);
            }
        }
        right--;
    }
}

void ShowObjectsQuantity(production_t* array, int length) {
    production_t* new_array = new production_t[length];
    for (int i = 0; i < length; i++) {
        new_array[i] = array[i];
    }
    ShakerSort(new_array, length);
    std::cout << "Количество произведенных товаров: " << std::endl;
    for (int i = 0; i < length; i++) {
        std::cout << i + 1 << ") " << new_array[i].name << ": " << new_array[i].quantity << " шт." << std::endl;
    }
    delete[] new_array;
}

void Save(production_t* array, int length) {
    std::fstream file;
    file.open("production", std::ios::out | std::ios::binary);
    file.write((char *)array, length * sizeof(production_t));
    file.close();
}

void Read(production_t* &array, int &length) {
    std::fstream file;
    file.open("production", std::ios::in | std::ios::binary);
    if (file.good()) {
        file.seekg(0, file.end);
        length = file.tellg() / sizeof(production_t);
        file.seekg(0, file.beg);
        delete[] array;
        array = nullptr;
        array = new production_t[length];
        file.read((char *)array, length * sizeof(production_t));
        file.close();
    }
}

void ChangeEntry(production_t* array, int length, std::string name) {
    int object_index = FindObjectIndex(array, length, name);
    if (object_index == -1) {
        std::cout << "Запись не найдена" << std::endl;
        return;
    }
    const int size = sizeof(production_t);
    long long file_position = static_cast<long long>(object_index) * size;
    std::fstream file("production", std::ios::binary | std::ios::in | std::ios::out);
    production_t new_object = CreateObject();
    array[object_index] = new_object;
    file.seekp(file_position); 
    file.write(reinterpret_cast<const char*>(&new_object), size);
    std::cout << "Запись успешно изменена" << std::endl;
    file.close();
}