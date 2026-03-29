#include "stdio.h"
#include "version.h"

void display_help(void)
{
    printf("\
ft_nmap %i,%i\n\
Usage: ft_nmap [OPTIONS]\n\
\n\
A multi-threaded IPv4 port scanner supporting various TCP/UDP scan techniques.\n\
\n\
MANDATORY (Choose one):\n\
  --ip <address/host>    The target IPv4 address or FQDN to scan.\n\
  --file <path>          Path to a file containing a list of targets.\n\
\n\
OPTIONS:\n\
  --help                 Display this help menu and exit.\n\
  --ports <ports>        Ports to scan. Accepts a range (1-80) or \n\
                         individual ports (22,80,443).\n\
                         [Default: 1-1024] [Max ports: 1024]\n\
  --speedup <number>     Number of parallel threads to use (0-250).\n\
                         [Default: 0]\n\
  --scan <type>          Specific scan type(s) to perform. Can be used \n\
                         multiple times for simultaneous scans.\n\
                         Types: SYN, NULL, ACK, FIN, XMAS, UDP.\n\
                         [Default: All types]\n\
\n\
SCAN TYPES:\n\
  SYN                    Stealthy half-open connection scan.\n\
  NULL                   Scan with no flags set in the TCP header.\n\
  ACK                    Used to map out firewall rulesets.\n\
  FIN                    Sends a FIN packet to observe the response.\n\
  XMAS                   Sets FIN, PSH, and URG flags.\n\
  UDP                    Scans for open UDP services.\n\
\n\
EXAMPLES:\n\
  ft_nmap --ip 127.0.0.1 --speedup 20\n\
  ft_nmap --file targets.txt --ports 1-500 --scan SYN --scan UDP\n\
  ft_nmap --ip example.com --ports 80,443,8080\n\
\n\
REPORTING:\n\
  The program resolves service types and displays a clear summary of \n\
  results including the execution timeframe.\n", VERSION_MAJOR, VERSION_MINOR);
}