#include <cstdlib>
#include <string.h>
#include <arpa/inet.h>
#include <memory>

#include "Ethernet_Wrapper.h"
#include "Data_link.h"

void Ethernet_Wrapper::copy_payload(IP_Wrapper &ip_wrp)
{
    //Copy payload
    memcpy(frame->payload, ip_wrp.frame.get(), ip_wrp.frame_sz);
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


//Copy constructor will copy headers from eth_wrap and payload from arg
Ethernet_Wrapper::Ethernet_Wrapper(const Ethernet_Wrapper& eth_wrp, ARP::Frame* payload)
    : frame_sz (sizeof(Ethernet::Frame) + sizeof(ARP::Frame))
{
    //Copy headers
    if (eth_wrp.frame)
    {
        // Allocate new buffer
        auto buff = std::make_unique<char[]>(frame_sz);
        auto new_frame = reinterpret_cast<Ethernet::Frame*>(buff.get());
        
        // Copy headers field-by-field
        memcpy(new_frame->dmac, eth_wrp.frame->dmac, 6);
        memcpy(new_frame->smac, eth_wrp.frame->smac, 6);
        new_frame->ethertype = eth_wrp.frame->ethertype;
        
        //Copy payload
        memcpy(new_frame->payload, payload, sizeof(ARP::Frame));
        
        frame = std::unique_ptr<Ethernet::Frame>(
            reinterpret_cast<Ethernet::Frame*>(buff.release())
        );
    }
}