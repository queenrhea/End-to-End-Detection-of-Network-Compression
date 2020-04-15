#define _XOPEN_SOURCE
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

struct user {
	char firstname[50];
	char lastname[50];
	char username[50];
	char password[256];
	int admin;
};


char* cs336Hash(const char* password) {
	return crypt(password, "00");
}

struct user* createUsers(int* count) {
	FILE* fp;
	char ch = '0';

	fp = fopen("credential_file", "r");
	while((ch = getc(fp))!= EOF)
	{
		if (ch == '\n')
			++*(count);
	}
	fclose(fp);

	return (struct user*) calloc(sizeof(struct user), *count);

}


void populateUsers(void* users) {
	char line[1000];
	FILE* f = fopen("credential_file", "r");
	if (f == NULL) {
		return;
	}
	int index = 0;
	int userIndex = 0;
	while (!feof(f))
	{
		char ch = fgetc(f);
		if (ch == '\n') {
			line[index] = 0;
			struct user* u = (struct user*)users + userIndex;
			char* token = strtok(line, "\t");
			strcpy(u->firstname, token);
			token = strtok(NULL, "\t");
			strcpy(u->lastname, token);
			token = strtok(NULL, "\t");
			strcpy(u->username, token);
			token = strtok(NULL, "\t");
			strcpy(u->password, token);
			token = strtok(NULL, "\t");
			u->admin = atoi(token);
			index = 0;
			++userIndex;
		}
		else {
			line[index++] = ch;
		}
	}
	fclose(f);

	printf("Exiting populate users\n");
}


int checkAdminPassword(char* password, struct user* users, int count) {
	for (int i = 0; i < count; ++i) {
		if (strcmp((users + i)->username, "admin") == 0) {
			if (strcmp((users+i)-> password, cs336Hash(password)) == 0) {
				return 1;
	    		}
	    	else {
			return 0;
		    }
		}
	}
	return 0;
}

struct user* addUser(struct user* users, int* count, char* username, char* password, char* firstname, char* lastname, int admin) {
	++*count;
	struct user* newUsers = (struct user*) calloc(sizeof(struct user), *count);
	for(int line = 0; line< *count-1; ++line)
	{
		strcpy((newUsers + line)  -> firstname, (users + line)  -> firstname);
		strcpy((newUsers + line)  -> lastname, (users + line)  -> lastname);
		strcpy((newUsers + line)  -> username, (users + line)  -> username);
		strcpy((newUsers + line)  -> password, (users + line)  -> password);
		(users + line)  -> admin = (users + line)  -> admin;
	
	}
	strcpy((newUsers + *count - 1)  -> firstname, firstname);
	strcpy((newUsers + *count - 1)  -> lastname, lastname);
	strcpy((newUsers + *count - 1)  -> username, username);
	strcpy((newUsers + *count - 1)  -> password, password);
	(users + *count - 1)  -> admin = admin;
	
	free (users);
	return newUsers;
	     
}

void saveUsers(struct user* users, int count) {
	FILE *fp;
	fp = fopen("credential_file", "w");
	
	char* storageInt = " ";
	for(int line = 0; line < count; ++line)
	{	
		//Typecast int -> char*
		storageInt = ((users + line)  -> admin) + "0";
		fputs((users + line)  -> firstname, fp);
		fputs("\t", fp);
		fputs((users + line)  -> lastname, fp);
		fputs("\t", fp);
		fputs((users + line)  -> username, fp);
		fputs("\t", fp);
		fputs((users + line)  -> password, fp);
		fputs("\t", fp);
		fputs(storageInt, fp);
		fputs("\n", fp);	
	}
	fclose(fp);
}



void printUsers(struct user*users, int count)
{
	for (int i = 0; i < count; ++i) 
	{
		printf("First:%s\n",((users +i)->firstname));
		printf("Last:%s\n",((users +i)->lastname));
		printf("User:%s\n",((users +i)->username));
		printf("Pass:%s\n",(users +i)->password);
		printf("Admin:%d\n\n",(users +i)->admin);
	}
}

int main(void) {
	int user_count = 0;
	struct user* users = createUsers(&user_count);
	if (users == NULL) {
		return EXIT_FAILURE;
	}
	printf("\n Entering Populate users\n");
	populateUsers(users);
	printf("\n Exiting 2 Populate users\n");

	printUsers(users, user_count);
	printf("Enter admin password to add new users:");
	char entered_admin_password[50];
	scanf("%s", entered_admin_password);
	if (checkAdminPassword(entered_admin_password, users, user_count)) {
		struct user new_user;
		printf("Enter username:");
		scanf("%s", new_user.username);
		printf("Enter first name:");
		scanf("%s", new_user.firstname);
		printf("Enter last name:");
		scanf("%s", new_user.lastname);
		printf("Enter password:");
		scanf("%s", new_user.password);
		printf("Enter admin level:");
		scanf("%d", &(new_user.admin));
		users = addUser(users, &user_count, new_user.username, cs336Hash(new_user.password), new_user.firstname, new_user.lastname, new_user.admin);
		if (users == NULL) {
		    return EXIT_FAILURE;
		}
	}
	else{
		printf("False\n");
	}
	printUsers(users, user_count);
	saveUsers(users, user_count);
	free(users);
	return EXIT_SUCCESS;
}

