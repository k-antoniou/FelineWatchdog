# Setting up a Wi-Fi Hotspot on Embedded System

# <div align="center">Option 1: Using hostapd</div>


### Step 1: Install hostapd
```bash
sudo apt update
sudo apt install hostapd
```

### Step 2: Configure hostapd

1. Edit the hostapd configuration file:
```bash
sudo nano /etc/hostapd/hostapd.conf
```


2. Add the following lines:
```bash
interface=wlan0
driver=nl80211
ssid=FelineWatchdog-Hotspot
hw_mode=g
channel=7
wmm_enabled=0
macaddr_acl=0
auth_algs=1
ignore_broadcast_ssid=0
wpa=2
wpa_passphrase=12345678
wpa_key_mgmt=WPA-PSK
wpa_pairwise=TKIP
rsn_pairwise=CCMP
```

3. Save and exit the file.

### Step 3: Start hostapd
```bash
sudo systemctl unmask hostapd
sudo systemctl enable hostapd
sudo systemctl start hostapd
```
# <div align="center">Option 2: Using dnsmasq</div>

### Step 1: Install dnsmasq

sudo apt install dnsmasq

### Step 2: Configure dnsmasq

1. Create a new configuration file:

    
```bash
sudo mv /etc/dnsmasq.conf /etc/dnsmasq.conf.orig
sudo nano /etc/dnsmasq.conf
```
2. Add the following lines to the file:

```bash
interface=wlan0
dhcp-range=192.168.4.2,192.168.4.20,255.255.255.0,24h
```


3. Save and exit the file.

### Step 3: Enable and start dnsmasq
```bash
sudo systemctl enable dnsmasq
sudo systemctl start dnsmasq
```

# <div align="center">Option 3: Using nmcli</div>

### Step 1: Create Wi-Fi hotspot with nmcli
```bash
nmcli dev wifi hotspot ifname wln0 con-name nano-hotspot ssid "FelineWatchdog-Hotspot" password "12345678"
```
### Step 2: Modify connection settings to enable autoconnect
```bash
nmcli con modify nano-hotspot connection.autoconnect yes
```