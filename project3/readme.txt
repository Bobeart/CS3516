William Hartman
wahartman@wpi.edu

10/11/16 - CS3516 - Networks - Project 3

PROJECT STRUCTURE

The project structure is outlined below.
.
├── include
│   └── project3.h
├── Makefile
├── NodeConfigurationFile
├── p3
├── readme.txt
└── src
    ├── node0.c
    ├── node1.c
    ├── node2.c
    ├── node3.c
    └── project3.c

All source files are in the src/ directory. All header files are in the include/
directory. All .o files from building will be put into a build/ directory that
is created by the build script.

Each of the nodeN.c files are nearly identical. Only small changes at the top of
each function were made, indicating the proper node-specific data structures and
functions.

In node0.c, the sendUpdates() functions is defined and implemented. This function
sends packets indicating updates to the other nodes in the network. This function
does not use any of the globals defined in node0.c and used in all other nodeN.c
files for this use.





COMPILING AND RUNNING THE CLIENT

from project root:
run make          - 'make'
run project 3     - './p3 1' - the '1' can be replaced with the desired trace
                               level number

The compiler being used must support C99. The standard is specified in the
makefile, so any reasonably modern compiler should be fine. This project was
tested with clang (on my own computer), gcc 6.2.1 (on my own computer), and
gcc 4.1.2 (on the CCC machines).

Run 'make clean' to delete the executable and all build files.





EXAMPLE OUTPUT (Using default NodeConfigurationFile, trace level 1)

via
D0 |     1     2     3
----|-------------------------------
dest 1|     1  9999  9999
dest 2|  9999     3  9999
dest 3|  9999  9999     7

At time t=0.000000, node 0 sends packet to node 1 with: 0 1 3 7
At time t=0.000000, node 0 sends packet to node 2 with: 0 1 3 7
At time t=0.000000, node 0 sends packet to node 3 with: 0 1 3 7
At time t=0.000000, rtinit0() called.
via
D1 |     0     2
----|-------------------------------
dest 0|     1  9999
dest 2|  9999     1
dest 3|  9999  9999

At time t=0.000000, node 1 sends packet to node 0 with: 1 0 1 9999
At time t=0.000000, node 1 sends packet to node 2 with: 1 0 1 9999
At time t=0.000000, rtinit1() called.
via
D2 |     0     1     3
----|-------------------------------
dest 0|     3  9999  9999
dest 1|  9999     1  9999
dest 3|  9999  9999     2

At time t=0.000000, node 2 sends packet to node 0 with: 3 1 0 2
At time t=0.000000, node 2 sends packet to node 1 with: 3 1 0 2
At time t=0.000000, node 2 sends packet to node 3 with: 3 1 0 2
At time t=0.000000, rtinit2() called.
via
D3 |     0     2
----|-------------------------------
dest 0|     7  9999
dest 1|  9999  9999
dest 2|  9999     2

At time t=0.000000, node 3 sends packet to node 0 with: 7 9999 2 0
At time t=0.000000, node 3 sends packet to node 2 with: 7 9999 2 0
At time t=0.000000, rtinit3() called.
via
D2 |     0     1     3
----|-------------------------------
dest 0|     3  9999  9999
dest 1|     4     1  9999
dest 3|    10  9999     2

At time t=0.124745, node 2 sends packet to node 0 with: 3 1 0 2
At time t=0.124745, node 2 sends packet to node 1 with: 3 1 0 2
At time t=0.124745, node 2 sends packet to node 3 with: 3 1 0 2
At time t=0.124745, rtupdate2() called.
via
D3 |     0     2
----|-------------------------------
dest 0|     7  9999
dest 1|     8  9999
dest 2|    10     2

At time t=0.586824, node 3 sends packet to node 0 with: 7 8 2 0
At time t=0.586824, node 3 sends packet to node 2 with: 7 8 2 0
At time t=0.586824, rtupdate3() called.
via
D2 |     0     1     3
----|-------------------------------
dest 0|     3     2  9999
dest 1|     4     1  9999
dest 3|    10  9999     2

At time t=0.609690, node 2 sends packet to node 0 with: 2 1 0 2
At time t=0.609690, node 2 sends packet to node 1 with: 2 1 0 2
At time t=0.609690, node 2 sends packet to node 3 with: 2 1 0 2
At time t=0.609690, rtupdate2() called.
via
D0 |     1     2     3
----|-------------------------------
dest 1|     1  9999  9999
dest 2|     2     3  9999
dest 3|  9999  9999     7

At time t=0.745790, node 0 sends packet to node 1 with: 0 1 2 7
At time t=0.745790, node 0 sends packet to node 2 with: 0 1 2 7
At time t=0.745790, node 0 sends packet to node 3 with: 0 1 2 7
At time t=0.745790, rtupdate0() called.
via
D3 |     0     2
----|-------------------------------
dest 0|     7     5
dest 1|     8     3
dest 2|    10     2

