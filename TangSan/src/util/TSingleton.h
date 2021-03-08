/*
* \file CSingleton
* \brief 线程安全的单例宏
*/
#ifndef TSINGLETON_H
#define TSINGLETON_H
#include <stdlib.h>
#include <mutex>
#include <iostream>

template<typename T>
class TSingleton
{
public:
    static T *instance(){
        static std::once_flag std_once_flag;
        std::call_once(std_once_flag, [&](){
            t = new (T)();
            atexit(destory);
        });
        return t;
    }

    ~TSingleton() = default;

private:
    static void destory(){
        delete t;
        t = nullptr;
    }

    TSingleton() = default; // 构造函数
    TSingleton(const TSingleton&) = delete; // 拷贝构造
    TSingleton& operator=(const TSingleton&) = delete; // 赋值运算符
    // default表示默认存在构造函数
    // delete表示默认删除拷贝构造函数和赋值运算符, 这样的对象就不能通过值传递，也不能进行赋值运算


private:
    static T* volatile t;
    // 编译器不会对volatile修饰的变量进行任何优化
    // 编译器对volatile修饰的变量，当要读取这个变量时，任何情况下都会从内存中读取，而不会从寄存器缓存中读取
};

template <typename T>
T* volatile TSingleton<T>::t = nullptr;

#endif // TSINGLETON_H
