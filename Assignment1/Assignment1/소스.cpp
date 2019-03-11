#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <string.h>
#include <vector>
using namespace std;
vector<string> *dict;	// 사전을 담을 벡터
int counts, capacity;	// 단어들의 수, 용량

void init();			// 시작시 변수 초기화
void reallocate();		// 오버플로우 방지
void print(int n);
void movement();		// 메인 동작
void read(string name);	// 파일 읽어서 dict에 저장
void search(string target); // dict에서 target 찾기
int find(vector<string> *words, char* target, int begin, int end); // target을 찾는 동작


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

		getline(cin, line);	// 공백 입력도 처리하기위함
		istringstream iss(line);
		iss >> cmd;	// 여백 띄우는 방법

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
	char* temp = (char*)target.c_str();	// 찾고 싶은 단어

	int index = find(dict, temp, 0, counts - 1);
	if (index == -1) { index = 0; }
	char* comp =(char*) dict[index].at(0).c_str();	// 반환받은 위치 단어
	int check = _strcmpi(temp, comp);

	if (check == 0) {
		int start = index, end = index;
		// 동일 단어 전부 출력 위해 index를 단어 가장앞으로 이동
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
		// 찾았을 떄 출력
		cout << "Found " << end - start + 1 << " items.\n";
		for (int i = start; i <= end; i++) {
			print(i);
		}

	}// 찾는 단어가 있을때
	else {
		cout << "Not found.\n";
		if (index == 0) {
			cout << "- - -\n";
			for (int i = 0; i < dict[index].size(); i++) {
				string temp = dict[index].at(i);
				cout << temp << " ";
				if (temp[temp.size() - 1] == ')') break; // 마지막 문자가 )이면 종료
			}	
		}// 제일 앞 단어가 존재하지 않을때
		else if (index == counts - 1) {
			for (int i = 0; i < dict[index].size(); i++) {
				string temp = dict[index].at(i);
				cout << temp << " ";
				if (temp[temp.size() - 1] == ')') break; // 마지막 문자가 )이면 종료
			}
			cout << endl;
			cout << "- - -\n";
		}// 제일 뒤 단어가 존재하지 않을떄
		else {
			for (int i = 0; i < dict[index].size(); i++) {
				string temp = dict[index].at(i);
				cout << temp << " ";
				if (temp[temp.size() - 1] == ')') break; // 마지막 문자가 )이면 종료
			}
			cout << endl;
			cout << "- - -\n";
			for (int i = 0; i < dict[index+1].size(); i++) {
				string temp = dict[index+1].at(i);
				cout << temp << " ";
				if (temp[temp.size() - 1] == ')') break; // 마지막 문자가 )이면 종료
			}
			cout << endl;
		} // 앞 뒤 단어가 다 있을때
	}// 찾는 단어가 없을때
}

int find(vector<string> *words, char* target, int begin, int end) {
	int middle = (begin + end) / 2;
	if (begin > end && end == -1) return -1;
	if (begin > end) return middle;
	else {
		char *temp = (char*)words[middle].at(0).c_str(); // 비교할 첫 번째단어
		
		int comp = _strcmpi(temp, target);

		if (comp == 0) return middle;
		else if (comp > 0) return find(words, target, begin, middle - 1);
		else return find(words, target, middle + 1, end);
	}
}