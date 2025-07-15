#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_TIME_SLOTS 50
#define FULL 0
#define MSB_8 1
#define SUCCESS 1
#define FAILED 0

typedef struct prefix{
	char format[30];
    unsigned ip[2]; // The full 32-bit IP addresses
    unsigned char len; // The prefix length (length of subnet mask)
    struct prefix* next; // singly linked-list pointer
} Prefix;
typedef struct record{
	unsigned long long cycle;
	int count;
	struct record *next;
} Record;
//short time_table[10000000] = {};

static inline unsigned long long int rdtsc_64bits()//64-bit
{
   unsigned long long int x;
   unsigned a, d;

   __asm__ volatile("rdtsc" : "=a" (a), "=d" (d));

   return ((unsigned long long)a) | (((unsigned long long)d) << 32);;
}
Record *genRecord(Record *prev, unsigned long long cycle)
{
	Record *record = malloc(sizeof(Record));
	record->cycle = cycle; record->next = NULL;
	if (prev != NULL) prev->next = record;
	return record;
}
void insert_record(Record *record, Record *dummy)
{
	if (record == NULL) return;
	//printf("Debug - Incoming cycle value: %llu\n", record->cycle);
	Record *p = dummy;
	for (; p->next != NULL; p = p->next){
		if (p->next->cycle > record->cycle) break;
		if (p->next->cycle == record->cycle){
			(p->next->count)++; free(record); return;
		}
	}
	if (p->next != NULL) record->next = p->next;
	p->next = record; record->count = 1;
	//printf("%llu ", record->cycle);
}
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
	char format[30]; fscanf(fp, "%s", format);
	unsigned a, b, c, d; unsigned char k;
	sscanf(format, "%u.%u.%u.%u/%hhu\n", &a, &b, &c, &d, &k);
	unsigned num = (a<<24)|(b<<16)|(c<<8)|d;
	Prefix *head = genNode(NULL, num, a, k), *prev = head;
	strcpy(head->format, format);
	//print_bit(num);
	//printf(" is %u.%u.%u.%u/%hhu\n", a, b, c, d, k);
	while (fscanf(fp, "%s", format) != EOF){
		sscanf(format, "%u.%u.%u.%u/%hhu", &a, &b, &c, &d, &k);
		num = (a<<24)|(b<<16)|(c<<8)|d;
		Prefix *node = genNode(prev, num, a, k);
		prev = node; strcpy(node->format, format);
		//print_bit(num);
		//printf(" is %u.%u.%u.%u/%hhu\n", a, b, c, d, k);
	}
	fclose(fp);
	unsigned long long count = 0;
	for (Prefix *p = head; p != NULL; p = p->next) count++;
	printf("The total number of prefixes in the `routing_table.txt` is : %llu\n", count);
	return head;
}
void insert(Prefix *node, Prefix **head)
{
	if (node == NULL) return;
	Prefix **x = head;
	while ((*x) != NULL && ((*x)->ip)[FULL] < (node->ip)[FULL])
		x = &((*x)->next);
	node->next = (*x);
	(*x) = node;
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
Prefix **group_len(Prefix **head)
{
	Prefix **g = calloc(33, sizeof(Prefix*));
	while (*head != NULL){
		Prefix *tmp = *head; *head = (*head)->next;
		tmp->next == NULL; insert(tmp, g+tmp->len);
	}
	return g;
}
Prefix ***segment(Prefix **head)
{
	Prefix ***G = calloc(33, sizeof(Prefix**)), **g = group_len(head);
	for (int i = 0; i < 33; i++){
		if (g[i] != NULL){
			G[i] = calloc(256, sizeof(Prefix*));
			while (g[i] != NULL){
				Prefix *tmp = g[i]; g[i] = g[i]->next;
				tmp->next == NULL; insert(tmp, &G[i][(tmp->ip)[MSB_8]]);
			}
		}
	}
	return G;
}
void prefix_insert(char filepath[], Prefix ***G, Record *dummy_t)
{
	FILE *fp; fp = fopen(filepath, "r");
	char format[30];
	unsigned a, b, c, d; unsigned char k;
	unsigned begin, end;
	while (fscanf(fp, "%s", format) != EOF){
		sscanf(format, "%u.%u.%u.%u/%hhu", &a, &b, &c, &d, &k);
		Prefix *p = genNode(NULL, (a<<24)|(b<<16)|(c<<8)|d, a, k);
		strcpy(p->format, format);
		begin = rdtsc_64bits();
		insert(p, &G[p->len][(p->ip)[MSB_8]]);
		end = rdtsc_64bits();
		unsigned long long cycle = (end-begin)/MAX_TIME_SLOTS;
		Record *record = genRecord(NULL, cycle);
		insert_record(record, dummy_t);
	}
	fclose(fp);
}
void prefix_delete(char filepath[], Prefix ***G, Record *dummy_t)
{
	FILE *fp; fp = fopen(filepath, "r");
	unsigned a, b, c, d; unsigned char k;
	unsigned begin, end;
	while (fscanf(fp, "%u.%u.%u.%u/%hhu", &a, &b, &c, &d, &k) != EOF){
		begin = rdtsc_64bits();
		delete((a<<24)|(b<<16)|(c<<8)|d, &G[k][a]);
		end = rdtsc_64bits();
		unsigned long long cycle = (end-begin)/MAX_TIME_SLOTS;
		Record *record = genRecord(NULL, cycle);
		insert_record(record, dummy_t);
	}
	fclose(fp);
}
short match(unsigned aim, unsigned reference, unsigned char len)
{
	unsigned i = (1<<31); short check = SUCCESS;
	for (int _ = 0; _ < len; _++, i >>= 1){
		if ((aim & i) != (reference & i)){
			check = FAILED; break;
		}
	}
	return check;
}
void search(unsigned a, unsigned b, unsigned c, unsigned d, Prefix ***G)
{
	short check = 0;
	for (int i = 0; i < 33; i++){
		if (G[i] != NULL){
			for (Prefix *p = G[i][a]; p != NULL; p = p->next){
				if (match((a<<24)|(b<<16)|(c<<8)|d, p->ip[0], p->len)){
					//printf("%u.%u.%u.%u matched successfully\n", a, b, c, d);
					check = 1; break;
				}
			}
			if (check) break;
		}
	}
	//if (!check) printf("%u.%u.%u.%u failed to match\n", a, b, c, d);
}
void prefix_search(char filepath[], Prefix ***G, Record *dummy_t)
{
	FILE *fp; fp = fopen(filepath, "r");
	unsigned a, b, c, d; unsigned long long begin, end;
	while (fscanf(fp, "%u.%u.%u.%u", &a, &b, &c, &d) != EOF){
		begin = rdtsc_64bits();
		search(a, b, c, d, G);
		end = rdtsc_64bits();
		unsigned long long cycle = (end-begin)/MAX_TIME_SLOTS;
		Record *record = genRecord(NULL, cycle);
		insert_record(record, dummy_t);
	}
	fclose(fp);
}
int main()
{
	char routing_table_filepath[] = "C:\\C\\NCKU\\HW10\\hw10-2024-12-26\\routing_table.txt";
	char inserted_prefixes_filepath[] = "C:\\C\\NCKU\\HW10\\hw10-2024-12-26\\inserted_prefixes.txt";
	char deleted_prefixes_filepath[] = "C:\\C\\NCKU\\HW10\\hw10-2024-12-26\\deleted_prefixes.txt";
	char trace_file[] = "C:\\C\\NCKU\\HW10\\hw10-2024-12-26\\trace_file.txt";
	Prefix *head = input(routing_table_filepath);
	Prefix ***G = segment(&head);

	Record *dummy_of_time_table = genRecord(NULL, -1);
	prefix_search(trace_file, G, dummy_of_time_table);
	//int cnt = 0;
	puts("cycle: ");
	for (Record *p = dummy_of_time_table->next; p != NULL; p = p->next){
		printf("%llu\n", p->cycle);
		//cnt++;
	}
	puts("count: ");
	for (Record *p = dummy_of_time_table->next; p != NULL; p = p->next)
		printf("%d\n", p->count);
	//printf("%d\n", cnt);
	return 0;
}