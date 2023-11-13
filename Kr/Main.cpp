#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <chrono>
#include <sstream>
#include <string>

double Balance = 100.0; 

std::mutex balanceMutex;

void BalanceChange(const std::vector<double>& changes) {
    for (double change : changes) {
        bool operationCompleted = false;
        int maxAttempts = 3; 

        while (!operationCompleted && maxAttempts > 0) {
            std::this_thread::sleep_for(std::chrono::milliseconds(50));  

            std::unique_lock<std::mutex> lock(balanceMutex);
            double prevBalance = Balance;
            double newBalance = prevBalance + change;

            if (newBalance >= 0) {
                Balance = newBalance;
                operationCompleted = true;

                std::stringstream notification;
                std::cout << "было=" << prevBalance << ", операция " << (change >= 0 ? "+" : "-") << std::abs(change) << ", стало=" << newBalance;
                std::this_thread::sleep_for(std::chrono::milliseconds(50));  
                std::cout << notification.str() << std::endl;
            }
            else {
                
                maxAttempts--;
                if (maxAttempts > 0) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(100)); 
                }
                else {
                    std::cout << "Не удалось выполнить операцию " << (change >= 0 ? "пополнения" : "снятия") << " на сумму " << std::abs(change) << ". Максимальное количество попыток исчерпано." << std::endl;
                }
            }
        }
    }
}

void BalanceCheck() {
    std::lock_guard<std::mutex> lock(balanceMutex);
    std::cout << "Текущий баланс счёта: " << Balance << std::endl;
}

int main(int argc, char* argv[]) {
    std::vector<double> scenario1;
    setlocale(LC_ALL, "RUS");
    if (argc > 1) {
        for (int i = 1; i < argc; ++i) {
            double change;
            std::stringstream ss(argv[i]);
            ss >> change;
            scenario1.push_back(change);
        }
    }
    else {
        scenario1 = { -90.0, 20.0, 25.0 };
    }

    std::vector<double> scenario2 = { -50.0, -40.0, 100.0 };

    std::thread thread1(BalanceChange, scenario1);
    std::thread thread2(BalanceChange, scenario2);

    thread1.join();
    thread2.join();

    BalanceCheck();

    return 0;
}
