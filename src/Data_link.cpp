#include "Data_link.h"
#include "common.h"
#include<iostream>

Ethernet::Frame Data_link::process_packet(Ethernet::Frame* raw_frame, uint16_t frame_size)
{
    LOG("Processing ethernet frame");


    switch (Ethernet::payload_type(raw_frame))
    {
        using namespace Ethernet;
        case Payloads::IPV4:
            LOG("Ethernet payload is an IPv4 packet");

            break;
        case Payloads::ARP:
            LOG("Ethernet payload is an ARP packet");

            uint16_t arp_len {Ethernet::payload_len(raw_frame, frame_size)};
            Data_link::handle_arp(
                reinterpret_cast<ARP::Frame*>(raw_frame->payload), arp_len);

            break; 
        default:
            LOG("Ethernet payload type is unsupported");
            exit(1);
    }
}

//Parse ARP frame and update ip_to_mac cache
void Data_link::handle_arp(ARP::Frame* arp_packet, uint16_t arp_len)
{
    LOG("TODO: Implement ARP parsing algorithm");
    return;
}
