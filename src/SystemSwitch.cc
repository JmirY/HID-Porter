// SystemSwitch.cc
// JMIRY
#include "SystemSwitch.h"
#include <iostream>
#include <fcntl.h>
#include <unistd.h>

#define BUF_SIZE 256

void
SystemSwitch::addSystem(System* sys)
{
    if (m_systems.size() == MAX_SYS_LEN)
    {
        perror("[ERR] Vector is full");
        return;
    }

    m_systems.push_back(sys);
}

// void
// SystemSwitch::deliver()
// {
//     char buf[BUF_SIZE];
//     while (1)
//     {
//         read(m_host->getMouse(), buf, BUF_SIZE);
//     }
// }

int
SystemSwitch::checkByte(char* buf)
{

}