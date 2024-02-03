void readFileProfile() {
    FILE* file = fopen("profile.txt", "r");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return;
    }

    char buffer[100];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("%s", buffer);
    }

    fclose(file);
}
