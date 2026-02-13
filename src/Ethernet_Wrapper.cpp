#include <cstdlib>
#include <string.h>
#include <arpa/inet.h>
#include <memory>

#include "Ethernet_Wrapper.h"
#include "Data_link.h"
#include "common.h"

void Ethernet_Wrapper::copy_payload(IP_Wrapper& ip_wrp)
{
    //Copy payload
    memcpy(this->frame()->payload, ip_wrp.frame(), ip_wrp.frame_sz);
}


Ethernet::Payloads Ethernet_Wrapper::payload_type() const
{
    if (!this->frame()) { return Ethernet::Payloads::maxPayloads; }

    switch (ntohs(this->frame()->ethertype))
    {
        case ETH_P_IP:
            return Ethernet::Payloads::IPV4; 
        case ETH_P_ARP: 
            return Ethernet::Payloads::ARP; 
        default:
            return Ethernet::Payloads::maxPayloads; 
    } 
}


//Constructor will construct a valid eth wrapper from the corresponding input frame + output payload
Ethernet_Wrapper::Ethernet_Wrapper(const Ethernet_Wrapper& input_eth, ARP::Frame* payload)
    : frame_sz (sizeof(Ethernet::Frame) + sizeof(ARP::Frame))
{
    //Copy headers
    Ethernet::Frame* input_frame {input_eth.frame()};
    if (input_frame)
    {
        // Allocate new buffer
        auto buff = std::make_unique<char[]>(frame_sz);
        auto new_frame = reinterpret_cast<Ethernet::Frame*>(buff.get());
        
        // Copy & Swap headers field-by-field
        memcpy(new_frame->dmac, input_frame->smac, 6);
        memcpy(new_frame->smac, my_mac, 6);
        new_frame->ethertype = input_frame->ethertype;
        
        //Copy payload
        memcpy(new_frame->payload, payload, sizeof(ARP::Frame));
        
        frame_buff = std::move(buff);
    }
}