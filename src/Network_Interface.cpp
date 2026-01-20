#include <linux/if.h>
#include <linux/if_tun.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <cstring> 

#include "Network_Interface.h"
#include "common.h"
Network_Interface Network_Interface::create_entry_point(const std::string& dev_name)
{
    LOG("Creating TUN/TAP device");
    struct ifreq ifr;
    int fd, err;

    if( (fd = open("/dev/net/tap", O_RDWR)) < 0 ) {
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
        return err;
    }

    return Network_Interface(fd);
}

Ethernet::Frame* Network_Interface::read_frame(ssize_t& nread)
{
    size_t BUFF_LEN {2048};
    char* buff = (char*) calloc(sizeof(char), BUFF_LEN);
    if (!buff)
    {
        perror("malloc");
        exit(1);
    }
    
    nread = read(m_tap_fd, buff, BUFF_LEN);
    if (nread < 0) {
        perror("Reading from interface");
        free(buff);
        exit(1);
    }


    return reinterpret_cast<Ethernet::Frame*>(BUFF_LEN);
}
