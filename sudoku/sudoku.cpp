
#include<iostream>
#include<algorithm>
#include <time.h>//随机数有关 
#include<fstream> //文件有关 
#include<conio.h>
using namespace std;

int shudu[10][10];//数独矩阵
bool getShuDu(int a,int b)
{
	int num;
	bool jie = true;
	if( a > 9 || b > 9 ){
		return true;
	}
	for(num=1;num<=9;num++)
	{
		jie=true;
		for(int i=1;i<b;i++)
		{
			if(shudu[a][i]!=num)//检查同一行里有没有num这个数，没有则 进入下一个检查 
			  {
			  	jie=true;
			  }
			else
			{
				jie=false;
				break;
			}
		}
		if(jie)//检查同一列中有没有num这个数，没有则进入下一个检查 
		{
			for(int j=1;j<a;j++)
			{
				if(shudu[j][b]==num)
				{
					jie=false;
				}
			}
		}
		if(jie)//检测小方格中有没有数字num 
		{
			int fangge1,fangge2;
			
			fangge1=a-a%3+1;
			fangge2=b-b%3+1;
			
			if(a%3==0)
				fangge1=a-2;
			if(b%3==0)
				fangge2=b-2;
			
			for( int t = 0 ; t < 3 ; t++  )
			{
				if( jie == false )
					break;
				for( int r = fangge2 ; r < fangge2+3 ; r++  )
				{
					if( shudu[fangge1][r] == num )
					{
						jie = false;
						break;
					}
				}
				fangge1++;	
			}
		
		}	
		if(jie)//利用递归把剩下的填完 
		{
			shudu[a][b]=num;
			if( b < 9)
			{
				if( getShuDu( a , b+1 ) )
				return true;
			}
			else
			{
				if( a < 9 )
				{
					if( getShuDu( a+1 ,1) )
					return true;
				}
				else
					return true;
			}
		shudu[a][b]=0;//如果不符合，则恢复数据 
		}	
	}
	return false;
	
 } 
	
void kaishi()//把第一排设置成随机数 
{
	
	int i,j;
	for( i = 1 ; i <= 9 ; i++ )
	{
		for( j = 1 ; j <= 9 ; j++ )
		{
			
			shudu[i][j]=0;
		}
	}
	for( j = 1 ; j <= 9 ; j++ )
		{
			if(j==1)
			shudu[1][j]=4;
			else
			if(j==4)
			shudu[1][4]=1;
			else
			shudu[1][j]=j;
		}
	random_shuffle( & (shudu[1][2]) , & (shudu[1][10]));
	getShuDu(2,1);//开始向下一行生成数据 
}

int main()
{
	ofstream outfile("sudoku.txt");
	srand( (unsigned)time(NULL) );//生成随机数种子，要放在主函数中，如果放在函数中则会导致时间相差太短生成的种子都一样 
	int n;
	int i,j,t;
	cin>>n;
	for(i=0;i<n;i++)
	{
		kaishi();
		for( int j = 1 ; j <= 9 ; ++ j ) 
    	{
        	for( int t = 1 ; t <= 9 ; ++t ) 
            	outfile<< shudu [j][t] <<" " ;
        	outfile<<endl; 
   		 }
	outfile<<endl;
	}
	outfile.close();//文件覆盖上一次就要写close 
	return 0;
	
}
