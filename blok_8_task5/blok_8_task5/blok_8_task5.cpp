// Task5

#include <iostream>
#include <list>
#include <cmath>
#include <string>


class Human
{
    public:
    std::string m_name;
    int m_age;

    Human(std::string name = "", int age = 0)
        : m_name(name), m_age(age)
    {
    }



    void dropHumen(Human* humans, int length)
    {
        int namber;
        std::string dropname;
        std::cout << "Enter number student";
        std::cin >> namber;
        std::cout << "Enter korekt name student";
        std::cin >> dropname;
        for (int Index = 0; Index < length; ++Index)
        {
            if (Index == namber)
                humans[Index].m_name = dropname;
            break;
        }

    }
};

class Student : public Human
{
public:
    std::string s_VNZ;
   
    std::list<int> mark;

  

    Student(std::string VNZ = "")
        :Human(), s_VNZ(VNZ)
    {
    }


    void addMark(int newmark)
    {
        this->mark.push_back(newmark);
    
    }
    void Print()
    {
        std::cout << std::endl;
        for (auto mark : this->mark)
        {
            std::cout << mark ;
        }
    }
   void GPA( )
    {
       int sum=0, n=0;
       int gpa;

       for (auto mark : this->mark)
       {
           sum=sum+mark;
           n++;
       }
       gpa=sum/n;
       std::cout <<"Hearty ball  :: " << gpa;
    }

};


int main()
{
    int numStudents = 0;
    do
    {
        std::cout << "How many students do you want to enter? ";
        std::cin >> numStudents;
    } while (numStudents <= 0);


    Student* students = new Student[numStudents];

        int newmark, n_mark;
    for (int index = 0; index < numStudents; ++index)
    {
        std::cout << "Enter name #" << index + 1 << ": ";
        std::cin >> students[index].m_name;
        std::cout << "Enter age #" << index + 1 << ": ";
        std::cin >> students[index].m_age;
        std::cout << "Enter VNZ #" << index + 1 << ": ";
        std::cin >> students[index].s_VNZ;
        std::cout << "Enter number mark #" << index + 1 << ": ";
        std::cin >> n_mark;
        for (int j = 0; j < n_mark; j++)
        {
            std::cout << "Enter mark #" << index + 1 << ": ";
            std::cin >> newmark;
            students[index].addMark(newmark);
        }
    }

    for (int index = 0; index < numStudents; ++index)
    {
        std::cout << "Student #  " << index;
        std::cout << " Name : " << students[index].m_name;
        std::cout << " VNZ" << students[index].s_VNZ;
        std::cout << " age of " << students[index].m_age;
        std::cout << " Mark "; students[index].Print();
        std::cout << " GPA "; students[index].GPA();

    }
    std::cout << "You want to change the student's name yes/no";
    Student student;
    std::string qw;
    std::cin >> qw;
    if (qw == "yes")
    {
        student.dropHumen(students, numStudents);
    }    
    
   

    delete[] students;
    return 0;
}