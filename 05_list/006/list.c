#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _VOICE_HISTORY_NODE_
{
	char * voice_url;
	struct _VOICE_HISTORY_NODE_ * prev;
	struct _VOICE_HISTORY_NODE_ * next;
}VOICE_HISTORY_NODE;

void create_list_head(VOICE_HISTORY_NODE ** head);
void destory_list(VOICE_HISTORY_NODE ** head);
void print_list(VOICE_HISTORY_NODE * head);
int init_voice_history_list(VOICE_HISTORY_NODE * head, int node_count);
void voice_history_play_prev(VOICE_HISTORY_NODE ** head);
void voice_history_play_next(VOICE_HISTORY_NODE ** head);
void voice_history_play_new_voice(VOICE_HISTORY_NODE ** list_new_voice_p, VOICE_HISTORY_NODE ** list_ctrl_p, char * url);
void voice_history_read_from_file(VOICE_HISTORY_NODE * head, char *path);
void voice_history_write_to_file(VOICE_HISTORY_NODE * list_new_voice_p, char *path);

int main(void)
{
	int input = 0;
	int i = 0;
	char url[1024] = {0};
	VOICE_HISTORY_NODE * head = NULL;
	VOICE_HISTORY_NODE * list_ctrl_p = NULL;
	VOICE_HISTORY_NODE * list_new_voice_p = NULL;

	create_list_head(&head);
	init_voice_history_list(head, 4);

	
	voice_history_read_from_file(head, "./voice_history.txt");
	print_list(head);
	list_ctrl_p = head;
	list_new_voice_p = head;
	
	while(1)
	{
		fflush(stdin);
		input = getchar();
		printf("input:%c\n", input);
		switch(input)
		{
			case '1':
				voice_history_play_prev(&list_ctrl_p);
				break;

			case '2':
				voice_history_play_next(&list_ctrl_p);
				break;
			case 'n':
				i ++;
				sprintf(url, "new:%d", i);
				printf("url: %s\n", url);
				voice_history_play_new_voice(&list_new_voice_p, &list_ctrl_p, url);
				
				break;

			case 'q':
				break;
		}
		if('q' == input)
		{
			break;
		}
		fflush(stdout);
		fflush(stdin);
	}

	voice_history_write_to_file(list_new_voice_p, "./voice_history.txt");
	destory_list(&head);
	return 0;
}

void create_list_head(VOICE_HISTORY_NODE ** head)
{
	*head = (VOICE_HISTORY_NODE *)malloc(sizeof(VOICE_HISTORY_NODE));
	if(!(*head))
	{
		printf("create newnode error!\n");
	}
	(*head)->next = *head;	
	(*head)->prev = *head;
}

void clear_list(VOICE_HISTORY_NODE * head)
{
	VOICE_HISTORY_NODE * p = head->next;  

	while (p != head)
	{
		p = p->next;
		if(p->prev->voice_url != NULL)
		{
			printf("free node: p->prev->voice_url: %s\n", p->prev->voice_url);
			free(p->prev->voice_url);
		}
		free(p->prev);
	}
	head->next = head;
	head->prev = head;
}

void destory_list(VOICE_HISTORY_NODE ** head)
{
	clear_list(*head);
	if((*head)->voice_url)
	{
		printf("free head: head->voice_url: %s\n", (*head)->voice_url);
		free((*head)->voice_url);
	}
	free(*head);
	*head = NULL;	
}

void print_list(VOICE_HISTORY_NODE * head)
{
	VOICE_HISTORY_NODE * p = head;  

	do
	{
		if(p->voice_url != NULL)
		{
			printf("voice_url:%s\n", p->voice_url);
		}
		p = p->next;
	}
	while (p != head);
}

int init_voice_history_list(VOICE_HISTORY_NODE * head, int node_count)
{
	VOICE_HISTORY_NODE * p = head;		
	VOICE_HISTORY_NODE * newnode = NULL;
	int i = 0; 
	
	for(i = 0; i < node_count; i ++)
	{
		newnode = (VOICE_HISTORY_NODE *)malloc(sizeof(VOICE_HISTORY_NODE));	
		newnode->voice_url = NULL;

		newnode->next = p->next;
		newnode->prev = p;
		p->next = newnode;
		head->prev = newnode;
		p = newnode;
	}	
	
	return 0;
}

void voice_history_play_prev(VOICE_HISTORY_NODE ** list_ctrl_p)
{
	VOICE_HISTORY_NODE * tmp = NULL;

	tmp = (*list_ctrl_p);
	do
	{
		if(tmp->voice_url != NULL)
		{
			printf("prev OK:%s\n", tmp->voice_url);
			tmp = tmp->prev;
			break;
		}
		tmp = tmp->prev;
	}	
	while(tmp != (*list_ctrl_p));
	*list_ctrl_p = tmp;
}

void voice_history_play_next(VOICE_HISTORY_NODE ** list_ctrl_p)
{
	VOICE_HISTORY_NODE * tmp = NULL;

	tmp = (*list_ctrl_p)->next;
	do
	{
		if(tmp->voice_url != NULL)
		{
			printf("next OK:%s\n", tmp->voice_url);
			break;
		}
		tmp = tmp->next;
	}	
	while(tmp != (*list_ctrl_p)->next);
	*list_ctrl_p = tmp;
}

void voice_history_play_new_voice(VOICE_HISTORY_NODE ** list_new_voice_p, VOICE_HISTORY_NODE ** list_ctrl_p, char * url)
{
	VOICE_HISTORY_NODE * tmp = NULL;
	tmp = (*list_new_voice_p)->next;
	if(tmp->voice_url != NULL)
	{
		free(tmp->voice_url);
	}
	tmp->voice_url = (char *)malloc(strlen(url));
	strcpy(tmp->voice_url, url);
	
	*list_new_voice_p = tmp;
	*list_ctrl_p = *list_new_voice_p;
	//*list_ctrl_p = (*list_new_voice_p)->next;
}

void voice_history_read_from_file(VOICE_HISTORY_NODE * head, char *path)
{
	FILE *fp = NULL;
	char buf[1024] = {0};
	VOICE_HISTORY_NODE * tmp = head;

	fp = fopen(path, "r");
	if(NULL == fp)
	{
		return;
	}
	while(0 < fscanf(fp, "%s\n", buf))
	{
		if(tmp->voice_url)
		{
			free(tmp->voice_url);
		}
		tmp->voice_url = (char *)malloc(strlen(buf));
		strcpy(tmp->voice_url, buf);
		memset(buf, 0, 1024);
		tmp = tmp->next;
	}

	fclose(fp);
}

void voice_history_write_to_file(VOICE_HISTORY_NODE * list_new_voice_p, char *path)
{
	FILE *fp = NULL;
	VOICE_HISTORY_NODE * p = NULL;  

	fp = fopen(path, "w");
	if(NULL == fp)
	{
		return;
	}
	
	p = list_new_voice_p;
	do
	{
		if(p->voice_url != NULL)
		{
			fprintf(fp, "%s\n", p->voice_url);
		}
		p = p->next;
	}
	while (p != list_new_voice_p);

	fclose(fp);
}