At time t=0.810576, node 3 sends packet to node 0 with: 5 3 2 0
At time t=0.810576, node 3 sends packet to node 2 with: 5 3 2 0
At time t=0.810576, rtupdate3() called.
via
D2 |     0     1     3
----|-------------------------------
dest 0|     3     2     9
dest 1|     4     1  9999
dest 3|    10  9999     2

At time t=0.962070, node 2 sends packet to node 0 with: 2 1 0 2
At time t=0.962070, node 2 sends packet to node 1 with: 2 1 0 2
At time t=0.962070, node 2 sends packet to node 3 with: 2 1 0 2
At time t=0.962070, rtupdate2() called.
via
D2 |     0     1     3
----|-------------------------------
dest 0|     3     2     9
dest 1|     4     1    10
dest 3|    10  9999     2

At time t=1.019291, node 2 sends packet to node 0 with: 2 1 0 2
At time t=1.019291, node 2 sends packet to node 1 with: 2 1 0 2
At time t=1.019291, node 2 sends packet to node 3 with: 2 1 0 2
At time t=1.019291, rtupdate2() called.
via
D1 |     0     2
----|-------------------------------
dest 0|     1  9999
dest 2|     4     1
dest 3|     8  9999

At time t=1.080034, node 1 sends packet to node 0 with: 1 0 1 8
At time t=1.080034, node 1 sends packet to node 2 with: 1 0 1 8
At time t=1.080034, rtupdate1() called.
via
D2 |     0     1     3
----|-------------------------------
dest 0|     3     2     9
dest 1|     4     1    10
dest 3|    10  9999     2

At time t=1.201254, node 2 sends packet to node 0 with: 2 1 0 2
At time t=1.201254, node 2 sends packet to node 1 with: 2 1 0 2
At time t=1.201254, node 2 sends packet to node 3 with: 2 1 0 2
At time t=1.201254, rtupdate2() called.
via
D0 |     1     2     3
----|-------------------------------
dest 1|     1     4  9999
dest 2|     2     3  9999
dest 3|  9999     5     7

At time t=1.224738, node 0 sends packet to node 1 with: 0 1 2 5
At time t=1.224738, node 0 sends packet to node 2 with: 0 1 2 5
At time t=1.224738, node 0 sends packet to node 3 with: 0 1 2 5
At time t=1.224738, rtupdate0() called.
At time t=1.701228, rtupdate3() called.
via
D0 |     1     2     3
----|-------------------------------
dest 1|     1     4  9999
dest 2|     2     3     9
dest 3|  9999     5     7

At time t=1.826770, node 0 sends packet to node 1 with: 0 1 2 5
At time t=1.826770, node 0 sends packet to node 2 with: 0 1 2 5
At time t=1.826770, node 0 sends packet to node 3 with: 0 1 2 5
At time t=1.826770, rtupdate0() called.
At time t=2.275775, rtupdate0() called.
via
D3 |     0     2
----|-------------------------------
dest 0|     7     4
dest 1|     8     3
dest 2|    10     2

At time t=2.490709, node 3 sends packet to node 0 with: 4 3 2 0
At time t=2.490709, node 3 sends packet to node 2 with: 4 3 2 0
At time t=2.490709, rtupdate3() called.
via
D2 |     0     1     3
----|-------------------------------
dest 0|     3     2     7
dest 1|     4     1     5
dest 3|    10  9999     2

At time t=2.718230, node 2 sends packet to node 0 with: 2 1 0 2
At time t=2.718230, node 2 sends packet to node 1 with: 2 1 0 2
At time t=2.718230, node 2 sends packet to node 3 with: 2 1 0 2
At time t=2.718230, rtupdate2() called.
via
D3 |     0     2
----|-------------------------------
dest 0|     7     4
dest 1|     8     3
dest 2|     9     2

At time t=2.735769, node 3 sends packet to node 0 with: 4 3 2 0
At time t=2.735769, node 3 sends packet to node 2 with: 4 3 2 0
At time t=2.735769, rtupdate3() called.
via
D1 |     0     2
----|-------------------------------
dest 0|     1     4
dest 2|     4     1
dest 3|     8     3

At time t=2.768510, node 1 sends packet to node 0 with: 1 0 1 3
At time t=2.768510, node 1 sends packet to node 2 with: 1 0 1 3
At time t=2.768510, rtupdate1() called.
At time t=3.186960, rtupdate1() called.
via
D1 |     0     2
----|-------------------------------
dest 0|     1     3
dest 2|     4     1
dest 3|     8     3

