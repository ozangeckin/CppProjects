#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;


void display(int **puzzle,int row)//puzzle'�n anl�k halini g�stermek i�in..
{
	for(int i=0 ; i<row ; i++)
	{
		for(int j=0 ; j<row ; j++)
		{
			if(puzzle[i][j] == row*row)
			{
				cout<<"  ";
				continue;
			}
			cout<<puzzle[i][j]<<" ";
			
		}
		cout<<endl;
	}
}
int control(int **puzzle , int row)//puzzle ��z�ld� m� onun kontrol�..
{
	for(int i = 0 ; i < row ; i++)
	{
		for(int j = 0 ; j < row ; j++)
		{
			if(puzzle[i][j]!=(i*row)+j+1)
				return 0;
		}
	}
	return 1;
}
int return_inversion_number(int **puzzle, int row)//solvable test i�in inversion say�s�n� kulland�m.. 
{
	int inversion=0;
	int *array = new int[row*row-1];
	int n = 0;
	for(int i = 0 ; i < row ; i++)
	{
		for(int j = 0 ; j < row ; j++)
		{
			if(puzzle[i][j]!=row*row)
			{
				array[n] = puzzle[i][j];
				n++;
			}
		}
	}
	
	for(int i = 0 ; i < n ; i++)
	{
		for (int j=i+1 ; j < n ; j++)
		{
			
			if(array[i]>array[j])
				inversion++;
		}
	}

	return inversion;
}

