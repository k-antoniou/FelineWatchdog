#!/bin/bash

ESP32_IP="192.168.1.100"  # Replace with the actual IP address of your ESP32
NOTIFY_COMMAND="curl -d 'Cat missing. Find the Tobby' ntfy.sh/cat"

# Function to check if ESP32 is connected
is_connected() {
    ping -c 1 "$ESP32_IP" > /dev/null 2>&1
}

# Main loop
while true; do
    if ! is_connected; then
        echo "Connection with ESP32 lost. Triggering notification..."
        $NOTIFY_COMMAND
    else
        echo "Connection with ESP32 is fine."
    fi

    # Check connection status every 10 seconds
    sleep 10
done
