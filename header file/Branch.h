#pragma once

#include <string>
#include <vector>
#include "Book.h"

// Класс Branch описывает филиал библиотечной сети.
// Содержит коллекцию объектов Book — каталог филиала — и вместимость.
class Branch {
private:
    std::string name;
    int capacity;
    std::vector<Book> catalog;

public:
    Branch(const std::string& name, int capacity);

    // Работа с коллекцией книг
    bool addBook(const Book& book);   // false, если филиал переполнен
    bool removeBookById(int id);
    const Book* findBookById(int id) const;
    bool isFull() const;

    // Получение отдельных характеристик
    std::string getName() const;
    int getCapacity() const;
    int getBooksCount() const;

    // Получение и вывод полной информации об объекте
    void printCatalog() const;
    void printShort() const;
};
