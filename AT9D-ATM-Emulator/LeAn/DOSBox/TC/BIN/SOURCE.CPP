#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <dos.h>
#include <dirent.h> // Thu vien kiem tra dir => liet ke danh sach file
#include <dir.h> // Thu vien de lay current dir
union REGS in,out; // Khai bao cho mouse

//Const phuc vu do hoa
char blank1[81] = "                                                                                ";
char blank2[30] = "                             ";

//Hien thi MS output -> input
int MaSoOutput[8];

//Func cho mouse
int Callmouse()
{
	in.x.ax=1;
	int86(51,&in,&out);
	return 1;
}
void Mousepos(int &xpos,int &ypos,int &click)
{
	in.x.ax=3;
	int86(51,&in,&out);
	click=out.x.bx;
	xpos=out.x.cx/8;
	ypos=out.x.dx/8;
}
int Mousehide()
{
	in.x.ax=2;
	int86(51,&in,&out);
	return 1;
}
void Setmousepos(int &xpos,int &ypos)
{
	in.x.ax=4;
	in.x.cx=xpos*8;
	in.x.dx=ypos*8;
	int86(51,&in,&out);
}
//Ket thuc

//Func xu ly du lieu
struct SinhVien
	{
		int MaSV;
		float DTB[11];
		char TenSV[100], DiaChi[100];
		struct SinhVien *next;
		struct SinhVien *back;
	};
typedef struct SinhVien *pointer;
pointer firstSV, DTBSort, SortPointer, FilterList;

//Function sap xep
void Sort()
{
	//Giai phong vung nho
	if (DTBSort != NULL)
	{
		while (DTBSort->next != NULL)
		{
			DTBSort = DTBSort->next;
			free(DTBSort->back);
		}
		free(DTBSort);
	}
	
	pointer p, q, newp;
	DTBSort = (pointer)malloc(sizeof(struct SinhVien));
	*DTBSort = *firstSV;
	DTBSort->next = NULL;
	DTBSort->back = NULL;
	
	p = FilterList->next;
	int kt;
	while (p != NULL)
	{
		kt = 0;
		q = DTBSort;
		if (p->DTB[10] >= q->DTB[10])
		{
			newp = (pointer)malloc(sizeof(struct SinhVien));
			*newp = *p;
			newp->next = DTBSort;
			newp->back = NULL;
			DTBSort->back = newp;
			DTBSort = newp;
			kt = 1;
		}
		while ((q->next != NULL) && (kt == 0))
		{
			q = q->next;
			if (p->DTB[10] >= q->DTB[10])
			{
				newp = (pointer)malloc(sizeof(struct SinhVien));
				*newp = *p;
				newp->next = q;
				newp->back = q->back;
				(q->back)->next = newp;
				q->back = newp;
				kt = 1;
				continue;
			}	
		}
		if (kt == 0)
		{
			newp = (pointer)malloc(sizeof(struct SinhVien));
			*newp = *p;
			newp->next = NULL;
			newp->back = q;
			q->next = newp;
			
		}
		p = p->next;
	}
}

void NhapFile(FILE *f)
{
	float TempFloat;
	int i;
	pointer p1, p2;
	//Giai phong vung nho truoc
	if (firstSV != NULL)
	{
		while (firstSV->next != NULL)
		{
			firstSV = firstSV->next;
			free(firstSV->back);
		}
		free(firstSV);
	}
	
	//Bat dau load du lieu
	firstSV = (pointer)malloc(sizeof(struct SinhVien));
	fscanf(f,"%d",&firstSV->MaSV);
	fgetc(f);//xuong hang
	fgets(firstSV->TenSV,100,f);
	fgets(firstSV->DiaChi,100,f);
	
	int HeSo;
	HeSo = 0;
	firstSV->DTB[10] = 0;
	for (i = 0; i < 10; i++)
	{
		fscanf(f,"%f", &TempFloat);
		firstSV->DTB[i] = TempFloat;
		if (firstSV->DTB[i] > -1)
		{
			firstSV->DTB[10] += firstSV->DTB[i];
			HeSo++;
		}
	}
	if (HeSo > 0)
	{
		firstSV->DTB[10] /= HeSo;
	}
	else
	{
		firstSV->DTB[10] = -1;
	}
	p1 = (pointer)malloc(sizeof(struct SinhVien));
	p1->back = firstSV;
	firstSV->next = p1;
	firstSV->back = NULL;
	
	while (fgetc(f) != EOF)
	{
		fscanf(f,"%d",&p1->MaSV);
		fgetc(f);//xuong hang
		fgets(p1->TenSV,100,f);
		fgets(p1->DiaChi,100,f);
		HeSo = 0;
		p1->DTB[10] = 0;
		for (i = 0; i < 10; i++)
		{
			fscanf(f,"%f", &TempFloat);
			p1->DTB[i] = TempFloat;
			if (p1->DTB[i] > -1)
			{
				p1->DTB[10] += p1->DTB[i];
				HeSo++;
			}
		}
		if (HeSo > 0)
		{
			p1->DTB[10] /= HeSo;
		}
		else
		{
			p1->DTB[10] = -1;
		}
		p2 = p1;
		p1 = (pointer)malloc(sizeof(struct SinhVien));
		p1->back = p2;
		p2->next = p1;
	}
	p2->next = NULL;
	free(p1);
	fclose(f);
	
	if (FilterList != NULL)
	{
		while (FilterList->next != NULL)
		{
			FilterList = FilterList->next;
			free(FilterList->back);
		}
		free(FilterList);
	}
	
	p1 = firstSV;
	FilterList = (pointer)malloc(sizeof(struct SinhVien));
	p2 = FilterList;
	*p2 = *firstSV;
	p2->back = NULL;
	
	p1 = p1->next;
	pointer newp;
	while (p1 != NULL)
	{
		newp = (pointer)malloc(sizeof(struct SinhVien));
		*newp = *p1;
		newp->back = p2;
		p2->next = newp;
		p2 = newp;
		
		p1 = p1->next;
	}
	
	Sort();
	SortPointer = FilterList;
}

void XuatFile(FILE *f)
{
	pointer p;
	int i;

	p = firstSV;
	while (p != NULL)
	{
		fprintf(f,"\n");
		fprintf(f,"\n");
		fprintf(f,"%d\n",p->MaSV);
		fprintf(f,"%s",p->TenSV);
		fprintf(f,"%s",p->DiaChi);
		for (i = 0; i < 9; i++)
		{
			fprintf(f,"%.1f ",p->DTB[i]);
		}
		fprintf(f,"%.1f",p->DTB[9]);
		p = p->next;
	}
	fclose(f);
}
//Ket thuc

//Func Giao dien
//Ham custom write
void Write(char *text, int Backgroundcolor, int Textcolor)
{
	textbackground(Backgroundcolor);
	textcolor(Textcolor);
	cprintf(text);
	textbackground(BLACK);

}

//Background (Menu + DATA)
void Menu()
{
	gotoxy(1,1);
	Write(" ³File",WHITE,BLACK);
	Write("³ ³Edit",WHITE,BLACK);
	Write("³ ³Filter³",WHITE,BLACK);
	Write("                                                         ",WHITE,WHITE);
	gotoxy(80,25);
}

// Menu file

