#ifndef LAB4_PBA_H
#define LAB4_PBA_H
#include "test.h"
#include <stdio.h>
#include <time.h>

int PBA(MemSchedule s1)
{
	clock_t start, finish;
	start = clock();
	int miss = 0;
	printf("***************�����ȳ��㷨*****************\n");
	printf("seq\t");
	for (int i = 0; i<s1.e; i++)
	{
		printf("%d\t", i + 1);
	}
	printf("\n");
	for (int i = 0; i<s1.length; i++)
	{
		//pointerָ��ǰ���ڷ��ʵ���������
		int pointer = s1.VisitSeq[i];
		printf("%d:\t", pointer);
		//�жϵ�ǰ�Ƿ��п��������
		if (s1.work_len<s1.e)
		{
			//��ʾ����ʣ��Ŀ��������
			int flag = 0;//flag���ڱ����һ��ҳ���Ƿ����������
			//ɨ��һ�鹤�������鿴��һ��ҳ���Ƿ����
			for (int m = 0; m<s1.work_len; m++)
			{
				s1.WorkSpace[m].priority--;
				if (s1.WorkSpace[m].seq == pointer)
					//���������ڴ�����flag��Ϊ1
				{
					flag = 1;
					s1.WorkSpace[m].priority = s1.e;
				}
			}
			if (flag == 1)
			{
				//����һ�����ʵ�ҳ�����ڴ��У���û�з���ȱҳ������Ҫ�����滻,changeֵ��ʾ��һ��û��
				//ȱҳ
				s1.change = -1;
			}
			if (flag == 0)
			{
				//����һ��Ҫ���ʵ�ҳ�Ų����ڴ��У�����ȱҳ����Ҫֱ�ӽ��µ�ҳ�ŷ�����һ�����п���
				//���ȸ���ȫ�����ȼ�
				//ֱ�ӽ���һ�����п��滻
				s1.WorkSpace[s1.work_len].seq = pointer;
				s1.WorkSpace[s1.work_len].priority = s1.e;
				//���滻�仯�˵��ڴ���д��
				s1.change = s1.work_len;
				//����ʹ�õ��ڴ�������һ
				s1.work_len++;
			}
			//��ӡ��Ϣ
			for (int k = 0; k<s1.work_len; k++)
			{
				//���������ҳ���û������ӡ��@����Ϣ
				if (k == s1.change)
				{
					printf("%d@\t", s1.WorkSpace[k].seq);
					//ȱҳ�ʼ�һ
					miss++;
				}
				else
					printf("%d\t", s1.WorkSpace[k].seq);
			}
			//ʣ�¿��е�ҳ��ȫ����ӡ*
			for (int j = 0; j<s1.e - s1.work_len; j++)
			{
				printf("*\t");
			}


		}
		else
		{
			//��ʾû�п��������
			//����ʹ��flag��ʾ��ǰ����ҳ���Ƿ����ڴ����
			int flag = 0;
			for (int m = 0; m<s1.work_len; m++)
			{
				//ÿ����һ���µ�ҳ�棬�������ȼ�ȫ���½�һ
				s1.WorkSpace[m].priority--;
				if (s1.WorkSpace[m].seq == pointer)
				{
					flag = 1;
					s1.WorkSpace[m].priority = s1.e;

				}
			}
			if (flag == 1)
			{
				//��ʾ�ڴ���Ѿ����ֹ�
				s1.change = -1;
			}
			if (flag == 0)
			{
				//min��ʾ��С���ȼ����Ǹ��ڴ���
				int min_pri = 0xffffff;
				for (int m = 0; m<s1.work_len; m++)
				{
					//�������㷨������ֻ�����ȼ��������ķ�ʽ��ͬ
					int n = s1.WorkSpace[m].priority;
					if (n < min_pri)
					{
						s1.change = m;
						min_pri = n;
					}
				}
				//��ʾ�����滻�仯�Ŀ��s1.change
				s1.WorkSpace[s1.change].seq = pointer;
				//�����»����ҳ�����ȼ�Ϊwork_len
				s1.WorkSpace[s1.change].priority = s1.e;
			}
			for (int m = 0; m<s1.e; m++)
			{
				if (m == s1.change)
				{
					printf("%d@\t", s1.WorkSpace[m].seq);
					miss++;
				}
				else
					printf("%d\t", s1.WorkSpace[m].seq);
			}


		}
		printf("\n");
	}
	finish = clock();
	printf("******************�㷨����**************\n");
	printf("ȱҳ��:\t%.2f %%\n", (miss*1.0) / s1.length * 100);
	printf("ʱ�俪��:\t%.2f ms\n", (double)(finish - start));
	free(s1.WorkSpace);
	free(s1.VisitSeq);
	return  0;
}
#endif //LAB4_PBA_H