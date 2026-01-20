TUN/TAP Device:
    A TUN/TAP device allows us to open a network interface that bypasses the kernel 
    OSI stack and directly read and write L2 packets from a virtual buffer. Can be thought of
    as opening a socket - except the data that is spad out out of a socket is after the kernel has processed the data up to L4. 

Eth Frame
    The structure of the frame that encompasses a network layer packet. Cyclic redundancy 
    check happens at the end of the packet to verify integrity of the frame. It is not handled in the 
    implementation. The Eth standard the code follows is Ethernet II. 
    +----------+----------+----------+----------+
    | Preamble | Dest MAC | Src MAC  |   Type   |
    | (7 bytes)| (6 bytes)| (6 bytes)|(2 bytes) |
    +----------+----------+----------+----------+
                      |
                      v
            +-------------------+
            |   Payload/Data    |
            |   (46-1500 bytes) |
            +-------------------+

ARP 
    A protocol that is used to dynamically map MAC addresses (L2) to IP addresses (L3).
    Doesn't fit cleanly into the OSI model - in the code I consider it an L2    void handle_arp(Arp_frame arp_frame);
 protocol to
    simply implementation. 

    ARP techinically has 4 different formats signalled by the opcode in the arp
    header. But RARP request and reply have been depreciated and the code only 
    handle ARP request and reply. 

    ARP handling algorithm:
        ?Do I have the hardware type in hwtype?
        Yes: (almost definitely)
        [optionally check the hardware length hwsize]
        ?Do I speak the protocol in protype?
        Yes:
            [optionally check the protocol length prosize]
            Merge_flag := false
            If the pair <protocol type, sender protocol address> is
                already in my translation table, update the sender
                hardware address field of the entry with the new
                information in the packet and set Merge_flag to true.
            ?Am I the target protocol address?
            Yes:
            If Merge_flag is false, add the triplet <protocol type,
                sender protocol address, sender hardware address> to
                the translation table.
            ?Is the opcode APR_REQUEST?  (NOW look at the opcode!!)
            Yes:
                Swap hardware and protocol fields, putting the local
                    hardware and protocol addresses in the sender fields.
                Set the opcode field to ARP_REPLY
                Send the packet to the (new) target hardware address on
                    the same hardware on which the request was received.