#include <iostream>
#include <fstream>
#include <vector>
#include <string>

void saveToFile(const std::string &filename, const std::vector<std::string> &data)
{
    std::fstream out(filename);

    for (const auto &word : data)
    {
        out << word << std::endl;
    }

    out.close();
}

void loadFromFile(const std::string &filename, std::vector<std::string> &outData)
{

    std::fstream in(filename);

    std::string word;
    while (std::getline(in, word))
    {
        std::cout << word << std::endl;
    }
    in.close();
}

int main()
{
    std::vector<std::string> words = {"a", "b", "c"};

    saveToFile("1.txt", words);
    std::vector<std::string> loadedWords;
    loadFromFile("1.txt", loadedWords);
    for (const auto &word : loadedWords)
    {
        std::cout << word << std::endl;
    }
}
