#pragma once

#include <cstddef>
#include <memory>

#include "Network.h"

//RAII-compliant Wrapper for an IP frame
class IP_Wrapper
{
public:
    size_t frame_sz {};

    IP_Wrapper() = default; 
    IP_Wrapper(const Ethernet_Wrapper& eth, size_t payload_sz);

    inline IP::Frame* frame() const {
        return reinterpret_cast<IP::Frame*>(frame_buff.get());
    }

    //Destructor frees frame
    ~IP_Wrapper() = default;

private: 
    std::unique_ptr<char[]> frame_buff {nullptr};
};