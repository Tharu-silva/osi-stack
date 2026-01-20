#pragma once 
#include <linux/if_ether.h>
#include <cstdint>
#include <unordered_map>

typedef uint64_t mac_t; 
typedef uint32_t ipv4_t; 

class Data_link 
{
public:
    Data_link() = default;
    
    Eth_frame process_packet(Eth_frame& raw_packet, uint16_t frame_size);
private:
    std::unordered_map<ipv4_t, mac_t> ip_to_mac {};

    void handle_arp(Arp_frame& arp_frame);
};

struct Eth_frame
{
    unsigned char dmac[6];
    unsigned char smac[6];
    uint16_t ethertype; //Type of the payload. If >1536 then shows the protocol. 
    unsigned char payload[];
} __attribute__((packed));

struct Arp_frame
{
    uint16_t hwtype;
    uint16_t protype;
    unsigned char hwsize;
    unsigned char prosize;
    uint16_t opcode;
    arp_ipv4 data;
} __attribute__((packed));

struct arp_ipv4
{
    unsigned char smac[6];
    ipv4_t sip;
    unsigned char dmac[6];
    ipv4_t dip;
} __attribute__((packed));