#include <stdio.h> //fflush, perror, fprintf, fopen, fgetc, fputc, fclose
#include <string.h> //strcpy,strtok,strsep,strcmp
#include <stdlib.h> //system, srand
#include <unistd.h> //fork,pipe,exec,usleep, getcwd, gethostname, close , dup2
#include <sys/types.h> //waitpid
#include <sys/wait.h>//waitpid
#include <readline/readline.h> //readline
#include <readline/history.h> //add_history
#include <sys/sysinfo.h> //sysinfo
#include <signal.h> // for SIGINT
#include <errno.h> //for specific errors
/*#include <time.h> 
#include <strings.h>
*/
#define MAX_INPUT 200
#define MAX_ARG 10

char* BuiltInCmd[8] = {"cd", "exit", "help", "cp", "history", "fortune", "free", "forkbomb"};

 //variables for history
static const char *historyCmd[100];
int count = 0;

//colors
void white(){
    printf("\033[1;37m");
}
void blue(){
    printf("\033[1;34m");
}
void red(){
    printf("\033[1;31m");
}
void green(){
    printf("\033[1;32m");
}
void purple(){
    printf("\033[1;35m");
}
void yellow(){
    printf("\033[1;33m");
}

int main();
int  handle_cmd(char* input, char** cmd,char** pipeCmd); //handles the input/command, it will check what type of command it is and return the flag based on it
void parse_input(char *input, char **commands); //it just parses the input into tokens
int splitPipe(char* str, char** strpiped); // splits the two commands for pipe, returns 0 if not pipe
int input_loop(char* str); //main loop where we input 
int BuiltIn(char** cmd); //function that handles our Built-In functions
void executePipeCmd(char** cmd, char** pipeCmd); //executes the pipe
void executeExternalCmd(char** cmd); //executes programs with fork() that are not Built-In 
void help(); //help
void forkBomb_cmd(); // Built-In forkbomb
void cp_cmd(char** cmd); // Built-In copy 
void history_cmd(char** cmd); //Built-In history
void fortune_cmd(char** cmd); //Built-In fortune
void free_cmd(char** cmd); //Built-In free
void printIntro(); // Prints intro on start

int main()
{
    char input[MAX_INPUT];
    char *parsedCmd[MAX_ARG];  //in case of pipe, this is the first program
    char *parsedPipeCmd[MAX_ARG]; // and this is the second
    int cmdType;
    printf("\033]0;DarkShell\007"); //name of shell
    printIntro();
    while(1)
    {
       if( input_loop(input)){
	    continue;
       }
        cmdType = handle_cmd(input, parsedCmd,parsedPipeCmd);

        if(cmdType == 1){
	     executeExternalCmd(parsedCmd);
	    }
        else if(cmdType == 2){
            executePipeCmd(parsedCmd,parsedPipeCmd);
        }
    }
    return 0;
}

