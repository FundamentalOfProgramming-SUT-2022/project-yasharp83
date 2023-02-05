#include "HeaderMaster.h"


////////sec funcs
int File_exist(char * path){
    FILE * my_file = fopen(path , "r") ; 
    if (my_file==NULL)
        return 1 ; 
    return 0 ; 
}

int Dir_exist(char * path){
    if (mkdir(path , 0700)==-1)
        return 0 ; 
    return 1 ; 
}

void clear_input(){
    for (int i = 0 ; i < cnt_input_file ; i++){
        strcpy(input_file[i] , "\0") ; 
    }
    for (int i = 0 ; i < cnt_input_opt ; i++){
        strcpy(input_opt[i] , "\0") ; 
    }
    for (int i = 0 ; i < cnt_input_opt_size ; i++){
        input_opt_size[i] = 0 ; 
    }
    for (int i = 0 ; i < cnt_input_pos ; i++){
        strcpy(input_pos[i] , "\0") ; 
    }
    for (int i = 0 ; i < cnt_input_str ; i++){
        strcpy(input_str[i] , "\0") ; 
    }
    for (int i = 0 ; i < cnt_unknown ; i++){
        strcpy(input_unknown[i] , "\0") ; 
    }
    strcpy(input_kind , "\0") ; 
    cnt_input_file = 0 ; 
    cnt_input_opt = 0 ; 
    cnt_input_str = 0 ; 
    cnt_unknown = 0 ;
    cnt_input_pos = 0 ; 
    cnt_input_opt_size = 0 ;  
}

void input_debugger(){
    printf("kind : %s\n" , input_kind) ; 
    for (int i = 0 ; i < cnt_input_file ; i++){
        printf("file %d : %s\n" , i , input_file[i]) ; 
    }
    for (int i = 0 ; i < cnt_input_str ; i++){
        printf("str %d : %s\n" , i , input_str[i]) ; 
    }
    return ; 
}

void main_input(char command[]){
    char *cur_str_ptr = strtok(command , " ");
    if (cur_str_ptr==NULL)
        return ; 
    strcpy(input_kind , cur_str_ptr); 
    while(1){
        cur_str_ptr = strtok(NULL , " ") ; 
        if (cur_str_ptr==NULL)
            return ; 
        if (cur_str_ptr[0]=='-' && cur_str_ptr[1]=='-'){
            if (strcmp(cur_str_ptr , "--file")==0){
                cur_str_ptr = strtok(NULL , " ") ; 
                if (cur_str_ptr==NULL)
                    return ; 
                if (cur_str_ptr[0]=='\"') {
                    while(1){  
                        strcat(input_file[cnt_input_file] , cur_str_ptr) ; 
                        if (cur_str_ptr[strlen(cur_str_ptr)-1]=='\"' && cur_str_ptr[strlen(cur_str_ptr)-2]!='\\')
                            break ; 
                        strcat(input_file[cnt_input_file] , " ") ; 
                        cur_str_ptr = strtok(NULL , " ");
                    }
                }
                else {
                    strcpy(input_file[cnt_input_file] , cur_str_ptr) ; 
                }
                cnt_input_file++ ; 
            }
            else if (strcmp(cur_str_ptr , "--str")==0 ||strcmp(cur_str_ptr , "--str1")==0 ||strcmp(cur_str_ptr , "--str2")==0){
                cur_str_ptr =  strtok(NULL , " ") ; 
                if (cur_str_ptr==NULL)
                    return ; 
                if (cur_str_ptr[0]=='\"') {
                    while(1){
                        strcat(input_str[cnt_input_str] , cur_str_ptr) ; 
                        if (cur_str_ptr[strlen(cur_str_ptr)-1]=='\"' && cur_str_ptr[strlen(cur_str_ptr)-2]!='\\')
                            break ; 
                        strcat(input_str[cnt_input_str] , " ") ; 
                        cur_str_ptr =  strtok(NULL , " ") ; 
                    }
                }
                else {
                    strcpy(input_str[cnt_input_str] , cur_str_ptr) ; 
                }
                cnt_input_str++; 
            }
            else if (strcmp(cur_str_ptr , "--pos")==0){
                cur_str_ptr = strtok(NULL , " ") ; 
                if (cur_str_ptr==NULL)
                    return ; 
                strcpy(input_pos[cnt_input_pos] , cur_str_ptr) ; 
                cnt_input_pos++ ; 
            }
            else if (strcmp(cur_str_ptr , "--files")==0){
                while(1){
                    cur_str_ptr = strtok(NULL , " ") ; 
                    if (cur_str_ptr==NULL)
                        return ; 
                    if (cur_str_ptr==NULL)
                        return ; 
                    if (cur_str_ptr[0]=='\"') {
                        while(1){  
                            strcat(input_file[cnt_input_file] , cur_str_ptr) ; 
                            if (cur_str_ptr[strlen(cur_str_ptr)-1]=='\"' && cur_str_ptr[strlen(cur_str_ptr)-2]!='\\')
                                break ; 
                            strcat(input_file[cnt_input_file] , " ") ; 
                            cur_str_ptr = strtok(NULL , " ");
                        }
                    }
                    else {
                        strcpy(input_file[cnt_input_file] , cur_str_ptr) ; 
                    }
                    cnt_input_file++ ; 
                }
            }
        }
        else if (cur_str_ptr[0]=='-' && !(cur_str_ptr[1]-'0' < 10 && cur_str_ptr[1]-'0' >= 0)){
            if (strcmp(cur_str_ptr , "-size")==0){
                cur_str_ptr = strtok(NULL , " ") ; 
                if (cur_str_ptr==NULL)
                    return ; 
                input_opt_size[cnt_input_opt_size] = atoi(cur_str_ptr) ; 
                cnt_input_opt_size++ ; 
            }
            else {
                strcpy(input_opt[cnt_input_opt] , cur_str_ptr) ; 
                cnt_input_opt++ ; 
            }
        }
        else {
            strcpy(input_unknown[cnt_unknown] , cur_str_ptr) ; 
            cnt_unknown++ ; 
        }
    }
}

