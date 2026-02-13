#include "Network_Interface.h"
#include "Data_link.h"
#include <iostream>

int main()
{
    Network_Interface ni {Network_Interface::create_entry_point("dev0")};

    size_t frame_len {};
    
    while (true)
    {
        Ethernet_Wrapper input_eth {ni.read_frame(frame_len)};

        Ethernet_Wrapper out_eth {Data_link::process_packet(input_eth)};
        
        //Write output frame if not null
        if (out_eth.frame)
        {
            ni.respond_frame(out_eth);
        }
    }

    return 0;
}