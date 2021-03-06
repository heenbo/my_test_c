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

int main(void)
{
	int input = 0;
	int i = 0;
	char url[1024] = {0};
	VOICE_HISTORY_NODE * head = NULL;
	VOICE_HISTORY_NODE * list_ctrl_p = NULL;
	VOICE_HISTORY_NODE * list_new_voice_p = NULL;

	create_list_head(&head);

	init_voice_history_list(head, 5);
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
				sprintf(url, "new:%d\n", i);
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
//	(*head)->voice_url = (char *)malloc(strlen("00001\n"));
//	strcpy((*head)->voice_url, "00001\n");
}

void clear_list(VOICE_HISTORY_NODE * head)
{
	VOICE_HISTORY_NODE * p = head->next;  

	while (p != head)
	{
		p = p->next;
		if(p->prev->voice_url != NULL)
		{
			printf("free: p->prev->voice_url: %s\n", p->prev->voice_url);
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
		//if(i != 3)
		if(0)
		{
			newnode->voice_url = (char *)malloc(10);
			sprintf(newnode->voice_url, "aaa:%d\n", i);
		}

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
	tmp = (*list_ctrl_p)->prev;
	while(tmp != (*list_ctrl_p))
	{
		if(tmp->voice_url != NULL)
		{
			printf("prev OK:%s\n", tmp->voice_url);
			break;
		}
		tmp = tmp->prev;
	}	
	*list_ctrl_p = tmp;
}

void voice_history_play_next(VOICE_HISTORY_NODE ** list_ctrl_p)
{
	VOICE_HISTORY_NODE * tmp = NULL;
	tmp = *list_ctrl_p;
	while(tmp != (*list_ctrl_p)->prev)
	{
		if(tmp->voice_url != NULL)
		{
			printf("next OK:%s\n", tmp->voice_url);
			tmp = tmp->next;
			break;
		}
		tmp = tmp->next;
	}	
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
	*list_ctrl_p = (*list_new_voice_p)->next;
}
