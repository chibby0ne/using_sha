# Simple c program that caluclates sha256sum using OpenSSL's Libcrypto

## Build

```
mkdir build
cd build
cmake ..
make
```

## Usage 
For use simply provide one command line argument to calculate the sha256sum,
by using both: the sha256 functions from the library, and the bash
command `sha256sum` for verification.

eg:

```
$ ./sha256_test ioajpdsoijfpojdsf
Word to hash: ioajpdsoijfpojdsf
Calculated hash: 050b2748fd858f0eefcae1216e0788caed979ac8edc6c7c4690b84d04952ac6e
Golden hash (sha256sum): 050b2748fd858f0eefcae1216e0788caed979ac8edc6c7c4690b84d04952ac6e
Hash matches!
```

## License

MIT
