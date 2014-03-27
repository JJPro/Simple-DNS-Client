#include <stdbool.h>

bool is_mx;
bool is_ns;

typedef struct {
	unsigned int h_id:16;
	unsigned int h_qr:1;
	unsigned int h_op:4;
	unsigned int h_aa:1;
	unsigned int h_tc:1;
	unsigned int h_rd:1;
	unsigned int h_ra:1;
	unsigned int h_z:3;
	unsigned int h_rcode:4;
	unsigned int h_qdcount:16;
	unsigned int h_ancount:16;
	unsigned int h_nscount:16;
	unsigned int h_arcount:16;
} header_t;

// typedef struct {
//     header_t d_header;
//     quest_t  d_quest;
//     answer_t d_answer;
//     authority_t d_authority;
//     additional_t d_additional;
// } dns_t;




char *name2dnsp(const char *name, int *length);
		/* convert string name (eg. google.com) to dns presentation (eg. 6google3com0) */
int   setup_question(const char *name, char ** questp);
		/* Return the constructed DNS question in a buffer */