
#ifndef LAB4_bCLOCK_H
#define LAB4_BCLOCK_H

#include "test.h"
#include <stdio.h>
#include <time.h>

int Clock(MemSchedule s1)
{
	int miss = 0;
	clock_t start, finish;
	start = clock();
	printf("***************�Ľ�Clock�㷨*****************\n");
	printf("seq\t");
	for (int i = 0; i<s1.e; i++)
	{
		printf("[%d]UM\t", i + 1);
	}
	printf("\n");
	for (int i = 0; i<s1.length; i++)
	{
		//pointerָ����һ����Ҫ���ʵ�ҳ��
		int pointer = s1.VisitSeq[i];
		printf("%d:\t", pointer);
		//�жϵ�ǰ�Ƿ��п��������
		if (s1.work_len < s1.e)
		{
			//��ʾ���п��������
			int flag = 0;//��ʾ��һ��Ҫ���ʵ�ҳ���Ƿ����ڴ����
			int flag1 = 0;//�������һ��ҳ����ͬ���ڴ���
			for (int m = 0; m<s1.work_len; m++)
			{
				if (s1.WorkSpace[m].seq == pointer)
					//���������ڴ�����flag��Ϊ1
				{
					flag = 1;
					flag1 = m;
					break;

				}
			}
			if (flag == 1)
			{
				//����һ�����ʵ�ҳ�����ڴ��У���û�з���ȱҳ������Ҫ�����滻,changeֵ��ʾ��һ��û��
				//ȱҳ
				s1.change = -1;
				s1.WorkSpace[flag1].Modified = 'Y';
			}
			if (flag == 0)
			{
				//����һ��Ҫ���ʵ�ҳ�Ų����ڴ��У�����ȱҳ����Ҫֱ�ӽ��µ�ҳ�ŷ�����һ�����п���
				//���ȸ���ȫ�����ȼ�
				//ֱ�ӽ���һ�����п��滻
				s1.WorkSpace[s1.work_len].seq = pointer;
				//���ոյ����ڴ�������ŵ�ʹ��λ����Ϊ1
				s1.WorkSpace[s1.work_len].Used = 'Y';
				s1.WorkSpace[s1.work_len].Modified = 'N';
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
					printf("[%d]%c%c@\t", s1.WorkSpace[k].seq, s1.WorkSpace[k].Used, s1.WorkSpace[k].Modified);
					//ȱҳ�ʼ�һ
					miss++;
				}
				else
					printf("[%d]%c%c\t", s1.WorkSpace[k].seq, s1.WorkSpace[k].Used, s1.WorkSpace[k].Modified);
			}
			//ʣ�¿��е�ҳ��ȫ����ӡ*
			for (int j = 0; j<s1.e - s1.work_len; j++)
			{
				printf("*\t");
			}



		}
		else
		{
			//�˴���ʾû�п���ҳ������
			//����ʹ��flag��ʾ�µ����ҳ���Ƿ����ڴ����Ѿ�����
			int flag = 0;
			int flag1 = 0;//flag1��¼��һ��Ҫ���ʵ�ҳ�����ڴ��еĿ��
			for (int m = 0; m<s1.work_len; m++)
			{
				if (s1.WorkSpace[m].seq == pointer)
				{
					flag = 1;
					flag1 = m;
					break;
				}
			}
			if (flag == 1)
			{
				//��ʾ�ڴ���Ѿ����ֹ�
				s1.WorkSpace[flag1].Modified = 'Y';
				s1.change = -1;
			}
			if (flag == 0)
			{
				//��ʾ�ڴ����û�г��ֹ�
				for (int t = 0; t<2; t++)
				{
					int flag = 0;
					for (int m = 0; m<s1.work_len; m++)
					{
						if (s1.WorkSpace[m].Used == 'N' && s1.WorkSpace[m].Modified == 'N')
						{
							s1.change = m;
							flag = 1;
							break;
						}
					}
					if (flag == 0)
					{
						for (int m = 0; m<s1.work_len; m++)
						{
							if (s1.WorkSpace[m].Used == 'N' && s1.WorkSpace[m].Modified == 'Y')
							{
								s1.change = m;
								flag = 1;
								break;
							}
							s1.WorkSpace[m].Used = 'N';
						}
					}
					if (flag != 0)
						break;

				}
				s1.WorkSpace[s1.change].seq = pointer;
				s1.WorkSpace[s1.change].Used = 'Y';
				s1.WorkSpace[s1.change].Modified = 'N';

			}
			//��ӡ��Ϣ
			for (int k = 0; k<s1.work_len; k++)
			{
				//���������ҳ���û������ӡ��@����Ϣ
				if (k == s1.change)
				{
					printf("[%d]%c%c@\t", s1.WorkSpace[k].seq, s1.WorkSpace[k].Used, s1.WorkSpace[k].Modified);
					//ȱҳ�ʼ�һ
					miss++;
				}
				else
					printf("[%d]%c%c\t", s1.WorkSpace[k].seq, s1.WorkSpace[k].Used, s1.WorkSpace[k].Modified);
			}
		}
		printf("\n");
	}
	finish = clock();
	printf("******************�㷨����**************\n");
	printf("ȱҳ��:\t%.2f %%\n", (miss*1.0) / s1.length * 100);
	printf("ʱ�俪��:%.2f ms\n", (double)(finish - start));
	free(s1.WorkSpace);
	free(s1.VisitSeq);
	return 0;
}
#endif //LAB4_CLOCK_H