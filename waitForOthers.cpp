#include <iostream>
#include <condition_variable>
#include <random>
#include <mutex>
#include <chrono>
#include <string>
// has only one funcntion
int num_threads = 10;
std::default_random_engine e;
std::uniform_int_distribution<> id(1,2000);

void thread(std::string s) {// is a function called thread mish an actual thread
     std::this_thread::sleep_for(std::chrono::milliseconds(id(e)));// sleeps then prints phase 1
     std::cout << "phase 1 " << std::endl;

     std::this_thread::sleep_for(std::chrono::milliseconds(id(e)));//then sleeps again then prints is done 

     std::cout << s << " is done" << std::endl;

}
//int main()
//{
//   
//    std::vector<std::thread> mythreads;
//    for (int i = 0; i < num_threads; i++) {         //create a number of threads to execute the function thread
//        mythreads.push_back(std::thread(thread, std::to_string(i)));
//    }
//    for (auto& t : mythreads)
//        t.join();
//  
//}

//we should synchronize so they wait for each other only can be done after all finish phase 1 