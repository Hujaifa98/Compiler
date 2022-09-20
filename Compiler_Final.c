#include<stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
FILE *p1,*p2,*p3,*p4;
char c;

int errortype[100];
int errorline[100];
int errorcnt=0;
int newlinecnt[100];

void countinglex()
{
    int newline = 0;
    p4 = fopen("intermediate.txt","r");

    char kkk[50];
    int kk=0;

    newlinecnt[newline]=0;
    while((c = fgetc(p4))!=EOF)
    {
        if(c==',' || c==';' || c==' ' || c=='\n' || c=='(' || c==')' || c=='=' || c=='+' || c=='*' || c=='-' || c=='/' || c=='<' || c=='>' || c=='{' || c=='}' || c=='[' || c==']')
        {
            //printf("%s %c %d %d!\n",kkk,c,newline+1,newlinecnt[newline]);
            kkk[kk]='\0';
            if(kk!=0)
                newlinecnt[newline]++;
            if(c!='\n'){
                if(c!=' ')
                    newlinecnt[newline]++;
            }
            else
            {

                newline++;
                newlinecnt[newline]=0;
            }
            //printf("%s %c %d %d!\n",kkk,c,newline+1,newlinecnt[newline]);

            kk=0;
        }
        else
        {
            //printf("%c",c);
            kkk[kk++]=c;
        }

    }

    fclose(p4);
}

void errorDetection()
{


    int ifflag=0;
    int firstbrac=0,secbrac=0,thirdbrac=0;
    printf("\n\n");
    int line=1;
    printf("%d. ",line);

    p4 = fopen("intermediate.txt","r");
    p1 = fopen("intermediate2.txt","w");
    fputc(line+48,p1);
    fputs(". ",p1);
    //printf("!");
    char kkk[50];
    int kk=0;


    while((c = fgetc(p4))!=EOF)
    {
        if(c==',' || c==';' || c==' ' || c=='\n' || c=='(' || c==')' || c=='=' || c=='+' || c=='*' || c=='-' || c=='/' || c=='<' || c=='>' || c=='{' || c=='}' || c=='[' || c==']')
        {
            kkk[kk]='\0';
            //printf(" st %s en ",kkk);
            if(search2(kkk)!=-1)
            {
                printf("id ");
                fputs("id ",p1);
            }
            printf("%s",kkk);
            fputs(kkk,p1);

            if(c!='\n'){
                printf("%c",c);
                fputc(c,p1);

            }
            else
            {
                printf("%c",c);
                fputc(c,p1);
                line++;
                printf("%d. ",line);
                fputc(line+48,p1);
                fputs(". ",p1);


            }

            if(strcmp("if",kkk)==0){
                ifflag++;
                //printf("!");
            }
            if(strcmp("else",kkk)==0)
            {

                if(ifflag==0)
                {
                    //printf("!!");
                    errortype[errorcnt]=1;
                    errorline[errorcnt]=line;
                    errorcnt++;
                }
                else
                    ifflag--;
            }

            if(c=='(')
                firstbrac++;
            if(c==')')
            {
                if(firstbrac==0)
                {
                    errortype[errorcnt]=2;
                    errorline[errorcnt]=line;
                    errorcnt++;
                }
                else
                    firstbrac--;
            }

            if(c=='{')
                secbrac++;
            if(c=='}')
            {
                if(secbrac==0)
                {
                    errortype[errorcnt]=3;
                    errorline[errorcnt]=line;
                    errorcnt++;
                }
                else
                    secbrac--;
            }

             if(c=='[')
                thirdbrac++;
            if(c==']')
            {
                if(thirdbrac==0)
                {
                    errortype[errorcnt]=4;
                    errorline[errorcnt]=line;
                    errorcnt++;
                }
                else
                    thirdbrac--;
            }



            kk=0;
        }
        else
        {
            //printf("%c",c);
            kkk[kk++]=c;
        }

    }

    fclose(p4);
    fclose(p1);

    p1 = fopen("errors.txt","w");

    printf("\n\n");
    for(int i=0;i<errorcnt;i++)
    {
        if(errortype[i]==1)
        {
            printf("Unmatched 'else' at line %d,",errorline[i]);
            fputs("Unmatched 'else' at line",p1);
            fputc(errorline[i]+48,p1);
            fputs(", ",p1);
        }
        else if(errortype[i]==2)
        {
            printf("Misplaced ')' at line %d,",errorline[i]);
            fputs("Misplaced ')' at line",p1);
            fputc(errorline[i]+48,p1);
            fputs(", ",p1);
        }
        else if(errortype[i]==3)
        {
            printf("Misplaced '}' at line %d,",errorline[i]);
            fputs("Misplaced '}' at line",p1);
            fputc(errorline[i]+48,p1);
            fputs(", ",p1);
        }
        else if(errortype[i]==4)
        {
            printf("Misplaced '[' at line %d,",errorline[i]);
            fputs("Misplaced '[' at line",p1);
            fputc(errorline[i]+48,p1);
            fputs(", ",p1);
        }
        else if(errortype[i]==5)
        {
            printf("Undeclared identifier at line %d,",errorline[i]);
            fputs("Undeclared identifier at line",p1);
            fputc(errorline[i]+48,p1);
            fputs(", ",p1);
        }
        else if(errortype[i]==6)
        {
            printf("Duplicate identifier declaration at line %d,",errorline[i]);
            fputs("Duplicate identifier declaration at line",p1);
            fputc(errorline[i]+48,p1);
            fputs(", ",p1);
        }
    }
    printf("\n");
}

