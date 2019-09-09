LOCAL_IPv4_ADDR=127.0.0.1
INTERNAL_IPV4_ADDR=127.0.0.2
REMOTE_IPv4_ADDR=127.0.0.1
REMOTE_INTERNAL_SUBNET=127.0.0.2

ip link add name ipip0 type ipip local ${LOCAL_IPv4_ADDR} remote ${REMOTE_IPv4_ADDR}
ip link set ipip0 up
ip addr add ${INTERNAL_IPV4_ADDR}/24 dev ipip0
ip route add ${REMOTE_INTERNAL_SUBNET}/24 dev ipip0
