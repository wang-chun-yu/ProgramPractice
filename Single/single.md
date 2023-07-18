## 单例模式
### 使用场景
- 在对象初始化后，需要一直维持生命周期到进程结束。需要提供访问接口，在不同位置，不同线程访问都是同一个对象。比如说上点初始化一个电机，我们在状态管理的模块想获取它的状态，在控制模块想对它进行控制，需要保证操作的是同一对象。
### 背景
- 最简单的做法是使用一个全局变量。但是如果多个人维护一份代码，并不知道你的全局变量代表的含义，或是编码时不注意在多个地方进行初始化。这些情况编译器是不会进行提醒的。这个时候单例模式就出现了，虽然有各种实现，但我觉得一个完整的实现需要满足：在需要定义一个单例对象时使用该机制进行定义，那么其他违背单例的原则的行为需要在编译时被禁止的（如下例子，显式禁止了拷贝构造函数和复制构造函数，很明显这些操作都是违背了单例的思想）。
- 需要注意的是在哪里定义，也就是初始化。有的做法会提前定义好，有的做法是用到的时候再进行定义。用到的时候在初始化，就需要考虑多线程的情况，因为存在可能两个线程同时在初始化，这样就可能产生两个对象。所以就需要一些机制来保证。
- 网上教程会提及到的懒汉式：指没有提前初始化。饿汉式：指的是提前进行了初始化.
### 使用方式
1. 类的静态成员变量并提前进行初始化.
    - 使用类的静态成员变量是因为具有以下特性：
        - 静态成员变量属于类，不属于某一个具体的类对象。所有的类对象共用同一份内存数据。
        - 静态成员变量和普通静态变量一样，都在内存分区中的全局数据区分配内存，到程序结束时才释放。这就意味着，static成员变量不随对象的创建而分配内存，也不随对象的销毁而释放内存。而普通成员变量在对象创建时分配内存，在对象销毁时释放内存。
        - 静态成员变量必须初始化，而且只能在类体外进行。
    - 具体实现
        ```
        #include <iostream>
        #include <thread>
        #include <ctime>
        #include <unistd.h>
        
        
        
        class Singleton01 
        {
            private:
                static Singleton01* singleton01;//保存该对象的指向
            private:                            //禁止构造函数被显式调用，保证get_instance()是唯一的获取入口
                Singleton01(){}; 
                Singleton01(const Singleton01 &) = delete; //禁用复制构造函数，在编译阶段起提醒作用。
                Singleton01& operator=(const Singleton01 &) = delete;//禁用赋值构造函数，在编译阶段起提醒作用。
            public:
                static Singleton01* get_instance() 
                {
                    if(singleton01 == nullptr)
                    {
                        std::this_thread::sleep_for(std::chrono::seconds(1));//把实例化的时间延长，方便得到实验结果。
                        singleton01 = new Singleton01();
                    }
                    return singleton01;
                }
        };
        
        #define INIT1
        #ifdef INIT1
            Singleton01* Singleton01::singleton01 = Singleton01::get_instance(); //初始化
        #else
            Singleton01* Singleton01::singleton01 = nullptr; //未初始化
        #endif
        
        void threadFun1(int i)
        {
            // std::this_thread::sleep_for(std::chrono::seconds(1)); //不在同一个时间获取，避免不同线程同时获取实例
            // Singleton01 example;
            auto ptr = Singleton01::get_instance();
            std::cout << "cur thread name:" << std::this_thread::get_id()<<std::endl;
            std::cout << "ptr" << i <<"：" << ptr << std::endl;
        }
        
        int main(int, char**)
        {
        #ifndef INIT1        
        /* ======提前进行初始化，避免了多线程同时进行第一次赋值时都检测到未初始化 ======*/
            auto ptr = Singleton01::get_instance();
            std::cout << "ptr=" << ptr << std::endl;
        /* ======提前进行初始化，避免了多线程同时进行第一次赋值时都检测到未初始化 ======*/
        #endif
            std::thread threads[10];
            for (auto i=0; i<10; i++)
            {
                threads[i] = std::thread(threadFun1,i); 
            }
            for(auto i=0; i<10; i++)
            {
                threads[i].join();
            }
            return 0;
        }
        ```
    - 其关键点是静态成员变量在使用前需要进行初始化，避免了在第一次访问（即静态成员变量未初始化）时，如果有多个线程同时访问，可能会发生单例对象指针（这里是静态成员变量），指向不同内存地址。
    - 如果不想提前进行初始化，那可以在获取对象指针时进行加解锁。
