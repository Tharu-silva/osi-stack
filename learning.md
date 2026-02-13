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
    header. But RARP request and reply have been depreciated and the logic only 
    handles ARP request and replies. 

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


IP 
    IP Packets have a fixed size header of 20 bytes. Then there are var length IP 
    options if ihl > 5, then comes the actual payload. We can think of the ip options as part
    of the payload, or simply as a header to the payload.

    Fragment reassembly algo would check if MF=0, then it would calc the total size of the datagram,
    Then it would lookup the datagram in some map and check if all byte ranges are covered. If not then does nothing
    otherwise it processes. If We get a MF=1 fragment we check if the size of datagram is known. If so, then check byte 
    ranges have been fuffiled and if this fragment completes it. If so then we process otherwise not. 

    Best DS to represent the recieved bytes of a datagram? 
        We can MAP datagram saddr, ID to a [ptr, recv, total_size] triple. 
        Where 
            ptr is a ptr to a vector containing each datagram in order (each time new frontier packet is observed we extend the vector)

            recv is the total number of bytes recieved

            total_size is the total size of the datagram or -1 if unknown

    Completion conditiosn
        MF==1 AND bytes_recieved == total_size
        OR
        MF==0 AND MF=1 recieved AND bytes_recieved == total_size

    IP Packet parsing algorithm:
        Is this the last necessary packet of a datagram?
        Yes:
            Lookup the rest of the packets in the datagram map
        No:
            Add this packet to the datagram accumulator data structure and respond with nothing