int tablecnt = 0,del=0;
struct table
{
    char * name;
    char * idType;
    char* dataType;
    char* scope;
    char* value;

}table1[100];

void insert(int ind,char* _name, char* _id,char* _dat,char* _scope,char* _value)
{
    table1[ind].name  =_name;
    table1[ind].idType= _id;
    table1[ind].dataType = _dat;
    table1[ind].scope  =_scope;
    table1[ind].value  =_value;
}

void display()
{
    int i=0;
    printf("\nSl. No.\t\tName\t\tId Type\t\tData Type\tScope\t\tValue\n");
    for(i=0;i<tablecnt;i++)
    {
        if(strcmp(table1[i].value,"-1")==0)
            continue;
        printf("%d\t\t%s\t\t%s\t\t%s\t\t%s\t\t%s\n",(i+1),table1[i].name,table1[i].idType,table1[i].dataType,table1[i].scope,table1[i].value);
    }
}



int search(char* _name,char* _id,char* _scope)
{
    int i=0;

    for(i=0;i<tablecnt;i++)
    {
        if(strcmp(table1[i].name,_name)==0 && strcmp(table1[i].idType,_id)==0 && strcmp(table1[i].scope,_scope)==0 )
        {
            return i;
        }
    }
    return -1;
}

int search2(char* _name)
{
    int i=0;

    //printf("st %s en",_name);
    for(i=0;i<tablecnt;i++)
    {
        //printf("! %s @ %s !",table1[i].name,_name);
        if(strcmp(table1[i].name,_name)==0)
        {
            return i;
        }
    }
    return -1;
}

char* chck(char * x)
{
    if(strlen(x)==0)
        return x;
    if(x[0]>='0' && x[0]<='9')
        return x;
    return "";
}

void dlete(int cur)
{
    update(cur,"-1");
    del++;
}

void update(int cur,char* val)
{
    table1[cur].value  = val;
}

