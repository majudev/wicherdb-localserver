#include "Database.h"

Wicher::Database::Database() : c(false){
    Toolkit::log("Creating Database() singleton...");
}

Wicher::Database & Wicher::Database::getSingleton(){
    static Database db;
    return db;
}

bool Wicher::Database::conn(std::string address, int port){
    if(this->connected()){
        return true;
    }
#ifdef WIN
    Toolkit::log("Initializing Winsock2...");
    WSADATA wsadata;
    int error = WSAStartup(0x0202, &wsadata);
    if(error){
        Toolkit::log("Error when initializing Winsock2. Will now halt.\n");
        perror("Error");
        return false;
    }

    if(wsadata.wVersion != 0x0202){
        Toolkit::log("Error. Cannot get 0x0202 version of Winsock. Will now halt.\n");
        WSACleanup();
        return false;
    }
#endif
    Toolkit::log("Creating socket...");
    this->sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0){
            perror("Error when creating socket");
            return false;
    }
    struct hostent * server = gethostbyname(address.c_str());
    if(server == NULL){
            Toolkit::log("Error: wrong hostname!");
            return false;
    }
    struct sockaddr_in server_addr;
    bzero((char *) &server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    bcopy((char *) server->h_addr, (char *) &server_addr.sin_addr.s_addr, server->h_length);
    server_addr.sin_port = htons(port);
    Toolkit::log("Connecting to " + address + ":" + Toolkit::itostr(port));
    if(connect(sock, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0){
            perror("Error when connecting");
            return false;
    }else{
            Toolkit::log("Got connection!");
            this->c = true;
            return true;
    }
}

bool Wicher::Database::connected(){ return this->c; }

std::string Wicher::Database::run(std::string msg){
    if(!connected()) return std::string("NOT_CONNECTED");
    if(!this->send(msg)){
        return std::string("SEND_FAILED");
    }
    std::string r = this->recv();
    if(r == std::string("")){
        return std::string("RECV_FAILED");
    }
    return r;
}

bool Wicher::Database::login(std::string login, std::string password){
    std::string resp = this->run(Query::login(login, password));
    json_t * root = json_loads(resp.c_str(), 0, 0);
    json_t * response = json_object_get(root, "response");
    const char * response_str = json_string_value(response);
    if(!response_str){
        Toolkit::log("Cannot read server's response. Auth failed.");
        return false;
    }
    std::string r(response_str);
    free(root);
    return r == std::string("ok");
}

static bool send_msg(std::string msg, int sock){
#ifdef WIN
	int res = send(sock, msg.c_str(), msg.size() + 1, 0);
#elif defined(UNI)
	int res = write(sock, msg.c_str(), msg.size() + 1);
#endif
	if(res < 0){
		Wicher::Toolkit::log("Failed to send message!");
	}//else std::cerr << "Sent: " << msg << std::endl;
	return !(res < 0);
}

bool Wicher::Database::send(std::string msg){
	return send_msg(msg, this->sock);
}

static std::string recv_msg(int sock){
	char buffer[10241];
	buffer[0] = '\0';
#ifdef WIN
	int res = recv(sock, buffer, 10240, 0);
#elif defined(UNI)
	int res = read(sock, buffer, 10240);
#endif
	if(!(res < 0) && buffer[res-1] != '\0'){
		Wicher::Toolkit::log("Got non null-terminated string!");
		buffer[res] = '\0';
	}else if(res < 0){
		Wicher::Toolkit::log("Failed to recv message!");
	}
	//std::cerr << "Got: " << buffer << std::endl;
	return std::string(buffer);
}

std::string Wicher::Database::recv(){
	return recv_msg(this->sock);
}

Wicher::Database::~Database(){
    send("BYE");
	Toolkit::log("Closing connection...");
#ifdef WIN
    closesocket(this->sock);
    Toolkit::log("Cleaning up Winsock2...");
    WSACleanup();
#elif defined(UNI)
    close(this->sock);
#endif
}
