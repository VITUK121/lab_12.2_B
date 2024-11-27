#include <iostream>
#include <Windows.h>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

enum Majors { KN = 1, IT, ME, PI, TN };

struct Student {
	char prizv[100];
	int course;
	Majors major;
	int physics;
	int math;
	union {
		int prog;
		int num_meth;
		int pedagogika;
	};
};

void writeFile(string filename) {
	ofstream file(filename, ios::binary | ios::app);

	if (!file) {
		cout << "�� ������� ������� ����!" << endl;
		return;
	}

	Student student;
	string continueInput;

	do {
		cout << "������ ������� ��������: ";
		cin >> student.prizv;

		cout << "������ ����: ";
		cin >> student.course;

		while (student.course < 1 || student.course > 6) {
			cout << "����������� ����. ������ ���� �� 1 �� 6: ";
			cin >> student.course;
		}

		cout << "������� ������������ (1 = KN, 2 = IT, 3 = ME, 4 = PI, 5 = TN): ";
		int majorInput;
		cin >> majorInput;

		while (majorInput < 1 || majorInput > 3) {
			cout << "����������� ����. ������� 1, 2 ��� 3: ";
			cin >> majorInput;
		}
		student.major = static_cast<Majors>(majorInput);

		cout << "������ ������ � ������: ";
		cin >> student.physics;

		cout << "������ ������ � ����������: ";
		cin >> student.math;

		string message;

		switch (student.major)
		{
		case KN:
			message = "�������������";
			break;
		case IT:
			message = "��������� ������";
			break;
		case ME:
			message = "���������";
			break;
		case PI:
			message = "���������";
			break;
		case TN:
			message = "���������";
			break;
		}

		cout << "������ ������ � " << message << ": ";
		cin >> student.prog;

		file.write((char*)&student, sizeof(Student));

		cout << "������ ������ �� ������ ��������? (���/�): ";
		cin >> continueInput;

	} while (continueInput == "���" || continueInput == "���");

	file.close();
	cout << "��� ������ ������� � ����." << endl;
}

int lenOfLongestPrizv(string filename, int n) {
	int res = 0;

	ifstream file(filename, ios::binary);
	Student student;

	for (int i = 0; i < n; i++) {
		file.read((char*)(&student), sizeof(Student));
		if (strlen(student.prizv) > res) {
			res = strlen(student.prizv);
		}
	}

	file.close();
	return res;
}


int calc_n(int n) {
	int res = 0;
	while (n != 0) {
		n /= 10;
		res++;
	}
	return res;
}

int counter(string filename) {
	ifstream file(filename, ios::binary);
	if (!file) {
		cout << "�� ������� ������� ����!" << endl;
		return 0;
	}

	Student student;
	int count = 0;

	while (file.read((char*)(&student), sizeof(Student))) {
		count++;
	}

	file.close();
	return count;
}


void printStudents(string filename, int n) {
	int width = lenOfLongestPrizv(filename, n);
	(width <= 8) ? (width = 8) : (NULL);
	int maxDigits = calc_n(n);

	for (int i = 0; i < (maxDigits - 1) + (width - 8) + 104; i++) {
		cout << "=";
	}
	cout << endl;

	cout << "|" << setw(maxDigits) << right << "�";
	cout << "|" << setw(width) << left << "�������" << "| ���� | ������������ | Գ���� | ���������� | ������������� | ������� ������ | ��������� |" << endl;

	for (int i = 0; i < (maxDigits - 1) + (width - 8) + 104; i++) {
		cout << "-";
	}
	cout << endl;

	ifstream file(filename, ios::binary);
	
	Student student;

	for (int i = 0; i < n; i++){
		file.read((char*)&student, sizeof(Student));

		cout << "|" << setw(maxDigits) << right << i + 1;
		cout << "|" << setw(width) << left << student.prizv;
		cout << "|" << setw(6) << left << student.course;
		cout << "|" << setw(15) << left;

		switch (student.major) {
			case KN: cout << "KN"; break;
			case IT: cout << "IT"; break;
			case ME: cout << "ME"; break;
			case PI: cout << "PI"; break;
			case TN: cout << "TN"; break;
		}

		cout << "|" << setw(8) << left << student.physics;
		cout << "|" << setw(12) << left << student.math;
		cout << "|" << setw(15) << left;
		(student.major == KN ? cout << student.prog : cout << "-");
		cout << "|" << setw(17) << left;
		(student.major == IT ? cout << student.prog : cout << "-");
		cout << "|" << setw(12) << left;
		(student.major != KN && student.major != IT ? cout << student.prog : cout << "-");
		cout << setw(13) << "|" << endl;
	}
	for (int i = 0; i < (maxDigits - 1) + (width - 8) + 104; i++) {
		cout << "-";
	}
	cout << endl;

}

double average(string filename, int n, int subject) {
	ifstream file(filename, ios::binary);

	Student student;
	double res = 0;

	for (int i = 0; i < n; i++) {
		file.read((char*)&student, sizeof(Student));

		switch (subject) {
		case 1:
			res += student.physics;
			break;
		case 2:
			res += student.math;
			break;
		case 3:
			res += student.prog;
			break;
		}
	}
	file.close();
	return res / n;
}

int mark_counter(string filename, int n) {
	int res = 0;

	ifstream file(filename, ios::binary);

	Student student;

	for (int i = 0; i < n; i++) {
		file.read((char*)&student, sizeof(Student));

		if (student.physics == 4 || student.physics == 5) {
			res++;
		}
	}
	file.close();
	return res;
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	string filename;

	cout << "��'� �����: "; cin >> filename;

	writeFile(filename);

	int n = counter(filename);

	printStudents(filename, n);

	cout << "������� ��� � ������: " << average(filename, n, 1) << endl;
	cout << "������� ��� � ����������: " << average(filename, n, 2) << endl;
	cout << "������� ��� � �������� ��������: " << average(filename, n, 3) << endl;

	cout << "ʳ������ ���� � ������� 4 ��� 5 � ������: " << mark_counter(filename, n);
}
