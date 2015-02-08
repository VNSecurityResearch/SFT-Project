#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include <ctype.h>
typedef struct
{
    char soTk[15];
    char pin[7];
    char tenTk[30];
    unsigned int soDu;
    char trangThai[60];
    char time[30];
}
khachHang;
void sudung(char *dir);
void nhapthe(char *dir);
int main()
{
    char dir[30];
    nhapthe(dir);
    sudung(dir);
    return 0;
}
int docso(char* dir,int choice)  //ham xuat ra so tiep theo tu CSDL , dir la ten CSDL (nameATM.txt,soTk.txt)
{
    FILE *fp;
    fp = fopen(dir,"r+");//mo tep dir de ghi theo kieu van ban,gan tep dir voi con tro fp
    if (fp == NULL)  // neu nhu chua khoi tao thi khoi tao. gan gia tri dau tien bang 1
    {
        int result = 1;
        fp = fopen(dir,"w");
        if (choice == 1)
        {
            fprintf(fp,"\n%d",result);
        }
        fclose(fp);
        return result;
    }
    else
    {
        int i=0,result;
        char temp,number[20];
        fseek(fp,0,2);// chuyen con tro toi vi tri can thiet (dau ? cuoi)
        while((temp=fgetc(fp))!='\n')  //kiem tra vi tri cua so cuoi cung(fget doc 1 day ki tu)
        {
            fseek(fp,-2,1);
        }
        while(!feof(fp))//ham feof(fp) kiem tra cuoi tep fp
        {
            number[i++]=fgetc(fp); //quet so vao mang number
        }
        result = atoi(number) + 1;
        if (choice == 1)//chon 1
        {
            fprintf(fp,"\n%d",result);
        } // in gia tri ke tiep vao CSDL
        fclose(fp);
        return result;
    }
}
void taodau(char s[], int size)  // chuong trinh mat khau dau *
{
    char ch=0;
    memset(s,0,size);//sau memset() tat ca cac gia tri trong mang s deu duoc khoi tao va co cung 1 gia tri 0
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
                printf("%c ",ch);
                printf("%c",ch);
            }
        }
    }
    printf("\n");
    fflush(stdin);
}
char* duongdan(char* dir,int num)  //ham tao duong dan tu so lieu lay tu CSDL
{
    char temp[20];
    itoa(num,temp,10);
    strcpy(dir,"acc");
    strcat(dir,temp);
    strcat(dir,".dat");
}
void taosoTk(char* soTk,int num) 	//tao so tai khoan
{
    char temp[7];
    strcpy(soTk,"");				//tao so tai khoan
    itoa(num,temp,10);
    strcat(soTk,temp);
}
char* xuattg() 	// ham lay thong tin thoi gian hien tai
{
    time_t now = time(0);
    return asctime(localtime(&now));
}
void intttk(khachHang khach, int choice,char* trangThai) 	// ham in thong tin , neu choice = 1 thi in ra password
{
    printf("    So Tai Khoan            : %s\n",khach.soTk);	// tuy chon Trang Thai
    printf("    Ten Tai Khoan           : %s\n",khach.tenTk);
    if (choice == 1 || choice == 2)
    {
        printf("    Ma PIN                  : %s\n",khach.pin);
    }
    printf("    So Du                   : %d VND\n",khach.soDu);
    printf("    Trang Thai              : %s\n",trangThai);
    printf("    Thoi Gian               : %s\n",khach.time);
}
int	yesNo() 	// Chuong Trinh Kiem Tra YES NO, Neu Nhap y hoac Y thi tra ve 1, n hoac N
{
    char check;	// thi tra ve 0, nhap khac thi nhap lai
    int flag = 0;
    while(1)
    {
        check = getch();
        if(check == 'y' || check == 'Y')
            return 1;
        else if(check == 'n' || check == 'N')
            return 0;
    }
}
void animation() 		// tao hieu ung nhay chay theo 100ms ( dep mat )
{
    Sleep(100);
    system("cls");
    printf("\\");
    Sleep(100);
    system("cls");
    printf("|");
    Sleep(100);
    printf("/");
    system("cls");
    Sleep(100);
    system("cls");
    printf("-");
    Sleep(100);
    system("cls");
    printf("\\");
    Sleep(100);
    system("cls");
    printf("|");
    Sleep(100);
    system("cls");
    printf("/");
    system("cls");
    Sleep(100);
    system("cls");
    printf("-");
    Sleep(100);
    system("cls");
    Sleep(100);
    system("cls");
    printf("\\");
    Sleep(100);
    system("cls");
    printf("|");
    Sleep(100);
    printf("/");
    system("cls");
    Sleep(100);
    system("cls");
    printf("-");
    Sleep(100);
    system("cls");
    printf("\\");
    Sleep(100);
    system("cls");
    printf("|");
    Sleep(100);
    system("cls");
}
void inPhieu(char *dir,char* trangThai) 	// Chuong trinh in phieu
{
    FILE *fp;
    khachHang temp;
    fp = fopen(dir,"rb");
    fread(&temp,sizeof(temp),1,fp);
    fclose(fp);
    printf(" Ban Co Muon In Phieu? (Y/N)\n");
    if (yesNo() == 1)
    {
        printf("\n ..Dang In.");
        animation();
        printf("\n ..Xong........\n\n\n");
        intttk(temp,0,trangThai);
    }
    else return;
}
int taoacc() 	// ham tao tai khoan
{
    FILE *fp;
    char dir[30];
    khachHang khach,temp;
    int stt;
    duongdan(dir,stt=docso("CSDL.txt",1));		// tao ten duong dan  acc1.dat, acc2.dat ....
    taosoTk(khach.soTk,docso("CSDL.txt",0) - 1); //tao so tai khoan
    khach.soDu= 500000000;
Menu:
    printf("==================Ngan Hang Hoc Vien Mat Ma===========\n");
    printf("\n==================Tao Tai Khoan ATM==================\n");
    printf("\n Nhap Ho Ten : ");
    fflush(stdin);
    gets(khach.tenTk);
    printf("\n Nhap Ma PIN : ");
    while(1)
    {
        taodau(khach.pin,7);
        if(strlen(khach.pin) < 6)
        {
            printf("\n Khong Du 6 Chu So. Nhan Phim Bat Ky De Nhap Lai Ma PIN\n");
            getch();
            system("cls");
            printf("==================Ngan Hang Hoc Vien Mat Ma===========\n");
            printf("\n==================Tao Tai Khoan ATM==================\n");
            printf("\n Nhap Ho Ten : %s\n",khach.tenTk);
            printf("\n Nhap Ma PIN : ");
        }
        else
            break;
    }
    strcpy(khach.time,xuattg());
    printf("\n\n");
    strcpy(khach.trangThai,"Tao Tai Khoan");
    intttk(khach,1,khach.trangThai);
    printf("\n Dong Y Tao Tai Khoan ? (Y/N)\n");
    if(yesNo()==1) goto TaoTk;
    else
    {
        system("cls");
        goto Menu;
    }
TaoTk:
    fp=fopen(dir,"wb");
    fwrite(&khach,sizeof(khach),1,fp);
    fclose(fp);
    printf("\n Tao Tai Khoan Thanh Cong\n");
    getch();
    return stt;		//tra ve so thu tu cua file  acc1.dat thi stt = 1
}
void nhapthe(char *dir)     // ham nhap the ATM
{
    FILE *fp;
    int num,choice;
    khachHang khach;
Nhap:
    printf("===========Ngan Hang Hoc Vien Mat Ma=====\n");
    printf("\n-----------Dua The Vao-------------------\n");
    printf("\n#Nhap Ma So The : ");
    scanf("%d",&num);
    duongdan(dir,num);
    fp=fopen(dir,"rb");
    fread(&khach,sizeof(khach),1,fp);
    if(fp == NULL) 		//kiem tra xem da ton tai file chua
    {
        fclose(fp);
        printf("=====Ngan Hang Hoc Vien Mat Ma=====\n");
        printf("\nThe Chua Duoc Tao, Ban Muon :\n\n");
        printf("---1.Nhap Lai Ma So The Khac\n\n");
        printf("---2.Tao Tai Khoan Moi\n\n");
        printf("---3.Thoat Chuong Trinh\n\n");
        do
        {
            printf("#Chon : ");
            scanf("%d",&choice);
            if (choice == 1)
            {
                system("cls");
                goto Nhap;
            }
            else if (choice == 2)
            {
                system("cls");
                taoacc();
            }
            else if (choice == 3)
            {
                printf("\nXin Chao Va Hen Gap Lai\n");
                exit(0);
            }
            else
            {
                printf("\nNhap Sai, Nhan Phim Bat Ky De Nhap Lai\n\n");
                getch();
                system("cls");
                printf("========Ngan Hang Hoc Vien Mat Ma=====\n");
                printf("\n-------Dua The Vao------------\n");
                printf("\n#Nhap Ma So The : %d\n",num);
                printf("\nThe Chua Duoc Tao, Ban Muon :\n\n");
                printf("---1.Nhap Lai Ma So The Khac\n\n");
                printf("---2.Thoat Chuong Trinh\n\n");
            }
        }
        while(choice < 1 || choice > 2);
        return ;
    }
    else
    {
        char input[7];
        int dem=1;
        while(1)
        {
            if(dem>5)
            {
                printf("\n------------Nhap Ma Pin------------\n");
                printf("\nBan Nhap Sai Qua 5 Lan. \n");
                printf("\nChuong Trinh Tu Dong Thoat\n");
                fp = fopen(dir,"wb");
                fwrite(&khach,sizeof(khach),1,fp);
                fclose(fp);
                getch();
                exit(1);
            }
            printf("\n------------Nhap Ma Pin------------\n");
            dem++;
            printf("\nMa Pin : ");
            taodau(input,7);
            printf("\n");
            fread(&khach,sizeof(khach),1,fp);
            if(strcmp(input,khach.pin) != 0)
            {
                printf("Nhap Sai. Nhap Lai. Nhan Phim Bat Ki De Tiep Tuc");
                if(dem <= 5)
                {
                    getch();
                }
                system("cls");
                printf("==========Ngan Hang Hoc Vien Mat Ma=====\n");
                printf("\n----------Dua The Vao------------\n");
                printf("\n#Nhap Ma So The : %d\n",num);
            }
            else break;
        }
        fclose(fp);
    }
}
void inls(char *dir,khachHang temp)
{
    // in vao file lich su
    FILE *fp;
    char dirLog[30];
    strcpy(dirLog,dir);
    dirLog[strlen(dirLog) - 4] = NULL;
    strcat(dirLog,"_log.dat");
    fp = fopen(dirLog,"a+b");
    fwrite(&temp,sizeof(temp),1,fp);
    fclose(fp);
}// in vao file log
int xemls(char *dir) 	//diruser chi khi nao in userlog thi moi xai
{
    int num;
    FILE *fp;
    khachHang temp;
Nhap:
    system("cls");
    printf("================Ngan Hang Hoc Vien Mat Ma============\n");
    printf("\n================Xem Lich Su Giao Dich================\n");
    strcpy(dir,dir);
    dir[strlen(dir) - 4] = NULL;
    strcat(dir,"_log.dat");
    if((fp=fopen(dir,"rb")) == NULL)
    {
        fclose(fp);
        int choice;
        do
        {
            printf("\n Account Nay Chua Co lich su. Ban Muon\n");
            printf("\n ---1.Nhap Ma So The Khac\n");
            printf("\n ---2.Tro Ve Menu\n");
            printf("\n #Chon : ");
            fflush(stdin);
            scanf("%d",&choice);
            switch (choice)
            {
            case 1 :
                system("cls");
                goto Nhap;
                break;
            case 2 :
                return 0;
            default :
                system("cls");
                printf("\n====================Xem lich su=====================\n");
                printf("\n #Nhap Ma So The : %d\n",num);
                break;
            }
        }
        while(choice > 2 || choice < 1 );
    }
    else
    {
        printf("\n\n\n\n");
        while(fread(&temp,sizeof(temp),1,fp) == 1)
        {
            intttk(temp,2,temp.trangThai);
            printf("\n\n");
        }
        printf("\n Nhan Phim Bat Ky De Quay Ve Menu\n");
        getch();
        return 1;
    }
}
void kttk(char *dir)       // ham kiem tra tai khoan ATM, in ra cac thong tin
{
    FILE *fp;
    khachHang temp;
    fp = fopen(dir,"rb");
    fread(&temp,sizeof(temp),1,fp);
    fclose(fp);
    printf("================Ngan Hang Hoc Vien Mat Ma=========\n");
    printf("\n================Kiem Tra Tai Khoan================\n");
    printf("\n So Du Trong Tai Khoan : %d\n",temp.soDu);
    printf("\n Lan Giao Dich Gan Nhat : %s\n",temp.time);
    strcpy(temp.time,xuattg());
    sprintf(temp.trangThai,"Kiem Tra Tai Khoan");
    fp = fopen(dir,"wb");
    fwrite(&temp,sizeof(temp),1,fp);
    fclose(fp);
    inPhieu(dir,temp.trangThai);
    fclose(fp);
}
int rutTien(char *dir) 		// ham rut tien tai khoan ATM
{
    unsigned int tien;
    FILE *fp;
    khachHang temp;
    char tempTThai[50];
    fp = fopen(dir,"rb");
    fread(&temp,sizeof(temp),1,fp);
    fclose(fp);
    while(1) 	// kiem tra dieu kien
    {
        printf("=====================Ngan Hang Hoc Vien Mat Ma=====\n");
        printf("\n=====================Rut Tien======================\n");
        printf("\n Nhap So Tien Can Rut (Toi Thieu 10000) : ");
        scanf("%d",&tien);
        if(tien > temp.soDu) 		// so du nho hon thi nhap lai so tien can rut
        {
            printf("\n So Du Khong Du. Ban Co Muon Nhap Lai So Tien Muon Rut (Y/N)\n");
            if(yesNo() == 1)
            {
                system("cls");
                continue;
            }
            else
                return 0;
        }
        else if(tien < 10000) 		// so du nho hon 10000 thi nhap lai so tien can rut
        {
            printf("\n So Tien Ban Rut Qua It. Ban Co Muon Nhap Lai So Tien Muon Rut (Y/N)\n");
            if(yesNo() == 1)
            {
                system("cls");
                continue;
            }
            else
                return 0;
        }
        printf("\n Ban Co Muon Rut So Tien Nay (Y/N)\n");
        if(yesNo() == 1)
        {
            temp.soDu -= tien;
            strcpy(temp.time,xuattg());
            printf("\n ...Dang Thuc Hien Rut Tien.");
            fp = fopen(dir,"wb");
            fwrite(&temp,sizeof(temp),1,fp);
            fclose(fp);
            animation();
            printf("\n ...Xong........................\n");
            printf("\n So Du Trong Tai Khoan Cua Ban : %d\n",temp.soDu);
            printf("\n >> Nhan Tien : Nhan Mot Phim Bat Ky <<\n");
            getch();
            Sleep(500);
            printf("\n Moi Ban Nhan Tien\n");
            printf(" \n $%-10d\n\n",tien);
            sprintf(temp.trangThai,"Da Rut %dVND",tien);
            fp = fopen(dir,"wb");
            fwrite(&temp,sizeof(temp),1,fp);
            fclose(fp);
            inPhieu(dir,temp.trangThai);
            inls(dir,temp);
            break;
        }
        else
        {
            system("cls");
            continue;
        }
        return tien;
    }
}
int chuyenKhoan(char* dir) 		// chuyen khoan (tuong tu rut tien)
{
    int i;
    int num = 0;
    unsigned int tien;
    char desName[15],desDir[30],tempTThai[50];		// des = destination ( tai khoan can chuyen )
    FILE *fp;							// name la soTk, Dir la ten file, vd : acc1.dat
    khachHang temp,desTemp;				// temp la cua tai khoan chuyen, desTemp la tai khoan duoc chuyen
    fp = fopen(dir,"rb");				// ghi cac du lieu can thiet vao temp
    fread(&temp,sizeof(temp),1,fp);
    fclose(fp);
    printf("====================Ngan Hang Hoc Vien Mat Ma=======\n");
    printf("\n====================Chuyen Khoan====================\n");
    printf("\n So Du Trong Tai Khoan Cua Ban : %d\n",temp.soDu);
    while(1)
    {
        printf("\n Nhap Tai Khoan Muon Chuyen : ");
        fflush(stdin);
        gets(desName);
        num = atoi(desName);			//chuyen alpha thanh integer
        duongdan(desDir,num);			//tao duong dan (ten file) tu bien num
        if((fp=fopen(desDir,"rb")) == NULL) 		//kiem tra xem da ton tai file chua
        {
            fclose(fp);
            printf("\n The Khong Ton Tai. Nhan Phim Bat Ky De Nhap Lai\n");
            getch();
            system("cls");		// 2 dong nay de trinh bay dep mat them
            printf("\n====================Chuyen Khoan====================\n");
            printf(" So Du Trong Tai Khoan Cua Ban : %d\n",temp.soDu);
            continue;
        }
        else if(strcmp(desDir,dir)==0)
        {
            printf("\n The Duoc Chuyen Trung Voi The Chuyen Tien\n");
            printf("\n Nhan Phim Bat Ky De Nhap Lai\n");
            getch();
            system("cls");		// 2 dong nay de trinh bay dep mat them
            printf("\n====================Chuyen Khoan====================\n");
            printf(" So Du Trong Tai Khoan Cua Ban : %d\n",temp.soDu);
            continue;
        }
        else
        {
            fp = fopen(desDir,"rb");
            fread(&desTemp,sizeof(desTemp),1,fp);
            fclose(fp);
            break;
        }
    }
    while(1)
    {
        printf("\n Nhap So Tien Muon Chuyen (Toi Thieu 10000) : ");
        scanf("%d",&tien);
        if(tien > temp.soDu) 	// nhu ham rutTien
        {
            printf("\n So Du Khong Du. Ban Co Muon Nhap Lai So Tien Muon Chuyen (Y/N)\n");
            if(yesNo() == 1)
            {
                system("cls");
                continue;
            }
            else
                return 0;
        }
        else if(tien < 10000)
        {
            printf("\n So Tien Ban Muon Chuyen Qua It. Ban Co Muon Nhap Lai So Tien Muon Chuyen (Y/N)\n");
            if(yesNo() == 1)
            {
                system("cls");
                continue;
            }
            else
            {
                return 0;
            }
        }
        printf("\n Ban Co Muon Chuyen So Tien Nay (Y/N)\n");
        if(yesNo() == 1)
        {
            temp.soDu -= tien;
            strcpy(temp.time,xuattg());	//cap nhat du lieu cho tai khoan chuyen tien
            fp = fopen(dir,"wb");
            fwrite(&temp,sizeof(temp),1,fp);
            fclose(fp);
            desTemp.soDu += tien;				//cap nhat du lieu cho tai khoan duoc chuyen tien
            sprintf(desTemp.trangThai,"Da Nhan Tu Tai Khoan %s %dVND",temp.soTk,tien);
            inls(desDir,desTemp);
            printf("\n ...Dang Chuyen.");
            fp = fopen(desDir,"wb");
            fwrite(&desTemp,sizeof(desTemp),1,fp);
            fclose(fp);
            animation();
            printf("\n ...Xong............\n");
            printf("\n So Du Trong Tai Khoan Cua Ban : %d\n\n",temp.soDu);
            sprintf(temp.trangThai,"Da Chuyen Cho Tai Khoan %s %dVND",desTemp.soTk,tien);
            fp = fopen(dir,"wb");
            fwrite(&temp,sizeof(temp),1,fp);
            fclose(fp);
            inPhieu(dir,temp.trangThai);
            inls(dir,temp);
            break;
        }
        else
        {
            system("cls");
            continue;
        }
        return tien;
    }

}

