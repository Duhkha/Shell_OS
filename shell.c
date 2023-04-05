#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <time.h>
#include <sys/sysinfo.h>
 

char* BuiltInCmd[8] = {"cd", "exit", "help", "cp", "history", "fortune", "free", "forkbomb"};

 //variables for history
static const char *historyCmd[100];
int count = 0;
 //colors
void white(){
    printf("\033[1;37m");
}
 
void purple(){
    printf("\033[1;35m");
}
 
void cyan(){
    printf("\033[1;36m");
}
 
void green(){
    printf("\033[1;32m");
}
 
void yellow(){
    printf("\033[1;33m");
}
 
void blue(){
    printf("\033[1;34m");
}
 
void red(){
    printf("\033[1;31m");
}

//free command
void freeCmd(char** cmd){
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

printf("Total RAM:  %5.1f \n", si.totalram / byteType);
printf("Free RAM: %5.1f \n", si.freeram / byteType);
printf("Used RAM: %5.1f \n", (si.totalram- si.freeram) / byteType);
printf("Shared RAM: %5.1f \n", si.sharedram / byteType);
printf("Buffered RAM: %5.1f \n", si.bufferram / byteType);
printf("Total swap space size : %5.1f \n", si.totalswap / byteType);
printf("Total available swap space : %5.1f \n", si.freeswap / byteType);
printf("Total used swap space : %5.1f \n", (si.totalswap - si.freeswap) / byteType);

white();
return;
}
 
//fortune command 
 
void fortune(char** cmd){
    red();
    srand(time(NULL));
    int arrayLen = 15;
    char fortuneArray[arrayLen][100];
 
    strcpy(fortuneArray[0], "I'm not paranoid, they're really after me.");
    strcpy(fortuneArray[1], "Eyes everywhere! Always watching!"); 
    strcpy(fortuneArray[2], "BE EXCELLENT TO EACH OTHER");
    strcpy(fortuneArray[3], "ERMAHGERD");
    strcpy(fortuneArray[4], "FIRST!");
    strcpy(fortuneArray[5], "AINT NOBODY GOT TIME FOR DAT");
    strcpy(fortuneArray[6], "NEVER GONNA GIVE YOU UP...");
    strcpy(fortuneArray[7], "WOW TERMINAL SUCH HACKER WOW");
    strcpy(fortuneArray[8], "MAGNETS. HOW DO THEY WORK?");
    strcpy(fortuneArray[9], "ITS A TRAP!");
    strcpy(fortuneArray[10], "COOL STORY, BRO");
    strcpy(fortuneArray[11], "TROLOLOLO LOLOLOLO");
    strcpy(fortuneArray[12], "REDRUM");
    strcpy(fortuneArray[13], "ITS OVER 9000!!!");
    strcpy(fortuneArray[14], "Where we're going, we don't need guns.");
 
//prints one random quote from fortune array
if(cmd[1] == NULL){
    int random = rand() % 14;
    for(int i = 0; i < arrayLen; i++){
	if(i + 1 == random){
	    printf("%s\n", fortuneArray[i]);
	    }
        }
    } //custom -all option that prints the whole fortune array
else if(strcmp(cmd[1], "*") == 0){
    for(int j = 0; j < arrayLen; j++){
        printf("%s\n", fortuneArray[j]);
        }
    }
//handles invalid commands
else{
    perror("fortune");
    }
    white();
    return;
}
 
//history command
void history(char** cmd)
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
 
