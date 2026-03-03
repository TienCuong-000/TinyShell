#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <tlhelp32.h> 

#define MAX_NUM 4096

typedef struct PRC_inf_BGR {
    PROCESS_INFORMATION pi;
    int background;
    char name_prc[MAX_NUM];
    char active[100];
} PRC_inf_BGR;

int Exitt( char input[]) {          //EXIT CHO SHELL
    int l = (int)strlen(input);
    if (!_stricmp(input, "exit") || !_stricmp(input, "thoat") || !strcmp(input, "&"))
        return 1;
    if (l >= 4 && !_stricmp(input + l - 4, "exit"))
        return 1;
     if (!_stricmp(input, "exitshell") || !_stricmp(input, "KET_THUC") || !strcmp(input, "exit_shell")){
          printf ("CHAO_BAN_CAM_ON_BAN_DA_DEN");
        Sleep(5000);
        exit(0);
     }
    if (l >= 10 && !_stricmp(input + l - 10, "exit_shell")){
        printf ("CHAO_BAN_CAM_ON_BAN_DA_DEN");
        Sleep(5000);
        exit(0);
    }
  return 0 ; 
}



void Exit_Shell (char input[]){    //EXIT CHO CHƯƠNG TRÌNH
     int l = (int)strlen(input);
    if (!_stricmp(input, "exit") || !_stricmp(input, "thoat")){
        printf ("CHAO_BAN_CAM_ON_BAN_DA_DEN");
        Sleep(1000);
        exit(0);
    }
    if (l >= 4 && !_stricmp(input + l - 4, "exit")){
        printf ("CHAO_BAN_CAM_ON_BAN_DA_DEN");
        Sleep(1000);
        exit(0);
    }
       if (!_stricmp(input, "exitshell") || !_stricmp(input, "KET_THUC") || !strcmp(input, "exit_shell")){
          printf ("CHAO_BAN_CAM_ON_BAN_DA_DEN");
        Sleep(1000);
        exit(0);
     }
    if (l >= 10 && !_stricmp(input + l - 10, "exit_shell")){
        printf ("CHAO_BAN_CAM_ON_BAN_DA_DEN");
        Sleep(1000);
        exit(0);
}
}

PROCESS_INFORMATION *piInf;

/*void sigint_handle(int sig){
    if(piInf->hProcess!=NULL){
        printf("Terminated_Succesful\n");
        TerminateProcess(piInf->hProcess,0);
        CloseHandle(piInf->hProcess);
        CloseHandle(piInf->hThread);
        piInf->hProcess=NULL;
        piInf=NULL;
        return;
   }
   else return;
}*/
BOOL WINAPI CtrlHandler(DWORD ctrlType) {
    if(ctrlType == CTRL_C_EVENT) {  // Ctrl+C
        if(piInf != NULL && piInf->hProcess != NULL) {
            printf("Terminated_Succesful\n");
            TerminateProcess(piInf->hProcess, 0); // kill foreground process
            CloseHandle(piInf->hProcess);
            CloseHandle(piInf->hThread);
            piInf->hProcess = NULL;
            piInf = NULL;
        } 
        return TRUE; 
    }
 
    return TRUE;
}

