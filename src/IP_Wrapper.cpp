#include <cstdlib>
#include <string.h>

#include "IP_Wrapper.h"
#include "Ethernet_Wrapper.h"

IP_Wrapper::IP_Wrapper(const Ethernet_Wrapper& eth, size_t payload_sz)
        : frame_sz (payload_sz),
        frame_buff(std::make_unique<char[]>(payload_sz))
{
    //Copy frame mem
    memcpy(frame_buff.get(), eth.frame()->payload, payload_sz);
}