void printIntro(){
int i;
for (i = 0; i <= 100; i++) {
    printf("Loading: [%-20s] %3d%%\r", "====================", i);
    fflush(stdout);
    usleep(20000);

}
printf("\n");

system("clear"); //clear screen

char* user = getenv("USER");
red();
printf("        @@@@@@@@@@@@@@@@@@\n");
printf("      @@@@@@@@@@@@@@@@@@@@@@@\n");
printf("    @@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
printf("   @@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
printf("  @@@@@@@@@@@@@@@/      \\@@@/   @\n");
printf(" @@@@@@@@@@@@@@@@\\      @@  @___@\n");
printf(" @@@@@@@@@@@@@ @@@@@@@@@@  | \\@@@@@\n");
printf(" @@@@@@@@@@@@@ @@@@@@@@@\\__@_/@@@@@\n");
printf("  @@@@@@@@@@@@@@@/,/,/./'/_|.\'\\,\\ \n");
printf("   @@@@@@@@@@@@@|  | | | | | | | | \n");
printf("                  \\_|_|_|_|_|_|_|_|         Welcome %s \n",user);

}

int input_loop(char* input){
    char cwd[1024];
    
    //char *getcwd(char *buf, size_t size);
    getcwd(cwd, sizeof(cwd));
    
    char* stringInput;
    char* user = getenv("USER");
    char machineName[1024];

    //int gethostname(char *name, size_t len);
    gethostname(machineName,1024);

    green();
    printf("%s",user);
    printf("@");
    printf("%s",machineName);
    white();
    printf(":");
    blue();
    printf("%s~", cwd);
    white();

    //readline (const char *prompt);
    stringInput = readline("$ ");
    if (strlen(stringInput) != 0) {
        historyCmd[count]=stringInput;
        add_history(stringInput); // user can use arrows for commands
        count++;

        //char *strcpy(char *dest, const char *src);
        strcpy(input, stringInput);
        return 0;
    } else {
        return 1;
    }
}

int  handle_cmd(char* input, char** cmd,char** pipeCmd){
char* pipestr[2];
int pipe = splitPipe(input, pipestr);
 
if(pipe){       
    parse_input(pipestr[0], cmd);
    parse_input(pipestr[1], pipeCmd);
}else{
  //here goes input that is not pipe
  parse_input(input, cmd);
  
}
if(BuiltIn(cmd)){
return 0;
} else {
return 1+pipe;
}
}

void parse_input(char *input, char **commands) {
    char *token = strtok(input, " ");
    int i = 0;
    while (token != NULL && i < MAX_ARG) {
        commands[i] = token;
        i++;
        token = strtok(NULL, " ");
    }
    commands[i] = NULL;
}
 
int splitPipe(char* input, char** pipe)
{
    int i;
    for (i = 0; i < 2; i++) {
        pipe[i] = strsep(&input, "|");
        if (pipe[i] == NULL) {
            break;
          }
    }
    if (pipe[1] == NULL) {
        // if not pipe
        return 0; 
     }
    else {
        return 1;
    }
}

void executeExternalCmd(char** cmd){
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return;
    } else if (pid == 0) {
        //child
        execvp(cmd[0], cmd);
        perror(cmd[0]);
        exit(1);
    } else {
        //parent
        int status;
        pid_t wpid = waitpid(pid, &status, 0);
        if (wpid == -1) {
            perror("waitpid");
            exit(EXIT_FAILURE);
        }
    }
}


void executePipeCmd(char** cmd, char** pipeCmd){
    int pipefd[2]; 
    pid_t pid1, pid2;
 
    if (pipe(pipefd) < 0) {
        perror("pipe");
        return;
    }
    pid1 = fork();
    if (pid1 < 0) {
        perror("fork");
        return;
    }
 
    if (pid1 == 0) {
        // Child 1
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO); //The dup2() duplicates file descr
        close(pipefd[1]);
 
        if (execvp(cmd[0], cmd) < 0) {
            perror(cmd[0]);
            exit(0);
        }
 
    } else {
        // Parent
        pid2 = fork();
 
        if (pid2 < 0) {
            perror("fork");
            return;
        }
 
        if (pid2 == 0) {
            // Child 2
            close(pipefd[1]);
            dup2(pipefd[0], STDIN_FILENO);
            close(pipefd[0]);
            if (execvp(pipeCmd[0], pipeCmd) < 0) {
                perror(pipeCmd[0]);
                exit(0);
            }
 
        } else {
            // parent
            close(pipefd[0]);
            close(pipefd[1]);
            waitpid(pid1, NULL, 0);
            waitpid(pid2, NULL, 0);
        }
 
    }
}


int BuiltIn(char** cmd){
    int cmdNum;
    
    for (int i = 0; i < 8; i++) {
        if (strcmp(cmd[0], BuiltInCmd[i]) == 0) {
            cmdNum=i+1;
            break;
        }
    }
 
    switch (cmdNum) {
    case 1:
        chdir(cmd[1]);
        return 1;
    case 2:
        exit(0);
    case 3:
        help();
        return 1;
    case 4:
        cp_cmd(cmd);
        return 1;
    case 5:
        history_cmd(cmd);
        return 1;
    case 6:
        fortune_cmd(cmd);
        return 1;
    case 7:
	    free_cmd(cmd);
	    return 1;
    case 8:
        forkBomb_cmd();
        return 1;
    default:
        break;
    }
 
    return 0;
}

