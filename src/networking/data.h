typedef struct message_header_t {
	char type;
	char error;
	unsigned int room;
	unsigned int payload_length;
} message_header;

typedef struct packet_t {
	struct message_header_t header;
	char payload[1000];
} packet;

typedef struct send_t {
  double watts;
  double watt_hours;
  int start_time;
  int end_time;
} send_t;
