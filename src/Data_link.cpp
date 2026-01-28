#include "Data_link.h"
#include "common.h"
#include <iostream>
#include <arpa/inet.h>
#include <string.h>
#include <net/if_arp.h>

Ethernet::Frame* Data_link::process_packet(Ethernet::Frame* raw_frame, uint16_t frame_size)
{
    //Deep copy input frame
    Ethernet::Frame* out_eth {};

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
            ARP::Frame* out_arp = Data_link::handle_arp(
                        reinterpret_cast<ARP::Frame*>(raw_frame->payload), arp_len);
            
            //Don't construct reply frame if out_arp is NULL
            if (!out_arp) { break; }

            //Copy input eth frame
            out_eth = (Ethernet::Frame*) malloc(sizeof(Ethernet::Frame) + arp_len);
            memcpy(out_eth, raw_frame, sizeof(Ethernet::Frame)); //Copy headers
                
            //Swap dmac and smac
            Data_link::swap_mac(out_eth->dmac, out_eth->smac);

            //Set the payload as out_arp
            memcpy(out_eth->payload, out_arp, arp_len);
            free(out_arp);
            break; 
        }
        default: {
            LOG("Ethernet payload type is unsupported");
        }
    }

    return out_eth; //NULL if nothing to send back
}

//Parse ARP frame and update ip_to_mac cache
ARP::Frame* Data_link::handle_arp(ARP::Frame* arp_packet, uint16_t arp_len)
{
    ARP::Frame* arp_out {};

    //Check if hwtype and protype are spoken by the host
    if (ntohs(arp_packet->hwtype) != ETHERNET_HW ||
        ntohs(arp_packet->protype) != ETH_P_IP)
    {
        LOG("Arp hwtype or protype is not supported");
        exit(1);
    }

    mac_t source_mac = Data_link::convert_mac(arp_packet->data.smac);
    mac_t dest_mac = Data_link::convert_mac(arp_packet->data.dmac);

    ipv4_t source_ip = ntohl(arp_packet->data.sip);
    ipv4_t dest_ip = ntohl(arp_packet->data.dip);

    //The following logic assumes that all dest frames of ARP packets sent is the host IP
    //Conservative updates, only adds new entry when a sender wants to communicate with us
    
    //Follows RFC 826
    //Only update if mapping exists
    bool merge_flag {};
    if (ip_to_mac.find(source_ip) != ip_to_mac.end())
    { 
        ip_to_mac[source_ip] = source_mac; 
        merge_flag = true; 
    }

    if (ntohs(arp_packet->opcode) == ARPOP_REQUEST)
    {
        //Update sender info in ip_to_mac cache
        if (!merge_flag)
        { ip_to_mac[source_ip] = source_mac; }
        
        arp_out = new ARP::Frame(*arp_packet);

        //Swap ip
        ipv4_t dip {arp_out->data.dip};
        arp_out->data.dip = arp_out->data.sip;
        arp_out->data.sip = dip;
        
        //Swap mac
        Data_link::swap_mac(arp_out->data.dmac, arp_out->data.smac); 
        //Populate smac
        for (int i = 0; i < 6; ++i)
        { arp_out->data.smac[i] = my_mac[i]; }
    
        arp_out->opcode = htons(ARPOP_REPLY);
    }
    
    return arp_out;
}


Ethernet::Payloads Ethernet::payload_type(Ethernet::Frame* frame)
{
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

void Data_link::swap_mac(unsigned char* dmac, unsigned char* smac)
{
    for (int i = 0; i < 6; ++i)
    {
        unsigned char d_byte {dmac[i]};
        dmac[i] = smac[i];
        smac[i] = d_byte; 
    }
}
