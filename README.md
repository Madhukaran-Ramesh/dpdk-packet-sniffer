# DPDK Packet Sniffer

A high-performance packet sniffer built using **DPDK (Data Plane Development Kit)**. This tool enables fast and efficient packet capture by leveraging DPDK's kernel bypass technology. It features filtering, aggregation, and logging capabilities, making it ideal for real-time network traffic analysis and troubleshooting.

## Features
- High-speed packet capture using DPDK.
- Command-line filtering (by source IP, destination IP, port, or protocol).
- Real-time traffic aggregation (e.g., packet count per IP or protocol).
- Export traffic logs in PCAP format for analysis in tools like Wireshark.
- Optional integration with logging and visualization tools like Elasticsearch and Grafana.

## Requirements
- **Operating System**: Linux (tested on Ubuntu 20.04/22.04 and CentOS 8).
- **Dependencies**:
  - DPDK (latest stable version)
  - GCC or Clang (for building the project)
  - Make or CMake
  - Optional: Wireshark (for PCAP file analysis), Elasticsearch, Grafana
  
## Installation
1. Clone the repository:
   ```bash
   git clone https://github.com/your-username/dpdk-packet-sniffer.git
   cd dpdk-packet-sniffer
