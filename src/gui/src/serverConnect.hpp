/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** serverConnect
*/

#ifndef INCLUDED_SERVERCONNECT_HPP
    #define INCLUDED_SERVERCONNECT_HPP

    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <unistd.h>
    #include <string.h>
    #include <iostream>
    #include <vector>

    class serverConnect
    {
        private:
            int fd = -1;

        public:
            std::string readFromServer();

            void connectToServer(int port, const char *ip);
    
            serverConnect();
            ~serverConnect();
    };
        
    void serverConnect::connectToServer(int port, const char *ip)
    {
        this->fd = socket(AF_INET, SOCK_STREAM, 0);
        if (this->fd < 0) {
            throw std::runtime_error("Failed to create a socket");
        }

        struct sockaddr_in server_addr;
        memset(&server_addr, 0, sizeof(server_addr));
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(port);

        if (inet_pton(AF_INET, ip, &server_addr.sin_addr) <= 0) {
            throw std::runtime_error("Invalid address");
        }
        if (connect(this->fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
            throw std::runtime_error("Failed to connect to the server");
        }
    }

    serverConnect::serverConnect()
    {
    }

    serverConnect::~serverConnect()
    {
        if (this->fd >= 0)
            close(this->fd);
    }

    std::string serverConnect::readFromServer()
    {
        std::vector<char> buffer(2048);
        ssize_t bytesRead = read(this->fd, buffer.data(), buffer.size() - 1);

        if (bytesRead < 0) {
            throw std::runtime_error("Failed to read from the server");
        }
        buffer[bytesRead] = '\0';
        return std::string(buffer.data());
    }

#endif
