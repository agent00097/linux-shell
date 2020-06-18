#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>

char error_message[30] = "An error has occurred\n";

//Function for me
int check_redir(char *token);
void sort_it_out(char *thisworks, char **getting, char *arg, char **all_paths, char **final_paths, char *comeon, char filename[], int total_paths, size_t i, size_t n, int child, int status, int path_position, int doku, char **path, char *path_copy, char *command);
void execute_function_redir(char **path, char *filename, char *path_copy);
void check_path(char **final_path, int this_much);
int check_if_path_has_arguments(char *token);
void run_cd(char *token);
void execute_function(char **path, int status, int child, char *path_copy);



void sort_it_out(char *thisworks, char **getting, char *arg, char **all_paths, char **final_paths, char *comeon, char filename[], int total_paths, size_t i, size_t n, int child, int status, int path_position, int doku, char **path, char *path_copy, char *command)
{

    char *new_token = malloc(sizeof(char) * 20);

    new_token = strtok(command, " \n\t\r");

    //If user enters path

    //first check if path has any arguments


    //If user presses cd
   

        //If not a path or a built in command then user checks for whether the command exists in the provided paths

        for (int r = 0; r < total_paths; r++)
        {
            strcpy(path_copy, final_paths[r]);
            strcat(path_copy, "/");
            strcat(path_copy, new_token);

            if (access(path_copy, X_OK) == 0)
            {
                comeon = path_copy;
                strcpy(arg, path_copy);
                break;
            }
        }

        for (i = 0; i < 16 && new_token != NULL; i++)
        {
            char *p;
            char *a;

            //

            if (new_token != NULL)
            {
                p = strstr(new_token, ">");
                if (p)
                {
                    doku = 1;
                    new_token = strtok(NULL, " \t\n\r");
                    if (new_token == NULL)
                    {
                        doku++;
                    }
                    else
                    {
                        strcpy(filename, new_token);
                        strcpy(thisworks, "./");
                        strcat(thisworks, new_token);
                        new_token = strtok(NULL, " \t\n\r");
                        if (new_token != NULL)
                        {
                            doku++;
                        }
                    }
                }
                else
                {
                    path[i] = new_token;
                    path_position = i + 1;
                    new_token = strtok(NULL, " \t\n\r");
                    strcpy(thisworks, "notthis");
                }
            }
        }
        path[path_position] = NULL;
        for (int i = 0; i < path_position; i++)
        {
            strcpy(getting[i], path[i]);
        }
        getting[path_position] = NULL;
    }

