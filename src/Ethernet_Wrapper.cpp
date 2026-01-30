#include "Ethernet_Wrapper.h"
#include <cstdlib>

Ethernet_Wrapper::~Ethernet_Wrapper()
{
    if (!frame) { return; } //Do nothing is frame is null
    free(frame);
}