void syntaxanalysis()
{
    int newline=0;
    char ar1[10000],ar2[10000],ar4[10000],ar3[1000][100];
    int indx[10000];
    int i,n,t,k,j,x=0,y=0,m;
    p1 = fopen("scannedcode.txt","r");
    i =0;
    while(fscanf(p1,"%c",&ar1[i])!=EOF)
    {
        i++;
    }
    ar1[i]  = '\0';
    fclose(p1);

    k=0;
    for(i=0;i<strlen(ar1);i++)
    {
        if(ar1[i]=='[')
        {
            ar2[k++]  = ar1[i++];
            j = 0;
            while(ar1[i]!=' ')
            {
                ar4[j++]  = ar1[i];
                i++;

            }
            ar4[j]  = '\0';
            if(strcmp(ar4,"id")==0)
            {
                ar2[k++]  = 'i';
                ar2[k++]  = 'd';
                ar2[k++]  = ' ';
            }
            i++;
            while(ar1[i]!=']')
            {
                ar2[k++]  = ar1[i];
                i++;

            }
            ar2[k++] =  ar1[i];

        }
    }
    ar2[k]  = '\0';
    /*printf("!\n");
    puts(ar2);*/

    p1 = fopen("keywordsfiltered.txt","w");
    fputs(ar2,p1);
    fclose(p1);

    k = 0;
    for(i=0;i<strlen(ar2);i++)
    {
        if(ar2[i]=='[')
        {
            j= 0;
            i++;
            while(ar2[i]!=']' && ar2[i]!=' ')
            {
                ar3[k][j++]  = ar2[i++];
            }
            ar3[k][j]  = '\0';
            k++;
            if(ar2[i]==' ')
            {
                j= 0;
                i++;
                while(ar2[i]!=']')
                {
                    ar3[k][j++]  = ar2[i++];
                }
                ar3[k][j]  = '\0';
                k++;
            }

        }
    }
    //printf("!!\n");

    int it = 0;
    char * scope = "global";
    for(i=0;i<k;i++)
    {
        //printf("%s %s\n",ar3[i],scope);
        //printf("%d %d\n",newline,newlinecnt[newline]);

        while(newlinecnt[newline]==0 && newline<50)
            newline++;

        //printf("%d %d!\n",newline,newlinecnt[newline]);
        //printf("%s %d\n",ar3[i],newline+1);
        newlinecnt[newline]--;
        if(strcmp(ar3[i],"id")==0)
        {
            //newlinecnt[newline]--;
            if(strcmp(ar3[i+2],"(")==0)
            {
                if(strcmp(ar3[i-1],"int")==0 || strcmp(ar3[i-1],"double")==0 || strcmp(ar3[i-1],"float")==0 || strcmp(ar3[i-1],"char")==0 )
                {
                    indx[it++]  = tablecnt;
                    insert(tablecnt++,ar3[i+1],"func",ar3[i-1],scope,"");
                    scope = ar3[i+1];
                    i+= 2;
                }
                else
                {
                    int pq  = search(ar3[i+1],"func","global");
                    if(pq!=-1)
                        indx[it++] = pq;
                    else {
                        printf("%s was not declared\n",ar3[i+1]);
                        errortype[errorcnt]=5;
                        errorline[errorcnt]=newline+2;
                        errorcnt++;
                    }
                    i+= 2;
                }
            }
            else if(strcmp(ar3[i+2],"=")==0)
            {

                if(strcmp(ar3[i-1],"int")==0 || strcmp(ar3[i-1],"double")==0 || strcmp(ar3[i-1],"float")==0 || strcmp(ar3[i-1],"char")==0 )
                {
                    if(search(ar3[i+1],"var",scope)==-1)
                    {
                        indx[it++]  = tablecnt;
                        insert(tablecnt++,ar3[i+1],"var",ar3[i-1],scope,chck(ar3[i+3]));
                    }
                    else
                    {
                        printf("%s is already declared in %s scope\n",ar3[i+1],scope);
                        errortype[errorcnt]=6;
                        errorline[errorcnt]=newline+2;
                        errorcnt++;
                    }
                }
                else
                {
                    int pq = search(ar3[i+1],"var",scope);
                    int qq = search(ar3[i+1],"var","global");
                    if(pq==-1 && qq==-1)
                    {
                        //printf("%d!!!!",tablecnt);
                        printf("%s is not declared\n",ar3[i+1]);
                        errortype[errorcnt]=5;
                        errorline[errorcnt]=newline+2;
                        errorcnt++;
                    }
                    else
                    {
                        update(pq,chck(ar3[i+3]));
                        indx[it++]  = pq;
                    }
                }
                i+=2;
            }
            else if(strcmp(ar3[i+2],";")==0 || strcmp(ar3[i+2],",")==0 || strcmp(ar3[i+2],")")==0 )
            {

                if(strcmp(ar3[i-1],"int")==0 || strcmp(ar3[i-1],"double")==0 || strcmp(ar3[i-1],"float")==0 || strcmp(ar3[i-1],"char")==0 )
                {
                    //printf("%s %s !!!!! ",ar3[i+1],scope);
                    if(search(ar3[i+1],"var",scope)==-1)
                    {
                        indx[it++]  = tablecnt;
                        insert(tablecnt++,ar3[i+1],"var",ar3[i-1],scope,"");
                    }
                    else{
                        printf("%s is already declared in %s scope\n",ar3[i+1],scope);
                        errortype[errorcnt]=6;
                        errorline[errorcnt]=newline+2;
                        errorcnt++;
                    }
                    i+= 2;
                }
                else
                {
                     //printf("%s %s @@@@ ",ar3[i+1],scope);
                    if(search(ar3[i+1],"var",scope)==-1 &&  search(ar3[i+1],"var","global")==-1)
                    {
                        printf("%s is not declared \n",ar3[i+1]);
                        errortype[errorcnt]=5;
                        errorline[errorcnt]=newline+2;
                        errorcnt++;
                    }
                    else indx[it++]  = search(ar3[i+1],"var",scope);
                    i+= 2;
                }
            }
        }
        else if(strcmp(ar3[i],"}")==0)
        {
            scope = "global";

        }


    }

    display();
    //dlete(3);
    //display();

    printf("\n\n");
    //printf("!!!!\n");

    p1 = fopen("syntaxanalysed.txt","w");
    it =0;
    for(i=0;i<strlen(ar2);i++)
    {
        if(ar2[i]=='[')
        {
            printf("%c",ar2[i]);
            fputc(ar2[i],p1);
            i++;
            while(ar2[i]!=']' && ar2[i]!=' ')
            {
                printf("%c",ar2[i]);
                fputc(ar2[i],p1);
                i++;
            }
            if(ar2[i]==' ')
            {
                printf("%c",ar2[i]);
                fputc(ar2[i],p1);
                j= 0;
                i++;
                while(ar2[i]!=']')
                {
                    i++;
                }
                fputc(indx[it]+1+48,p1);
                printf("%d",indx[it++]+1);
            }
            printf("%c",ar2[i]);
            fputc(ar2[i],p1);

        }
        else
        {
            printf("%c",ar2[i]);
        }
    }
    fclose(p1);

}

