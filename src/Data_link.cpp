#include "Data_link.h"
#include "common.h"

#include<iostream>

Ethernet::Frame Data_link::process_packet(Ethernet::Frame* raw_frame, uint16_t frame_size)
{
    LOG("Processing ethernet frame");

    switch (Ethernet::payload_type(raw_frame))
    {
        using namespace Ethernet;
        case Payloads::IPV4: {
            LOG("Ethernet payload is an IPv4 packet");
            break;
        }
        case Payloads::ARP: {
            LOG("Ethernet payload is an ARP packet");

            uint16_t arp_len {Ethernet::payload_len(raw_frame, frame_size)};
            Data_link::handle_arp(
                reinterpret_cast<ARP::Frame*>(raw_frame->payload), arp_len);

            break; 
        }
        default: {
            LOG("Ethernet payload type is unsupported");
            exit(1);
        }
    }

    return Ethernet::Frame{};
}

//Parse ARP frame and update ip_to_mac cache
void Data_link::handle_arp(ARP::Frame* arp_packet, uint16_t arp_len)
{
    LOG("TODO: Implement ARP parsing algorithm");
    return;
}

void print_frame_hex(unsigned char* buffer, ssize_t length)
{
    printf("=== Frame Hex Dump (%zd bytes) ===\n", length);
    for (ssize_t i = 0; i < length; i++) {
        printf("%02x ", buffer[i]);
        if ((i + 1) % 16 == 0) {
            printf("\n");
        } else if ((i + 1) % 8 == 0) {
            printf(" ");
        }
    }
    printf("\n");
}


Ethernet::Payloads Ethernet::payload_type(Ethernet::Frame* frame)
{
    LOG("Checking payload Type");
    switch (frame->ethertype)
    {
        case ETH_P_IP:
            return Payloads::IPV4; 
        case ETH_P_ARP: 
            return Payloads::ARP; 
        default:
            return Payloads::maxPayloads; 
    } 
}
