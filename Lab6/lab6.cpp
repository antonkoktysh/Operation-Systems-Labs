#include <iostream>
#include <vector>
#include <thread>
#include <condition_variable>
#include <chrono>
#include <cmath>
#include <random>

std::condition_variable cv;
std::mutex cv_m;
bool ready = false;
std::vector<double> arr;
int count = 0;

void work() {
    std::cout << "Введите временной интервал (в миллисекундах): ";
    int interval;
    std::cin >> interval;

    for (auto& num : arr) {
        if (num > 0) {
            num = sqrt(num);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(interval));
        std::cout << num << ' ';
    }
    std::cout << std::endl;

    {
        std::lock_guard<std::mutex> lk(cv_m);
        ready = true;
    }
    cv.notify_one();
}

void countIntegers() {
    std::unique_lock<std::mutex> lk(cv_m);
    cv.wait(lk, [] {return ready; });

    for (const auto& num : arr) {
        if (floor(num) == num) {
            count++;
        }
    }

    ready = false;
    lk.unlock();
    cv.notify_one();
}

int main() {
    setlocale(LC_ALL, "Russian");
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis1(1, 15);
    std::uniform_int_distribution<> dis2(-50, 50);

    int n = dis1(gen);
    arr.resize(n);
    for (auto& num : arr) {
        num = dis2(gen);
    }

    std::cout << "Размерность массива: " << n << std::endl;
    std::cout << "Элементы массива: ";
    for (const auto& num : arr) {
        std::cout << num << ' ';
    }
    std::cout << std::endl;

    std::thread worker(work);
    std::thread counter(countIntegers);

    worker.join();
    counter.join();

    std::cout << "Количество целых чисел: " << count << std::endl;

    return 0;
}
