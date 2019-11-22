// App.cc
// JMIRY
#include "App.h"
#include "SystemSwitch.h"
#include <iostream>
#include <cstring>
#include <thread>

#define HOST_MOUSE "/dev/hidraw2"
#define HOST_KBD "/dev/hidraw0"
#define HOST_MOUSE_EV "/dev/input/event17"
#define HOST_KBD_EV "/dev/input/event11"
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
    std::string mouseHandler("/dev/input/");
    std::string kbdHandler("/dev/input/");
    char buf[BUF_SIZE] = {0};
    findHandler(mouse, buf);
    mouseHandler += buf;

    memset(buf, 0, BUF_SIZE);
    findHandler(kbd, buf);
    kbdHandler += buf;

    // create host system & system switch instance
    HostSystem* host = new HostSystem(
        mouse,
        kbd,
        mouseHandler.c_str(),
        kbdHandler.c_str()
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
    for (int i = 0; i < cnt; ++i)
    {
        memset(mouse, 0, BUF_SIZE);
        memset(kbd, 0, BUF_SIZE);
        std::cout << "--> Input info about guest no." << i+1 << std::endl;
        std::cout << "--> Gadget mouse device node : ";
        std::cin >> mouse;
        std::cout << "--> Gadget keyboard device node : ";
        std::cin >> kbd;
        sysSwitch.addSystem( new System(mouse, kbd) );
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