2. 局部静态变量
    - 本质没啥区别，同样要注意多线程下，要不提前先初始化，要不增加互斥锁。（其他教程说有线程不安全，但下面代码没有提前初始化，也没有加互斥锁，但获取的地址还是同一个。）
    - 具体实现
        ```
        #include <iostream>
        #include <thread>
        #include <ctime>
        #include <unistd.h>



        class Singleton01 
        {
            private:
                static Singleton01* singleton01;//保存该对象的指向
            private:                            //禁止构造函数被显式调用，保证get_instance()是唯一的获取入口
                Singleton01(){}; 
                Singleton01(const Singleton01 &) = delete; //禁用复制构造函数，在编译阶段起提醒作用。
                Singleton01& operator=(const Singleton01 &) = delete;//禁用赋值构造函数，在编译阶段起提醒作用。
            public:
                static Singleton01* get_instance() 
                {
                    if(singleton01 == nullptr)
                    {
                        std::this_thread::sleep_for(std::chrono::seconds(1));//把实例化的时间延长，方便得到实验结果。
                        singleton01 = new Singleton01();
                    }
                    return singleton01;
                }
        };

        #define INIT1
        #ifdef INIT1
            Singleton01* Singleton01::singleton01 = Singleton01::get_instance(); //初始化
        #else
            Singleton01* Singleton01::singleton01 = nullptr; //未初始化
        #endif

        void threadFun1(int i)
        {
            // std::this_thread::sleep_for(std::chrono::seconds(1)); //不在同一个时间获取，避免不同线程同时获取实例
            // Singleton01 example;
            auto ptr = Singleton01::get_instance();
            printf("cur thread name: %d\n", std::this_thread::get_id());
            printf("ptr%d: %lx\n", i,ptr);
        }

        int main(int, char**)
        {
        #ifndef INIT1        
        /* ======提前进行初始化，避免了多线程同时进行第一次赋值时都检测到未初始化 ======*/
            auto ptr = Singleton01::get_instance();
            std::cout << "ptr=" << ptr << std::endl;
        /* ======提前进行初始化，避免了多线程同时进行第一次赋值时都检测到未初始化 ======*/
        #endif
            std::thread threads[10];
            for (auto i=0; i<10; i++)
            {
                threads[i] = std::thread(threadFun1,i); 
            }
            for(auto i=0; i<10; i++)
            {
                threads[i].join();
            }
            return 0;
        }
        ```    
3. 内存管理:上述用的对象指针是一个静态的函数对象，它会在进程结束的时候进行销毁。如果我们使用了智能指针来封装对象指针，那当使用到该对象的线程全部结束，该对象指针应该会自动释放。这个可以实验测试。因为当前没有用到该场景，就暂时不测试。
4. 单例类模板
    制作一个模板类，使运用该模板的类具备了单例的特性。
    - 4.1 用类封装一个接口  
    ```
    #ifndef __SINGLE_TEMPLATE_H__
    #define __SINGLE_TEMPLATE_H__
    
    template<typename T>
    class Instance
    {
    public:
        static T* getInstance()
        {
            static T instance;
            return &instance;
        }
    };
    #endif
    
    main.cpp:一个简单的例子
    
    ```
    很明显，使用该模板在多线程的场景，需要注意先初始化。
    - 4.2 在多线程场景，可以利用互斥锁和智能指针，可以达到的效果：初始化时多线程安全，线程不适用该对象时，对象的引用减1，当所有线程都退出时，会自动对其释放。测试结果：不需要使用互斥锁，因为只能指针是局部静态变量，所以当使用的所有子线程退出，只能指针的计数为1。
    ```
    #ifndef __SINGLE_TEMPLATE1_H__
    #define __SINGLE_TEMPLATE1_H__
    #include <memory>



    template<typename T>
    class Instance
    {
    private:
        Instance(){};
        Instance(const Instance & )=delete; 
        Instance& operator=(const Instance)=delete;   
    public:
        static std::shared_ptr<T> getInstance() //调用唯一入口
        {
            static std::shared_ptr<T> instance = std::make_shared<T>();
            // std::lock_guard<std::mutex> lck(mtx);
            return instance;
        }
    private:
        // static std::mutex mtx;
    };

    // template<typename T>
    // std::mutex Instance<T>::mtx;


    #endif
    ```