#include "Book.h"
#include <iostream>

Book::Book(int id, const std::string& title, const std::string& author,
    const std::string& initialBranchName)
    : id(id), title(title), author(author), issued(false),
    currentLocation(initialBranchName) {
    history.push_back(initialBranchName);
}

void Book::setTitle(const std::string& newTitle) { title = newTitle; }
void Book::setAuthor(const std::string& newAuthor) { author = newAuthor; }

void Book::markIssued() {
    issued = true;
    currentLocation = "У читателя";
    history.push_back(currentLocation);
}

void Book::markReturned(const std::string& branchName) {
    issued = false;
    currentLocation = branchName;
    history.push_back(branchName);
}

void Book::markMoved(const std::string& branchName) {
    currentLocation = branchName;
    history.push_back(branchName);
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
    std::cout << "  ID " << id << ": \"" << title << "\", " << author << "\n";
}