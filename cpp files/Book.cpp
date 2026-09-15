#include "Book.h"
#include <iostream>

Book::Book(int id, const std::string& title, const std::string& author)
    : id(id), title(title), author(author) {}

int Book::getId() const { return id; }
std::string Book::getTitle() const { return title; }
std::string Book::getAuthor() const { return author; }

void Book::printInfo() const {
    std::cout << "ID: " << id << "\n";
    std::cout << "Название: " << title << "\n";
    std::cout << "Автор: " << author << "\n";
}

void Book::printShort() const {
    std::cout << "  ID " << id << ": \"" << title << "\", " << author << "\n";
}
