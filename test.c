#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int main()
{
	int mode;

	while (1)
	{
		printf("Single Precision (32��Ʈ)=0\nDouble Precision (64��Ʈ)=1\n��弱��:");
		scanf("%d", &mode);

		if (mode == 0)
		{
			char bits[33];
			printf("32��Ʈ�� �Է��Ͻʽÿ�\n");
			scanf("%s", &bits);
			printf("�Է��Ͻ� ��Ʈ�� ������ �����ϴ�\n");
			for (int i = 0; i < 32; i++)
			{
				printf("%c", bits[i]);
			}
			printf("\n");

			int exp[8];
			printf("��ȣ��Ʈ:%c\n������:", bits[0]);
			for (int i = 1; i < 9; i++)
			{
				exp[i - 1] = (bits[i] - '0');
				printf("%c", bits[i]);
			}
			double frac[23];
			printf("\nFraction�κ�:");
			for (int i = 9; i < 32; i++)
			{
				frac[i - 9] = (bits[i] - '0');
				printf("%c", bits[i]);
			}
			printf("\n\n\n���� ���Ŀ� ���� 10�������� ����ϰڽ��ϴ�.");
			
			int tmp = 0;
			for (int i = 8; i>0; i--)
			{
				if (exp[i-1]==1)
				{
					tmp = tmp + pow(2, 8-i);
				}
			}
			int exp_final = tmp - 127;

			double tmp2 = 0;
			for (int i = 0; i < 23; i++)
			{
				if (frac[i]== 1)
				{
					tmp2 = tmp2 + pow(2, -1*(i+1));
				}
			}
			double frac_final = tmp2 + 1;

			int signbit;
			if (bits[0]=='0')
			{
				signbit = 1;
			}
			else
			{
				signbit = -1;
			}

			if (exp_final==-127)
			{
				if (tmp2==0 && signbit ==1)
				{
					printf("\nDenormal Number �Դϴ�.\nexp�� Frac �κ��� ���� 0�̹Ƿ� �����+0.0\n");
					goto ask;
				}
				else if(tmp2==0 && signbit == -1)
				{
					printf("\nDenormal Number �Դϴ�.\nexp�� Frac �κ��� ���� 0�̹Ƿ� �����-0.0\n");
					goto ask;
				}
				double result_denormal = signbit * tmp2 * pow(2, exp_final);
				printf("\nDenormal Number�Դϴ�.\nx=(-1)^s+(0+fraction)*2^(-127)�̹Ƿ�\n����� %.15f\n", result_denormal);
				goto ask;
			}
			double result = signbit * frac_final * pow(2, exp_final);
			printf("\n\n\n%d * %.15f * 2^(%d) = %.15f\n", signbit, frac_final, exp_final, result);

			if (exp_final == 128)
			{
				if (tmp2==0 && signbit==1)
				{
					printf("\nexp�κ��� ���� 1�̰� Frac�κ��� ���� 0�̹Ƿ� \n����� +Infinity�Դϴ�\n");
					goto ask;
				}
				else if(tmp2==0 && signbit==-1)
				{
					printf("\nexp�κ��� ���� 1�̰� Frac�κ��� ���� 0�̹Ƿ� \n����� -Infinity�Դϴ�\n");
					goto ask;
				}
				else
				{
					printf("\nexp�κ��� ���� 1�̰� Frac�κ��� ���� 0�� �ƴϹǷ� \n ����� NaN�Դϴ�\n");
					goto ask;
				}
			}
			
		ask:
			int repeat;
			printf("�ٽ��Ͻðڽ��ϱ�? Yes:0,No:1\n");
			scanf("%d", &repeat);
			if (repeat)
			{
				goto finish;
			}
		}
	}

finish:

	return 0;
}