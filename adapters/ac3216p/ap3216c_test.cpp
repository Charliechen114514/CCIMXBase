#include "ap3216c_adapter.h"
#include <iostream>
#include <thread>
#define DEV_FILE "/dev/ap3216c"
int main()
{
    AP3216CAdapter adapter;
    bool succ = adapter.bind_file(DEV_FILE);
    if(!succ){
        std::cerr << "Failed to bind the file! " << DEV_FILE << "\n";
        return -1;
    }
    while(1)
    {
        auto data_possible = adapter.sync_read_once();
        if(data_possible.has_value()){
            AP3216CData data = data_possible.value();
            std::cout << "get the res, ir: " << data.ir
                      << ", als: " << data.als
                      << ", ps: " << data.ps << std::endl;
        }else{
            std::cerr << "Failed to read the file! " << DEV_FILE << "\n";
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}




