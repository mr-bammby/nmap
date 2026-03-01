CC = gcc
CFLAGS = -Wall -O2

all: sender responder sniffer_pcap sniffer_raw

sender: sender.c
	$(CC) $(CFLAGS) -o sender sender.c

responder: responder.c
	$(CC) $(CFLAGS) -o responder responder.c

sniffer_pcap: sniffer_pcap.c
	$(CC) $(CFLAGS) -o sniffer_pcap sniffer_pcap.c -lpcap

sniffer_raw: sniffer_raw.c
	$(CC) $(CFLAGS) -o sniffer_raw sniffer_raw.c

clean:
	rm -f sender responder sniffer_pcap sniffer_raw
