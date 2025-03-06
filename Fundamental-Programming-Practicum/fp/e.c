#include <stdio.h>
#include <string.h>
#include <math.h>

int main(){
    int t, len;
    scanf("%d", &t); 

    char text[100];
    scanf("%s", text); 
 
    if (strlen(text)%t == 0) len = strlen(text);
    else len = strlen(text) + (t - (strlen(text)%t));
    
    int col = len/t;
    char arr[t][col];
    int dim = t*col;
    int empty = dim % strlen(text);
    
    int x = 0, get = t;

    for(int i = 0; i < t; i++, get--) {
        for(int j = 0; j < col; j++) {
            if(j == col-1 && get <= empty) break;
            else arr[i][j] = text[x++];
        }
    }

    for(int i = 0; i < t; i++){
        for(int j = 0; j < col; j++){
            if(arr[i][j] == '_') {
            arr[i][j] = ' ';
            }
        }
    }

    int length = 0;
    for(int j = 0; j < col; j++){
        for(int i = 0; i < t; i++, length++){
            if(length >= (int)strlen(text)) break;
            else if(arr[i][j] !='\0') printf("%c", arr[i][j]);
        }
    }
}