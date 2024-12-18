#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <map>

enum Score
{
    Unsatisfactorily = 2,
    Satisfactorily,
    Good,
    Excellent
};

struct Student
{
    std::string Name;
    int Year;
    std::map<std::string, Score> RecordBook;
};
using Groups = std::map<std::string, std::vector<Student>>;

void saveToFile(const std::string &filename, const Groups &groups)
{

    std::fstream out(filename);
    for (const auto &gr : groups)
    {
        out << "Group " << gr.first << std::endl;
        for (const auto &stud : gr.second)
        {
            out << "Student " << stud.Name << "\t" << stud.Year << "\t" << std::endl;
            for (const auto &rec : stud.RecordBook)
            {
                out << rec.first << "\t" << rec.second << std::endl;
            }
            out << "---------" << std::endl;
        }
        out << "end of group" << std::endl;
    }
    out.close();
}

void loadFromFile(const std::string &filename, Groups &outGroups)
{
    std::fstream in(filename);

    std::string line;
    std::string currentGroup;
    Student currentStudent;
    bool readingStudent = false;

    while (std::getline(in, line))
    {
        if (line.find("Group: ") == 0)
        {
            currentGroup = line.substr(6);
            outGroups[currentGroup] = std::vector<Student>();
        }
        else if (line.find("Student ") == 0)
        {
            if (readingStudent)
            {
                outGroups[currentGroup].push_back(currentStudent);
                currentStudent = Student();
            }
            readingStudent = true;
            std::stringstream ss(line.substr(8));
            ss >> currentStudent.Name >> currentStudent.Year;
        }
        else if (line == "EndStudent")
        {
            outGroups[currentGroup].push_back(currentStudent);
            currentStudent = Student();
            readingStudent = false;
        }
        else if (line == "EndGroup")
        {
            continue;
        }
        else
        {
            std::string subject;
            int score;
            std::stringstream ss(line);
            ss >> subject >> score;
            currentStudent.RecordBook[subject] = static_cast<Score>(score);
        }
    }

    in.close();
}

int main()
{
    Groups groups = {
        {"Group1", {{"Student1", 2020, {{"Math", Good}, {"Physics", Excellent}}}, {"Student2", 2021, {{"Math", Satisfactorily}, {"Physics", Good}}}}},
        {"Group2", {{"Student3", 2022, {{"Math", Excellent}, {"Physics", Good}}}, {"Student4", 2023, {{"Math", Satisfactorily}, {"Physics", Unsatisfactorily}}}}}};

    saveToFile("groups.txt", groups);
    Groups loadedGroups;
    loadFromFile("groups.txt", loadedGroups);
    for (const auto &group : loadedGroups)
    {
        std::cout << "Group: " << group.first << std::endl;
        for (const auto &student : group.second)
        {
            std::cout << "  Student: " << student.Name << ", Year: " << student.Year << std::endl;
            for (const auto &record : student.RecordBook)
            {
                std::cout << "    " << record.first << ": " << record.second << std::endl;
            }
        }
    }
}
