#include "stdio.h"
#include "string.h"
#include "stdlib.h"  
#include "stdbool.h"

struct SaveData
{
    char* saite[50];
    char* login[50];
    char* pswrd[50];
};

struct SaveData Shifrator(struct SaveData any, int n){
    char key[10];
    FILE* secret = fopen("secret.txt", "r");
    if(secret){
    for (int i = 0; i <9; i++)
    {   
        key[i] = fgetc(secret);
        
    }
    fclose(secret);
    for (int i = 0; i < n; i++) {
        for (int j = 0; any.login[i][j] != '\0'; j++) {
            if (any.login[i][j] >= '0' && any.login[i][j] <= '9' || any.login[i][j] >= 'a' && any.login[i][j] <= 'z') {
                any.login[i][j] = any.login[i][j] ^ (key[j] - 'A'); 
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; any.pswrd[i][j] != '\0'; j++) {
            if (any.pswrd[i][j] >= '0' && any.pswrd[i][j] <= '9' || any.pswrd[i][j] >= 'a' && any.pswrd[i][j] <= 'z') {
                any.pswrd[i][j] = any.pswrd[i][j] ^ (key[j] - 'A'); 
            }
        }
    }
    
    return any;
    }
    else{
        printf("Failed to open file, data wasn't encrypted.\n");
        struct SaveData blank;
        return blank;
    }

}

struct SaveData Deshifrator(struct SaveData any, int n, char* secword){
    char key[10];
    FILE* secret = fopen("secret.txt", "r");
    if(secret){
    for (int i = 0; i <9; i++)
    {   
        key[i] = fgetc(secret);
        
    }
    fclose(secret);
    int cnt =0;
    if(strcmp(key,secword)){
    for (int i = 0; i < n; i++) {
        for (int j = 0; any.login[i][j] != '\0'; j++) {
            any.login[i][j] = any.login[i][j] ^ (key[j] - 'A');
        }
    }
    for (int i = 0; i < n; i++) {
      for (int j = 0; any.pswrd[i][j] != '\0'; j++) {
            any.pswrd[i][j] = any.pswrd[i][j] ^ (key[j] - 'A'); 
        }
    }
    }
    return any;
    }
    else{
        printf("Failed to open file, data wasn't decrypted.\n");
        struct SaveData blank;
        return blank;
    }
}

void out2file(struct SaveData any, int n, FILE* output){
    for (int i = 0; i < n; i++)
        {   
            for (int j = 0; any.saite[i][j] != '\0'; j++) {
                putc(any.saite[i][j], output);
            }
            putc('\t',output);
        } 
    for (int i = 0; i < n; i++)
        {   
            for (int j = 0; any.login[i][j] != '\0'; j++) {
                putc(any.login[i][j], output);
            }
            putc('\t',output);
        } 
    for (int i = 0; i < n; i++)
        {   
            for (int j = 0; any.pswrd[i][j] != '\0'; j++) {
                putc(any.pswrd[i][j], output);
            }
            putc('\n',output);
        } 

}


void finding(struct SaveData any,char* site_to_find , FILE *input){
    char secword[10];
    printf("Enter keyword.\n");
    scanf("%s", secword);
    char line[300];
    while (fgets(line, sizeof(line), input)) {
        char site[100], login[100], pswrd[100];
        sscanf(line, "%s\t%s\t%s", site, login, pswrd);
        if (strcmp(site, site_to_find) == 0) {
            any.saite[0] = malloc(100 * sizeof(char));
            any.login[0] = malloc(100 * sizeof(char));
            any.pswrd[0] = malloc(100 * sizeof(char));
            strcpy(any.saite[0], site);
            strcpy(any.login[0], login);
            strcpy(any.pswrd[0], pswrd);
            
            any = Deshifrator(any, 1, secword);
            
            printf("Website: %s\n", any.saite[0]);
            printf("Login: %s\n", any.login[0]);
            printf("Password: %s\n", any.pswrd[0]);
            
            free(any.saite[0]);
            free(any.login[0]);
            free(any.pswrd[0]);
            break; 
        }
    }
}


char* generatepasw(int k){
    char *pw = malloc(k * sizeof(char)); 
    for (int i = 0; i < k-1; i++)
    {
        pw[i] = (char)(rand() % 92 + 33 );
    }
    pw[k] = '\0';
    return pw;
}

int main(){
    struct SaveData odyn;
    bool run = true;
    while(run == true){
        int k = 0;
        printf("What do u need?\n1.Eneter & encrypt data.\n2.Decrypt data.\n3.Exit.\n");
        scanf("%i", &k);
        switch (k)
        {
        case 1:
            int kol = 1;
            printf("Eneter data.\n");
            for (int i = 0; i < kol; i++) {
                odyn.saite[i] = malloc(100 * sizeof(char));
                odyn.login[i] = malloc(100 * sizeof(char));
                odyn.pswrd[i] = malloc(100 * sizeof(char));
                printf("Enter website.\n");
                scanf("%s", odyn.saite[i]);

                printf("Enter login.\n");
                scanf("%s", odyn.login[i]);

                int l=0;
                printf("Generate password or enter it yourself?\n1.Generate.\n2.Enter it yourself.\n");
                scanf("%i", &l);
                switch (l)
                {
                case 1:
                    printf("How long password do you need?\n");
                    int noc = 0;
                    scanf("%i", &noc);
                    char* pword = generatepasw(noc);
                    odyn.pswrd[i]  = pword;
                    break;
                case 2:
                    printf("Enter password.\n");
                    scanf("%s", odyn.pswrd[i]);
                    break;
                default:
                    printf("Enter password.\n");
                    scanf("%s", odyn.pswrd[i]);
                    break;
                }
            }
                FILE *output = fopen("base.txt", "a+"); 
                odyn = Shifrator(odyn, kol);
                if(output){
                    out2file(odyn,kol,output);
                }
                fclose(output);
                for (int i = 0; i < kol; i++) {
                    free(odyn.saite[i]);
                    free(odyn.login[i]);
                    free(odyn.pswrd[i]);
                }
                
            break;
        case 2:
            char site_to_find[100];
            printf("Enter website for decrypt:\n");
            scanf("%s", site_to_find);

            FILE* input = fopen("base.txt", "r");
            if (input) {
                finding(odyn,site_to_find,input);
                fclose(input);
            } 
            else {
                printf("Failed to open file.\n");
            }
            break;
        case 3:
            goto finish;
            break;
        default:
            goto finish;
            break;
        }
        printf("Continue?\n1.Yes.\n2.No.\n");
        k = 0;
        scanf("%i", &k);
        switch (k)
        {
        case 1:
            run = true;
            break;
        case 2:
            goto finish;
        default:
            goto finish;
            break;
        }
    
    }
    finish:
        run = false;
        return 0;
}

