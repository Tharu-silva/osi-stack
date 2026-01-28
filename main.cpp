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
        Ethernet::Frame* output_frame {dl.process_packet(input_frame, frame_len)};

        //Write output frame

        //Free frames
        free(input_frame);
        free(output_frame);
    }

    return 0;
}