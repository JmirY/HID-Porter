// App.cc
// JMIRY
#include "App.h"
#include "SystemSwitch.h"
#include <iostream>
#include <cstring>

#define HOST_MOUSE "/dev/hidraw2"
#define HOST_KBD "/dev/hidraw0"
#define HOST_MOUSE_EV "/dev/input/event17"
#define HOST_KBD_EV "/dev/input/event11"
#define BUF_SIZE 64

void
App::run()
{
    std::cout << "<<<<< HID-Porter >>>>>" << std::endl;
    
    // create host system & system switch instance
    HostSystem* host = new HostSystem(
        HOST_MOUSE,
        HOST_KBD,
        HOST_MOUSE_EV,
        HOST_KBD_EV
    );
    SystemSwitch sysSwitch = SystemSwitch();
    sysSwitch.addSystem(host);

    // get the number of VMs
    int cnt = 0;
    do
    {
        std::cout << "How many VMs want to attach? (up to 9): ";
        std::cin >> cnt;
    } while (cnt < 1 | cnt > 9);
    
    // add guests to switch
    char g_mouse[BUF_SIZE] = {0};
    char g_kbd[BUF_SIZE] = {0};
    for (int i = 0; i < cnt; ++i)
    {
        memset(g_mouse, 0, BUF_SIZE);
        memset(g_kbd, 0, BUF_SIZE);
        std::cout << "Input info about guest no." << i+1 << std::endl;
        std::cout << "Gadget mouse device node : ";
        std::cin >> g_mouse;
        std::cout << "Gadget keyboard device node : ";
        std::cin >> g_kbd;
        sysSwitch.addSystem( new System(g_mouse, g_kbd) );
    }

    delete host;
}