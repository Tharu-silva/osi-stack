#pragma once

#include <string>

//Class encapsulates a network entry point
class Network_stack
{
public: 
    Network_stack(int tap_fd): m_tap_fd(tap_fd)  
    {};

    //Creates a network entry point and associates a tap device
    static Network_stack create_entry_point(const std::string& dev_name);
private: 
    int m_tap_fd; 
};