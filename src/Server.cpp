#include <iostream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <thread>

using namespace std;

class ChatServer {
public:
    explicit ChatServer(const int port) : serverSocket(0), port_(port), address() {
    }

    [[noreturn]] void start() {
        // Create socket
        serverSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (serverSocket < 0) {
            perror("socket");
            exit(1);
        }

        // reuse
        constexpr int reuse = 1;
        const int result = setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
        if ( result < 0 ) {
            perror("ERROR SO_REUSEADDR:");
        }

        // Set address and port reuse
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons(port_);

        // Bind socket to port
        if (bind(serverSocket, reinterpret_cast<sockaddr *>(&address), sizeof(address)) < 0) {
            perror("bind");
            exit(1);
        }
        // Listen for connections
        if (listen(serverSocket, 3) < 0) {
            perror("listen");
            exit(1);
        }
        cout << "Server listening on port " << port_ << endl;

        while (true) {
            // Accept incoming connection
            int clientSocket = accept(serverSocket, nullptr, nullptr);
            if (clientSocket < 0) {
                cerr << "Accept failed" << endl;
                continue;
            }
            cout << "Connection accepted" << endl;

            // Handle client in a new thread
            thread([clientSocket]() {
                char buffer[1024];
                string message;
                while (true) {
                    // Receive message from client
                    int bytesReceived = recv(clientSocket, buffer, 1024, 0);
                    if (bytesReceived < 0) {
                        cerr << "Recv failed" << endl;
                        break;
                    }
                    if (bytesReceived == 0) {
                        cout << "Client disconnected" << endl;
                        break;
                    }
                    message = string(buffer, bytesReceived);
                    cout << "Message received: " << message << endl;

                    // Send response back
                    string response = "Server: " + message;
                    send(clientSocket, response.c_str(), response.size(), 0);
                }
                close(clientSocket);
            }).detach();
        }
    }

private:
    int serverSocket;
    int port_;
    sockaddr_in address;
};

int main() {
    ChatServer server(9090);
    server.start();
}