bool isDelimiter(char ch)
{
    if (ch == ' ' || ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == ',' || ch == ';' || ch == '>' || ch == '<' || ch == '=' || ch == '(' || ch == ')' || ch == '[' || ch == ']' || ch == '{' || ch == '}' || ch=='\'')
        return true;
    return false;
}

bool isOperator(char ch)
{
    if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '>' || ch == '<' || ch == '=')
        return true;
    return false;
}

bool isIdentifier(char* str)
{
    if (str[0] == '0' || str[0] == '1' || str[0] == '2' || str[0] == '3' || str[0] == '4' || str[0] == '5' || str[0] == '6' || str[0] == '7' || str[0] == '8' || str[0] == '9' || isDelimiter(str[0]) == true)
        return false;
    return true;
}

bool isKeyword(char* str)
{
    if (!strcmp(str, "if") || !strcmp(str, "else") || !strcmp(str, "while") || !strcmp(str, "do") || !strcmp(str, "break") ||
         !strcmp(str, "continue") || !strcmp(str, "int")
        || !strcmp(str, "double") || !strcmp(str, "float")
        || !strcmp(str, "return") || !strcmp(str, "char")
        || !strcmp(str, "case") || !strcmp(str, "char")
        || !strcmp(str, "sizeof") || !strcmp(str, "long")
        || !strcmp(str, "short") || !strcmp(str, "typedef")
        || !strcmp(str, "switch") || !strcmp(str, "unsigned")
        || !strcmp(str, "void") || !strcmp(str, "static")
        || !strcmp(str, "struct") || !strcmp(str, "goto")
        || !strcmp(str, "#include") || !strcmp(str, "stdio.h")
        || !strcmp(str, "stdbool.h") || !strcmp(str, "string.h")
        || !strcmp(str, "stdlib.h"))
        return true;
    return false;
}

