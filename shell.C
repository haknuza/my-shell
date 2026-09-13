    #ifndef _GNU_SOURCE
    #define _GNU_SOURCE
    #endif
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    #include <sys/types.h>
    #include <sys/wait.h>


int GetArgsCount(char* text, ssize_t len)
{
    int count = 0;
    int inside_word = 0;
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (text[i] != ' ' && !inside_word)
        {
            count++;
            inside_word = 1;
        }
        else if (text[i] == ' ')
        {
            inside_word = 0;
            text[i] = '\0';
        }
    }
    return count;
}

void FillInArgs(char** args, int args_count, char* text)
{
    int j = 0;
    for (int i = 0; i < args_count; i++)
    {
        args[i] = &text[j];
        while (text[j] != '\0')
        {
            j++;
        }
        j++;
    }
    args[args_count] = NULL;
}

int main()
{
    char* text = NULL;
    size_t size = 0;
    ssize_t chars_read;
    int args_count = 0;
    pid_t childId;

    while (1)
    {
        char* currentDir = getcwd(NULL, 0);
        printf("%s --> ", currentDir);
        free(currentDir);
        //fflush(stdout);

        chars_read = getline(&text, &size, stdin);

        if (chars_read == -1)
        {
            printf("\nits over ;( \n");
            break;
        }

        if ((chars_read != 0) && text[chars_read-1] == '\n')
        {
            text[chars_read-1] = '\0';
        }
        if (text[0] == '\0') 
        {
            continue;
        }
        
        args_count = GetArgsCount(text, chars_read);

        if (args_count == 0)
        {
            continue;
        }

        char* args[args_count+1];
        FillInArgs(args, args_count, text);


                //IF USER EXITS
        if (strcmp(args[0], "exit") == 0)
        {
            break;
        }
        if (strcmp(args[0], "cd") == 0)
        {
            char* path = args[1];
            if (path == NULL)
            {
                path = getenv("HOME");
            }
            if (chdir(path) != 0)   
            {
                perror("Invalid input: ");
                continue;
            }
            continue;

        }

        childId = fork();

        if (childId < 0)
        {
            perror("premature girl");
            exit(EXIT_FAILURE);
        }
        if (childId == 0)
        {
            execvp(args[0], args);
            perror("error running the command"); 
            exit(EXIT_FAILURE);
        }
        else if (childId > 0)
        {
            waitpid(childId, NULL, 0);
        }
        //else {printf("written command-> %s\n", text);}

    // amaoralalalsdasd

    }
    free(text);
}