// Duyet thu muc
void Display_All_Directories(char *searchstring, int page)
{
	int count = 0;
	DIR *directory_list;
	struct dirent *dentry;
	char buf[512];
	directory_list = opendir (searchstring);
	dentry = readdir (directory_list);
	dentry = readdir (directory_list);


	// Lay ten file dau tien
	int done;
	struct ffblk file;
	char filedir[512] = "";
	strcat(filedir,searchstring);
	strcat(filedir,"*.*");
	done = findfirst(filedir,&file,0);
	
	// Xuat thu muc
	dentry = readdir (directory_list);
	int result;
	result = strncmp(dentry->d_name, file.ff_name, 255);
	if ((dentry->d_name != NULL) && ( result != 0))
	{
		do
		{
			strcpy(buf,searchstring);
			strcat(buf, dentry->d_name);
			if ((count / 10) == (page - 1)) // Kiem soat PAGE Nao thi xuat dung file trong PAGE do.
			{
				gotoxy(3,7 + (count % 10));
				Write(dentry->d_name,CYAN,BLACK);
				Write("\\",CYAN,BLACK);
			}
			count++;
			dentry = readdir (directory_list);
			result = strncmp(dentry->d_name, file.ff_name, 255);
		}while ((dentry->d_name != NULL) && ( result != 0));
	}
	// Xuat file
	while(!done)
	{
			if ((count / 10) == (page - 1))
			{
				gotoxy(3,7 + (count % 10));
				Write(file.ff_name,CYAN,BLACK);
			}
		done = findnext(&file);
		count++;
	}
	closedir (directory_list);
}

//Choose File
char *WhatIsThatFile(char *searchstring, int SoThuTu, int *DirOrFile)
{
	int count = 0;
	DIR *directory_list;
	struct dirent *dentry;
	char buf[512];
	directory_list = opendir (searchstring);
	dentry = readdir (directory_list);
	dentry = readdir (directory_list);


	// Lay ten file dau tien
	int done;
	struct ffblk file;
	char filedir[512] = "";
	strcat(filedir,searchstring);
	strcat(filedir,"*.*");
	done = findfirst(filedir,&file,0);
	
	// Xuat thu muc
	dentry = readdir (directory_list);
	int result;
	result = strncmp(dentry->d_name, file.ff_name, 255);
	if ((dentry->d_name != NULL) && ( result != 0))
	{
		do
		{
			strcpy(buf,searchstring);
			strcat(buf, dentry->d_name);
			if (count == SoThuTu) 
			{
				*DirOrFile = 1;
				return dentry->d_name;
			}
			count++;
			dentry = readdir (directory_list);
			result = strncmp(dentry->d_name, file.ff_name, 255);
		}while ((dentry->d_name != NULL) && ( result != 0));
	}
	// Xuat file
	while(!done)
	{
			if (count == SoThuTu )
			{
				*DirOrFile = 2;
				return file.ff_name;
			}
		done = findnext(&file);
		count++;
	}
	closedir (directory_list);
}
//Load
void Load()
{
	Mousehide();
	clrscr();
	Menu();
	gotoxy(1,2);
	Write(" ÚÄLOADÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿ ",LIGHTGRAY,WHITE);
	gotoxy(1,3);
	Write(" ³ÚÄÄÄÄÄÄ¿                             ³ ",LIGHTGRAY,WHITE);
	gotoxy(1,4);
	Write(" ³³<=BACK³                             ³ ",LIGHTGRAY,WHITE);
	gotoxy(1,5);
	Write(" ³ÀÄÄÄÄÄÄÙ                             ³ ",LIGHTGRAY,WHITE);
	gotoxy(1,6);
	Write(" ³                                     ³ ",LIGHTGRAY,WHITE);
	gotoxy(1,7);
	Write(" ³                                     ³ ",LIGHTGRAY,WHITE);
	gotoxy(1,8);
	Write(" ³                                     ³ ",LIGHTGRAY,WHITE);
	gotoxy(1,9);
	Write(" ³                                     ³ ",LIGHTGRAY,WHITE);
	gotoxy(1,10);
	Write(" ³                                     ³ ",LIGHTGRAY,WHITE);
	gotoxy(1,11);
	Write(" ³                                     ³ ",LIGHTGRAY,WHITE);
	gotoxy(1,12);
	Write(" ³                             ÚÄÄÄÄÄÄ¿³ ",LIGHTGRAY,WHITE);
	gotoxy(1,13);
	Write(" ³                             ³ Load ³³ ",LIGHTGRAY,WHITE);
	gotoxy(1,14);
	Write(" ³                             ÀÄÄÄÄÄÄÙ³ ",LIGHTGRAY,WHITE);
	gotoxy(1,15);
	Write(" ³                             ÚÄÄÄÄÄÄ¿³ ",LIGHTGRAY,WHITE);
	gotoxy(1,16);
	Write(" ³                             ³Cancel³³ ",LIGHTGRAY,WHITE);
	gotoxy(1,17);
	Write(" ³                             ÀÄÄÄÄÄÄÙ³ ",LIGHTGRAY,WHITE);
	gotoxy(1,18);
	Write(" ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ ",LIGHTGRAY,WHITE);

	// lay current dir
	char currentdir[512];
	char currentdir_backup[512];
	getcwd(currentdir,512);
	strcat(currentdir,"\\");

	int cancel = 0, page = 1;
	char *pageSTRING;
	int x,y,cl;// Toa do + trang thai click chuot
	Callmouse();
	do
	{
		//BACKGROUND DATA
		gotoxy(3,6);
		Write("                                     ",LIGHTGRAY,LIGHTGRAY);
		gotoxy(3,6);
		Write("Address: ",LIGHTGRAY,BLACK);
		Write(currentdir,LIGHTGRAY,BLACK);
		
		gotoxy(3,7);
		Write(blank2,CYAN,CYAN);
		gotoxy(3,8);
		Write(blank2,CYAN,CYAN);
		gotoxy(3,9);
		Write(blank2,CYAN,CYAN);
		gotoxy(3,10);
		Write(blank2,CYAN,CYAN);
		gotoxy(3,11);
		Write(blank2,CYAN,CYAN);
		gotoxy(3,12);
		Write(blank2,CYAN,CYAN);
		gotoxy(3,13);
		Write(blank2,CYAN,CYAN);
		gotoxy(3,14);
		Write(blank2,CYAN,CYAN);
		gotoxy(3,15);
		Write(blank2,CYAN,CYAN);
		gotoxy(3,16);
		Write(blank2,CYAN,CYAN);
		gotoxy(3,17);
		Write(" <= Page ",LIGHTGRAY,WHITE);
		itoa(page,pageSTRING,10);
		Write(pageSTRING,LIGHTGRAY,BLACK);
		//Tinh toan so page co bao nhieu chu so de xet vi tri click chuot cua nut next page
		int nextbuttonpos = 0, temp = page;
		while (temp != 0)
		{
			nextbuttonpos++;
			temp /= 10;
		}
		//Ket thuc
		Write(" => ",LIGHTGRAY,WHITE);
		gotoxy(80,25);
		
		
		Display_All_Directories(currentdir, page);
		do
		{
			Mousepos(x,y,cl);
		}while (cl == 0);
		
		int DirOrFile = 0;
		char *WhatYouChoose;
		if (((y-5)*(y-16) < 0) && ((x-1)*(x-31) < 0))// Click vao bang folder va file
		{
			Mousehide();
			gotoxy(3,y+1);
			Write(blank2,GREEN,GREEN);
			gotoxy(3,y+1);
			WhatYouChoose = WhatIsThatFile(currentdir, (page-1)*10 + y-6, &DirOrFile);
			Write(WhatYouChoose,GREEN,WHITE);
			if (DirOrFile == 1)
			{
				Write("\\",GREEN,WHITE);
			}
			Callmouse();
			while (cl == 1)//Doi khi nao nha? chuot moi chay code
			{
				Mousepos(x,y,cl);
			}
			do // Sau khi chon file xem coi tiep theo click vao dau?
			{
				Mousepos(x,y,cl);
			}while (cl == 0);
			
		}
		if (((y-13)*(y-17) < 0) && ((x-30)*(x-39) < 0))// Cancel
		{
			while (cl == 1)//Doi khi nao nha? chuot moi chay code
			{
				Mousepos(x,y,cl);
			}
			cancel = 1;
		}
		if (((y-10)*(y-14) < 0) && ((x-30)*(x-39) < 0))// Load
		{
			while (cl == 1)//Doi khi nao nha? chuot moi chay code
			{
				Mousepos(x,y,cl);
			}
			strcpy(currentdir_backup,currentdir);//Luu backup lai truoc
			strcat(currentdir, WhatYouChoose);
			switch(DirOrFile)
			{
				case 1:
					strcat(currentdir,"\\");
					break;
   				case 2:
   					NhapFile(fopen(currentdir,"r"));
   					cancel = 1;
   					break;
    			case 0:
    				strcpy(currentdir,currentdir_backup);//Backup ...
    				break;
			}
		}
		if (((y-1)*(y-5) < 0) && ((x-1)*(x-10) < 0))// BACK
		{
			while (cl == 1)//Doi khi nao nha? chuot moi chay code
			{
				Mousepos(x,y,cl);
			}
   				char tempchar[512] = "";
   				int i = strlen(currentdir) - 2;
   				do
   				{
   					i--;
   				} while ((currentdir[i] != '\\') && (i > -1));
   				if (i != -1)
   				{
   					int j = 0;
   					do
   					{
   						tempchar[j] = currentdir[j];
   						j++;
					} while (j <= i);
					strcpy(currentdir,tempchar);
					page = 1;
				}
				
		}
		if ((y == 16) && ((x-2)*(x-5) < 0) && (page > 1))// Giam page
		{
			while (cl == 1)//Doi khi nao nha? chuot moi chay code
			{
				Mousepos(x,y,cl);
			}
			page--;
		}
		if ((y == 16) && ((x - (11 + nextbuttonpos))*(x - (14 + nextbuttonpos)) < 0))// Tang page
		{
			while (cl == 1)//Doi khi nao nha? chuot moi chay code
			{
				Mousepos(x,y,cl);
			}
			page++;
		}
	}while (cancel == 0);
}


