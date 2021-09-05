#include <iostream>
#include "KernelInterface.hpp"

int main()
{
    KernelInterface Driver = KernelInterface("\\\\.\\rootkit_ping");

    int err = Driver.PingRootkit();

    while (true)
    {

    }
}
