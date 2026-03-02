
### QoS Quality of Service ###

This script helps control outgoing bandwidth for the RXB network.
It limits TCP traffic that uses port 8327 which is the network port for RXB.  
Local network traffic is not affected.

The idea is simple.
  
You can keep one RXB node running all the time and still run another local RXB instance that connects to it.  
This keeps your network stable and prevents your connection from being overloaded.

The script uses standard Linux tools and can be enabled or disabled at any time.

It is optional and safe to remove if you do not need it.

