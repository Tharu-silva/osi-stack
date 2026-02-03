#pragma once

#include <cstddef>
#include <memory>

#include "Network.h"

//RAII-compliant Wrapper for an IP frame
class IP_Wrapper
{
public:
    IP_Wrapper() = default; 
    IP_Wrapper(const Ethernet_Wrapper& eth, size_t frame_sz);
    std::unique_ptr<IP::Frame> frame {nullptr};
    size_t frame_sz {};

    //Destructor frees frame
    ~IP_Wrapper() = default;

private: 
};