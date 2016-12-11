#include <stdio.h>

//构造金字塔结构，结构成员为地基
//长度、立方体个数以及金字塔类型。 
struct pyramid
{
	int base;
	double sum;
	char type;		
}Aftersort[323], target[100];		//Aftersort的规模由High型金字塔的个数+Low型金字塔的个数-3确定 

int Upbound(double num);

int funct(int pyramids_used, double num, int max);

int main(void)
{
	int pyramids_used, upbound, flag, index, case_input;
	double num;			
	
	//输入样例并在不同输入样例下计算符合要求的方案  
	case_input=0;				
	scanf("%lf", &num);
	if (num <= 0){  //非法输入
        printf("Input number is invalid!\n");
        return 0;
    }
	while(num!=0)			//输入0表示结束 
	{
		upbound=Upbound(num);								//计算所用金字塔数的上界 
	
		for(pyramids_used=1; pyramids_used<=upbound; pyramids_used++)	//不妨设用pyramids_used个金字塔可以完成任务 
		{
			flag=funct(pyramids_used, num, 322);
			if(flag==1)													//flag=1,说明找到符合要求的方案，输出相应的金字塔 
			{	
				printf("Case %d: ", case_input+1);
				
				for(index=pyramids_used-1; index>=1; index--)    
					printf("%d%c ", target[index].base, target[index].type);		
								
				printf("%d%c", target[index].base, target[index].type);	
				printf("\n");
				
				break;
			}
		}	

		if(flag==0)														//flag=0,说明不存在符合要求的方案，输出impossible 
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
	int base_h=2, base_l=3;		 				//金字塔层数不少于2，故High型地基长度不少于2，Low型地基长度不少于3。
	struct pyramid Hightype[145], Lowtype[182]; //立方体个数不少于10^6的High型金字塔最小地基长度为144
	 											//立方体个数不少于10^6的Low型金字塔最小地基长度为181
	
	//计算所有类型金字塔所用的立方体数
    //并以金字塔立方体个数为键进行排序。
	Hightype[0].sum = Hightype[1].sum = 0;      //地基长度小于2的High型为无用金字塔 
	for(i=2; i<=144; i++)
	{
		Hightype[i].base=i;
		Hightype[i].sum=i*(i+1)*(2*i+1)/6;		//存储所有high型金字塔的结构信息（基底为2——144）。
		Hightype[i].type='H';
	}
	
	Lowtype[0].sum = Lowtype[1].sum = Lowtype[2].sum = 0;  //地基长度小于3的Low型为无用金字塔 
	for(i=3; i<=181; i++)
	{
		Lowtype[i].base=i; 
		Lowtype[i].sum=i*(i+1)*(i+2)/6;			//存储所有low型金字塔的结构信息（基底为3——181）。 
		Lowtype[i].type='L';
	} 
	
	i=1;
	
	//以金字塔立方体个数为键进行合并排序
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
	
	//计算最多需要多少个金字塔 
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
	
	if(num==0)								  //所有立方体恰好用完，说明这种方案符合要求 
		return 1;
	
	if(max<=0)								  //金字塔已经用完了，说明不符合要求 
		return 0;
		
	if(pyramids_used*Aftersort[max].sum<num)  //因为这种情况下肯定用不完所有立方体，所以肯定不符合要求。 
		return 0;
	
	while(Aftersort[max].sum>num)			  //若第max个金字塔的立方体数超过了立方体总数， 
	{										  //那么将max减一来看下一个立方体数较少的金字
		max-=1;								  //塔 ，直到找到一个立方体数少于总数的金字塔 
		if(max<=0)							  //为止，若没有这样的金字塔，则说明不符合要求。 
			return 0;				
	}	
	
	while(max>=1)			
	{
		flag=funct(pyramids_used-1, num-Aftersort[max].sum, max-1);		//递归 
										  
		if(flag==1)
		{	
			target[pyramids_used-1]=Aftersort[max];
			return 1;
		}
		
		max--;															 
	}
	return 0;
	
} 
