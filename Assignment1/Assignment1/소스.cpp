/*
		201412700 ������ ������Ű��а�
		���� ���α׷� - ���ϴ� �ܾ� �������, �ܾ ������ �� �� �ܾ� ���
		���� �ӵ�: 5.379 sec
*/
#pragma warning(disable:4996)
#include <iostream>
#include <sstream>
#include <string>
#include <string.h>
//#include <time.h>
#define BUFFER 4096	 // ���� �� ���� ���۰� �� ũ��

using namespace std;

string dict[200000];			// ù��° �ܾ�
string wordclass[200000];		// ǰ��
string explain[200000];			// ����

int counts;	// �ܾ���� ��

void init();			// ���۽� ���� �ʱ�ȭ
void print(int n);		// �ܾ� ���� ���
void movement();		// ���� ����
void read(string name);	// ���� �о dict�� ����
void search(string target); // dict���� target ã��
int find(string *words, char* target, int begin, int end); // target�� ã�� ����


int main() {
	init();				// ���� ������ ���� ������ �ʱ�ȭ
	movement();			// ���� ���α׷� ����
}

void init() {	counts = 0;	}	// �ܾ���� �� �ʱ�ȭ

void print(int n) {		// n ��° �ܾ��� ���� ���
	cout << dict[n] << " " << wordclass[n] << explain[n];
}

void movement() {	// ����
	string line, cmd;	// �Է�, ��ɾ�
	while (1) {
		cout << "$ ";
		getline(cin, line);	// ���� �Էµ� ó���ϱ�����
		istringstream iss(line);
		iss >> cmd;	// �ܾ� ������ ���� �����ϰ� �Է¹���

		if (cmd == "read") {		if (iss >> cmd) read(cmd);		}	// �б� ����
		else if (cmd == "size") {	cout << counts << endl;			}	// ���� ������ ���
		else if (cmd == "find") {	if (iss >> cmd) search(cmd);	}	// �ܾ� ã��
		else if (cmd == "exit") break;
	}
}

void read(string name) {	// �ܾ��� �д� ���� - ���� ����
	//clock_t begin, end;
	//begin = clock();
	FILE *fin = fopen((char*)name.c_str(), "r");
	if(NULL== fin) cout << "File Open Fail\n";

	char line[BUFFER];

	while (NULL != fgets(line, sizeof(line), fin)) {
		if (strcmp("\n", line) == 0) continue;
		string str(line);	// char �迭 line�� string �� str�� ����
		int pos1, pos2;
		pos1 = str.find("(");
		pos2 = str.find(")");

		dict[counts] = str.substr(0, pos1 - 1);							// ( �ձ����� �ܾ�
		wordclass[counts] = str.substr(pos1, pos2 - pos1 + 1);			// () ���̴� ǰ��
		explain[counts] = str.substr(pos2 + 1, str.size() - pos2-1);	// ) �ڴ� ����

		counts++;														// �ܾ� �� ����
	}
	fclose(fin);
	//end = clock();
	//cout << "����ð� : " << (double)(end - begin) << "\n";
	
}// ���� ����

void search(string target) {					// ���ϴ� �ܾ ã�� ����

	char* temp = (char*)target.c_str();	// ã�� ���� �ܾ� temp
	int index = find(dict, temp, 0, counts - 1);	// ������ ���ϴ� �ܾ �ִ��� �������� ã�� ����. �ܾ��� �ε��� ��ȯ
	char* comp = (char*)dict[index].c_str();	// ��ȯ���� ��ġ �ܾ�
	int check = _strcmpi(temp, comp);				// ��ȯ���� �ε����� ã�� �������� ��ġ����, �����Ͱ� �������� ��ġ���� Ȯ��

	if (check == 0) {								// ã�� �ܾ ������
		int start = index, end = index;

		// ���� �ܾ� ���� ���� index �� start�� ����
		for (int i = index; i >= 0; i--) {
			char* s = (char*)dict[i].c_str();
			int c = _strcmpi(temp, s);
			if (c != 0) { start = i + 1; break; }
		}// ���� �ܾ� �� ���� ���� index�� end�� ����
		for (int i = index; i < counts; i++) {
			char* s = (char*)dict[i].c_str();
			int c = _strcmpi(temp, s);
			if (c != 0) { end = i - 1; break; }
		}

		// ã���� �� ���
		cout << "Found " << end - start + 1 << " items.\n";
		// ���� �ܾ� ���� ���
		for (int i = start; i <= end; i++) {
			print(i);
		}
	}// ã�� �ܾ ������ ��� 3���� ���� ����
	else {
		cout << "Not found.\n";
		// ���� �� �ܾ �������� ������
		if (index == 0) {
			cout << "- - -\n";
			cout << dict[index] << " " << wordclass[index] << endl;
		}// ���� �� �ܾ �������� ������
		else if (index == counts - 1) {
			cout << dict[index] << " " << wordclass[index] << endl;
			cout << "- - -\n";
		}// �� �� �ܾ �� ������
		else {
			cout << dict[index] << " " << wordclass[index] << endl;
			cout << "- - -\n";
			cout << dict[index + 1] << " " << wordclass[index + 1] << endl;
		}
	}
}

// ���ϴ� �ܾ �������� ã�� ��ȯ�˻� O(logn)
int find(string *words, char* target, int begin, int end) {
	int middle = (begin + end) / 2;
	if (begin > end) return middle;
	else {
		char *temp = (char*)words[middle].c_str(); // ���� ù ��°�ܾ�
		int comp = _stricmp(temp, target);				// ��� �ܾ�� ã�� �ܾ ��(��ҹ��� �������)
	
		if (comp == 0) return middle;
		else if (comp > 0) return find(words, target, begin, middle - 1);
		else return find(words, target, middle + 1, end);
	}
}