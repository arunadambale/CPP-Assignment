#include <iostream>
#include "Library.h"

using namespace LibrarySystem;
class Book {
class LibraryException : public std::exception {
protected:
    std::string message;

public:
    LibraryException(std::string msg, std::string func, int line) {
        message = msg + " | Function: " + func + " | Line: " + std::to_string(line);
    }

    const char* what() const noexcept override {
        return message.c_str();
    }
};

class BookNotFoundException : public LibraryException {
public:
    BookNotFoundException(std::string f, int l)
        : LibraryException("Book Not Found", f, l) {}
};

class MemberNotFoundException : public LibraryException {
public:
    MemberNotFoundException(std::string f, int l)
        : LibraryException("Member Not Found", f, l) {}
};

}
enum class BookStatus { AVAILABLE, ISSUED };
enum class BookGenre { PROGRAMMING, DATABASE, NETWORKING };

class Book {

private:
    int bookId;
    std::string title;
    std::string author;
    std::string isbn;
    BookStatus status;
    int quantity;
    int availableCopies;

public:

    Book();
    Book(int id, std::string t, std::string a, std::string i, int q);

    int getId() const;

    Book& operator++();      // pre increment
    Book operator++(int);    // post increment

    Book& operator--();
    bool operator==(const Book& b) const;
    bool operator<(const Book& b) const;

    std::string operator[](int index) const;

    friend std::ostream& operator<<(std::ostream&, const Book&);
    friend std::istream& operator>>(std::istream&, Book&);
};

class Person {

protected:
    int id;
    std::string name;
    std::string phone;

public:

    Person(int i, std::string n, std::string p);

    virtual void displayInfo() const = 0;

    virtual ~Person() {}
};

class Member : public Person {

private:
    int booksIssued;
    int* issuedBookIds;

public:

    Member(int id, std::string name, std::string phone);

    Member(const Member& m); // deep copy

    Member& operator=(const Member& m);

    bool operator==(const Member& m);

    void displayInfo() const override;

    ~Member();
};
class Librarian : public Person {

private:
    int employeeId;
    double salary;

public:

    Librarian(int id, std::string name, std::string phone,
              int empId, double sal);

    void displayInfo() const override;
};

template <typename T>
class Container {

private:
    T* data;
    int size;
    int capacity;

public:

    Container(int cap = 10) {
        capacity = cap;
        size = 0;
        data = new T[capacity];
    }

    Container(const Container& c) {
        size = c.size;
        capacity = c.capacity;

        data = new T[capacity];

        for(int i=0;i<size;i++)
            data[i] = c.data[i];
    }

    Container& operator=(const Container& c) {

        if(this!=&c) {
            delete[] data;

            size = c.size;
            capacity = c.capacity;

            data = new T[capacity];

            for(int i=0;i<size;i++)
                data[i] = c.data[i];
        }

        return *this;
    }

    void add(const T& item) {
        data[size++] = item;
    }

    T* find(int id) {
        for(int i=0;i<size;i++)
            if(data[i].getId()==id)
                return &data[i];
        return nullptr;
    }

    int getSize() const { return size; }

    ~Container() {
        delete[] data;
    }
};

class Transaction {

private:
    static int counter;

    int transactionId;
    int memberId;
    int bookId;

    std::string issueDate;
    std::string dueDate;
    std::string returnDate;

    double fineAmount;

    static const int fineRate = 5;

public:

    Transaction(int m, int b, std::string issue, std::string due);

    double calculateFine(int overdueDays);
};

class Library {

private:

    Container<Book> books;
    Container<Member> members;

    std::vector<Transaction> transactions;

    std::map<int,int> issuedBooks;

public:

    void addBook(const Book&);
    void removeBook(int id);
    void searchBook(int id);

    void registerMember(const Member&);
    void removeMember(int id);

    void issueBook(int bookId,int memberId);
    void returnBook(int bookId);

    void saveData();
    void loadData();
};



int main() {

    Library lib;
    int choice;

    do {

        try {

            std::cout<<"\n1 Add Book\n";
            std::cout<<"2 Remove Book\n";
            std::cout<<"3 Search Book\n";
            std::cout<<"4 Display Books\n";
            std::cout<<"5 Register Member\n";
            std::cout<<"6 Issue Book\n";
            std::cout<<"7 Return Book\n";
            std::cout<<"12 Save\n";
            std::cout<<"13 Load\n";
            std::cout<<"0 Exit\n";

            std::cin>>choice;

            switch(choice) {

                case 1:
                    // add book
                    break;

                case 6:
                    // issue book
                    break;

            }

        }

        catch(const LibraryException& e) {
            std::cout<<e.what()<<std::endl;
        }

    } while(choice!=0);

}