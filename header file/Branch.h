#pragma once

#include <string>
#include <string_view>
#include <vector>
#include "Book.h"

// Класс Branch описывает филиал библиотечной сети.
// Содержит коллекцию объектов Book — каталог филиала — и ограничение
// на количество книг, которое филиал может вместить.
class Branch {
private:
    std::string name;
    int capacity; // максимальное число книг в филиале
    std::vector<Book> catalog; // коллекция книг, хранящихся в филиале

public:
    Branch(std::string_view name, int capacity);

    // Изменение характеристик объекта
    void setName(std::string_view newName);
    void setCapacity(int newCapacity);

    // Работа с коллекцией книг
    bool addBook(const Book& book); // false, если филиал переполнен
    bool removeBookById(int id);
    Book* findBookById(int id);
    const Book* findBookById(int id) const;
    bool isFull() const;

    // Получение отдельных характеристик
    std::string getName() const;
    int getCapacity() const;
    int getBooksCount() const;

    // Получение и вывод полной информации об объекте
    void printCatalog() const;
    void printShort() const; // короткая строка для списков выбора
};