int special(){           //SPECIAL 
    int num =0 ; 
    while(1){
        char input[MAX_NUM];
        printf("  >>Special_CMD...: ");
        fgets(input,sizeof(input),stdin);
        input[strcspn(input , "\n")] = 0; 
        if(Exitt(input)) break;
        
     if (!_stricmp(input, "help") || !_stricmp(input, "giup_do")){       ///HELP
           printf("----------------------------------------------------------\n");
           printf("Cac lenh ban co the su dung:\n");
           printf("  - EXIT / thoat       : Thoat khoi shell\n");
           printf("  - HELP /giup_do      : Hien thi danh sach lenh \n");
           printf("  - DATE /ngay         : In ngay hien tai\n");
           printf("  - TIME /thoi_gian    : In gio hien tai\n");
           printf("  - DIR                : Liet ke thu muc hien tai\n");
           printf("  - PATH               : Xem danh sach bien moi truong PATH\n");
           printf("  - USERPROFIlE        : Xem danh sach USER_PROFILE\n");
           //printf("  - TEMP               : Xem danh sach bien TEMP\n");
           printf("  - ADDPATH <dir>      : Them duong dan vao PATH\n");
           printf("----------------------------------------------------------\n");
        num= 1 ;
     }
      else if (!_stricmp(input, "date") || !_stricmp(input, "ngay")){         //IN RA DATE
        SYSTEMTIME st;
        GetLocalTime(&st);
        printf( "DATE....: %02d - %02d - %02d\n" , st.wDay, st.wMonth, st.wYear);
        num= 1 ;
     }
      else if (!_stricmp(input, "time") || !_stricmp(input, "thoi_gian")){    //IN RA TIME 
        SYSTEMTIME st;
        GetLocalTime(&st);
        printf( "TIME....: %02d - %02d - %02d\n" , st.wHour, st.wMinute, st.wSecond);
        num= 1 ;
     }
     else if (!_stricmp(input, "dir")){                                      //IN RA DIRECTION
        WIN32_FIND_DATA listData;
        HANDLE tmp;
        if(( tmp = FindFirstFile("*.*",&listData))==INVALID_HANDLE_VALUE)
            { 
                printf("Khong_The_Mo_File_Hien_Tai. \n");
                num=1 ;
            }
        do{
            if(strcmp(listData.cFileName,".") != 0 && strcmp(listData.cFileName,"..") != 0 ){
                if(listData.dwFileAttributes &FILE_ATTRIBUTE_DIRECTORY){
                    printf("[DIR]       :%s\n",listData.cFileName);
                }else{
                    printf("Normal file :%s\n",listData.cFileName);
                }
            }
        }while(FindNextFile(tmp,&listData));
        FindClose(tmp);
        num= 1 ;
     }
     else if (!_stricmp(input, "addpath")){                                   //THÊM BIẾN MÔI TRƯỜNG PATH
       char namePath[MAX_NUM];
       printf("  ( Nhap_exit_De_Thoat ) ");
       printf("Nhap_Duong_Dan_PATH_Muon_Add...>");
       fgets(namePath,sizeof(namePath), stdin);
       namePath[strcspn(namePath, "\n")] = 0;
       if(Exitt(namePath)){
        printf("Exit_AddPATH\n");
         num=1;
         continue;
       }
       char *oPath=getenv("PATH");
       if(oPath!=NULL){
            char nPath[MAX_NUM*10];
            snprintf(nPath ,sizeof(nPath),"%s;%s",oPath,namePath);
            _putenv_s("PATH",nPath);
       }
       else{
        _putenv_s("PATH",namePath);
       }
       printf("ADD_%s_TO_PATH\n",namePath);
       num=1;
     }
     else if (!_stricmp(input, "path")){                                      //IN RA LIST PATH
        char *path=NULL;
        path = getenv("PATH");
        if(path!=NULL){
            printf("CUR_PATH_:%s\n",path);
        }
        else{
            printf("Cannot_Find_PATH / PATH_Is_Not_Set\n");
        }
        num= 1 ; 
     }
     else if (!_stricmp(input, "userprofile")){                               //IN RA LIST USERPROFILE → thư mục người dùng
        char *userprofile=NULL;
        userprofile = getenv("USERPROFILE");
        if(userprofile!=NULL){
            printf("CUR_HOME_:%s\n",userprofile);
        }
        else{
            printf("Cannot_Find_HOME / HOME_Is_Not_Set\n");
        }
        num= 1;
     }
    else if (!_stricmp(input, "temp")){                                      //IN RA LIST TEMP
        char *temp=NULL;
        temp = getenv("TEMP");
        if(temp!=NULL){
            printf("CUR_TEMP_:%s\n",temp);
        }
        else{
            printf("Cannot_Find_TEMP / TEMP_Is_Not_Set\n");
        }
        num= 1;
     }  
     else num=0;
    }
  return num;
}

