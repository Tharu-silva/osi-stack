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
        Ethernet::Frame* input_frame {ni.read_frame(frame_len)};
        
        Ethernet_Wrapper input_eth {input_frame, static_cast<size_t>(frame_len)};
        Ethernet_Wrapper out_eth {};

        dl.process_packet(input_eth, out_eth);
        

        //Write output frame if not null
        if (out_eth.frame)
        {
            ni.respond_frame(out_eth);
        }
    }

    return 0;
}