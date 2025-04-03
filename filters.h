#include <rte_mbuf.h>
#include <rte_ether.h>
#include <rte_ip.h>
#include <rte_udp.h>
#include <rte_tcp.h>
#include <stdbool.h>

// Define the filter criteria
#define FILTER_DST_IP 0xC0A80001 // 192.168.0.1 in hexadecimal
#define FILTER_PROTOCOL IPPROTO_UDP // Filter for UDP packets

bool apply_filters(struct rte_mbuf *mbuf) {
    // Extract the Ethernet header
    struct rte_ether_hdr *eth_hdr = rte_pktmbuf_mtod(mbuf, struct rte_ether_hdr *);

    // Check if the packet is an IPv4 packet
    if (eth_hdr->ether_type != rte_cpu_to_be_16(RTE_ETHER_TYPE_IPV4)) {
        return false; // Not an IPv4 packet
    }

    // Extract the IPv4 header
    struct rte_ipv4_hdr *ip_hdr = (struct rte_ipv4_hdr *)(eth_hdr + 1);

    // Check the destination IP address
    if (ip_hdr->dst_addr != rte_cpu_to_be_32(FILTER_DST_IP)) {
        return false; // Destination IP does not match
    }

    // Check the protocol
    if (ip_hdr->next_proto_id != FILTER_PROTOCOL) {
        return false; // Protocol does not match
    }

    // If all criteria match, return true
    return true;
}
