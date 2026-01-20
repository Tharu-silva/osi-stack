#include <Network_Interface.h>
#include <Data_link.h>

int main()
{
    Network_Interface ni {Network_Interface::create_entry_point("dev0")};

    ssize_t frame_len {};
    Ethernet::Frame* eth_frame {ni.read_frame(frame_len)};
    Data_link dl {};

    dl.process_packet(eth_frame, frame_len);

    return 0;
}