struct DY_str * init_DY_str (){
    struct DY_str * now = (struct DY_str *) malloc(sizeof(struct DY_str)) ; 
    now->size = MX_CMD ; 
    now->str = (char *) calloc(1 , now->size) ; 
    now->pos = 0 ; 
    return now ; 
}

struct DY_str * change_size(struct DY_str * A){
    A->size = A->size*2 ; 
    A->str = realloc(A->str , A->size) ; 
}

char * substr(int l , int r ,char * A ) {
    char * now = (char *)calloc(1 , MX_CMD) ; 
    for (int i = l ; i <= r ; i++)
        now[i-l] = A[i] ; 
    return now ; 
}

void file_to_str(char * path, struct DY_str * DY ){
    FILE * now_file = fopen(path , "r") ; 
    char A[MX_CMD] ; 
    while(fgets(A , MX_CMD , now_file)!=NULL){
        while ((strlen(A) + DY->pos )*2 >= DY->size)
            change_size(DY) ; 
        DY->pos = DY->pos + strlen(A) ; 
        strcat(DY->str , A) ; 
    }
}

void saving_output(){
    last_output = init_DY_str() ; 
    last_output->pos = output->pos ; 
    last_output->size= output->size / 2; 
    change_size(last_output) ; 
    strcpy(last_output->str , output->str) ; 
    free(output->str) ; 
    free(output) ; 
    return ; 
}

int find_pos_by_line(int l_p , int x_p , char * path){
    FILE * my_file = fopen(path , "r") ; 
    int l_n = 0 ; 
    int ans ;
    while(l_n < l_p){
        char * A =(char *) calloc(1 , MX_CMD) ; 
        l_n++ ; 
        if (l_n==l_p){
            fseek(my_file , x_p , SEEK_CUR) ; 
            ans = (int)ftell(my_file) ; 
            break ; 
        }
        fgets(A , MX_CMD , my_file) ; 
    }
    fclose(my_file) ; 
    return ans ; 
}

void file_to_str_L_R(int l , int r , char * path , struct DY_str * DA){
    FILE * my_file = fopen(path , "r") ; 
    fseek(my_file , l , SEEK_CUR) ; 
    char c ; 
    while(l <= r){
        c = fgetc(my_file) ; 
        if (c=='\0'|| c==EOF) 
            break ; 
        l++ ; 
        char A[2] = {c , '\0'} ; 
        if (DA->size <= (DA->pos+1)*2){
            change_size(DA) ; 
        }
        DA->pos++ ; 
        strcat(DA->str , A) ; 
    }
    fclose(my_file) ; 
}

void str_to_file (char * path , char * str) { 
    FILE * my_file = fopen(path , "w") ; 
    for (int i = 0 ; i < strlen(str) ; i++)
        putc(str[i] , my_file) ;
    fclose(my_file) ; 
}

long long poww (long long a , long long b){
    if (b==0)
        return 1 ; 
    if (b==1)   
        return a ; 
    long long pp = poww(a , b/2) ; 
    if (b%2)
        return pp*a%mod * pp %mod ; 
    return
        pp*pp%mod ; 
}

int min (int a , int b){
    if (a > b)  
        return b ; 
    return a ;
}
int max(int a , int b){
    if (a > b)
        return a ; 
    return b ; 
}

long long HASH_file_name(char * str){
    long long hash = 0 ; 
    for (int i = 0 ; i < strlen(str) ; i++)
        hash = hash + poww((int)str[i] , 300) ; 
    return hash ; 
}
//copies 2 to 1
void copy_file_file (char * path1 , char * path2){
    struct DY_str * DY = init_DY_str() ; 
    file_to_str(path2 , DY) ; 
    str_to_file(path1 , DY->str) ; 
    free(DY->str) ; 
    free(DY) ; 
}

void Back_up(char * path){
    char * hash = calloc(1 , MX_CMD) ; 
    sprintf(hash , "%lld" , HASH_file_name(path)) ; 
    char * new_path = calloc(1 , MX_CMD) ; 
    strcpy(new_path , BACK_UP) ; 
    strcat(new_path , "/") ; 
    strcat(new_path , hash) ; 
    strcat(new_path , ".txt") ; 
    copy_file_file(new_path, path) ; 
}

int counter_word(int pos , char * str){
    int cnt = 1 ; 
    for (int i = 0 ; i < pos ; i++){
        if (str[i]==' ' || str[i]=='\n')
            cnt++ ; 
    }
    return cnt ; 
}
int coutner_line (int pos , char * str){
    int cnt = 1 ; 
    for (int i = 0 ; i < pos ; i++){
        if (str[i]=='\n')
            cnt++ ; 
    }
    return cnt ; 
}
char * file_line(int l_p , char *path){
    FILE * my_file = fopen(path , "r") ; 
    int l_n = 0 ; 
    while(l_n < l_p){
        char * A =(char *) calloc(1 , MX_CMD) ; 
        l_n++ ; 
        fgets(A , MX_CMD , my_file) ; 
        if (l_n==l_p){
            fclose(my_file) ; 
            return A  ; 
        }
    }
}
///////funcs


void create_file(){
    if (input_file[0][0]=='\"'){
        strcpy(input_file[0] , substr(1 , strlen(input_file[0])-2 , input_file[0])) ; 
    }
    char * now ; 
    now = strtok(input_file[0] , "/") ; 
    char * now_dir = (char*)malloc(MX_CMD); 
    while(1){
        strcat(now_dir , now) ; 
        now = strtok(NULL , "/") ; 
        if (now==NULL)
            break ; 
        printf(":::%s:\n" , now_dir) ; 
        mkdir(now_dir, 0700) ; 
        strcat(now_dir , "/") ; 
    }
    if (!File_exist(now_dir)){
        printf("File already exist!\n") ; 
    }
    else{
        printf("File added\n") ; 
        FILE * my_file = fopen(now_dir, "w") ; 
        fclose(my_file) ; 
    }
}

void cat (){
    if (input_file[0][0]=='\"'){
        strcpy(input_file[0] , substr(1 , strlen(input_file[0])-2 , input_file[0])) ; 
    }
    if (File_exist(input_file[0])){
        printf("No such File or directory!\n") ; 
        return ; 
    }
    output = init_DY_str() ; 
    file_to_str(input_file[0] , output) ; 
    printf("%s" , output->str) ; 
}

