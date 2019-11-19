// System.cc
// JMIRY
#include "System.h"
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>

System::System(const char* mouse_node, const char* kbd_node)
{
    m_mouse_fd = open(mouse_node, O_RDONLY | O_NONBLOCK);
    if (m_mouse_fd < 0)
    {
        perror("[ERR] Opening gadget mouse node failed");
    }

    m_kbd_fd = open(kbd_node, O_RDONLY | O_NONBLOCK);
    if (m_kbd_fd < 0)
    {
        perror("[ERR] Opening gadget keyboard node failed");
    }
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

    m_kbd_fd = open(kbd_node, O_RDONLY);
    if (m_kbd_fd < 0)
    {
        perror("[ERR] Opening host keyboard node failed");
    }

    m_mouse_event_fd = open(mouse_event_node, O_RDONLY);
    if (m_mouse_event_fd < 0)
    {
        perror("[ERR] Opening host mouse event node failed");;
    }

    m_kbd_event_fd = open(kbd_event_node, O_RDONLY);
    if (m_kbd_event_fd < 0)
    {
        perror("[ERR] Opening host keyboard event node failed");;
    }
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
    usleep(300000);
    if ( ioctl(m_mouse_event_fd, EVIOCGRAB, 1) < 0 )
    {
        perror("[ERR] Lock mouse event failed");
        std::cout << m_mouse_event_fd << std::endl;
    }

    if ( ioctl(m_kbd_event_fd, EVIOCGRAB, 1) < 0 )
    {
        perror("[ERR] Lock keyboard event failed");
        std::cout << m_kbd_event_fd << std::endl;
    }
}

void
HostSystem::unlockEvent()
{   
    if ( ioctl(m_mouse_event_fd, EVIOCGRAB, 0) < 0 )
    {
        perror("[ERR] Unlock mouse event failed");
    }

    if ( ioctl(m_kbd_event_fd, EVIOCGRAB, 0) < 0 )
    {
        perror("[ERR] Unlock keyboard event failed");
    }
}
