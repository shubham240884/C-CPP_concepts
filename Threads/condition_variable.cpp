/*
 * This program illustrates the use of condition_variables and locks in C++.
 * The objective of the program is to create 3 threads and synchronize them
 * in such a way that the threads print the numbers in increasing order one
 * by one
 */

#include <iostream>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <math.h>

std::mutex mt;
std::condition_variable cv;

int i = 1;

void print_num(int id) {
    int count = 0;
    while (count < 5) {
        std::unique_lock <std::mutex> lk(mt);
        cv.wait(lk, [id]{return id == i;});
        std::cout << "thread : " << id << " val " << i + (count*3) << std::endl;
        i++;
        if (i == 4) {
            i = 1;
        }
        cv.notify_all();
        count++;
    }
}

int main() {
    std::thread t1(print_num, 1);
    std::thread t2(print_num, 2);
    std::thread t3(print_num, 3);
    t1.join();
    t2.join();
    t3.join();
    return 0;
}
