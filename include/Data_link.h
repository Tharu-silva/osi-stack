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

    inline uint16_t payload_len(uint16_t frame_sz)
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
    
    void process_packet(const Ethernet_Wrapper& input_eth, Ethernet_Wrapper& out_eth);
    
    //Converts mac from it's raw size to 
    static inline mac_t convert_mac(unsigned char* raw_mac)
    {
        mac_t res {};
        //Big-endian (Network byte order)
        for (int i = 0; i < 6; ++i)
        {
            res = (res << 8) | raw_mac[i];
        }
        return res; 
    }

    //Swaps dmac and smac
    static void swap_mac(unsigned char* dmac, unsigned char* smac);
private:
    std::unordered_map<ipv4_t, mac_t> ip_to_mac {};

    ARP::Frame* handle_arp(ARP::Frame* arp_packet, uint16_t arp_len);
};

