#include <linux/if.h>
#include <linux/if_tun.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <cstring> 
#include <memory>
#include <arpa/inet.h>

#include "Network_Interface.h"
#include "common.h"

Network_Interface Network_Interface::create_entry_point(const std::string& dev_name)
{
    LOG("Creating TUN/TAP device");
    struct ifreq ifr;
    int fd, err;

    if( (fd = open("/dev/net/tun", O_RDWR)) < 0 ) {
        std::cerr << "Cannot open TUN/TAP device" << '\n';
        exit(1);
    }

    memset(&ifr, 0, sizeof(ifr));

    /* Flags: IFF_TUN   - TUN device (no Ethernet headers)
     *        IFF_TAP   - TAP device
     *
     *        IFF_NO_PI - Do not provide packet information
     */
    ifr.ifr_flags = IFF_TAP | IFF_NO_PI;
    if(dev_name.size() > 0) {
        strncpy(ifr.ifr_name, dev_name.c_str(), IFNAMSIZ);
    }

    if( (err = ioctl(fd, TUNSETIFF, (void *) &ifr)) < 0 ){
        std::cerr << "ERR: Could not ioctl tun: " << strerror(errno) << '\n';
        close(fd);
        exit(1);
    }

    LOG("Created TAP device");
    return Network_Interface(fd);
}

Ethernet_Wrapper Network_Interface::read_frame(size_t& nread)
{
    constexpr size_t BUFF_LEN {2048};
    auto buff = std::make_unique<char[]>(BUFF_LEN);
    if (!buff)
    {
        perror("malloc");
        exit(1);
    }
    
    nread = read(m_tap_fd, buff.get(), BUFF_LEN);
    if (nread < 0) {
        perror("Reading from interface");
        exit(1);
    }

    auto frame_ptr = std::unique_ptr<Ethernet::Frame>(
    reinterpret_cast<Ethernet::Frame*>(buff.release())
    );

    return Ethernet_Wrapper(std::move(frame_ptr), nread);
}

ssize_t Network_Interface::respond_frame(Ethernet_Wrapper& out_eth)
{
    ssize_t nwrite {}; 
    nwrite = write(m_tap_fd, out_eth.frame.get(), out_eth.frame_sz);
    if (nwrite < 0)
    {
        perror("Writing to interface");
        exit(1);
    }

    
    return nwrite;
}