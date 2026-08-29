import os
import signal
import subprocess
import time
import pytest

BINARY = "./ft_nmap.out"
TARGET_FILE = "test_targets.txt"
TARGET_IP = "scanme.nmap.org"  # Known to be up and responsive for testing

# Map ft_nmap scan types to official nmap CLI flags
SCAN_MAP = {
    "SYN": "-sS",
    "NULL": "-sN",
    "ACK": "-sA",
    "FIN": "-sF",
    "XMAS": "-sX",
    "UDP": "-sU",
}

@pytest.fixture(scope="session", autouse=True)
def setup_environment():
    """Create temporary file targets for tests."""
    with open(TARGET_FILE, "w") as f:
        f.write("127.0.0.1\nscanme.nmap.org\n")
    yield
    if os.path.exists(TARGET_FILE):
        os.remove(TARGET_FILE)

def run_cmd(args):
    """Utility helper to run binary with sudo."""
    cmd = ["sudo", BINARY] + args
    result = subprocess.run(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
    return result

# --- Mandatory Parameter Tests ---

def test_no_args():
    res = run_cmd([])
    assert res.returncode != 0

def test_help_flag():
    res = run_cmd(["--help"])
    assert res.returncode == 0
    assert "Help Screen" in res.stdout
    assert "MANDATORY" in res.stdout

def test_missing_mandatory_ip_or_file():
    res = run_cmd(["--ports", "80"])
    assert res.returncode != 0

def test_both_ip_and_file():
    res = run_cmd(["--ip", "127.0.0.1", "--file", TARGET_FILE])
    assert res.returncode != 0

# --- Option & Boundary Validation Tests ---

@pytest.mark.parametrize("ports_arg,valid", [
    ("80", True),
    ("1-100", True),
    ("22,80,443,5555,33333", True),
    ("22,80-100,443", True),       # Mixed ranges and individual ports
    ("1-1025", False),             # Exceeds max ports limit (1024)
    ("0-80", False),                # Invalid port 0
    ("70000", False),              # Exceeds max IPv4 port (65535)
    ("80-", False),                 # Malformed range (trailing dash)
    ("-80", False),                 # Malformed range (leading dash)
    ("80--90", False),              # Malformed range (double dash)
    ("invalid", False)
])
def test_port_parsing(ports_arg, valid):
    res = run_cmd(["--ip", "127.0.0.1", "--port", ports_arg])
    if valid:
        assert res.returncode == 0
    else:
        assert res.returncode != 0

@pytest.mark.parametrize("speedup,valid", [
    ("0", True),    
    ("1", True),   
    ("150", True),
    ("250", True),
    ("251", False),   
    ("-1", False)
])
def test_speedup_bounds(speedup, valid):
    res = run_cmd(["--ip", "127.0.0.1", "--port", "80", "--speedup", speedup])
    if valid:
        assert res.returncode == 0
    else:
        assert res.returncode != 0

@pytest.mark.parametrize("scan_type,valid", [
    ("SYN", True),
    ("NULL", True),
    ("ACK", True),
    ("FIN", True),
    ("XMAS", True),
    ("UDP", True),
    ("INVALID_SCAN", False)
])
def test_scan_types(scan_type, valid):
    res = run_cmd(["--ip", "127.0.0.1", "--port", "80", "--scan", scan_type])
    if valid:
        assert res.returncode == 0
    else:
        assert res.returncode != 0

# --- Targets & Network Error Handling ---

def test_comma_separated_ips():
    res = run_cmd(["--ip", "127.0.0.1,8.8.8.8", "--port", "53", "--speedup", "10"])
    assert res.returncode == 0
    assert "127.0.0.1" in res.stdout
    assert "8.8.8.8" in res.stdout

@pytest.mark.parametrize("invalid_target", [
    "invalid.hostname.nonexistent.test",
    "256.256.256.256",
    "127.0.0.999"
])
def test_invalid_network_targets(invalid_target):
    """Ensure graceful exit on unresolvable hosts or invalid IP addresses."""
    res = run_cmd(["--ip", invalid_target, "--port", "80"])
    assert res.returncode != 0

# --- Target File Option Tests ---

def test_file_option_valid():
    """Verify scanning targets specified via a text file."""
    res = run_cmd(["--file", TARGET_FILE, "--port", "80", "--speedup", "10"])
    assert res.returncode == 0
    assert "127.0.0.1" in res.stdout
    assert "45.33.32.156" in res.stdout

def test_file_option_nonexistent():
    """Verify proper error exit when target file does not exist."""
    res = run_cmd(["--file", "nonexistent_file_12345.txt"])
    assert res.returncode != 0

def test_file_with_blank_lines(tmp_path):
    """Check target file parsing fails on blank lines (by design)."""
    target_file = tmp_path / "whitespace_targets.txt"
    target_file.write_text("\n127.0.0.1\n   \nscanme.nmap.org\n\n")
    
    res = run_cmd(["--file", str(target_file), "--port", "80", "--speedup", "10"])
    assert res.returncode != 0
    assert "Help Screen" in res.stdout

# --- Output Structure Validation ---

def test_output_formatting():
    res = run_cmd(["--ip", "127.0.0.1", "--port", "80", "--scan", "SYN"])
    assert res.returncode == 0
    assert "Scan Configurations" in res.stdout
    assert "Scan took" in res.stdout
    assert "Port" in res.stdout
    assert "Service Name" in res.stdout
    assert "Results" in res.stdout
    assert "Conclusion" in res.stdout

# --- Leaks, Threading & Signal Cleanup ---

def test_valgrind_memory_and_sockets():
    """Check for memory leaks and unclosed sockets/file descriptors."""
    cmd = [
        "sudo", "valgrind",
        "--leak-check=full",
        "--show-leak-kinds=all",
        "--track-fds=yes",       # Detects unclosed sockets
        "--error-exitcode=42",   # Forces Valgrind to exit with 42 on error
        BINARY, "--ip", "127.0.0.1", "--port", "80-85", "--speedup", "10"
    ]
    res = subprocess.run(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
    
    assert res.returncode != 42, f"Memory leak or open socket detected!\nValgrind output:\n{res.stderr}"
    assert res.returncode == 0

def test_valgrind_thread_safety():
    """Use Helgrind to check for thread synchronization errors."""
    cmd = [
        "sudo", "valgrind",
        "--tool=helgrind",
        "--error-exitcode=42",
        BINARY, "--ip", "127.0.0.1", "--port", "22,80", "--speedup", "5"
    ]
    res = subprocess.run(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
    
    assert res.returncode != 42, f"Thread race condition or lock error detected!\nHelgrind output:\n{res.stderr}"

def test_thread_deadlock_timeout():
    """Ensure threads do not hang the program indefinitely."""
    cmd = ["sudo", BINARY, "--ip", "127.0.0.1", "--port", "1-1000", "--speedup", "250"]
    try:
        res = subprocess.run(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, timeout=15)
        assert res.returncode == 0
    except subprocess.TimeoutExpired:
        pytest.fail("Program timed out! Threads are likely deadlocked or stuck waiting to join.")

def test_sigint_graceful_cleanup():
    """Verify that sending SIGINT during a scan terminates without segfaulting."""
    cmd = ["sudo", BINARY, "--ip", "127.0.0.1", "--port", "1-1024", "--scan", "UDP", "--speedup", "1"]
    
    proc = subprocess.Popen(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
    time.sleep(0.5)  # Allow threads and sockets to initialize
    
    proc.send_signal(signal.SIGINT)
    stdout, stderr = proc.communicate(timeout=5)
    
    assert proc.returncode != -signal.SIGSEGV, "Program crashed with SIGSEGV on SIGINT!"

# --- Performance & Speed Benchmarks vs Official Nmap ---

def run_ft_nmap_timing(scan_type, ports, speedup):
    """Run ft_nmap and return execution duration in seconds."""
    port_str = f"1-{ports}" if ports > 1 else "80"
    cmd = [
        "sudo", BINARY,
        "--ip", TARGET_IP,
        "--port", port_str,
        "--scan", scan_type,
        "--speedup", str(speedup)
    ]
    
    start = time.perf_counter()
    res = subprocess.run(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
    duration = time.perf_counter() - start
    
    assert res.returncode == 0, f"ft_nmap failed on {scan_type} ports={ports} speedup={speedup}:\n{res.stderr}"
    return duration

def run_official_nmap_timing(scan_type, ports, speedup):
    """Run official nmap with parallelism set to match ft_nmap total worker threads."""
    port_str = f"1-{ports}" if ports > 1 else "80"
    nmap_flag = SCAN_MAP[scan_type]
    
    # speedup 0 = main thread (1 worker)
    # speedup N = main thread + N worker threads (N + 1 workers)
    parallelism = speedup + 1
    
    cmd = [
        "sudo", "nmap", nmap_flag,
        "-p", port_str,
        "-n", "-Pn",
        f"--min-parallelism={parallelism}",
        f"--max-parallelism={parallelism}",
        TARGET_IP
    ]
    
    start = time.perf_counter()
    res = subprocess.run(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
    duration = time.perf_counter() - start
    
    assert res.returncode == 0, f"Official nmap failed on {scan_type} ports={ports}:\n{res.stderr}"
    return duration

# Matrix generation logic
MATRIX_SMALL_PORTS = [
    (scan, ports, speedup)
    for scan in SCAN_MAP.keys()
    for ports in [10, 30, 50]
    for speedup in [0, 25, 50, 100, 250]
]

MATRIX_LARGE_PORTS = [
    (scan, ports, speedup)
    for scan in SCAN_MAP.keys()
    for ports in [100, 500, 1024]
    for speedup in [25, 50, 100, 250]
]

BENCHMARK_MATRIX = MATRIX_SMALL_PORTS + MATRIX_LARGE_PORTS

@pytest.mark.parametrize("scan_type,ports,speedup", BENCHMARK_MATRIX)
def test_compare_speed_with_nmap(scan_type, ports, speedup):
    """Compare execution speed between official nmap and ft_nmap within a 50% margin."""
    
    ft_time = run_ft_nmap_timing(scan_type, ports, speedup)
    nmap_time = run_official_nmap_timing(scan_type, ports, speedup)
    
    diff_pct = ((ft_time - nmap_time) / nmap_time) * 100.0
    
    if diff_pct < 0:
        performance_str = f"{abs(diff_pct):.2f}% FASTER than nmap"
    else:
        performance_str = f"{diff_pct:.2f}% SLOWER than nmap"

    # Console readout during run
    print(
        f"\n[BENCHMARK] {scan_type:<5} | Ports: {ports:<4} | Speedup: {speedup:<3} "
        f"| ft_nmap: {ft_time:.3f}s | nmap: {nmap_time:.3f}s | Result: {performance_str}"
    )

    # Upper limit check (+50% slower threshold)
    assert ft_time <= nmap_time * 1.50, (
        f"ft_nmap is too slow! Took {ft_time:.3f}s vs nmap's {nmap_time:.3f}s ({performance_str})"
    )
    
    # Lower limit check (-20% faster threshold)
    assert ft_time >= nmap_time * 0.50, (
        f"ft_nmap executed suspiciously fast! Took {ft_time:.3f}s vs nmap's {nmap_time:.3f}s ({performance_str})"
    )