// SystemSwitch.cc
// JMIRY
#include "SystemSwitch.h"
#include <iostream>
#include <cstring>
#include <bitset>
#include <fcntl.h>
#include <unistd.h>

#define BUF_SIZE 8

SystemSwitch::~SystemSwitch()
{
    for (System* pSys : m_systems)
    {
        if (pSys != nullptr) delete pSys;
    }
}

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

void
SystemSwitch::portKBD()
{
    char buf[BUF_SIZE] = {0};
    int host_fd, guest_fd;
    int ret = 0;

    HostSystem* host = dynamic_cast<HostSystem*>(m_systems[0]);
    host_fd = host->getKBD();
    while (1)
    {
        memset(buf, 0, BUF_SIZE);
        // read data
        ret = read(host_fd, buf, BUF_SIZE);
        if (ret < 0)
        {
            perror("[ERR] Reading host keyboard fd failed");
            continue;
        }

        // check if user want to change data direction
        // if 'm_active' is host(= 0) then do not send data
        ret = checkKeyCombo(buf);
        if (ret >= 0 && ret < m_systems.size() && m_active != ret)
        {
            if (ret == 0)
                host->unlockEvent();
            else
                host->lockEvent();
            m_active = ret;
            continue;
        }

        if (m_active)
        {
            // send data
            guest_fd = m_systems[m_active]->getKBD();
            ret = write(guest_fd, buf, BUF_SIZE);
            if (ret < 0)
            {
                perror("[ERR] Writing guest keyboard fd failed");
                continue;
            }
        }
    }
}

int
SystemSwitch::checkKeyCombo(const char* buf)
{
    std::bitset<8>first_byte(buf[0]);
    std::bitset<8>third_byte(buf[2]);
    unsigned long third = third_byte.to_ulong();
    if (first_byte.to_ulong() == 4 && third > 29 && third < 40)
    {
        return third - 30;
    }
    return -1;
}