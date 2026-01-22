#pragma once

#include <linux/if_ether.h>
#include <cstdint>
#include <unordered_map>

typedef uint64_t mac_t; 
typedef uint32_t ipv4_t; 

namespace Ethernet
{
    enum class Payloads
    {
        IPV4, 
        ARP,
        maxPayloads
    }; 

    struct Frame
    {
        unsigned char dmac[6];
        unsigned char smac[6];
        uint16_t ethertype; //Type of the payload. If >1536 then shows the protocol. 
        unsigned char payload[];
    } __attribute__((packed));

    inline bool payload_len(Ethernet::Frame* frame, uint16_t frame_sz)
    {
        return frame_sz - 14; 
    }

    //Returns the type of the ethernet payload
    Ethernet::Payloads payload_type(Ethernet::Frame* frame);
} 

namespace ARP 
{
    struct arp_ipv4
    {
        unsigned char smac[6];
        ipv4_t sip;
        unsigned char dmac[6];
        ipv4_t dip;
    } __attribute__((packed));

    struct Frame
    {
        uint16_t hwtype;
        uint16_t protype;
        unsigned char hwsize;
        unsigned char prosize;
        uint16_t opcode;
        ARP::arp_ipv4 data;
    } __attribute__((packed));   
}


class Data_link 
{
public:
    Data_link() = default;
    
    Ethernet::Frame process_packet(Ethernet::Frame* raw_packet, uint16_t frame_size);
private:
    std::unordered_map<ipv4_t, mac_t> ip_to_mac {};

    void handle_arp(ARP::Frame* arp_packet, uint16_t arp_len);
};

