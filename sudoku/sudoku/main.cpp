#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
ofstream output;
ifstream input;
int n;
int result = 0; //结果数
int map[9][9];
void creat_shudu() //生成终局并输出到sudoku文件中
{
	int tmp[9] = { 2,3,4,5,6,7,8,9,1 };//tmp表示第一行数字
	int i, j, k, moveright[8] = { 3,6,1,4,7,2,5,8 };    //右移位数
	for (i = 0; i < 40320; i++)    //8!=40320
	{
		memcpy(map[0], tmp, sizeof(tmp));
		for (j = 0; j < 8; j++)
			for (k = 0; k < 9; k++)
				map[j + 1][(k + moveright[j]) % 9] = map[0][k];//初始模板
		int row[9] = { 0,1,2,3,4,5,6,7,8 };//fol函数是接下来输出的1-9行对应数独模板的fol行
		for (j = 0; j < 6; j++)
		{
			if (j != 0)
				next_permutation(row + 3, row + 6);//此函数是求4-7行的下一个排列
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
			}//完成一次数独的输出
			row[6] = 7, row[7] = 8, row[8] = 9;
		}//每种数独模板有36种形式,最多能输出8!*36=1451520种
		next_permutation(tmp + 1, tmp + 9);//对tmp函数进行一次全排列
	}
	return;
}
int convert(char* str)//判断输入的字符串是否均为数字（即n）
{
	int len = strlen(str);
	for (int i = 0;i < len;i++)
		if (str[i]<'0' || str[i]>'9')
			return 0;
	return 1;
}
//输出可行的解
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

//判断是否可以将第i行、第j列的数设为k
bool check(int a[9][9], int i, int j, int k) {
	int m, n;
	//判断行
	for (n = 0; n<9; n++) {
		if (a[i][n] == k)
			return false;
	}
	//判断列
	for (m = 0; m<9; m++) {
		if (a[m][j] == k)
			return false;
	}
	//判断所在小九宫格
	int t1 = (i / 3) * 3, t2 = (j / 3) * 3;
	for (m = t1; m<t1 + 3; m++) {
		for (n = t2; n<t2 + 3; n++) {
			if (a[m][n] == k)
				return false;
		}
	}
	//可行，返回true
	return true;
}

//数独求解函数
void Sudoku(int a[9][9], int n) {
	int temp[9][9];
	int i, j;
	for (i = 0; i<9; i++) {
		for (j = 0; j<9; j++)
			temp[i][j] = a[i][j];
	}
	i = n / 9;
	j = n % 9; //求出第n个数的行数和列数
	if (a[i][j] != 0) { //已经有原始数据
		if (n == 80) {  //是最后一个格子，输出可行解
			print(temp);
		}
		else    //不是最后一个格子，求下一个格子
			Sudoku(temp, n + 1);
	}
	else { //没有数据
		for (int k = 1; k <= 9; k++) {
			bool flag = check(temp, i, j, k);
			if (flag) { //第i行、第j列可以是k
				temp[i][j] = k; //设为k
				if (n == 80) {
					print(temp);
					break;
				}
				else
					Sudoku(temp, n + 1);
				temp[i][j] = 0; //恢复为0，判断下一个k
			}
		}
	}
}

int main(int argc, char *argv[])
{
	output.open("../BIN/sudoku.txt", std::ios::out | std::ios::app);//结果输出到指定文件
	if (argv[1][0] == '-'&&argv[1][1] == 'c')
	{
		if (convert(argv[2]))
			n = atoi(argv[2]);//如果输入是有效的,则转化为整数
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
		while (!input.eof())//输入至文件结尾
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
