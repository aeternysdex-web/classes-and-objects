#pragma once

#include <string>
#include <string_view>
#include <vector>

// Класс Book описывает один экземпляр издания в сети библиотек.
// Хранит состояние (название, автор, текущее местонахождение, историю
// перемещений) и умеет менять статус: выдана / возвращена / перемещена.
class Book {
private:
    int id;
    std::string title;
    std::string author;
    bool issued = false; // выдана ли книга читателю сейчас
    std::string currentLocation; // название филиала или "У читателя"
    std::vector<std::string> history; // вся история местонахождений книги

public:
    Book(int id, std::string_view title, std::string_view author,
        std::string_view initialBranchName);

    // Изменение характеристик объекта
    void setTitle(std::string_view newTitle);
    void setAuthor(std::string_view newAuthor);
    void markIssued(); // книгу забрал читатель
    void markReturned(std::string_view branchName); // книгу вернули в филиал
    void markMoved(std::string_view branchName); // книгу переместили между филиалами

    // Получение отдельных характеристик
    int getId() const;
    std::string getTitle() const;
    std::string getAuthor() const;
    bool isIssued() const;
    std::string getLocation() const;

    // Получение и вывод полной информации об объекте
    void printInfo() const;
    void printShort() const; // короткая строка для списков выбора
};
