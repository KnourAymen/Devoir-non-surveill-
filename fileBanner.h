void readFileBanner() {
    FILE* file = fopen("gestionTexte.txt", "r");  // Open the file in read mode
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return;
    }

    char buffer[100];  // Buffer to store each line of the file

    // Read and print each line of the file
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("%s", buffer);
    }

    fclose(file);  // Close the file
}
