# nfc-amiibo

This is a tool for spoofing amiibo NFC tags using a PN532 NFC compatible reader/writer with [libnfc](http://nfc-tools.org/index.php/Libnfc)  
This is a very shallow clone of [pimiibo](https://github.com/garrett-davidson/pimiibo), all credits go to the original creator, I only made some edits to have it work on regular Linux.

## Hardware
1. You can probably use any `libnfc` supported NFC reader/writer(I used the always popular ACR122U)

2. `NTAG215` NFC tags  

## Software setup

1. Clone this repository with submodules:

    `git clone --recurse-submodules https://github.com/crazyquark/nfc-amiibo.git`

2. Install `libnfc-dev`:

    `sudo apt-get update && sudo apt-get install libnfc-dev`

3. Compile sources.  

    `make`

## Getting the required files
After you have followed the above setup, you just need two more files to start making your own amiibo: an amiibo dump, and the key file.

### Amiibo Dump
Amiibo dumps are not hard to get. Amiibo are 540 bytes and usually stored in a .bin (binary) file. Assuming you are simply cloning your own legitimate amiibo, you can use any dumping tool to dump it to a .bin file. Otherwise, that's probably copyright infringement or something.

### Key file
This is the file containing Nintendo's key, which they use to encrypt/decrypt data on the amiibo. It is probably also copyrighted content, but it's a 160 byte .bin file which matches the MD5 `45fd53569f5765eef9c337bd5172f937`.

## Usage

Start the program:
`./nfc-amiibo path-to-key-file path-to-amiibo-file`

Once you see `***Scan tag***`, place and hold your blank NFC tag on the reader/writer. You should then see messages scrolling past with each data page as it begins writing them. ***Do not remove your tag until the write is finished.*** When you see `Finished writing tag`, it is safe to remove your tag and enjoy your new amiibo!

## Common Problems

* Failed to initialize adapter
```
Initializing NFC adapter
ERROR: Unable to open NFC device.
``` 
  Check that something like the PN533 driver or the pcscd daemon is blocking access to your reader. If you have `libnfc-bin` installed try `nfc-list` first. These are common problems with `libnfc` on Linux so you should first check that you can use `nfc-list` or any other common tool.

* Failed to write a page
  ```
  Writing to 4: a5 b0 d1 00...Failed
  Failed to write to tag
  Write: RF Transmission Error
  ```
  This means your tag is already locked. The NTAG 21x spec declares locking bits which permanently prevent certain parts of a tag from being written to once they are set. Therefore once the locking bits are set, you cannot rewrite this tag to another amiibo. All amiibo are required to have certain locking bits sets, so you cannot change a tag once you've used it.

    If this happened anywhere other than page 4, it probably means that your device lost connection to the tag. Try again while keeping the tag closer to your device. Hopefully in the future I'll add a feature to check which of these problems occurred.
