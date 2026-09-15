#include "Book.h"
#include <iostream>

Book::Book(int id, std::string_view title, std::string_view author,
    std::string_view initialBranchName)
    : id(id), title(title), author(author),
      currentLocation(initialBranchName) {
    history.emplace_back(initialBranchName);
}

void Book::setTitle(std::string_view newTitle) { title = newTitle; }
void Book::setAuthor(std::string_view newAuthor) { author = newAuthor; }

void Book::markIssued() {
    issued = true;
    currentLocation = "У читателя";
    history.push_back(currentLocation);
}

void Book::markReturned(std::string_view branchName) {
    issued = false;
    currentLocation = branchName;
    history.emplace_back(branchName);
}

void Book::markMoved(std::string_view branchName) {
    currentLocation = branchName;
    history.emplace_back(branchName);
}

int Book::getId() const { return id; }
std::string Book::getTitle() const { return title; }
std::string Book::getAuthor() const { return author; }
bool Book::isIssued() const { return issued; }
std::string Book::getLocation() const { return currentLocation; }

void Book::printInfo() const {
    std::cout << "----- Информация об издании -----\n";
    std::cout << "ID: " << id << "\n";
    std::cout << "Название: " << title << "\n";
    std::cout << "Автор: " << author << "\n";
    std::cout << "Текущее местонахождение: " << currentLocation << "\n";
    std::cout << "История: ";
    for (size_t i = 0; i < history.size(); ++i) {
        std::cout << history[i];
        if (i + 1 < history.size()) std::cout << " -> ";
    }
    std::cout << "\n----------------------------------\n";
}

void Book::printShort() const {
    std::cout << " ID " << id << ": \"" << title << "\", " << author << "\n";
}
