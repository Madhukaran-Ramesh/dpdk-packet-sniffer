#include <rte_eal.h>
#include <rte_ethdev.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    // Initialize DPDK Environment
    if (rte_eal_init(argc, argv) < 0) {
        fprintf(stderr, "Failed to initialize DPDK\n");
        return -1;
    }

    printf("DPDK Initialized Successfully!\n");

    // Cleanup and exit
    rte_eal_cleanup();
    return 0;
}
