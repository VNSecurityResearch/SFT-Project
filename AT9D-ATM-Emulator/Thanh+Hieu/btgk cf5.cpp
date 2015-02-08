#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include<iostream.h>
#include<string.h>
#include <windows.h>
#include <dos.h>
FILE *f;
FILE *fi;
FILE *fn;
char ddan[20],ten[30];
void gotoxy(int x,int y)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE) ;
    COORD position = {x,y} ;
    SetConsoleCursorPosition(hStdout,position ) ;
}
void getpin(char s[], int size)  // chuong trinh mat khau dau *
{
    char ch=0;
    memset(s,0,size);
    fflush(stdin);
    while (ch!=13)  //ch khác Enter
    {
        fflush(stdin);
        ch=getch();
        if (ch<=0)
            getch(); // loai bo cac ki tu dieu khien
        else if(ch>47 && ch<58)  //in cac ki tu so
        {
            if ((strlen(s))<size-1)  //neu chuoi chua day
            {
                printf("*");;
                s[strlen(s)]=ch;
            }
        }
        else if (ch==8)  //backspace.
        {
            if (s[0])  //neu chuoi khac rong
            {
                s[strlen(s)-1]=0; //xoa ki tu cuoi cung
                printf("%c ",ch); // |   xoa ki tu truoc do tren man hinh
                printf("%c",ch); //  |
            }
        }
    }
    printf("\n");
    fflush(stdin);
}
char* getTime() 	// ham lay thong tin thoi gian hien tai
{
    time_t now = time(0);
    return asctime(localtime(&now));
}
void inphieu()
{
    char b[30],d[30],s[30],g[30],m[40],log[10]= {"log_"};
    unsigned long  a,c;
    f=fopen(ddan,"rt");
    fscanf(f,"%d",&a);
    fscanf(f," ");
    fgets(s,30,f);
    fgets(d,30,f);
    fscanf(f,"%d",&c);
    fscanf(f," ");
    fgets(b,30,f);
    fclose(f);
    fi=fopen(strcat(log,ddan),"at");
    fputs(s,fi);
    fputs(d,fi);
    fputs("da giao dich so tien con lai:",fi);
    fprintf(fi,"%d\n",c);
    fputs(getTime(),fi);
    fclose(fi);
}
void password()//nhap password
{
    int i,a;
    char pas[7],inpass[7];
dualai:
    printf("       DUA THE VAO: ");
    gets(ddan);
    if((f = fopen(ddan, "rt")) == NULL)  // dua the vao
    {
        printf("ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ\n");
        printf("       THE KHONG HOP LE.\n");
        printf("ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ\n");
        goto dualai;
    }
    else
    {
        printf("ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ\n");
        printf("       THE HOP LE      \n");
        printf("ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ\n");
    }
    fclose(f);
    for (i=1; i<4; i++)
    {
        printf("       Vui long nhap ma PIN :");
        getpin(inpass,7);
        f=fopen(ddan,"rt");
        fgets(pas,7,f);
        fscanf(f," ");
        fgets(ten,30,f);
        fseek(f,-3,SEEK_END);
        fscanf(f,"%d",&a);
        fclose(f);
        if (strcmp(inpass,pas)==0&&a==0)
            break;
        else if(strcmp(inpass,pas)!=0&&a==0)
        {
            printf("     Ban da nhap sai %d lan.Vui long nhap lai\n",i);
            printf("ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ\n");
        }
        else
        {
            printf("       Tai khoan bi khoa\n");
            printf("ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ\n");
            goto dualai;
        }
    };
    if(i==4)
    {
        f=fopen(ddan,"at");
        fprintf(f,"\n");
        fprintf(f,"%d",1);
        fclose(f);
        printf("Ban da nhap sai qua 3 lan tai khoan  bi khoa.\n");
        goto dualai;
    }
}
void ktrasodutk()
{
    char b[50],d[30],s[30];
    unsigned long  a,c;
    int e;
    printf("ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ\n");
    f=fopen(ddan,"rt");
    fscanf(f,"%d",&a);
    fscanf(f," ");
    fgets(s,30,f);
    fgets(d,30,f);
    fscanf(f,"%d",&c);
    fscanf(f," ");
    fgets(b,30,f);
    fclose(f);
    printf("So du trong tai khoan: %d \n",c);
    printf("Lan giao dich gan nhat: %s \n",b);
    printf("ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ\n");
    printf("Ban co muon in phieu Y/N : ");
    scanf("%d",&e);
    if ((e=getchar())=='y'||(e=getchar())=='Y')
    {
        printf(".........Dang in..........\n");
        inphieu();
        printf(".........Xong..........\n");
    }
    printf("ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ\n");
    printf("Ban co muon thuc hien giao dich Y/N : ");
    scanf("%d",&e);
    if ((e=getchar())=='y'||(e=getchar())=='Y');
    else
        exit(0);
}
void ruttien()
{
    char b[50],d[30],s[30];
    unsigned long n,a,c;
    int e;
    unsigned long tien;
    printf("ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ\n");
    printf("Nhap so tien can rut : ");
    scanf("%d",&tien);
	printf("ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ\n");
    printf("Ban co muon rut so tien nay Y/N :");
    scanf("%d",&e);
    f=fopen(ddan,"rt");
    fscanf(f,"%d",&a);
    fscanf(f," ");
    fgets(s,30,f);
    fgets(d,30,f);
    fscanf(f,"%d",&c);
    fscanf(f," ");
    fgets(b,30,f);
    fseek(f,-3,SEEK_END);
    fscanf(f,"%d",&n);
    fclose(f);
    if ((e=getchar())=='y'||(e=getchar())=='Y')
    {
        if (tien<=c&&tien>=50000&&tien>0)
        {
            printf("............Dang thuc hien rut tien............\n");
            c=c-tien;
            f=fopen(ddan,"wt");
            fprintf(f,"%d\n",a);
            fputs(s,f);
            fputs(d,f);
            fprintf(f,"%d\n",c);
            fputs(getTime(),f);
            fprintf(f,"%d",n);
            fclose(f);
            Sleep(2000);
            printf(".......................Xong ...................\n");
            Sleep(2000);
            printf("So du trong tai khoan con : %d \n",c);
        }
        else if(tien>0)
        {
        	printf("khong thuc hien dc.(khong nhap so am ).\n");
        }
        else if (tien<50000&&tien<c)
        {
            printf("       Phai rut 50.000 tro len\n");
        }
        else
        {
            printf("       Tai khoan khong du\n");
        }
    }
    printf("ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ\n");
    printf("Ban co muon in phieu Y/N: ");
    scanf("%d",&e);
    if ((e=getchar())=='y'||(e=getchar())=='Y')
    {
        printf("...................dang in......................\n");
        inphieu();
        Sleep(2000);
        printf(".....................xong.......................\n");
        Sleep(2000);
    }
    printf("ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ\n");
    printf("Ban co muon thuc hien tiep giao dich Y/N: ");

    scanf("%d",&e);
    if ((e=getchar())=='y'||(e=getchar())=='Y');
    else
        exit(0);

}
void chuyentien ()
{
    FILE *ft;
    char b[30],d[30],s[30],g[30],ct[20],m[30],h[30];
    unsigned long n,a,c,o,k,l;
    int e;
    unsigned long tien;
    printf("ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ\n");
    f=fopen(ddan,"rt");
    fscanf(f,"%d",&a);
    fscanf(f," ");
    fgets(s,30,f);
    fgets(d,30,f);
    fscanf(f,"%d",&c);
    fscanf(f," ");
    fgets(b,30,f);
    fseek(f,-3,SEEK_END);
    fscanf(f,"%d",&n);
    fclose(f);
    printf("So du trong tai khoan con : %d\n",c);

    printf("Nhap tai khoan muon chuyen: ");
    fflush(stdin);
    gets(ct);
    while(((ft = fopen(ct, "rt")) == NULL))
    {
        printf("Tai khoan khong ton tai\n");
        printf("Nhap tai khoan muon chuyen: ");
        fflush(stdin);
        gets(ct);
    };
    fclose(ft);
    ft=fopen(ct,"rt");
    fscanf(ft,"%d",&o);
    fscanf(ft," ");
    fgets(g,30,ft);
    fgets(m,30,ft);
    fscanf(ft,"%d",&k);
    fscanf(ft," ");
    fgets(h,30,ft);
    fseek(ft,-3,SEEK_END);
    fscanf(ft,"%d",&l);
    fclose(ft);
    printf ("nhap so tien muon chuyen: ");
    scanf("%d",&tien);
    printf("ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ\n");
    printf("\n Ban co muon chuyen so tien nay Y/N :");
    scanf("%d",&e);
    if ((e=getchar())=='y'||(e=getchar())=='Y')
    {
        if (tien<=c&&tien>=50000)
        {
            printf ("...............Dang chuyen..............\n ");
            c=c-tien;
            k=k+tien;
            f=fopen(ddan,"wt");
            fprintf(f,"%d\n",a);
            fputs(s,f);
            fputs(d,f);
            fprintf(f,"%d\n",c);
            fputs(getTime(),f);
            fprintf(f,"%d",n);
            fclose(f);
            ft=fopen(ct,"wt");
            fprintf(ft,"%d\n",o);
            fputs(g,ft);
            fputs(m,ft);
            fprintf(ft,"%d\n",k);
            fputs(h,ft);
            fprintf(ft,"%d",l);
            fclose(ft);
            Sleep(2000);
            printf ("................Xong.................\n");
            Sleep(2000);
            printf ("So du trong tai khoan cua ban la : %d \n",c);

        }
        else if (tien<50000&&tien<c)
        {
            printf("Phai chuyen 50.000 tro len\n");
        }
        else
        {
            printf("Tai khoan khong du\n");
        }
    }
    printf("ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ\n");
    printf("Ban co muon in phieu Y/N :");
    scanf("%d",&e);
    if ((e=getchar())=='y'||(e=getchar())=='Y')
    {
        printf(".....................Dang in.....................\n");
        inphieu();
        Sleep(2000);
        printf("......................Xong........................\n");
        Sleep(2000);
    }
    printf("ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ\n");
    printf("Ban co muon thuc hien giao dich Y/N :");
    scanf("%d",&e);
    if ((e=getchar())=='y'||(e=getchar())=='Y');
    else
        exit(0);
}

