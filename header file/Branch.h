#pragma once

#include <string>
#include <vector>
#include "Book.h"

class Branch 
{
private:
    std::string name;
    int capacity;
    std::vector<Book> catalog;

public:
    Branch(const std::string& name, int capacity);

    bool addBook(const Book& book);   
    bool removeBookById(int id);
    const Book* findBookById(int id) const;
    bool isFull() const;

    std::string getName() const;
    int getCapacity() const;
    int getBooksCount() const;

    void printCatalog() const;
    void printShort() const;
};
