#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

struct Book
{
    std::string Author;
    std::string Title;
    int Year;
};

void saveToFile(const std::string &filename, const std::vector<Book> &data)
{

    std::fstream out(filename);

    for (const auto &book : data)
    {
        out << book.Author << "\t" << book.Title << "\t" << book.Year << std::endl;
    }

    out.close();
}

void loadFromFile(const std::string &filename, std::vector<Book> &outData)
{

    std::fstream in(filename);
    std::string line;
    while (std::getline(in, line))
    {
        std::stringstream ss(line);
        Book book;
        ss >> book.Author >> book.Title >> book.Year;
        outData.push_back(book);
    }

    in.close();
}

int main()
{

    std::vector<Book> books = {
        {"Pushkin", "1", 1800},
        {"Dostoevski", "2", 1810},
        {"Gogol'", "3", 1822}};

    saveToFile("books.txt", books);

    std::vector<Book> loadedBooks;
    loadFromFile("books.txt", loadedBooks);

    for (const auto &book : loadedBooks)
    {
        std::cout << "Author: " << book.Author << ", Title: " << book.Title << ", Year: " << book.Year << std::endl;
    }
}