void dir_dfs(char * dir , char * prefix , int depth){
    if (depth==0)
        return ; 
    char *filepath = (char *)malloc(MX_CMD) ; 
    DIR *dp ; 
    struct dirent *dirp ; 
    struct stat filestat ; 

    dp = opendir(dir) ; 
    if (dp==NULL){
        printf("failed to open\n") ; 
        return ; 
    }
    while(dirp = readdir(dp)){
        if (dirp->d_name[0]=='.')
            continue ; 
        strcpy(filepath , "") ; 
        strcat(filepath , dir) ; 
        strcat(filepath , "/") ; 
        strcat(filepath , dirp->d_name) ;
        char * now = (char *)calloc(1 , MX_CMD) ; 
        strcpy(now , substr(0 , strlen(prefix)-2,  prefix)) ; 
        strcat(now , "|--") ; 
        strcat(now , dirp->d_name) ; 
        strcat(now , "\n") ; 
        while ((strlen(now) + output->pos )*2 >= output->size)
            change_size(output) ; 
        output->pos = output->pos + strlen(now) ; 
        strcat(output->str , now) ;
        //printf("%s|--%s\n" , substr(0 , strlen(prefix)-2,  prefix) , dirp->d_name) ; 
        if (stat(filepath , &filestat))
            continue ; 
        if (S_ISDIR(filestat.st_mode)){
            char Z [MX_CMD] ; 
            strcpy(Z , prefix) ; 
            strcat(prefix , "  |") ; 
            dir_dfs(filepath , prefix , depth-1) ; 
            strcpy(prefix , Z) ; 
        }
    }
    closedir(dp) ; 
}

void tree(){
    char *A = calloc(1 , MX_CMD) ; 
    char *B = calloc(1 , MX_CMD); 
    strcpy(A , "root") ; 
    strcpy(B , "|") ; 
    int d = atoi(input_unknown[0]) ; 
    if (d==-1)
        d = 1000000000 ; 
    output = init_DY_str() ; 
    dir_dfs(A , B , d) ; 
    printf("%s" , output->str) ; 
}

void insertstr(){
    if (input_file[0][0]=='\"'){
        strcpy(input_file[0] , substr(1 , strlen(input_file[0])-2 , input_file[0])) ; 
    }
    Back_up(input_file[0]) ; 
    int line = atoi(strtok(input_pos[0] , ":")) ; 
    int x = atoi(strtok(NULL , ":")) ; 
    int pos = find_pos_by_line(line , x , input_file[0]) ; 
    struct DY_str * now_DY = init_DY_str() ; 
    file_to_str_L_R(0 , pos -1 , input_file[0] , now_DY) ; 
    while (now_DY->size <= 2*(str_in->size + now_DY->pos))
        change_size(now_DY) ; 
    now_DY->pos = now_DY->pos + str_in->pos ; 
    strcat(now_DY->str, str_in->str) ;
    file_to_str_L_R(pos , inf , input_file[0] , now_DY) ; 
    str_to_file(input_file[0] , now_DY->str) ; 
    free(now_DY->str) ; 
    free(now_DY) ; 
}

void undo(){
    if (input_file[0][0]=='\"'){
        strcpy(input_file[0] , substr(1 , strlen(input_file[0])-2 , input_file[0])) ; 
    }
    char * hash = calloc(1 , MX_CMD) ; 
    sprintf(hash , "%lld" , HASH_file_name(input_file[0])) ; 
    char * new_path = calloc(1 , MX_CMD) ; 
    strcpy(new_path , BACK_UP) ; 
    strcat(new_path , "/") ; 
    strcat(new_path , hash) ; 
    strcat(new_path , ".txt") ;
    struct DY_str * DY = init_DY_str() ; 
    file_to_str(input_file[0]  , DY) ;
    copy_file_file(input_file[0] , new_path) ; 
    str_to_file(new_path , DY->str) ; 
    free(DY->str) ;
    free(DY) ; 
}

void removestr(){
    if (input_file[0][0]=='\"'){
        strcpy(input_file[0] , substr(1 , strlen(input_file[0])-2 , input_file[0])) ; 
    }
    int line = atoi(strtok(input_pos[0] , ":")) ; 
    int x = atoi(strtok(NULL , ":")) ; 
    int pos = find_pos_by_line(line , x , input_file[0]) ; 
    int siz = input_opt_size[0] ; 
    Back_up(input_file[0]) ; 
    int t = -1 ; 
    if (!strcmp(input_opt[0] , "-f"))
        t = 1 ; 
    int l = min (pos , pos + t*(siz)) ; 
    l = max(0 , l) ; 
    int r = max (pos , pos + t*(siz)) ; 
    struct DY_str * DY = init_DY_str() ; 
    file_to_str_L_R(0 , l - 1 , input_file[0] , DY) ; 
    file_to_str_L_R(r , inf , input_file[0] , DY) ; 
    str_to_file(input_file[0] , DY->str) ; 
    free(DY->str) ;
    free(DY) ; 
}

void copystr(){
    if (input_file[0][0]=='\"'){
        strcpy(input_file[0] , substr(1 , strlen(input_file[0])-2 , input_file[0])) ; 
    }
    int line = atoi(strtok(input_pos[0] , ":")) ; 
    int x = atoi(strtok(NULL , ":")) ; 
    int pos = find_pos_by_line(line , x , input_file[0]) ; 
    int siz = input_opt_size[0] ; 
    Back_up(input_file[0]) ; 
    int t = -1 ; 
    if (!strcmp(input_opt[0] , "-f"))
        t = 1 ; 
    int l = min (pos , pos + t*(siz)) ; 
    l = max(0 , l) ; 
    int r = max (pos , pos + t*(siz)) ; 
    clip_board = init_DY_str() ; 
    file_to_str_L_R(l , r-1 , input_file[0] , clip_board) ; 
}

