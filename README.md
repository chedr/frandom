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

## Hardware/Kernel Info

* Benchmarks were performed on a Hyper-V virtual machine with the following specs:
```
❯ uname -a
Linux seppuku 4.7.7-200.fc24.x86_64 #1 SMP Sat Oct 8 00:21:59 UTC 2016 x86_64 x86_64 x86_64 GNU/Linux

❯ cat /etc/os-release
NAME=Fedora
VERSION="24 (Workstation Edition)"
ID=fedora
VERSION_ID=24
PRETTY_NAME="Fedora 24 (Workstation Edition)"
ANSI_COLOR="0;34"
CPE_NAME="cpe:/o:fedoraproject:fedora:24"
HOME_URL="https://fedoraproject.org/"
BUG_REPORT_URL="https://bugzilla.redhat.com/"
REDHAT_BUGZILLA_PRODUCT="Fedora"
REDHAT_BUGZILLA_PRODUCT_VERSION=24
REDHAT_SUPPORT_PRODUCT="Fedora"
REDHAT_SUPPORT_PRODUCT_VERSION=24
PRIVACY_POLICY_URL=https://fedoraproject.org/wiki/Legal:PrivacyPolicy
VARIANT="Workstation Edition"
VARIANT_ID=workstation

❯ cat /proc/cpuinfo
processor	: 0
vendor_id	: GenuineIntel
cpu family	: 6
model		: 79
model name	: Intel(R) Core(TM) i7-6850K CPU @ 3.60GHz
stepping	: 1
microcode	: 0xffffffff
cpu MHz		: 3599.965
cache size	: 15360 KB
physical id	: 0
siblings	: 2
core id		: 0
cpu cores	: 2
apicid		: 0
initial apicid	: 0
fpu		: yes
fpu_exception	: yes
cpuid level	: 20
wp		: yes
flags		: fpu vme de pse tsc msr pae mce cx8 apic sep mtrr pge mca cmov pat pse36 clflush mmx fxsr sse sse2 ss ht syscall nx pdpe1gb rdtscp lm constant_tsc rep_good nopl xtopology eagerfpu pni pclmulqdq ssse3 fma cx16 sse4_1 sse4_2 movbe popcnt aes xsave avx f16c rdrand hypervisor lahf_lm abm 3dnowprefetch fsgsbase bmi1 hle avx2 smep bmi2 erms rtm rdseed adx smap xsaveopt
bugs		:
bogomips	: 7199.93
clflush size	: 64
cache_alignment	: 64
address sizes	: 44 bits physical, 48 bits virtual
power management:

processor	: 1
vendor_id	: GenuineIntel
cpu family	: 6
model		: 79
model name	: Intel(R) Core(TM) i7-6850K CPU @ 3.60GHz
stepping	: 1
microcode	: 0xffffffff
cpu MHz		: 3599.965
cache size	: 15360 KB
physical id	: 0
siblings	: 2
core id		: 1
cpu cores	: 2
apicid		: 1
initial apicid	: 1
fpu		: yes
fpu_exception	: yes
cpuid level	: 20
wp		: yes
flags		: fpu vme de pse tsc msr pae mce cx8 apic sep mtrr pge mca cmov pat pse36 clflush mmx fxsr sse sse2 ss ht syscall nx pdpe1gb rdtscp lm constant_tsc rep_good nopl xtopology eagerfpu pni pclmulqdq ssse3 fma cx16 sse4_1 sse4_2 movbe popcnt aes xsave avx f16c rdrand hypervisor lahf_lm abm 3dnowprefetch fsgsbase bmi1 hle avx2 smep bmi2 erms rtm rdseed adx smap xsaveopt
bugs		:
bogomips	: 7221.78
clflush size	: 64
cache_alignment	: 64
address sizes	: 44 bits physical, 48 bits virtual
power management:
```

## Security
* This utility makes use of Intel's secure hardware accelerated RNG when available.
* When the aforementioned is not available, an insecure software RNG is used.
