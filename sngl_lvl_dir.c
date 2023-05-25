#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILES 100
#define MAX_FILENAME_LENGTH 50

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

int main()
{
    Directory singleLevelDirectory;
    strcpy(singleLevelDirectory.name, "Single Level Directory");
    singleLevelDirectory.fileCount = 0;

    File file1, file2;
    strcpy(file1.name, "File 1");
    strcpy(file2.name, "File 2");

    // Add files to the directory
    if (singleLevelDirectory.fileCount < MAX_FILES)
    {
        singleLevelDirectory.files[singleLevelDirectory.fileCount++] = file1;
        singleLevelDirectory.files[singleLevelDirectory.fileCount++] = file2;
    }

    // Display the files in the directory
    printf("Files in '%s':\n", singleLevelDirectory.name);
    for (int i = 0; i < singleLevelDirectory.fileCount; i++)
    {
        printf("%s\n", singleLevelDirectory.files[i].name);
    }

    return 0;
}