bool isInteger(char* str)
{
    int i, len = strlen(str);

    if (len == 0)
        return false;
    for (i = 0; i < len; i++) {
        if (str[i] != '0' && str[i] != '1' && str[i] != '2' && str[i] != '3' && str[i] != '4' && str[i] != '5' && str[i] != '6'
            && str[i] != '7' && str[i] != '8' && str[i] != '9' || (str[i] == '-' && i > 0))
            return false;
    }
    return true;
}

bool isRealNumber(char* str)
{
    int i, len = strlen(str);
    bool hasDecimal = false;

    if (len == 0)
        return false;
    for (i = 0; i < len; i++) {
        if (str[i] != '0' && str[i] != '1' && str[i] != '2'
            && str[i] != '3' && str[i] != '4' && str[i] != '5'
            && str[i] != '6' && str[i] != '7' && str[i] != '8'
            && str[i] != '9' && str[i] != '.' ||
            (str[i] == '-' && i > 0))
            return false;
        if (str[i] == '.')
            hasDecimal = true;
    }
    return hasDecimal;
}

char* subString(char* str, int l, int r)
{
    int i;
    char* subStr = (char*)malloc(sizeof(char) * (r-l+2));

    for (i=l;i<=r;i++)
        subStr[i-l]=str[i];
    subStr[r-l+1] = '\0';
    return subStr;
}

void findlexemes(char* str)
{

    p3 = fopen("scannedcode.txt","w");
    //printf("!");

    int l=0, r=0, len = strlen(str);
    //printf("%d",len);
    while (r<=len && l<=r)
    {
        //printf("%d %d\n",l,r);
        //printf("%c %c\n",str[l],str[r]);
        if (isDelimiter(str[r]) == false)
            r++;
        //printf("%d %d\n",l,r);
        //printf("%c %c\n",str[l],str[r]);
        if (isDelimiter(str[r]) == true && l == r)
        {
            //printf("!");
            if (isOperator(str[r]) == true){
                if((str[r]=='<' || str[r]=='>') && str[r+1]=='='){
                  //printf("[op %c %c] ", str[r],str[r+1]);
                  fputs("[op ",p3);
                  fputc(str[r],p3);
                  fputc(str[r+1],p3);
                  fputs("] ",p3);
                  r+=2;
                  l=r;

                }
                else{
                    //printf("[op %c] ", str[r]);
                    fputs("[op ",p3);
                    fputc(str[r],p3);
                    fputs("] ",p3);
                    r++;
                    l =r;
                }

            }
            else if(str[r]=='(' || str[r]==')' || str[r]=='{' || str[r]=='}' || str[r]=='[' || str[r]==']'){
                //printf("[par %c] ",str[r]);
                fputs("[par ",p3);
                fputc(str[r],p3);
                fputs("] ",p3);
                r++;
                l =r;
            }
            else if(str[r]!=' '){
                //printf("[sep %c] ",str[r]);
                fputs("[sep ",p3);
                fputc(str[r],p3);
                fputs("] ",p3);
                r++;
                l =r;
            }
            else
            {
                r++;
                l =r;
            }
           // printf("@");

        }
        else if (isDelimiter(str[r]) == true && l != r || (r == len && l != r))
        {
            //printf("!!");
            char* subStr = subString(str, l, r-1);


            if (isKeyword(subStr) == true){
                //printf("[kw %s] ", subStr);
                fputs("[kw ",p3);
                fputs(subStr,p3);
                fputs("] ",p3);
            }

            else if (isInteger(subStr) == true){
                //printf("[num %s] ", subStr);
                fputs("[num ",p3);
                fputs(subStr,p3);
                fputs("] ",p3);
            }

            else if (isRealNumber(subStr) == true){
                //printf("[num %s] ", subStr);
                fputs("[num ",p3);
                fputs(subStr,p3);
                fputs("] ",p3);
            }

            else if (isIdentifier(subStr) == true && isDelimiter(str[r-1]) == false){
                //printf("[id %s] ", subStr);
                fputs("[id ",p3);
                fputs(subStr,p3);
                fputs("] ",p3);
            }

            else if (isIdentifier(subStr) == false && isDelimiter(str[r-1]) == false){
                //printf("[unkn %s] ", subStr);
                fputs("[unkn ",p3);
                fputs(subStr,p3);
                fputs("] ",p3);
            }
            l=r;
        }
    }
    fclose(p3);
    return;
}

