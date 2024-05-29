#include <linux/bpf.h>
#include <linux/pkt_cls.h>

#define SEC(NAME) __attribute__((section(NAME), used))

SEC("filter")
int drop_tcp_port(struct __sk_buff *skb) {
    // Define the port number to drop packets for
    // You can make this configurable from user space by using BPF maps
    unsigned short port = 4040;

    // Load transport layer protocol (TCP/UDP) header offset
    unsigned int transport_header_offset = 0;
    unsigned int network_header_offset = 0;

    // Load protocol from network layer
    unsigned int protocol = skb->protocol;

    // Load network header offset based on the protocol
    if (protocol == htons(ETH_P_IP)) {
        struct iphdr *iph = (struct iphdr *)(skb->data + skb->network_header);
        network_header_offset = iph->ihl * 4;
        if (iph->protocol != IPPROTO_TCP)
            return TC_ACT_OK;
    } else if (protocol == htons(ETH_P_IPV6)) {
        struct ipv6hdr *ipv6h = (struct ipv6hdr *)(skb->data + skb->network_header);
        network_header_offset = sizeof(struct ipv6hdr);
        if (ipv6h->nexthdr != IPPROTO_TCP)
            return TC_ACT_OK;
    } else {
        return TC_ACT_OK; // Not an IP packet
    }

    // Load transport header offset based on the network header offset
    if (skb->protocol == htons(ETH_P_IP)) {
        struct tcphdr *tcph = (struct tcphdr *)(skb->data + skb->network_header + network_header_offset);
        transport_header_offset = tcph->doff * 4;
    } else if (skb->protocol == htons(ETH_P_IPV6)) {
        struct tcphdr *tcph = (struct tcphdr *)(skb->data + skb->network_header + network_header_offset);
        transport_header_offset = sizeof(struct tcphdr);
    } else {
        return TC_ACT_OK; // Not an IP packet
    }

    // Load destination port number from the transport header
    unsigned short dest_port = 0;
    if (skb->protocol == htons(ETH_P_IP)) {
        struct tcphdr *tcph = (struct tcphdr *)(skb->data + skb->network_header + network_header_offset + transport_header_offset);
        dest_port = ntohs(tcph->dest);
    } else if (skb->protocol == htons(ETH_P_IPV6)) {
        struct tcphdr *tcph = (struct tcphdr *)(skb->data + skb->network_header + network_header_offset + transport_header_offset);
        dest_port = ntohs(tcph->dest);
    }

    // Drop packets destined for the specified port
    if (dest_port == port) {
        return TC_ACT_SHOT;
    }

    return TC_ACT_OK;
}

char _license[] SEC("license") = "GPL";
