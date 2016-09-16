William Hartman
wahartman@wpi.edu

9/16/16 - CS3516 - Networks - Project 1

Each piece of the project (the http_client and the http_server) have their
own project folder structure. On unzipping the submission, you should see
this file structure:
.
├── http_client
│   ├── include
│   │   ├── HTTPClient.h
│   │   └── SocketWrapper.h
│   ├── src
│   │   ├── HTTPClient.c
│   │   └── SocketWrapper.c
│   ├── http_client
│   └── Makefile
├── http_server
│   ├── include
│   │   └── ServerSocketWrapper.h
│   ├── src
│   │   ├── HTTPServer.c
│   │   └── ServerSocketWrapper.c
│   ├── TMDG_files
│   │   ├── PGheader.jpg
│   │   ├── ProjectGutenbergCC.jpg
│   │   └── show_ads.js
│   ├── http_server
│   ├── Makefile
│   └── TMDG.html
├── Readme.txt
└── RTT_results.txt


COMPILING AND RUNNING THE CLIENT
from project root:
cd into the client's directory - 'cd http_client'
run make                       - 'make'
run http_client                - './http_client -p google.com 80'

COMPILING AND RUNNING THE SERVER
from project root:
cd into the server's directory - 'cd http_server'
run make                       - 'make'
run http_client                - './http_server 55555'

Any reasonably modern compiler should be fine. This project was tested with
clang (on my own computer), gcc 6.2.1 (on my own computer), and gcc 4.1.2
(on the CCC machine).
