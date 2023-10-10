#include <iostream>
#include <string>
using namespace std;
class Student{
public:
    Student(string name = "", int age = 0, float score = 0.0f);  //普通构造函数
    Student(const Student &stu);  //拷贝构造函数
public:
    Student & operator=(const Student &stu);  //重载=运算符
    void display();
private:
    string m_name;
    int m_age;
    float m_score;
};
Student::Student(string name, int age, float score): m_name(name), m_age(age), m_score(score){ }
//拷贝构造函数
Student::Student(const Student &stu){
    this->m_name = stu.m_name;
    this->m_age = stu.m_age;
    this->m_score = stu.m_score;
    cout<<"Copy constructor was called."<<endl;
}
//重载=运算符
Student & Student::operator=(const Student &stu){
    this->m_name = stu.m_name;
    this->m_age = stu.m_age;
    this->m_score = stu.m_score;
    cout<<"operator=() was called."<<endl;
   
    return *this;
}
void Student::display(){
    cout<<m_name<<"的年龄是"<<m_age<<"，成绩是"<<m_score<<endl;
}

Student func(){
    Student s("小明", 16, 90.5);
    return s;
}

const Student func1(){
    Student s("小明", 16, 90.5);
    return s;
}

// 引用不能绑定到局部变量上
Student& func2(){
    Student s("小明", 16, 90.5);
    return s;

}

// 常引用不能绑定到局部变量上
const Student& func3(){
    Student s("小明", 16, 90.5);
    return s;
}

int main(int argv, char** argc)
{
    Student stu[4]{func(), func1(), func1(), func1()};
    for(int i=0; i<4; i++)
    {
        stu[i].display();
    }
}

// 当函数的返回值为类类型时，return 语句会返回一个对象，不过为了防止局部对象被销毁，
// 也为了防止通过返回值修改原来的局部对象，编译器并不会直接返回这个对象，而是根据这个
// 对象先创建出一个临时对象（匿名对象），返回该临时对象。

// 现代编译器都支持返回值优化技术，会尽量避免拷贝对象，以提高程序运行效率。