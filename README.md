# Computer Networks - CA 1

- [Computer Networks - CA 1](#Computer-Networks---CA-1)
    - [Introduction](#Introduction)
    - [Problem Statement](#Problem-Statement)
        - [Server](#Server)
        - [Client](#Client)
            - [Admin](#Admin)
            - [User](#User)



## Introduction
In this Computer Assignment, we learn about socket programming in C/C++.<br>

## Problem Statement
The problem statement is to create a server and client program that can communicate with each other. The server will be a hotel reservation system and the client will be a person who wants to reserve a room.

### Server
The server is a hotel reservation system that maintains a list of rooms and user information, all of which are stored in JSON files. It is designed to handle multiple client requests simultaneously and provide their responses. The hostname and port number are read from a config.json file and the server will bind to these values accordingly.

Moreover, the server is capable of handling diverse types of requests and responding with relevant data. To ensure the reliability and stability of the system, robust error handling mechanisms will be implemented.

### Client
We have two types of clients, the admin and the user. They have some common functionalities, such as login and logout, but they also have some unique functionalities, such as admin can view all user information and user can reserve a room.