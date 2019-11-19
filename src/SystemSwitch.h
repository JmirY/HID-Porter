// SystemSwitch.h
// JMIRY
#include "System.h"
#include <vector>

#define MAX_SYS_LEN 10

class SystemSwitch
{
public:
    SystemSwitch()
        : m_active(0) { m_systems.reserve(MAX_SYS_LEN); }
    ~SystemSwitch() {}

public:
    void addSystem(System*);
    void deliver();
    int getSize() { return m_systems.size(); }
    int checkByte(char* buf);

private:
    std::vector<System*> m_systems;
    // index of active system (host=0, guest=1~9)
    int m_active;
};