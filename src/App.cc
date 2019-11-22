// App.cc
// JMIRY
#include "App.h"
#include "SystemSwitch.h"
#include <iostream>
#include <cstring>
#include <thread>

#define BUF_SIZE 64

void
App::run()
{
    std::cout << "<<<<< HID-Porter >>>>>" << std::endl;

    // get HID node info
    char mouse[BUF_SIZE] = {0};
    char kbd[BUF_SIZE] = {0};
    std::cout << "--> Input info about host" << std::endl;
    std::cout << "--> Mouse device node : ";
    std::cin >> mouse;
    std::cout << "--> Keyboard device node : ";
    std::cin >> kbd;

    // find event handler of each device
    std::string mouseStr("/dev/input/");
    std::string kbdStr("/dev/input/");
    char buf[BUF_SIZE] = {0};
    findHandler(mouse, buf);
    mouseStr += buf;

    memset(buf, 0, BUF_SIZE);
    findHandler(kbd, buf);
    kbdStr += buf;

    // create host system & system switch instance
    HostSystem* host = new HostSystem(
        mouse,
        kbd,
        mouseStr.c_str(),
        kbdStr.c_str()
    );
    SystemSwitch sysSwitch = SystemSwitch();
    sysSwitch.addSystem(host);

    // get the number of VMs
    int cnt = 0;
    do
    {
        std::cout << "--> How many VMs want to attach? (up to 9): ";
        std::cin >> cnt;
    } while (cnt < 1 | cnt > 9);
    
    // add guests to switch
    mouseStr.clear();
    kbdStr.clear();
    mouseStr = "/dev/hidg";
    kbdStr = "/dev/hidg";
    char mouseNum[BUF_SIZE]={0};
    char kbdNum[BUF_SIZE]={0};
    for (int i = 0; i < cnt; ++i)
    {
        memset(mouseNum, 0, BUF_SIZE);
        memset(kbdNum, 0, BUF_SIZE);

        sprintf(mouseNum, "%d", i);
        sprintf(kbdNum, "%d", i+cnt);

        sysSwitch.addSystem(
            new System(
                std::string(mouseStr + mouseNum).c_str(),
                std::string(kbdStr + kbdNum).c_str()
            )
        );
    }

    // port HID device input data to designated system
    std::thread tPortMouse(
        &SystemSwitch::portMouse,
        &sysSwitch
    );
    std::thread tPortKBD(
        &SystemSwitch::portKBD,
        &sysSwitch
    );
    std::cout << "--> Porters are working :)" << std::endl;
    tPortMouse.join();
    tPortKBD.join();
}

void
App::findHandler(const char* node, char* buf)
{
    // assemble command
    std::string cmd("src/evhandler-finder.sh ");
    std::string path_node(node);
    cmd += path_node;

    // execute script
    FILE *fp = NULL;
    char* ret = nullptr;

    fp = popen(cmd.c_str(), "r");
    if (fp == NULL)
    {
        perror("[ERR] popen() failed");
        return;
    }
    ret = fgets(buf, BUF_SIZE, fp);
    if (ret == nullptr)
    {
        perror("[ERR] fgets() failed");
        return;
    }

    // trim '\n'
    buf[strlen(buf)-1] = '\0';
}