//Save
void Save()
{
	Mousehide();
	clrscr();
	Menu();
	gotoxy(1,2);
	Write(" ÚÄSAVEÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿ ",LIGHTGRAY,WHITE);
	gotoxy(1,3);
	Write(" ³ÚÄÄÄÄÄÄ¿                             ³ ",LIGHTGRAY,WHITE);
	gotoxy(1,4);
	Write(" ³³<=BACK³                             ³ ",LIGHTGRAY,WHITE);
	gotoxy(1,5);
	Write(" ³ÀÄÄÄÄÄÄÙ                             ³ ",LIGHTGRAY,WHITE);
	gotoxy(1,6);
	Write(" ³                                     ³ ",LIGHTGRAY,WHITE);
	gotoxy(1,7);
	Write(" ³                                     ³ ",LIGHTGRAY,WHITE);
	gotoxy(1,8);
	Write(" ³                                     ³ ",LIGHTGRAY,WHITE);
	gotoxy(1,9);
	Write(" ³                                     ³ ",LIGHTGRAY,WHITE);
	gotoxy(1,10);
	Write(" ³                                     ³ ",LIGHTGRAY,WHITE);
	gotoxy(1,11);
	Write(" ³                                     ³ ",LIGHTGRAY,WHITE);
	gotoxy(1,12);
	Write(" ³                             ÚÄÄÄÄÄÄ¿³ ",LIGHTGRAY,WHITE);
	gotoxy(1,13);
	Write(" ³                             ³ Save ³³ ",LIGHTGRAY,WHITE);
	gotoxy(1,14);
	Write(" ³                             ÀÄÄÄÄÄÄÙ³ ",LIGHTGRAY,WHITE);
	gotoxy(1,15);
	Write(" ³                             ÚÄÄÄÄÄÄ¿³ ",LIGHTGRAY,WHITE);
	gotoxy(1,16);
	Write(" ³                             ³Cancel³³ ",LIGHTGRAY,WHITE);
	gotoxy(1,17);
	Write(" ³                             ÀÄÄÄÄÄÄÙ³ ",LIGHTGRAY,WHITE);
	gotoxy(1,18);
	Write(" ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ ",LIGHTGRAY,WHITE);

	// lay current dir
	char currentdir[512];
	char currentdir_backup[512];
	getcwd(currentdir,512);
	strcat(currentdir,"\\");

	int cancel = 0, page = 1;
	char *pageSTRING;
	int x,y,cl;// Toa do + trang thai click chuot
	Callmouse();
	do
	{
		//BACKGROUND DATA
		gotoxy(3,6);
		Write("                                     ",LIGHTGRAY,BLACK);
		gotoxy(3,6);
		Write("Address: ",LIGHTGRAY,BLACK);
		Write(currentdir,LIGHTGRAY,BLACK);
		
		gotoxy(3,7);
		Write(blank2,CYAN,CYAN);
		gotoxy(3,8);
		Write(blank2,CYAN,CYAN);
		gotoxy(3,9);
		Write(blank2,CYAN,CYAN);
		gotoxy(3,10);
		Write(blank2,CYAN,CYAN);
		gotoxy(3,11);
		Write(blank2,CYAN,CYAN);
		gotoxy(3,12);
		Write(blank2,CYAN,CYAN);
		gotoxy(3,13);
		Write(blank2,CYAN,CYAN);
		gotoxy(3,14);
		Write(blank2,CYAN,CYAN);
		gotoxy(3,15);
		Write(blank2,CYAN,CYAN);
		gotoxy(3,16);
		Write(blank2,CYAN,CYAN);
		gotoxy(3,17);
		Write(" <= Page ",LIGHTGRAY,WHITE);
		itoa(page,pageSTRING,10);
		Write(pageSTRING,LIGHTGRAY,BLACK);
		//Tinh toan so page co bao nhieu chu so de xet vi tri click chuot cua nut next page
		int nextbuttonpos = 0, temp = page;
		while (temp != 0)
		{
			nextbuttonpos++;
			temp /= 10;
		}
		//Ket thuc
		Write(" => ",LIGHTGRAY,WHITE);
		gotoxy(80,25);
		
		
		Display_All_Directories(currentdir, page);
		do
		{
			Mousepos(x,y,cl);
		}while (cl == 0);
		
		int DirOrFile = 0;
		char *WhatYouChoose;
		
		if (((y-5)*(y-16) < 0) && ((x-1)*(x-31) < 0))// Click vao bang folder va file
		{
			Mousehide();
			gotoxy(3,y+1);
			Write(blank2,GREEN,GREEN);
			gotoxy(3,y+1);
			WhatYouChoose = WhatIsThatFile(currentdir, (page-1)*10 + y-6, &DirOrFile);
			Write(WhatYouChoose,GREEN,WHITE);
			if (DirOrFile == 1)
			{
				Write("\\",GREEN,WHITE);
			}
			Callmouse();
			while (cl == 1)//Doi khi nao nha? chuot moi chay code
			{
				Mousepos(x,y,cl);
			}
			do // Sau khi chon file xem coi tiep theo click vao dau?
			{
				Mousepos(x,y,cl);
			}while (cl == 0);
			
		}
		if (((y-13)*(y-17) < 0) && ((x-30)*(x-39) < 0))// Cancel
		{
			while (cl == 1)//Doi khi nao nha? chuot moi chay code
			{
				Mousepos(x,y,cl);
			}
			cancel = 1;
		}
		if (((y-10)*(y-14) < 0) && ((x-30)*(x-39) < 0))// SAVE
		{
			while (cl == 1)//Doi khi nao nha? chuot moi chay code
			{
				Mousepos(x,y,cl);
			}
			strcpy(currentdir_backup,currentdir);//Luu backup lai truoc
			strcat(currentdir, WhatYouChoose);
			switch(DirOrFile)
			{
				case 1:
					strcat(currentdir,"\\");
					break;
   				case 2:
   					XuatFile(fopen(currentdir,"w"));
   					cancel = 1;
   					break;
    			case 0:
    				strcpy(currentdir,currentdir_backup);//Backup ...
    				gotoxy(12 + strlen(currentdir) ,6);
    				scanf("%s", WhatYouChoose);
    				strcat(currentdir, WhatYouChoose);
    				XuatFile(fopen(currentdir,"w"));
    				cancel = 1;
    				break;
			}
		}
		if (((y-1)*(y-5) < 0) && ((x-1)*(x-10) < 0))// BACK
		{
			while (cl == 1)//Doi khi nao nha? chuot moi chay code
			{
				Mousepos(x,y,cl);
			}
   				char tempchar[512] = "";
   				int i = strlen(currentdir) - 2;
   				do
   				{
   					i--;
   				} while ((currentdir[i] != '\\') && (i > -1));
   				if (i != -1)
   				{
   					int j = 0;
   					do
   					{
   						tempchar[j] = currentdir[j];
   						j++;
					} while (j <= i);
					strcpy(currentdir,tempchar);
					page = 1;
				}
				
		}
		if ((y == 16) && ((x-2)*(x-5) < 0) && (page > 1))// Giam page
		{
			while (cl == 1)//Doi khi nao nha? chuot moi chay code
			{
				Mousepos(x,y,cl);
			}
			page--;
		}
		if ((y == 16) && ((x - (11 + nextbuttonpos))*(x - (14 + nextbuttonpos)) < 0))// Tang page
		{
			while (cl == 1)//Doi khi nao nha? chuot moi chay code
			{
				Mousepos(x,y,cl);
			}
			page++;
		}
	}while (cancel == 0);
}

