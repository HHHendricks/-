#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define M 10
#define N 15
#define Z 25			//课程数量 

char code[] = "123456"; 	//登录密码 

typedef struct course {			//课程信息 
	float mark;
	char name[Z];
}C;

typedef struct student {			//学生信息 
	char name[M];		//姓名 
	char number[N];		//学号 
	char Class[M];		//班级 
	char grade[M];		//年级 
	C course[100];		//课程
	int n;				//课程数量 
	struct student *next;
}S;

void lode(S *student);
void lodestudent(S *student);
void lodeteacher(S *student);
void lodeadmin(S *student);
void funcadmin(S *student);
S* readstudent();
void addstudent(S *student);
void deletestudent(S *student);
void addcourse(S *student);
void deletecourse(S *student);
void functeacher(S *student);
void funcstudent(S *p, S *student);
void addmark(S *student);
void average(S *student);
void certaincourse(S *student);

void lode(S *student)				//登录界面 
{
	int k;
	printf("请输入你的身份或者退出程序\n\n");
	printf("1:管理员\n2：教师\n3：学生\n按其他数字键退出\n");
	scanf("%d", &k);
	switch (k)
	{
	case 1: {
		system("cls");
		lodeadmin(student);
		break;
	}
	case 2: {
		system("cls");
		lodeteacher(student);
		break;
	}
	case 3: {
		system("cls");
		lodestudent(student);
		break;
	}
	default: return;
	}
}

void lodestudent(S *student)		//学生登录
{
	char num[N];
	char node[N];
	S *p;
	printf("请输入你的学号：");
	scanf("%s", num);
	printf("输入密码：");
	getchar();				//吃掉换行符
	scanf("%s", node);
	while (1)
	{
		p = student;
		while (p != NULL && strcmp(num, p->number))
			p = p->next;
		if (p == NULL)
		{
			printf("没有该学生，重新输入学号\n\n");
			printf("请输入学号：");
			scanf("%15s", num);
			system("cls");
		}
		else if (strcmp(node, code))
		{
			printf("密码错误，重新输入密码\n\n");
			printf("请输入密码：");
			scanf("%15s", node);
			system("cls");
		}
		else
		{
			system("cls");
			funcstudent(p,student);						//进入学生模式 
			return;
		}
	}
}

void lodeteacher(S *student)				//教师登录 
{
	char num[N];
	printf("输入教师登录密码：");
	scanf("%15s", num);
	while (1)
	{
		if (strcmp(num, code))
		{
			printf("密码错误，重新输入\n");
			printf("请输入：");
			scanf("%15s", num);
			system("cls");
		}
		else
		{
			system("cls");
			functeacher(student);			//进入教师模式 
			return;
		}
	}
}

void lodeadmin(S *student)				//管理员登录 
{
	char num[N];
	printf("输入管理员登录密码：");
	scanf("%15s", num);
	while (1)
	{
		if (strcmp(num, code))
		{
			printf("密码错误，重新输入\n");
			printf("请输入：");
			scanf("%15s", num);
			system("cls");
		}
		else
		{
			system("cls");
			funcadmin(student);				//进入管理员模式 
			break;
		}
	}
}

void funcadmin(S *student)					//管理员模式 
{
	printf("已进入管理员模式\n\n");

	int k;
	printf("以下是所有学生的信息：\n");
	S *p = student;
	printf("\t学号\t\t姓名\t班级\t年级\t课程及分数\n");
	while (p != NULL)
	{
		printf("\t%s\t%s\t%s\t%s", p->number, p->name, p->Class, p->grade);
		if(p->course[0].mark>=0)
			printf("\t%s %.2f\n", p->course[0].name, p->course[0].mark);
		for (int i = 1; i < p->n; i++)
			if (p->course[i].mark >= 0)
				printf("\t\t\t\t\t\t%s %.2f\n", p->course[i].name, p->course[i].mark);
		printf("\n");
		p = p->next;
	}
	printf("\n");
	printf("输入你接下来的操作：\n");
	printf("1：添加学生\n2：删除学生\n3：添加课程\n4：删除课程\n5：退出\n输入其他数字返回上一级\n");
	printf("请输入：");
	scanf("%d", &k);
	switch (k)
	{
	case 1: {
		system("cls");
		addstudent(student);			//添加学生模式 
		break;
	}
	case 2: {
		system("cls");
		deletestudent(student);			//删除学生模式 
		break;
	}
	case 3: {
		system("cls");
		addcourse(student);				//添加课程模式 
		break;
	}
	case 4: {
		system("cls");
		deletecourse(student);			//删除课程模式 
		break;
	}
	case 5: {
		return;						//退出 
	}
	default: {
		system("cls");
		lode(student);					//返回上一级 
	}
	}
}

