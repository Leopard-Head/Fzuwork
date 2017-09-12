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
0,0,0,0,0,0,0,0,0 }; //��ʼ������
int N;
vector <int> area[81];//������¼ÿ��λ�õĿ�ѡ��, ���k= row*9 + col

bool can_update = true;// ��¼�Ƿ����,�ɸ����п�λ�ӣ����ɸ��£�û�п�λ�ӣ���������� 

bool is_blank = true;// �ж�is_blank���ڿ�λ�ã����п�ѡ�� ��is_blank=false�Ļ������ڿ�λ��û�п�ѡ�� 

pair < int, int > chosen;  // (chose_area, can_use_number)
								//һ�Լ�ֵ��first��λ�ã�second�ǿ�ѡ������ 
int num = 0;
int is_over = false;

//�ҳ�area[x][y]�Ŀ�ѡ�� 
vector <int> find(int x, int y) 
{
	int a[10] = { 0 };
	vector <int> ret;//����һ��int������ret 
	for (int i = 0; i < 9; i++)
	 {
		if (sudu[i][y] > 0) 
		a[sudu[i][y]] = 1;//�����������������������ʹ�� 
		if (sudu[x][i] > 0)
	    a[sudu[x][i]] = 1; //�����������������������ʹ�� 
		
	}
	int row = x / 3, col = y / 3;//���ڹ������������������ʹ�� 
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
	if (!a[i]) ret.push_back(i);//�������ʣ���ѡ�� 
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
			int k = i * 9 + j;//kΪ�ÿհ׸���� 
			area[k] = find(i, j);//�����ѡ�� 
			if (area[k].empty()) is_blank = false;//û�п�ѡ�� 
			if (area[k].size() < chosen.second) chosen = make_pair(k, area[k].size());//���� 
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
		int y = areaition - x * 9;//x,yΪ��λ������ 

		int size = chosen.second;//sizeΪѡ�������� 
		vector <int> k = area[areaition];
		for (int i = 0; i < size; i++) 
		{
			sudu[x][y] = k[i];
			num_sudu();

			sudu[x][y] = 0;
			is_blank = true;
			// ����, ��ԭ����, ԭis_blank, ǰ�������,��û����ȷ��,�ᵼ��is_blank=false
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
		return 0;//�������ڶ�����������-c �����
	}
	for (int i = 0; argv[2][i] != '\0'; i++)
	{
		if (argv[2][i] < 48 || argv[2][i]>57)
		{
			cout << "please input the correct number" << endl;
			return 0;//������������������������ �����
			break;
		}
		N = argv[2][i] - '0' + N * 10;
	}
	freopen("sudoku.txt", "w" ,stdout);

	num_sudu();
	fclose(stdout);
}





