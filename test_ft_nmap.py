import os
import subprocess
import pytest

BINARY = "./ft_nmap.out"
TARGET_FILE = "test_targets.txt"

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
    ("22,80,443", True),
    ("1-1025", False),  # Exceeds max ports (1024)
    ("0-80", False),     # Invalid port 0
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

# --- Targets & Output Structure Validation ---

def test_comma_separated_ips():
    res = run_cmd(["--ip", "127.0.0.1,8.8.8.8", "--port", "53", "--speedup", "10"])
    assert res.returncode == 0
    assert "127.0.0.1" in res.stdout
    assert "8.8.8.8" in res.stdout

def test_output_formatting():
    res = run_cmd(["--ip", "127.0.0.1", "--port", "80", "--scan", "SYN"])
    assert res.returncode == 0
    assert "Scan Configurations" in res.stdout
    assert "Scan took" in res.stdout
    assert "Port" in res.stdout
    assert "Service Name" in res.stdout
    assert "Results" in res.stdout
    assert "Conclusion" in res.stdout