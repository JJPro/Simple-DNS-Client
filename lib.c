#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdio.h>
#include "lib.h"



char *
name2dnsp(const char *name, int *length)
{
	*length = strlen(name) + 2;
	char *ans = calloc(0, *length);
	char m_name[strlen(name) +1];
	strcpy(m_name, name);

	char *word;
	int p = 0;
	word = strtok(m_name, ".");
	if (word){
		*(ans+p) = (char)strlen(word);
		p++;
		strcpy(ans+p, word);
		p += strlen(word);
	}
	while ((word = strtok(NULL, ".")) != NULL){
		*(ans+p) = (char )strlen(word);
		p++;
		strcpy(ans+p, word);
		p += strlen(word);
	}
	*(ans+p) = 0;
	return ans;
}

int
setup_question(const char *name, char **questp)
{
	int len;
	int p = 0;
	char *qnamep = name2dnsp(name, &len);
	char *buf = calloc(0, len+2+2); /* len bytes for qname, 
										2 for qtype;
										2 for qclass; */
	memcpy(buf+p, qnamep, len);
	p += len;
	uint16_t qtype;
	if (is_ns)
		qtype = htons(2);
	else if (is_mx)
		qtype = htons(15);
	else 
		qtype = htons(1);
	memcpy(buf+p, &qtype, 2);
	p += 2;
	uint16_t qclass = htons(1);
	memcpy(buf+p, &qclass, 2);

	*questp = buf;
	return len + 4;
}


void
notfound()
{
	printf("NOTFOUND\n");
}

void
noresponse()
{
	printf("NORESPONSE\n");
}

void
err(const char *format, ...)
		/* output error mesage to stdout */
{
	va_list args; 
	va_start(args, format);
	char * new_format = calloc(1, strlen(format) + 6 + 1 + 1); 
										/* 6 for "ERROR<tab>" 
										   1 for \n
										   1 for null char */
	strcat(new_format, "ERROR\t");
	strcat(new_format, format);
	strcat(new_format, "\n");
	printf(new_format, args);
	va_end(args);
}