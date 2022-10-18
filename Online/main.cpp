#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include "reseau.h"


int main(int argc, char **argv)
{

	sf::TcpSocket socket;
	sf::Socket::Status status = socket.connect("192.168.64.239", 9999);
	if (status != sf::Socket::Done)
	{
		// erreur...
		std::cout << "Erreur lors de la connexion au serveur." << std::endl;
	}



	char data[20];
	std::size_t received;

	// socket TCP:
	if (socket.receive(data, 20, received) != sf::Socket::Done)
	{
		// erreur...
	}
	std::cout << "Received " << received << " bytes" << std::endl;
	data[received] = '\0';
	std::cout << "Message : " << data;

	socket.send("Hello server", 12);

	// socket TCP:
	if (socket.receive(data, 20, received) != sf::Socket::Done)
	{
		// erreur...
	}
	std::cout << "Received " << received << " bytes" << std::endl;
	data[received] = '\0';
	std::cout << "Message : " << data;

	socket.send("Hello player", 12);

	sf::Uint32 x = 20;
	std::string s = "hello";
	double d = 0.6;

	sf::Packet packet;
	packet << x << s << d;

}

//fin de projet