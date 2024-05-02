# 🐱 Feline Watchdog: Missing Cat Alert System

Feline Watchdog is an ESP32-based system designed to monitor the Wi-Fi connection between your cat's collar-mounted ESP32 device and a Raspberry Pi. If the Wi-Fi connection is lost, indicating that your cat may have wandered out of range, the system sends a notification to your iOS or Android device using the ntfy Linux tool running in a Docker container on the Raspberry Pi.

## Overview

Have you ever worried about your cat wandering too far from home? Feline Watchdog provides peace of mind by alerting you when your cat goes missing. By monitoring the Wi-Fi connection between your cat's collar-mounted ESP32 device and your Raspberry Pi, Feline Watchdog can detect when your cat is out of range and send you an alert notification on your mobile device.

## Prerequisites

- ESP32 microcontroller
- Raspberry Pi
- Docker installed on Raspberry Pi
- Pushover account (or another notification service supported by ntfy)

## Installation
1. If you want to create a Wi-Fi hotspot on your Raspberry Pi, you can use the provided bash script. First, make sure to connect your Raspberry Pi to the internet. Then, execute the script using the following commands:
   ```bash
   chmod +x myscript.sh
   ```
   ```bash
   bash create_hotspot.sh
   ```
   or
   ```bash
   ./create_hotspot.sh
   ```
1. Connect your ESP32 to your Raspberry Pi via Wi-Fi.
2. Install Docker on your Raspberry Pi if not already installed:

   
   curl -fsSL https://get.docker.com -o get-docker.sh
   sudo sh get-docker.sh
   

3. Clone this repository to your Raspberry Pi:

   
   git clone <repository_url>
   

## Usage

1. Set up a Pushover account or another notification service supported by ntfy, and obtain the necessary API keys.
2. Customize the Dockerfile to include your Pushover API keys or other notification service credentials.
3. Build the Docker image:

   
   cd FelineWatchdog
   docker build -t feline-watchdog .
   

4. Run the Docker container:

   
   docker run -d --name feline-watchdog-container feline-watchdog
   

5. The container will continuously monitor the Wi-Fi connection between the ESP32 and Raspberry Pi.
6. If the connection is lost, it will send a notification to your iOS or Android device using ntfy with the configured notification service.

## Contributing

Contributions are welcome! Feel free to submit pull requests or open issues if you encounter any problems.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
