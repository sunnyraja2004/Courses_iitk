#include <iostream>
#include <string>
#include <thread>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <fstream>
#include <mutex>
#include <sstream>
#include <winsock2.h>
#include <sys/socket.h>
#include <unistd.h>

const int PORT = 12345;
const int BUFFER_SIZE = 1024;
std::unordered_map<int, std::string> clients; // socket -> username
std::unordered_map<std::string, std::string> users; // username -> password
std::unordered_map<std::string, std::unordered_set<int>> groups; // group -> sockets
std::mutex mtx;

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    std::string username;

    // Authentication
    send(client_socket, "Enter username: ", 17, 0);
    recv(client_socket, buffer, BUFFER_SIZE, 0);
    username = std::string(buffer);
    send(client_socket, "Enter password: ", 17, 0);
    recv(client_socket, buffer, BUFFER_SIZE, 0);
    std::string password = std::string(buffer);

    {
        std::lock_guard<std::mutex> lock(mtx);
        if (users.find(username) == users.end() || users[username] != password) {
            send(client_socket, "Authentication failed.\n", 23, 0);
            close(client_socket);
            return;
        }
        clients[client_socket] = username;
    }

    send(client_socket, "Welcome to the chat server!\n", 28, 0);

    while (true) {
        memset(buffer, 0, BUFFER_SIZE);
        int bytes_received = recv(client_socket, buffer, BUFFER_SIZE, 0);
        if (bytes_received <= 0) break;

        std::string message(buffer);
        std::istringstream iss(message);
        std::string command;
        iss >> command;

        if (command == "/msg") {
            std::string target_user, msg;
            iss >> target_user;
            std::getline(iss, msg);
            {
                std::lock_guard<std::mutex> lock(mtx);
                for (const auto& [sock, user] : clients) {
                    if (user == target_user) {
                        send(sock, msg.c_str(), msg.size(), 0);
                        break;
                    }
                }
            }
        } else if (command == "/broadcast") {
            std::string msg;
            std::getline(iss, msg);
            {
                std::lock_guard<std::mutex> lock(mtx);
                for (const auto& [sock, user] : clients) {
                    send(sock, msg.c_str(), msg.size(), 0);
                }
            }
        } else if (command == "/create_group") {
            std::string group_name;
            iss >> group_name;
            {
                std::lock_guard<std::mutex> lock(mtx);
                groups[group_name] = {};
                send(client_socket, "Group created.\n", 15, 0);
            }
        } else if (command == "/join_group") {
            std::string group_name;
            iss >> group_name;
            {
                std::lock_guard<std::mutex> lock(mtx);
                groups[group_name].insert(client_socket);
                send(client_socket, "Joined group.\n", 14, 0);
            }
        } else if (command == "/leave_group") {
            std::string group_name;
            iss >> group_name;
            {
                std::lock_guard<std::mutex> lock(mtx);
                groups[group_name].erase(client_socket);
                send(client_socket, "Left group.\n", 12, 0);
            }
        } else if (command == "/group_msg") {
            std::string group_name, msg;
            iss >> group_name;
            std::getline(iss, msg);
            {
                std::lock_guard<std::mutex> lock(mtx);
                for (int sock : groups[group_name]) {
                    send(sock, msg.c_str(), msg.size(), 0);
                }
            }
        }
    }

    {
        std::lock_guard<std::mutex> lock(mtx);
        clients.erase(client_socket);
        for (auto& [group, members] : groups) {
            members.erase(client_socket);
        }
    }
    close(client_socket);
}

int main() {
    // Load users
    std::ifstream file("users.txt");
    std::string line;
    while (std::getline(file, line)) {
        size_t pos = line.find(':');
        std::string username = line.substr(0, pos);
        std::string password = line.substr(pos + 1);
        users[username] = password;
    }

    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in server_addr = {AF_INET, htons(PORT), INADDR_ANY};
    bind(server_socket, (sockaddr*)&server_addr, sizeof(server_addr));
    listen(server_socket, 5);

    std::cout << "Server started on port " << PORT << std::endl;

    while (true) {
        int client_socket = accept(server_socket, nullptr, nullptr);
        std::thread(handle_client, client_socket).detach();
    }

    close(server_socket);
    return 0;
}
