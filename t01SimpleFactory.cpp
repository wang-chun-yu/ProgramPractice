#include <iostream>
#include <string>
#include <memory>

//简易计算器：实现两个数的加减乘除
// 1 业务逻辑和界面分离：采用封装的思想。
// 2 对业务逻辑进行抽象，抽离出就有共性对象。这里可以抽象出二元运算符。
// 3 理清抽象对象个关系。这里使用继承模型，对二元运算符作为基类，加减乘除作为派生的子类。
// 4 设计给其他程序使用的接口。


class operation
{
    protected: //
        double _num1;
        double _num2;
    public:
        operation(double num1, double num2):_num1(num1),_num2(num2){};
        ~operation(){std::cout<<"operation delete"<<std::endl;};

        virtual double GetResult(){};
        virtual bool DeleteOperation(){};
};

class addoperation: public operation
{
    public:
        addoperation(double num1, double num2):operation(num1, num2){};
        ~addoperation(){std::cout<<"addoperation delete"<<std::endl;};
        double GetResult() override
        {
            double result = 0;
            result = _num1 + _num2;
            std::cout << "add result = "<< result << std::endl;
            return result;
        }    
        bool DeleteOperation() override
        {
            
        }
};

//只需要知道一个类：
//一个工厂，但能制造出多个产品
//可以随时制造和销毁

//只有new没有delete，会造成内存泄露.
/*======================================================
class OperationFactory //: public operation
{
    private:
        operation* p = nullptr;
    public:
        OperationFactory()
        {
            if(p != nullptr) delete p;
        };
        ~OperationFactory(){};
        void CreateInstance(char mark,double num1, double num2)
        {
            if(p != nullptr) delete p;
            switch (mark)
            {
            case '+':
                p = new addoperation(num1,num2); 
                break;
            case '-':
                break;
            default:
                break;
            }
        };
        double GetResult()
        {
            return p->GetResult();
        };
};
======================================================*/


//只需要知道一个类： mod：只知道一个类不行。
//一个工厂，但能制造出多个产品
//可以随时制造和销毁
class OperationFactory //: public operation
{
    // private:
    //     operation* p = nullptr;
    public:
        OperationFactory(){};
        ~OperationFactory(){};
        
        operation* CreateInstance(char mark,double num1, double num2)
        {
            operation* p = nullptr;
            switch (mark)
            {
            case '+':
                p = new addoperation(num1,num2); 
                break;
            case '-':
                break;
            default:
                break;
            }
            return p;
        };
        // double GetResult()
        // {
        //     return p->GetResult();
        // };
};



//每次创建一个实例，会new实例，可以通过delete
int main(int, char**) {

    //使用智能指针
    OperationFactory A;
    operation* p1 = A.CreateInstance('+',5,6);
    
    // std::shared_ptr<operation> p1 = ;

    double result = p1->GetResult();
    std::cout << result << std::endl;
    delete p1;
    
    auto p2 = A.CreateInstance('+',5.5,6.6);
    result = p2->GetResult();
    std::cout << result << std::endl;
    delete p2;
    
    // A.CreateInstance('+',5.5,6.6);
    // std::cout << A.GetResult() << std::endl;
}

//继续改进，使用智能指针
#if 0
class OperationFactory 
{
    public:
        OperationFactory(){};
        ~OperationFactory(){};
        
        operation* CreateInstance(char mark,double num1, double num2)
        {
            operation* p = nullptr;
            
            switch (mark)
            {
            case '+':
                p = new addoperation(num1,num2); 
                break;
            case '-':
                break;
            default:
                break;
            }
            return p;
        };
        // double GetResult()
        // {
        //     return p->GetResult();
        // };
};
#endif