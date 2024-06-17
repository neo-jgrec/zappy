#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <criterion/internal/assert.h>
#include <criterion/hooks.h>
#include <string>
#include <sys/socket.h>

#include "../../src/parser/ServerConnect.hpp"
#include "../../src/utils/GuiException.hpp"

Test(ServerConnect, connectFails)
{
    ServerConnect server;
    int port = 3000;
    std::string ip = "127.0.0.1";

    cr_assert_throw(server.connectToServer(port, ip.c_str()), guiException);
}

Test(ServerConnect, socketThrow)
{
    ServerConnect server;
    int port = 3000;
    std::string ip = "127.0.0.1";
    int sockfd;

    while ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) != -1);
    cr_assert_throw(server.connectToServer(port, ip.c_str()), guiException);
    close(sockfd);
}

Test(ServerConnect, inet_ptonThrow)
{
    ServerConnect server;
    int port = 3000;
    std::string ip = "127.0.0.1";

    cr_assert_throw(server.connectToServer(port, "A"), guiException);
}

// Test(ServerConnect, successful_connection) {
//     ServerConnect server;

//     cr_assert_no_throw(server.connectToServer(3000, "127.0.0.1"), guiException);
// }

// Test(ServerConnect, readFromServer) {
//     ServerConnect server;

//     cr_assert_no_throw(server.readFromServer(), guiException);
// }

// Test(ServerConnect, readFromServerThrow) {
//     ServerConnect server;

//     cr_assert_throw(server.readFromServer(), guiException);
// }

// Test(ServerConnect, sendToServer) {
//     ServerConnect server;

//     cr_assert_no_throw(server.sendToServer("Hello"), guiException);
// }

Test(ServerConnect, sendToServerThrow) {
    ServerConnect server;

    cr_assert_throw(server.sendToServer("Hello"), guiException);
}

