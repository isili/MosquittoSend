#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

/*******************************************************************************
                                LINKED LIST

/*    @desc: structure to handle the list of commands
 *    @params:  key --> command name and params
 *              cmd --> argument 1
 *              data --> argument 2

*******************************************************************************/

struct node {
  char *key;
  char *data;
  char *cmd;
  struct node *next;
};

struct node *head = NULL;
struct node *current = NULL;

//display the list
void printList() {
  struct node *ptr = head;
  while (ptr != NULL) {
    printf("%s,%s,%s\n", ptr->key, ptr->cmd, ptr->data);
    ptr = ptr->next;
  }
}

//insert link at the first location
void insertFirst(char *key, char *cmd, char *data) {
  struct node *link = (struct node*) malloc(sizeof(struct node));  //create a link
  link->key = malloc(strlen(key)+1);
  link->cmd = malloc(strlen(cmd)+1);
  link->data = malloc(strlen(data)+1);
  strcpy(link->key,key);
  strcpy(link->cmd,cmd);
  strcpy(link->data,data);
  link->next = head;                                //point it to old first node
  head = link;                                      //point first to new first node
}

//delete first item
struct node* deleteFirst() {
  struct node *tempLink = head;
  head = head->next;                                //mark next to first link as first
  return tempLink;                                  //return the deleted link
}

//is list empty
bool isEmpty() {
   return head == NULL;
}

//return the length of the linked list
int listLength() {
   int length = 0;
   struct node *current;
   for(current = head; current != NULL; current = current->next) {
      length++;
   }
   return length;
}

//get first element
struct node* pop() {
   struct node* current = head;                   //start from the first link
   if(head == NULL) {                             //if list is empty
      return NULL;
   }
   return current;                                //return the current Link (head)
}

void sort() {
   int i, j, k;
   struct node *current;
   struct node *next;
   char *tempKey;
   char *tempData;
   char *tempCmd;
   int size = listLength();
   k = size ;
   for ( i = 0 ; i < size - 1 ; i++, k-- ) {
      current = head;
      next = head->next;
      for ( j = 1 ; j < k ; j++ ) {

          tempData = current->data;
          current->data = next->data;
          next->data = tempData;

          tempKey = current->key;
          current->key = next->key;
          next->key = tempKey;

          tempCmd = current->cmd;
          current->cmd = next->cmd;
          next->cmd = tempCmd;

          current = current->next;
          next = next->next;
      }
   }
}

/*------------------------------------------------------------------------------
                                   UTILS
------------------------------------------------------------------------------*/

#define BUFFER_LENGTH 16384
#define HALF_BUFFER_LENGTH 8192
#define QUARTER_BUFFER_LENGTH 4096
#define SMALL_BUFFER_LENGTH 1024
#define MINI_BUFFER_LENGTH 128

//*********************************************************************************************************
/*    @desc: check presence of prefix and suffix parameters
 *    @params:  prefix -- string of text
 *              suffix -- string of text
 *    @return: false if prefix is initialized and suffix not. false if suffix is initializedand prefix not.
 *             true if prefix and suffix are both inizialized or both not.
 *
**********************************************************************************************************/

bool checkPrefixSuffix(char prefix[HALF_BUFFER_LENGTH], char suffix[HALF_BUFFER_LENGTH]){
    if ( prefix[0] == '\0' && suffix[0] == '\0'){
      return true;
    } else if ( prefix[0] != '\0' && suffix[0] != '\0' ) {
      return true;
    } else {
      return false;
    }
}

//******************************************************************************
/*    @desc: counts occurrencies of a char or string in a string
 *    @params:  prm -- full string of text
 *              sep -- separator string
 *    @return: int numer of occurrencies
 *
*******************************************************************************/

int countParms (char * prm, char * sep) {
  int count = 0;
  const char *tmp = prm;
  while(tmp = strstr(tmp, sep))
  {
     count++;
     tmp++;
  }
  return count;
}

//*********************************************************************************************************************************************
/*    @desc: add a command to the commands list.
 *    @params:  incommand -- name of the command, it can provide his own params separated by commas. example {commandname,param1,param2}
 *              filename  -- location of the command list text file on  your computer.

**********************************************************************************************************************************************/

