#include "Branch.h"
#include <iostream>

Branch::Branch(std::string_view name, int capacity)
    : name(name), capacity(capacity) {}

void Branch::setName(std::string_view newName) { name = newName; }
void Branch::setCapacity(int newCapacity) { capacity = newCapacity; }

bool Branch::addBook(const Book& book) {
    // Ограничение предметной области: нельзя превышать вместимость филиала
    if (isFull()) return false;
    catalog.push_back(book);
    return true;
}

bool Branch::removeBookById(int id) {
    for (size_t i = 0; i < catalog.size(); ++i) {
        if (catalog[i].getId() == id) {
            catalog.erase(catalog.begin() + i);
            return true;
        }
    }
    return false;
}

Book* Branch::findBookById(int id) {
    for (auto& book : catalog) {
        if (book.getId() == id) return &book;
    }
    return nullptr;
}

const Book* Branch::findBookById(int id) const {
    for (const auto& book : catalog) {
        if (book.getId() == id) return &book;
    }
    return nullptr;
}

bool Branch::isFull() const {
    return static_cast<int>(catalog.size()) >= capacity;
}

std::string Branch::getName() const { return name; }
int Branch::getCapacity() const { return capacity; }
int Branch::getBooksCount() const { return static_cast<int>(catalog.size()); }

void Branch::printCatalog() const {
    std::cout << "=== Филиал \"" << name << "\" (книг: " << catalog.size()
               << "/" << capacity << ") ===\n";
    if (catalog.empty()) {
        std::cout << " В филиале нет книг.\n";
    }
    for (const auto& book : catalog) {
        book.printShort();
    }
}

void Branch::printShort() const {
    std::cout << name << " (книг: " << catalog.size() << "/" << capacity << ")\n";
}
