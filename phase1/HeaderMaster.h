#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <errno.h>

#define MX_str 1000*1000 + 10
#define MX_CMD 5000 + 10
#define BACK_UP "root/.BACK_UP"

char input_str[3][MX_CMD] ,input_pos[3][MX_CMD] , input_file[100][MX_CMD] , input_opt[5][MX_CMD] , input_kind[MX_CMD] , input_unknown[3][MX_CMD] ,input_arman[100][MX_CMD] ;
int input_opt_size[3]; 
int cnt_input_str , cnt_input_file , cnt_input_opt , cnt_unknown , is_arman  , cnt_arman , cnt_input_pos , cnt_input_opt_size , cnt_grep; 
const int inf = 1000*1000*1000 + 10 ; 
const long long mod = 1000*1000*1000 + 7 ; 

int File_exist(char *) ; 
int Dir_exist(char *) ; 
void clear_input() ; 
void main_input( char *) ; 
char * substr(int  , int  ,char *) ; 
void dir_dfs(char * , char * , int) ; 
long long poww(long long , long long ) ; 
long long HASH_file_name(char *) ; 

void createfile(); 
void cat() ; 
void tree() ;
void insertstr() ;  
void undo() ; 
void removestr() ; 
void copystr() ; 
void cutstr() ; 
void pastestr() ; 
void compare() ; 
void find() ; 
void replace() ; 
void grep() ; 
void auto_indent() ; 

struct DY_str
{
    char * str ; 
    int size ; 
    int pos ; 
};
struct DY_str * init_DY_str () ; 
struct DY_str * change_size(struct DY_str*) ; 
struct DY_str * last_output , * output , * str_in , * clip_board ; 

void file_to_str(char * , struct DY_str *) ; 
void saving_output() ; 
void file_to_str_L_R(int , int , char * , struct DY_str *) ; 
void copy_file_file(char * , char *) ; 
void Back_up(char *) ; 
int find_pos_by_line(int , int , char *) ; 
void str_to_file(char * , char *) ; 
int min(int , int) ; 
int max(int , int) ; 
int counter_word(int  , char * ) ; 
int counter_line (int  , char *) ; 
char * file_line (int , char *) ; 
