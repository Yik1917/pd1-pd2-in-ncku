#include <stdio.h>
#include <stdlib.h>
#define FULL 0
#define MSB_8 1
#define SUCCESS 1
#define FAILED 0

typedef struct prefix {
    unsigned ip[2]; // The full 32-bit IP addresses
    unsigned char len; // The prefix length (length of subnet mask)
    struct prefix* next; // singly linked-list pointer
} Prefix;

Prefix *genNode(Prefix *prev, unsigned data, unsigned a, unsigned char len)
{
	Prefix *node = malloc(sizeof(Prefix));
	(node->ip)[FULL] = data; (node->ip)[MSB_8] = a;
	node->len = len; node->next = NULL;
	if (prev != NULL) prev->next = node;
	return node;
}
Prefix *input(char filepath[])
{
	FILE *fp; fp = fopen(filepath, "r");
	if (fp == NULL) printf("bad\n");
	unsigned a, b, c, d; unsigned char k;
	fscanf(fp, "%u.%u.%u.%u/%hhu\n", &a, &b, &c, &d, &k);
	unsigned num = (a<<24)|(b<<16)|(c<<8)|d;
	Prefix *head = genNode(NULL, num, a, k), *prev = head;
	while (fscanf(fp, "%u.%u.%u.%u/%hhu\n", &a, &b, &c, &d, &k) != EOF){
		num = (a<<24)|(b<<16)|(c<<8)|d;
		Prefix *node = genNode(prev, num, a, k);
		prev = node;
	}
	fclose(fp);
	unsigned long long count = 0;
	for (Prefix *p = head; p != NULL; p = p->next) count++;
	printf("The total number of prefixes in the routing_table.txt is : %llu\n", count);
	return head;
}
Prefix ***group_len(Prefix **head)
{
	Prefix **G = calloc(33, sizeof(Prefix*));
	while (*head != NULL){
		Prefix *tmp = *head; *head = (*head)->next;
		tmp->next = G[tmp->len]; G[tmp->len] = tmp;
	}
	return G;
}
void length_distribution(Prefix **G)
{
	for (int i = 0; i < 33; i++){
		int cnt = 0;
		for (Prefix *p = G[i]; p != NULL; p = p->next) cnt++;
		if (cnt != 0) printf("The number of prefixes with prefix length %d = %d\n", i, cnt);
	}
}
void prefix_insert(char filepath[], Prefix **G)
{
	FILE *fp; fp = fopen(filepath, "r");
	char format[30];
	unsigned a, b, c, d; unsigned char k;
	while (fscanf(fp, "%u.%u.%u.%u/%hhu", &a, &b, &c, &d, &k) != EOF){
		Prefix *p = genNode(NULL, (a<<24)|(b<<16)|(c<<8)|d, a, k);
		p->next = G[p->len]; G[p->len] = p;
	}
	fclose(fp);
}
void delete(unsigned full_ip, Prefix **head)
{
	if (*head == NULL || head == NULL) return;
	Prefix **x = head;
	while (*x != NULL){
		if ((*x)->ip[0] == full_ip){
			Prefix *temp = *x;
			*x = (*x)->next;
			free(temp);
		}else
			x = &((*x)->next);
	}
}
void prefix_delete(char filepath[], Prefix **G)
{
	FILE *fp; fp = fopen(filepath, "r");
	unsigned a, b, c, d; unsigned char k;
	while (fscanf(fp, "%u.%u.%u.%u/%hhu", &a, &b, &c, &d, &k) != EOF)
		delete((a<<24)|(b<<16)|(c<<8)|d, G+k);
	fclose(fp);
}
int main(int argc, char *argv[])
{
	char *routing_table_filepath = argv[1];
	char *inserted_prefixes_filepath = argv[2];
	char *deleted_prefixes_filepath = argv[3];
	char *trace_file = argv[4];
	printf("The file initializing the routing table: %s\n", routing_table_filepath);
	printf("The file for extra insertion into the routing table: %s\n", inserted_prefixes_filepath);
	printf("The file to delete specific IPs from the routing table: %s\n", deleted_prefixes_filepath);
	printf("The file for IP lookups: %s\n\n", trace_file);
	Prefix *head = input(routing_table_filepath);
	Prefix **G = group_len(&head);
	prefix_insert(inserted_prefixes_filepath, G);
	prefix_delete(deleted_prefixes_filepath, G);
	length_distribution(G);

	return 0;
}