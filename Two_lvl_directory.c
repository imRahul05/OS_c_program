#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILES 100
#define MAX_FILENAME_LENGTH 50
#define MAX_DIRECTORIES 10

typedef struct
{
    char name[MAX_FILENAME_LENGTH];
} File;

typedef struct
{
    char name[MAX_FILENAME_LENGTH];
    int fileCount;
    File files[MAX_FILES];
} Directory;

typedef struct
{
    char name[MAX_FILENAME_LENGTH];
    int directoryCount;
    Directory directories[MAX_DIRECTORIES];
} TwoLevelDirectory;

int main()
{
    TwoLevelDirectory twoLevelDirectory;
    strcpy(twoLevelDirectory.name, "Two Level Directory");
    twoLevelDirectory.directoryCount = 0;

    Directory directory1, directory2;
    strcpy(directory1.name, "Directory 1");
    strcpy(directory2.name, "Directory 2");

    File file1, file2;
    strcpy(file1.name, "File 1");
    strcpy(file2.name, "File 2");

    // Add files to Directory 1
    if (directory1.fileCount < MAX_FILES)
    {
        directory1.files[directory1.fileCount++] = file1;
    }

    // Add files to Directory 2
    if (directory2.fileCount < MAX_FILES)
    {
        directory2.files[directory2.fileCount++] = file2;
    }

    // Add directories to the Two Level Directory
    if (twoLevelDirectory.directoryCount < MAX_DIRECTORIES)
    {
        twoLevelDirectory.directories[twoLevelDirectory.directoryCount++] = directory1;
        twoLevelDirectory.directories[twoLevelDirectory.directoryCount++] = directory2;
    }

    // Display the files in Directory 1
    printf("Files in '%s/%s':\n", twoLevelDirectory.name, directory1.name);
    for (int i = 0; i < directory1.fileCount; i++)
    {
        printf("%s\n", directory1.files[i].name);
    }

    // Display the files in Directory 2
    printf("Files in '%s/%s':\n", twoLevelDirectory.name, directory2.name);
    for (int i = 0; i < directory2.fileCount; i++)
    {
        printf("%s\n", directory2.files[i].name);
    }

    return 0;
}
