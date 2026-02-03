#include <cstdlib>
#include <string.h>

#include "IP_Wrapper.h"
#include "Ethernet_Wrapper.h"

IP_Wrapper::IP_Wrapper(const Ethernet_Wrapper& eth, size_t frame_sz)
        : frame_sz (frame_sz) 
{
    //Deep copy payload 
    frame = (IP::Frame*) malloc(frame_sz);
    memcpy(frame, eth.frame->payload, frame_sz);
}

IP_Wrapper::~IP_Wrapper()
{
    if (!frame) { return; } //Do nothing is frame is null
    free(frame);
}
