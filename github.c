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

static int jsoneq(const char *json, jsmntok_t *tok, const char *s) {
  if (tok->type == JSMN_STRING && (int)strlen(s) == tok->end - tok->start &&
      strncmp(json + tok->start, s, tok->end - tok->start) == 0) {
    return 0;
  }
  return -1;
}

int parse_json(char *JSON_STRING) {
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
	printf("%s\n", user->name);
	printf("%s\n", user->location);
	printf("%s\n", user->bio);
	printf("%d\n", user->followers);
	printf("%d\n", user->following);
	printf("%d\n", user->public_repos);
	printf("%s\n", user->created_at);
	printf("%s\n", user->updated_at);
}


int request(char username[60]) {
    req_t req;                     /* declare struct used to store data */
    int ret = requests_init(&req); /* setup */
    if (ret) {
        return 1;
    }

		char url[] = "https://api.github.com/users/";
		strcat(url, username);

    requests_get(&req, url); /* submit GET request */
    
		parse_json(req.text);

    requests_close(&req); /* clean up */
    return 0;
}

int main() {
	int i, n;

	printf("Enter number of users you want to fetch: ");
	scanf("%d", &n);

	char usernames[n][30];
	// struct user_data users_arr[n];

	for (i=0; i<n; i++) {
		printf("Enter username %d: ", i+1);
		scanf("%s", &usernames[i][0]);
	}

	for (i=0; i<n; i++) {
    request(usernames[i]);
	}




}
// CHANGE main() TO: Y/N KI AUR INPUT YA NHI RATHER THAN ASKING NUMBER OF INPUTS
// THEN MAKE LINKED LIST AND SORT
