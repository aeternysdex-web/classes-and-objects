#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "Book.h"
#include "Branch.h"

using namespace std;

int readInt(const string& prompt) {
    string input;
    while (true) {
        cout << prompt;
        getline(cin, input);
        stringstream ss(input);
        int number;
        char extra;
        if (ss >> number && !(ss >> extra)) return number;
        cout << "Ошибка! Введите целое число.\n";
    }
}

string readLine(const string& prompt) {
    cout << prompt;
    string line;
    getline(cin, line);
    return line;
}

// Ищет книгу по ID. Если книга в одном из филиалов — branchIndex указывает
// на него, и возвращается указатель на книгу. Если книга у читателя —
// branchIndex = -1. Если книга не найдена нигде — возвращается nullptr.
Book* findBook(vector<Branch>& branches, vector<Book>& issued, int id, int& branchIndex) {
    for (size_t i = 0; i < branches.size(); ++i) {
        Book* book = branches[i].findBookById(id);
        if (book) {
            branchIndex = static_cast<int>(i);
            return book;
        }
    }
    for (auto& book : issued) {
        if (book.getId() == id) {
            branchIndex = -1;
            return &book;
        }
    }
    return nullptr;
}

void printBranchesShort(vector<Branch>& branches) {
    for (size_t i = 0; i < branches.size(); ++i) {
        cout << i + 1 << ". ";
        branches[i].printShort();
    }
}

void printEverything(vector<Branch>& branches, vector<Book>& issued) {
    for (auto& branch : branches) branch.printCatalog();
    cout << "У читателей:\n";
    if (issued.empty()) cout << "  Никого.\n";
    for (auto& book : issued) book.printShort();
}

// Даёт выбрать филиал из списка; переспрашивает, если он переполнен.
// 0 — отмена (возвращает -1).
int chooseFreeBranch(vector<Branch>& branches) {
    if (branches.empty()) {
        cout << "Филиалов пока нет.\n";
        return -1;
    }
    while (true) {
        printBranchesShort(branches);
        cout << "0. Отмена\n";
        int choice = readInt("Номер филиала: ");
        if (choice == 0) return -1;
        if (choice < 1 || choice > static_cast<int>(branches.size())) {
            cout << "Некорректный номер, попробуйте снова.\n";
            continue;
        }
        if (branches[choice - 1].isFull()) {
            cout << "Филиал \"" << branches[choice - 1].getName() << "\" переполнен, выберите другой.\n";
            continue;
        }
        return choice - 1;
    }
}

// ---------- Пункты главного меню ----------

void showBranches(vector<Branch>& branches) {
    if (branches.empty()) { cout << "Филиалов пока нет.\n"; return; }
    for (auto& branch : branches) branch.printCatalog();
}

void showBookInfo(vector<Branch>& branches, vector<Book>& issued) {
    printEverything(branches, issued);
    int id = readInt("Введите ID книги: ");
    int branchIndex;
    Book* book = findBook(branches, issued, id, branchIndex);
    if (!book) { cout << "Книга с таким ID не найдена.\n"; return; }
    book->printInfo();
}

void issueBook(vector<Branch>& branches, vector<Book>& issued) {
    for (auto& branch : branches) branch.printCatalog();
    int id = readInt("Введите ID книги для выдачи: ");
    int branchIndex;
    Book* book = findBook(branches, issued, id, branchIndex);
    if (!book || branchIndex == -1) { cout << "Книга с таким ID не найдена в филиалах.\n"; return; }

    Book copy = *book;
    copy.markIssued();
    branches[branchIndex].removeBookById(id);
    issued.push_back(copy);
    cout << "Книга \"" << copy.getTitle() << "\" выдана читателю.\n";
}

void returnBook(vector<Branch>& branches, vector<Book>& issued) {
    if (issued.empty()) { cout << "Сейчас ни одна книга не у читателей.\n"; return; }
    for (auto& book : issued) book.printShort();

    int id = readInt("Введите ID книги для возврата: ");
    int branchIndex;
    Book* book = findBook(branches, issued, id, branchIndex);
    if (!book || branchIndex != -1) { cout << "Книга с таким ID не числится у читателей.\n"; return; }

    cout << "Выберите филиал для возврата:\n";
    int destIndex = chooseFreeBranch(branches);
    if (destIndex == -1) { cout << "Возврат отменён.\n"; return; }

    Book copy = *book;
    copy.markReturned(branches[destIndex].getName());
    for (size_t i = 0; i < issued.size(); ++i) {
        if (issued[i].getId() == id) { issued.erase(issued.begin() + i); break; }
    }
    branches[destIndex].addBook(copy);
    cout << "Книга \"" << copy.getTitle() << "\" возвращена в \"" << branches[destIndex].getName() << "\".\n";
}