S *readstudent()				//读取学生信息 
{
	S *p, *head = NULL;
	FILE *fp = fopen("inf.txt", "r");
	if (fp == NULL)
	{
		printf("没有学生的信息\n");
		exit(0);
	}
	char num[N];
	while (fscanf(fp,"%s",num)==1)
	{
		p = (S*)malloc(sizeof(S));
		fscanf(fp, "%s %s %s %d",p->name, p->Class, p->grade, &p->n);
		for (int i = 0; i < p->n; i++)
			fscanf(fp,"%s %f", p->course[i].name, &p->course[i].mark);
		strcpy(p->number, num);
		p->next = head;
		head = p;
	}
	fclose(fp);
	return head;
}

void addstudent(S *student)			//添加学生 
{
	S *p = student;
	S *q;
	FILE *fp = fopen("inf1.txt", "w");
	if (fp == NULL)
	{
		printf("文件打开失败\n");
		exit(0);
	}
	printf("已进入添加学生模块\n\n");
	while (1)
	{
		printf("以下是所有学生的信息：\n");
		printf("\t学号\t\t姓名\t班级\t年级\t课程及分数\n");
		while (p != NULL)
		{
			printf("\t%s\t%s\t%s\t%s", p->number, p->name, p->Class, p->grade);
			if (p->course[0].mark >= 0)
				printf("\t%s %.2f\n", p->course[0].name, p->course[0].mark);
			for (int i = 1; i < p->n; i++)
				if (p->course[i].mark >= 0)
					printf("\t\t\t\t\t\t%s %.2f\n", p->course[i].name, p->course[i].mark);
			printf("\n");
			p = p->next;
		}
		printf("\n");

	
		p = student;
		q = (S*)malloc(sizeof(S));
		printf("请输入该学生的学号、姓名、班级、年级（中间以空格隔开）:\n\n");
		scanf("%s %s %s %s", q->number, q->name, q->Class, q->grade);
		while (p != NULL && strcmp(q->number, p->number))
			p = p->next;
		if (p != NULL)
			printf("该学生信息被已经导入\n\n");
		else
		{
			q->n = student->n;
			for (int i = 0; i < q->n;i++)
			{
				strcpy(q->course[i].name, student->course[i].name);
				q->course[i].mark = -1;
			}
			q->next = student;
			student = q;
			printf("添加成功\n\n");
		}
		int a;
		printf("是否继续添加学生？输入1继续，输入2返回上一级\n");
		scanf("%d", &a);
		system("cls");
		if (a == 2)
			break;
	}
	q = student;
	while (q != NULL)
	{
		fprintf(fp, "%s %s %s %s %d", q->number, q->name, q->Class, q->grade, q->n);
		for (int i = 0; i < q->n; i++)
			fprintf(fp, " %s %f", q->course[i].name, q->course[i].mark);
		fprintf(fp, "\n");
		q = q->next;
	}
	fclose(fp);
	remove("inf.txt");
	rename("inf1.txt", "inf.txt");
	system("cls");
	funcadmin(student);
}

