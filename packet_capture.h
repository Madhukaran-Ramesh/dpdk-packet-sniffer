#ifndef PACKET_CAPTURE_H
#define PACKET_CAPTURE_H

#include <rte_mbuf.h>
#include <rte_ethdev.h>
#include <stdint.h>

/* Default Configuration Constants */
#define RX_RING_SIZE 1024
#define TX_RING_SIZE 1024
#define NUM_MBUFS 8192
#define MBUF_CACHE_SIZE 250
#define BURST_SIZE 32

/* Function Prototypes */

/**
 * @brief Initializes the DPDK environment and configures the Ethernet device.
 *
 * @param port_id The ID of the port to configure.
 * @return 0 on success
