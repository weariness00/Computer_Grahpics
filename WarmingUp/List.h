#pragma once
#include<iostream>
#include<random>
#include<math.h>
#include<conio.h>

using namespace std;

namespace ListMenu
{
	typedef struct List {
		int x[10], y[10], z[10];
		int x_clone[10], y_clone[10], z_clone[10];
		double data[10], data_clone[10];
	}List;

	typedef struct NecessaryData {
		int top;
		int	bottom;
		bool onS;
	}NecessaryData;

	void Init_List(List& list, NecessaryData& data);
	void Push_Front(List& list, NecessaryData& data);
	void Pop_Front(List& list, NecessaryData& data);
	void Push_Back(List& list, NecessaryData& data);
	void Pop_Back(List& list, NecessaryData& data);
	void FindFarDot(List& list, NecessaryData& data);
	void FindNearDot(List& list, NecessaryData& data);
	void SortList(List& list, NecessaryData& data);

	void PrintList(List list, NecessaryData data);
	void PrintMenu();
}