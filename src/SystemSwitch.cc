// SystemSwitch.cc
// JMIRY
#include "SystemSwitch.h"
#include <iostream>
#include <cstring>
#include <fcntl.h>
#include <unistd.h>

#define BUF_SIZE 8

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

void
SystemSwitch::portMouse()
{
    char buf[BUF_SIZE] = {0};
    int host_fd, guest_fd;
    int ret = 0, tmp = 0;

    host_fd = m_systems[0]->getMouse();
    while (1)
    {
        memset(buf, 0, BUF_SIZE);
        // read data
        ret = read(host_fd, buf, BUF_SIZE);
        if (ret < 0)
        {
            perror("[ERR] Reading host mouse fd failed");
            continue;
        }

        // check if user want to change data direction
        // if 'm_active' is host(= 0) then do not send data
        tmp = checkByte(buf);
        if (tmp >= 0 && m_active != tmp)
        {
            m_active = tmp;
            continue;
        }

        if (m_active)
        {
            // send data
            guest_fd = m_systems[m_active]->getMouse();
            ret = write(guest_fd, buf, BUF_SIZE);
            if (ret < 0)
            {
                perror("[ERR] Writing guest mouse fd failed");
                continue;
            }
        }
    }
}

int
SystemSwitch::checkByte(const char* buf)
{

}