void New()
{
	if (firstSV != NULL)
	{
		while (firstSV->next != NULL)
		{
			firstSV = firstSV->next;
			free(firstSV->back);
		}
		free(firstSV);
	}
	
	if (FilterList != NULL)
	{
		while (FilterList->next != NULL)
		{
			FilterList = FilterList->next;
			free(FilterList->back);
		}
		free(FilterList);
	}

	if (DTBSort != NULL)
	{
		while (DTBSort->next != NULL)
		{
			DTBSort = DTBSort->next;
			free(DTBSort->back);
		}
		free(DTBSort);
	}
	
	firstSV = NULL;
	FilterList = NULL;
	DTBSort = NULL;		
	SortPointer = NULL;
}





void File()
{
	gotoxy(3,1);
	Write("File",WHITE,RED);
	gotoxy(1,2);
	Write(" ÚÄÄÄÄÄÄ¿ ",WHITE,BLACK);
	gotoxy(1,3);
	Write(" ³ New  ³ ",WHITE,BLACK);
	gotoxy(1,4);
	Write(" ³ Load ³ ",WHITE,BLACK);
	gotoxy(1,5);
	Write(" ³ Save ³ ",WHITE,BLACK);
	gotoxy(1,6);
	Write(" ³ Exit ³ ",WHITE,BLACK);
	gotoxy(1,7);
	Write(" ÀÄÄÄÄÄÄÙ ",WHITE,BLACK);
	gotoxy(80,25);

	//Chon Load hoac Save hoac Exit
	int x,y,cl;// Toa do + trang thai click chuot
	Callmouse();
	do
	{
		Mousepos(x,y,cl);
	}while (cl == 0);
	if ((y == 2) && ((x-2)*(x-7) < 0))// Load
	{
		while (cl == 1)//Doi khi nao nha? chuot moi chay code
		{
			Mousepos(x,y,cl);
		}
		New();
	}
	if ((y == 3) && ((x-2)*(x-7) < 0))// Load
	{
		while (cl == 1)//Doi khi nao nha? chuot moi chay code
		{
			Mousepos(x,y,cl);
		}
		Load();
	}
	if ((y == 4) && ((x-2)*(x-7) < 0))// Save
	{
		while (cl == 1)//Doi khi nao nha? chuot moi chay code
		{
			Mousepos(x,y,cl);
		}
		Save();
	}
	if ((y == 5) && ((x-2)*(x-7) < 0))// Exit
	{
		while (cl == 1)//Doi khi nao nha? chuot moi chay code
		{
			Mousepos(x,y,cl);
		}
		abort();
	}
	Mousehide();
	clrscr();
}


