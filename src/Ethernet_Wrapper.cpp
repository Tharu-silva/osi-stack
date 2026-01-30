#include "Ethernet_Wrapper.h"
#include <cstdlib>
#include <string.h>

Ethernet_Wrapper::~Ethernet_Wrapper()
{
    if (!frame) { return; } //Do nothing is frame is null
    free(frame);
}

void Ethernet_Wrapper::copy_payload(IP_Wrapper &ip_wrp)
{
    //Copy payload
    memcpy(frame->payload, ip_wrp.frame, ip_wrp.frame_sz);
}