void doipin()
{
    char m[10],a[7],b[30],d[30],s[30],pas[7],laipas[7],pasm[7];
    unsigned long  c;
    int n,e;
    printf("ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ\n");
    printf("Nhap ma PIN hien tai: ");
    getpin(pas,7);
    printf("Nhap ma PIN moi: ");
    getpin(pasm,7);
    printf("Nhap lai PIN moi : ");
    getpin(laipas,7);
    printf("ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ\n");
    printf("Nan co muon doi ma PIN (Y/N): ");
    scanf("%d",&e);
    if ((e=getchar())=='y'||(e=getchar())=='Y');
    {
        f=fopen(ddan,"rt");
        fgets(a,7,f);
        fgets(m,10,f);
        fgets(s,30,f);
        fgets(d,30,f);
        fscanf(f,"%d",&c);
        fscanf(f," ");
        fgets(b,30,f);
        fseek(f,-3,SEEK_END);
        fscanf(f,"%d",&n);
        fclose(f);
        if((strcmp(a,pas)==0)&&(strcmp(pasm,laipas)==0))
        {
            f=fopen(ddan,"wt");
            fputs(pasm,f);
            fputs(m,f);
            fputs(s,f);
            fputs(d,f);
            fprintf(f,"%d\n",c);
            fputs(getTime(),f);
            fseek(f,0,SEEK_END);
            fprintf(f,"%d",n);
            fclose(f);
            printf("           Da doi ma PIN.\n");
        }
        else
            printf("           Khong doi duoc \n");
    }
    printf("ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ\n");
    printf("Ban co muon giao dich tiep (Y/N): ");
    scanf("%d",&e);
    if ((e=getchar())=='y'||(e=getchar())=='Y');
    else
        exit(0);
}
main()
{
    int menu;
tiep:
    printf("=================================================\n");
    printf("         NGAN HANG HOC VIEN KI THUAT MAT MA      \n");
    printf("-------------------------------------------------\n");
    printf("           Vui long dua thong tin the vao\n");
    printf("ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ\n");
    password();
chon:
    system("cls");
    printf("=================================================\n");
    printf("         NGAN HANG HOC VIEN KI THUAT MAT MA      \n");
    printf("-------------------------------------------------\n");
    printf("====================Chao mung ===================\n");
    printf("                     %s      ",ten);
    printf("         Vui long chon cac muc sau day           \n");
    printf("ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ\n");
    printf("|| 1.Kiem tra so du tai khoan\n");
    printf("|| 2.Rut tien\n");
    gotoxy(24,7);
    printf("||  3.Chuyen khoan     ||\n");
    gotoxy(24,8);
    printf("||  4.Doi ma PIN       ||\n");
    printf("|| 0.Thoat              ||\n");
    printf("ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ\n");
    printf("CHON MUC TUONG UNG: ");
    scanf("%d",&menu);
    if (menu>=0&&menu<5)
    {
        switch(menu)
        {
        case 1:
            system("cls");
            printf("=================================================\n");
            printf("         NGAN HANG HOC VIEN KI THUAT MAT MA      \n");
            printf("-------------------------------------------------\n");
            printf("            Kiem tra so du tai khoan             \n");
            ktrasodutk();
            goto chon;
            break;
        case 2:
            system("cls");
            printf("=================================================\n");
            printf("         NGAN HANG HOC VIEN KI THUAT MAT MA      \n");
            printf("-------------------------------------------------\n");;
            printf("                    Rut tien                     \n");
            ruttien();
            goto chon;
            break;
        case 3:
            system("cls");
            printf("=================================================\n");
            printf("         NGAN HANG HOC VIEN KI THUAT MAT MA      \n");
            printf("-------------------------------------------------\n");
            printf("                  Chuyen khoan                   \n");
            chuyentien();
            goto chon;
            break;
        case 4:
            system("cls");
            printf("=================================================\n");
            printf("         NGAN HANG HOC VIEN KI THUAT MAT MA      \n");
            printf("-------------------------------------------------\n");
            printf("                   Doi ma PIN                    \n");
            doipin();
            goto chon;
            break;
        case 0:
            printf("                   Hen gap lai\n");
            break;
        default :
            printf("Loi nhap lai\n");
            break;
        }
    }
    else
        goto chon;
}
