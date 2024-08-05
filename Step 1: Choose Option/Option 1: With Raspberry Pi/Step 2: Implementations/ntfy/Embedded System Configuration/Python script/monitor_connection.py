import os
import time

# Function to check if ESP32 is connected to the Raspberry Pi's Wi-Fi hotspot
def is_connected():
    # Ping the ESP32 (replace 192.168.1.100 with the actual IP address of the ESP32)
    response = os.system("ping -c 1 192.168.1.100 > /dev/null 2>&1")
    return response == 0

# Function to trigger notification using ntfy
def send_notification():
    os.system("curl -d 'Cat missing. Find the Tobby' ntfy.sh/cat")

# Main loop
while True:
    if not is_connected():
        print("Connection with ESP32 lost. Triggering notification...")
        send_notification()
    else:
        print("Connection with ESP32 is fine.")

    # Check connection status every 10 seconds
    time.sleep(10)
