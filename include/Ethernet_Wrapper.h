#pragma once

#include "Data_link.h"
#include "IP_Wrapper.h"

//RAII-compliant Wrapper for an ethernet frame
class Ethernet_Wrapper
{
public:
    Ethernet_Wrapper() = default; 
    Ethernet_Wrapper(Ethernet::Frame* frame, size_t frame_sz)
        : frame(frame), frame_sz (frame_sz) {}

    Ethernet::Frame* frame {NULL};
    size_t frame_sz {};

    //Destructor frees frame
    ~Ethernet_Wrapper();
    //Transfer ownership
    void copy_payload(IP_Wrapper& ip_wrp);
private: 
};