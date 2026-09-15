#pragma once

#include <string>

// Класс Book описывает один экземпляр издания в сети библиотек.
class Book {
private:
    int id;
    std::string title;
    std::string author;

public:
    Book(int id, const std::string& title, const std::string& author);

    // Получение отдельных характеристик
    int getId() const;
    std::string getTitle() const;
    std::string getAuthor() const;

    // Получение и вывод полной информации об объекте
    void printInfo() const;   // ID, название, автор
    void printShort() const;  // короткая строка для списков
};
