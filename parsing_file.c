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