void Add()
{
	clrscr();
	Mousehide();
	Menu(); //Ve menu lai cho dep =]]
	
	pointer p;
	p = (pointer)malloc(sizeof(struct SinhVien));
	
	gotoxy(1,3);
	Write("Nhap ma so SV:\n",BLACK,WHITE);
	gotoxy(1,4);
	Write(blank1,BLUE,WHITE);
	gotoxy(1,4);
	scanf("%d", &p->MaSV);
	
	gotoxy(1,5);
	Write("Nhap ten SV:\n",BLACK,WHITE);
	gotoxy(1,6);
	Write(blank1,BLUE,WHITE);
	gotoxy(1,6);
	gets(p->TenSV);
	gets(p->TenSV);
	strcat(p->TenSV, "\n");
	
	gotoxy(1,7);
	Write("Nhap dia chi SV:\n",BLACK,WHITE);
	gotoxy(1,8);
	Write(blank1,BLUE,WHITE);
	gotoxy(1,8);
	gets(p->DiaChi);
	strcat(p->DiaChi, "\n");
	
	gotoxy(1,9);
	Write("Nhap diem SV:",BLACK,WHITE);
	gotoxy(1,10);
	Write("(Luu y: neu chua co diem nhap -1)",BLACK,WHITE);
	int linenumber = 11, HeSo = 0;
	p->DTB[10] = 0;
	while (linenumber < 21)
	{
		gotoxy(1,linenumber);
		Write("", BLACK, WHITE);//Chon mau chu va nen
		cprintf("HK%2d: ", linenumber-10);
		Write("                                                                          ",BLUE,WHITE);
		gotoxy(7,linenumber);
		scanf("%f", &p->DTB[linenumber-11]);
		if (p->DTB[linenumber-11] > -1)
		{
			p->DTB[10] += p->DTB[linenumber-11];
			HeSo++;
		}
		linenumber++;
	}
	if (HeSo > 0)
	{
		p->DTB[10] /= HeSo;
	}
	else
	{
		p->DTB[10] = -1;
	}
	
	if (firstSV == NULL)
	{
		firstSV = (pointer)malloc(sizeof(struct SinhVien));
		*firstSV = *p;
		firstSV->next = NULL;
		firstSV->back = NULL;
		SortPointer = firstSV;
	}
	else
	{
		pointer q, newp;
		int kt = 0;
		q = firstSV;
		if (p->MaSV < q->MaSV)
		{
			newp = (pointer)malloc(sizeof(struct SinhVien));
			*newp = *p;
			newp->next = firstSV;
			newp->back = NULL;
			firstSV->back = newp;
			firstSV = newp;
			kt = 1;
		}
		while ((q->next != NULL) && (kt == 0))
		{
			q = q->next;
			if (p->MaSV < q->MaSV)
			{
				newp = (pointer)malloc(sizeof(struct SinhVien));
				*newp = *p;
				newp->next = q;
				newp->back = q->back;
				(q->back)->next = newp;
				q->back = newp;
				kt = 1;
			}	
		}
		if (kt == 0)
		{
			newp = (pointer)malloc(sizeof(struct SinhVien));
			*newp = *p;
			newp->next = NULL;
			newp->back = q;
			q->next = newp;
		}
	}
	
	pointer p1,p2;
	
	if (FilterList != NULL)
	{
		while (FilterList->next != NULL)
		{
			FilterList = FilterList->next;
			free(FilterList->back);
		}
		free(FilterList);
	}
	
	p1 = firstSV;
	FilterList = (pointer)malloc(sizeof(struct SinhVien));
	p2 = FilterList;
	*p2 = *firstSV;
	p2->back = NULL;
	
	p1 = p1->next;
	pointer newp;
	while (p1 != NULL)
	{
		newp = (pointer)malloc(sizeof(struct SinhVien));
		*newp = *p1;
		newp->back = p2;
		p2->next = newp;
		p2 = newp;
		
		p1 = p1->next;
	}
	
	
	
	
	Sort();
	SortPointer = FilterList;
	clrscr();
	Callmouse();
}


void Delete(int MS)
{

	int TempPointer = 1;
	if (SortPointer == firstSV)
    {
		TempPointer = 1;
    }
	if (SortPointer == FilterList)
    {
		TempPointer = 2;
    }
	if (SortPointer == DTBSort)
    {
		TempPointer = 3;
    }
	pointer p;
	int kt = 0;
	p = firstSV;
	if (p->MaSV == MS)
	{
		firstSV = firstSV->next;
		firstSV->back = NULL;
		free(p);
		kt = 1;
	}
	while ((p->next != NULL) && (kt == 0))
	{
		p = p->next;
		if (p->MaSV == MS)
		{
			(p->next)->back = p->back;
			(p->back)->next = p->next;
			free(p);
			kt = 1;
		}	
	}
	
	kt = 0;
	p = FilterList;
	if (p->MaSV == MS)
	{
		FilterList = FilterList->next;
		FilterList->back = NULL;
		free(p);
		kt = 1;
	}
	while ((p->next != NULL) && (kt == 0))
	{
		p = p->next;
		if (p->MaSV == MS)
		{
			(p->next)->back = p->back;
			(p->back)->next = p->next;
			free(p);
			kt = 1;
		}	
	}

	kt = 0;
	p = DTBSort;
	if (p->MaSV == MS)
	{
		DTBSort = DTBSort->next;
		DTBSort->back = NULL;
		free(p);
		kt = 1;
	}
	while ((p->next != NULL) && (kt == 0))
	{
		p = p->next;
		if (p->MaSV == MS)
		{
			(p->next)->back = p->back;
			(p->back)->next = p->next;
			free(p);
			kt = 1;
		}	
	}

	switch(TempPointer){
    case 1:
    	SortPointer = firstSV;
     	break;
	case 2:
    	SortPointer = FilterList;
     	break;
	case 3:
    	SortPointer = DTBSort;
     	break;
	}
}


