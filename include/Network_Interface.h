#pragma once

#include <string>
#include "Data_link.h"
#include "Ethernet_Wrapper.h"

//Class encapsulates a network entry point
class Network_Interface
{
public: 
    Network_Interface(int tap_fd): m_tap_fd(tap_fd)  
    {};

    //Creates a network entry point and associates a tap device
    static Network_Interface create_entry_point(const std::string& dev_name);

    Ethernet_Wrapper read_frame(size_t& nread);
    ssize_t respond_frame(Ethernet_Wrapper& out_eth);

private: 
    int m_tap_fd; 
};