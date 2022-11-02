#include <iostream>
#include "Service/AvnService.h"
using namespace std;

int main()
{
    AvnService service;
//    service.start();

    thread mqthread(service.runMqReceiveLooper());
    mqthread.join();
    return 0;
}
