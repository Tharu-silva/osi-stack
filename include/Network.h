#pragma once

#include "IP_Wrapper.h"

namespace IP
{
    struct Frame 
    {
        uint8_t version : 4;
        uint8_t ihl : 4;
        uint8_t tos;
        uint16_t len;
        uint16_t id;
        uint16_t flags : 3;
        uint16_t frag_offset : 13;
        uint8_t ttl;
        uint8_t proto;
        uint16_t csum;
        uint32_t saddr;
        uint32_t daddr;
        uint8_t options_and_payload[];  
    } __attribute__((packed));

} // namespace IP


namespace Network 
{    
    IP_Wrapper process_packet(const IP_Wrapper& input_ip);
};
