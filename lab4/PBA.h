#ifndef LAB4_TEST_H
#define LAB4_TEST_H

#include <stdio.h>
#include <stdlib.h>
#include <queue>
using namespace std;
//
typedef struct WorkItem
{
	int seq;
	int priority;
	char Used;
	char Modified;
}WorkItem;

typedef struct MemSchedule
{
	WorkItem* WorkSpace = NULL;
	int *VisitSeq = NULL;
	int N = 64;
	int p = 0;
	//��������С
	int e = 5;
	int m = 1;
	//����������г���o
	int length;
	//��ǰ��ʹ���������
	int work_len = 0;
	//�����滻��������
	int change = 0;
	float t, r;
	//   ���г���
	int queue_free_len = 0;
	int queue_modified_len = 0;
	WorkItem free[2];
	WorkItem Modified[2];


}MemSchedule;


MemSchedule SetMemSchedule(MemSchedule s1)
{
	printf("�����������ڴ�ߴ�N:");
	scanf_s("%d", &s1.N);
	printf("�����빤������ʼλ��p:");
	scanf_s("%d", &s1.p);
	printf("�����빤��������ҳ��e:");
	scanf_s("%d", &s1.e);
	printf("�����빤�����ƶ�Ч��m:");
	scanf_s("%d", &s1.m);
	printf("**************����***************\n");
	printf("�����ڴ�:%d\t", s1.N);
	printf("��ʼλ��p:%d\n", s1.p);
	printf("����ҳ��e:%d\t", s1.e);
	printf("�ƶ�Ч��m:%d\n", s1.m);
	printf("********************************\n");
	return s1;

}

MemSchedule GeneVisitSeq(int l)
{
	MemSchedule schedule1;
	printf("�Ƿ��趨�����㷨����(Y/N):");
	char flag;
	scanf_s("%c", &flag);
	if (flag == 'Y')
	{
		schedule1 = SetMemSchedule(schedule1);
	}
	schedule1.t = rand() % 1000 / 1000.0;
	schedule1.VisitSeq = (int *)malloc(l*sizeof(schedule1.m));
	printf("��������ڴ�������У�\n");
	for (int i = 0; i<l; i++)
	{
		for (int j = 0; j<schedule1.m; j++)
		{
			schedule1.VisitSeq[i*schedule1.m + j] = rand() % schedule1.e + schedule1.p;
			printf("%d ", schedule1.VisitSeq[i*schedule1.m + j]);
		}
		schedule1.r = rand() % 1000 / 1000.0;
		if (schedule1.r<schedule1.t)
		{
			schedule1.p = (schedule1.p + 1) % schedule1.N;
		}
	}
	printf("\n");
	schedule1.length = l*schedule1.m;
	schedule1.WorkSpace = (WorkItem *)malloc(schedule1.e *sizeof(WorkItem));
	return schedule1;
}

//�˺���������ǰ��������ѯ����������ĳ��ҳ�ų��ֵ�λ��
// seq �����Ƿ������У�work_now�ǵ�ǰ�������е�λ�ã�target��Ŀ��ҳ�ţ�direct�ǲ�ѯ���� 0��ʾ����������1��ʾ����������
//length��ʾ���г���
//����ֵ����δ�ҵ��򷵻�-1���ҵ����ؾ���
int SearchVisitSqe(int seq[], int work_now, int target, int direct, int length)
{
	if (direct == 0)
	{
		//��ָ�������Ǵ�ǰ����������ʱ��
		for (int i = 0; i<length - work_now; i++)
		{
			if (seq[work_now + i + 1] == target)
				return i + 1;
		}
		return -1;
	}
	else
	{
		//��ָ�������ǴӺ���ǰ������ʱ��
		for (int i = 0; i<work_now; i++)
		{
			if (seq[work_now - i] == target)
				return i;
		}
		return -1;
	}
}

//�˺������ڴ�ӡ���ж��к��޸Ķ���
WorkItem* Insert(WorkItem* q, int len, WorkItem item, int priority)
{
	if (len == 0)
	{
		q[0] = item;
		return q;
	}
	else if (len == 1)
	{
		q[1] = item;
		return q;
	}
	else
	{
		if (q[0].priority > q[1].priority)
		{
			q[0] = item;
			return q;
		}
		else
		{
			q[1] = item;
			return q;
		}
	}

}

#endif //LAB4_TEST_H