void commentfilter()
{

    p3 = fopen("commentsfiltered.txt","w");

    p1 = fopen("code.txt","r");

    p2 = fopen("intermediate.txt","w");
    if(!p1)
    {
        printf("\nFile can't be opened!");
    }
    else
    {
        int flag=0;
        //printf("!\n");
        while((c = fgetc(p1))!=EOF)
        {
            //printf("!");

            if(c=='/' && flag==0)
                flag=1;
            else if(c=='/' && flag==1)
                flag=2;
            else if(c=='*' && flag==1)
                flag=3;
            else if(c=='*' && flag==3)
                flag=4;
            else if(c=='/' && flag==4)
                flag=-1;
            else if(c=='\n' && flag==2)
                flag=-1;
            if((flag==0) && c!='\n')
            {
                //printf("%c\n",c);
                fputc(c,p3);
                fputc(c,p2);
            }
            if(flag==-1)
                flag=0;
            //printf("%c %d\n",c,flag);
            if(c=='\n')
                fputc(c,p2);
        }
    }

    fclose(p1);
    fclose(p2);
    fclose(p3);
}

void spacefilter()
{

    p3 = fopen("spacefiltered.txt","w");

    p1 = fopen("commentsfiltered.txt","r");
    if(!p1)
    {
        printf("\nFile can't be opened!");
    }
    else
    {

        int flag=0;
        while((c = fgetc(p1))!=EOF)
        {

            if(c==' ' && flag==0)
                flag=1;
            else if(c==' ' && flag==1)
                flag=2;
            else
                flag=0;
            if(flag!=2)
            {

                fputc(c,p3);
            }
            //printf("%c %d\n",c,flag);
        }
    }

    fclose(p1);
    fclose(p3);
}




int main(void)
{


    p2 = fopen("code.txt","w");
    char ch;

    while(1)
    {
        scanf("%c",&ch);
        if(ch=='~')
            break;
        fputc(ch,p2);
    }
    fclose(p2);
    spacefilter();
    commentfilter();

    //printf("!");
    p3 = fopen("spacefiltered.txt","r");

    char str[100000];
    //printf("!");
    int i=0;
    if(!p3)
    {
        printf("\nFile can't be opened!");
    }
    else
    {

        while((c = fgetc(p3))!=EOF)
        {
            str[i]=c;
            i++;
        }
    }

    //printf("%d",i);

    fclose(p3);

    findlexemes(str);

    countinglex();

    syntaxanalysis();

    errorDetection();

    return 0;
}
