#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>
#include <netdb.h>
#include "peer.h"


void receive_packet      ();
void create_room_request ();
void find_open_rooms     ();
void *read_input (void *ptr);
void display_err (char *error);

int sock;
struct sockaddr_in watcher_addr;
struct sockaddr_in sock_addr;
struct sockaddr_in peer_list[100];
unsigned int room_num = 0;
int peer_num = 0;

pthread_mutex_t stdout_lock;
pthread_mutex_t peer_list_lock;

int main(int argc, char **argv) {
	run(argv[1]);
	return 0;
}

int run (char *watcher_ip) {

	if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
		display_err("creating socket.");

	if (bind(sock, (struct sockaddr *)&sock_addr, sizeof(sock_addr)) == -1)
		display_err("binding");

	short watcher_port = WATCHER_PORT;
	short sock_port = (short) random();

	sock_addr.sin_family = AF_INET;
	sock_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	sock_addr.sin_port = htons(sock_port);

	watcher_addr.sin_family = AF_INET;
	if (inet_aton(watcher_ip, &watcher_addr.sin_addr) == 0)
		display_err("parsing watcher ip.");

	watcher_addr.sin_port = htons(watcher_port);
	create_room_request ();
	find_open_rooms ();

	/* create a thread to read user input */
	pthread_t input_thread;
	pthread_create(&input_thread, NULL, read_input, NULL);
	pthread_detach(input_thread);

	receive_packet();
	return 0;
}

void *read_input(void *ptr) {

	while (1) {}

  return NULL;
}

void receive_packet () {

	struct sockaddr_in sender_addr;
	socklen_t addrlen = 10;
	packet pkt;
	int status;

	while (1) {
		if ((status = recvfrom(sock, &pkt, sizeof(pkt), 0, (struct sockaddr *)&sender_addr, &addrlen)) == -1) {
			pthread_mutex_lock(&stdout_lock);
			perror("receiving a packet, ignoring");
			pthread_mutex_unlock(&stdout_lock);
			continue;
		}
	}
}

void create_room_request () {
	int status;
	/* format packet */
	packet pkt;
	pkt.header.type = 'c';
	pkt.header.error = '\0';
	pkt.header.payload_length = 0;

	/* send packet to watcher */
	if ((status = sendto(sock, &pkt, sizeof(pkt.header), 0, (struct sockaddr *)&watcher_addr, sizeof(struct sockaddr_in))) == -1) {
		pthread_mutex_lock(&stdout_lock);
		perror("sending packet to watcher");
		pthread_mutex_unlock(&stdout_lock);
	}
}

void join_room (int new_room_num) {
	int status;
	/* format packet */
	packet pkt;
	pkt.header.type = 'j';
	pkt.header.error = '\0';
	pkt.header.room = new_room_num;
	pkt.header.payload_length = 0;

	/* send packet to watcher */
	if ((status = sendto(sock, &pkt, sizeof(pkt.header), 0, (struct sockaddr *)&watcher_addr, sizeof(struct sockaddr_in))) == -1) {
		pthread_mutex_lock(&stdout_lock);
		perror("sending packet to watcher");
		pthread_mutex_unlock(&stdout_lock);
	}
}

void leave_room () {
	int status;
	/* format packet */
	packet pkt;
	pkt.header.type = 'l';
	pkt.header.error = '\0';
	pkt.header.room = room_num;
	pkt.header.payload_length = 0;

	/* send packet to watcher */
	if ((status = sendto(sock, &pkt, sizeof(pkt.header), 0, (struct sockaddr *)&watcher_addr, sizeof(struct sockaddr_in))) == -1) {
		pthread_mutex_lock(&stdout_lock);
		perror("sending packet to watcher");
		pthread_mutex_unlock(&stdout_lock);
	}
}

void find_open_rooms () {
	int status;
	/* format packet */
	packet pkt;
	pkt.header.type = 'r';
	pkt.header.error = '\0';
	pkt.header.room = room_num;
	pkt.header.payload_length = 0;

	/* send packet to watcher */
	if ((status = sendto(sock, &pkt, sizeof(pkt.header), 0, (struct sockaddr *)&watcher_addr, sizeof(struct sockaddr_in))) == -1) {
		pthread_mutex_lock(&stdout_lock);
		perror("sending packet to watcher");
		pthread_mutex_unlock(&stdout_lock);
	}
}

/* local method that prints out a list of all peer in the chatroom */
void get_room_info () {
	pthread_mutex_lock(&stdout_lock);
	if (peer_num == 0) {
		perror("you are not in any room!");
	}
	else {
		printf("%s %d\n", "you are in chatroom number", room_num);
		printf("%s\n", "member: ");

		char *peer_ip;
		short peer_port;
		for (int i = 0; i < peer_num; i++) {
			peer_ip = inet_ntoa(peer_list[i].sin_addr);
			peer_port = htons(peer_list[i].sin_port);
			printf("%s:%d\n", peer_ip, peer_port);
		}
	}
	pthread_mutex_unlock(&stdout_lock);
}

