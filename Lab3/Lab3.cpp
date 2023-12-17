#include <windows.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include <algorithm>

CRITICAL_SECTION cs;
HANDLE event1, event2;
std::vector<double> arr;
int count = 0;

DWORD WINAPI Work(LPVOID lpParam) {
    double interval;
    std::cout << "Enter sleeptime interval: ";
    std::cin >> interval;
    std::cout << "Resulted array in worker: ";
    for (auto& item : arr) {
        if (item > 0) {
            item = sqrt(item);
        }
        std::cout << item << ' ';
        Sleep(interval * 1000);
    }
    std::cout << std::endl;
    SetEvent(event1);
    return 0;
}

DWORD WINAPI Count(LPVOID lpParam) {
    EnterCriticalSection(&cs);

    for (const auto& item : arr) {
        if (floor(item) == item) {
            ++count;
        }
    }

    LeaveCriticalSection(&cs);
    SetEvent(event2);
    return count;
}

int main() {
    setlocale(LC_ALL, "Russian");
    InitializeCriticalSection(&cs);
    EnterCriticalSection(&cs);
    event1 = CreateEvent(NULL, TRUE, FALSE, NULL);
    if (event1 == NULL) {
        return GetLastError();
    }
    event2 = CreateEvent(NULL, TRUE, FALSE, NULL);
    if (event2 == NULL) {
        return GetLastError();
    }

    int n;
    std::cout << "Enter size of array: ";
    std::cin >> n;
    arr.resize(n);

    srand(time(0));
    for (auto& item : arr) {
        item = rand() % 100 - 50;
    }

    std::cout << "Previous array: ";
    for (const auto& item : arr) {
        std::cout << item << ' ';
    }
    std::cout << std::endl;

    HANDLE hWork = CreateThread(NULL, 0, Work, NULL, 0, NULL);
    if (hWork == NULL) {
        return GetLastError();
    }
    HANDLE hCount = CreateThread(NULL, 0, Count, NULL, 0, NULL);
    if (hCount == NULL) {
        return GetLastError();
    }

    WaitForSingleObject(event1, INFINITE);
    std::cout << "Resulted array: ";
    for (const auto& item : arr) {
        std::cout << item << ' ';
    }
    std::cout << std::endl;
    LeaveCriticalSection(&cs);
    WaitForSingleObject(event2, INFINITE);
    std::cout << "Count of integers in array: " << count << std::endl;

    CloseHandle(hWork);
    CloseHandle(hCount);
    CloseHandle(event1);
    CloseHandle(event2);
    DeleteCriticalSection(&cs);

    return 0;
}
