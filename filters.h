#ifndef FILTERS_H
#define FILTERS_H

#include <stdint.h>
#include <stdbool.h>
#include <rte_mbuf.h>

/* Function Prototypes */

/**
 * @brief Filters a packet based on IP, port, or protocol criteria.
 *
 * @param packet Pointer to the rte_mbuf containing the packet.
 * @param ip_filter IP address to filter (in uint32_t format, or 0 for no filtering).
 * @param port_filter Port to filter (0 for no filtering).
 * @param protocol_filter Protocol to filter (0 for no filtering).
 * @return true if the packet matches the filter, false otherwise.
 */
bool apply_filters(struct rte_mbuf *packet, uint32_t ip_filter, uint16_t port_filter, uint8_t protocol_filter);

#endif /* FILTERS_H */