void create_room_reply (packet *pkt) {
	// error checking
	char error;
	if ((error = pkt->header.error) != '\0') {
		pthread_mutex_lock(&stdout_lock);
		if (error == 'o')
			perror("the application is out of chatrooms!");
		else if (error == 'e')
			perror("you already exist in a chatroom!");
		else
			perror("unspecified error.");

		pthread_mutex_unlock(&stdout_lock);
		return;
	}

	pthread_mutex_lock(&peer_list_lock);
	room_num = pkt->header.room;
	peer_num = 1;
	memcpy(peer_list, &sock_addr, sizeof(struct sockaddr_in));
	pthread_mutex_unlock(&peer_list_lock);
	pthread_mutex_lock(&stdout_lock);
	printf("You've created and joined chatroom %d\n", room_num);
	pthread_mutex_unlock(&stdout_lock);
}

void join_room_reply (packet *pkt) {
	/* error checking */
	char error;
	if ((error = pkt->header.error) != '\0') {
		pthread_mutex_lock(&stdout_lock);
		if (error == 'f')
			perror("the chatroom is full!");
		else if (error == 'e')
			perror("the chatroom does not exist!");
		else if (error == 'a')
			perror("you are already in that chatroom!");
		else
			perror("unspecified error.");
		pthread_mutex_unlock(&stdout_lock);
		return;
	}

	pthread_mutex_lock(&peer_list_lock);
	room_num = pkt->header.room;

	/* store sockaddr list in payload */
	peer_num = pkt->header.payload_length / sizeof(struct sockaddr_in);
	if (peer_num <= 0) {
		pthread_mutex_lock(&stdout_lock);
		perror("peer list missing, can't join chatroom, leaving old chatroom if switching.");
		pthread_mutex_unlock(&stdout_lock);
		room_num = 0;
		peer_num = 0;
	}
	else {
		memcpy(peer_list, pkt->payload, peer_num * sizeof(struct sockaddr_in));
		pthread_mutex_lock(&stdout_lock);
		printf("you have joined chatroom %d\n", room_num);
		pthread_mutex_unlock(&stdout_lock);
	}
	pthread_mutex_unlock(&peer_list_lock);
}

void leave_room_reply (packet *pkt) {
	/* error checking */
	char error;
	if ((error = pkt->header.error) != '\0') {
		pthread_mutex_lock(&stdout_lock);
		if (error == 'e')
			perror("you are not in any chatroom!");
		else
			perror("unspecified error.");

		pthread_mutex_unlock(&stdout_lock);
		return;
	}

	pthread_mutex_lock(&peer_list_lock);
	room_num = 0;
	peer_num = 0;
	pthread_mutex_unlock(&peer_list_lock);
	pthread_mutex_lock(&stdout_lock);
	puts("you have left the chatroom");
	pthread_mutex_unlock(&stdout_lock);
}

void user_connection_updates (packet *pkt) {

	pthread_mutex_lock(&peer_list_lock);
	int new_peer_num;

	/* store sockaddr list in payload */
	if ((new_peer_num = pkt->header.payload_length / sizeof(struct sockaddr_in)) <= 0) {
		pthread_mutex_lock(&stdout_lock);
		perror("peer list missing");
		pthread_mutex_unlock(&stdout_lock);
	}
	else {
		pthread_mutex_lock(&stdout_lock);
		puts("room update recieved");
		pthread_mutex_unlock(&stdout_lock);
		peer_num = new_peer_num;
		memcpy(peer_list, pkt->payload, peer_num * sizeof(struct sockaddr_in));
	}
	pthread_mutex_unlock(&peer_list_lock);
}

/* Use this method when searching for Users who are selling */
void receive_available_producers (packet *pkt) {
	pthread_mutex_lock(&stdout_lock);
	printf("Room List: \n%s", pkt->payload);
	pthread_mutex_unlock(&stdout_lock);
}

void receive_power (struct sockaddr_in *sender_addr, packet *pkt) {
	/* fetch sender information */
	char *sender_ip = inet_ntoa(sender_addr->sin_addr);
	short sender_port = htons(sender_addr->sin_port);

	// display message in stdout if the message is from the chatroom that peer is in
	if (pkt->header.room == room_num) {
		pthread_mutex_lock(&stdout_lock);
		printf("%s:%d - %s\n", sender_ip, sender_port, pkt->payload);
		pthread_mutex_unlock(&stdout_lock);
	}
}

void reply_to_ping (struct sockaddr_in *sender_addr) {
	int status;
	/* format packet */
	packet pkt;
	pkt.header.type = 'p';
	pkt.header.error = '\0';
	pkt.header.payload_length = 0;

	/* send ping reply */
	if ((status = sendto(sock, &pkt, sizeof(pkt.header), 0, (struct sockaddr *)sender_addr, sizeof(struct sockaddr_in))) == -1) {
		pthread_mutex_lock(&stdout_lock);
		perror("error - error replying to ping message, possibility of being opt-out");
		pthread_mutex_unlock(&stdout_lock);
	}
}

void display_err (char *s) {
  perror(s);
  abort();
}
