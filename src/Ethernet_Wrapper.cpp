#include <cstdlib>
#include <string.h>
#include <arpa/inet.h>

#include "Ethernet_Wrapper.h"
#include "Data_link.h"

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


Ethernet::Payloads Ethernet_Wrapper::payload_type() const
{
    if (!frame) { return Ethernet::Payloads::maxPayloads; }

    switch (ntohs(frame->ethertype))
    {
        case ETH_P_IP:
            return Ethernet::Payloads::IPV4; 
        case ETH_P_ARP: 
            return Ethernet::Payloads::ARP; 
        default:
            return Ethernet::Payloads::maxPayloads; 
    } 
}