void deletestudent(S *student)				//删除学生 
{
	FILE *ftp;
	ftp = fopen("inf1.txt", "w");
	if (ftp == NULL)
	{
		printf("没有学生信息，无法删除学生\n");
		exit(0);
	}
	S *pre, *p;
	while (1)
	{
		printf("以下是所有学生的信息：\n");
		p = student;
		printf("\t学号\t\t姓名\t班级\t年级\t课程及分数\n");
		while (p != NULL)
		{
			printf("\t%s\t%s\t%s\t%s", p->number, p->name, p->Class, p->grade);
			if(p->course[0].mark>=0)
				printf("\t%s %.2f\n", p->course[0].name, p->course[0].mark);
			for (int i = 1; i < p->n; i++)
				if (p->course[i].mark >= 0)
					printf("\t\t\t\t\t\t%s %.2f\n", p->course[i].name, p->course[i].mark);
			printf("\n");
			p = p->next;
		}
		printf("\n");
		char num[N];
	
		p = student;
		printf("输入要删除的学生学号：");
		scanf("%s", num);
		while (strcmp(num, p->number)&& p->next != NULL)			//查找是否有该学生 
		{
			pre = p;
			p = p->next;
		}
		if (strcmp(num, p->number))
			printf("该学生信息未被添加或已被删除\n");
		else												//找到，更新信息表 
		{
			if (p == student)
				student = p->next;
			else
				pre->next = p->next;
			free(p);
			printf("删除成功\n\n");
		}

		char a;
		printf("是否继续删除学生？输入1继续，输入其他返回上一级");
		getchar();
		scanf("%c", &a);
		system("cls");
		if (a != '1')
			break;
	}
	p = student;
	while (p != NULL)
	{
		fprintf(ftp, "%s %s %s %s %d", p->number, p->name, p->Class, p->grade, p->n);
		for (int i = 0; i < p->n; i++)
			fprintf(ftp, " %s %f", p->course[i].name, p->course[i].mark);
		fprintf(ftp, "\n");
		p = p->next;
	}
	fclose(ftp);
	remove("inf.txt");
	rename("inf1.txt", "inf.txt");
	funcadmin(student);
}

void addcourse(S *student)					//添加课程
{
	FILE *fp;
	fp = fopen("inf1.txt", "w");
	if (fp == NULL)
	{
		printf("没有学生信息，无法添加课程\n");
		exit(0);
	}

	char num[25];
	S *p;
	while (1)
	{
		p = student;
		printf("以下是所有的课程：\n");
		for (int i = 0; i < p->n; i++)
			if (p->course[i].mark!=-2)
				printf("\t\t%s\n", p->course[i].name);
		printf("\n");

		printf("输入你要增加的课程名：");
		scanf("%s", num);
		p = student;
		while (p != NULL)
		{
			int i;
			for (i = 0; i < p->n; i++)
				if (!strcmp(num, p->course[i].name))
					break;
			if (i >= p->n)
			{
				strcpy(p->course[p->n].name, num);
				p->course[p->n].mark = -1;
				p->n++;
				if(p->next==NULL)
					printf("添加成功\n\n");
			}
			else if (p->course[i].mark == -2)
			{
				p->course[i].mark = -1;
				if(p->next==NULL)
					printf("添加成功\n\n");
			}
			else if (p->course[i].mark >= -1)
			{
				printf("该课程已经添加\n\n");
				break;
			}
			p = p->next;
		}

		printf("是否继续添加课程？\n");
		printf("输入1继续，输入其他返回上一级\n\n");
		printf("请输入：");
		char a;
		getchar();
		scanf("%c", &a);
		system("cls");
		if (a != '1')
			break;
	}
	p = student;
	while (p != NULL)
	{
		fprintf(fp, "%s %s %s %s %d", p->number, p->name, p->Class, p->grade, p->n);
		for (int i = 0; i < p->n; i++)
			fprintf(fp, " %s %f", p->course[i].name, p->course[i].mark);
		fprintf(fp, "\n");
		p = p->next;
	}
	fclose(fp);
	remove("inf.txt");
	rename("inf1.txt", "inf.txt");
	funcadmin(student);
}

void deletecourse(S *student)			//删除学生课程 
{
	S *p;
	FILE *fp;
	fp = fopen("inf1.txt", "w");
	if (fp == NULL)
	{
		printf("没有学生信息，无法删除课程");
		exit(0);
	}
	while (1)
	{
		p = student;
		printf("以下是所有的课程：\n");
		for (int i = 1; i < p->n; i++)
			if (p->course[i].mark != -2)
				printf("\t\t%s\n", p->course[i].name);
	
		char num[Z];
		p = student;
		printf("输入你要删除的课程名：");
		scanf("%s", num);
		while (p != NULL)
		{
			int i;
			for(i=0;i<p->n;i++)
				if (!strcmp(num, p->course[i].name))
					break;
			if (i >= p->n || p->course[i].mark == -2)
			{
				printf("该课程还未添加\n\n");
				break;
			}
			else
			{
				p->course[i].mark = -2;
				if (p->next == NULL)
					printf("删除成功\n\n");
			}
			p = p->next;
		}
		printf("是否继续删除课程？\n");
		printf("输入1继续，按其他键返回上一级\n\n");
		printf("请输入：");
		char a;
		getchar();			//吃掉换行符
		scanf("%c",&a);
		system("cls");
		if (a != '1')
			break;
	}
	p = student;
	while (p != NULL)
	{
		fprintf(fp, "%s %s %s %s %d", p->number, p->name, p->Class, p->grade, p->n);
		for (int i = 0; i < p->n; i++)
			fprintf(fp, " %s %f", p->course[i].name, p->course[i].mark);
		fprintf(fp, "\n");
		p = p->next;
	}
	fclose(fp);
	remove("inf.txt");
	rename("inf1.txt", "inf.txt");
	funcadmin(student);
}