void doiMaPin(char* dir)
{
    char mapinbandau[7],mapin[7],xacnhan[7];	//mapin va xacnhan... dung de xac nhan mat khau
    FILE *fp;
    khachHang temp;
    int dem = 1;
    fp = fopen(dir,"rb");
    fread(&temp,sizeof(temp),1,fp);		//doc cac gia tri tu file
    fclose(fp);
    strcpy(mapinbandau,temp.pin);
    while(1)
    {
        if(dem > 5) 		// dieu kien nhu o duoi
        {
            printf("\n Ban Da Nhap Sai Qua 5 Lan...\n");
            Sleep(1000);
            printf("\n Chuong Trinh Tu Dong Thoat...\n\n");
            exit(0);
        }
        printf("===================Ngan Hang Hoc Vien Mat Ma=====\n");
        printf("\n===================Doi Ma Pin====================\n");
        printf("\n Nhap Ma PIN Hien Tai : ");
        taodau(mapin,7);
        if(strcmp(mapin,temp.pin) != 0) 	// neu khong dung thi nhap lai
        {
            dem++;
            printf("\n Ma Pin Sai. Nhan Phim Bat Ky De Nhap Lai\n");
            getch();
            system("cls");
            continue;
        }
        else
        {
            while(1)
            {
                printf("\n Nhap Ma PIN Moi : ");
                taodau(mapin,7);
                if(strlen(mapin) < 6)
                {
                    printf("\n Ma Pin Phai Day Du 6 Chu So\n");
                    printf("\n Nhan Phim Bat Ky De Nhap Lai\n");
                    getch();
                    system("cls");
                    printf("\n===================Doi Ma Pin===================\n");
                    printf("\n Nhap Ma PIN Hien Tai : ******\n");
                    continue;
                }
                printf("\n Xac Nhan Ma PIN Moi : ");
                taodau(xacnhan,7);
                if(strcmp(mapin,xacnhan) != 0) 			// neu khong trung thi nhap lai
                {
                    printf("\n Ma Pin Khong Trung Khop. Nhan Phim Bat Ky De Nhap Lai\n");
                    getch();
                    system("cls");
                    printf("\n===================Doi Ma Pin===================\n");
                    printf("\n Nhap Ma PIN Hien Tai : ******\n");
                }
                else 									// trung thi doi ma pin
                {
                    printf("\n ...Dang Doi Ma Pin.");
                    animation();
                    strcpy(temp.pin,mapin);
                    strcpy(temp.time,xuattg());
                    fp = fopen(dir,"wb");
                    fwrite(&temp,sizeof(temp),1,fp);	//cap nhat ma pin cho file
                    fclose(fp);
                    printf("\n ...Xong................\n");
                    sprintf(temp.trangThai,"Doi Ma Pin Tu %s Sang %s",mapinbandau,temp.pin);
                    fp = fopen(dir,"wb");
                    fwrite(&temp,sizeof(temp),1,fp);
                    fclose(fp);
                    return;
                }
            }
        }
    }
}