At time t=3.190339, node 1 sends packet to node 0 with: 1 0 1 3
At time t=3.190339, node 1 sends packet to node 2 with: 1 0 1 3
At time t=3.190339, rtupdate1() called.
via
D0 |     1     2     3
----|-------------------------------
dest 1|     1     4    15
dest 2|     2     3     9
dest 3|  9999     5     7

At time t=3.463617, node 0 sends packet to node 1 with: 0 1 2 5
At time t=3.463617, node 0 sends packet to node 2 with: 0 1 2 5
At time t=3.463617, node 0 sends packet to node 3 with: 0 1 2 5
At time t=3.463617, rtupdate0() called.
via
D2 |     0     1     3
----|-------------------------------
dest 0|     3     2     7
dest 1|     4     1     5
dest 3|    10     9     2

At time t=3.898621, node 2 sends packet to node 0 with: 2 1 0 2
At time t=3.898621, node 2 sends packet to node 1 with: 2 1 0 2
At time t=3.898621, node 2 sends packet to node 3 with: 2 1 0 2
At time t=3.898621, rtupdate2() called.
via
D1 |     0     2
----|-------------------------------
dest 0|     1     3
dest 2|     3     1
dest 3|     8     3

At time t=4.005606, node 1 sends packet to node 0 with: 1 0 1 3
At time t=4.005606, node 1 sends packet to node 2 with: 1 0 1 3
At time t=4.005606, rtupdate1() called.
At time t=4.295501, rtupdate3() called.
At time t=4.830842, rtupdate3() called.
At time t=5.155933, rtupdate1() called.
via
D0 |     1     2     3
----|-------------------------------
dest 1|     1     4    15
dest 2|     2     3     9
dest 3|  9999     5     7

At time t=5.174571, node 0 sends packet to node 1 with: 0 1 2 5
At time t=5.174571, node 0 sends packet to node 2 with: 0 1 2 5
At time t=5.174571, node 0 sends packet to node 3 with: 0 1 2 5
At time t=5.174571, rtupdate0() called.
via
D2 |     0     1     3
----|-------------------------------
dest 0|     3     2     7
dest 1|     4     1     5
dest 3|     8     9     2

At time t=5.807990, node 2 sends packet to node 0 with: 2 1 0 2
At time t=5.807990, node 2 sends packet to node 1 with: 2 1 0 2
At time t=5.807990, node 2 sends packet to node 3 with: 2 1 0 2
At time t=5.807990, rtupdate2() called.
via
D0 |     1     2     3
----|-------------------------------
dest 1|     1     4    10
dest 2|     2     3     9
dest 3|  9999     5     7

At time t=5.885198, node 0 sends packet to node 1 with: 0 1 2 5
At time t=5.885198, node 0 sends packet to node 2 with: 0 1 2 5
At time t=5.885198, node 0 sends packet to node 3 with: 0 1 2 5
At time t=5.885198, rtupdate0() called.
At time t=6.192557, rtupdate1() called.
At time t=6.199400, rtupdate3() called.
At time t=6.733784, rtupdate2() called.
via
D3 |     0     2
----|-------------------------------
dest 0|     7     4
dest 1|     8     3
dest 2|     9     2

At time t=6.971700, node 3 sends packet to node 0 with: 4 3 2 0
At time t=6.971700, node 3 sends packet to node 2 with: 4 3 2 0
At time t=6.971700, rtupdate3() called.
via
D2 |     0     1     3
----|-------------------------------
dest 0|     3     2     6
dest 1|     4     1     5
dest 3|     8     9     2

At time t=7.232019, node 2 sends packet to node 0 with: 2 1 0 2
At time t=7.232019, node 2 sends packet to node 1 with: 2 1 0 2
At time t=7.232019, node 2 sends packet to node 3 with: 2 1 0 2
At time t=7.232019, rtupdate2() called.
At time t=7.712124, rtupdate0() called.
At time t=7.903831, rtupdate1() called.
At time t=8.132249, rtupdate0() called.
At time t=8.790092, rtupdate2() called.
At time t=8.796252, rtupdate3() called.
via
D2 |     0     1     3
----|-------------------------------
dest 0|     3     2     6
dest 1|     4     1     5
dest 3|     8     4     2

At time t=8.864112, node 2 sends packet to node 0 with: 2 1 0 2
At time t=8.864112, node 2 sends packet to node 1 with: 2 1 0 2
At time t=8.864112, node 2 sends packet to node 3 with: 2 1 0 2
At time t=8.864112, rtupdate2() called.
At time t=9.260755, rtupdate3() called.
via
D1 |     0     2
----|-------------------------------
dest 0|     1     3
dest 2|     3     1
dest 3|     6     3

