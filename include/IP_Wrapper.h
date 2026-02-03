#pragma once

#include "Network.h"
#include <cstddef>

//RAII-compliant Wrapper for an IP frame
class IP_Wrapper
{
public:
    IP_Wrapper() = default; 
    IP_Wrapper(const Ethernet_Wrapper& eth, size_t frame_sz);
    IP::Frame* frame {NULL};
    size_t frame_sz {};

    //Destructor frees frame
    ~IP_Wrapper();

private: 
};