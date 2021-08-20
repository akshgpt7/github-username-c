#include <stdio.h>
#include <string.h>
#include "requests.h"
#include "jsmn.h"

struct user_data {
	char name[100];
	char location[50];
	char bio[300];
	int public_repos;
	int followers;
	int following;
	char created_at[30];
	char updated_at[30];
};

struct node {
    // node of the linked list to store the users
    struct user_data data;
    struct node *next;
};

struct node *head = NULL;

void insert(struct user_data u) {
		struct node *r, *temp;
		r = calloc(1, sizeof(struct node));

		strcpy(r->data.name, u.name);
		strcpy(r->data.location, u.location);
    strcpy(r->data.bio, u.bio);
		r->data.public_repos = u.public_repos;
		r->data.followers = u.followers;
		r->data.following = u.following;
		strcpy(r->data.created_at, u.created_at);
    strcpy(r->data.updated_at, u.updated_at);
		r->next = NULL;
		if(head == NULL) {
		head = r;
		return;
	}
	temp = head;
	while(temp->next != NULL){
		temp = temp->next;
	}
	temp->next = r;
}

void display(struct node *head) {
	int ctr = 0;
	struct node *current;
  current = head;
  
	printf("\n----------------------------------------\n\n");
	while (current != NULL) {
    printf("\n\n---------- #%d ----------\n\n", ctr+1);
		printf("Full Name :: %s\n", current->data.name);
		printf("Location :: %s\n", current->data.location);
		printf("Bio :: %s\n", current->data.bio);
		printf("Public Repositories :: %d\n", current->data.public_repos);
		printf("Followers :: %d\n", current->data.followers);
		printf("Following :: %d\n", current->data.following);
		printf("Account created at :: %s\n", current->data.created_at);
		printf("Account updated at :: %s\n", current->data.updated_at);

		current = current->next;
		ctr++;
	}
}

void swap(struct node *a, struct node *b) 
{ 
    struct user_data temp = a->data; 
    a->data = b->data; 
    b->data = temp; 
}

void sort_by_followers(struct node *head) {
    int swapped, i; 
    struct node *ptr1; 
    struct node *lptr = NULL; 
  
    if (head == NULL) 
        return; 
    do
    { 
        swapped = 0; 
        ptr1 = head; 
        while (ptr1->next != lptr) 
        { 
            if (ptr1->data.followers < ptr1->next->data.followers) 
            {  
                swap(ptr1, ptr1->next); 
                swapped = 1; 
            } 
            ptr1 = ptr1->next; 
        } 
        lptr = ptr1; 
    } 
    while (swapped); 
}

void sort_by_following(struct node *head) {
    int swapped, i; 
    struct node *ptr1; 
    struct node *lptr = NULL; 
  
    if (head == NULL) 
        return; 
    do
    { 
        swapped = 0; 
        ptr1 = head; 
        while (ptr1->next != lptr) 
        { 
            if (ptr1->data.following < ptr1->next->data.following) 
            {  
                swap(ptr1, ptr1->next); 
                swapped = 1; 
            } 
            ptr1 = ptr1->next; 
        } 
        lptr = ptr1; 
    } 
    while (swapped); 
}

void sort_by_public_repos(struct node *head) {
    int swapped, i; 
    struct node *ptr1; 
    struct node *lptr = NULL; 
  
    if (head == NULL) 
        return; 
    do
    { 
        swapped = 0; 
        ptr1 = head; 
        while (ptr1->next != lptr) 
        { 
            if (ptr1->data.public_repos < ptr1->next->data.public_repos) 
            {  
                swap(ptr1, ptr1->next); 
                swapped = 1; 
            } 
            ptr1 = ptr1->next; 
        } 
        lptr = ptr1; 
    } 
    while (swapped); 
}

void sort_by_created_at(struct node *head) {
    int swapped, i; 
    struct node *ptr1; 
    struct node *lptr = NULL; 
  
    if (head == NULL) 
        return; 
    do
    { 
        swapped = 0; 
        ptr1 = head; 
        while (ptr1->next != lptr) 
        { 
            if (ptr1->data.created_at < ptr1->next->data.created_at) 
            {  
                swap(ptr1, ptr1->next); 
                swapped = 1; 
            } 
            ptr1 = ptr1->next; 
        } 
        lptr = ptr1; 
    } 
    while (swapped); 
}

void sort_by_updated_at(struct node *head) {
    int swapped, i; 
    struct node *ptr1; 
    struct node *lptr = NULL; 
  
    if (head == NULL) 
        return; 
    do
    { 
        swapped = 0; 
        ptr1 = head; 
        while (ptr1->next != lptr) 
        { 
            if (ptr1->data.updated_at < ptr1->next->data.updated_at) 
            {  
                swap(ptr1, ptr1->next); 
                swapped = 1; 
            } 
            ptr1 = ptr1->next; 
        } 
        lptr = ptr1; 
    } 
    while (swapped); 
}