void addCmdToList(char *incommand, char *filename, char arg_firstpar[MINI_BUFFER_LENGTH], char prefix[MINI_BUFFER_LENGTH], char suffix[MINI_BUFFER_LENGTH]){
    FILE * fp = fopen(filename, "r");
    if (fp == NULL) {
      printf("can't open file\n");
      exit(-1);
    }

    char line[BUFFER_LENGTH], *tl, *tok, *partok, seps[] = "\t";
    char command[BUFFER_LENGTH] = "";
    char firstpar[QUARTER_BUFFER_LENGTH] = "";
    char temp_firstpar[QUARTER_BUFFER_LENGTH] = "";
    char scndpar[HALF_BUFFER_LENGTH] = "";
    char temp_scndpar[HALF_BUFFER_LENGTH] = "";
    char dest_scndpar[HALF_BUFFER_LENGTH] = "";
    char default_scndpar[MINI_BUFFER_LENGTH] = "";
    char * incommand_aux = malloc(strlen(incommand)+1);
    char pref_aux[MINI_BUFFER_LENGTH] = "";
    char suff_aux[MINI_BUFFER_LENGTH] = "";
    int j = 1;
    ( prefix[0] == '\0') ? (strncpy(pref_aux,"data", MINI_BUFFER_LENGTH)) : (strncpy(pref_aux, prefix, MINI_BUFFER_LENGTH));
    ( suffix[0] == '\0') ? (strncpy(suff_aux,"timestamp", MINI_BUFFER_LENGTH)) : (strncpy(suff_aux, suffix, MINI_BUFFER_LENGTH));
    sprintf(default_scndpar, "{\"%s\":{%s}, \"%s\":\"20170623105756\"}", pref_aux, "%s", suff_aux);
    while ( (fgets(line,BUFFER_LENGTH,fp)) != NULL){
      if(line[0] == '#'){continue;}
      if(line[strlen(line)-1] == '\n'){
        line[strlen(line)-1] = '\0';
      }
      strcpy(incommand_aux, incommand);
      sscanf(line, "%s", command);
      if (strncmp(incommand, command, strlen(command)) == 0 && strlen(command) == strlen(strtok(incommand_aux, ","))){
        for (tl = strtok (line, seps); tl; tl = strtok (NULL,seps)){
            if (j == 1) {strncpy(command, tl, QUARTER_BUFFER_LENGTH);}
            if (j == 2) {strncpy(firstpar, tl, QUARTER_BUFFER_LENGTH);}
            if (j == 3) {strncpy(scndpar, tl, HALF_BUFFER_LENGTH);}
            j++;
        }
        if (strstr(firstpar, "%s")){
          strncpy(temp_firstpar, firstpar, QUARTER_BUFFER_LENGTH);
          sprintf(firstpar, temp_firstpar, arg_firstpar);
        }

        if (scndpar[0] == '\0'){
          sprintf(scndpar, default_scndpar, "");
        } else {
          sprintf(temp_scndpar, default_scndpar, scndpar);
          strncpy(scndpar, temp_scndpar, HALF_BUFFER_LENGTH);
        }

        int i,cp = 1;
        int numPrmsIncommand = 0;
        int numPrmsscndpar = 0;
        numPrmsIncommand = countParms(incommand, ",");
        numPrmsscndpar = countParms(scndpar , "%s");
        if (countParms(incommand, ",") != countParms(scndpar , "%s")){
            printf("Wrong number of params on command: %s\n", strtok(incommand, ","));
            printf("needed: %d - given: %d\n", numPrmsscndpar, numPrmsIncommand);
            fclose(fp);
            exit(-1);
        }else{
          if (strstr(incommand, ",") != NULL ) {
            int c = 0;
            partok = strtok(incommand, ",");
            partok = strtok(NULL, ",");

            for (i = 0; i <= strlen(scndpar); i++) {
              if (scndpar[i] != '\%'){
                dest_scndpar[c] = scndpar[i];
                c++;
              } else {
                if ((scndpar[i] == '\%') && (scndpar[i+1] == 's')){
                  strcat(dest_scndpar, partok);
                  c = c + strlen(partok);
                  partok = strtok(NULL, ",");
                  i++;
                } else {
                  dest_scndpar[c] = scndpar[i];
                  c++;
                }
              }
            }
            strncpy(scndpar, dest_scndpar, HALF_BUFFER_LENGTH);
          }
        }
        insertFirst(command, firstpar, scndpar);
        pref_aux[0] = '\0';
        suff_aux[0] = '\0';
        fclose(fp);
        return;
      }
    }
    free(incommand_aux);
    printf("Can't find: %s\n", incommand);
    fclose(fp);
    exit(-1);
}

//******************************************************************************
//    @desc: show help on screen (opt -?)

//******************************************************************************

