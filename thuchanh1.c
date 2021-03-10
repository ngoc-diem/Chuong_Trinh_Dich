#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define max 1000
typedef struct list{
  char word[max];
  int num;//so lan xuat hien
  int dong[800];//vi tri xuat hien
  int sdong;//so vi tri xuat hien
}list;
int CheckNumber(char *s)//Neu la so return 1
{
 int co=0;
 for(int i=0;i<strlen(s);i++)
   {
     for(int j=48;j<=57;j++)
     {
     if(s[i]==j) co=1;
     
     }
   }
 return co;  
}
int stopwf(char *word,int num,char stopw[20][20])//Check cac tu khong co y nghia
{
    int t=0;
    for(int i =0; i<num; i++){
        if(strcmp(word,stopw[i])==0){
            t=1;
            break;
        }
       
    }
    return t;
}
void danhTuRieng(char *s){//Dua nhung tu ko la danh tu rieng ve in thuong
    for (int i = 2; i < strlen(s); i++)
    {
        if((s[i]>='A'&&s[i]<='Z')&&s[i-2]=='.'){
            s[i] += 32;
           

        }

    }
    

}
void themHoacDem(char *word,int dong, struct list *words, int *size, int num, char stopw[20][20]) {
	int i;
     
     int test=0;
	bool tonTai = false;
    if(CheckNumber(word)!=0 ||(word[0]>='A'&&word[0]<='Z') ){//Bo nhung tu la danh tu rieng va ky tu so
        
    }else{
        if(stopwf(word,num,stopw)==1){}//Bo cac tu vo nghia
        else{
        for(i = 0; i < *size; i++) {
		if(strcmp(word, words[i].word) == 0) {//Test xem tu da co trong list chua???
			words[i].num++;
            for (int k = 0; k < words[i].sdong; k++)
            {
                if(dong == words[i].dong[k])
                test =1;
            }
            if(test == 0){
                
                words[i].dong[words[i].sdong]=dong;
                words[i].sdong ++;
            }
			tonTai = true;
			break;
		}
        }
        if(!tonTai) {//Neu chua co thi them vao list
            
		strcpy(words[*size].word, word);
		words[*size].num = 1;
        words[*size].dong[words[*size].sdong]=dong;
        words[*size].sdong ++;
            
		(*size) ++;
	}
	}

	
	 
    }
   
}

void tachTu(char *s, int dong,struct list *words, int *size, int num, char stopw[20][20]) {//Tach dong thanh cac tu
	char *p;
	const char* delim = " \t\n,.?!;:()-";
	for(p = strtok(s, delim); p != NULL; p = strtok(NULL, delim)) {
		themHoacDem(p,dong, words, size,num, stopw);
	}
}


void hienThi(struct list* words, int size) {
	struct list t;
    //Sap Xep
       for (int i = 1; i < size; i++) {
      for (int j = 1; j < size; j++) {
         if (strcmp(words[j - 1].word, words[j].word) > 0) {
            t = words[j - 1];
            words[j - 1]=words[j];
            words[j]= t;
         }
      }
   }
	for(int i = 1; i < size; i++) {
		printf("%s : %d ", words[i].word, words[i].num);
        
        for (int j = 0; j < words[i].sdong; j++)
        {
            printf("%d ",words[i].dong[j]);

        }
        printf("\n");
        
	}
}

int main()
{
    FILE *f1,*f2;
    struct list *l;
    l = (list*) malloc(10000*sizeof(list));
    char str[4000][300];//luu cac dong
    char stopw[20][20];//danh sach tu vo nghia
    
    int num=0;//So tu vo nghia
    int d=0;//So dong trong file
    int size = 0 ;//so tu
    f1=fopen("alice30.txt","r+");
    
    if(f1==NULL)
	{
		printf("Cannot open file \n");
		return 0;
    }
    f2=fopen("stopw.txt","r+");
    
    if(f2==NULL)
	{
		printf("Cannot open file \n");
		return 0;
    }
    //tach dong
    while (!feof(f1))
    {

        fgets(str[d],200,f1);
        d++;
    }
    while (!feof(f2))
    {

        fscanf(f2,"%s\n",stopw[num]);
        num++;
    }
    
    for (int i = 0; i < d; i++)
    {
        danhTuRieng(str[i]);
    
        tachTu(str[i], i+1,l, &size,num,stopw);
       
    }
    
     
	 hienThi(l, size);
     
    fclose(f1);
    fclose(f2);

    return 0;
}

