#pragma once

#include "IP_Wrapper.h"

namespace IP
{
    struct Frame {};

} // namespace IP


namespace Network 
{    
    void process_packet(const IP_Wrapper& input_ip, IP_Wrapper& out_ip);
};