void functeacher(S *student)			//教师登录模式 
{
	printf("已进入教师模式\n\n");
	printf("以下是所有学生的信息：\n");
	S *p = student;
	printf("\t学号\t\t姓名\t班级\t年级\t课程及分数\n");
	while (p != NULL)
	{
		printf("\t%s\t%s\t%s\t%s", p->number, p->name, p->Class, p->grade);
		if (p->course[0].mark >= 0)
			printf("\t%s %.2f\n", p->course[0].name, p->course[0].mark);
		for (int i = 1; i < p->n; i++)
			if (p->course[i].mark >= 0)
				printf("\t\t\t\t\t\t%s %.2f\n", p->course[i].name, p->course[i].mark);
		printf("\n");
		p = p->next;
	}
	printf("\n");
	int k;
	printf("输入你接下来的操作：\n");
	printf("1：输入学生课程分数\n2：统计某门课的及格率和平均分\n3：统计所有学生的某门课的分数\n4：退出\n按其他键返回上一级\n");
	printf("请输入：");
	scanf("%d", &k);
	switch (k)
	{
	case 1: {
		system("cls");
		addmark(student);
		break;
	}
	case 2: {
		system("cls");
		average(student);
		break;
	}
	case 3: {
		system("cls");
		certaincourse(student);
		break;
	}
	case 4: {
		return;
	}
	default: {
		system("cls");
		lode(student);
	}
	}
}

void addmark(S *student)				//添加学生成绩 
{
	S *p;
	FILE *fp;
	fp = fopen("inf1.txt", "w");
	if (fp == NULL)
	{
		printf("没有学生信息，无法添加分数\n");
		exit(0);
	}
	while (1)
	{
		printf("以下是所有学生的学号和姓名：\n");
		p = student;
		printf("\t学号\t\t姓名\n");
		while (p != NULL)
		{
			printf("\t%s\t%s\n", p->number, p->name);
			p = p->next;
		}
		printf("\n");
	
		p = student;
		printf("以下是所有的课程：\n");
		for (int i = 1; i < p->n; i++)
			if (p->course[i].mark != -2)
				printf("\t\t%s\n", p->course[i].name);
		printf("\n\n");

		char num[Z];
		printf("输入要添加课程的学生学号：");
		scanf("%s", num);
		while (p != NULL && strcmp(num, p->number))
			p = p->next;
		if (p == NULL)
			printf("该学生信息未被添加或已经被删除\n");
		else
		{

			int i = 0;
			printf("输入你要增加分数的课程名：");
			scanf("%s", num);
			while (1)
			{
				if (!strcmp(num, p->course[i].name))
				{
					if (p->course[i].mark == -2)
						break;
					printf("输入分数：");
					scanf("%f", &p->course[i].mark);

					if (p->course[i].mark < 0 || p->course[i].mark>100)
					{
						i--;
						printf("请输入0—100之间的数\n\n");
					}
					else
					{
						printf("添加成功\n\n");
						break;
					}
				}
				i++;
				if (i >= p->n)
					break;
			}
			if (i >= p->n || p->course[i].mark == -2)
				printf("没有该课程\n\n");

		}
		printf("是否继续添加成绩？\n");
		printf("输入1继续，输入其他数字返回上一级\n\n");
		printf("请输入：");
		int a;
		scanf("%d", &a);
		system("cls");
		if (a != 1)
			break;
	}
		p = student;
		while (p != NULL)
		{
			fprintf(fp, "%s %s %s %s %d", p->number, p->name, p->Class, p->grade, p->n);
			for (int i = 0; i < p->n; i++)
				fprintf(fp, " %s %f", p->course[i].name, p->course[i].mark);
			fprintf(fp, "\n");
			p = p->next;
		}
		fclose(fp);
		remove("inf.txt");
		rename("inf1.txt", "inf.txt");
	
	functeacher(student);
}

