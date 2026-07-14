#!/usr/bin/env bash
set -euo pipefail

# Run the multi_thread_test harness using a file of sample addresses.
# Usage: ./multi_thread_test_addresses.sh

BINARY=./multi_thread_test.out
ADDRESS_FILE=./multi_thread_test_addresses.conf

if [[ ! -x "$BINARY" ]]; then
    echo "Building test harness..."
    make multi_thread_test.out
fi

cat > "$ADDRESS_FILE" <<'EOF'
127.0.0.1
192.168.1.1
10.0.0.5
8.8.8.8
1.1.1.1
45.33.32.156
EOF

echo "Using address file: $ADDRESS_FILE"
cat "$ADDRESS_FILE"

echo "============================================================"
echo "Running: $BINARY --file $ADDRESS_FILE --port 80-88 --scan SYN"
echo "============================================================"
"$BINARY" --file "$ADDRESS_FILE" --port 80-88 --scan SYN