void cutstr(){
    if (input_file[0][0]=='\"'){
        strcpy(input_file[0] , substr(1 , strlen(input_file[0])-2 , input_file[0])) ; 
    }
    Back_up(input_file[0]) ; 
    int line = atoi(strtok(input_pos[0] , ":")) ; 
    int x = atoi(strtok(NULL , ":")) ; 
    int pos = find_pos_by_line(line , x , input_file[0]) ; 
    int siz = input_opt_size[0] ; 
    int t = -1 ; 
    if (!strcmp(input_opt[0] , "-f"))
        t = 1 ; 
    int l = min (pos , pos + t*(siz)) ; 
    l = max(0 , l) ; 
    int r = max (pos , pos + t*(siz)) ; 
    clip_board = init_DY_str() ; 
    file_to_str_L_R(l , r-1 , input_file[0] , clip_board) ; 

    struct DY_str * DY = init_DY_str() ; 
    file_to_str_L_R(0 , l - 1 , input_file[0] , DY) ; 
    file_to_str_L_R(r , inf , input_file[0] , DY) ; 
    str_to_file(input_file[0] , DY->str) ; 
    free(DY->str) ;
    free(DY) ; 
}

void pastestr(){
    str_in = init_DY_str() ; 
    while (str_in->size <= 2*(str_in->pos + clip_board->size))
        change_size(str_in) ; 
    str_in->pos = clip_board->pos ; 
    strcat(str_in->str, clip_board->str) ;
    insertstr() ; 
    free(str_in->str) ; 
    free(str_in) ; 
}

void compare(){
    if (input_file[0][0]=='\"'){
        strcpy(input_file[0] , substr(1 , strlen(input_file[0])-2 , input_file[0])) ; 
    }
    if (input_file[1][0]=='\"'){
        strcpy(input_file[1] , substr(1 , strlen(input_file[1])-2 , input_file[1])) ; 
    }
    FILE * file1 = fopen(input_file[0] , "r") ; 
    FILE * file2 = fopen(input_file[1] , "r") ;     
    int t = -1 ; 
    int li = 1 ; 
    output = init_DY_str() ; 
    while(1){
        char A[MX_CMD] , B[MX_CMD] , tmp[MX_CMD*10] ; 
        if (fgets(A , MX_CMD , file1)==NULL){
            if (fgets(B , MX_CMD , file2)==NULL)
                break ; 
            sprintf(tmp, "!@# file 1 ended #@!\n") ; 
            strcat(output->str , tmp) ; 
            output->pos = output->pos + 40 ; 
            while(1){
                while (output->size <= 2*(output->pos + strlen(B) + 10))
                    change_size(output) ; 
                output->pos = output->pos + strlen(B) + 40 ; 
                sprintf(tmp , ">>%s<<\n" , B) ;
                strcat(output->str , tmp) ; 
                if(fgets(B , MX_CMD , file2)==NULL)
                    break ; 
            }
            break ; 
        }
        if (fgets(B , MX_CMD , file2)==NULL){
            sprintf(tmp, "!@# file 2 ended #@!\n") ; 
            strcat(output->str , tmp) ; 
            output->pos = output->pos + 40 ; 
            while(1){
                while (output->size <= 2*(output->pos + strlen(A) + 10))
                    change_size(output) ; 
                output->pos = output->pos + strlen(A) + 40 ; 
                sprintf(tmp, ">>%s<<\n" , A) ;
                strcat(output->str , tmp) ; 
                if(fgets(A , MX_CMD , file1)==NULL)
                    break ; 
            }
            break ; 
        }
        if (strcmp(A , B)!=0){
            while (output->size <= 2*(output->pos + strlen(A) , strlen(B) + 40))
                change_size(output) ; 
            output->pos = output->pos + strlen(A) + strlen(B) +40 ;
            sprintf(tmp , "========== line : %d ==========\n" , li) ; 
            strcat(output->str , tmp) ; 
            sprintf(tmp , ">>%s<<\n" , A) ; 
            strcat(output->str , tmp) ; 
            sprintf(tmp , ">>%s<<\n" , B) ; 
            strcat(output->str , tmp) ; 
            li++ ; 
        }
    }
    fclose(file1) ; 
    fclose(file2) ; 
}