static int jsoneq(const char *json, jsmntok_t *tok, const char *s) {
  if (tok->type == JSMN_STRING && (int)strlen(s) == tok->end - tok->start &&
      strncmp(json + tok->start, s, tok->end - tok->start) == 0) {
    return 0;
  }
  return -1;
}

struct user_data *parse_json(char *JSON_STRING) {
  int i;
  int r;
	char name[100] = "";
	char location[50] = "";
	char bio[300] = "";
	char public_repos[5] = "null";
	char followers[5] = "0";
	char following[5] = "0";
	char created_at[30] = "";
	char updated_at[30] = "";

  jsmn_parser p;
  jsmntok_t t[128];

	struct user_data *user = calloc(1, sizeof(struct user_data));

  jsmn_init(&p);
  r = jsmn_parse(&p, JSON_STRING, strlen(JSON_STRING), t,
                 sizeof(t) / sizeof(t[0]));

	for (i = 1; i < r; i++) {
    if (jsoneq(JSON_STRING, &t[i], "name") == 0) {
			strncpy(name, JSON_STRING + t[i + 1].start, t[i + 1].end - t[i + 1].start);
			strcpy(user->name, name);
			i++;
    }
		else if (jsoneq(JSON_STRING, &t[i], "location") == 0) {
			strncpy(location, JSON_STRING + t[i + 1].start, t[i + 1].end - t[i + 1].start);
			strcpy(user->location, location);
			i++;
		}
		else if (jsoneq(JSON_STRING, &t[i], "bio") == 0) {
			strncpy(bio, JSON_STRING + t[i + 1].start, t[i + 1].end - t[i + 1].start);
			strcpy(user->bio, bio);
			i++;
		}
		else if (jsoneq(JSON_STRING, &t[i], "public_repos") == 0) {
			strncpy(public_repos, JSON_STRING + t[i + 1].start, t[i + 1].end - t[i + 1].start);
			sscanf(public_repos, "%d", &user->public_repos);
			i++;
		}
		else if (jsoneq(JSON_STRING, &t[i], "followers") == 0) {
			strncpy(followers, JSON_STRING + t[i + 1].start, t[i + 1].end - t[i + 1].start);
			sscanf(followers, "%d", &user->followers);
			i++;
		}
		else if (jsoneq(JSON_STRING, &t[i], "following") == 0) {
			strncpy(following, JSON_STRING + t[i + 1].start, t[i + 1].end - t[i + 1].start);
			sscanf(following, "%d", &user->following);
			i++;
		}
		else if (jsoneq(JSON_STRING, &t[i], "created_at") == 0) {
			strncpy(created_at, JSON_STRING + t[i + 1].start, t[i + 1].end - t[i + 1].start);
			strcpy(user->created_at, created_at);
			i++;
		}
		else if (jsoneq(JSON_STRING, &t[i], "updated_at") == 0) {
			strncpy(updated_at, JSON_STRING + t[i + 1].start, t[i + 1].end - t[i + 1].start);
			strcpy(user->updated_at, updated_at);
			i++;
		}

  }
	return user;
}


struct user_data *request(char username[60]) {
    req_t req;           
    int ret = requests_init(&req); 
    if (ret) {
        return NULL;
    }
	// making the request to the /users/<username> endpoint

		char url[] = "https://api.github.com/users/";
		strcat(url, username);

    requests_get(&req, url); /* submit GET request */
        struct user_data *ptr;
		ptr = parse_json(req.text);

    requests_close(&req); 
    return ptr;
}

int main() {
    char username[60], c;
    struct user_data *ptr;
    int choice;

		printf("Enter Username: ");
		scanf("%s", username);
		ptr = request(username);
		insert(*ptr);

    while(1) {
        printf("Do you want to enter more usernames? (y/n): ");
        scanf("\n%c",&c);
        if(c == 'n' || c == 'N')
            break;
				else {
					printf("Enter Username: ");
		      scanf("%s", username);
		      ptr = request(username);
		      insert(*ptr);
				}
    }
		printf("\n\nSort users by: \n");
		printf("1. Number of Followers\n");
		printf("2. Number of Following\n");
		printf("3. Number of public repositories\n");
		printf("4. Date of account creation\n");
		printf("5. Date of account last updated\n");
    
		printf("\nEnter choice: ");
		scanf("%d", &choice);
		
		switch(choice) {
			case 1:
				printf("\n\nSorted by Followers.");
				sort_by_followers(head);
				break;
			case 2:
				printf("\n\nSorted by Following.");
				sort_by_following(head);
				break;
			case 3:
				printf("\n\nSorted by number of public repositories.");
				sort_by_public_repos(head);
				break;
			case 4:
				printf("\n\nSorted by date of account creation.");
				sort_by_created_at(head);
				break;
			case 5:
				printf("\n\nSorted by date of account last updated.");
				sort_by_updated_at(head);
				break;
			default:
				printf("Invalid choice");
		}
    
    display(head);
}

