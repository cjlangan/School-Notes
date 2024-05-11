# Connecting to Aviary From Home on Ubuntu/Debian-Based

## Step 1: 
- open a terminal then enter the following commands one by one, ensuring no errors for each:
```bash
sudo apt update
sudo apt-get install net-tools
sudo apt-get install libnss3-tools
wget https://dl.technion.ac.il/docs/cis/public/ssl-vpn/ps-pulse-ubuntu-debian.deb
sudo dpkg -i ps-pulse-ubuntu-debian.deb
sudo /opt/pulsesecure/bin/setup_cef.sh install
```
- this will install the dependencies for Pulse, then install Pulse itself, then give Pulse superuser permissions so that it will be allowed to download and use a Chromium Embedded Framework (CEF)

## Step 2: 
- Search for Pulse as you would any other application and open it
- Click the `+` icon
- Enter any name for the VPN, such as "Umanitoba VPN"
- Set the server URL to `vpn.cc.umanitoba.ca/student`
- Click `add`, then click `connect`, then click `proceed`
- If prompted to download a CEF, choose yes

## Step 3: 
- Pulse should now redirect you to a website using the CEF it downloaded.
- Enter your UM Email and Password, and allow the login from your MFA method
- You should now be connected to the Umanitoba VPN, you may now connect to Aviary via SSH.

## Step 4:
- To disconnect: Open Pulse and click `disconnect`
- To reconnect: Open Pulse, click `connect`, and login using your Umanitoba information

## Notes:
- Pulse may not want to close properly/fully even when disconnected from the VPN, to forcefully close it:
    - Open System Monitor, click on the `Processes` tab
    - click the search icon and search for `pulse`
    - right click the `pulseUI` process and then choose `End`
    - Then confirm you want to end the process.
