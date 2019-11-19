// SystemSwitch.h
// JMIRY
#include "System.h"
#include <vector>

class SystemSwitch
{
public:
    SystemSwitch() {}
    SystemSwitch(HostSystem* host)
        : m_host(host), m_active(0) { m_systems.reserve(9); }
    ~SystemSwitch() {}

public:
    void addSystem(System*);
    void deliver();
    int getSize() { return m_systems.size(); }
    int checkByte(char* buf);

private:
    HostSystem* m_host;
    std::vector<System*> m_systems;
    // index of active system (host=0, guest=1~9)
    int m_active;
};