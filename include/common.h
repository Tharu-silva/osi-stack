#pragma once

#define LOG(msg) std::cout << "[LOG] " << msg << std::endl
const uint16_t ETHERNET_HW = 0x0001; //Symbolic constant for ETH hardware spec in an ARP packet
unsigned char my_mac[6] = {0x02, 0x00, 0x00, 0x00, 0x00, 0x01};