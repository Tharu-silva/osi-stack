#pragma once 

struct Eth_frame
{
    //Props represent structural info
};

class Data_link 
{
public:
    Data_link(Eth_frame raw_packet) : m_packet(raw_packet)
    {} 

private:
    Eth_frame m_packet;
};