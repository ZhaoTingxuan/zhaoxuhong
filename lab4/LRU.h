#ifndef LAB4_LRU_H
#define LAB4_LRU_H

#include <stdio.h>
#include "test.h"
#include <time.h>

int LRU(MemSchedule s1)
{
	//start��finish���ڼ�¼ʱ��
	clock_t start, finish;
	//num��ʾ���ȼ���ÿ����һ��ָ���һ���������ȼ���͵ľ������û�б����ʵĵ��ģ�ѡ�����滻
	int miss = 0;
	start = clock();
	printf("***************����û��㷨*****************\n");
	printf("seq\t");
	for (int i = 0; i<s1.e; i++)
	{
		printf("%d\t", i + 1);
	}
	printf("\n");
	for (int i = 0; i<s1.length; i++)
	{
		int pointer = s1.VisitSeq[i];
		printf("%d:\t", pointer);
		//�жϵ�ǰ�Ƿ��п��������
		if (s1.work_len<s1.e)
		{
			//�˴���flag�����жϵ�ǰ���ʵ��������Ѿ����ڴ���
			int flag = 0;
			//ɨ��һ�鵱ǰ���ڴ�飬���и������ȼ������Ͳ�ѯ��һ�����ʵ�ҳ���Ƿ����ڴ���
			for (int m = 0; m<s1.work_len; m++)
			{
				if (s1.WorkSpace[m].seq == pointer)
					//���������ڴ�����flag��Ϊ1
					flag = 1;
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
			//��ʾû�п����ڴ��
			//����ʹ��flag��ʾ��ǰ��������ڴ����Ƿ����
			int flag = 0;
			for (int m = 0; m<s1.work_len; m++)
			{
				if (s1.WorkSpace[m].seq == pointer)
					flag = 1;
			}
			if (flag == 1)
			{
				//��ʾ�ڴ���Ѿ����ֹ�
				s1.change = -1;
			}
			if (flag == 0)
			{
				//min��ʾ��С���ȼ����Ǹ��ڴ���
				int min_pri = -10000;
				for (int m = 0; m<s1.work_len; m++)
				{
					int n = SearchVisitSqe(s1.VisitSeq, i, s1.WorkSpace[m].seq, 1, i);
					s1.WorkSpace[m].priority = n;
					if (n > min_pri)
					{
						s1.change = m;
						min_pri = n;
					}
				}
				//��ʾ�����滻�仯�Ŀ��s1.change
				s1.WorkSpace[s1.change].seq = pointer;
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
		finish = clock();
	}

	printf("******************�㷨����**************\n");
	printf("ȱҳ��:\t%.2f %%\n", (miss*1.0) / s1.length * 100);
	printf("ʱ�俪��:\t%.2f ms\n", (double)(finish - start));
	free(s1.WorkSpace);
	free(s1.VisitSeq);
	return 0;
}

#endif //LAB4_LRU_H