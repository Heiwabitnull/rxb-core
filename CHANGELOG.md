# RXB Core Changelog

## v0.2.0 — April 2026

### Consensus

The difficulty adjustment algorithm has been revised to improve network
stability under adverse conditions. The solvetime window has been widened
to allow the algorithm to respond correctly when the chain experiences
prolonged periods without blocks. 
The clamp on difficulty movement is now asymmetric: 
difficulty may rise by no more than five percent per block,
whilst it may fall by up to thirty-three percent per block. 
This should makes any attempt to manipulate the network through sustained external hashrate
considerably less rewarding. 
Overflow protections have been added to the target arithmetic as a matter of good practice.

### Security

The network withstood a hashrate attack and remained operational. 
The changes above directly address the conditions that made such an attack
possible and substantially raise the cost of any future attempt.

### Upgrade Notice

This release contains consensus-critical changes. All node operators are
kindly requested to upgrade to v0.2.0 at their earliest convenience.
Nodes running v0.1.0 will not be compatible with the updated network
rules. The latest source code is available at
https://github.com/Heiwabitnull/rxb-core


## v0.1.0 — February 2026

Initial release of RXB Core.