void Rewrite()
{
	strcpy(blank1, "                                                                                ");
	Mousehide();
	clrscr();
	Menu(); //Ve menu lai cho dep =]]

	//Nhap ma so SV muon sua
	gotoxy(1,3);
	Write("Nhap ma so SV:\n",BLACK,WHITE);
	gotoxy(1,4);
	Write(blank1,BLUE,WHITE);
	gotoxy(1,4);
	int MS;
	scanf("%d", &MS);
	
	
	pointer p;
	int kt = 0;
	p = firstSV;
	while ((p->next != NULL) && (p->MaSV != MS)) //Tim Sinh vien do
	{
		p = p->next;
	}
	
	if (p->MaSV == MS) // Tim thay
	{
		gotoxy(1,3);
		Write(blank1,BLACK,BLACK);
		gotoxy(1,3);
		Write("Ma SV: ",BLACK,WHITE);
		Write("", BLACK, WHITE);
		cprintf("%06d", p->MaSV);
		gotoxy(1,4);
		Write(blank1,BLUE,WHITE);
		
		gotoxy(1,6);
		Write("Ten SV: ",BLACK,WHITE);
		Write(p->TenSV,BLACK,WHITE);
		gotoxy(1,7);
		Write(blank1,BLUE,WHITE);
		
		gotoxy(1,9);
		Write("Dia chi SV: ",BLACK,WHITE);
		Write(p->DiaChi,BLACK,WHITE);
		gotoxy(1,10);
		Write(blank1,BLUE,WHITE);
		
		gotoxy(1,12);
		Write("Diem Trung Binh:",BLACK,WHITE);
		gotoxy(1,13);
		Write("(Luu y: -1 tuong duong voi chua co diem)",BLACK,WHITE);		
		int linenumber = 14;
		while (linenumber < 24)
		{
			gotoxy(1,linenumber);
			Write("", BLACK, WHITE);//Chon mau chu va nen
			cprintf("HK%02d: %.1f ", linenumber-13, p->DTB[linenumber-14]);
			gotoxy(12,linenumber);
			Write("                                                                     ",BLUE,WHITE);
			linenumber++;
		}
		
		gotoxy(67,25);
		Write(" Cancel ", WHITE, BLACK);
		gotoxy(76,25);
		Write(" OK ", WHITE, BLACK);
		
		int notok = 1;
		int x,y,cl;// Toa do + trang thai click chuot
		pointer temp;
		*temp = *p;
		//Don't ask ...
		char dontask[1];
		gets(dontask);
		//Don't ask ...
		
		while (notok == 1)
		{
			//Lap cho toi khi co click chuot
			Callmouse();
			do
			{
				Mousepos(x,y,cl);
			}while (cl == 0);	
				
			// KT xem click o dau va lam viec tuong ung
			
			if ((cl == 1) && (y == 3))//Ma SV
			{
				while (cl == 1)//Doi khi nao nha? chuot moi chay code
				{
					Mousepos(x,y,cl);
				}
				gotoxy(1,4);
				scanf("%d", &temp->MaSV);
				gotoxy(1,3);
				Write("Ma SV: ",BLACK,WHITE);
				Write("", BLACK, WHITE);
				cprintf("%06d", temp->MaSV);
				gotoxy(1,4);
				Write(blank1,BLUE,WHITE);
			}

			if ((cl == 1) && (y == 6))//Ten SV
			{
				while (cl == 1)//Doi khi nao nha? chuot moi chay code
				{
					Mousepos(x,y,cl);
				}
				gotoxy(1,7);
				gets(temp->TenSV);
				strcat(temp->TenSV, "\n");
				gotoxy(1,6);
				Write(blank1,BLACK,WHITE);//Xoa hien thu du lieu cu
				gotoxy(1,6);
				Write("Ten SV: ",BLACK,WHITE);
				Write(temp->TenSV,BLACK,WHITE);
				gotoxy(1,7);
				Write(blank1,BLUE,WHITE);
			}

			if ((cl == 1) && (y == 9))//Dia chi
			{
				while (cl == 1)//Doi khi nao nha? chuot moi chay code
				{
					Mousepos(x,y,cl);
				}
				gotoxy(1,10);
				gets(temp->DiaChi);
				strcat(temp->DiaChi, "\n");
				gotoxy(1,9);
				Write(blank1,BLACK,WHITE);//Xoa hien thu du lieu cu
				gotoxy(1,9);
				Write("Dia chi SV: ",BLACK,WHITE);
				Write(temp->DiaChi,BLACK,WHITE);
				gotoxy(1,10);
				Write(blank1,BLUE,WHITE);
			}
			
			if ((cl == 1) && ((y - 12)*(y - 23) < 0))//DTB
			{
				while (cl == 1)//Doi khi nao nha? chuot moi chay code
				{
					Mousepos(x,x,cl);
				}
				gotoxy(12,y+1);
				scanf("%f", &temp->DTB[y-13]);
				gotoxy(1,y+1);
				Write("", BLACK, WHITE);//Chon mau chu va nen
				cprintf("HK%02d: %.1f ", y-12, temp->DTB[y-13]);
				gotoxy(12,y+1);
				Write("                                                                     ",BLUE,WHITE);
				gotoxy(80,25);
			}
			
			if ((cl == 1) && (y == 24) && ((x-74)*(x-79) < 0)) //OK
			{
				while (cl == 1)//Doi khi nao nha? chuot moi chay code
				{
					Mousepos(x,y,cl);
				}
				notok = 0;
			 
			 	//Tinh toan lai DTB
			 	int HeSo = 0;
			 	temp->DTB[10] = 0;
			 	for( int i = 0; i < 10; i++ )
			 	{
	 				if (temp->DTB[i] > -1)
	 				{
				 		temp->DTB[10] += temp->DTB[i];
						HeSo++;
				 	}
	 			}
				temp->DTB[10] /= HeSo;
				
				//Xoa du lieu cu
				kt = 0;
				p = firstSV;
				if (p->MaSV == MS)
				{
					firstSV = firstSV->next;
					firstSV->back = NULL;
					free(p);
					kt = 1;
				}
				while ((p->next != NULL) && (kt == 0))
				{
					p = p->next;
					if (p->MaSV == MS)
					{
						(p->next)->back = p->back;
						(p->back)->next = p->next;
						free(p);
						kt = 1;
					}	
				}
				
				//Them du lieu moi
				if (firstSV == NULL)
				{
					firstSV = (pointer)malloc(sizeof(struct SinhVien));
					*firstSV = *temp;
					firstSV->next = NULL;
					firstSV->back = NULL;
					SortPointer = firstSV;
				}
				else
				{
					pointer q, newp;
					kt = 0;
					q = firstSV;
					if (temp->MaSV < q->MaSV)
					{
						newp = (pointer)malloc(sizeof(struct SinhVien));
						*newp = *temp;
						newp->next = firstSV;
						newp->back = NULL;
						firstSV->back = newp;
						firstSV = newp;
						kt = 1;
					}
					while ((q->next != NULL) && (kt == 0))
					{
						q = q->next;
						if (temp->MaSV < q->MaSV)
						{
							newp = (pointer)malloc(sizeof(struct SinhVien));
							*newp = *temp;
							newp->next = q;
							newp->back = q->back;
							(q->back)->next = newp;
							q->back = newp;
							kt = 1;
						}	
					}
					if (kt == 0)
					{
						newp = (pointer)malloc(sizeof(struct SinhVien));
						*newp = *temp;
						newp->next = NULL;
						newp->back = q;
						q->next = newp;
					}	
				}
				//Cap nhat va sap xep
				Sort();
				SortPointer = firstSV;
			}
				
			if ((cl == 1) && (y == 24) && ((x-65)*(x-74) < 0)) //Cancel
			{
				while (cl == 1)//Doi khi nao nha? chuot moi chay code
				{
					Mousepos(x,y,cl);
				}
				notok = 0;
			}			
		}
	}
	else //K tim thay
	{
		clrscr();
		Menu(); //Ve menu lai cho dep =]]
		gotoxy(1,3);
		Write("Not found!",BLACK,WHITE);
		
		gotoxy(76,25);
		Write(" OK ", WHITE, BLACK);
		gotoxy(80,25);
		
		int notok = 1;
		int x,y,cl;// Toa do + trang thai click chuot
		
		while (notok == 1)
		{
			//Lap cho toi khi co click chuot
			Callmouse();
			do
			{
				Mousepos(x,y,cl);
			}while (cl == 0);	
			
			// KT xem click o dau va lam viec tuong ung
			if ((cl == 1) && (y == 24) && ((x-74)*(x-79) < 0)) //OK
			{
				while (cl == 1)//Doi khi nao nha? chuot moi chay code
				{
					Mousepos(x,y,cl);
				}
				notok = 0;
			}
		}
	}
	clrscr();
	Callmouse();
}


void Edit()
{
	
	gotoxy(10,1);
	Write("Edit",WHITE,RED);
	gotoxy(8,2);
	Write(" ÚÄÄÄÄÄÄÄÄÄ¿ ",WHITE,BLACK);
	gotoxy(8,3);
	Write(" ³ Add     ³ ",WHITE,BLACK);
	gotoxy(8,4);
	Write(" ³ Rewrite ³ ",WHITE,BLACK);
	gotoxy(8,5);
	Write(" ÀÄÄÄÄÄÄÄÄÄÙ ",WHITE,BLACK);
	gotoxy(80,25);
	
	int x,y,cl;// Toa do + trang thai click chuot
	Callmouse();
	do
	{
		Mousepos(x,y,cl);
	}while (cl == 0);
	if ((y == 2) && ((x-9)*(x-13) < 0))// Add
	{
		while (cl == 1)//Doi khi nao nha? chuot moi chay code
		{
			Mousepos(x,y,cl);
		}
		Add();
	}
	
	if ((y == 3) && ((x-9)*(x-16) < 0))// Delete
	{
		while (cl == 1)//Doi khi nao nha? chuot moi chay code
		{
			Mousepos(x,y,cl);
		}
		Rewrite();
	}
	Mousehide();
	clrscr();
}

