#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
ofstream output;
ifstream input;
int n;
int result = 0; //�����
int map[9][9];
void creat_shudu() //�����վֲ������sudoku�ļ���
{
	int tmp[9] = { 2,3,4,5,6,7,8,9,1 };//tmp��ʾ��һ������
	int i, j, k, moveright[8] = { 3,6,1,4,7,2,5,8 };    //����λ��
	for (i = 0; i < 40320; i++)    //8!=40320
	{
		memcpy(map[0], tmp, sizeof(tmp));
		for (j = 0; j < 8; j++)
			for (k = 0; k < 9; k++)
				map[j + 1][(k + moveright[j]) % 9] = map[0][k];//��ʼģ��
		int row[9] = { 0,1,2,3,4,5,6,7,8 };//fol�����ǽ����������1-9�ж�Ӧ����ģ���fol��
		for (j = 0; j < 6; j++)
		{
			if (j != 0)
				next_permutation(row + 3, row + 6);//�˺�������4-7�е���һ������
			for (k = 0; k < 6; k++)
			{
				if (k != 0)
					next_permutation(row + 6, row + 9);
				for (int a = 0; a < 9; a++)
				{
					for (int b = 0; b < 9; b++)
					{
						if (b == 0)
							output << map[row[a]][b];
						else
							output << " " << map[row[a]][b];
					}
					output << endl;
				}
				output << endl;
				if (!--n)
					return;
			}//���һ�����������
			row[6] = 7, row[7] = 8, row[8] = 9;
		}//ÿ������ģ����36����ʽ,��������8!*36=1451520��
		next_permutation(tmp + 1, tmp + 9);//��tmp��������һ��ȫ����
	}
	return;
}
int convert(char* str)//�ж�������ַ����Ƿ��Ϊ���֣���n��
{
	int len = strlen(str);
	for (int i = 0;i < len;i++)
		if (str[i]<'0' || str[i]>'9')
			return 0;
	return 1;
}
//������еĽ�
void print(int a[9][9]) {
	result++;
	for (int i = 0; i<9; i++) {
		for (int j = 0; j<9; j++) {
			if (j == 0)
				output << a[i][j];
			else output << " " << a[i][j];
		}
		output << endl;
	}
	output << endl;
}

//�ж��Ƿ���Խ���i�С���j�е�����Ϊk
bool check(int a[9][9], int i, int j, int k) {
	int m, n;
	//�ж���
	for (n = 0; n<9; n++) {
		if (a[i][n] == k)
			return false;
	}
	//�ж���
	for (m = 0; m<9; m++) {
		if (a[m][j] == k)
			return false;
	}
	//�ж�����С�Ź���
	int t1 = (i / 3) * 3, t2 = (j / 3) * 3;
	for (m = t1; m<t1 + 3; m++) {
		for (n = t2; n<t2 + 3; n++) {
			if (a[m][n] == k)
				return false;
		}
	}
	//���У�����true
	return true;
}

//������⺯��
void Sudoku(int a[9][9], int n) {
	int temp[9][9];
	int i, j;
	for (i = 0; i<9; i++) {
		for (j = 0; j<9; j++)
			temp[i][j] = a[i][j];
	}
	i = n / 9;
	j = n % 9; //�����n����������������
	if (a[i][j] != 0) { //�Ѿ���ԭʼ����
		if (n == 80) {  //�����һ�����ӣ�������н�
			print(temp);
		}
		else    //�������һ�����ӣ�����һ������
			Sudoku(temp, n + 1);
	}
	else { //û������
		for (int k = 1; k <= 9; k++) {
			bool flag = check(temp, i, j, k);
			if (flag) { //��i�С���j�п�����k
				temp[i][j] = k; //��Ϊk
				if (n == 80) {
					print(temp);
					break;
				}
				else
					Sudoku(temp, n + 1);
				temp[i][j] = 0; //�ָ�Ϊ0���ж���һ��k
			}
		}
	}
}

int main(int argc, char *argv[])
{
	output.open("../BIN/sudoku.txt", std::ios::out | std::ios::app);//��������ָ���ļ�
	if (argv[1][0] == '-'&&argv[1][1] == 'c')
	{
		if (convert(argv[2]))
			n = atoi(argv[2]);//�����������Ч��,��ת��Ϊ����
		else n = -1;
		if (n <= 0)
			cout << "Wrong Input!" << endl;
		else
			creat_shudu();
	}
	else if (argv[1][0] == '-'&&argv[1][1] == 's')
	{
		input.open(argv[2]);
		int i = 0, j = 0;
		while (!input.eof())//�������ļ���β
		{
			input >> map[i][j];
			j++;
			if (j >= 9) {
				j = 0;i++;
			}
			if (i >= 9) {
				i = 0; j = 0;
				Sudoku(map, 0);
				if (result == 0) {
					output << "No Solution" << endl;
					output << endl;
				}

				memset(map, 0, sizeof map);
			}
		}
	}
	else cout << "Wrong input!" << endl;
	return 0;
}
