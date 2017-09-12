#include<iostream>
#include<vector>
#include<utility>
#include<stdio.h>
//#include"text.h"
using namespace std;

int sudu[9][9] = { 7,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0 }; //初始化数独
int N;
vector <int> area[81];//用来记录每个位置的可选数, 序号k= row*9 + col

bool can_update = true;// 记录是否更新,可更新有空位子，不可更新，没有空位子，数独已完成 

bool is_blank = true;// 判断is_blank存在空位置，且有可选数 ，is_blank=false的话，存在空位置没有可选数 

pair < int, int > chosen;  // (chose_area, can_use_number)
								//一对键值，first是位置，second是可选数个数 
int num = 0;
int is_over = false;

//找出area[x][y]的可选数 
vector <int> find(int x, int y) 
{
	int a[10] = { 0 };
	vector <int> ret;//声明一个int型向量ret 
	for (int i = 0; i < 9; i++)
	 {
		if (sudu[i][y] > 0) 
		a[sudu[i][y]] = 1;//所在行若有其他数，标记已使用 
		if (sudu[x][i] > 0)
	    a[sudu[x][i]] = 1; //所在列若有其他数，标记已使用 
		
	}
	int row = x / 3, col = y / 3;//所在宫若有其他数，标记已使用 
	for (int i = row * 3; i < row * 3 + 3; i++)
	{ 
		for (int j = col * 3; j < col * 3 + 3; j++)
		 {
			if (sudu[i][j] > 0) 
			a[sudu[i][j]] = 1;
		}
	}
	for (int i = 1; i <= 9; i++) 
	{
	if (!a[i]) ret.push_back(i);//逐个填入剩余可选数 
    }
	return ret;
}


void update() {
	for (int i = 0; i < 81; i++) area[i].clear();
	chosen = make_pair(0, 10);
	can_update = false;
	for (int i = 0; i < 9; i++	)
	{
		for (int j = 0; j < 9; j++) if (sudu[i][j]==0) 
		{
			int k = i * 9 + j;//k为该空白格序号 
			area[k] = find(i, j);//填入可选数 
			if (area[k].empty()) is_blank = false;//没有可选数 
			if (area[k].size() < chosen.second) chosen = make_pair(k, area[k].size());//更新 
			can_update = true;
		}
	}
}
void print()
 {
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++) 
		{
			cout << sudu[i][j] << " ";
			if (j == 8) cout << endl;
		}
	cout <<endl;
}

void num_sudu() 
{
	update();
	if (can_update==false)
	 {
		num++;
		if (num >=N) is_over = true;
		print();
	}
	else if (is_blank==false) 
	{
		return;
	}
	else if (is_over==false)
	 {
		int areaition = chosen.first;
		int x = areaition / 9;
		int y = areaition - x * 9;//x,y为该位置坐标 

		int size = chosen.second;//size为选中数个数 
		vector <int> k = area[areaition];
		for (int i = 0; i < size; i++) 
		{
			sudu[x][y] = k[i];
			num_sudu();

			sudu[x][y] = 0;
			is_blank = true;
			// 回溯, 还原数据, 原is_blank, 前面的深搜,都没有正确答案,会导致is_blank=false
		}
	}
}
int main(int argc, char *argv[]) {
	
	//cin >> N;
		if (argc != 3)
	{
		cout << "please input the correct order"<< endl;
		return 0;
	}
	if (argv[1][0] != '-' || argv[1][1] != 'c' || argv[1][2] != '\0')
	{
		cout << "please input -c " << endl;
		return 0;//如果输入第二个参数不是-c 不输出
	}
	for (int i = 0; argv[2][i] != '\0'; i++)
	{
		if (argv[2][i] < 48 || argv[2][i]>57)
		{
			cout << "please input the correct number" << endl;
			return 0;//如果输入第三个参数不是数字 不输出
			break;
		}
		N = argv[2][i] - '0' + N * 10;
	}
	freopen("sudoku.txt", "w" ,stdout);

	num_sudu();
	fclose(stdout);
}





