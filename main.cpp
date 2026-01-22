#include "Network_Interface.h"
#include "Data_link.h"
#include <iostream>

int main()
{
    Network_Interface ni {Network_Interface::create_entry_point("dev0")};

    ssize_t frame_len {};
    Data_link dl {};
    

    while (true)
    {
        Ethernet::Frame* eth_frame {ni.read_frame(frame_len)};
        dl.process_packet(eth_frame, frame_len);
    }

    return 0;
}