void execute_function_redir(char **path, char *filename, char *path_copy)
{
    int rc = fork();
    if (rc < 0)
    {
        write(STDERR_FILENO, error_message, strlen(error_message));
    }
    else if (rc == 0)
    {
        close(STDOUT_FILENO);
        open(filename, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
        if (execv(path_copy, path))
        {
            write(STDERR_FILENO, error_message, strlen(error_message));
        }
    }
    else
    {
        int rc_wait = wait(NULL);
    }
}

//Important function

void run_cd(char *token)
{
    token = strtok(NULL, " \t\n\r");
    if (chdir(token) != 0)
    {
        write(STDERR_FILENO, error_message, strlen(error_message));
    }
}

void execute_function(char **path, int status, int child, char *path_copy)
{

    child = fork();
    if (child < 0)
    {
        write(STDERR_FILENO, error_message, strlen(error_message));
    }
    else if (child == 0)
    {
        if (execv(path_copy, path))
        {
            write(STDERR_FILENO, error_message, strlen(error_message));
        }
        exit(1);
    }
    else
    {
        int rc_wait = wait(NULL);
    }
}

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        //Interactive mode in shell

        char **all_paths = malloc(sizeof(char *) * 20);
        for (int i = 0; i < 20; i++)
        {
            all_paths[i] = (char *)malloc(21);
        }

        char **final_paths = malloc(sizeof(char *) * 20);
        for (int i = 0; i < 20; i++)
        {
            final_paths[i] = (char *)malloc(21);
        }

        //initial path provided
        final_paths[0] = "/bin";

        //Initial
        char *comeon;
        char filename[250];
        int total_paths = 1;
        size_t i, n;
        int child;
        int status;
        while (1)
        {

            int path_position = 0;
            int doku = 0;
            char **path = malloc(sizeof(char *) * 20);
            for (int i = 0; i < 20; i++)
            {
                path[i] = (char *)malloc(21);
            }
            char *path_copy = (char *)malloc(21);
            char *command = (char *)malloc(50);
            char *token = (char *)malloc(21);

            printf("mash> ");

            if (getline(&command, &n, stdin) == -1)
            {
                break;
            }

            char *new_here = strstr(command, "&");
            if (strstr(command, "&"))
            {
                char *filename2 = malloc(sizeof(char) * 20);
                char *filename3 = malloc(sizeof(char) * 20);
                char *filename4 = malloc(sizeof(char) * 20);
                char *token2 = malloc(sizeof(char) * 50);
                token2 = NULL;
                char *token3 = malloc(sizeof(char) * 50);
                char *token4 = malloc(sizeof(char) * 50);
                token3 = NULL;
                token4 = NULL;
                char **getting2 = malloc(sizeof(char *) * 10);
                for (int i = 0; i < 20; i++)
                {
                    getting2[i] = (char *)malloc(21);
                }
                char *arg2 = malloc(sizeof(char) * 10);
                char **getting3 = malloc(sizeof(char *) * 10);
                for (int i = 0; i < 20; i++)
                {
                    getting3[i] = (char *)malloc(21);
                }
                char *arg3 = malloc(sizeof(char) * 10);
                char **getting4 = malloc(sizeof(char *) * 10);
                for (int i = 0; i < 20; i++)
                {
                    getting4[i] = (char *)malloc(21);
                }
                char *arg4 = malloc(sizeof(char) * 10);
                token2 = strtok(command, "&");
                token3 = strtok(NULL, "&");
                token4 = strtok(NULL, "&");

                if (token2 == NULL && token2 == "\n")
                {
                    continue;
                }
                if (token3 == NULL && token2 != NULL && token2 == "\n")
                {
                    sort_it_out(filename2, getting2, arg2, all_paths, final_paths, comeon, filename, total_paths, i, n, child, status, path_position, doku, path, path_copy, token2);
                }

                if (token4 == NULL && token3 != NULL)
                {
                    sort_it_out(filename2, getting2, arg2, all_paths, final_paths, comeon, filename, total_paths, i, n, child, status, path_position, doku, path, path_copy, token2);
                    sort_it_out(filename3, getting3, arg3, all_paths, final_paths, comeon, filename, total_paths, i, n, child, status, path_position, doku, path, path_copy, token3);

                    if (filename3 != "")
                    {
                        int child12 = fork();
                        if (child12 < 0)
                        {

                            write(STDERR_FILENO, error_message, strlen(error_message));
                        }
                        else if (child12 == 0)
                        {
                            close(STDOUT_FILENO);
                            open(filename2, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
                            if (execv(arg2, getting2))
                            {
                                write(STDERR_FILENO, error_message, strlen(error_message));
                            }
                            exit(1);
                        }
                        int child22 = fork();
                        if (child22 < 0)
                        {
                            write(STDERR_FILENO, error_message, strlen(error_message));
                        }
                        else if (child22 == 0)
                        {
                            close(STDOUT_FILENO);
                            open(filename3, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
                            if (execv(arg3, getting3))
                            {

                                write(STDERR_FILENO, error_message, strlen(error_message));
                            }
                            exit(1);
                        }

                        int status;
                        pid_t pid;
                        int n = 2;
                        while (n > 0)
                        {
                            pid = wait(&status);
                            //printf("Child with PID %ld exited with status 0x%x.\n", (long)pid, status);
                            --n; // TODO(pts): Remove pid from the pids array.
                        }
                    }
                    else
                    {
                        int child12 = fork();
                        if (child12 < 0)
                        {
                            write(STDERR_FILENO, error_message, strlen(error_message));
                        }
                        else if (child12 == 0)
                        {
                            if (execv(arg2, getting2))
                            {
                                write(STDERR_FILENO, error_message, strlen(error_message));
                            }
                            exit(1);
                        }
                        int child22 = fork();
                        if (child22 < 0)
                        {
                            write(STDERR_FILENO, error_message, strlen(error_message));
                        }
                        else if (child22 == 0)
                        {
                            if (execv(arg3, getting3))
                            {
                                write(STDERR_FILENO, error_message, strlen(error_message));
                            }
                            exit(1);
                        }

                        int status;
                        pid_t pid;
                        int n = 2;
                        while (n > 0)
                        {
                            pid = wait(&status);
                            //printf("Child with PID %ld exited with status 0x%x.\n", (long)pid, status);
                            --n; // TODO(pts): Remove pid from the pids array.
                        }
                    }
                }
                if (token3 != NULL && token4 != NULL)
                {
                    sort_it_out(filename2, getting2, arg2, all_paths, final_paths, comeon, filename, total_paths, i, n, child, status, path_position, doku, path, path_copy, token2);
                    sort_it_out(filename3, getting3, arg3, all_paths, final_paths, comeon, filename, total_paths, i, n, child, status, path_position, doku, path, path_copy, token3);
                    if (strcmp(token4, "\n") == 0)
                    {
                        int child12 = fork();
                        if (child12 < 0)
                        {
                            write(STDERR_FILENO, error_message, strlen(error_message));
                        }
                        else if (child12 == 0)
                        {
                            if (execv(arg2, getting2))
                            {
                                write(STDERR_FILENO, error_message, strlen(error_message));
                            }
                            exit(1);
                        }
                        int child22 = fork();
                        if (child22 < 0)
                        {
                            write(STDERR_FILENO, error_message, strlen(error_message));
                        }
                        else if (child22 == 0)
                        {
                            if (execv(arg3, getting3))
                            {
                                write(STDERR_FILENO, error_message, strlen(error_message));
                            }
                            exit(1);
                        }

                        int status;
                        pid_t pid;
                        int n = 2;
                        while (n > 0)
                        {
                            pid = wait(&status);
                            //printf("Child with PID %ld exited with status 0x%x.\n", (long)pid, status);
                            --n; // TODO(pts): Remove pid from the pids array.
                        }
                    }
                    else
                    {

                        sort_it_out(filename4, getting4, arg4, all_paths, final_paths, comeon, filename, total_paths, i, n, child, status, path_position, doku, path, path_copy, token4);
                        if (strcmp(filename4, "notthis") != 0)
                        {
                            int child13 = fork();

                            if (child13 < 0)
                            {
                                write(STDERR_FILENO, error_message, strlen(error_message));
                            }
                            else if (child13 == 0)
                            {
                                close(STDOUT_FILENO);
                                open(filename2, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
                                if (execv(arg2, getting2))
                                {
                                    write(STDERR_FILENO, error_message, strlen(error_message));
                                }
                                exit(1);
                            }
                            int child23 = fork();
                            if (child13 < 0)
                            {
                                write(STDERR_FILENO, error_message, strlen(error_message));
                            }
                            else if (child23 == 0)
                            {
                                close(STDOUT_FILENO);
                                open(filename3, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
                                if (execv(arg3, getting3))
                                {
                                    write(STDERR_FILENO, error_message, strlen(error_message));
                                }
                                exit(1);
                            }
                            int child33 = fork();
                            if (child13 < 0)
                            {
                                write(STDERR_FILENO, error_message, strlen(error_message));
                            }
                            else if (child33 == 0)
                            {
                                close(STDOUT_FILENO);
                                open(filename4, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
                                if (execv(arg4, getting4))
                                {
                                    write(STDERR_FILENO, error_message, strlen(error_message));
                                }
                            }
                            int status;
                            pid_t pid;
                            int n = 3;
                            while (n > 0)
                            {
                                pid = wait(&status);
                                //printf("Child with PID %ld exited with status 0x%x.\n", (long)pid, status);
                                --n; // TODO(pts): Remove pid from the pids array.
                            }
                        }
                        else
                        {
                            int child13 = fork();

                            if (child13 < 0)
                            {
                                write(STDERR_FILENO, error_message, strlen(error_message));
                            }
                            else if (child13 == 0)
                            {
                                if (execv(arg2, getting2))
                                {
                                    write(STDERR_FILENO, error_message, strlen(error_message));
                                }
                                exit(1);
                            }
                            int child23 = fork();
                            if (child13 < 0)
                            {
                                write(STDERR_FILENO, error_message, strlen(error_message));
                            }
                            else if (child23 == 0)
                            {
                                if (execv(arg3, getting3))
                                {
                                    write(STDERR_FILENO, error_message, strlen(error_message));
                                }
                                exit(1);
                            }
                            int child33 = fork();
                            if (child13 < 0)
                            {
                                write(STDERR_FILENO, error_message, strlen(error_message));
                            }
                            else if (child33 == 0)
                            {
                                if (execv(arg4, getting4))
                                {
                                    write(STDERR_FILENO, error_message, strlen(error_message));
                                }
                            }
                            int status;
                            pid_t pid;
                            int n = 3;
                            while (n > 0)
                            {
                                pid = wait(&status);
                                //printf("Child with PID %ld exited with status 0x%x.\n", (long)pid, status);
                                --n; // TODO(pts): Remove pid from the pids array.
                            }
                        }
                    }
                }
            }
            else
            {

                //clearing all the whitespaces
                //sort_it_out(all_paths, final_paths, comeon, filename, total_paths, i, n, child, status, path_position, doku, path, path_copy, command);
                token = strtok(command, " \n\t\r");

                //If user enters path

                //first check if path has any arguments
                if (strcmp(token, "path") == 0)
                {

                    int see = 1;
                    for (i = 0; i < 16 && token != NULL; i++)
                    {

                        token = strtok(NULL, " \t\n\r");
                        if (token != NULL)
                        {
                            if (see = 1)
                            {
                                total_paths = 0;
                            }
                            all_paths[i] = token;
                            total_paths++;
                            see++;
                        }
                        if (token == NULL && see == 1)
                        {
                            all_paths[0] = NULL;
                            final_paths[0] = NULL;
                            total_paths = 0;
                        }
                    }
                    all_paths[i] = NULL;

                    //Copying the paths into new string array
                    for (i = 0; i < total_paths; i++)
                    {
                        final_paths[i] = all_paths[i];
                    }
                }

                //If first token found is & then execute other commands after &
                else if (strcmp(token, "&") == 0)
                {
                    break;
                }

                //If user presses exit

                else if (strcmp(token, "exit") == 0)
                {
                    token = strtok(NULL, " \t\n\r");
                    if (token != NULL)
                    {
                        write(STDERR_FILENO, error_message, strlen(error_message));
                    }
                    else
                    {
                        exit(0);
                    }
                }

                //If user presses cd
                else if (strcmp(token, "cd") == 0)
                {
                    run_cd(token);
                }

                else
                {

                    //If not a path or a built in command then user checks for whether the command exists in the provided paths

                    for (int r = 0; r < total_paths; r++)
                    {
                        strcpy(path_copy, final_paths[r]);
                        strcat(path_copy, "/");
                        strcat(path_copy, token);

                        if (access(path_copy, X_OK) == 0)
                        {
                            comeon = path_copy;
                            break;
                        }
                    }

                    for (i = 0; i < 16 && token != NULL; i++)
                    {
                        char *p;
                        char *a;

                        //

                        if (token != NULL)
                        {
                            p = strstr(token, ">");
                            if (p)
                            {
                                doku = 1;
                                token = strtok(NULL, " \t\n\r");
                                if (token == NULL)
                                {
                                    doku++;
                                }
                                else
                                {
                                    strcpy(filename, token);
                                    token = strtok(NULL, " \t\n\r");
                                    if (token != NULL)
                                    {
                                        doku++;
                                    }
                                }
                            }
                            else
                            {
                                path[i] = token;
                                path_position = i + 1;
                                token = strtok(NULL, " \t\n\r");
                            }
                        }
                    }
                    path[path_position] = NULL;
                    if (doku == 1)
                    {
                        //Redirection
                        char *with_slash = (char *)malloc(21);
                        strcat(with_slash, "./");
                        strcat(with_slash, filename);
                        execute_function_redir(path, with_slash, comeon);
                    }
                    else if (doku == 0)
                    {
                        if (comeon != NULL)
                        {
                            execute_function(path, status, child, comeon);
                        }
                        else
                        {
                            write(STDERR_FILENO, error_message, strlen(error_message));
                        }
                        comeon = NULL;
                    }
                    else
                    {
                        write(STDERR_FILENO, error_message, strlen(error_message));
                        comeon = NULL;
                    }
                }
            }
        }
    }
    else if (argc == 2)
    {
        //reading a batch file
        FILE *file_to_open = fopen(argv[1], "r");

        if (file_to_open == NULL)
        {
            write(STDERR_FILENO, error_message, strlen(error_message));
            exit(1);
        }
        else
        {
            char **all_paths = malloc(sizeof(char *) * 20);
            for (int i = 0; i < 20; i++)
            {
                all_paths[i] = (char *)malloc(21);
            }
            char **final_paths = malloc(sizeof(char *) * 20);
            for (int i = 0; i < 20; i++)
            {
                final_paths[i] = (char *)malloc(21);
            }

            //initial path provided
            final_paths[0] = "/bin";

            //Initial
            char *comeon;
            char filename[250];
            int total_paths = 1;
            size_t i, n;
            pid_t child;
            int status;
            while (1)
            {
                int path_position = 0;
                int doku = 0;
                char **path = malloc(sizeof(char *) * 20);
                for (int i = 0; i < 20; i++)
                {
                    path[i] = (char *)malloc(21);
                }
                char *path_copy = (char *)malloc(21);
                char *command = (char *)malloc(70);
                char *token = (char *)malloc(21);

                if (getline(&command, &n, file_to_open) == -1)
                {
                    break;
                }

                char *a = strstr(command, "&");
                //If user enters path
                if (a)
                {
                    char *filename2 = malloc(sizeof(char) * 20);
                    char *filename3 = malloc(sizeof(char) * 20);
                    char *filename4 = malloc(sizeof(char) * 20);
                    char *token2 = malloc(sizeof(char) * 50);
                    token2 = NULL;
                    char *token3 = malloc(sizeof(char) * 50);
                    char *token4 = malloc(sizeof(char) * 50);
                    token3 = NULL;
                    token4 = NULL;
                    char **getting2 = malloc(sizeof(char *) * 10);
                    for (int i = 0; i < 20; i++)
                    {
                        getting2[i] = (char *)malloc(21);
                    }
                    char *arg2 = malloc(sizeof(char) * 10);
                    char **getting3 = malloc(sizeof(char *) * 10);
                    for (int i = 0; i < 20; i++)
                    {
                        getting3[i] = (char *)malloc(21);
                    }
                    char *arg3 = malloc(sizeof(char) * 10);
                    char **getting4 = malloc(sizeof(char *) * 10);
                    for (int i = 0; i < 20; i++)
                    {
                        getting4[i] = (char *)malloc(21);
                    }
                    char *arg4 = malloc(sizeof(char) * 10);
                    token2 = strtok(command, "&");
                    token3 = strtok(NULL, "&");
                    token4 = strtok(NULL, "&");

                    if (token2 == NULL && token2 == "\n")
                    {
                        continue;
                    }
                    if (token3 == NULL && token2 != NULL && token2 == "\n")
                    {
                        sort_it_out(filename2, getting2, arg2, all_paths, final_paths, comeon, filename, total_paths, i, n, child, status, path_position, doku, path, path_copy, token2);
                    }

                    if (token4 == NULL && token3 != NULL)
                    {
                        sort_it_out(filename2, getting2, arg2, all_paths, final_paths, comeon, filename, total_paths, i, n, child, status, path_position, doku, path, path_copy, token2);
                        sort_it_out(filename3, getting3, arg3, all_paths, final_paths, comeon, filename, total_paths, i, n, child, status, path_position, doku, path, path_copy, token3);

                        if (filename3 != "")
                        {
                            int child12 = fork();
                            if (child12 < 0)
                            {

                                write(STDERR_FILENO, error_message, strlen(error_message));
                            }
                            else if (child12 == 0)
                            {
                                close(STDOUT_FILENO);
                                open(filename2, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
                                if (execv(arg2, getting2))
                                {
                                    write(STDERR_FILENO, error_message, strlen(error_message));
                                }
                                exit(1);
                            }
                            int child22 = fork();
                            if (child22 < 0)
                            {
                                write(STDERR_FILENO, error_message, strlen(error_message));
                            }
                            else if (child22 == 0)
                            {
                                close(STDOUT_FILENO);
                                open(filename3, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
                                if (execv(arg3, getting3))
                                {

                                    write(STDERR_FILENO, error_message, strlen(error_message));
                                }
                                exit(1);
                            }

                            int status;
                            pid_t pid;
                            int n = 2;
                            while (n > 0)
                            {
                                pid = wait(&status);
                                //printf("Child with PID %ld exited with status 0x%x.\n", (long)pid, status);
                                --n; // TODO(pts): Remove pid from the pids array.
                            }
                        }
                        else
                        {
                            int child12 = fork();
                            if (child12 < 0)
                            {
                                write(STDERR_FILENO, error_message, strlen(error_message));
                            }
                            else if (child12 == 0)
                            {
                                if (execv(arg2, getting2))
                                {
                                    write(STDERR_FILENO, error_message, strlen(error_message));
                                }
                                exit(1);
                            }
                            int child22 = fork();
                            if (child22 < 0)
                            {
                                write(STDERR_FILENO, error_message, strlen(error_message));
                            }
                            else if (child22 == 0)
                            {
                                if (execv(arg3, getting3))
                                {
                                    write(STDERR_FILENO, error_message, strlen(error_message));
                                }
                                exit(1);
                            }

                            int status;
                            pid_t pid;
                            int n = 2;
                            while (n > 0)
                            {
                                pid = wait(&status);
                                //printf("Child with PID %ld exited with status 0x%x.\n", (long)pid, status);
                                --n; // TODO(pts): Remove pid from the pids array.
                            }
                        }
                    }
                    if (token3 != NULL && token4 != NULL)
                    {
                        sort_it_out(filename2, getting2, arg2, all_paths, final_paths, comeon, filename, total_paths, i, n, child, status, path_position, doku, path, path_copy, token2);
                        sort_it_out(filename3, getting3, arg3, all_paths, final_paths, comeon, filename, total_paths, i, n, child, status, path_position, doku, path, path_copy, token3);
                        if (strcmp(token4, "\n") == 0)
                        {
                            int child12 = fork();
                            if (child12 < 0)
                            {
                                write(STDERR_FILENO, error_message, strlen(error_message));
                            }
                            else if (child12 == 0)
                            {
                                if (execv(arg2, getting2))
                                {
                                    write(STDERR_FILENO, error_message, strlen(error_message));
                                }
                                exit(1);
                            }
                            int child22 = fork();
                            if (child22 < 0)
                            {
                                write(STDERR_FILENO, error_message, strlen(error_message));
                            }
                            else if (child22 == 0)
                            {
                                if (execv(arg3, getting3))
                                {
                                    write(STDERR_FILENO, error_message, strlen(error_message));
                                }
                                exit(1);
                            }

                            int status;
                            pid_t pid;
                            int n = 2;
                            while (n > 0)
                            {
                                pid = wait(&status);
                                //printf("Child with PID %ld exited with status 0x%x.\n", (long)pid, status);
                                --n; // TODO(pts): Remove pid from the pids array.
                            }
                        }
                        else
                        {

                            sort_it_out(filename4, getting4, arg4, all_paths, final_paths, comeon, filename, total_paths, i, n, child, status, path_position, doku, path, path_copy, token4);
                            if (strcmp(filename4, "notthis") != 0)
                            {
                                int child13 = fork();

                                if (child13 < 0)
                                {
                                    write(STDERR_FILENO, error_message, strlen(error_message));
                                }
                                else if (child13 == 0)
                                {
                                    close(STDOUT_FILENO);
                                    open(filename2, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
                                    if (execv(arg2, getting2))
                                    {
                                        write(STDERR_FILENO, error_message, strlen(error_message));
                                    }
                                    exit(1);
                                }
                                int child23 = fork();
                                if (child13 < 0)
                                {
                                    write(STDERR_FILENO, error_message, strlen(error_message));
                                }
                                else if (child23 == 0)
                                {
                                    close(STDOUT_FILENO);
                                    open(filename3, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
                                    if (execv(arg3, getting3))
                                    {
                                        write(STDERR_FILENO, error_message, strlen(error_message));
                                    }
                                    exit(1);
                                }
                                int child33 = fork();
                                if (child13 < 0)
                                {
                                    write(STDERR_FILENO, error_message, strlen(error_message));
                                }
                                else if (child33 == 0)
                                {
                                    close(STDOUT_FILENO);
                                    open(filename4, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
                                    if (execv(arg4, getting4))
                                    {
                                        write(STDERR_FILENO, error_message, strlen(error_message));
                                    }
                                }
                                int status;
                                pid_t pid;
                                int n = 3;
                                while (n > 0)
                                {
                                    pid = wait(&status);
                                    //printf("Child with PID %ld exited with status 0x%x.\n", (long)pid, status);
                                    --n; // TODO(pts): Remove pid from the pids array.
                                }
                            }
                            else
                            {
                                int child13 = fork();

                                if (child13 < 0)
                                {
                                    write(STDERR_FILENO, error_message, strlen(error_message));
                                }
                                else if (child13 == 0)
                                {
                                    if (execv(arg2, getting2))
                                    {
                                        write(STDERR_FILENO, error_message, strlen(error_message));
                                    }
                                    exit(1);
                                }
                                int child23 = fork();
                                if (child13 < 0)
                                {
                                    write(STDERR_FILENO, error_message, strlen(error_message));
                                }
                                else if (child23 == 0)
                                {
                                    if (execv(arg3, getting3))
                                    {
                                        write(STDERR_FILENO, error_message, strlen(error_message));
                                    }
                                    exit(1);
                                }
                                int child33 = fork();
                                if (child13 < 0)
                                {
                                    write(STDERR_FILENO, error_message, strlen(error_message));
                                }
                                else if (child33 == 0)
                                {
                                    if (execv(arg4, getting4))
                                    {
                                        write(STDERR_FILENO, error_message, strlen(error_message));
                                    }
                                }
                                int status;
                                pid_t pid;
                                int n = 3;
                                while (n > 0)
                                {
                                    pid = wait(&status);
                                    //printf("Child with PID %ld exited with status 0x%x.\n", (long)pid, status);
                                    --n; // TODO(pts): Remove pid from the pids array.
                                }
                            }
                        }
                    }
                }
                else
                {
                    token = strtok(command, " \n\t\r");
                    if (token != NULL)
                    {
                        if (strcmp(token, ">") == 0)
                        {
                            write(STDERR_FILENO, error_message, strlen(error_message));
                            break;
                        }
                        //first check if path has any arguments
                        else if (strcmp(token, "path") == 0)
                        {

                            int see = 1;
                            for (i = 0; i < 16 && token != NULL; i++)
                            {

                                token = strtok(NULL, " \t\n\r");
                                if (token != NULL)
                                {
                                    if (see == 1)
                                    {
                                        total_paths = 0;
                                    }
                                    all_paths[i] = token;
                                    total_paths++;
                                    see++;
                                }
                                if (token == NULL && see == 1)
                                {
                                    all_paths[0] = NULL;
                                    final_paths[0] = NULL;
                                    total_paths = 0;
                                }
                            }
                            all_paths[i] = NULL;

                            //Copying the paths into new string array
                            for (i = 0; i < total_paths; i++)
                            {
                                final_paths[i] = all_paths[i];
                            }
                        }
                        //If first token found is & then execute other commands after &
                        else if (strcmp(token, "&") == 0)
                        {
                            break;
                        }

                        //If user presses exit

                        else if (strcmp(token, "exit") == 0)
                        {
                            token = strtok(NULL, " \t\n\r");
                            if (token != NULL)
                            {
                                write(STDERR_FILENO, error_message, strlen(error_message));
                            }
                            else
                            {
                                exit(0);
                            }
                        }

                        //If user presses cd
                        else if (strcmp(token, "cd") == 0)
                        {
                            run_cd(token);
                        }

                        else
                        {

                            //If not a path or a built in command then user checks for whether the command exists in the provided paths

                            for (int r = 0; r < total_paths; r++)
                            {
                                strcpy(path_copy, final_paths[r]);
                                strcat(path_copy, "/");
                                strcat(path_copy, token);

                                if (access(path_copy, X_OK) == 0)
                                {
                                    comeon = path_copy;
                                    break;
                                }
                            }

                            for (i = 0; i < 16 && token != NULL; i++)
                            {
                                char *p;

                                if (token != NULL)
                                {
                                    p = strstr(token, ">");
                                    if (p)
                                    {
                                        char *asd;
                                        doku = 1;
                                        token = strtok(NULL, " \t\n\r");

                                        if (token == NULL)
                                        {
                                            doku++;
                                        }
                                        else
                                        {
                                            strcpy(filename, token);
                                            token = strtok(NULL, " \t\n\r");
                                            char *now;
                                            now = strstr(token, ">");
                                            if (now)
                                            {
                                                write(STDERR_FILENO, error_message, strlen(error_message));
                                                break;
                                            }
                                            if (token != NULL)
                                            {
                                                doku++;
                                            }
                                        }
                                    }
                                    else
                                    {
                                        path[i] = token;
                                        path_position = i + 1;
                                        token = strtok(NULL, " \t\n\r");
                                    }
                                }
                            }
                            path[path_position] = NULL;

                            if (doku == 1)
                            {
                                //Redirection
                                char *with_slash = (char *)malloc(21);
                                strcat(with_slash, "./");
                                strcat(with_slash, filename);
                                execute_function_redir(path, with_slash, comeon);
                            }
                            else if (doku == 0)
                            {
                                if (comeon != NULL)
                                {
                                    execute_function(path, status, child, comeon);
                                }
                                else
                                {
                                    write(STDERR_FILENO, error_message, strlen(error_message));
                                }
                                comeon = NULL;
                            }
                            else
                            {
                                write(STDERR_FILENO, error_message, strlen(error_message));
                                comeon = NULL;
                            }
                        }
                    }
                }
            }
        }
        fclose(file_to_open);
    }
    else
    {
        write(STDERR_FILENO, error_message, strlen(error_message));
        exit(1);
    }

    return 0;
}