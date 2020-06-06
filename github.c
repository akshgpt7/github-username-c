#include <stdio.h>
#include <string.h>
#include "requests.h"
#include "json-c/json.h"


int write_json_to_file(char *json) {
	FILE *fp;
	fp = fopen("response.json", "w");
	fprintf(fp, "%s", json);
	fclose(fp);
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
    
		write_json_to_file(req.text);

    requests_close(&req); /* clean up */
    return 0;
}



int main() {
	int i, n;

	printf("Enter number of users you want to fetch: ");
	scanf("%d", &n);

	char usernames[n][30];

	for (i=0; i<n; i++) {
		printf("Enter username %d: ", i+1);
		scanf("%s", &usernames[i][0]);
	}

	for (i=0; i<n; i++) {
    request(usernames[i]);
	}




}
