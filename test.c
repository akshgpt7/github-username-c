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
    struct user_data *data;
    struct node *next;
};

struct node *head = NULL;

void insert(struct user_data *u) {
    struct node *r, *temp;
    r = calloc(1, sizeof(struct node));
    strcpy(r->data->name,u->name);
    strcpy(r->data->location,u->location);
    strcpy(r->data->bio,u->bio);
    r->data->public_repos=u->public_repos;
    r->data->followers=u->followers;
    r->data->following=u->following;
    strcpy(r->data->created_at,u->created_at);
    strcpy(r->data->updated_at,u->updated_at);
    r->next=NULL;
    if(head==NULL){
		head=r;
		return;
	}
	temp=head;
	while(temp->next!=NULL){
		temp=temp->next;
	}
	temp->next=r;
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
    req_t req;                     /* declare struct used to store data */
    int ret = requests_init(&req); /* setup */
    if (ret) {
        return NULL;
    }

		char url[] = "https://api.github.com/users/";
		strcat(url, username);

    requests_get(&req, url); /* submit GET request */
        struct user_data *ptr;
		ptr=parse_json(req.text);

    requests_close(&req); /* clean up */
    return ptr;
}

int main() {
    char username[60],c;
    while(1){
        printf("Enter Username:");
        scanf("%s",username);
        struct user_data *ptr;
        ptr=request(username);
        insert(ptr);
        printf("Press Y to continue and N to abort:");
        scanf("%c",&c);
        if(c=='N')
            break;
    }
}
// CHANGE main() TO: Y/N KI AUR INPUT YA NHI RATHER THAN ASKING NUMBER OF INPUTS
// THEN MAKE LINKED LIST AND SORT