int main()
{
	int row,i,size;
	cout<<"Welcome This Puzzle Game"<<endl;
	cout<<"Move Down to D"<<endl;
	cout<<"Move Up to U"<<endl;
	cout<<"Move Left to L"<<endl;
	cout<<"Move Right to R"<<endl;
	cout<<"Move Intelligent to I"<<endl;
	cout<<"Move Shuffle to S"<<endl;
	cout<<"Please enter row number"<<endl;
	cin >> row;
	size = row*row;
	
	int x,y;
	
	srand( time(0) );
	
	int random;
	
	int *array = new int[size];//size a g�re dynamic memory allocation..
	
	
	
	int **puzzle = new int*[row];//size a g�re dynamic memory allocation..(double pointer)
	
	for(i=0 ; i<size ; ++i)
	{
		puzzle[i] = new int[row];
	}
	while(1)
	{
		for(i =1 ; i <= size ; i++ )
		{
			array[i-1]=i;
		}
		for(i=0 ; i<row ; i++)
		{
			for(int j=0 ; j<row ; j++)
			{
				while(1)
				{
					random = rand() % (size-1-0+1);
					if(array[random] != -1)//ayn� say� gelmesin diye..
						break;
				}
				if(array[random] == size)
				{
				 	x=i;//position of x from bottom de�eri i�in laz�m olacak
					y=j;
				}
				puzzle[i][j] = array[random];//random bir �ekilde puzzle doldurulur..
				array[random] = -1;
			
			}
		}
		if(row%2 != 0) //sat�r ve s�tun say�s�n�n �ift mi tek mi anlamak i�in..
		{
			if(return_inversion_number(puzzle,row)%2 == 0)//e�er inversion say�s� �ift ise ��z�lebilir..
				break;
			else //e�er tekse tekrar doldurulmas� gerekir ��nk� ��z�lemez..
				continue;
		}
		else //e�er �ift ise farkl� kurallar gerekli .. position of x from bottom say�s� �nemli..
		{
			if(return_inversion_number(puzzle,row)%2 == 0)//e�er inversion say�s� �ift ise position of x from bottom say�s� tek olmal�
			{
				if(row-x%2 != 0)//x bulundu�u i de�eri..(i,j) .. B�yle olursa ��z�lebilir
				{
					break;
				}
				else//��z�lemez..
				{
					continue;
				}
			}
			if(return_inversion_number(puzzle,row)%2 != 0)//e�er inversion say�s� tek ise position of x from bottom say�s� �ift olmal�
			{
				if(row-x%2 == 0)//x bulundu�u i de�eri..(i,j) .. B�yle olursa ��z�lebilir
				{
					break;
				}
				else//��z�lemez..
				{
					continue;
				}
			}
			
		}
	
		
	}
	
	cout<<"Your initial random board is"<<endl;
	display(puzzle,row);//ilk hali g�sterilir..
	
	char move;
	int count=0,select;
	
	cout<<"Your move: ";
	cin>>move;
	count++;
	while(move != 'Q')//Q komutunu alana kadar devam et..
	{
		
		switch(move)//verilen komuta g�re switch yap�s �al���r..
		{
			case 'D':
				if(x==row-1)//s�n�r kontrolleri..
					break;
				puzzle[x][y]=puzzle[x+1][y];
				puzzle[x+1][y]=size;
				x=x+1;
				break;
			case 'U':
				if(x==0)
					break;
				puzzle[x][y]=puzzle[x-1][y];
				puzzle[x-1][y]=size;
				x=x-1;
				break;
			case 'L':
				if(y==0)
					break;
				puzzle[x][y]=puzzle[x][y-1];
				puzzle[x][y-1]=size;
				y=y-1;
				break;
			case 'R':
				if(y==row-1)
					break;
				puzzle[x][y]=puzzle[x][y+1];
				puzzle[x][y+1]=size;
				y=y+1;
				break;
			case 'S':
				for(int i = 0 ; i < size ; i++)//size kadar devam eder ��nk� size kadar ad�m istiyor..
				{
					random = rand() % (3-0+1);//rastgele kar��mas� i�in..
					switch(random)
					{
						case 0:
							if(y==row-1)
								break;
							puzzle[x][y]=puzzle[x][y+1];
							puzzle[x][y+1]=size;
							y=y+1;
							break;
						case 1:
							if(y==0)
								break;
							puzzle[x][y]=puzzle[x][y-1];
							puzzle[x][y-1]=size;
							y=y-1;
							break;
						case 2:
							if(x==0)
								break;
							puzzle[x][y]=puzzle[x-1][y];
							puzzle[x-1][y]=size;
							x=x-1;
							break;
						case 3:
							if(x==row-1)
								break;
							puzzle[x][y]=puzzle[x+1][y];
							puzzle[x+1][y]=size;
							x=x+1;
							break;
					}		
				}
				break;
				
			case 'I'://if else yap�lar� ile en mant�kl� y�n se�ilir..
				if (x == row-2 && y == row-1)
				{
					select = 3;
					cout<<"Intelligent move chooses D"<<endl;
				}
				else if (x == row-1 && y == row-2)
				{
					select = 0;
					cout<<"Intelligent move chooses R"<<endl;
				}
				else if (y == row-1 )
				{
					select = 3;
					cout<<"Intelligent move chooses D"<<endl;
				}
				else if (x == row-1)
				{
					select =0;
					cout<<"Intelligent move chooses R"<<endl;
				}
				else if (x == row-2 && y ==row-2)
				{
					if(puzzle[row-1][row-3]+1 == puzzle[row-2][row-1] )
					{
						select = 0;
						cout<<"Intelligent move chooses R"<<endl;
					}
						
					else if(puzzle[row-2][row-3]+1 == puzzle[row-1][row-2] )
					{
						select = 3;
						cout<<"Intelligent move chooses D"<<endl;
					}
				}
				else if(x == row-3 && y == row-2)
				{
					if(puzzle[row-3][row-3]+1 == puzzle[row-3][row-1] )
					{
						select = 0;
						cout<<"Intelligent move chooses R"<<endl;
					}
						
					else if(puzzle[row-3][row-3]+1 == puzzle[row-2][row-2] )
					{
						select = 3;
						cout<<"Intelligent move chooses D"<<endl;
					}
				}
				switch(select)
				{
					case 0:
						if(y==row-1)
							break;
						puzzle[x][y]=puzzle[x][y+1];
						puzzle[x][y+1]=size;
						y=y+1;
						break;
					case 1:
						if(y==0)
							break;
						puzzle[x][y]=puzzle[x][y-1];
						puzzle[x][y-1]=size;
						y=y-1;
						break;
					case 2:
						if(x==0)
							break;
						puzzle[x][y]=puzzle[x-1][y];
						puzzle[x-1][y]=size;
						x=x-1;
						break;
					case 3:
						if(x==row-1)
							break;
						puzzle[x][y]=puzzle[x+1][y];
						puzzle[x+1][y]=size;
						x=x+1;
						break;
					}	
					
		}
		display(puzzle,row);//son halini g�stermek i�in..
		
		if(control(puzzle,row)==1)//��z�ld� m� kontrol�..
		{
			cout<<"Problem Solved!"<<endl;
			cout<<"Total number of moves "<<count<<endl;
			break;
		}
		cout<<"Your move: ";
		cin>>move;
		count++;//ka� hamle yapt���n� ��renmek i�in..
	}
	
	
	
	
	
	
	
	
}
