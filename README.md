# TCP Socket in Linux Advanced C

## Introduction

This is a project to create a `TCP server` and a `TCP client` and perform a simple pre-defined message exchange between them, and here are (so far) some notes on how it was developed.

<img alt="Photo TCP Protocol" src="https://media.geeksforgeeks.org/wp-content/uploads/20220330131350/StatediagramforserverandclientmodelofSocketdrawio2-448x660.png">

## Techs

* [C](https://www.iso.org/standard/74528.html): programming language;
* [TCP]: `Transmission Control Protocol` - one of the main Internet protocols and is part of the `TCP/IP` protocol suite;
* [Linux](https://www.linux.org/): operating systems or operating systems that use the `Linux kernel`;
* [Kali Linux](https://www.kali.org/): `GNU/Linux` distribution based on Debian;

### Necessary Functions - Linux C
- `sockets-client.c`:   
    * initialize the socket --> socket();
    * fill the socket structure --> servaddr; (ip address, port, address family);
    * connect to the server --> connetc();
    * write - send data/request --> write();
    * read - receive data/response --> read();
    * close the connection/close the socket --> close();

- `sockets-server.c`:
    * initialize the socket --> socket();
    * fill the socket structure --> srv; (0 - 'we are listening on all ip addresses'; port; address family);
    * bind to a client (bind the socket structure to the server address and port) --> bind();
    * listen to a TCP port (wait for an incoming connection from the client) --> listen();
    * connection established. Creates a new connected socket and returns a new file descriptor for that socket --> accept();
    * read - receive data/request --> read();
    * write - send data/response --> write();
    * close the connection/close the socket --> close();

## Compilation and Execution

- Test the `client-server` connection:

    ```c
    - Terminal A:
        1. compile the source code
            `gcc sockets-server.c -o sockets-server`

        2. run the `sockets-server` file
            `./sockets-server`

    - Terminal B:
        1. compile the source code
            `gcc sockets-client.c -o sockets-client`
        
        2. run the `sockets-client` file
            `./sockets-client`
    ```

## Notes

- `Socket` programming in C
    * a way to `connect two nodes` in a `network` to `communicate with each other`.
    * one `socket (node)` listens on a specific `PORT` on an `IP`, while the other `socket (node)` searches/reaches for what it is listening on to form a connection.

## Tests

### Socket 1: TCP Client
1. `Initial test` - Objective: connect to a web server through a specific port
    - Test: send the HEAD command and print the server's response (in this case, the server header, which is sent as a response)

    ```c
    - Step by step:
        1. connect to a web server - (in this case, the domain below and port 80 were used):
            `nc www.google.se 80`

        2. send an http header - HEAD command (checks the headers of the referenced web server - the response will only be the header)
            `HEAD / HTTP/1.0`

        note: press `ENTER twice`
    ```

2. `Initial test` - Create a source code in `C programming language` to send a request to a web server:
    socket
        * ​​usually an `IP` connection
        * connects to a server somewhere on the Internet or on the local network and sends data
        * We will make: TCP connection on port 80 (http - used for clear text communication on the web)

    ```c
    - Step by step:
        1. get the `IP address` of the web server - (in this case the web server will be: www.google.se 'or any other')
            `host www.google.se` or
            `nslookup www.google.se` or
            `ping www.google.se`

        2. create the file: `sockets-client.c` - (in this case the `vim` editor was used)
            `vim sockets-client.c`
    ```

3. `Final implementation` - Implement the source code of the `sockets-client.c` file to communicate with the server that will be created in the source code of `sockets-server.c` file:

    ```c
    - Step by step:
        1. modify the connection `IP address`
            `0.0.0.0` or `127.0.0.1`

        2. modify the connection `port`
            `8181`

        3. customize the message that will be sent
            `Hello from server` or other
    ```

### Sockets 2: TCP Server
1. `Final implementation` - Objective: listen to a TCP port and when a connection is established, send a predefined message and finally close the program

- Create a source code in `C programming language` to be the server:

    ```c
    - Step by step:
        1. create the file: `sockets-server.c` - (in this case the `vim` editor was used)
            `vim sockets-server.c`

        2. establish the connection port
            `8181`

        3. bind the server to localhost
            `0` or `INADDR_ANY`
    ```