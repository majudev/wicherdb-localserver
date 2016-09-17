#include "ConnectionManager.h"

Wicher::DB::ConnectionManager::ConnectionManager(int port){
#ifdef WIN
    Log::info("Initializing Winsock2...");
    WSADATA wsadata;
    int error = WSAStartup(0x0202, &wsadata);
    if(error){
        Log::info("Error when initializing Winsock2. Will now halt.\n");
        perror("Error");
        exit(1);
    }

    if(wsadata.wVersion != 0x0202){
        Log::info("Error. Cannot get 0x0202 version of Winsock. Will now halt.\n");
        WSACleanup();
        exit(1);
    }
#endif
	Log::info("Creating socket for server");
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock < 0){
		perror("Error when creating socket");
		exit(1);
	}else Log::info("OK");
	struct sockaddr_in server_addr;
	bzero((char *) &server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	//server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(port);
	Log::info(std::string("Binding to 127.0.0.1:") + Toolkit::itostr(port));
	if(bind(sock, (struct sockaddr*) &server_addr, sizeof(server_addr)) < 0){
		perror("Error when binding to port");
		exit(1);
	}else Log::info("OK");
	Log::info("Listening on socket with interval 5...");
	if(listen(sock, 5) < 0){
		perror("Error when listening");
		exit(1);
	}else Log::info("OK");
}

Wicher::DB::ConnectionManager::~ConnectionManager(){
    Log::server("Closing connection...");
#ifdef WIN
    closesocket(clientsock);
    closesocket(sock);
    Log::server("Cleanning up Winsock2...");
    WSACleanup();
#elif defined(UNI)
    close(clientsock);
	close(sock);
#endif
	Log::server("Done.");
}

bool Wicher::DB::ConnectionManager::get_connection(){
    Log::info("Waiting for connection...");
    struct sockaddr_in client_addr;
#ifdef WIN
    int client_addr_len = sizeof(client_addr);
#elif defined(UNI)
    socklen_t client_addr_len = sizeof(client_addr);
#endif
	clientsock = accept(sock, (struct sockaddr*) &client_addr, &client_addr_len);
	if(clientsock < 0){
		perror("Error when accepting connection");
		return false;
	}else{
		Log::server("Got connection");
		return true;
	}
}

std::string Wicher::DB::ConnectionManager::recv_msg(){
    char buffer[256];
#ifdef WIN
    int r = recv(clientsock, buffer, 255, 0);
#elif defined(UNI)
    int r = read(clientsock, buffer, 255);
#endif
    if(r < 0){
        perror("Error when receiving message");
        std::string tr;
        return tr;
    }
    if(buffer[r-1] != '\0'){
        buffer[r] = '\0';
        Log::server("Got non null-terminated string!");
    }
    std::string tr(buffer);
    return tr;
}

bool Wicher::DB::ConnectionManager::send_msg(std::string msg){
#ifdef WIN
    int res = send(clientsock, msg.c_str(), msg.size() + 1, 0);
#elif defined(UNI)
    int res = write(clientsock, msg.c_str(), msg.size() + 1);
#endif
    if(res != msg.size() + 1){
        perror("Error when writing to socket!");
        return false;
    }
    return true;
}

bool Wicher::DB::ConnectionManager::is_up(){
#ifdef WIN
    char buffer[256];
    int buffersize = 256;
    if(getsockopt(sock, SOL_SOCKET, SO_ERROR, buffer, &buffersize)){
        Log::server(std::string("Socket error."));
        return false;
    }
    if(getsockopt(sock, SOL_SOCKET, SO_ERROR, buffer, &buffersize)){
        Log::client(std::string("Socket error."));
        return false;
    }
    return true;
#elif defined(UNI)
    int error = 0;
    socklen_t len = sizeof (error);
    getsockopt (sock, SOL_SOCKET, SO_ERROR, &error, &len);
    if(error != 0){
        Log::server(std::string("Socket error: ") + std::string(strerror(error)));
        return false;
    }
    getsockopt (clientsock, SOL_SOCKET, SO_ERROR, &error, &len);
    if(error != 0){
        Log::client(std::string("Socket error: ") + std::string(strerror(error)));
        return false;
    }
    return true;
#endif
}
