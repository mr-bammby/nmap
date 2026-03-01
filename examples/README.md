# UDP send + sniff examples

Files:
- `sender.c` — sends one UDP message and waits briefly for a response
- `responder.c` — simple UDP echo server (single request -> reply then exits)
- `sniffer_pcap.c` — capture UDP packets on an interface using libpcap
- `sniffer_raw.c` — capture UDP packets using a raw socket (requires root)
- `Makefile` — build targets

Build:

```sh
cd examples
make
```

Run steps (recommended order):

1. Start the responder (listens on port 9999):

```sh
sudo ./responder 9999
```

2. In another terminal start the pcap sniffer on loopback:

```sh
sudo ./sniffer_pcap lo 9999
```

3. Optionally start the raw sniffer (requires root):

```sh
sudo ./sniffer_raw  0 9999
```

4. Send one message with the sender (this will also wait for the echo reply):

```sh
./sender 127.0.0.1 9999
```

Notes:
- Sniffers require root privileges to capture raw packets or open libpcap on interfaces.
- `sniffer_pcap` uses a BPF filter `udp and port 9999` and prints payload hex+ascii.
- `sniffer_raw` uses a raw IP socket and prints UDP payload in hex.
