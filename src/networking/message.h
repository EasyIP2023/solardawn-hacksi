/* https://github.com/bschmaltz/c-p2p-chat */

#include <time.h>

typedef struct message_header_t {
	char type;
	char error;
	unsigned int room;
	unsigned int payload_length;
	double watts;
	double watt_hours;
	time_t start_time;
	time_t end_time;
} message_header;

typedef struct packet_t {
	struct message_header_t header;
	char payload[1000];
} packet;
