#include "List.h"
namespace ListMenu
{
	void Init_List(List& list, NecessaryData& data)
	{
		for (int i = 0; i < 10; i++) {
			list.x[i] = 0; list.y[i] = 0; list.z[i] = 0; list.data[i] = 0; list.data_clone[i] = 0;
			list.x_clone[i] = 0; list.y_clone[i] = 0; list.z_clone[i] = 0;
		}
		data.top = 0;
		data.bottom = 0;
		data.onS = false;
	}

	void Push_Front(List& list, NecessaryData& data)
	{
		int x, y, z;
		cout << "입력할 x, y, z값을 적어주세요: ";
		cin >> x >> y >> z;
		if (data.top >= 10 && data.bottom > 0)
		{
			list.x[data.bottom] = x; list.y[data.bottom] = y; list.z[data.bottom] = z; list.data[data.bottom] = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
			data.bottom--;
			PrintList(list, data);
		}
		else if (data.top >= 10 && data.bottom <= 0)
			cout << "\n데이터가 가득찼습니다.\n";
		else {
			list.x[data.top] = x; list.y[data.top] = y; list.z[data.top] = z; list.data[data.top] = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
			data.top++;
			PrintList(list, data);
		}
	}

	void Pop_Front(List& list, NecessaryData& data)
	{
		if (data.top <= data.bottom)
			cout << "더 이상 지울 데이터가 없습니다.\n";
		else {
			list.x[data.top] = 0; list.y[data.top] = 0; list.z[data.top] = 0; list.data[data.top] = 0;
			data.top--;
			PrintList(list, data);
		}
	}

	void Push_Back(List& list, NecessaryData& data)
	{
		int x, y, z;
		cout << "입력할 x, y, z값을 적어주세요: ";
		cin >> x >> y >> z;
		if (data.bottom == 0) {
			for (int i = data.top; i >= 0; i--) {
				list.x[i + 1] = list.x[i];
				list.y[i + 1] = list.y[i];
				list.z[i + 1] = list.z[i];
			}
			list.x[0] = x; list.y[0] = y; list.z[0] = z;
			data.top++;
			PrintList(list, data);
		}
		else {
			data.bottom--;
			list.x[data.bottom] = x; list.y[data.bottom] = y; list.z[data.bottom] = z; list.data[data.bottom] = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
			PrintList(list, data);
		}
	}

	void Pop_Back(List& list, NecessaryData& data)
	{
		list.x[data.bottom] = 0; list.y[data.bottom] = 0; list.z[data.bottom] = 0; list.data[data.bottom] = 0;
		data.bottom++;
		PrintList(list, data);
	}

	void FindFarDot(List& list, NecessaryData& data)
	{
		int x, y, z;
		int	max = list.data[data.bottom];
		x = list.x[data.bottom]; y = list.y[data.bottom]; z = list.z[data.bottom];
		for (int i = data.bottom; i <= data.top; i++) {
			if (list.data[i] > max) {
				max = list.data[i];
				x = list.x[i]; y = list.y[i]; z = list.z[i];
			}
		}

		cout << "원점에서 가장 먼 거리에 있는 점의 좌표 : ( " << x << " " << y << " " << z << " )" << endl;
	}

	void FindNearDot(List& list, NecessaryData& data)
	{
		int x, y, z;
		int min = list.data[data.bottom];
		x = list.x[data.bottom]; y = list.y[data.bottom]; z = list.z[data.bottom];
		for (int i = data.bottom; i <= data.top; i++)
		{
			if (list.data[i] < min) {
				min = list.data[i];
				x = list.x[i]; y = list.y[i]; z = list.z[i];
			}
		}

		cout << "원점에서 가장 가까운 거리에 있는 점의 좌표 : ( " << x << " " << y << " " << z << " )" << endl;
	}

	void SortList(List& list, NecessaryData& data)
	{
		int temp = 0;
		int c_top = 0;

		if (data.onS)
		{
			PrintList(list, data);
			data.onS = false;
			return;
		}

		data.onS = true;
		for (int i = 0; i < data.top; i++) {
			list.x_clone[i] = list.x[i + data.bottom]; list.y_clone[i] = list.y[i + data.bottom]; list.z_clone[i] = list.z[i + data.bottom];
			list.data_clone[i] = list.data[i + data.bottom];
		}

		for (int i = data.bottom; i < data.top; i++) {
			for (int j = 0; j < data.top - 1; j++) {
				if (list.data_clone[j] > list.data_clone[j + 1]) {
					temp = list.data_clone[j];
					list.data_clone[j] = list.data_clone[j + 1];
					list.data_clone[j + 1] = temp;

					temp = list.x_clone[j];
					list.x_clone[j] = list.x_clone[j + 1];
					list.x_clone[j + 1] = temp;

					temp = list.y_clone[j];
					list.y_clone[j] = list.y_clone[j + 1];
					list.y_clone[j + 1] = temp;

					temp = list.z_clone[j];
					list.z_clone[j] = list.z_clone[j + 1];
					list.z_clone[j + 1] = temp;
				}
			}
		}
		c_top = data.top - data.bottom;
		cout << endl;
		for (int i = data.bottom; i <= c_top; i++)
			cout <<  i - data.bottom << " | " << list.x_clone[i] << " " << list.y_clone[i] << " " << list.z_clone[i] << endl;
	}

	void PrintList(List list, NecessaryData data)
	{
		if (data.top == 0)
		{
			cout << "리스트에 데이터가 없습니다." << endl;
			return;
		}

		cout << endl;
		for (int i = data.bottom; i < data.top; i++)
			cout << i << " | " << list.x[i] << " " << list.y[i] << " " << list.z[i] << endl;
	}

	void PrintMenu()
	{
		cout << "\n메뉴 목록\n";
		cout << "+ : x y z: 리스트의 맨 위에 입력 (x, y, z: 숫자)\n";
		cout << "- : 리스트의 맨 위에서 삭제한다\n";
		cout << "e : x y z: 리스트의 맨 아래에 입력 (명령어 +와 반대의 위치, 리스트에 저장된 데이터값이 위로 올라간다.)\n";
		cout << "d: 리스트의 맨 아래에서 삭제한다. (리스트에서 삭제된 칸이 비어있다.)\n";
		cout << "c: 리스트를 비운다. 리스트를 비운 후 다시 입력하면 0번부터 저장된다.\n";
		cout << "m: 원점에서 가장 먼 거리에 있는 점의 좌표값을 출력한다.\n";
		cout << "n: 원점에서 가장 가까운 거리에 있는 점의 좌표값을 출력한다.\n";
		cout << "s: 원점과의 거리를 정렬하여 오름차순 (또는 내림차순)으로 정렬하여 출력한다. 인덱스 0번부터 빈 칸없이 저장하여 출력한다. 다시 s를 누르면 원래의 인덱스 위치에 출력한다.\n";
		cout << "l: 리스트에 저장된 점의 개수를 출력한다.\n";
		cout << "q: 프로그램을 종료한다.\n";
	}
}