void moveBook(vector<Branch>& branches) {
    for (auto& branch : branches) branch.printCatalog();
    int id = readInt("Введите ID книги для перемещения: ");
    int branchIndex;
    vector<Book> empty; // выдаваемых книг тут не ищем
    Book* book = findBook(branches, empty, id, branchIndex);
    if (!book || branchIndex == -1) { cout << "Книга с таким ID не найдена в филиалах.\n"; return; }

    cout << "Книга сейчас в филиале \"" << branches[branchIndex].getName() << "\". Куда переместить?\n";
    printBranchesShort(branches);
    int destChoice = readInt("Номер филиала: ");
    if (destChoice < 1 || destChoice > static_cast<int>(branches.size())) { cout << "Некорректный номер.\n"; return; }
    int destIndex = destChoice - 1;

    if (destIndex == branchIndex) { cout << "Книга уже находится в этом филиале.\n"; return; }
    if (branches[destIndex].isFull()) { cout << "Филиал \"" << branches[destIndex].getName() << "\" переполнен.\n"; return; }

    Book copy = *book;
    copy.markMoved(branches[destIndex].getName());
    branches[branchIndex].removeBookById(id);
    branches[destIndex].addBook(copy);
    cout << "Книга \"" << copy.getTitle() << "\" перемещена в \"" << branches[destIndex].getName() << "\".\n";
}

// ---------- Управление ----------

void manage(vector<Branch>& branches, vector<Book>& issued, int& nextId) {
    int choice;
    do {
        cout << "\n----- Управление -----\n";
        cout << "1. Добавить филиал\n2. Добавить книгу\n3. Удалить книгу\n4. Удалить филиал\n0. Назад\n";
        choice = readInt("Выберите пункт: ");

        if (choice == 1) {
            string name = readLine("Название филиала: ");
            int capacity = readInt("Вместимость: ");
            branches.push_back(Branch(name, capacity));
            cout << "Филиал \"" << name << "\" добавлен.\n";

        }
        else if (choice == 2) {
            if (branches.empty()) { cout << "Сначала добавьте филиал.\n"; continue; }
            string title = readLine("Название книги: ");
            string author = readLine("Автор: ");
            cout << "Куда поместить книгу?\n";
            int branchIndex = chooseFreeBranch(branches);
            if (branchIndex == -1) { cout << "Добавление отменено.\n"; continue; }
            Book newBook(nextId, title, author, branches[branchIndex].getName());
            branches[branchIndex].addBook(newBook);
            cout << "Книга добавлена с ID " << nextId << ".\n";
            nextId++;

        }
        else if (choice == 3) {
            for (auto& branch : branches) branch.printCatalog();
            int id = readInt("Введите ID книги для удаления: ");
            int branchIndex;
            Book* book = findBook(branches, issued, id, branchIndex);
            if (!book) { cout << "Книга с таким ID не найдена.\n"; }
            else if (branchIndex == -1) { cout << "Эта книга сейчас у читателя, удалить её нельзя.\n"; }
            else {
                cout << "Книга \"" << book->getTitle() << "\" удалена.\n";
                branches[branchIndex].removeBookById(id);
            }

        }
        else if (choice == 4) {
            if (branches.empty()) { cout << "Филиалов пока нет.\n"; continue; }
            printBranchesShort(branches);
            int num = readInt("Номер филиала для удаления: ");
            if (num < 1 || num > static_cast<int>(branches.size())) { cout << "Некорректный номер.\n"; continue; }
            string name = branches[num - 1].getName();
            branches.erase(branches.begin() + (num - 1));
            cout << "Филиал \"" << name << "\" и все его книги удалены.\n";

        }
        else if (choice != 0) {
            cout << "Такого пункта меню нет.\n";
        }
    } while (choice != 0);
}

// ---------- main ----------

void printMenu() {
    cout << "\n========== Сеть библиотек ==========\n";
    cout << "1. Показать филиалы и книги в них\n";
    cout << "2. Показать информацию о книге\n";
    cout << "3. Выдать книгу читателю\n";
    cout << "4. Вернуть книгу в филиал\n";
    cout << "5. Переместить книгу между филиалами\n";
    cout << "6. Управление (добавить/удалить)\n";
    cout << "0. Выход\n";
    cout << "=====================================\n";
}

int main() {
    vector<Branch> branches;
    vector<Book> issued;
    int nextId = 1;

    branches.push_back(Branch("Филиал №1", 5));
    branches.push_back(Branch("Филиал №2", 5));
    branches[0].addBook(Book(nextId++, "Война и мир", "Л.Н. Толстой", branches[0].getName()));
    branches[0].addBook(Book(nextId++, "Мастер и Маргарита", "М.А. Булгаков", branches[0].getName()));
    branches[1].addBook(Book(nextId++, "Евгений Онегин", "А.С. Пушкин", branches[1].getName()));
    cout << "Загружены тестовые данные: 2 филиала.\n";

    int choice;
    do {
        printMenu();
        choice = readInt("Выберите пункт меню: ");
        switch (choice) {
        case 1: showBranches(branches); break;
        case 2: showBookInfo(branches, issued); break;
        case 3: issueBook(branches, issued); break;
        case 4: returnBook(branches, issued); break;
        case 5: moveBook(branches); break;
        case 6: manage(branches, issued, nextId); break;
        case 0: cout << "Завершение работы.\n"; break;
        default: cout << "Такого пункта меню нет, попробуйте снова.\n";
        }
    } while (choice != 0);

    return 0;
}