void sudung(char *dir)
{
    FILE *fp;
    khachHang temp;
    fp = fopen(dir,"rb");
    fread(&temp,sizeof(temp),1,fp);		// doc cac thong tin tu file
    fclose(fp);
    int choice;				// bien lua chon switch case
    do
    {
        system("cls");
        printf("\n===Ngan Hang Hoc Vien Ky Thuat MM==\n");
        printf("\n$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
        printf("\n$  Xin Chao %-20s  $",temp.tenTk);
        printf("\n$                                 $");
        printf("\n$  1.Kiem Tra So Du Tai Khoan     $");
        printf("\n$                                 $");
        printf("\n$  2.Rut Tien                     $");
        printf("\n$                                 $");
        printf("\n$  3.Chuyen Khoan                 $");
        printf("\n$                                 $");
        printf("\n$  4.Doi Ma Pin                   $");
        printf("\n$                                 $");
        printf("\n$  5.Xem Lich Su Giao Dich        $");
        printf("\n$                                 $");
        printf("\n$  6.Thoat                        $");
        printf("\n$                                 $");
        printf("\n$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
        printf("\n#Chon : ");
        fflush(stdin);
        scanf("%d",&choice);
        switch (choice)
        {
        case 1 :
            system("cls");
            kttk(dir);
            printf("\n Ban Co Muon Thuc Hien Tiep Giao Dich (Y/N) \n");
            if(yesNo() == 1)
            {
                system("cls");
                choice = 0; // de quay ve menu, thoa dieu kien vong lap
                continue;
            }
            else
            {
                printf("\n Xin Chao Va Hen Gap Lai\n");
                getch();
                exit(0);		//thoat chuong trinh
                break;
            }
        case 2 :
            system("cls");
            rutTien(dir);
            printf("\n Ban Co Muon Thuc Hien Tiep Giao Dich (Y/N) \n");
            if(yesNo() == 1)
            {
                system("cls");
                choice = 0; // de quay ve menu
                continue;
            }
            else
            {
                printf("\n Xin Chao Va Hen Gap Lai\n");
                getch();
                exit(0);		//thoat chuong trinh
                break;
            }
        case 3 :
            system("cls");
            chuyenKhoan(dir);
            printf("\n Ban Co Muon Thuc Hien Tiep Giao Dich (Y/N) \n");
            if(yesNo() == 1)
            {
                system("cls");
                choice = 0; // de quay ve menu
                continue;
            }
            else
            {
                printf("\n Xin Chao Va Hen Gap Lai\n");
                getch();
                exit(0);		//thoat chuong trinh
                break;
            }
        case 4 :
            system("cls");
            doiMaPin(dir);
            printf("\n Ban Co Muon Thuc Hien Tiep Giao Dich (Y/N) \n");
            if(yesNo() == 1)
            {
                system("cls");
                choice = 0; // de quay ve menu
                continue;
            }
            else
            {
                printf("\n Xin Chao Va Hen Gap Lai\n");
                getch();
                exit(0);		//thoat chuong trinh
                break;
            }
        case 5 :
            system("cls");
            xemls(dir);
            printf("\n Ban Co Muon Thuc Hien Tiep Giao Dich (Y/N) \n");
            system("cls");
            choice = 0; // de quay ve menu
            continue;
        case 6 :
            printf("\nXin Chao Va Hen Gap Lai\n");
            getch();
            exit(0);		//thoat chuong trinh
            break;
        default:
            system("cls"); // xoa man hinh, nhap lai
            break;
        }
    }
    while (choice > 6 || choice < 1);
}
