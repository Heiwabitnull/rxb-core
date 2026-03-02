# Linearize for RXB
Construct a linear, best version of the RXB blockchain.

## Step 1: Download hash list

    $ ./linearize-hashes.py linearize.cfg > hashlist.txt

Required configuration file settings for linearize-hashes:
* RPC: `rpcuser`, `rpcpassword` (Required if `datadir` is not specified)
* RPC: `host`  (Default: `127.0.0.1`)
* RPC: `port`  (RXB mainnet default: `8328`)

Optional config file settings for linearize-hashes:
* Blockchain: `min_height`, `max_height` (Default max_height: `313000`)
* `rev_hash_bytes`: If true, the written block hash list will be
byte-reversed. (In other words, the hash returned by getblockhash will have its
bytes reversed.) False by default. Intended for generation of
standalone hash lists but safe to use with linearize-data.py, which will output
the same data no matter which byte format is chosen.

The `linearize-hashes` script requires a connection, local or remote, to a
JSON-RPC server. Running `rxbd` or `rxb-qt -server` will be sufficient.

---

## Step 2: Copy local block data

    $ ./linearize-data.py linearize.cfg

Required configuration file settings:
* `output_file`: The file that will contain the final blockchain.
      or
* `output`: Output directory for linearized `blocks/blkNNNNN.dat` output.

Optional config file settings for linearize-data:
* `debug_output`: Some printouts may not always be desired. If true, such output
will be printed.
* `file_timestamp`: Set each file's last-accessed and last-modified times,
respectively, to the current time and to the timestamp of the most recent block
written to the script's blockchain.
* `genesis`: The hash of the RXB genesis block (Default: `8b14580a4896b53b4b51a3e10d6fe60f9435d267f0e045973b444ca3020d0000`)
* `input`: RXB blocks/ directory containing `blkNNNNN.dat`
* `hashlist`: Text file containing list of block hashes created by
linearize-hashes.py.
* `max_out_sz`: Maximum size for files created by the `output_file` option
(Default: `1000*1000*1000 bytes`)
* `netmagic`: Network magic number for RXB (Default: `D95187AE` = `RXB_MAGIC`)
* `out_of_order_cache_sz`: If out-of-order blocks are being read, the block can
be written to a cache so that the blockchain doesn't have to be sought again.
This option specifies the cache size. (Default: `100*1000*1000 bytes`)
* `rev_hash_bytes`: If true, the block hash list written by linearize-hashes.py
will be byte-reversed when read by linearize-data.py. See the linearize-hashes
entry for more information.
* `split_timestamp`: Split blockchain files when a new month is first seen, in
addition to reaching a maximum file size (`max_out_sz`).

---

## RXB Notes

* **Mainnet only**: RXB does not support testnet or regtest.  
* **Ports**: P2P = `8327`, RPC = `8328`.  
* **Max block size**: 6 MB.  
* **OP_RETURN limit**: 300 bytes.  
* **Block time**: 10 minutes.  
* **Coinbase maturity**: 50 blocks.  
* **Initial block reward**: 100 RXB.  
* **Smallest unit**: satoshi.  
* **Genesis transaction**: First transaction in genesis deliberately uses OP_RETURN so coins are unspendable.  
* **Initial difficulty**: `0x1d00ffff`.  
* **Halving interval**: 195,000 blocks.  
* **Network magic bytes**: `RXB_MAGIC` (`D95187AE`).  
* **Prefixed addresses and keys**: Defined in `chainparams` and must not be changed.

> Make sure your `linearize.cfg` is adapted with these RXB-specific parameters.
