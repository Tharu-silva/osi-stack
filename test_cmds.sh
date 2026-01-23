sudo ip link set dev0 up
sudo ip addr add 192.168.100.1/24 dev dev0
sudo arping -I dev0 192.168.100.2