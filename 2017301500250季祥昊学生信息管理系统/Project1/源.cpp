#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define M 10
#define N 15
#define Z 25			//�γ����� 

char code[] = "123456"; 	//��¼���� 

typedef struct course {			//�γ���Ϣ 
	float mark;
	char name[Z];
}C;

typedef struct student {			//ѧ����Ϣ 
	char name[M];		//���� 
	char number[N];		//ѧ�� 
	char Class[M];		//�༶ 
	char grade[M];		//�꼶 
	C course[100];		//�γ�
	int n;				//�γ����� 
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

void lode(S *student)				//��¼���� 
{
	int k;
	printf("�����������ݻ����˳�����\n\n");
	printf("1:����Ա\n2����ʦ\n3��ѧ��\n���������ּ��˳�\n");
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

void lodestudent(S *student)		//ѧ����¼
{
	char num[N];
	char node[N];
	S *p;
	printf("���������ѧ�ţ�");
	scanf("%s", num);
	printf("�������룺");
	getchar();				//�Ե����з�
	scanf("%s", node);
	while (1)
	{
		p = student;
		while (p != NULL && strcmp(num, p->number))
			p = p->next;
		if (p == NULL)
		{
			printf("û�и�ѧ������������ѧ��\n\n");
			printf("������ѧ�ţ�");
			scanf("%15s", num);
			system("cls");
		}
		else if (strcmp(node, code))
		{
			printf("�������������������\n\n");
			printf("���������룺");
			scanf("%15s", node);
			system("cls");
		}
		else
		{
			system("cls");
			funcstudent(p,student);						//����ѧ��ģʽ 
			return;
		}
	}
}

void lodeteacher(S *student)				//��ʦ��¼ 
{
	char num[N];
	printf("�����ʦ��¼���룺");
	scanf("%15s", num);
	while (1)
	{
		if (strcmp(num, code))
		{
			printf("���������������\n");
			printf("�����룺");
			scanf("%15s", num);
			system("cls");
		}
		else
		{
			system("cls");
			functeacher(student);			//�����ʦģʽ 
			return;
		}
	}
}

void lodeadmin(S *student)				//����Ա��¼ 
{
	char num[N];
	printf("�������Ա��¼���룺");
	scanf("%15s", num);
	while (1)
	{
		if (strcmp(num, code))
		{
			printf("���������������\n");
			printf("�����룺");
			scanf("%15s", num);
			system("cls");
		}
		else
		{
			system("cls");
			funcadmin(student);				//�������Աģʽ 
			break;
		}
	}
}

void funcadmin(S *student)					//����Աģʽ 
{
	printf("�ѽ������Աģʽ\n\n");

	int k;
	printf("����������ѧ������Ϣ��\n");
	S *p = student;
	printf("\tѧ��\t\t����\t�༶\t�꼶\t�γ̼�����\n");
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
	printf("������������Ĳ�����\n");
	printf("1�����ѧ��\n2��ɾ��ѧ��\n3����ӿγ�\n4��ɾ���γ�\n5���˳�\n�����������ַ�����һ��\n");
	printf("�����룺");
	scanf("%d", &k);
	switch (k)
	{
	case 1: {
		system("cls");
		addstudent(student);			//���ѧ��ģʽ 
		break;
	}
	case 2: {
		system("cls");
		deletestudent(student);			//ɾ��ѧ��ģʽ 
		break;
	}
	case 3: {
		system("cls");
		addcourse(student);				//��ӿγ�ģʽ 
		break;
	}
	case 4: {
		system("cls");
		deletecourse(student);			//ɾ���γ�ģʽ 
		break;
	}
	case 5: {
		return;						//�˳� 
	}
	default: {
		system("cls");
		lode(student);					//������һ�� 
	}
	}
}

S *readstudent()				//��ȡѧ����Ϣ 
{
	S *p, *head = NULL;
	FILE *fp = fopen("inf.txt", "r");
	if (fp == NULL)
	{
		printf("û��ѧ������Ϣ\n");
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

void addstudent(S *student)			//���ѧ�� 
{
	S *p = student;
	S *q;
	FILE *fp = fopen("inf1.txt", "w");
	if (fp == NULL)
	{
		printf("�ļ���ʧ��\n");
		exit(0);
	}
	printf("�ѽ������ѧ��ģ��\n\n");
	while (1)
	{
		printf("����������ѧ������Ϣ��\n");
		printf("\tѧ��\t\t����\t�༶\t�꼶\t�γ̼�����\n");
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
		printf("�������ѧ����ѧ�š��������༶���꼶���м��Կո������:\n\n");
		scanf("%s %s %s %s", q->number, q->name, q->Class, q->grade);
		while (p != NULL && strcmp(q->number, p->number))
			p = p->next;
		if (p != NULL)
			printf("��ѧ����Ϣ���Ѿ�����\n\n");
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
			printf("��ӳɹ�\n\n");
		}
		int a;
		printf("�Ƿ�������ѧ��������1����������2������һ��\n");
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

void deletestudent(S *student)				//ɾ��ѧ�� 
{
	FILE *ftp;
	ftp = fopen("inf1.txt", "w");
	if (ftp == NULL)
	{
		printf("û��ѧ����Ϣ���޷�ɾ��ѧ��\n");
		exit(0);
	}
	S *pre, *p;
	while (1)
	{
		printf("����������ѧ������Ϣ��\n");
		p = student;
		printf("\tѧ��\t\t����\t�༶\t�꼶\t�γ̼�����\n");
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
		printf("����Ҫɾ����ѧ��ѧ�ţ�");
		scanf("%s", num);
		while (strcmp(num, p->number)&& p->next != NULL)			//�����Ƿ��и�ѧ�� 
		{
			pre = p;
			p = p->next;
		}
		if (strcmp(num, p->number))
			printf("��ѧ����Ϣδ����ӻ��ѱ�ɾ��\n");
		else												//�ҵ���������Ϣ�� 
		{
			if (p == student)
				student = p->next;
			else
				pre->next = p->next;
			free(p);
			printf("ɾ���ɹ�\n\n");
		}

		char a;
		printf("�Ƿ����ɾ��ѧ��������1��������������������һ��");
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

void addcourse(S *student)					//��ӿγ�
{
	FILE *fp;
	fp = fopen("inf1.txt", "w");
	if (fp == NULL)
	{
		printf("û��ѧ����Ϣ���޷���ӿγ�\n");
		exit(0);
	}

	char num[25];
	S *p;
	while (1)
	{
		p = student;
		printf("���������еĿγ̣�\n");
		for (int i = 0; i < p->n; i++)
			if (p->course[i].mark!=-2)
				printf("\t\t%s\n", p->course[i].name);
		printf("\n");

		printf("������Ҫ���ӵĿγ�����");
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
					printf("��ӳɹ�\n\n");
			}
			else if (p->course[i].mark == -2)
			{
				p->course[i].mark = -1;
				if(p->next==NULL)
					printf("��ӳɹ�\n\n");
			}
			else if (p->course[i].mark >= -1)
			{
				printf("�ÿγ��Ѿ����\n\n");
				break;
			}
			p = p->next;
		}

		printf("�Ƿ������ӿγ̣�\n");
		printf("����1��������������������һ��\n\n");
		printf("�����룺");
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

void deletecourse(S *student)			//ɾ��ѧ���γ� 
{
	S *p;
	FILE *fp;
	fp = fopen("inf1.txt", "w");
	if (fp == NULL)
	{
		printf("û��ѧ����Ϣ���޷�ɾ���γ�");
		exit(0);
	}
	while (1)
	{
		p = student;
		printf("���������еĿγ̣�\n");
		for (int i = 1; i < p->n; i++)
			if (p->course[i].mark != -2)
				printf("\t\t%s\n", p->course[i].name);
	
		char num[Z];
		p = student;
		printf("������Ҫɾ���Ŀγ�����");
		scanf("%s", num);
		while (p != NULL)
		{
			int i;
			for(i=0;i<p->n;i++)
				if (!strcmp(num, p->course[i].name))
					break;
			if (i >= p->n || p->course[i].mark == -2)
			{
				printf("�ÿγ̻�δ���\n\n");
				break;
			}
			else
			{
				p->course[i].mark = -2;
				if (p->next == NULL)
					printf("ɾ���ɹ�\n\n");
			}
			p = p->next;
		}
		printf("�Ƿ����ɾ���γ̣�\n");
		printf("����1��������������������һ��\n\n");
		printf("�����룺");
		char a;
		getchar();			//�Ե����з�
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

void functeacher(S *student)			//��ʦ��¼ģʽ 
{
	printf("�ѽ����ʦģʽ\n\n");
	printf("����������ѧ������Ϣ��\n");
	S *p = student;
	printf("\tѧ��\t\t����\t�༶\t�꼶\t�γ̼�����\n");
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
	printf("������������Ĳ�����\n");
	printf("1������ѧ���γ̷���\n2��ͳ��ĳ�ſεļ����ʺ�ƽ����\n3��ͳ������ѧ����ĳ�ſεķ���\n4���˳�\n��������������һ��\n");
	printf("�����룺");
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

void addmark(S *student)				//���ѧ���ɼ� 
{
	S *p;
	FILE *fp;
	fp = fopen("inf1.txt", "w");
	if (fp == NULL)
	{
		printf("û��ѧ����Ϣ���޷���ӷ���\n");
		exit(0);
	}
	while (1)
	{
		printf("����������ѧ����ѧ�ź�������\n");
		p = student;
		printf("\tѧ��\t\t����\n");
		while (p != NULL)
		{
			printf("\t%s\t%s\n", p->number, p->name);
			p = p->next;
		}
		printf("\n");
	
		p = student;
		printf("���������еĿγ̣�\n");
		for (int i = 1; i < p->n; i++)
			if (p->course[i].mark != -2)
				printf("\t\t%s\n", p->course[i].name);
		printf("\n\n");

		char num[Z];
		printf("����Ҫ��ӿγ̵�ѧ��ѧ�ţ�");
		scanf("%s", num);
		while (p != NULL && strcmp(num, p->number))
			p = p->next;
		if (p == NULL)
			printf("��ѧ����Ϣδ����ӻ��Ѿ���ɾ��\n");
		else
		{

			int i = 0;
			printf("������Ҫ���ӷ����Ŀγ�����");
			scanf("%s", num);
			while (1)
			{
				if (!strcmp(num, p->course[i].name))
				{
					if (p->course[i].mark == -2)
						break;
					printf("���������");
					scanf("%f", &p->course[i].mark);

					if (p->course[i].mark < 0 || p->course[i].mark>100)
					{
						i--;
						printf("������0��100֮�����\n\n");
					}
					else
					{
						printf("��ӳɹ�\n\n");
						break;
					}
				}
				i++;
				if (i >= p->n)
					break;
			}
			if (i >= p->n || p->course[i].mark == -2)
				printf("û�иÿγ�\n\n");

		}
		printf("�Ƿ������ӳɼ���\n");
		printf("����1�����������������ַ�����һ��\n\n");
		printf("�����룺");
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

void average(S *student)		//ͳ�ƾ��ֺͼ����� 
{
	S *p = student;
	
	while (1)
	{
		float n = 0, n1 = 0,n2=0;			//n����ѧ�������� n1������������� a��ƽ����
		float a = 0;

		p = student;
		printf("���������еĿγ̣�\n");
		for (int i = 0; i < p->n; i++)
			if (p->course[i].mark != -2)
				printf("\t\t%s\n", p->course[i].name);
		printf("\n\n");

		char num[Z];
		printf("����Ҫ���ҵĿγ�����");
		scanf("%s", num);

		while (p != NULL)					//����ƽ���ֺͼ����� 
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
			printf("��ѧ�Ʋ�����\n\n");
		else if (n == 0)
			printf("û��ѧ���޸��ǿγ�\n\n");
		else
			printf("�ÿ�Ŀ��ƽ����Ϊ��%.2f��������Ϊ��%.2f%%\n", a / n, (1 - n1 / n) * 100);

		printf("�Ƿ�������ң�\n����1�����������������ַ�����һ��\n\n");
		printf("�����룺");
		int b;
		scanf("%d", &b);
		system("cls");
		if (b !=1)
			break;
	}
	functeacher(student);
}

void certaincourse(S *student)			//��������ѧ��ĳ��ѧ�Ƶķ��� 
{
	S *p = student;

	while (1)
	{
		int n = 0,n1=0;	//������ 
		p = student;

		printf("���������еĿγ̣�\n");
		for (int i = 0; i < p->n; i++)
			if (p->course[i].mark != -2)
				printf("\t\t%s\n", p->course[i].name);
		printf("\n\n");

		char num[Z];
		printf("����Ҫ���ҵĿγ�����");
		scanf("%s", num);

		while (p != NULL)
		{
			for (int i = 0; i < p->n; i++)
			{
				if (!strcmp(num, p->course[i].name) && p->course[i].mark >= 0)
				{
					printf("\t%s��%.2f\n", p->name, p->course[i].mark);
					n++;
				}
				if (!strcmp(num, p->course[i].name) && p->course[i].mark >= -1)
					n1++;
			}
			p = p->next;
		}
		if (n1 == 0)
			printf("�ÿγ̲�����\n\n");
		else if (n == 0)
			printf("û��ѧ���޸��ǿγ�\n\n");
		printf("�Ƿ�������ң�\n����1�����������������ַ�����һ��\n\n");
		int b;
		printf("�����룺");
		scanf("%d", &b);
		system("cls");
		if (b != 1)
			break;
	}
	functeacher(student);
}

void funcstudent(S *p,S *student)			//ѧ������
{
	printf("��ĸ���Ϣ���£�\n");
	printf("\tѧ��\t\t����\t�༶\t�꼶\t�γ̼�����\n");
	printf("\t%s\t%s\t%s\t%s", p->number, p->name, p->Class, p->grade);
	printf("\t%s %.2f\n", p->course[0].name, p->course[0].mark);
	for (int i = 1; i < p->n; i++)
		if(p->course[i].mark>=0)
			printf("\t\t\t\t\t\t%s %.2f\n", p->course[i].name, p->course[i].mark);
	printf("\n\n");
	char a;
	getchar();			//�Ե����з�
	printf("����1������һ���������������˳�\n\n");
	printf("�����룺");
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