//prints intro when the shell starts
void printIntro(){
printf("\033[H\033[J"); //command to clear screen

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
 
//cp command 
void cp(char** cmd)
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
 
//implementation of forkbomb as a command
void forkBomb(){
    while(1)
        fork();
    return;
}
 
//help command
 
void help()
{
    blue();
    printf("Commands:\n");
    printf(">ls\n");
    printf(">cd\n");
    printf(">cp\n");
    printf(">history [-r]\n");
    printf(">fortune [*]\n");
    printf(">free [-b /-g ]\n");
    printf(">forkbomb(CAUTION)\n");
    printf(">exit\n");
    white();
    return;
}
 
//execute system commands using forks
void executeSysCmd(char** cmd)
{
    pid_t pid = fork();
 
    if (pid < 0) {
        perror("fork");
        return;
    } else if (pid == 0) {
	execvp(cmd[0], cmd);
        if (execvp(cmd[0], cmd) < 0) {
            perror(cmd[0]);
        }
        exit(0);
    } else {
        wait(NULL);
        return;
    }
}
 
//execute pipe commands using forks
void executePipeCmd(char** cmd, char** pipeCmd)
{
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
 
      }
	else {
        // Parent
        pid2 = fork();
 
        if (pid2 < 0) {
            perror("fork");
            return;
        }
 
        // Child 2
        if (pid2 == 0) {
            close(pipefd[1]);
            dup2(pipefd[0], STDIN_FILENO);// dup2() dupilcates
            close(pipefd[0]);
            if (execvp(pipeCmd[0], pipeCmd) < 0) {
                perror(pipeCmd[0]);
                exit(0);
            }
 
        } else {
            // parent
            wait(NULL);
            wait(NULL);
            //waitpid
        }
 
    }
}
 
//function to handle built-in commands 
int BuiltIn(char** cmd)
{
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
        cp(cmd);
        return 1;
    case 5:
        history(cmd);
        return 1;
    case 6:
        fortune(cmd);
        return 1;
    case 7:
	    freeCmd(cmd);
	    return 1;
    case 8:
        forkBomb();
        return 1;
    default:
        break;
    }
 
    return 0;
}
 


 


//read username and machinename and handle input of commands
int cmdInput(char* str)
{
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    //printf("\n %s ", cwd);
    char* stringInput;
    char* user = getenv("USER");
    char machineName[1024];
    gethostname(machineName,1024);
    
    printf( "/n ");//?
    green();
    printf("%s",user);
    printf("@");
    printf("%s",machineName);
    white();
    printf(":");
    blue();
    printf("%s~", cwd);
    white();
    stringInput = readline("$ ");
    if (strlen(stringInput) != 0) {
        historyCmd[count]=stringInput;
        count++;
        strcpy(str, stringInput);
        return 0;
    } else {
        return 1;
    }
}

//parse pipe commands
int parsePipe(char* str, char** strpiped)
{
    int i;
    for (i = 0; i < 2; i++) {
        strpiped[i] = strsep(&str, "|");
        if (strpiped[i] == NULL) {
            break;
          }
    }
    if (strpiped[1] == NULL) {
        return 0; // no pipe is found.
     }
    else {
        return 1;
    }
}

//parse command and check if pipe or not in order to correctly execute
int  parse_input(char* input, char** cmd,char** pipeCmd){
char* pipestr[2];
int pipe = parsePipe(input, pipestr);
 
//handle command that includes piping
if(pipe){

        
        char *p1 = strtok(pipestr[0], " ");
        int i = 0;
        while (p1 != NULL && i < 100) {
        cmd[i] = p1;
        i++;
        p1 = strtok(NULL, " ");
    }
        cmd[i] = NULL;

        char *p2 = strtok(pipestr[1], " ");
        i = 0;
        while (p2 != NULL && i < 100) {
        pipeCmd[i] = p2;
        i++;
        p2 = strtok(NULL, " ");
    }
        pipeCmd[i] = NULL;

//handle command that does not include piping
}else{
    char* token = strtok(input, " ");
    int i = 0;
    while (token != NULL && i < 100) {
    cmd[i] = token;
    i++;
    token = strtok(NULL, " ");
}
cmd[i] = NULL;


}//return flags
    if(BuiltIn(cmd)){
	return 0;
    } else {
	return 1+pipe;
    }
}

int main()
{
    char input[1000];
    char *parsedCmd[100];
    char *parsedPipeCmd[100];
    int cmdType;
    printIntro();


    while(1)
    {
        
 
        if(cmdInput(input)){
	    continue;
        }
        cmdType = parse_input(input, parsedCmd,parsedPipeCmd);
 
        //handle flags for system and piping commands
        if(cmdType == 1){
	     executeSysCmd(parsedCmd);
	}
        if(cmdType == 2){
            executePipeCmd(parsedCmd,parsedPipeCmd);
 
        }
    }
    return 0;
}