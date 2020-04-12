// readersWriters.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <random>
#include <thread>
#include <mutex>
#include <chrono>
#include <shared_mutex>

std::random_device e;
std::uniform_int_distribution<> dist(1,9);
std::vector<int> v;             //in common a vector of integers
#define DATA_SIZE 100
#define NUM_TRIALS 10

std::shared_mutex wrt;              //initialize shared mutex

                                    /* Readers writer setup. The common data is the 
 * vector of integers v. The writers write a random
 * value from 1 to 9 and the next its negative such
 * that the total sum is 0. for example
 * [2,-2,2,-2,2,-2....]
 * The readers check that the sum in the vector is zero
 * if not it will print the sum (which means data is corrupted)
 */
/* You must not remove any of the code below. ADD to it sync
 * primites so it works. Basically using c++ to implement the
 * solution we saw in class (it is in the lecture notes)
 */
class Reader {
public:
    static int num;
    void operator() () {
        int sum = 0;
        wrt.lock_shared();                 //locking before starting to read  but many readers can read its the shared mutex (not exclusive ) multiple readers no writers
        for (auto x : v) {
            
            sum += x;
            
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }           // sums it up and should give zero
        wrt.unlock_shared();               //unlocking shared mutex after reading
        if(sum!=0) std::cout<< "sum is " << sum << std::endl; // if not zero he writes the sum so fi error 
    }
};

class Writer {
   
public:
    Writer() {
   }
    void operator() () {
        int value = dist(e);
        wrt.lock();             //locking before starting to write
        for (auto& x : v) {
            x = value;
            value = -value;
           
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
        wrt.unlock();           //unlocking after finishing writing;
    }
};

//int main()
//{
//    int value = 1;
//    for (int i = 0; i < DATA_SIZE; i++) { //initialize the vector such that sum of all elements is zero
//        v.push_back(value);
//        value = -value;
//    }
//    for (int i = 0; i < NUM_TRIALS; i++) { //number of trials to detect mistakes
//        std::cout << "Trial " << i << std::endl;
//        std::vector<std::thread> mythreads;       //vector containing all threads
//        for(int i=0;i<5;i++){
//            Reader r1, r2;
//            Writer w;
//            std::thread t1(r1);
//            std::thread t2(w);
//            std::thread t3(r2);
//            mythreads.push_back(std::move(t1));
//            mythreads.push_back(std::move(t2));
//            mythreads.push_back(std::move(t3));
//        }
//       for (auto& t : mythreads)
//            t.join();
//        std::cout << "----------------" << std::endl;
//    }
//    
//   
//}