void printHelp() {
  printf("____________________________________________________________________________________________________\n");
  printf("-- The program sends mosquitto commands along with data stored in a tab-delimited command file --\n");
  printf("Use: mosquitto_send [ARGUMENTS]\n");
  printf("  -f FILENAME       : change filename to FILENAME\n");
  printf("  -c COMMAND NAME   : search and execute given command/s\n");
  printf("  -s SLEEPTIME      : set given sleeptime between commands, default 0\n");
  printf("  -h HOST           : change default host mosquitto server to HOST\n");
  printf("  -i ID             : device ID, default 0, set it before a command to modify all the following commands\n" );
  printf("  -a PREFIX         : set the prefix parameter, dependency (-b), set it before a command to modify all the following commands \n");
  printf("  -b SUFFIX         : set the suffix parameter, dependency (-a), set it before a command to modify all the following commands \n");
  printf("  -d                : debug mode\n");
  printf("  -m                : show help\n");
  printf("____________________________________________________________________________________________________\n");
  exit(0);
}

//*********************************************************************************************************
/*    @desc: check if the provided sleeptime is positive value, if not set 0. Then it prints out on screen.
 *    @params:  int sleeptime (opt -s)

**********************************************************************************************************/

int checkSleepTime(int sleeptime) {
  if (sleeptime < 0 ){
    sleeptime = 0;
  }
  printf("sleeptime -->: %d\n", sleeptime);
  return sleeptime;
}

/*------------------------------------------------------------------------------
                                    MAIN
------------------------------------------------------------------------------*/

int main(int argc, char **argv){
  char * filename = "mqtt_commands.txt";
  char * optcmd = NULL;
  char arg_firstpar[MINI_BUFFER_LENGTH] = "0";
  char incmd[BUFFER_LENGTH] = "";
  char strcmd[BUFFER_LENGTH];
  char prefix[HALF_BUFFER_LENGTH] = "";
  char suffix[HALF_BUFFER_LENGTH] = "";
  int sleeptime = 0;
  int opt;
  int length = 0;
  int r;
  bool debug = false;
  bool presuffix = true;

  while ((opt = getopt(argc,argv,"?mdf:c:s:h:i:a:b:")) != -1) {
    switch(opt) {
      case '?':
            printHelp();
          break;
      case 'm':
            printHelp();
          break;
      case 'f':
            filename = malloc(strlen(optarg)+1);
            strcpy (filename, optarg);
            printf("filename: %s\n", filename);
          break;
      case 'c':
            strncpy (incmd, optarg, BUFFER_LENGTH);
            addCmdToList(incmd,filename,arg_firstpar,prefix,suffix);
          break;
      case 's':
            sleeptime = atoi(optarg);
          break;
      case 'h':
            optcmd = malloc(strlen(optarg)+1);
            strcpy(optcmd, optarg);
          break;
      case 'd':
            debug = true;
          break;
      case 'i':
            strncpy (arg_firstpar, optarg, MINI_BUFFER_LENGTH);
          break;
      case 'a':
            strncpy (prefix, optarg, HALF_BUFFER_LENGTH);
          break;
      case 'b':
            strncpy (suffix, optarg, HALF_BUFFER_LENGTH);
          break;
      default:
      printHelp();
          break;
    }
  }

  if ( checkPrefixSuffix(prefix, suffix) != presuffix) {
    printf("a and b params must be both set or unset\n");
    exit(-1);
  }
  checkSleepTime(sleeptime);
  sort();
  length = listLength();

  while (length > 0) {
    struct node *thisNode = pop();
    if (optcmd){

      printf("mosquitto_pub -h '%s' -t '%s' -m '%s'\n", optcmd, thisNode->cmd, thisNode->data );
      if (!debug) {
        sprintf(strcmd, "mosquitto_pub -h '%s' -t '%s' -m '%s'", optcmd, thisNode->cmd, thisNode->data);
        r = system(strcmd);
        if (r != EXIT_SUCCESS) {
          printf("command has failed with code %d\n", WEXITSTATUS(r));
          exit(r);
        }
      }
    }
    else{
      printf("mosquitto_pub -t '%s' -m '%s'\n", thisNode->cmd, thisNode->data);
      if(!debug){
        sprintf(strcmd, "mosquitto_pub -t '%s' -m '%s'", thisNode->cmd, thisNode->data);
        r = system(strcmd);
        if (r != EXIT_SUCCESS) {
          printf("command has failed with code %d\n", WEXITSTATUS(r));
          exit(r);
        }
      }
    }
    deleteFirst();
    if (sleeptime != 0) {
      if (!isEmpty()) {
        printf("-- sleep %d seconds --\n", sleeptime);
        sleep(sleeptime);
      }
    }
    length--;
  }

  return 0;
  }