void free_cmd(char** cmd){
double byteType;
struct sysinfo si;
sysinfo (&si);
green();


if(cmd[1] == NULL || strcmp(cmd[1],"-b") == 0){
    byteType=1;
}else if(strcmp(cmd[1], "-m") == 0){
    byteType=1024*1024;
} else if(strcmp(cmd[1], "-g") == 0){
    byteType=1024 * 1024 * 1024;
} else {
    perror("free");
}
printf("%-20s %10s %10s %10s %10s %10s\n", "", "total", "used", "free", "shared", "buff/cache");
printf("%-20s %10.1f %10.1f %10.1f %10.1f %10.1f\n", "Mem:", si.totalram / byteType, (si.totalram - si.freeram) / byteType, si.freeram / byteType, si.sharedram / byteType, si.bufferram / byteType);
printf("%-20s %10.1f %10s %10.1f %10s %10s\n", "Swap:", si.totalswap / byteType, "-", si.freeswap / byteType, "-", "-");

white();
return;
}
 
void fortune_cmd(char** cmd) {
    purple();
    const char* fortunes[] = {
        "I'm not paranoid, they're really after me.",
        "Eyes everywhere! Always watching!",
        "BE EXCELLENT TO EACH OTHER",
        "ERMAHGERD",
        "FIRST!",
        "AINT NOBODY GOT TIME FOR DAT",
        "NEVER GONNA GIVE YOU UP...",
        "WOW TERMINAL SUCH HACKER WOW",
        "MAGNETS. HOW DO THEY WORK?",
        "ITS A TRAP!",
        "COOL STORY, BRO",
        "TROLOLOLO LOLOLOLO",
        "REDRUM",
        "ITS OVER 9000!!!",
        "Where we're going, we don't need guns."
    };
    const int num_fortunes = sizeof(fortunes) / sizeof(fortunes[0]);

    srand(time(NULL));

    if (cmd[1] == NULL) {
        // Print a random fortune
        const int random_index = rand() % num_fortunes;
        printf("%s\n", fortunes[random_index]);
    }
    else if (strcmp(cmd[1], "-a") == 0) {
        // Print all fortunes
        for (int i = 0; i < num_fortunes; i++) {
            printf("%s\n", fortunes[i]);
        }
    }
    else {
        // Invalid option
        fprintf(stderr, "Invalid option: %s\n", cmd[1]);
        fprintf(stderr, "Usage: fortune [-a]\n");
        return;
    }
}

void history_cmd(char** cmd)
{
    yellow();
    if (cmd[1] == NULL){
	for(int i = 0; i < count; i++){
	    printf("%s\n", historyCmd[i]);
        }
    }
//-r option
    else if(strcmp(cmd[1], "-r") == 0){
	for (int j=count-1; j >=0; j--) {
	    printf("%s\n",historyCmd[j]);
	}
    }

    
//handles invalid command
    else{
	perror("history");
    }
}

void cp_cmd(char** cmd)
{
   FILE *src, *dest;
   src = fopen(cmd[1], "r");
   dest = fopen(cmd[2], "w");
   char contents = fgetc(src);
   while (contents != EOF){
      fputc(contents, dest);
      contents = fgetc(src);
   }
   fclose(src);
   fclose(dest);
}
 

void forkBomb_cmd(){
    while(1)
        fork();
    return;
}
 


void help()
{
    blue();
    printf("Commands:\n");
    printf(">ls\n");
    printf(">cd\n");
    printf(">cp\n");
    printf(">history [-r]\n");
    printf(">fortune [-a]\n");
    printf(">free [-b/-m/-g]\n");
    printf(">forkbomb(CAUTION)\n");
    printf(">exit\n");
    white();
    return;
}
