# frandom
A really fast random file generator. Much faster than /dev/urandom.

## Benchmarks
* frandom performance (insecure): 1.82 GiB/s
* frandom performance (secure): 99.60 MiB/s
* /dev/zero performance: 18.48 GiB/s
* /dev/urandom performance: 17.56 MiB/s

```
❯ time ./frandom /dev/null $((1 * 1024 * 1024 * 1024)); time dd if=/dev/zero of=/dev/null bs=4M count=256
./frandom /dev/null $((1 * 1024 * 1024 * 1024))  0.59s user 0.00s system 99% cpu 0.592 total
256+0 records in
256+0 records out
1073741824 bytes (1.1 GB, 1.0 GiB) copied, 0.0580986 s, 18.5 GB/s
dd if=/dev/zero of=/dev/null bs=4M count=256  0.00s user 0.06s system 98% cpu 0.059 total
```

```
❯ time ./frandom /dev/null $((1 * 1024 * 1024 * 1024)); time dd if=/dev/urandom of=/dev/null bs=4M count=256
./frandom /dev/null $((1 * 1024 * 1024 * 1024))  10.78s user 0.01s system 99% cpu 10.879 total
256+0 records in
256+0 records out
1073741824 bytes (1.1 GB, 1.0 GiB) copied, 62.1205 s, 17.3 MB/s
dd if=/dev/urandom of=/dev/null bs=4M count=256  0.00s user 61.14s system 98% cpu 1:02.12 total
```

## Security
* This utility makes use of Intel's secure hardware accelerated RNG when available.
* When the aforementioned is not available, an insecure software RNG is used.
