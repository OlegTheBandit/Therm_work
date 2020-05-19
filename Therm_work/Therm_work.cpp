

#include <memory.h>
#include <stdio.h>
#include <iostream>
#include "List.h"
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;



void city_list_build(List<string>& list, ifstream& file)
{
	char c;
	string city;
	int i = 0;
	while (!file.eof())
	{
		c = file.get();
		if (c == ' ')
		{
			i++;
			if (i > 0)
			{
				bool flag = 1;
				for (int i = 0; i < (int)list.get_size(); i++)
				{
					if (list.get_pointer(i)->data == city)
					{
						flag = 0;
						break;
					}
				}
				if (flag == 1)
				{
					list.push_back(city);
				}
				city.clear();
			}
			if (i == 2)
			{
				i = 0;

				c = file.get();

				while (c != '\n')
				{
					if (file.eof())
						return;
					c = file.get();
				}
			}
		}
		else
			city.push_back(c);
	}

}



void matrix_build(List<string>& list, ifstream& file, int**matrix)
{
	
	char c;
	string city_1;
	string city_2;
	string bandwidth;
	int i = 0;
	while (!file.eof())
	{
		c = file.get();
		if (c == ' ')
		{
			i++;
				
			
		}
		else
		{
			if (i == 0)
				city_1.push_back(c);
			if (i == 1)
				city_2.push_back(c);
			if (i == 2)
			{
				i = 0;

				
				while (c != '\n')
				{
					bandwidth.push_back(c);
					if (file.eof())
					{
						for (int i = 0; i < list.get_size(); i++)
						{
							if (list.get_pointer(i)->data == city_1)
							{
								for (int j = 0; j < list.get_size(); j++)
								{
									if (list.get_pointer(j)->data == city_2)
									{
										matrix[i][j] = atoi(bandwidth.c_str());
										
									}
								}
							}
						}
						return;
					}
					c = file.get();
					
				}
				for (int i = 0; i < list.get_size(); i++)
				{
					if (list.get_pointer(i)->data == city_1)
					{
						for (int j = 0; j < list.get_size(); j++)
						{
							if (list.get_pointer(j)->data == city_2)
							{
								matrix[i][j] = atoi(bandwidth.c_str());
								
							}
						}
					}
				}
				city_1.clear();
				city_2.clear();
				bandwidth.clear();
			}
		}


		
	}

}

void recurFind(int top, int end, int** color_matrix, bool& temp, List<string>& list)
{
	int match = 0;
	for (int i = 0; i < list.get_size(); i++)
	{
		if (color_matrix[top][i] != 0)
		{

			switch (color_matrix[top][i])
			{
			case 1:
				for (int j = 0; j < list.get_size(); j++)
					if (color_matrix[j][i] != 0)
						color_matrix[j][i] = 2;
				break;
			case 2:
				temp = false;
				return;
				break;
			default:
				break;
			}
			match++;
			recurFind(i, end, color_matrix, temp, list);
		}
	}
	if (match == 0 && top == end) {
		temp * true;
		for (int j = 0; j < list.get_size(); j++)
			if (color_matrix[j][top] != 0)
				color_matrix[j][top] = 3;
		return;
	}
	else if (match == 0 && top != end) {
		temp = false;
		for (int j = 0; j < list.get_size(); j++)
			if (color_matrix[j][top] != 0)
				color_matrix[j][top] = 3;
		return;
	}
	else {
		for (int j = 0; j < list.get_size(); j++)
			if (color_matrix[j][top] != 0)
				color_matrix[j][top] = 3;
		return;
	}
}