void find(){
    if (input_file[0][0]=='\"'){
        strcpy(input_file[0] , substr(1 , strlen(input_file[0])-2 , input_file[0])) ; 
    }
    //Back_up(input_file[0]) ;
    struct DY_str * DA = init_DY_str(); 
    file_to_str(input_file[0] , DA) ; 
    int is_wild_l = 0 , is_wild_r = 0 , m_size = 0; 
    char *m_world;
    m_world = (char *)calloc(1 , MX_CMD) ; 
    int sz = strlen(str_in->str) ; 
    int T = 0 ; 
    if (str_in->str[0]=='*')
        is_wild_l = 1 ; 
    if (str_in->str[sz-1]=='*'&& str_in->str[sz-2]!='\\')
        is_wild_r = 1 ; 
    if (!(is_wild_l||is_wild_r)){
        m_size = sz ;
        strcpy(m_world , substr(0 , sz-1 , str_in->str)) ; 
    }
    else if (is_wild_l){
        m_size = sz-1 ; 
        strcpy(m_world , substr(1 , sz-1 , str_in->str)) ; 
    }
    else {
        m_size = sz-1 ; 
        strcpy(m_world , substr(0 , sz-2 , str_in->str)) ; 
    }

    int pri_cnt_find = 0 ; 
    int pri_pos_find[MX_CMD] ; 
    int sz2 = strlen(DA->str) ; 
    for (int i = 0 ; i < sz2; i++){
        int t = 1 ; 
        for (int j = i ; j < i + m_size ; j++){
            if (j >= sz2){
                t = 0 ; 
                break ; 
            }
            if (m_world[j-i] != DA->str[j]){
                t = 0 ; 
                break ; 
            }
        }
        if (t==1){
            pri_pos_find[pri_cnt_find] = i ; 
            pri_cnt_find++ ; 
        }
    }
    int cnt_find = 0 ; 
    int pos_find[MX_CMD] ; 
    int f_pos_find[MX_CMD] ; 
    for (int cur = 0 ; cur < pri_cnt_find ; cur++){
        if (!(is_wild_l||is_wild_r)){
            int pos = pri_pos_find[cur] ; 
            int fpos = pos + m_size - 1 ; 
            if ((pos==0||DA->str[pos-1]==' '||DA->str[pos-1]=='\n')&&(fpos==sz2-1||DA->str[fpos+1]==' '||DA->str[fpos+1]=='\n'||DA->str[fpos+1]=='\0')){
                pos_find[cnt_find] = pos ; 
                f_pos_find[cnt_find] = fpos ; 
                cnt_find++ ; 
            }
        }
        else if(is_wild_l){
            int pos = pri_pos_find[cur] ; 
            int fpos = pos + m_size - 1; 
            if ((fpos==sz2-1||DA->str[fpos+1]==' '||DA->str[fpos+1]=='\n'||DA->str[fpos+1]=='\0')){
                while(pos >=1 && !(DA->str[pos-1]==' '||DA->str[pos-1]=='\n'||DA->str[pos-1]=='\0'))
                    pos-- ; 
                pos_find[cnt_find] = pos ; 
                f_pos_find[cnt_find] = fpos ; 
                cnt_find++ ; 
            }
        }
        else if (is_wild_r){
            int pos = pri_pos_find[cur] ; 
            int fpos = pos + m_size - 1; 
            if (pos==0 || DA->str[pos-1]==' '||DA->str[pos-1]=='\n'||DA->str[pos-1]=='\0'){
                while(fpos < sz2-1&&!(DA->str[fpos+1]==' '||DA->str[fpos+1]=='\n'||DA->str[fpos+1]=='\0'))
                    fpos++ ;
                pos_find[cnt_find] = pos ; 
                f_pos_find[cnt_find] = fpos ; 
                cnt_find++ ; 
            }
        }
    }

    output = init_DY_str() ; 
    int at_on = 0 , count_on = 0, byword_on = 0 , all_on = 0 ; 
    for (int i = 0 ; i < cnt_input_opt ; i++){
        if (strcmp(input_opt[i] , "-at")==0)
            at_on = 1 ; 
        if (strcmp(input_opt[i] , "-all")==0)
            all_on = 1 ; 
        if (strcmp(input_opt[i] , "-count")==0)
            count_on = 1 ; 
        if (strcmp(input_opt[i] , "-byword")==0)
            byword_on = 1 ; 
    }
    if (at_on&&all_on){
        printf("-at and -all can't be applied in same time\n") ; 
        return ; 
    }
    if (count_on&&(at_on||all_on||count_on)){
        printf("coutn can't be applied with other options at same time\n") ; 
    }
    int ans[MX_CMD] ; 
    while(output->size < MX_CMD * MX_CMD)
        change_size(output) ; 
    if (byword_on){
        for (int i = 0 ; i < cnt_find ; i++)
            ans[i] = counter_word(pos_find[i] , DA->str) ; 
    }
    if (!byword_on){
        for (int i = 0 ; i < cnt_find ; i++)
            ans[i] = pos_find[i] ; 
    }
    if (!(at_on||all_on||count_on)){
        if (cnt_find==0){
            strcpy(output->str , "-1") ; 
            free(DA->str) ; 
            free(DA) ;
            return ;
        }
        char  A[1000] ; 
        sprintf(A , "%d" , ans[0]) ; 
        strcpy(output->str, A) ;
        free(DA->str) ; 
        free(DA) ; 
        return ; 
    }
    if (count_on){
        char A[1000] ; 
        sprintf(A , "%d" , cnt_find) ; 
        strcpy(output->str , A) ; 
        free(DA->str) ; 
        free(DA) ; 
        return ; 
    }
    if (at_on){
        int pos = atoi(input_unknown[0]) ; 
        pos-- ; 
        if (cnt_find < pos){
            printf("%dth not founded\n" , pos) ; 
            return ; 
        }
        char A[1000] ; 
        sprintf(A , "%d" , ans[pos]) ; 
        strcpy(output->str , A) ; 
        free(DA->str) ; 
        free(DA) ; 
        return ; 
    }
    if (all_on){
        for (int i = 0 ; i < cnt_find ; i++){
            char A[1000] ; 
            sprintf(A , "%d" , ans[i]) ; 
            strcpy(output->str , A) ; 
            if (i!=cnt_find-1)
                strcat(output->str , " , " ) ; 
        }
        free(DA->str) ; 
        free(DA) ; 
        return ; 
    }
}

