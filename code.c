#include<stdio.h>
#include<string.h>
#include<stdlib.h>
void main()
{
char add[50],label[50],mn[50],oper[50],slab[50],soper[50],sop[50],omn[50],osize[50],oop[50],op[50];
char nw[50],nww[50],nwo[50];
char start[50],str[50],opcode[50],omne[50],oadd[50],ooadd[50];
int i,j,l,leoc,len,count,count1,f,check,size;
char sstr[10],strg[10];

FILE *fp1,*fp2,*fp3;
FILE *fp5;
FILE *fp7;
FILE *fp4;
FILE *fp6;

fp1=fopen("Intermediate.txt","r");
fp2=fopen("Symtab.txt","r");
fp5=fopen("Length.txt","r");
fp4=fopen("Output.txt","w");
fp7=fopen("ObjectProgram.txt","w");
fp6=fopen("File.txt","w");
fscanf(fp1,"%s %s %s %s",add,label,mn,oper);
fscanf(fp5,"%x",&len);

if(strcmp(mn,"START")==0)
{
    strcpy(start,oper);
    fprintf(fp4,"%s\t%s\t%s\t%s\n",add,label,mn,oper);
    fprintf(fp7,"H^%s^%06s^%06x",label,start,len);
    fscanf(fp1,"%s %s %s %s",add,label,mn,oper);
}



while(strcmp(mn,"END")!=0)
{
    count=count1=0;
    fp3=fopen("optab.txt","r");
    while(!feof(fp3))
    {
        fscanf(fp3,"%s %s %s",omn,osize,oop);
        if(strcmp(mn,omn)==0)
        {
            count=1;
            strcpy(op,oop);
            break;
        }
    }
    fclose(fp3);

    if(count==1)
    {
        fp2=fopen("symtab.txt","r");
        for(;!feof(fp2);)
        {
            fscanf(fp2,"%s %s",slab,soper);
            if(strcmp(slab,oper)==0)
            {
            sprintf(nw,"%s%s",oop,soper);
            fprintf(fp6,"%s\t%s\t%s\n",add,mn,nw);
            fprintf(fp4,"%s\t%s\t%s\t%s\t%s\n",add,label,mn,oper,nw);
            break;
            }
        }
        fclose(fp2);
    }
            if(strcmp(mn,"WORD")==0)
            {
                int hex=atoi(oper);
                fprintf(fp6,"%s\t%s\t%06x\n",add,mn,hex);
                fprintf(fp4,"%s\t%s\t%s\t%s\t%06x\n",add,label,mn,oper,hex);
            }
            else if(strcmp(mn,"BYTE")==0)
            {
                l=strlen(oper);
                char b[3],p[3];
                b[0]='\0';
                p[0]='\0';
                for(i=2;i<(l-1);i++)
                {
                    p[0]=oper[i];
                    p[1]='\0';
                    strcat(b,p);
                }
                b[i]='\0';
                if(oper[0]=='X')
                {
                fprintf(fp6,"%s\t%s\t%s\n",add,mn,b);
                fprintf(fp4,"%s\t%s\t%s\t%s\t%s\n",add,label,mn,oper,b);
                }
                else if(oper[0]=='C')
                {
                fprintf(fp6,"%s\t%s\t%s\n",add,mn,"454F46");
                fprintf(fp4,"%s\t%s\t%s\t%s\t%s\n",add,label,mn,oper,"454F46");
                }
            }
    else if(strcmp(mn,"RSUB")==0)
    {
        fp3=fopen("optab.txt","r");
        for(;!feof(fp3);)
        {
            fscanf(fp3,"%s %s %s",omn,osize,oop);
            if(strcmp(mn,omn)==0)
            {
            strcpy(nwo,oop);
            fprintf(fp6,"%s\t%s\t%s0000\n",add,mn,oop);
            fprintf(fp4,"%s\t%s\t%s\t%s\t%s0000\n",add,label,mn,oper,nwo);
            }
        }
        fclose(fp3);
    }
    if((strcmp(mn,"RESW")==0)||(strcmp(mn,"RESB")==0))
    {
        fprintf(fp6,"%s\t%s\t%s\n",add,mn,"-");
        fprintf(fp4,"%s\t%s\t%s\t%s\n",add,label,mn,oper);
    }
    fscanf(fp1,"%s %s %s %s",add,label,mn,oper);

}
fprintf(fp6,"%s\t%s\t-\n",add,mn);
fclose(fp6);




fp6=fopen("file.txt","r");


for(;!feof(fp6);)
{
    if(strcmp(omne,"END")==0)
    {


    }

    check=0;

    while(!feof(fp6))
{

    if(check>0)
    {
        fprintf(fp7,"%x",check);

    }

fscanf(fp6,"%s %s %s",oadd,omne,opcode);
if((strcmp(omne,"RESW")==0 || strcmp(omne,"RESB")==0)|| strcmp(omne,"END")==0)
{

    check=0;
    break;
}



else if(check>27)
{
    check=0;
    break;
}
else
{

    if(check==0)
    {
        fprintf(fp7,"\nT^%06s^",oadd);

    }

    fprintf(fp7,"%s^",opcode);

    size=strlen(opcode)/2;
    check=check+size;

}

}
}
fclose(fp6);

fprintf(fp7,"\nE^%06s",start);

fclose(fp7);
fclose(fp1);
fclose(fp2);
fclose(fp4);
fclose(fp3);
fclose(fp5);
fclose(fp6);
}
