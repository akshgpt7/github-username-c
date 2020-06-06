#include <stdio.h>
#include <string.h>
#include "requests.h"


int request(char username[30]) {
    req_t req;                     /* declare struct used to store data */
    int ret = requests_init(&req); /* setup */
    if (ret) {
        return 1;
    }

		char url[] = "https://api.github.com/users/";
		strcat(url, username);

    requests_get(&req, url); /* submit GET request */
    printf("Request URL: %s\n", req.url);
    printf("Response Code: %lu\n", req.code);
    printf("Response Body:\n%s", req.text);

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