void replace(){
    if (input_file[0][0]=='\"'){
        strcpy(input_file[0] , substr(1 , strlen(input_file[0])-2 , input_file[0])) ; 
    }
    Back_up(input_file[0]) ;
    struct DY_str * DA = init_DY_str(); 
    file_to_str(input_file[0] , DA) ; 
    int is_wild_l = 0 , is_wild_r = 0 , m_size = 0; 
    char *m_world;
    m_world = (char *)calloc(1 , MX_CMD) ; 
    int sz = strlen(str_in->str) ; 
    int T = 0 ; 
    if (str_in->str[0]=='*')
        is_wild_l = 1 ; 
    if (str_in->str[sz-1]=='*'&& str_in->str[sz-2]!='\\')
        is_wild_r = 1 ; 
    if (!(is_wild_l||is_wild_r)){
        m_size = sz ;
        strcpy(m_world , substr(0 , sz-1 , str_in->str)) ; 
    }
    else if (is_wild_l){
        m_size = sz-1 ; 
        strcpy(m_world , substr(1 , sz-1 , str_in->str)) ; 
    }
    else {
        m_size = sz-1 ; 
        strcpy(m_world , substr(0 , sz-2 , str_in->str)) ; 
    }

    int pri_cnt_find = 0 ; 
    int pri_pos_find[MX_CMD] ; 
    int sz2 = strlen(DA->str) ; 
    for (int i = 0 ; i < sz2; i++){
        int t = 1 ; 
        for (int j = i ; j < i + m_size ; j++){
            if (j >= sz2){
                t = 0 ; 
                break ; 
            }
            if (m_world[j-i] != DA->str[j]){
                t = 0 ; 
                break ; 
            }
        }
        if (t==1){
            pri_pos_find[pri_cnt_find] = i ; 
            pri_cnt_find++ ; 
        }
    }
    int cnt_find = 0 ; 
    int pos_find[MX_CMD] ; 
    int f_pos_find[MX_CMD] ; 
    for (int cur = 0 ; cur < pri_cnt_find ; cur++){
        if (!(is_wild_l||is_wild_r)){
            int pos = pri_pos_find[cur] ; 
            int fpos = pos + m_size - 1 ; 
            if ((pos==0||DA->str[pos-1]==' '||DA->str[pos-1]=='\n')&&(fpos==sz2-1||DA->str[fpos+1]==' '||DA->str[fpos+1]=='\n'||DA->str[fpos+1]=='\0')){
                pos_find[cnt_find] = pos ; 
                f_pos_find[cnt_find] = fpos ; 
                cnt_find++ ; 
            }
        }
        else if(is_wild_l){
            int pos = pri_pos_find[cur] ; 
            int fpos = pos + m_size - 1; 
            if ((fpos==sz2-1||DA->str[fpos+1]==' '||DA->str[fpos+1]=='\n'||DA->str[fpos+1]=='\0')){
                while(pos >=1 && !(DA->str[pos-1]==' '||DA->str[pos-1]=='\n'||DA->str[pos-1]=='\0'))
                    pos-- ; 
                pos_find[cnt_find] = pos ; 
                f_pos_find[cnt_find] = fpos ; 
                cnt_find++ ; 
            }
        }
        else if (is_wild_r){
            int pos = pri_pos_find[cur] ; 
            int fpos = pos + m_size - 1; 
            if (pos==0 || DA->str[pos-1]==' '||DA->str[pos-1]=='\n'||DA->str[pos-1]=='\0'){
                while(fpos < sz2-1&&!(DA->str[fpos+1]==' '||DA->str[fpos+1]=='\n'||DA->str[fpos+1]=='\0'))
                    fpos++ ;
                pos_find[cnt_find] = pos ; 
                f_pos_find[cnt_find] = fpos ; 
                cnt_find++ ; 
            }
        }
    }
    if (cnt_find==0){
        printf("no match!\n") ;
        return ;  
    }
    
    output = init_DY_str() ; 
    int at_on = 0 , all_on= 0 ; 
    for (int i = 0 ; i < cnt_input_opt ; i++){
        if (strcmp(input_opt[i] , "-at")==0)
            at_on = 1 ; 
        if (strcmp(input_opt[i] , "-all")==0)
            all_on = 1 ; 
    }
    if (at_on&&all_on){
        printf("-at and -all can't be applied in same time\n") ; 
        free(DA->str) ; 
        free(DA) ; 
        return ; 
    }
    if (all_on){
        int pre = 0 ; 
        for (int i = 0 ; i < cnt_find ; i++){
            strcat(output->str , substr(pre , pos_find[i]-1 , DA->str)) ; 
            strcat(output->str , input_str[1]) ; 
            if (i==cnt_find-1)
                strcat(output->str ,  substr(f_pos_find[i]+1 , sz2 , DA->str)) ; 
            pre = f_pos_find[i] + 1 ; 
        }
    }
    else {
        int pos ; 
        if (!at_on)
            pos = 0 ; 
        else 
            pos = atoi(input_unknown[0]) - 1 ; 
        strcat(output->str , substr(0 , pos_find[pos]-1 , DA->str)) ; 
        strcat(output->str , input_str[1]) ; 
        strcat(output->str ,  substr(f_pos_find[pos]+1 , sz2 , DA->str)) ; 
    }
    str_to_file(input_file[0] , output->str) ; 
    printf("Done\n") ; 
    free(DA->str) ; 
    free(DA) ; 
}

void grep(){
    if (input_file[0][0]=='\"'){
        strcpy(input_file[0] , substr(1 , strlen(input_file[0])-2 , input_file[0])) ; 
    }

    struct DY_str * DA = init_DY_str(); 
    file_to_str(input_file[0] , DA) ; 
    int is_wild_l = 0 , is_wild_r = 0 , m_size = 0; 
    char *m_world;
    m_world = (char *)calloc(1 , MX_CMD) ; 
    int sz = strlen(str_in->str) ; 
    int T = 0 ; 
    if (str_in->str[0]=='*')
        is_wild_l = 1 ; 
    if (str_in->str[sz-1]=='*'&& str_in->str[sz-2]!='\\')
        is_wild_r = 1 ; 
    if (!(is_wild_l||is_wild_r)){
        m_size = sz ;
        strcpy(m_world , substr(0 , sz-1 , str_in->str)) ; 
    }
    else if (is_wild_l){
        m_size = sz-1 ; 
        strcpy(m_world , substr(1 , sz-1 , str_in->str)) ; 
    }
    else {
        m_size = sz-1 ; 
        strcpy(m_world , substr(0 , sz-2 , str_in->str)) ; 
    }

    int pri_cnt_find = 0 ; 
    int pri_pos_find[MX_CMD] ; 
    int sz2 = strlen(DA->str) ; 
    for (int i = 0 ; i < sz2; i++){
        int t = 1 ; 
        for (int j = i ; j < i + m_size ; j++){
            if (j >= sz2){
                t = 0 ; 
                break ; 
            }
            if (m_world[j-i] != DA->str[j]){
                t = 0 ; 
                break ; 
            }
        }
        if (t==1){
            pri_pos_find[pri_cnt_find] = i ; 
            pri_cnt_find++ ; 
        }
    }
    int cnt_find = 0 ; 
    int pos_find[MX_CMD] ; 
    int f_pos_find[MX_CMD] ; 
    for (int cur = 0 ; cur < pri_cnt_find ; cur++){
        if (!(is_wild_l||is_wild_r)){
            int pos = pri_pos_find[cur] ; 
            int fpos = pos + m_size - 1 ; 
            if ((pos==0||DA->str[pos-1]==' '||DA->str[pos-1]=='\n')&&(fpos==sz2-1||DA->str[fpos+1]==' '||DA->str[fpos+1]=='\n'||DA->str[fpos+1]=='\0')){
                pos_find[cnt_find] = pos ; 
                f_pos_find[cnt_find] = fpos ; 
                cnt_find++ ; 
            }
        }
        else if(is_wild_l){
            int pos = pri_pos_find[cur] ; 
            int fpos = pos + m_size - 1; 
            if ((fpos==sz2-1||DA->str[fpos+1]==' '||DA->str[fpos+1]=='\n'||DA->str[fpos+1]=='\0')){
                while(pos >=1 && !(DA->str[pos-1]==' '||DA->str[pos-1]=='\n'||DA->str[pos-1]=='\0'))
                    pos-- ; 
                pos_find[cnt_find] = pos ; 
                f_pos_find[cnt_find] = fpos ; 
                cnt_find++ ; 
            }
        }
        else if (is_wild_r){
            int pos = pri_pos_find[cur] ; 
            int fpos = pos + m_size - 1; 
            if (pos==0 || DA->str[pos-1]==' '||DA->str[pos-1]=='\n'||DA->str[pos-1]=='\0'){
                while(fpos < sz2-1&&!(DA->str[fpos+1]==' '||DA->str[fpos+1]=='\n'||DA->str[fpos+1]=='\0'))
                    fpos++ ;
                pos_find[cnt_find] = pos ; 
                f_pos_find[cnt_find] = fpos ; 
                cnt_find++ ; 
            }
        }
    }
    if (cnt_find==0){
        //printf("no match!\n") ; 
        return ; 
    }
    while(output->size < MX_CMD * MX_CMD)
        change_size(output) ; 
    int op_c = 0  , op_l = 0 ; 
    for (int i = 0 ; i < cnt_input_opt ; i++){
        if (strcmp(input_opt[i] , "-c")==0)
            op_c = 1 ; 
        if (strcmp(input_opt[i] , "-l")==0)
            op_l = 1 ;
    }
    if(op_c&&op_l){
        printf("-p and -c can't be applied in same time\n") ; 
        return ; 
    }
    else if (op_l){
        strcat(output->str , input_file[0]) ; 
        strcat(output->str , "\n") ; 
        return ; 
    }
    else if (op_c){
        int pre = 0 ; 
        int cnt = 0 ; 
        for (int i = 0 ; i < cnt_find ; i++){
            int now_line = coutner_line(pos_find[i], DA->str) ; 
            if (now_line==pre)
                continue ;
            cnt_grep++ ;
            pre = now_line ; 
        }
        return ; 
    }
    int pre = 0 ; 
    for (int i = 0 ; i < cnt_find ; i++){
        int now_line = coutner_line(pos_find[i], DA->str) ; 
        if (now_line==pre)
            continue ;
        strcat(output->str , input_file[0]) ; 
        strcat(output->str , " : ") ; 
        strcat(output->str , file_line(now_line , input_file[0]) ); 
        strcat(output->str , "\n") ;  
        pre = now_line ; 
    }
    free(DA->str) ; 
    free(DA) ; 
}