void manager(PRC_inf_BGR *LIST[] , int *length){
    char inf[MAX_NUM];
    while (1)
    {
        printf( "  >>Manager_CMD...: ");
        fgets(inf , sizeof(inf), stdin);
        inf[strcspn(inf, "\n")] = 0;  // loại bỏ newline
        if(Exitt(inf)) break;

        if(_stricmp(inf , "list")==0){
            for(int i =0 ; i<(*length);i++){
                printf("%lu %s %s \n" ,LIST[i]->pi.dwProcessId , LIST[i]->name_prc , LIST[i]->active);
            }
            if((*length)==0) {
                printf("Empty_List...\n");
            }
            printf("Print_List_Sucessful...\n");
            continue;
        }
        else if (!_stricmp(inf , "kill")){
            printf("  ( Nhap_exit_De_Thoat ) ");
            printf("Press_Your_KILL_CMD_Name...>");
            char killinf[MAX_NUM];
            fgets(killinf , sizeof(killinf), stdin);
            killinf[strcspn(killinf, "\n")] = 0;
            if(Exitt(killinf)){
                printf("Exit_Kill\n");
                continue;
            }
            else{
                int flag=0;
                if(!strcmp(killinf,"all")){
                    for(int i =0 ; i<(*length);i++){
                        flag =1 ;
                        TerminateProcess(LIST[i]->pi.hProcess  ,0);
                        for(int j=i ; j<(*length)-1 ; j++){
                            LIST[j]= LIST[j+1];
                        }
                        LIST[(*length)-1]=NULL;
                        (*length)--;
                        i--;
                    }
                }
                else{
                for(int i =0 ; i<(*length);i++){
                    if(!strcmp(killinf,LIST[i]->name_prc)){
                        flag =1 ;
                        TerminateProcess(LIST[i]->pi.hProcess  ,0);
                        for(int j=i ; j<(*length)-1 ; j++){
                            LIST[j]= LIST[j+1];
                        }
                        LIST[(*length)-1]=NULL;
                        (*length)--;
                        i--;
                    }
                }
        }
            if(flag){
                printf("Kill_%s_Successful...\n", killinf);

            }
            else {
                printf("Cannot_Find_%s\n", killinf);
            }
            }
        }
         else if (!_stricmp(inf , "stop")){
            printf("  ( Nhap_exit_De_Thoat ) ");
            printf("Press_Your_STOP_CMD_Name...>");
            char stopinf[MAX_NUM];
            fgets(stopinf , sizeof(stopinf), stdin);
            stopinf[strcspn(stopinf, "\n")] = 0;
            if(Exitt(stopinf)){
                printf("Exit_Stop\n");
                continue;
            }
            else{
                int flag=0;
                if(!strcmp(stopinf,"all")){
                    for(int i =0 ; i<(*length);i++){
                        flag=1;
                        strcpy(LIST[i]->active,"unable");
                        DWORD PID = LIST[i]->pi.dwProcessId;
                        HANDLE snap= CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, PID);
                        THREADENTRY32 te;
                        te.dwSize=sizeof(te);
                        if(Thread32First(snap,&te)){
                            do{
                                if(te.th32OwnerProcessID==PID){
                                    HANDLE hThread =OpenThread(THREAD_SUSPEND_RESUME,FALSE,te.th32ThreadID);
                                    SuspendThread(hThread);
                                    CloseHandle(hThread);
                                 }
                             }while(Thread32Next(snap,&te));
                        }
                        CloseHandle(snap);
                     }
                }
                
                else{
                    for(int i =0 ; i<(*length);i++){
                        if(!strcmp(stopinf,LIST[i]->name_prc)){
                            flag=1;
                            strcpy(LIST[i]->active,"unable");
                            DWORD PID = LIST[i]->pi.dwProcessId;
                            HANDLE snap= CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, PID);
                            THREADENTRY32 te;
                            te.dwSize=sizeof(te);
                            if(Thread32First(snap,&te)){
                                do{
                                    if(te.th32OwnerProcessID==PID){
                                        HANDLE hThread =OpenThread(THREAD_SUSPEND_RESUME,FALSE,te.th32ThreadID);
                                        SuspendThread(hThread);
                                        CloseHandle(hThread);
                                    }
                                }while(Thread32Next(snap,&te));
                            }
                            CloseHandle(snap);
                        }
                    }
                }
            if(flag){
                printf("Stop_%s_Successfull...\n", stopinf);
            }
            else {
                printf("Cannot_Find_%s\n", stopinf);
            }
            }
        }
        else if (!_stricmp(inf , "resume")){
            printf("  ( Nhap_exit_De_Thoat ) ");
            printf("Press_Your_RESUME_CMD_Name...>");
            char resumeinf[MAX_NUM];
            fgets(resumeinf , sizeof(resumeinf), stdin);
            resumeinf[strcspn(resumeinf, "\n")] = 0;
            if(Exitt(resumeinf)){
                printf("Exit_Resume\n");            
                continue;
            }
            else{
                int flag=0;
                if(!strcmp(resumeinf,"all")){
                     for(int i =0 ; i<(*length);i++){
                        strcpy(LIST[i]->active,"enable");
                        flag=1;
                        DWORD PID = LIST[i]->pi.dwProcessId;
                        HANDLE snap= CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
                        THREADENTRY32 te;
                        te.dwSize=sizeof(te);
                        if(Thread32First(snap,&te)){
                            do{
                                if(te.th32OwnerProcessID==PID){
                                    HANDLE hThread =OpenThread(THREAD_SUSPEND_RESUME,FALSE,te.th32ThreadID);
                                    ResumeThread(hThread);
                                    CloseHandle(hThread);
                                }
                            }while(Thread32Next(snap,&te));
                        }
                        CloseHandle(snap);
                    }
                }
                else{
                     for(int i =0 ; i<(*length);i++){
                        if(!strcmp(resumeinf,LIST[i]->name_prc)){
                            strcpy(LIST[i]->active,"enable");
                        flag=1;
                            DWORD PID = LIST[i]->pi.dwProcessId;
                            HANDLE snap= CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
                            THREADENTRY32 te;
                            te.dwSize=sizeof(te);
                            if(Thread32First(snap,&te)){
                                do{
                                    if(te.th32OwnerProcessID==PID){
                                        HANDLE hThread =OpenThread(THREAD_SUSPEND_RESUME,FALSE,te.th32ThreadID);
                                        ResumeThread(hThread);
                                        CloseHandle(hThread);
                                }
                        }while(Thread32Next(snap,&te));
                        }
                        CloseHandle(snap);
                        }
                     }
                 }
               
            if(flag){
                printf("Resume_%s_Successfull...\n", resumeinf);

            }
            else {
                printf("Cannot_Find_%s\n", resumeinf);
            }
            }
        }
        else if (!_stricmp(inf, "help") || !_stricmp(inf, "giup_do")){       ///HELP
                printf("----------------------------------------------------------\n");
                printf("Cac lenh ban co the su dung:\n");
                printf("  - LIST               : Hien thi danh sach background process\n");
                printf("  - KILL->name_CMD     : Ket thuc tien trinh background\n");
                printf("  - RESUME->name_CMD   : Tiep tuc tien trinh background\n");
                printf("  - STOP->name_CMD     : Tam dung tien trinh background\n");
                printf("----------------------------------------------------------\n");
                continue;
           }
           else{
            printf("Cau_Lenh_Khong_Hop_Le...\n");
           }
    }
    return;
}

