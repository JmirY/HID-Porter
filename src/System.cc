// System.cc
// JMIRY
#include "System.h"
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>

System::System(const char* mouse_node, const char* kbd_node)
{
    m_mouse_fd = open(mouse_node, O_WRONLY | O_NONBLOCK);
    if (m_mouse_fd < 0)
    {
        perror("[ERR] Opening gadget mouse node failed");
    }
    std::cout << "[DBG] Gadget mouse fd opened : " << m_mouse_fd << std::endl;

    m_kbd_fd = open(kbd_node, O_WRONLY | O_NONBLOCK);
    if (m_kbd_fd < 0)
    {
        perror("[ERR] Opening gadget keyboard node failed");
    }
    std::cout << "[DBG] Gadget keyboard fd opened : " << m_kbd_fd << std::endl;
}

System::~System()
{
    close(m_mouse_fd);
    close(m_kbd_fd);
}

HostSystem::HostSystem(
    const char* mouse_node,
    const char* kbd_node,
    const char* mouse_event_node,
    const char* kbd_event_node
)
{
    m_mouse_fd = open(mouse_node, O_RDONLY);
    if (m_mouse_fd < 0)
    {
        perror("[ERR] Opening host mouse node failed");
    }
    std::cout << "[DBG] Host mouse fd opened : " << m_mouse_fd << std::endl;

    m_kbd_fd = open(kbd_node, O_RDONLY);
    if (m_kbd_fd < 0)
    {
        perror("[ERR] Opening host keyboard node failed");
    }
    std::cout << "[DBG] Host keyboard fd opened : " << m_kbd_fd << std::endl;

    m_mouse_event_fd = open(mouse_event_node, O_RDONLY);
    if (m_mouse_event_fd < 0)
    {
        perror("[ERR] Opening host mouse event node failed");;
    }
    std::cout << "[DBG] Host mouse event fd opened : " << m_mouse_event_fd << std::endl;

    m_kbd_event_fd = open(kbd_event_node, O_RDONLY);
    if (m_kbd_event_fd < 0)
    {
        perror("[ERR] Opening host keyboard event node failed");;
    }
    std::cout << "[DBG] Host keyboard event fd opened : " << m_kbd_event_fd << std::endl;
}

HostSystem::~HostSystem()
{
    close(m_mouse_fd);
    close(m_kbd_fd);
    close(m_mouse_event_fd);
    close(m_kbd_event_fd);
}

void
HostSystem::lockEvent()
{
    // sleep an while to prevent infinite input
    usleep(300000);
    if ( ioctl(m_mouse_event_fd, EVIOCGRAB, 1) < 0 )
    {
        perror("[ERR] Lock mouse event failed");
    }
    std::cout << "[DBG] Host mouse locked" << std::endl;

    if ( ioctl(m_kbd_event_fd, EVIOCGRAB, 1) < 0 )
    {
        perror("[ERR] Lock keyboard event failed");
    }
    std::cout << "[DBG] Host keyboard locked" << std::endl;

}

void
HostSystem::unlockEvent()
{   
    if ( ioctl(m_mouse_event_fd, EVIOCGRAB, 0) < 0 )
    {
        perror("[ERR] Unlock mouse event failed");
    }
    std::cout << "[DBG] Host mouse unlocked" << std::endl;

    if ( ioctl(m_kbd_event_fd, EVIOCGRAB, 0) < 0 )
    {
        perror("[ERR] Unlock keyboard event failed");
    }
    std::cout << "[DBG] Host keyboard unlocked" << std::endl;
}