void auto_indent(){
    if (input_file[0][0]=='\"'){
        strcpy(input_file[0] , substr(1 , strlen(input_file[0])-2 , input_file[0])) ; 
    }
    Back_up(input_file[0]) ; 
    struct DY_str * DA = init_DY_str(); 
    file_to_str(input_file[0] , DA) ; 
    int cnt = 0 , t = 1 ; 
    for (int i = 0 ; i < strlen(DA->str) ; i++){
        if (DA->str[i]=='}')
            cnt--  ;
        if (DA->str[i]=='{')
            cnt++ ; 
        if (cnt < 0)
            t = 0 ; 
    }
    if(!t){
        printf("akoolad bandi kharabe!\n") ;
        free(DA->str) ; 
        free(DA) ; 
        return ; 
    }
    output = init_DY_str() ; 
    int sz = strlen(DA->str) ; 
    int tab_size = 4 ; 
    int cnt_tab = 0 , cnt_space = 0; 
    char pre = '\0' ; 
    int pos = 0 ; 
    for (int i = 0 ; i < sz ; i++){
        char cur = DA->str[i] ; 
        if (cur==' '){
            cnt_space++ ; 
        }
        else if (cur=='{'){
            if (pre=='\0'){
                output->str[pos] = '{' ; 
                pos++ ; 
            }
            else if (pre=='{'){
                output->str[pos] = '\n' ; 
                pos++ ; 
                for (int j = 0 ; j < tab_size*cnt_tab ; j++){
                    output->str[pos] = ' ' ; 
                    pos++ ; 
                }
                output->str[pos] = '{' ; 
                pos++ ; 
            }
            else if (pre=='}'){
                output->str[pos] = '\n' ; 
                pos++ ; 
                for (int j = 0 ; j < tab_size*cnt_tab ; j++){
                    output->str[pos] = ' ' ; 
                    pos++ ; 
                }
                output->str[pos] = '{' ; 
                pos++ ; 
            }
            else {
                output->str[pos] = ' ' ; 
                pos++ ; 
                output->str[pos] = '{' ; 
                pos++ ; 
            }
            cnt_space = 0 ; 
            cnt_tab++ ; 
            pre = cur ; 
        }
        else if (cur=='}'){
            if (pre=='{'){
                output->str[pos] = '\n' ; 
                pos++ ; 
                output->str[pos] = '\n' ; 
                pos++ ; 
                for (int j = 0 ; j < (cnt_tab-1)*tab_size ; j++){
                    output->str[pos] = ' ' ; 
                    pos++ ; 
                }
                output->str[pos] = '}' ; 
                pos++ ; 
            }
            else if (pre=='}'){
                output->str[pos] = '\n' ; 
                pos++ ; 
                for (int j = 0 ; j < tab_size*cnt_tab ; j++){
                    output->str[pos] = ' ' ; 
                    pos++ ; 
                }
                output->str[pos] = '}' ; 
                pos++ ; 
            }
            else {
                output->str[pos] = '\n' ; 
                pos++ ; 
                for (int j = 0 ; j < tab_size*(cnt_tab-1) ; j++){
                    output->str[pos] = ' ' ; 
                    pos++ ; 
                }
                output->str[pos] = '}' ; 
                pos++ ; 
            }
            cnt_space = 0 ; 
            cnt_tab-- ; 
            pre = cur ; 
        }
        else{
            if (pre=='{'){
                output->str[pos] = '\n' ; 
                pos++ ; 
                for (int j = 0 ; j < tab_size*cnt_tab ; j++){
                    output->str[pos] = ' ' ; 
                    pos++ ; 
                }
                output->str[pos] = cur ; 
                pos++ ; 
            }
            else if (pre=='}'){
                output->str[pos] = '\n' ; 
                pos++ ; 
                for (int j = 0 ; j < tab_size*cnt_tab ; j++){
                    output->str[pos] = ' ' ; 
                    pos++ ; 
                }
                output->str[pos] = cur ; 
                pos++ ; 
            }
            else{
                for (int j = 0 ; j < cnt_space ; j++){
                    output->str[pos] = ' ' ; 
                    pos++ ; 
                }
                output->str[pos] = cur ; 
                pos++ ; 
            }
            cnt_space = 0 ; 
            pre = cur ; 
        }
    }
    str_to_file(input_file[0] , output->str) ; 
    free(DA->str) ; 
    free(DA) ; 
}

