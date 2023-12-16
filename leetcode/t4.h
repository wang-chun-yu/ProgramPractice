# ifndef  T3_H 
# define  T3_H
#include <string>
#include <iostream>

class Meanbase
{
public:
    Meanbase(){};
    virtual ~Meanbase(){};
    virtual std::string Mean(std::string line) = 0;
};

class MeanbaseA : public Meanbase
{
public:
    MeanbaseA(){};
    std::string Mean(std::string line) override;
};

class MeanbaseB : public Meanbase
{
public:
    MeanbaseB(){};
    std::string Mean(std::string line) override;
};

class MeanbaseC : public Meanbase
{
public:
    MeanbaseC(){};
    std::string Mean(std::string line) override;
};

class User
{
public:
    User(Meanbase* ptr): mean_ptr(ptr){};
    ~User(){ delete mean_ptr;};
    std::string useMean(std::string line)
    {
        if(mean_ptr != nullptr)
        {
            return mean_ptr->Mean(line);
        }
        std::cout << "error interpert!" << std::endl;
        return std::string("-1");
    }
private:
    Meanbase* mean_ptr = nullptr;
};

#endif