bool TrueTransport_network(int** matrix, List<string>& list)
{
	int top = -1;
	int stock = -1;
	for (int i = 0; i < list.get_size(); i++) {
		if (list.get_pointer(i)->data == "S")
			top = i;
		if (list.get_pointer(i)->data == "T")
			stock = i;
	}
	if (stock == -1 || top == -1)
		throw std::out_of_range("wrong graph");
	int** temp_matrix = new int* [list.get_size()];

	for (int i = 0; i < list.get_size(); i++)
	{
		temp_matrix[i] = new int[list.get_size()];
	}

	for (int i = 0; i < list.get_size(); i++)
	{
		for (int j = 0; j < list.get_size(); j++)
		{
			if (matrix[i][j] > 0)
				temp_matrix[i][j] = 1; // 1 it is white color, 2 it is gray, 3 it is black
			else
				temp_matrix[i][j] = 0;
		}
	}
	bool this_matrix = true;
	int double_match = -1;
	for (int j = 0; j < list.get_size(); j++)
		if (temp_matrix[j][top] != 0)
			temp_matrix[j][top] = 2;
	recurFind(top, stock, temp_matrix, this_matrix, list);
	return this_matrix;
}

void fild(List<bool>& marks)
{
	for (int i = 0; i < marks.get_size(); i++)
		marks.get_pointer(i)->data = 0;
}

int dfs(int** matrix, int v, int delta, List<bool>& marks, List<string>& list, int& flow)
{
	if (marks.get_pointer(v)->data == 1)
		return 0;
	marks.get_pointer(v)->data = 1;
	if (list.get_pointer(v)->data == "T")
	{
		
		return delta;
	}
	for (int i = 0; i < list.get_size(); i++)
	{
		if (matrix[v][i] > 0 && marks.get_pointer(i)->data ==0)
		{
			
				int mindelta = dfs(matrix, i, min(delta, matrix[v][i]), marks, list, flow);
				
				if (mindelta > 0)
				{
					matrix[v][i] -= mindelta;
					
					matrix[i][v] += mindelta;
					return mindelta;
				}
			
		}
	}
	return 0;
}

void print_matrix(int** matrix, int matrix_size)
{
	for (int i = 0; i < matrix_size; i++)
	{
		for (int j = 0; j < matrix_size; j++)
		{
			
			if (matrix[i][j] != -842150451)
				cout << matrix[i][j] << " ";
			else
				cout << "- ";
		}
		cout << endl;
	}
}

int main()
{
	
	ifstream input("input.txt");
	List<string> verties;
	city_list_build(verties, input);
	input.close();
	int flag = 0;
	for (int i = 0; i < verties.get_size(); i++)
	{
		if (verties.get_pointer(i)->data == "S" || verties.get_pointer(i)->data == "T")
		{
			flag++;
		}
	}
	if (flag != 2)
	{
		cout << "Haent got any verties";
		return 0;
	}
	int** matrix;
	matrix = new int* [verties.get_size()];
	for (int i = 0; i < verties.get_size(); i++)
	{
		matrix[i] = new int[verties.get_size()];
	}
	input.open("input.txt");
	matrix_build(verties, input, matrix);
	for (int i = 0; i < verties.get_size(); i++)
	{
		cout << verties.get_pointer(i)->data<<" ";
	}
	cout << endl;
	for (int i = 0; i < verties.get_size(); i++)
	{
		for (int j = 0; j < verties.get_size(); j++)
		{
			if(matrix[i][j] < 0)
				cout << "- ";
			else
			cout << matrix[i][j]<<" ";
		}
		cout << endl;
	}
	if (!TrueTransport_network(matrix, verties))
	{
		cout << "Bad graph error";
		return 0;
	}



	int source, target;
	for (int i = 0; i < verties.get_size(); i++)
	{
		if (verties.get_pointer(i)->data == "S")
			source = i;
		if (verties.get_pointer(i)->data == "T")
			target = i;
	}

	
	List<bool> marks;
	for (int i = 0; i < verties.get_size(); i++)
	{
		marks.push_back(0);
	}
	int delta;
	int flow = 0;
	for (int i = 0; i < verties.get_size(); i++)
	{
		for (int j = 0; j < verties.get_size(); j++)
		{
			
			if (matrix[i][j] < 0)
			{
				matrix[i][j]= 0;
			}
		}
	}

	while (1)
	{
		fild(marks);		
		delta = dfs(matrix, source, 9999999, marks, verties, flow);
		if (delta > 0)
			flow += delta;

		else
			break;
	}
	cout <<"Max flow in graph = "<<flow;
	return 0;
}
