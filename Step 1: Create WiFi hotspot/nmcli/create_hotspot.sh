#!/bin/bash

# Create a Wi-Fi hotspot named "nano-hotspot" with SSID "FelineWatchdog-Hotspot" and password "12345678"
nmcli dev wifi hotspot ifname wln0 con-name nano-hotspot ssid "FelineWatchdog-Hotspot" password "12345678"

# Modify the connection settings to enable autoconnect
nmcli con modify nano-hotspot connection.autoconnect yes
