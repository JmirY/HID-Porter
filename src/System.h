// System.h
// JMIRY
class System
{
public:
    // open file descriptor of input nodes
    System() {}
    System(const char* mouse_node , const char* kbd_node);
    virtual ~System();

    int getMouse() {return m_mouse_fd;}
    int getKBD()   {return m_kbd_fd;}

protected:
    int m_mouse_fd;
    int m_kbd_fd;
};

class HostSystem : public System
{
public:
    HostSystem() {}
    HostSystem(
        const char* mouse_node,
        const char* kbd_node,
        const char* mouse_event_node,
        const char* kbd_event_node
    );
    ~HostSystem();

    void lockEvent();
    void unlockEvent();

private:
    int m_mouse_event_fd;
    int m_kbd_event_fd;
};