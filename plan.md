In the router in data_link process packet
The an IP wrapper is created that contains the IP frame
This is then passed into process packet of the network layer
When this returns with an IP packett this then gets wrapped in an ethernet wrapper
and returned from Data_link::process_packet

Define two notions in each wrapper class
    Move ownership of payload
        This func would take in the wrapper instance of the layer above
        It would then copy the payload into the correct place within the frame
        Then make the frame ptr of the wrapper instance NULL. Thus transferring ownership


    Move ownership of frame 


Ethernet_Wrapper
    Move_payload 
        Takes in an IP_Wrapper and transfers ownership of payload from the IP_Wrapper
        to the current instance. 

IP_Wrapper
    Frame* 
    frame_sz
    Default constructor (Initialises empty wrapper)
    Constructor
        The constructor takes in a Ethernet_Wrapper and deep copies the frame from the payload
    