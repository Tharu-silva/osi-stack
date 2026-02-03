#pragma once

#include <memory>

#include "Data_link.h"
#include "IP_Wrapper.h"

//RAII-compliant Wrapper for an ethernet frame
class Ethernet_Wrapper
{
public:
    Ethernet_Wrapper() = default; 
    Ethernet_Wrapper(std::unique_ptr<Ethernet::Frame> f, size_t frame_sz)
        : frame(std::move(f)), frame_sz (frame_sz) {}

    //Copy constructor will copy headers from eth_wrap and payload from arg
    Ethernet_Wrapper(const Ethernet_Wrapper& eth_wrp, ARP::Frame* payload);

    std::unique_ptr<Ethernet::Frame> frame {nullptr};
    size_t frame_sz {};

    //Returns the type of the ethernet payload
    Ethernet::Payloads payload_type() const;

    //Destructor frees frame
    ~Ethernet_Wrapper() = default;

    //Transfer ownership
    void copy_payload(IP_Wrapper& ip_wrp);
private: 
};