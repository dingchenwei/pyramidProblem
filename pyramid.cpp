#include <stdio.h>

//����������ṹ���ṹ��ԱΪ�ػ�
//���ȡ�����������Լ����������͡� 
struct pyramid
{
	int base;
	double sum;
	char type;		
}Aftersort[323], target[100];		//Aftersort�Ĺ�ģ��High�ͽ������ĸ���+Low�ͽ������ĸ���-3ȷ�� 

int Upbound(double num);

int funct(int pyramids_used, double num, int max);

int main(void)
{
	int pyramids_used, upbound, flag, index, case_input;
	double num;			
	
	//�����������ڲ�ͬ���������¼������Ҫ��ķ���  
	case_input=0;				
	scanf("%lf", &num);
	if (num <= 0){  //�Ƿ�����
        printf("Input number is invalid!\n");
        return 0;
    }
	while(num!=0)			//����0��ʾ���� 
	{
		upbound=Upbound(num);								//�������ý����������Ͻ� 
	
		for(pyramids_used=1; pyramids_used<=upbound; pyramids_used++)	//��������pyramids_used������������������� 
		{
			flag=funct(pyramids_used, num, 322);
			if(flag==1)													//flag=1,˵���ҵ�����Ҫ��ķ����������Ӧ�Ľ����� 
			{	
				printf("Case %d: ", case_input+1);
				
				for(index=pyramids_used-1; index>=1; index--)    
					printf("%d%c ", target[index].base, target[index].type);		
								
				printf("%d%c", target[index].base, target[index].type);	
				printf("\n");
				
				break;
			}
		}	

		if(flag==0)														//flag=0,˵�������ڷ���Ҫ��ķ��������impossible 
		{ 
			printf("Case %d: impossible", case_input+1); 
			printf("\n");
		}	
		
		case_input++;
		scanf("%lf", &num);
	} 
	
	return 0;
}
 
int Upbound(double num)           
{
	int i, upbound, total=0;
	int base_h=2, base_l=3;		 				//����������������2����High�͵ػ����Ȳ�����2��Low�͵ػ����Ȳ�����3��
	struct pyramid Hightype[145], Lowtype[182]; //���������������10^6��High�ͽ�������С�ػ�����Ϊ144
	 											//���������������10^6��Low�ͽ�������С�ػ�����Ϊ181
	
	//�����������ͽ��������õ���������
    //���Խ��������������Ϊ����������
	Hightype[0].sum = Hightype[1].sum = 0;      //�ػ�����С��2��High��Ϊ���ý����� 
	for(i=2; i<=144; i++)
	{
		Hightype[i].base=i;
		Hightype[i].sum=i*(i+1)*(2*i+1)/6;		//�洢����high�ͽ������Ľṹ��Ϣ������Ϊ2����144����
		Hightype[i].type='H';
	}
	
	Lowtype[0].sum = Lowtype[1].sum = Lowtype[2].sum = 0;  //�ػ�����С��3��Low��Ϊ���ý����� 
	for(i=3; i<=181; i++)
	{
		Lowtype[i].base=i; 
		Lowtype[i].sum=i*(i+1)*(i+2)/6;			//�洢����low�ͽ������Ľṹ��Ϣ������Ϊ3����181���� 
		Lowtype[i].type='L';
	} 
	
	i=1;
	
	//�Խ��������������Ϊ�����кϲ�����
	while(base_h<=144&&base_l<=181)
	{
		if(Hightype[base_h].sum>=Lowtype[base_l].sum)
		{
			Aftersort[i]=Lowtype[base_l];
			base_l+=1;
		}
		else 
		{
			Aftersort[i]=Hightype[base_h];
			base_h+=1;
		}
		
		i+=1;		
	}
	
	if(base_h==145)
		while(i<=322)
		{
			Aftersort[i]=Lowtype[base_l];
			i++;
			base_l++;
		} 
	else
		while(i<=322)
		{
			Aftersort[i]=Hightype[base_h];
			i++;
			base_h++;
		} 
	
	//���������Ҫ���ٸ������� 
	for(upbound=1;upbound<=322;upbound++) 
    {
		total+=Aftersort[upbound].sum;
    	if(total>=num)
        	break;
	}
	
	return upbound;
}

int funct(int pyramids_used, double num, int max)
{
	int flag=0;
	
	if(num==0)								  //����������ǡ�����꣬˵�����ַ�������Ҫ�� 
		return 1;
	
	if(max<=0)								  //�������Ѿ������ˣ�˵��������Ҫ�� 
		return 0;
		
	if(pyramids_used*Aftersort[max].sum<num)  //��Ϊ��������¿϶��ò������������壬���Կ϶�������Ҫ�� 
		return 0;
	
	while(Aftersort[max].sum>num)			  //����max������������������������������������ 
	{										  //��ô��max��һ������һ�������������ٵĽ���
		max-=1;								  //�� ��ֱ���ҵ�һ�������������������Ľ����� 
		if(max<=0)							  //Ϊֹ����û�������Ľ���������˵��������Ҫ�� 
			return 0;				
	}	
	
	while(max>=1)			
	{
		flag=funct(pyramids_used-1, num-Aftersort[max].sum, max-1);		//�ݹ� 
										  
		if(flag==1)
		{	
			target[pyramids_used-1]=Aftersort[max];
			return 1;
		}
		
		max--;															 
	}
	return 0;
	
} 
