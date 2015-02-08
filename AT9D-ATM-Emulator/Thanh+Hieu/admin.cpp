#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include<iostream.h>
#include<string.h>
#include <windows.h>
FILE *f;
char ddan[30];
void gotoxy(int x,int y)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE) ;
    COORD position = {x,y} ;
    SetConsoleCursorPosition(hStdout,position ) ;
}
char* getTime() 	// ham lay thong tin thoi gian hien tai
{
    time_t now = time(0);
    return asctime(localtime(&now));
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
void ktpass()
{
    int i;
    char pas[7],inpass[7] ;
    printf("Vui long nhap ma PIN ");
    getpin(inpass,7);
    f=fopen("pass.dat","rt");
    fgets(pas,7,f);
    while(strcmp(inpass,pas)!=0)
    {
        printf("Vui long nhap ma PIN ");
        getpin(inpass,7);
    }
}
void naptien()
{
    char b[50],d[30],s[30],ddan[30];
    unsigned long int a,c,tien;
    int n,e;
    printf("ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ\n");
    printf("Tai Khoan : ");
    fflush(stdin);
    gets(ddan);
    if((f = fopen(ddan, "rt")) == NULL)
    {
    	printf("Khong co tai khoan nay trong he thong.\n");
    }
    else
    {
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
    	printf("So du trong tai khoan con : %d \n",c);
    	printf("Nhap so tien can nap : ");
    	scanf("%d",&tien);
    	printf("ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ\n");
    	printf("Ban co muon nap so tien nay Y/N :");
    	scanf("%d",&e);
    	if ((e=getchar())=='y'||(e=getchar())=='Y')
    		{
        		if (tien>=50000)
        			{
            			printf(".........Dang thuc hien nap tien..........\n");
            			c=c+tien;
            			f=fopen(ddan,"wt");
            			fprintf(f,"%d\n",a);
            			fputs(s,f);
            			fputs(d,f);
            			fprintf(f,"%d\n",c);
            			fputs(getTime(),f);
            			fprintf(f,"%d",n);
            			fclose(f);
            			Sleep(2000);
            			printf(".....................Xong ................\n");
            			printf("              Da nap : %d\n",tien);
            			printf("              Tai khoan con: %d\n",c);
            			Sleep(2000);
       				}
        		else 
            		printf(" Phai nap tu 50.000 tro len\n");
    		}
   	}
   	printf("ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ\n");
    printf("Ban co muon tro ve menu Y/N: ");
    scanf("%d",&e);
    if ((e=getchar())=='y'||(e=getchar())=='Y');
    else
        exit(0);
}
void xoatk()
{
    int e;
    printf("Tai Khoan : ");
    fflush(stdin);
    gets(ddan);
    if((f = fopen(ddan, "rt")) == NULL)
    {
    	printf("            Tai khoan khong ton tai.\n");
    	
    }
	else
	{
		fclose(f);
   		printf("ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ\n");
    	printf("Ban co muon xoa tai khoan nay Y/N :");
    	scanf("%d",&e);
    		if ((e=getchar())=='y'||(e=getchar())=='Y')
    			{
    				printf("................Dang xoa tai khoan...............\n");
        			remove(ddan);
        			Sleep(2000);
        			printf(".......................Xong......................\n");
        			Sleep(2000);
    			}	
	};
	printf("ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ\n");
    printf("Ban co muon tro ve menu Y/N :");
    scanf("%d",&e);
    if ((e=getchar())=='y'||(e=getchar())=='Y');
    else exit(0);
}
void motk()
{
    char a[7],b[50],d[30],s[30],ddan[30];
    unsigned long c=50000;
    int n=0,e;
    printf("ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ\n");
    printf("Nhap tai khoan muon tao: ");
    fflush(stdin);
    gets(ddan);
    if((f = fopen(ddan, "rt")) == NULL)  
    		{
    			printf("Nhap ma PIN: ");
   				getpin(a,7);
    			printf("Nhap ten tai khoan: ");
    			fflush(stdin);
    			gets(s);
    			printf("Nhap so tai khoan : ");
    			fflush(stdin);
    			gets(d);
    			printf("ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ\n");
    			printf("Ban co muon tao tai khoan nay Y/N :");
    			scanf("%d",&e);
    			if ((e=getchar())=='y'||(e=getchar())=='Y');
    				{
        				printf("................Dang tao tai khoan...............\n");
        				f=fopen(ddan,"wt");
        				fputs(a,f);
        				fprintf(f,"\n");
        				fputs(s,f);
        				fprintf(f,"\n");
        				fputs(d,f);
        				fprintf(f,"\n");
        				fprintf(f,"%d\n",c);
        				fputs(getTime(),f);
        				fprintf(f,"%d",n);
        				fclose(f);
        				Sleep(2000);
        				printf("......................Xong ......................\n");
        				Sleep(2000);
   					};
    		}
	else 
		printf("            Tai khoan da ton tai.                \n");
    printf("ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ\n");
    printf("Ban co muon tro ve menu Y/N :");
    scanf("%d",&e);
    if ((e=getchar())=='y'||(e=getchar())=='Y');
    else exit(0);
}
void xemlichsu()
{
    char b[30],s[30],d[30],a[50],log[10]= {"log_"};
    unsigned long c;
    int e,i;
    printf("ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ\n");
    printf("Nhap tai khoan muon xem:");
    fflush(stdin);
    gets(ddan);
    f=fopen(strcat(log,ddan),"rt");
    while(!feof(f))
       {
        fgets(s,30,f);
        fscanf(f," ");
        fgets(d,30,f);
        fscanf(f," ");
        fgets(a,50,f);
        fscanf(f," ");
        fgets(b,30,f);
        fscanf(f," ");
        puts(s);
        puts(d);
        puts(a);
        puts(b);
        printf("ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ\n");
    }
    printf("Ban co muon tro ve menu Y/N :");
    scanf("%d",&e);
    if ((e=getchar())=='y'||(e=getchar())=='Y');
    else exit(0);

}
void mokhoatk()
{
	 char b[50],d[30],s[30],ddan[30];
     unsigned long  a,c,tien;
     int n=0,e;
	 printf("ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ\n");
	 printf("nhap tai khoan muon mo khoa :");
	 fflush(stdin);
	 gets(ddan);
	 f=fopen(ddan,"rt");
     fscanf(f,"%d",&a);
     fscanf(f," ");
     fgets(s,30,f);
     fgets(d,30,f);
     fscanf(f,"%d",&c);
     fscanf(f," ");
     fgets(b,30,f);
     fclose(f);
     printf("ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ\n");
	 printf("Ban co muon mo khoa tai khoan Y/N :");
	 scanf("%d",&e);
     if ((e=getchar())=='y'||(e=getchar())=='Y')
     {
     	printf(".........Dang thuc hien nap tien..........\n");
            f=fopen(ddan,"wt");
            fprintf(f,"%d\n",a);
            fputs(s,f);
            fputs(d,f);
            fprintf(f,"%d\n",c);
            fputs(getTime(),f);
            fprintf(f,"%d",n);
            fclose(f);
            Sleep(2000);
            printf("..............Xong ............\n");
            Sleep(2000);
     }
     else exit(0);
     printf("ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ\n");
	 printf("Ban co muon tro ve menu Y/N :");
     scanf("%d",&e);
    	if ((e=getchar())=='y'||(e=getchar())=='Y');
    	else exit(0);
}
main()
{
    int menu;
    printf("=================================================\n");
    printf("          NGAN HANG HOC VIEN KI THUAT MAT MA     \n");
    printf("-------------------------------------------------\n");
    printf("========================Admin====================\n");
    ktpass();
chon:
    system("cls");
    printf("=================================================\n");
    printf("         NGAN HANG HOC VIEN KI THUAT MAT MA      \n");
    printf("-------------------------------------------------\n");
    printf("=======================Admin=====================\n");
    printf("         Vui long chon cac muc sau day\n");
    printf("ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ\n");
    printf("||1.Nap Tien\n");
    printf("||2.Xoa Tai Khoan\n");
    printf("||3.Mo Tai Khoan\n");
    gotoxy(20,6);
    printf("||  4.Mo Khoa Tai Khoan    ||");
    gotoxy(20,7);
    printf("||  5.Xem Lich Su Giao Dich||");
    gotoxy(20,8);
    printf("||  0.Thoat                ||\n");
    printf("ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ\n");
    printf("CHON MUC TUONG UNG: ");
    scanf("%d",&menu);
    if (menu>=0&&menu<6)
    {
        switch(menu)
        {
        case 1:
            system("cls");
            printf("=================================================\n");
    		printf("          NGAN HANG HOC VIEN KI THUAT MAT MA     \n");
    		printf("-------------------------------------------------\n");
            printf("======================Nap Tien===================\n");
            naptien();
            goto chon;
            break;
        case 2:
            system("cls");
            printf("=================================================\n");
    		printf("          NGAN HANG HOC VIEN KI THUAT MAT MA     \n");
    		printf("-------------------------------------------------\n");
            printf("====================Xoa Tai Khoan================\n");
            xoatk();
            goto chon;
            break;
        case 3:
            system("cls");
            printf("=================================================\n");
    		printf("          NGAN HANG HOC VIEN KI THUAT MAT MA     \n");
    		printf("-------------------------------------------------\n");
            printf("===================Mo Tai Khoan==================\n");
            motk();
            goto chon;
            break;
        case 4:
            system("cls");
            printf("NGAN HANG HOC VIEN KI THUAT MAT MA\n");
            printf("----------------------------------\n");
            printf("==========Mo Khoa Tai Khoan========\n");
            mokhoatk();
            goto chon;
            break;
        case 5:
            system("cls");
            printf("NGAN HANG HOC VIEN KI THUAT MAT MA\n");
            printf("----------------------------------\n");
            printf("======Xem Lich Su Giao Dich=======\n");
            xemlichsu();
            goto chon;
            break;
        case 0:
            printf("Hen Gap Lai.\n");
            break;
        }
    }
    else
        goto chon;
}