int NhapImput_R(PRC_inf_BGR *LIST[]) {
        char inf[MAX_NUM];
        int length =0 ;
        while (1) {
            printf("  >>Input_CMD....: ");
            if(fgets(inf, sizeof(inf),stdin)==NULL) break;
            inf[strcspn(inf, "\n")] = 0;
            char cmd[MAX_NUM];
            if(Exitt(inf)) break;
            
            if (!_stricmp(inf, "help") || !_stricmp(inf, "giup_do")){       ///HELP
                printf("----------------------------------------------------------\n");
                printf("Cac lenh ban co the su dung:\n");
                printf("  - EXIT / thoat       : Thoat khoi shell\n");
                printf("  - CMD                : Tien trinh khong chay background\n");
                printf("  - CMD&               : Tien trinh chay background\n");
                printf("  - LIST               : Danh sach goi y CMD\n");
                printf("----------------------------------------------------------\n");
                continue;
           }
           if (!_stricmp(inf, "listcmd") || !_stricmp(inf, "list_cmd") || !_stricmp(inf, "list") || !strcmp(inf, "Cmd")){       //list cmd
                printf("----------------------------------------------------------\n");
                printf("He thong / Quan ly Windows:\n");
                    printf("  - cmd.exe            : Command Prompt\n");
                    printf("  - powershell.exe     : PowerShell\n");
                    printf("  - taskmgr.exe        : Task Manager\n");
                    printf("  - explorer.exe       : File Explorer / Desktop\n");
                    printf("  - control.exe        : Control Panel\n");

                printf("\nUng dung do hoa / van phong:\n");
                    printf("  - calc.exe           : May Tinh\n");
                    printf("  - notepad.exe        : Notepad\n");
                    printf("  - mspaint.exe        : Paint\n");
                
                printf("----------------------------------------------------------\n");
                continue;
           }

            int n=(int)strlen(inf);
            if(n==0) continue;
            STARTUPINFO si;
            PROCESS_INFORMATION pi ;
            ZeroMemory(&si, sizeof(si));
            si.cb = sizeof(si);
            ZeroMemory(&pi, sizeof(pi));
            int background=0;
            DWORD flag =0 ;
            if(inf[n-1]=='&') {
                background =1;
                inf[strcspn(inf, "&")] =0;
            }
            strcpy(cmd, inf); 
            if(background) flag= CREATE_NEW_CONSOLE;
            if(CreateProcess(NULL , cmd , NULL , NULL, FALSE ,flag, NULL ,NULL ,&si ,&pi)){
                    if(!background) {
                        piInf=&pi;
                        WaitForSingleObject((pi).hProcess, INFINITE);
                        CloseHandle((pi).hProcess);
                        CloseHandle((pi).hThread);
                        printf("Close_Forground_Process\n");
                        piInf=NULL;
                        continue;
                    }
                    printf("%s\n", "Create_Sucessful....");
                    LIST[length] = malloc(sizeof(PRC_inf_BGR));
                    LIST[length]->pi=pi;
                    LIST[length]->background=1;
                    strcpy(LIST[length]->active,"enable");
                    strcpy(LIST[length]->name_prc , inf) ; 
                    length++ ;
                }
                else{
                    printf("%s\n", "Create_False...");
                    printf("%s\n", "Hay_Nhap_Lai_Lenh...");
                    continue;
                }
        }
        return length; 
    }

