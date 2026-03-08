#include <iostream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>
#include <utility>

using namespace std;

class ChatClient {
public:
    ChatClient(string ipAddress, const int port)
        : clientSocket(0), ipAddress_(std::move(ipAddress)), port_(port), serverAddress() {
    }

    void connectToServer() {
        // Create socket
        clientSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (clientSocket < 0) {
            cerr << "Failed to create socket" << endl;
            exit(1);
        }

        // reuse
        constexpr int reuse = 1;
        const int result = setsockopt(clientSocket, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
        if ( result < 0 ) {
            perror("ERROR SO_REUSEADDR:");
        }

        // Set server address
        serverAddress.sin_family = AF_INET;
        inet_pton(AF_INET, ipAddress_.c_str(), &serverAddress.sin_addr);
        serverAddress.sin_port = htons(port_);

        // Connect to server
        if (connect(clientSocket, reinterpret_cast<sockaddr *>(&serverAddress), sizeof(serverAddress)) < 0) {
            cerr << "Connection failed" << endl;
            exit(1);
        }
        cout << "Connected to server" << endl;

        // Start receiving messages
        thread receiveThread([this]() {
            char buffer[1024];
            while (true) {
                const int bytesReceived = recv(clientSocket, buffer, 1024, 0);
                if (bytesReceived <= 0) {
                    cout << "Connection closed" << endl;
                    break;
                }
                string message(buffer, bytesReceived);
                cout << message << endl;
            }
        });

        // Send messages to server
        string message;
        while (true) {
            cout << "You: ";
            getline(cin, message);
            send(clientSocket, message.c_str(), message.size(), 0);
            if (message == "quit") {
                break;
            }
        }
        close(clientSocket);
        receiveThread.join();
    }

private:
    int clientSocket;
    string ipAddress_;
    int port_;
    sockaddr_in serverAddress;
};

int main() {
    ChatClient client("127.0.0.1", 9090);
    client.connectToServer();
    return 0;
}