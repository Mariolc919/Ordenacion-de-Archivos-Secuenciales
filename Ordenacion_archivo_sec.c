#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define LONGITUD 16

int mezcla(FILE *fp1,FILE *fp2,FILE *fp3, int count);
void rebobin(FILE *fp1,FILE *fp2,FILE *fp3);

int main(int argc, char const *argv[]) {
  FILE *fp1, *fp2, *fp3;

    if((fp1 = fopen(argv[1],"r+")) == NULL){
      printf("No se puede abrir el fichero 1 %s\n",argv[1]);
      exit(0);
    }

    if((fp2 = fopen("ord1.txt","r+")) == NULL){
      printf("No se puede abrir el fichero 2\n");
      exit(0);
    }

    if((fp3 = fopen("ord2.txt","r+")) == NULL){
      printf("No se puede abrir el fichero 3\n");
      exit(0);
    }

    mezcla(fp1, fp2, fp3, LONGITUD);

    fclose(fp1);
    fclose(fp2);
    fclose(fp3);

  return 0;
}


int mezcla(FILE *fp1,FILE *fp2,FILE *fp3, int count){
  register int t, n, j, k, q;
  int x, y,  getx, gety;

  for(n = 1; n<count; n = n*2){

    /*Partir Fichero*/
    for(t=0;t<count/2;++t){
      if((getx = fgetc(fp1)) != EOF)
      fputc(getx,fp2);
    }//putc(int c, FIlLE *stream) escribe un caracter al flujo del fichero especificado
    //getc(FILE *stream) obtienes un caracter del flujo del archivo
    for(;t<count;++t){
      if((gety = fgetc(fp1)) != EOF)
      fputc(gety, fp3);
    }
    rebobin(fp1, fp2, fp3);

    for(q=0; q<count/2;q+=n){
      if((getx = fgetc(fp2)) != EOF)x = getx;
      if((gety = fgetc(fp3)) != EOF)y = gety;

      for(j=k=0;;){
        if(x<y){

          fputc(x, fp1);
          j++;
          if(j<n && (getx = fgetc(fp2)) != EOF) x = getx;
          else break;

        }else{
          fputc(y,fp1);
          k++;
          if(k<n && (gety = fgetc(fp3)) != EOF) y = gety;
          else break;
        }
      }
      if(j<n){
        fputc(x, fp1);
        j++;
      }
      if(k<n){
        fputc(y, fp1);
        k++;
      }
      for(;j<n;++j){
        if((getx = getc(fp2)) != EOF )
        fputc(getx,fp1);
      }
      for(;k<n;k++)
        if((gety = getc(fp3)) != EOF)
        fputc(gety, fp1);
    }
    rebobin(fp1,fp2,fp3);
  }
}

void rebobin(FILE *fp1,FILE *fp2,FILE *fp3){
  fseek(fp1, 0, SEEK_SET);
  fseek(fp2, 0, SEEK_SET);
  fseek(fp3, 0, SEEK_SET);
}