At time t=9.267067, node 1 sends packet to node 0 with: 1 0 1 3
At time t=9.267067, node 1 sends packet to node 2 with: 1 0 1 3
At time t=9.267067, rtupdate1() called.
At time t=9.305321, rtupdate1() called.
At time t=9.523180, rtupdate3() called.
At time t=9.539471, rtupdate2() called.
At time t=9.540557, rtupdate2() called.
via
D0 |     1     2     3
----|-------------------------------
dest 1|     1     4    10
dest 2|     2     3     9
dest 3|     9     5     7

At time t=9.609680, node 0 sends packet to node 1 with: 0 1 2 5
At time t=9.609680, node 0 sends packet to node 2 with: 0 1 2 5
At time t=9.609680, node 0 sends packet to node 3 with: 0 1 2 5
At time t=9.609680, rtupdate0() called.
At time t=9.756216, rtupdate3() called.
At time t=10.370619, rtupdate1() called.
At time t=10.428965, rtupdate0() called.
At time t=10.595822, rtupdate3() called.
At time t=11.131254, rtupdate1() called.
At time t=11.415976, rtupdate2() called.
via
D0 |     1     2     3
----|-------------------------------
dest 1|     1     4    10
dest 2|     2     3     9
dest 3|     9     5     7

At time t=11.669786, node 0 sends packet to node 1 with: 0 1 2 5
At time t=11.669786, node 0 sends packet to node 2 with: 0 1 2 5
At time t=11.669786, node 0 sends packet to node 3 with: 0 1 2 5
At time t=11.669786, rtupdate0() called.
At time t=11.690392, rtupdate3() called.
At time t=12.859119, rtupdate1() called.
At time t=12.931823, rtupdate2() called.
At time t=13.024735, rtupdate1() called.
At time t=13.153989, rtupdate2() called.
At time t=13.180450, rtupdate1() called.
At time t=13.341965, rtupdate2() called.
At time t=13.511702, rtupdate0() called.
At time t=13.605406, rtupdate1() called.
At time t=13.635763, rtupdate3() called.
At time t=13.780288, rtupdate2() called.
At time t=14.088828, rtupdate1() called.
At time t=14.396902, rtupdate0() called.
At time t=14.500940, rtupdate1() called.
At time t=14.521216, rtupdate3() called.
At time t=14.890537, rtupdate3() called.
via
D0 |     1     2     3
----|-------------------------------
dest 1|     1     4    10
dest 2|     2     3     9
dest 3|     4     5     7

At time t=14.918118, node 0 sends packet to node 1 with: 0 1 2 4
At time t=14.918118, node 0 sends packet to node 2 with: 0 1 2 4
At time t=14.918118, node 0 sends packet to node 3 with: 0 1 2 4
At time t=14.918118, rtupdate0() called.
At time t=14.982059, rtupdate0() called.
At time t=15.070696, rtupdate2() called.
At time t=15.403141, rtupdate1() called.
At time t=15.570726, rtupdate0() called.
At time t=16.215332, rtupdate0() called.
At time t=16.270386, rtupdate1() called.
At time t=16.785276, rtupdate3() called.
At time t=16.860922, rtupdate2() called.
At time t=17.106541, rtupdate3() called.
via
D2 |     0     1     3
----|-------------------------------
dest 0|     3     2     6
dest 1|     4     1     5
dest 3|     7     4     2

At time t=17.274082, node 2 sends packet to node 0 with: 2 1 0 2
At time t=17.274082, node 2 sends packet to node 1 with: 2 1 0 2
At time t=17.274082, node 2 sends packet to node 3 with: 2 1 0 2
At time t=17.274082, rtupdate2() called.
At time t=17.483980, rtupdate0() called.
via
D1 |     0     2
----|-------------------------------
dest 0|     1     3
dest 2|     3     1
dest 3|     5     3

At time t=17.761694, node 1 sends packet to node 0 with: 1 0 1 3
At time t=17.761694, node 1 sends packet to node 2 with: 1 0 1 3
At time t=17.761694, rtupdate1() called.
At time t=17.966894, rtupdate2() called.
via
D3 |     0     2
----|-------------------------------
dest 0|     7     4
dest 1|     8     3
dest 2|     9     2

At time t=19.081123, node 3 sends packet to node 0 with: 4 3 2 0
At time t=19.081123, node 3 sends packet to node 2 with: 4 3 2 0
At time t=19.081123, rtupdate3() called.
At time t=19.260189, rtupdate1() called.
At time t=19.340717, rtupdate0() called.
At time t=19.474649, rtupdate2() called.
At time t=20.282084, rtupdate3() called.
At time t=20.657936, rtupdate0() called.
At time t=22.470062, rtupdate0() called.
At time t=23.647812, rtupdate0() called.
At time t=24.449234, rtupdate0() called.
At time t=24.984856, rtupdate0() called.
At time t=25.775383, rtupdate0() called.

Simulator terminated at t=25.775383, no packets in medium
