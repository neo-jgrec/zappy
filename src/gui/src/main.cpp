/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** main
*/

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "serverConnect.hpp"
#include "guiException.hpp"

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
    } catch (const guiException& e) {
        std::cerr <<  e.what() << std::endl;
        return 1;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    while (1) {
        std::string data;
        try {
            data = server.readFromServer();
        } catch (const guiException& e) {
            std::cerr << e.what() << std::endl;
            return 1;
        } catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
            return 1;
        }
        if (data.compare(std::string("WELCOME\n")) == 0) {
            server.sendToServer("GRAPHIC\n");
            continue;
        }
    }
    return 0;
}
