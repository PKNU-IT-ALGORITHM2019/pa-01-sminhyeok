#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <string.h>
#include <vector>
using namespace std;
vector<string> *dict;	// ������ ���� ����
int counts, capacity;	// �ܾ���� ��, �뷮

void init();			// ���۽� ���� �ʱ�ȭ
void reallocate();		// �����÷ο� ����
void print(int n);
void movement();		// ���� ����
void read(string name);	// ���� �о dict�� ����
void search(string target); // dict���� target ã��
int find(vector<string> *words, char* target, int begin, int end); // target�� ã�� ����


int main() {
	init();
	movement();
}
void init() {
	counts = 0;
	capacity = 10;
	dict = new vector<string>[capacity];
}
void reallocate() {
	capacity *= 2;
	vector<string> *temp = new vector<string>[capacity];
	for (int i = 0; i < counts; i++)
		temp[i] = dict[i];
	dict = temp;
}
void print(int n) {
	for (int i = 0; i < dict[n].size(); i++) {
		cout << dict[n].at(i) << " ";
	}
	cout << endl;
}

void movement() {
	string line, cmd;

	while (1) {
		cout << "$ ";

		getline(cin, line);	// ���� �Էµ� ó���ϱ�����
		istringstream iss(line);
		iss >> cmd;	// ���� ���� ���

		if (cmd == "read") {
			if (iss >> cmd) read(cmd);
		}
		else if (cmd == "size") { 
			cout << counts << endl;
		}
		else if (cmd == "find") {
			if(iss >> cmd) search(cmd);
		}
		else if (cmd == "exit") break;
	}
}
void read(string name) {
	ifstream fin(name);
	if (!fin) cout << "File Open Fail\n";
	string line;
	while (getline(fin, line)) {

		if (line == "\0") continue;
		if (counts >= capacity) reallocate();
		istringstream iss(line);
		string word;

		for (int i = 0; ; i++) {
			if (iss >> word) {
				dict[counts].push_back(word);
			}
			else break;
		}
		counts++;
	}
	
}

void search(string target) {
	char* temp = (char*)target.c_str();	// ã�� ���� �ܾ�

	int index = find(dict, temp, 0, counts - 1);
	if (index == -1) { index = 0; }
	char* comp =(char*) dict[index].at(0).c_str();	// ��ȯ���� ��ġ �ܾ�
	int check = _strcmpi(temp, comp);

	if (check == 0) {
		int start = index, end = index;
		// ���� �ܾ� ���� ��� ���� index�� �ܾ� ��������� �̵�
		for (int i = index; i >= 0; i--) {
			char* s = (char*)dict[i].at(0).c_str();
			int c = _strcmpi(temp, s);
			if (c != 0) {start = i+1; break;}
		}
		for (int i = index; i < counts; i++) {
			char* s = (char*)dict[i].at(0).c_str();
			int c = _strcmpi(temp, s);
			if (c != 0) { end = i - 1; break; }
		}
		// ã���� �� ���
		cout << "Found " << end - start + 1 << " items.\n";
		for (int i = start; i <= end; i++) {
			print(i);
		}

	}// ã�� �ܾ ������
	else {
		cout << "Not found.\n";
		if (index == 0) {
			cout << "- - -\n";
			for (int i = 0; i < dict[index].size(); i++) {
				string temp = dict[index].at(i);
				cout << temp << " ";
				if (temp[temp.size() - 1] == ')') break; // ������ ���ڰ� )�̸� ����
			}	
		}// ���� �� �ܾ �������� ������
		else if (index == counts - 1) {
			for (int i = 0; i < dict[index].size(); i++) {
				string temp = dict[index].at(i);
				cout << temp << " ";
				if (temp[temp.size() - 1] == ')') break; // ������ ���ڰ� )�̸� ����
			}
			cout << endl;
			cout << "- - -\n";
		}// ���� �� �ܾ �������� ������
		else {
			for (int i = 0; i < dict[index].size(); i++) {
				string temp = dict[index].at(i);
				cout << temp << " ";
				if (temp[temp.size() - 1] == ')') break; // ������ ���ڰ� )�̸� ����
			}
			cout << endl;
			cout << "- - -\n";
			for (int i = 0; i < dict[index+1].size(); i++) {
				string temp = dict[index+1].at(i);
				cout << temp << " ";
				if (temp[temp.size() - 1] == ')') break; // ������ ���ڰ� )�̸� ����
			}
			cout << endl;
		} // �� �� �ܾ �� ������
	}// ã�� �ܾ ������
}

int find(vector<string> *words, char* target, int begin, int end) {
	int middle = (begin + end) / 2;
	if (begin > end && end == -1) return -1;
	if (begin > end) return middle;
	else {
		char *temp = (char*)words[middle].at(0).c_str(); // ���� ù ��°�ܾ�
		
		int comp = _strcmpi(temp, target);

		if (comp == 0) return middle;
		else if (comp > 0) return find(words, target, begin, middle - 1);
		else return find(words, target, middle + 1, end);
	}
}