void average(S *student)		//统计均分和及格率 
{
	S *p = student;
	
	while (1)
	{
		float n = 0, n1 = 0,n2=0;			//n：该学科总人数 n1：不及格的人数 a：平均分
		float a = 0;

		p = student;
		printf("以下是所有的课程：\n");
		for (int i = 0; i < p->n; i++)
			if (p->course[i].mark != -2)
				printf("\t\t%s\n", p->course[i].name);
		printf("\n\n");

		char num[Z];
		printf("输入要查找的课程名：");
		scanf("%s", num);

		while (p != NULL)					//计算平均分和及格率 
		{
			for (int i = 0; i < p->n; i++)
			{
				if (!strcmp(num, p->course[i].name) && p->course[i].mark >= 0)
				{
					a += p->course[i].mark;
					n++;
				}
				if (!strcmp(num, p->course[i].name) && p->course[i].mark >= 0 && p->course[i].mark < 60)
					n1++;
				if (!strcmp(num, p->course[i].name) && p->course[i].mark >= -1)
					n2++;
				
			}
			p = p->next;
		}
		if (n2 == 0)
			printf("该学科不存在\n\n");
		else if (n == 0)
			printf("没有学生修该们课程\n\n");
		else
			printf("该科目的平均分为：%.2f，及格率为：%.2f%%\n", a / n, (1 - n1 / n) * 100);

		printf("是否继续查找？\n输入1继续，输入其他数字返回上一级\n\n");
		printf("请输入：");
		int b;
		scanf("%d", &b);
		system("cls");
		if (b !=1)
			break;
	}
	functeacher(student);
}

void certaincourse(S *student)			//查找所有学生某门学科的分数 
{
	S *p = student;

	while (1)
	{
		int n = 0,n1=0;	//总人数 
		p = student;

		printf("以下是所有的课程：\n");
		for (int i = 0; i < p->n; i++)
			if (p->course[i].mark != -2)
				printf("\t\t%s\n", p->course[i].name);
		printf("\n\n");

		char num[Z];
		printf("输入要查找的课程名：");
		scanf("%s", num);

		while (p != NULL)
		{
			for (int i = 0; i < p->n; i++)
			{
				if (!strcmp(num, p->course[i].name) && p->course[i].mark >= 0)
				{
					printf("\t%s：%.2f\n", p->name, p->course[i].mark);
					n++;
				}
				if (!strcmp(num, p->course[i].name) && p->course[i].mark >= -1)
					n1++;
			}
			p = p->next;
		}
		if (n1 == 0)
			printf("该课程不存在\n\n");
		else if (n == 0)
			printf("没有学生修该们课程\n\n");
		printf("是否继续查找？\n输入1继续，输入其他数字返回上一级\n\n");
		int b;
		printf("请输入：");
		scanf("%d", &b);
		system("cls");
		if (b != 1)
			break;
	}
	functeacher(student);
}

void funcstudent(S *p,S *student)			//学生功能
{
	printf("你的各信息如下：\n");
	printf("\t学号\t\t姓名\t班级\t年级\t课程及分数\n");
	printf("\t%s\t%s\t%s\t%s", p->number, p->name, p->Class, p->grade);
	printf("\t%s %.2f\n", p->course[0].name, p->course[0].mark);
	for (int i = 1; i < p->n; i++)
		if(p->course[i].mark>=0)
			printf("\t\t\t\t\t\t%s %.2f\n", p->course[i].name, p->course[i].mark);
	printf("\n\n");
	char a;
	getchar();			//吃掉换行符
	printf("输入1返回上一级，输入其他键退出\n\n");
	printf("请输入：");
	scanf("%c", &a);
	system("cls");
	if (a == '1')
		lode(student);
	else
		return;
}

int main()
{
	S *student;
	student = readstudent();
	lode(student);
	return 0;
}