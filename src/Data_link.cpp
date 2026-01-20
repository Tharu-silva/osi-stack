#include "Data_link.h"

Eth_frame Data_link::process_packet(Eth_frame& raw_packet, uint16_t frame_size)
{
    //Check if its ARP then process here. Otherwise return an IPv4 Packet
}

//Parse ARP frame and update ip_to_mac cache
void Data_link::handle_arp(Arp_frame arp_frame)
{

}
