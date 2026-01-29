#pragma once

#include <string>
#include "Data_link.h"

//Class encapsulates a network entry point
class Network_Interface
{
public: 
    Network_Interface(int tap_fd): m_tap_fd(tap_fd)  
    {};

    //Creates a network entry point and associates a tap device
    static Network_Interface create_entry_point(const std::string& dev_name);

    Ethernet::Frame* read_frame(ssize_t& nread);
    ssize_t respond_frame(Ethernet_Wrapper& out_eth);

private: 
    int m_tap_fd; 
};