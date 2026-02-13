#pragma once

#include <memory>

#include "Data_link.h"
#include "IP_Wrapper.h"

//RAII-compliant Wrapper for an ethernet frame
class Ethernet_Wrapper
{
public:
    size_t frame_sz {};


    //Make constructor that takes in a unique ptr to eth frame, frame_sz + payload and an Ip_Wrapper.
    //Initialises vars then copies frame from the Ip_wrapper

    Ethernet_Wrapper() = default; 
    Ethernet_Wrapper(std::unique_ptr<char[]> f, size_t frame_sz)
        : frame_buff(std::move(f)), frame_sz (frame_sz) {}

    //Construct Ethernet Wrapper from input frame + payload proto wrapper or ptr
    Ethernet_Wrapper(const Ethernet_Wrapper& input_eth, ARP::Frame* payload);
    Ethernet_Wrapper(const Ethernet_Wrapper& input_eth, const IP_Wrapper& ip_wrp);

    inline Ethernet::Frame* frame() const { 
        return reinterpret_cast<Ethernet::Frame*>(frame_buff.get()); 
    }

    //Returns the type of the ethernet payload
    Ethernet::Payloads payload_type() const;

    //Destructor frees frame
    ~Ethernet_Wrapper() = default;

    //Transfer ownership
    void copy_payload(IP_Wrapper& ip_wrp);
private: 
    std::unique_ptr<char[]> frame_buff {nullptr};

};