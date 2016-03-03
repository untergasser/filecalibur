How to compile RSYNC on windows (important use 32bit!):

1. Install Cygwin.

2. Install the packages: make, gcc-core, gcc-g++, binutils, diffutils and vim

3. cd to your rsync directory in Cygwin.
   cd /cygdrive/c/_progs/rsync/

4. sh ./configure

5. make

6. make test

7. copy rsync.exe (from rsync folder) and cygwin1.dll, cyggcc_s-1.dll, cygiconv-2.dll (from cygwin folder) to a new folder and zip it.