void Filter()
{
	strcpy(blank1, "                                                                                ");
	Mousehide();
	clrscr();
	Menu(); //Ve menu lai cho dep =]]
	
	gotoxy(1,3);
	Write("Ma SV:",BLACK,WHITE);
	gotoxy(1,4);
	Write(blank1,BLUE,WHITE);
	
	gotoxy(1,6);
	Write("Ten SV:",BLACK,WHITE);
	gotoxy(1,7);
	Write(blank1,BLUE,WHITE);
	
	gotoxy(1,9);
	Write("Dia chi SV:",BLACK,WHITE);
	gotoxy(1,10);
	Write(blank1,BLUE,WHITE);
	
	gotoxy(1,12);
	Write("DTB lon hon: 0",BLACK,WHITE);
	gotoxy(1,13);
	Write(blank1,BLUE,WHITE);
	
	gotoxy(1,15);
	Write("DTB be hon: 10",BLACK,WHITE);
	gotoxy(1,16);
	Write(blank1,BLUE,WHITE);
	
	gotoxy(67,25);
	Write(" Cancel ", WHITE, BLACK);
	gotoxy(76,25);
	Write(" OK ", WHITE, BLACK);
		
	int MS = -1;
	float max = 10, min = -1;
	char Ten[100] = "";
	char DiaChi[100] = "";
	

	
	
	int notok = 1;
	int x,y,cl;// Toa do + trang thai click chuot
	Callmouse();
	
	
	while (notok == 1)
	{
		//Lap cho toi khi co click chuot
		Callmouse();
		do
		{
			
			Mousepos(x,y,cl);
		}while (cl == 0);	
		
		// KT xem click o dau va lam viec tuong ung
		if ((cl == 1) && (y == 3))//Ma SV
		{
			while (cl == 1)//Doi khi nao nha? chuot moi chay code
			{
				Mousepos(x,y,cl);
			}
			gotoxy(1,4);
			scanf("%d", &MS);
			gotoxy(1,3);
			Write("Ma SV: ",BLACK,WHITE);
			Write("", BLACK, WHITE);
			cprintf("%06d", MS);
			gotoxy(1,4);
			Write(blank1,BLUE,WHITE);
			gotoxy(80,25);
		}

		if ((cl == 1) && (y == 6))//Ten SV
		{
			while (cl == 1)//Doi khi nao nha? chuot moi chay code
			{
				Mousepos(x,y,cl);
			}
			gotoxy(1,7);
			gets(Ten);
			gotoxy(1,6);
			Write(blank1,BLACK,WHITE);//Xoa hien thu du lieu cu
			gotoxy(1,6);
			Write("Ten SV: ",BLACK,WHITE);
			Write(Ten,BLACK,WHITE);
			gotoxy(1,7);
			Write(blank1,BLUE,WHITE);
			gotoxy(80,25);
		}

		if ((cl == 1) && (y == 9))//Dia chi
		{
			while (cl == 1)//Doi khi nao nha? chuot moi chay code
			{
				Mousepos(x,y,cl);
			}
			gotoxy(1,10);
			gets(DiaChi);
			gotoxy(1,9);
			Write(blank1,BLACK,WHITE);//Xoa hien thu du lieu cu
			gotoxy(1,9);
			Write("Dia chi SV: ",BLACK,WHITE);
			Write(DiaChi,BLACK,WHITE);
			gotoxy(1,10);
			Write(blank1,BLUE,WHITE);
			gotoxy(80,25);
		}
		
		if ((cl == 1) && (y == 12))//Min
		{
			while (cl == 1)//Doi khi nao nha? chuot moi chay code
			{
				Mousepos(x,y,cl);
			}
			gotoxy(1,13);
			scanf("%f", &min);
			gotoxy(1,12);
			Write("DTB lon hon: ",BLACK,WHITE);
			Write("", BLACK, WHITE);
			cprintf("%.1f", min);
			gotoxy(1,13);
			Write(blank1,BLUE,WHITE);
			gotoxy(80,25);
		}
		
		if ((cl == 1) && (y == 15))//Max
		{
			while (cl == 1)//Doi khi nao nha? chuot moi chay code
			{
				Mousepos(x,y,cl);
			}
			gotoxy(1,16);
			scanf("%f", &max);
			gotoxy(1,15);
			Write("DTB be hon: ",BLACK,WHITE);
			Write("", BLACK, WHITE);
			cprintf("%.1f", max);
			gotoxy(1,16);
			Write(blank1,BLUE,WHITE);
			gotoxy(80,25);
		}		
			
		if ((cl == 1) && (y == 24) && ((x-74)*(x-79) < 0)) //OK
		{
			while (cl == 1)//Doi khi nao nha? chuot moi chay code
			{
				Mousepos(x,y,cl);
			}
			pointer p, q,newp;
			p = firstSV;
			
			if (FilterList != NULL)
			{
				while (FilterList->next != NULL)
				{
					FilterList = FilterList->next;
					free(FilterList->back);
				}
				free(FilterList);
			}
			
			FilterList = NULL;
			
			while ((p != NULL) && (((p->MaSV == MS) && (MS != -1)) || (strstr(p->TenSV, Ten) == NULL) || (strstr(p->DiaChi, DiaChi) == NULL) || ((p->DTB[10] - min)*(p->DTB[10] - max) > 0)))
			{
				p = p->next;	
			}
			if ((((p->MaSV == MS) || (MS == -1)) && (strstr(p->TenSV, Ten) != NULL) && (strstr(p->DiaChi, DiaChi) != NULL) && ((p->DTB[10] - min)*(p->DTB[10] - max) <= 0)) && (p != NULL))
			{
				FilterList = (pointer)malloc(sizeof(struct SinhVien));
				*FilterList = *p;
				FilterList->back = NULL;
				FilterList->next = NULL;
				q = FilterList;
				p = p->next;
			}
			
			while ((p != NULL))
			{
				if (((p->MaSV == MS) || (MS == -1)) && (strstr(p->TenSV, Ten) != NULL) && (strstr(p->DiaChi, DiaChi) != NULL) && ((p->DTB[10] - min)*(p->DTB[10] - max) <= 0))
				{
					newp = (pointer)malloc(sizeof(struct SinhVien));
					*newp = *p;
					newp->back = q;
					newp->next = NULL;
					q->next = newp;
					q = newp;
				}
				p = p->next;	
			}
			notok = 0;
			Sort();
			SortPointer = FilterList;
		}
				
		if ((cl == 1) && (y == 24) && ((x-65)*(x-74) < 0)) //Cancel
		{
			while (cl == 1)//Doi khi nao nha? chuot moi chay code
			{
				Mousepos(x,y,cl);
			}
			notok = 0;
		}			
	}
}




