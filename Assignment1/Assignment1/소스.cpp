/*
		201412700 성민혁 정보통신공학과
		사전 프로그램 - 원하는 단어 설명출력, 단어가 없으면 앞 뒤 단어 출력
*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <string.h>
using namespace std;

string dict[200000];			// 첫번째 단어
string wordclass[200000];		// 품사
string explain[200000];			// 설명

int counts;	// 단어들의 수

void init();			// 시작시 변수 초기화
void print(int n);		// 단어 설명 출력
void movement();		// 메인 동작
void read(string name);	// 파일 읽어서 dict에 저장
void search(string target); // dict에서 target 찾기
int find(string *words, char* target, int begin, int end); // target을 찾는 동작


int main() {
	init();				// 사전 생성을 위한 변수들 초기화
	movement();			// 사전 프로그램 구동
}

void init() {	counts = 0;	}	// 단어들의 수 초기화

void print(int n) {		// n 번째 단어의 정보 출력
	cout << dict[n] << " " << wordclass[n] << " " << explain[n];
	cout << endl;
}

void movement() {	// 구동
	string line, cmd;	// 입력, 명령어
	while (1) {
		cout << "$ ";
		getline(cin, line);	// 공백 입력도 처리하기위함
		istringstream iss(line);
		iss >> cmd;	// 단어 사이의 공백 무시하고 입력받음

		if (cmd == "read") {		if (iss >> cmd) read(cmd);		}	// 읽기 동작
		else if (cmd == "size") {	cout << counts << endl;			}	// 사전 사이즈 출력
		else if (cmd == "find") {	if (iss >> cmd) search(cmd);	}	// 단어 찾기
		else if (cmd == "exit") break;
	}
}

void read(string name) {	// 단어장 읽는 동작 - 사전 생성
	ifstream fin(name);
	if (!fin) cout << "File Open Fail\n";
	string line;	// 한 줄의 입력 담을 변수

	while (getline(fin, line, '(')) { // 더 이상 입력하는 단어가 없을때까지 반복
		if (line == "\0") continue;	// 단순 엔터이면 무시
		
		line.erase(line.size()-1); // 제일 뒤 공백 제거
		dict[counts] = line;

		getline(fin, line, ')');				// ()사이의 품사
		line.insert(line.begin(), '(');
		line += ')';							// () 붙여줌 + 품사생성
		wordclass[counts] = line;

		getline(fin, line);						// 설명 입력
		explain[counts] = line;

		getline(fin, line);						// 끝에 \0 하나 제거
		counts++;								// 단어가 1개 입력될때마다 단어 수 증가
	}
}// 리딩 종료

void search(string target) {					// 원하는 단어를 찾는 동작

	char* temp = (char*)target.c_str();	// 찾고 싶은 단어 temp
	int index = find(dict, temp, 0, counts - 1);	// 실제로 원하는 단어가 있는지 사전에서 찾는 동작. 단어의 인덱스 반환
	char* comp = (char*)dict[index].c_str();	// 반환받은 위치 단어
	int check = _strcmpi(temp, comp);				// 반환받은 인덱스가 찾은 데이터의 위치인지, 데이터가 없을떄의 위치인지 확인

	if (check == 0) {								// 찾는 단어가 있을때
		int start = index, end = index;

		// 동일 단어 가장 앞의 index 를 start에 저장
		for (int i = index; i >= 0; i--) {
			char* s = (char*)dict[i].c_str();
			int c = _strcmpi(temp, s);
			if (c != 0) { start = i + 1; break; }
		}// 동일 단어 중 가장 뒤의 index를 end에 저장
		for (int i = index; i < counts; i++) {
			char* s = (char*)dict[i].c_str();
			int c = _strcmpi(temp, s);
			if (c != 0) { end = i - 1; break; }
		}

		// 찾았을 떄 출력
		cout << "Found " << end - start + 1 << " items.\n";
		// 동일 단어 전부 출력
		for (int i = start; i <= end; i++) {
			print(i);
		}
	}// 찾는 단어가 없을때 출력 3가지 경우로 구분
	else {
		cout << "Not found.\n";
		// 제일 앞 단어가 존재하지 않을때
		if (index == 0) {
			cout << "- - -\n";
			cout << dict[index] << " " << wordclass[index] << endl;
		}// 제일 뒤 단어가 존재하지 않을떄
		else if (index == counts - 1) {
			cout << dict[index] << " " << wordclass[index] << endl;
			cout << "- - -\n";
		}// 앞 뒤 단어가 다 있을때
		else {
			cout << dict[index] << " " << wordclass[index] << endl;
			cout << "- - -\n";
			cout << dict[index + 1] << " " << wordclass[index + 1] << endl;
		}
	}
}

// 원하는 단어를 사전에서 찾는 순환검색 O(logn)
int find(string *words, char* target, int begin, int end) {
	int middle = (begin + end) / 2;
	if (begin > end) return middle;
	else {
		char *temp = (char*)words[middle].c_str(); // 비교할 첫 번째단어
		int comp = _stricmp(temp, target);				// 가운데 단어와 찾는 단어를 비교(대소문자 관계없이)
	
		if (comp == 0) return middle;
		else if (comp > 0) return find(words, target, begin, middle - 1);
		else return find(words, target, middle + 1, end);
	}
}