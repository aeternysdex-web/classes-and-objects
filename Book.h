#pragma once

#include <string>
#include <vector>

// Класс Book описывает один экземпляр издания в сети библиотек.
// Хранит состояние (название, автор, текущее местонахождение, историю
// перемещений) и умеет менять статус: выдана / возвращена / перемещена.
class Book {
private:
    int id;
    std::string title;
    std::string author;
    bool issued;                       // выдана ли книга читателю сейчас
    std::string currentLocation;       // название филиала или "У читателя"
    std::vector<std::string> history;  // вся история местонахождений книги

public:
    Book(int id, const std::string& title, const std::string& author,
        const std::string& initialBranchName);

    // Изменение характеристик объекта
    void setTitle(const std::string& newTitle);
    void setAuthor(const std::string& newAuthor);
    void markIssued();                                 // книгу забрал читатель
    void markReturned(const std::string& branchName);   // книгу вернули в филиал
    void markMoved(const std::string& branchName);      // книгу переместили между филиалами

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