#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int main()
{
	int mode;

	while (1)
	{
		printf("Single Precision (32비트)=0\nDouble Precision (64비트)=1\n모드선택:");
		scanf("%d", &mode);

		if (mode == 0)
		{
			char bits[33];
			printf("32비트를 입력하십시오\n");
			scanf("%s", &bits);
			printf("입력하신 비트는 다음과 같습니다\n");
			for (int i = 0; i < 32; i++)
			{
				printf("%c", bits[i]);
			}
			printf("\n");

			int exp[8];
			printf("부호비트:%c\n지수부:", bits[0]);
			for (int i = 1; i < 9; i++)
			{
				exp[i - 1] = (bits[i] - '0');
				printf("%c", bits[i]);
			}
			double frac[23];
			printf("\nFraction부분:");
			for (int i = 9; i < 32; i++)
			{
				frac[i - 9] = (bits[i] - '0');
				printf("%c", bits[i]);
			}
			printf("\n\n\n따라서 계산식에 따라 10진수값을 계산하겠습니다.");
			
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
					printf("\nDenormal Number 입니다.\nexp와 Frac 부분이 전부 0이므로 결과는+0.0\n");
					goto ask;
				}
				else if(tmp2==0 && signbit == -1)
				{
					printf("\nDenormal Number 입니다.\nexp와 Frac 부분이 전부 0이므로 결과는-0.0\n");
					goto ask;
				}
				double result_denormal = signbit * tmp2 * pow(2, exp_final);
				printf("\nDenormal Number입니다.\nx=(-1)^s+(0+fraction)*2^(-127)이므로\n결과는 %.15f\n", result_denormal);
				goto ask;
			}
			double result = signbit * frac_final * pow(2, exp_final);
			printf("\n\n\n%d * %.15f * 2^(%d) = %.15f\n", signbit, frac_final, exp_final, result);

			if (exp_final == 128)
			{
				if (tmp2==0 && signbit==1)
				{
					printf("\nexp부분이 전부 1이고 Frac부분이 전부 0이므로 \n결과는 +Infinity입니다\n");
					goto ask;
				}
				else if(tmp2==0 && signbit==-1)
				{
					printf("\nexp부분이 전부 1이고 Frac부분이 전부 0이므로 \n결과는 -Infinity입니다\n");
					goto ask;
				}
				else
				{
					printf("\nexp부분이 전부 1이고 Frac부분이 전부 0이 아니므로 \n 결과는 NaN입니다\n");
					goto ask;
				}
			}
			
		ask:
			int repeat;
			printf("다시하시겠습니까? Yes:0,No:1\n");
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