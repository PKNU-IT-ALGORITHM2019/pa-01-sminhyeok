/*
	201412700 ������ ������Ű��а�
	���� ���α׷� - ���ϴ� �ܾ� �������, �ܾ ������ �� �� �ܾ� ���
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <string.h>
#include <vector>
using namespace std;

vector<string> *dict;	// ������ ���� ���� , vector[i] ���� �տ� �� �ܾ ���� �� �ڿ��� i��° �ܾ��� ����
int counts, capacity;	// �ܾ���� ��, �뷮

void init();			// ���۽� ���� �ʱ�ȭ
void reallocate();		// �����÷ο� ����
void print(int n);		// �ܾ� ���� ���
void movement();		// ���� ����
void read(string name);	// ���� �о dict�� ����
void search(string target); // dict���� target ã��
int find(vector<string> *words, char* target, int begin, int end); // target�� ã�� ����


int main() {
	init();				// ���� ������ ���� ������ �ʱ�ȭ
	movement();			// ���� ���α׷� ����
}

void init() {
	counts = 0;			// �ܾ���� ��
	capacity = 10000;		// ó�� ������ ũ��
	dict = new vector<string>[capacity];	// capacity ũ���� ���� ����
}

void reallocate() {		// ������ �� á���� ���Ҵ�
	capacity *= 2;		// ���� �뷮 2��� ����
	vector<string> *temp = new vector<string>[capacity];
	for (int i = 0; i < counts; i++)
		temp[i] = dict[i];
	dict = temp;
}

void print(int n) {		// n ��° �ܾ��� ���� ���
	for (int i = 0; i < dict[n].size(); i++) {
		cout << dict[n].at(i) << " ";
	}
	cout << endl;
} 

void movement() {	// ����
	string line, cmd;	// �Է�, ��ɾ�

	while (1) {
		cout << "$ ";

		getline(cin, line);	// ���� �Էµ� ó���ϱ�����
		istringstream iss(line);
		iss >> cmd;	// �ܾ� ������ ���� �����ϰ� �Է¹���

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

void read(string name) {	// �ܾ��� �д� ���� - ���� ����
	ifstream fin(name);
	if (!fin) cout << "File Open Fail\n";
	
	string line;	// �� ���� �Է� ���� ����
	while (getline(fin, line)) { // �� �̻� �Է��ϴ� �ܾ ���������� �ݺ�
			
		if (line == "\0") continue;	// �ܼ� �����̸� ����
		if (counts >= capacity) reallocate();	// ������ �� á���� ���Ҵ�
		istringstream iss(line);				
		string word;							// line ������ �Էµ� �����͸� �������� �����ؼ� �Է� ����

		for (int i = 0; ; i++) {				// line�� ������ ������ ���� ������ �Է�
			if (iss >> word) {					// �� �̻� �����Ͱ� ������ �ݺ� ����
				dict[counts].push_back(word);	// dict[counts]�� �����͸� ����. ���� ù��°�� �ܾ� �� �ڴ� ����
			}
			else break;
		}
		counts++;								// �ܾ 1�� �Էµɶ����� �ܾ� �� ����
	}
	
}

void search(string target) {					// ���ϴ� �ܾ ã�� ����
	char* temp = (char*)target.c_str();	// ã�� ���� �ܾ� temp

	int index = find(dict, temp, 0, counts - 1);	// ������ ���ϴ� �ܾ �ִ��� �������� ã�� ����. �ܾ��� �ε��� ��ȯ
	if (index == -1) { index = 0; }					// ��ȿ ������ ���� ��� ����
	char* comp =(char*) dict[index].at(0).c_str();	// ��ȯ���� ��ġ �ܾ�
	int check = _strcmpi(temp, comp);				// ��ȯ���� �ε����� ã�� �������� ��ġ����, �����Ͱ� �������� ��ġ���� Ȯ��

	if (check == 0) {								// ã�� �ܾ ������
		int start = index, end = index;
		// ���� �ܾ� ���� ���� index �� start�� ����
		for (int i = index; i >= 0; i--) {
			char* s = (char*)dict[i].at(0).c_str();
			int c = _strcmpi(temp, s);
			if (c != 0) {start = i+1; break;}
		}// ���� �ܾ� �� ���� ���� index�� end�� ����
		for (int i = index; i < counts; i++) {
			char* s = (char*)dict[i].at(0).c_str();
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
	}
}

// ���ϴ� �ܾ �������� ã�� ��ȯ�˻� O(logn)
int find(vector<string> *words, char* target, int begin, int end) {
	int middle = (begin + end) / 2;

	if (begin > end) return middle;
	else {
		char *temp = (char*)words[middle].at(0).c_str(); // ���� ù ��°�ܾ�
		
		int comp = _strcmpi(temp, target);				// ��� �ܾ�� ã�� �ܾ ��(��ҹ��� �������)

		if (comp == 0) return middle;
		else if (comp > 0) return find(words, target, begin, middle - 1);
		else return find(words, target, middle + 1, end);
	}
}