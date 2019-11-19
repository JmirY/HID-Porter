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
    void portMouse();
    void portKBD();
    int getSize() { return m_systems.size(); }
    // return -1 if invalid command
    // return 0~9 index of designated system
    int checkKeyCombo(const char* buf);

private:
    std::vector<System*> m_systems;
    // index of system where data will be streamed
    // (host=0, guest=1~9)
    int m_active;
};