//////main
int main(){
    while(1){
        cnt_arman = 0 ; 
        char command[MX_CMD*10]; 
        fgets(command , MX_CMD *10, stdin) ; 
        if (strcmp(command,"\n")==0)
            continue ; 
        int lpos = 0 ; 
        for (int i = 0 ; i < strlen(command) ; i++){
            if ((command[i]=='='&&command[i+1]=='D') || command[i]=='\0' || command[i]=='\n'){
                strcpy(input_arman[cnt_arman] , substr(lpos , i-1 , command)) ; 
                cnt_arman++ ; 
                lpos = i + 2 ; 
            }
        }
        for (int i = 0 ; i < cnt_arman ; i++){
            if (i)
                is_arman = 1 ; 
            else 
                is_arman = 0 ; 
            clear_input() ; 
            main_input(input_arman[i]) ; 
            //input_debugger() ; 
            if (!strcmp(input_kind , "exit")){
                printf("OK\n") ; 
                return 0 ; 
            }
            else if (!strcmp(input_kind , "createfile")){
                create_file() ; 
            }
            else if (!strcmp(input_kind , "insertstr")){
                str_in = init_DY_str() ; 
                if (is_arman){
                    while(str_in->size < last_output->size)
                        change_size(str_in) ; 
                    strcpy(str_in->str, last_output->str) ; 
                }
                else {
                    if (input_str[0][0]=='\"')
                        strcpy(input_str[0] , substr(1 , strlen(input_str[0])-2 , input_str[0])) ; 

                    while(str_in->size < 2*strlen(input_str[0]))
                        change_size(str_in) ; 
                    strcpy(str_in->str , input_str[0]) ; 
                }
                insertstr() ; 
                free(str_in->str) ; 
                free(str_in) ; 
            }
            else if (!strcmp(input_kind , "cat")){
                cat() ; 
                saving_output() ; 
            }
            else if (!strcmp(input_kind , "removestr")){
                removestr() ; 
            }
            else if (!strcmp(input_kind , "copystr")){
                copystr() ; 
            }
            else if (!strcmp(input_kind , "cutstr")){
                cutstr() ; 
            }
            else if (!strcmp(input_kind , "pastestr")){
                pastestr() ; 
            }
            else if (!strcmp(input_kind , "find")){
                str_in = init_DY_str() ; 
                if (is_arman){
                    while(str_in->size < last_output->size)
                        change_size(str_in) ; 
                    strcpy(str_in->str, last_output->str) ; 
                }
                else {
                    if (input_str[0][0]=='\"')
                        strcpy(input_str[0] , substr(1 , strlen(input_str[0])-2 , input_str[0])) ; 

                    while(str_in->size < 2*strlen(input_str[0]))
                        change_size(str_in) ; 
                    strcpy(str_in->str , input_str[0]) ; 
                }
                find() ; 
                printf("%s\n" , output->str) ; 
                free(str_in->str) ; 
                free(str_in) ; 
                saving_output() ; 
            }
            else if (!strcmp(input_kind , "replace")){
                str_in = init_DY_str() ; 
                if (is_arman){
                    while(str_in->size < last_output->size)
                        change_size(str_in) ; 
                    strcpy(str_in->str, last_output->str) ; 
                }
                else {
                    if (input_str[0][0]=='\"')
                        strcpy(input_str[0] , substr(1 , strlen(input_str[0])-2 , input_str[0])) ; 

                    while(str_in->size < 2*strlen(input_str[0]))
                        change_size(str_in) ; 
                    strcpy(str_in->str , input_str[0]) ; 
                }
                if (input_str[1][0]=='\"')
                    strcpy(input_str[1] , substr(1 , strlen(input_str[1])-2 , input_str[1])) ; 
                replace() ; 
                //printf("%s\n" , output->str) ; 
                free(str_in->str) ; 
                free(str_in) ; 
            }
            else if (!strcmp(input_kind , "grep")){
                str_in = init_DY_str() ; 
                if (is_arman){
                    while(str_in->size < last_output->size)
                        change_size(str_in) ; 
                    strcpy(str_in->str, last_output->str) ; 
                }
                else {
                    if (input_str[0][0]=='\"')
                        strcpy(input_str[0] , substr(1 , strlen(input_str[0])-2 , input_str[0])) ; 

                    while(str_in->size < 2*strlen(input_str[0]))
                        change_size(str_in) ; 
                    strcpy(str_in->str , input_str[0]) ; 
                }
                output = init_DY_str() ; 
                for (int i = 0 ; i < cnt_input_file ; i++){
                    strcpy(input_file[0] , input_file[i]) ; 
                    grep() ; 
                }
                int op_c = 0 ; 
                for (int i = 0 ; i < cnt_input_opt ; i++){
                    if (strcmp(input_opt[i] , "-c")==0)
                        op_c = 1 ; 
                }
                if (op_c){
                    sprintf(output->str , "%d" , cnt_grep) ; 
                }
                printf("%s\n" , output->str) ; 
                saving_output() ; 
                cnt_grep = 0 ; 
            }
            else if (!strcmp(input_kind , "undo")){
                undo() ; 
            }
            else if (!strcmp(input_kind , "auto-indent")){
                auto_indent() ; 
            }
            else if (!strcmp(input_kind , "compare")){
                compare() ; 
                printf("%s\n.....................................................\n" , output->str) ; 
                saving_output() ; 
            }
            else if (!strcmp(input_kind , "tree")){
                tree() ; 
                saving_output() ; 
            }
            else {
                printf("Invalid command!\n") ; 
            }
        }
    }
}
