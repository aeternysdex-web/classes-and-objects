#include <iostream>
#include <string>
#include <vector>
#include "Book.h"
#include "Branch.h"

using namespace std;

int readInt(const string& prompt) {
    cout << prompt;
    int number;
    cin >> number;
    cin.ignore(1000, '\n');
    return number;
}

string readLine(const string& prompt) {
    cout << prompt;
    string line;
    getline(cin, line);
    return line;
}

void printBranches(const vector<Branch>& branches) {
    for (size_t i = 0; i < branches.size(); ++i) {
        cout << i + 1 << ". ";
        branches[i].printShort();
    }
}

const Book* findBook(const vector<Branch>& branches, int id, int& branchIndex) {
    for (size_t i = 0; i < branches.size(); ++i) {
        const Book* book = branches[i].findBookById(id);
        if (book) {
            branchIndex = static_cast<int>(i);
            return book;
        }
    }
    branchIndex = -1;
    return nullptr;
}

void showBranches(const vector<Branch>& branches) {
    for (const auto& branch : branches) branch.printCatalog();
}

void showBookInfo(const vector<Branch>& branches) {
    showBranches(branches);
    int id = readInt("Введите ID книги: ");
    int branchIndex;
    const Book* book = findBook(branches, id, branchIndex);
    if (!book) { cout << "Книга с таким ID не найдена.\n"; return; }
    book->printInfo();
}

void addBook(vector<Branch>& branches, int& nextId) {
    string title = readLine("Название книги: ");
    string author = readLine("Автор: ");
    cout << "В какой филиал добавить?\n";
    printBranches(branches);
    int choice = readInt("Номер филиала: ");
    if (choice < 1 || choice > static_cast<int>(branches.size())) { cout << "Некорректный номер.\n"; return; }
    int index = choice - 1;
    if (branches[index].isFull()) { cout << "Филиал \"" << branches[index].getName() << "\" переполнен.\n"; return; }

    branches[index].addBook(Book(nextId, title, author));
    cout << "Книга добавлена с ID " << nextId << ".\n";
    nextId++;
}

void deleteBook(vector<Branch>& branches) {
    showBranches(branches);
    int id = readInt("Введите ID книги для удаления: ");
    int branchIndex;
    const Book* book = findBook(branches, id, branchIndex);
    if (!book) { cout << "Книга с таким ID не найдена.\n"; return; }
    cout << "Книга \"" << book->getTitle() << "\" удалена.\n";
    branches[branchIndex].removeBookById(id);
}

void printMenu() {
    cout << "\n========== Сеть библиотек ==========\n";
    cout << "1. Показать филиалы и книги в них\n";
    cout << "2. Информация о книге\n";
    cout << "3. Добавить книгу\n";
    cout << "4. Удалить книгу\n";
    cout << "0. Выход\n";
    cout << "=====================================\n";
}

int main() {
    vector<Branch> branches;
    branches.emplace_back("Филиал №1", 5);
    branches.emplace_back("Филиал №2", 5);

    int nextId = 1;
    branches[0].addBook(Book(nextId++, "Война и мир", "Л.Н. Толстой"));
    branches[0].addBook(Book(nextId++, "Мастер и Маргарита", "М.А. Булгаков"));
    branches[1].addBook(Book(nextId++, "Евгений Онегин", "А.С. Пушкин"));
    cout << "Загружены тестовые данные: 2 филиала.\n";

    int choice;
    do {
        printMenu();
        choice = readInt("Выберите пункт меню: ");
        switch (choice) {
        case 1: showBranches(branches); break;
        case 2: showBookInfo(branches); break;
        case 3: addBook(branches, nextId); break;
        case 4: deleteBook(branches); break;
        case 0: cout << "Завершение работы.\n"; break;
        default: cout << "Такого пункта меню нет.\n";
        }
    } while (choice != 0);

    return 0;
}
