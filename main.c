#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <rte_eal.h>
#include <rte_ethdev.h>
#include <rte_mbuf.h>

#define RX_RING_SIZE 128
#define TX_RING_SIZE 512
#define NUM_MBUFS 8192
#define MBUF_CACHE_SIZE 250
#define BURST_SIZE 32

static const struct rte_eth_conf port_conf_default = {
    .rxmode = {
        .max_rx_pkt_len = RTE_ETHER_MAX_LEN,
    },
};

static void
initialize_port(uint16_t port_id, struct rte_mempool *mbuf_pool) {
    struct rte_eth_conf port_conf = port_conf_default;
    const uint16_t rx_rings = 1, tx_rings = 0;
    int retval;
    uint16_t q;

    // Configure the Ethernet device
    retval = rte_eth_dev_configure(port_id, rx_rings, tx_rings, &port_conf);
    if (retval != 0) {
        rte_exit(EXIT_FAILURE, "Error with port configuration\n");
    }

    // Allocate and set up RX queues
    for (q = 0; q < rx_rings; q++) {
        retval = rte_eth_rx_queue_setup(port_id, q, RX_RING_SIZE,
                                        rte_eth_dev_socket_id(port_id), NULL, mbuf_pool);
        if (retval < 0) {
            rte_exit(EXIT_FAILURE, "Error setting up RX queue\n");
        }
    }

    // Start the Ethernet port
    retval = rte_eth_dev_start(port_id);
    if (retval < 0) {
        rte_exit(EXIT_FAILURE, "Error starting Ethernet port\n");
    }

    // Enable promiscuous mode
    rte_eth_promiscuous_enable(port_id);
}

int main(int argc, char *argv[]) {
    struct rte_mempool *mbuf_pool;
    uint16_t port_id = 0;

    // Initialize the Environment Abstraction Layer (EAL)
    int ret = rte_eal_init(argc, argv);
    if (ret < 0) {
        rte_exit(EXIT_FAILURE, "Error with EAL initialization\n");
    }

    // Create a memory pool for packet buffers
    mbuf_pool = rte_pktmbuf_pool_create("MBUF_POOL", NUM_MBUFS,
                                        MBUF_CACHE_SIZE, 0, RTE_MBUF_DEFAULT_BUF_SIZE,
                                        rte_socket_id());
    if (mbuf_pool == NULL) {
        rte_exit(EXIT_FAILURE, "Cannot create mbuf pool\n");
    }

    // Initialize the Ethernet port
    initialize_port(port_id, mbuf_pool);

    printf("Starting packet capture on port %u...\n", port_id);

    // Packet capture loop
    struct rte_mbuf *bufs[BURST_SIZE];
    while (1) {
        const uint16_t nb_rx = rte_eth_rx_burst(port_id, 0, bufs, BURST_SIZE);
        if (nb_rx > 0) {
            printf("Captured %u packets\n", nb_rx);

            // Process each packet
            for (uint16_t i = 0; i < nb_rx; i++) {
                struct rte_mbuf *mbuf = bufs[i];
                // Example: Print packet length
                printf("Packet %u: length = %u\n", i, rte_pktmbuf_pkt_len(mbuf));
                rte_pktmbuf_free(mbuf); // Free the packet buffer
            }
        }
    }

    // Cleanup (unreachable in this example)
    rte_eth_dev_stop(port_id);
    rte_eth_dev_close(port_id);
    rte_eal_cleanup();

    return 0;
}
