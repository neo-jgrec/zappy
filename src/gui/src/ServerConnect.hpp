/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** serverConnect
*/

#ifndef INCLUDED_SERVERCONNECT_HPP
    #define INCLUDED_SERVERCONNECT_HPP

    #include <string>
    #include <unistd.h>

    class serverConnect
    {
        private:
            int fd = -1;

        public:

            /**
            * @brief read the message sent by the server
            * @return the message received from the server
            */
            std::string readFromServer();

            /**
            * @brief send a message to the server
            * @param message the message to send
            * @return void
            */
            void sendToServer(std::string message);

            /**
            * @brief connect to the given ip on the given port
            * @param port the port to use
            * @param ip the ip adress to connect to
            * @return void
            */
            void connectToServer(int port, const char *ip);
    
            serverConnect() {};
            ~serverConnect() { if (this->fd >= 0) close(this->fd); };
    };

#endif //SERVERCONNECT_HPP
