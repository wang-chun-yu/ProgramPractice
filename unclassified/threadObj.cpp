#include <iostream>
#include <chrono>
#include <thread>
#include <atomic>
#include <condition_variable>

// breif :
// 描述状态变量必须统一上锁.
// 如用a1=1/0,a2=1/0来表示4种状态,如果同时触发了更改的状态,就有可能状态更改到一半,其他状态接着更改.


class TimerBase {
public:
    TimerBase(int interval) : interval_(interval), running_(false), paused_(false)
    {
    }

    virtual ~TimerBase()
    {
        Stop();
    }

    void Start()
    {
        if (!running_) {
            running_ = true;
            paused_ = false;
            timer_thread_ = std::thread(&TimerBase::TimerLoop, this);
        }
    }

    void Pause()
    {
        if (running_ && !paused_) {
            paused_ = true;
            std::cout << "定时器暂停！" << std::endl;
        }
    }

    void Resume()
    {
        if (running_ && paused_) {
            paused_ = false;
            cond_var_.notify_one();
            std::cout << "定时器恢复！" << std::endl;
        }
    }

    void Stop()
    {
        if (running_) {
            running_ = false;
            if (paused_) {
                paused_ = false;
                cond_var_.notify_one();
            }
            if (timer_thread_.joinable()) {
                timer_thread_.join();
            }
        }
    }

protected:
    virtual void TimerCallback() = 0;

private:
    void TimerLoop()
    {
        while (running_) {
            // 是不是可以不要这个锁,
            std::unique_lock<std::mutex> lock(mutex_);

            if (paused_) {
                cond_var_.wait(lock); 
            } else {
                TimerCallback();
                // lock.unlock();

                std::this_thread::sleep_for(std::chrono::milliseconds(interval_));
            }
            printf("running.....\n");
        }
    }

protected:
    int interval_;
    std::atomic_bool running_;
    std::atomic_bool paused_;
    std::thread timer_thread_;
    std::mutex mutex_;
    std::condition_variable cond_var_;
};

class Timer : public TimerBase {
public:
    Timer(int interval) : TimerBase(interval)
    {
    }

protected:
    void TimerCallback() override
    {
        std::cout << "定时器触发！" << std::endl;
        printf("callback_id:%d\n", std::this_thread::get_id());
        // 在这里执行定时任务的代码
    }
};

#define TEST1
#ifdef TEST1
int main()
{
    int interval = 1000; // 间隔时间为1秒

    // 创建定时器对象
    Timer timer(interval);

    // 启动定时器
    timer.Start();

    // 主线程执行其他任务
    std::cout << "主线程在执行其他任务..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(5));

    // 暂停定时器
    timer.Pause();
    std::cout << "定时器已暂停" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(10));

    // 恢复定时器
    timer.Resume();
    std::cout << "定时器已恢复" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(3));

    // 停止定时器
    timer.Stop();
    std::cout << "定时器已停止" << std::endl;
    return 0;
}
#endif

// #define TEST2
#ifdef TEST2
int main()
{
    int interval = 1; // 间隔时间为1秒

    // 创建定时器对象
    Timer timer(interval);

    // 启动定时器
    timer.Start();

    // 主线程执行其他任务
    std::cout << "主线程在执行其他任务..." << std::endl;
    printf("main_id:%lx\n", std::this_thread::get_id());
    // std::this_thread::sleep_for(std::chrono::seconds(1));

    // 暂停定时器
    for(int i=0;i<100;++i)
    {
        printf("{%d}\n",i);
        timer.Pause();
        timer.Resume();
    }

    // timer.Pause();
    // std::cout << "定时器已暂停" << std::endl;
    // std::this_thread::sleep_for(std::chrono::seconds(3));

    // // 恢复定时器
    // timer.Resume();
    // std::cout << "定时器已恢复" << std::endl;
    // std::this_thread::sleep_for(std::chrono::seconds(3));

    // 停止定时器
    timer.Stop();
    std::cout << "定时器已停止" << std::endl;

    return 0;
}
#endif

// 1
// 0

// a1:0 
// a2:0

// a1:1
// a2:0

// a1:0
// a2:1

// a1:1
// a1:1

// 暂停
// running : 1
// pasued : 1