void WriteData(int page)
{
	//In so trang data ma hien thi
	gotoxy(1,3);
	textbackground(BLACK);
	textcolor(YELLOW);
	cprintf("Page: %d", page + 1);
	
	int linenumber = 4;
	//Ve khung du lieu 
	gotoxy(1, linenumber);
	Write("ÚÄDATAÄÂÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÂÄÄÄÂÄÄÄÂÄÄÄÂÄÄÄÂÄÄÄÂÄÄÄÂÄÄÄÂÄÄÄÂÄÄÄÂÄÄÄÄÂÄÄÄ¿",BLACK,YELLOW);
	gotoxy(1, linenumber + 1);
	Write("³MSSV  ³Ho Tˆn                   ³HK1³HK2³HK3³HK4³HK5³HK6³HK7³HK8³HK9³HK10³DTB³",BLACK,YELLOW);
	for(linenumber = 6; linenumber < 22; linenumber += 2)
	{
		gotoxy(1,linenumber);
		Write("³",BLACK,YELLOW);
		Write("ÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÅÄÄÄÅÄÄÄÅÄÄÄÅÄÄÄÅÄÄÄÅÄÄÄÅÄÄÄÅÄÄÄÅÄÄÄÅÄÄÄÄÅÄÄÄ",BLACK,WHITE);
		Write("³",BLACK,YELLOW);
				
		gotoxy(1,linenumber+1);
		Write("³",BLACK,YELLOW);
		Write("      ³                         ³   ³   ³   ³   ³   ³   ³   ³   ³   ³    ³   ",BLACK,WHITE);
		Write("³",BLACK,YELLOW);
	}
	gotoxy(1, linenumber);
	Write("ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ",BLACK,YELLOW);
	//Ve nut chon trang va sap xep
	gotoxy(1, 23);
	Write("ÚÄÄÄÄÄÄÄÄÄÄÄÄÄ¿",BLACK,YELLOW);
	gotoxy(1, 24);
	Write("³First Page   ³",BLACK,YELLOW);
	gotoxy(1, 25);
	Write("ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÙ",BLACK,YELLOW);
	
	gotoxy(17, 23);
	Write("ÚÄÄÄÄÄÄÄÄÄÄÄÄÄ¿",BLACK,YELLOW);
	gotoxy(17, 24);
	Write("³Previous Page³",BLACK,YELLOW);
	gotoxy(17, 25);
	Write("ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÙ",BLACK,YELLOW);
	
	gotoxy(65, 23);
	Write("ÚÄÄÄÄÄÄÄÄÄÄÄÄÄ¿",BLACK,YELLOW);
	gotoxy(65, 24);
	Write("³Next Page    ³",BLACK,YELLOW);
	gotoxy(65, 25);
	Write("ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÙ",BLACK,YELLOW);
	
	gotoxy(59, 23);
	Write("ÚÄÄÄÄ¿",BLACK,YELLOW);
	gotoxy(59, 24);
	Write("³DTB³",BLACK,YELLOW);
	gotoxy(59, 25);
	Write("ÀÄÄÄÄÙ",BLACK,YELLOW);
	
	gotoxy(52, 23);
	Write("ÚÄÄÄÄÄ¿",BLACK,YELLOW);
	gotoxy(52, 24);
	Write("³MSSV³",BLACK,YELLOW);
	gotoxy(52, 25);
	Write("ÀÄÄÄÄÄÙ",BLACK,YELLOW);
	
	//Ki tu mui ten xuong tang hinh =]] ""	
		
	//Chon mau viet
	textbackground(BLACK);
	textcolor(WHITE);
	
	pointer p;
	int i;
	int count = 0;
	
	linenumber = 7;
	p = SortPointer;
	if (p == NULL)
	{
		gotoxy(2,linenumber);
		Write("Data is empty",BLACK,WHITE);
	}
	while (p != NULL)
	{	
		if ((count / 8) == page)
		{
			gotoxy(80, linenumber);
			Write("X",BLACK,RED);
			Write("",BLACK,WHITE);
			gotoxy(2,linenumber);
			cprintf("%06d",p->MaSV);
			gotoxy(9,linenumber);
			cprintf("%s",p->TenSV);
			gotoxy(34,linenumber);
			for (i = 0; i < 10; i++)
			{
				if (p->DTB[i] < 0)
				{
					Write("³",BLACK,WHITE);	
					Write("N/A",BLACK,RED);
					Write("",BLACK,WHITE);//Tra lai mau nen den but trang
				}
				else if (p->DTB[i] == 10.0)
				{
					cprintf("³10 ");
				}
				else
				{
					cprintf("³%.1f",p->DTB[i]);
				}
			}
			gotoxy(74,linenumber);
			cprintf(" ³");
			if (p->DTB[10] == 10.0)
			{
				cprintf("10");
				
			}
			else if (p->DTB[10]> -1)
			{
				cprintf("%.1f",p->DTB[10]);
			}
			else
			{
				Write("N/A",BLACK,RED);
				Write("",BLACK,WHITE);//Tra lai mau nen den but trang
			}
			
			MaSoOutput[(linenumber-7)/2] = p->MaSV;
			linenumber += 2;
		}
		p = p->next;
		count++;
	}
	gotoxy(80,25);
}


//Ket thuc


void main()
{
	system("cls");
	int x,y,cl,page = 0;// Toa do + trang thai click chuot
	Callmouse();
	do
	{
		clrscr();
		Mousehide();
		Menu();
		WriteData(page);
		Mousepos(x,y,cl);
		
		//Lap cho toi khi co click chuot
		Callmouse();
		do
		{
			Mousepos(x,y,cl);
		}while (cl == 0);
		
		if ((cl == 1) && (y == 0) && ((x-0)*(x-7) < 0))
		{
			while (cl == 1)//Doi khi nao nha? chuot moi chay code
			{
				Mousepos(x,y,cl);
			}
			Mousehide();//Lay chuot ra de to^ do? chu~ file
			File();
			Callmouse();
		}
		if ((cl == 1) && (y == 0) && ((x-7)*(x-14) < 0))
		{
			while (cl == 1)//Doi khi nao nha? chuot moi chay code
			{
				Mousepos(x,y,cl);
			}
			Mousehide();//Lay chuot ra de to^ do? chu~ file
			Edit();
			Callmouse();
		}
		if ((cl == 1) && (y == 0) && ((x-14)*(x-23) < 0))
		{
			while (cl == 1)//Doi khi nao nha? chuot moi chay code
			{
				Mousepos(x,y,cl);
			}
			Mousehide();//Lay chuot ra de to^ do? chu~ file
			Filter();
			Callmouse();
		}
				
		//Dieu chinh page
		//First Page
		if ((cl == 1) && ((y-21)*(y-25) < 0) && ((x-(-1))*(x-15) < 0))
		{
			while (cl == 1)//Doi khi nao nha? chuot moi chay code
			{
				Mousepos(x,y,cl);
			}
			page = 0;
		}
		
		//Previous page
		if ((cl == 1) && ((y-21)*(y-25) < 0) && ((x-15)*(x-31) < 0))
		{
			while (cl == 1)//Doi khi nao nha? chuot moi chay code
			{
				Mousepos(x,y,cl);
			}
			if (page > 0) page--;
		}
		
		//Next page
		if ((cl == 1) && ((y-21)*(y-25) < 0) && ((x-63)*(x-79) < 0))
		{
			while (cl == 1)//Doi khi nao nha? chuot moi chay code
			{
				Mousepos(x,y,cl);
			}
			page++;
		}
		
		//DTB Sort
		if ((cl == 1) && ((y-21)*(y-25) < 0) && ((x-57)*(x-64) < 0))
		{
			while (cl == 1)//Doi khi nao nha? chuot moi chay code
			{
				Mousepos(x,y,cl);
			}
			SortPointer = DTBSort;
		}
		
		//MSSV Sort
		if ((cl == 1) && ((y-21)*(y-25) < 0) && ((x-50)*(x-58) < 0))
		{
			while (cl == 1)//Doi khi nao nha? chuot moi chay code
			{
				Mousepos(x,y,cl);
			}
			SortPointer = FilterList;
		}
		
		//Delete
		if ((cl == 1) && ((y % 2) == 0) && ((y-5)*(y-21) < 0) && (x == 79))
		{
			while (cl == 1)//Doi khi nao nha? chuot moi chay code
			{
				Mousepos(x,y,cl);
			}
			Delete(MaSoOutput[(y-6)/2]);
		}
	while (cl == 1)//Doi khi nao nha? chuot moi chay code
	{
		Mousepos(x,y,cl);
	}	
	}while(1);
}
