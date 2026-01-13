TUN/TAP Device:
    A TUN/TAP device allows us to open a network interface that bypasses the kernel 
    OSI stack and directly read and write L2 packets from a virtual buffer. Can be thought of
    as opening a socket - except the data that is spad out out of a socket is after the kernel has processed the data up to L4. 