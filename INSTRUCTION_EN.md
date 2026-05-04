===============================================================================
RXB Core v0.3.0 Foxbat - Complete Guide for Windows
===============================================================================

TABLE OF CONTENTS:
1. Basic Installation
2. Windows Firewall Configuration
3. Creating Configuration File
4. Creating Your Own Seed Node
5. Passwords and Security
6. Supporting the RXB
7. Troubleshooting

===============================================================================
1. BASIC INSTALLATION
===============================================================================

IMPORTANT: Before starting the node you must install the blockchain bootstrap.
This is required because direct sync from genesis block is not supported.

STEP 1: Download bootstrap file
Go to: https://github.com/Heiwabitnull/rxb-core/releases/tag/v0.3.0-foxbat
Download: rxb-bootstrap-4852.tar.gz

STEP 2: Extract bootstrap
Open PowerShell and run:
tar -xzf rxb-bootstrap-4852.tar.gz -C %APPDATA%\RXB\

STEP 3: Install node binaries
Download rxb-core binaries and extract to folder e.g: C:\RXB\

STEP 4: Run node
Run: rxbd.exe

FIRST RUN:
- Node will create rxb.conf automatically with secure random password
- Blockchain synchronization will start automatically
- Node connects to bridge at 135.181.255.219:8327


===============================================================================
2. WINDOWS FIREWALL CONFIGURATION
===============================================================================

RXB uses port 8327 for P2P communication with other nodes.

Step 1: Open Windows Firewall
- Press Windows key
- Type: Windows Defender Firewall
- Click: Windows Defender Firewall with Advanced Security

Step 2: Create Inbound Rule
- In left panel click: Inbound Rules
- In right panel click: New Rule
- Select: Port -> Next
- Select: TCP
- Select: Specific local ports
- Enter: 8327
- Click: Next
- Select: Allow the connection
- Click: Next
- Check all profiles (Domain, Private, Public)
- Name: RXB Core P2P Port 8327
- Click: Finish

Step 3: Create Outbound Rule
- In left panel click: Outbound Rules
- Repeat steps from above
- Name: RXB Core P2P Outbound 8327

Step 4: Check Router (optional, for full node)
- Log in to router panel (usually 192.168.1.1 or 192.168.0.1)
- Find Port Forwarding section
- Add rule:
  External port: 8327
  Internal port: 8327
  Protocol: TCP
  Device IP: your local IP e.g. 192.168.1.100
- Save changes


===============================================================================
3. CREATING CONFIGURATION FILE
===============================================================================

NOTE: rxb.conf is created automatically on first run with secure settings.
You only need to edit it manually if you want to customize your node.

CONFIGURATION FILE LOCATION:
C:\Users\[YOUR_NAME]\AppData\Roaming\RXB\rxb.conf

BASIC CONFIGURATION (created automatically on first run):

# RXB Core v0.3.0 Foxbat
# https://github.com/Heiwabitnull/rxb-core
listen=1
server=1
maxconnections=15
dnsseed=0
addnode=135.181.255.219:8327
rpcbind=127.0.0.1
rpcallowip=127.0.0.1
rpcport=8328
rpcuser=rxbuser
rpcpassword=[GENERATED_AUTOMATICALLY]

Save file and restart node.


===============================================================================
4. CREATING YOUR OWN SEED NODE
===============================================================================

REQUIREMENTS:
- Port 8327 open in firewall (see section 2)
- Port 8327 forwarded in router
- Stable internet connection
- Computer running 24/7 (recommended)
- Public IP or DynamicDNS

SEED NODE CONFIGURATION:

Step 1: Find your public IP
- Go to: https://whatismyipaddress.com
- Save your IP address

Step 2: Configure rxb.conf
Add to configuration file:

listen=1
externalip=[YOUR_PUBLIC_IP]:8327
maxconnections=50

Step 3: Start Node
- Run rxbd.exe
- Node will automatically connect to network

Step 4: Check Status
- Open CMD
- Navigate to RXB installation folder
- Run: rxb-cli.exe getnetworkinfo
- Check if localaddresses contains your IP

OPTIONAL DynamicDNS:
- Register at No-IP.com or DuckDNS.org (free)
- Create domain e.g: yournode.ddns.net
- Install DynamicDNS client
- Add to rxb.conf: externalip=yournode.ddns.net:8327


===============================================================================
5. PASSWORDS AND SECURITY
===============================================================================

rpcpassword is generated automatically with a strong random key on first run.
You do not need to set it manually.

FOR WALLET PASSWORD:
- Minimum 16 characters
- Upper and lowercase letters
- Numbers
- Special characters: !@#$%^&*()_+=[]{}

Example: MyRXBWallet2026!Secure

WALLET BACKUP:
1. Close RXB node
2. Navigate to: %APPDATA%\RXB
3. Copy wallet.dat file
4. Save on external drive or USB
5. Backup monthly or after every important transaction


===============================================================================
6. SUPPORTING THE RXB
===============================================================================

RXB is decentralized and runs thanks to its users.

RUNNING A NODE:
- Every active node increases network security
- If possible keep your node running 24/7

CREATING SEED NODES:
- If you have stable connection and public IP create your own seed node
- See section 4

HOW YOU CAN HELP:
1. Run a node and keep it online
2. If you have public IP - create a seed node
3. Help other users in the community

EVERY NODE COUNTS!


===============================================================================
7. TROUBLESHOOTING
===============================================================================

Problem: Windows blocks execution
Solution:
1. Right-click on .exe file
2. Select Properties
3. In General tab check Unblock
4. Click Apply and OK
5. Run again

Problem: Antivirus blocks program
Solution:
1. Add RXB folder to antivirus exceptions
2. Temporarily disable antivirus during installation
3. Re-enable antivirus after installation

Problem: Node not synchronizing
Solution:
1. Make sure bootstrap was extracted to %APPDATA%\RXB\ before first run
2. Check internet connection
3. Check if port 8327 is open in firewall (see section 2)
4. Restart program
5. Check logs: %APPDATA%\RXB\debug.log

Problem: Forgot wallet password
Solution:
Unfortunately there is no way to recover password.
ALWAYS BACKUP YOUR WALLET!


===============================================================================
IMPORTANT FILE LOCATIONS
===============================================================================

Data folder:
C:\Users\[YOUR_NAME]\AppData\Roaming\RXB\

Important files:
- wallet.dat    - Wallet (BACKUP!)
- rxb.conf      - Configuration
- debug.log     - Logs
- peers.dat     - List of known nodes
- blocks\       - Blockchain
- chainstate\   - Chain state


===============================================================================
PROJECT INFORMATION
===============================================================================

Website: https://rxbcore.org
Source:  https://github.com/Heiwabitnull/rxb-core

Version: RXB Core v0.3.0 Foxbat
Technology: Based on Bitcoin Core 0.20
Network: Mainnet
P2P Port: 8327


===============================================================================
SYSTEM REQUIREMENTS
===============================================================================

Minimum:
- System: Windows 7 SP1 64-bit or newer
- Processor: Dual-core 2.0 GHz
- RAM: 2 GB
- Disk: 10 GB free space
- Internet: Broadband connection

Recommended:
- System: Windows 10/11 64-bit
- Processor: Quad-core 2.5 GHz or better
- RAM: 4 GB or more
- Disk: SSD with 50 GB free space
- Internet: Broadband connection


===============================================================================
LICENSE
===============================================================================

RXB Core is open source software released under MIT license.
Software is provided AS IS without any warranties.


===============================================================================

Thank you for using RXB Core v0.3.0 Foxbat!
Every node strengthens the network.

===============================================================================
