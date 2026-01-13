#pragma once

#include <string>

//Class encapsulates a network entry point
class Network_entry
{
public: 
    Network_entry(int tap_fd): m_tap_fd(tap_fd)  
    {};

    //Creates a network entry point and associates a tap device
    static Network_entry create_entry_point(const std::string& dev_name);
private: 
    int m_tap_fd; 
};