void HuongDan_Shell() {
    printf("========================================\n");
    printf("Chao mung den voi MY_SHELL\n");
    printf("Cac lenh ban co the su dung:\n");
    printf("  - INPUT   / nhap_lenh      : Nhap danh sach tien trinh(exit, cmd, list, help...)\n");
    printf("  - MANAGER / quan_ly        : Quan ly tien trinh (List, Kill, Stop, Resume...)\n");
    printf("  - SPECIAL / dac_biet       : Thuc hien lenh dac biet (exit, help, date, time, dir, temp, path, addpath...)\n");
    printf("  - EXIT                     : Thoat khoi shell\n");
    printf("  - HELP                     : Thong tin cac cau lenh\n");
    printf("========================================\n\n");
}
 
int main (){
    SetConsoleCtrlHandler(CtrlHandler, TRUE);
    char pass[MAX_NUM];
/* do {
    printf("Password : ");
    fgets(pass, sizeof(pass), stdin);
    pass[strcspn(pass, "\n")] = 0;
} while (_stricmp(pass, "tinyshell") != 0);
 */

    piInf=NULL;
    //signal(SIGINT,sigint_handle);
    HuongDan_Shell();
    PRC_inf_BGR *LIST[MAX_NUM];
    char inf[MAX_NUM];
    int length=0;
    while (1){
        printf("MY_SHELL......>");
        fgets(inf, sizeof(inf),stdin);
        inf[strcspn(inf,"\n")]=0;
        Exit_Shell(inf);
         if (!_stricmp(inf, "nhap_lenh") || !_stricmp(inf, "input")){
            printf("----------------------------------------------------------\n");
            (length)=NhapImput_R(LIST);
            printf("Length_List : %d\n",(length));
         }
          else if (!_stricmp(inf, "quan_ly") || !_stricmp(inf, "manager")){
            printf("----------------------------------------------------------\n");
            manager(LIST,&length);
         }
          else if (!_stricmp(inf, "dac_biet") || !_stricmp(inf, "special")){
            printf("----------------------------------------------------------\n");
            int t = special();
            if(t==0){
                printf("Khong_Lam_Gi_Ca\n");
            }
            else{
                printf("Xu_Ly_Thanh_Cong\n");
            }
         }
         else {
            continue;
         }
    }
    return 0;
}