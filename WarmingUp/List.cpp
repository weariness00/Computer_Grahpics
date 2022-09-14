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
		cout << "�Է��� x, y, z���� �����ּ���: ";
		cin >> x >> y >> z;
		if (data.top >= 10 && data.bottom > 0)
		{
			list.x[data.bottom] = x; list.y[data.bottom] = y; list.z[data.bottom] = z; list.data[data.bottom] = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
			data.bottom--;
			PrintList(list, data);
		}
		else if (data.top >= 10 && data.bottom <= 0)
			cout << "\n�����Ͱ� ����á���ϴ�.\n";
		else {
			list.x[data.top] = x; list.y[data.top] = y; list.z[data.top] = z; list.data[data.top] = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
			data.top++;
			PrintList(list, data);
		}
	}

	void Pop_Front(List& list, NecessaryData& data)
	{
		if (data.top <= data.bottom)
			cout << "�� �̻� ���� �����Ͱ� �����ϴ�.\n";
		else {
			list.x[data.top] = 0; list.y[data.top] = 0; list.z[data.top] = 0; list.data[data.top] = 0;
			data.top--;
			PrintList(list, data);
		}
	}

	void Push_Back(List& list, NecessaryData& data)
	{
		int x, y, z;
		cout << "�Է��� x, y, z���� �����ּ���: ";
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

		cout << "�������� ���� �� �Ÿ��� �ִ� ���� ��ǥ : ( " << x << " " << y << " " << z << " )" << endl;
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

		cout << "�������� ���� ����� �Ÿ��� �ִ� ���� ��ǥ : ( " << x << " " << y << " " << z << " )" << endl;
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
			cout << "����Ʈ�� �����Ͱ� �����ϴ�." << endl;
			return;
		}

		cout << endl;
		for (int i = data.bottom; i < data.top; i++)
			cout << i << " | " << list.x[i] << " " << list.y[i] << " " << list.z[i] << endl;
	}

	void PrintMenu()
	{
		cout << "\n�޴� ���\n";
		cout << "+ : x y z: ����Ʈ�� �� ���� �Է� (x, y, z: ����)\n";
		cout << "- : ����Ʈ�� �� ������ �����Ѵ�\n";
		cout << "e : x y z: ����Ʈ�� �� �Ʒ��� �Է� (��ɾ� +�� �ݴ��� ��ġ, ����Ʈ�� ����� �����Ͱ��� ���� �ö󰣴�.)\n";
		cout << "d: ����Ʈ�� �� �Ʒ����� �����Ѵ�. (����Ʈ���� ������ ĭ�� ����ִ�.)\n";
		cout << "c: ����Ʈ�� ����. ����Ʈ�� ��� �� �ٽ� �Է��ϸ� 0������ ����ȴ�.\n";
		cout << "m: �������� ���� �� �Ÿ��� �ִ� ���� ��ǥ���� ����Ѵ�.\n";
		cout << "n: �������� ���� ����� �Ÿ��� �ִ� ���� ��ǥ���� ����Ѵ�.\n";
		cout << "s: �������� �Ÿ��� �����Ͽ� �������� (�Ǵ� ��������)���� �����Ͽ� ����Ѵ�. �ε��� 0������ �� ĭ���� �����Ͽ� ����Ѵ�. �ٽ� s�� ������ ������ �ε��� ��ġ�� ����Ѵ�.\n";
		cout << "l: ����Ʈ�� ����� ���� ������ ����Ѵ�.\n";
		cout << "q: ���α׷��� �����Ѵ�.\n";
	}
}
