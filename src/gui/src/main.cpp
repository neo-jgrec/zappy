/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** main
*/

#include <iostream>

#include "serverConnect.hpp"

#include "raylib-cpp.hpp"

int main() {
    int screenWidth = 800;
    int screenHeight = 450;
    raylib::Color textColor = raylib::Color::LightGray();
    raylib::Window window(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);
    while (!window.ShouldClose()) {
        BeginDrawing();
        {
            window.ClearBackground(RAYWHITE);
            textColor.DrawText("Congrats! You created your first window!", 190, 200, 20);
        }
        EndDrawing();
    }

    return 0; // FIXME: remove this and everything above

    serverConnect server;
    try {
        server.connectToServer(3000, "127.0.0.1");
    } catch (const std::exception& e) {
        std::cerr << "Failed to connect to the server\n";
        return 1;
    }
    while (1) {
        std::string data;
        try {
            data = server.readFromServer();
        } catch (const std::exception& e) {
            std::cerr << "Failed to read from the server\n";
            return 1;
        }
        std::cout << data << std::endl;
    }
    return 0;
}
