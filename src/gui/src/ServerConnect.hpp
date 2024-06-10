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

    #include "GuiException.hpp"

    class serverConnect
    {
        private:
            int fd = -1;

        public:
            std::string readFromServer();
            void sendToServer(std::string message);

            void connectToServer(int port, const char *ip);
    
            serverConnect();
            ~serverConnect();
    };

    /**
     * @brief connect to the given ip on the given port
     * @param port the port to use
     * @param ip the ip adress to connect to
     * @return void
    */
    void serverConnect::connectToServer(int port, const char *ip)
    {
        this->fd = socket(AF_INET, SOCK_STREAM, 0);
        if (this->fd < 0) {
            throw guiException("Failed to create a socket");
        }

        struct sockaddr_in server_addr;
        memset(&server_addr, 0, sizeof(server_addr));
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(port);

        if (inet_pton(AF_INET, ip, &server_addr.sin_addr) <= 0) {
            throw guiException("Invalid address");
        }
        if (connect(this->fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
            throw guiException("Failed to connect to the server");
        }
    }

    /**
     * @brief ecanpsulation of the C socket functions
    */
    serverConnect::serverConnect()
    {
    }

    serverConnect::~serverConnect()
    {
        if (this->fd >= 0)
            close(this->fd);
    }

    /**
     * @brief read the message sent by the server
     * @return the message received from the server
    */
    std::string serverConnect::readFromServer()
    {
        std::string message;
        std::vector<char> buffer(1024);
        int valread;

        while ((valread = read(this->fd, buffer.data(), buffer.size())) > 0) {
            message += std::string(buffer.data(), valread);
            if (message.back() == '\n' && valread != buffer.size())
                break;
        }

        if (valread < 0)
            throw guiException("Failed to read from the server");
        return message;
    }

    /**
     * @brief send a message to the server
     * @param message the message to send
     * @return void
    */
    void serverConnect::sendToServer(std::string message)
    {
        if (write(this->fd, message.c_str(), message.size()) < 0) {
            throw guiException("Failed to send message to the server");
        }
        std::cout << "Sent: " << message << std::endl;
    }

#endif //SERVERCONNECT_HPP
