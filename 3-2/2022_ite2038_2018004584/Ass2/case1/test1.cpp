#include <bits/stdc++.h>
using namespace std;

class name_age {
	public:
		string name;
		string age;
		
		void set_name_age(string tuple)
		{
			stringstream tuplestr(tuple);
			string agestr;

			getline(tuplestr, name, ',');
			getline(tuplestr, age);
		}
};

class name_salary {
	public:
		string name;
		string salary;
		
		void set_name_salary(string tuple)
		{
			stringstream tuplestr(tuple);
			string salarystr;

			getline(tuplestr, name, ',');
			getline(tuplestr, salary);
		}
};

string make_tuple(string name, string age, string salary)
{
	return name+ ',' + age + ',' + salary + '\n';
}

int main(){
// 변수 선언은 int형만 가능함. 그니까 읽어올 때 i, j 만 가능한 듯
	string buffer[2]; // 줄을 입력받을 때 필요함. getline을 할 때 필요하다고 함. 그리고 이놈을 통해서 make_tuple을 해야함.
	name_age temp0; // class 선언
	name_salary temp1; // class 선언
	int current_block[2] = {}; // 이놈은 어디에 쓸까?
	fstream block[12]; // 블록 안에 파일을 올리는 것을 해야 하는데 어캐 하냐? 이놈을 통해서 파일 이름을 받아와야 할 것 같은데
	ofstream output; //여기에 최종 결과를 쓰는 것
	output.open("./output1.csv");

	if(output.fail())
	{
		cout << "output file opening fail.\n";
	}

	/*********************************************************************************/
	// write codes here.

	for(int i=0; i<1000; i++){
		buffer[0] ="";
		buffer[0] += "./name_age/";
		buffer[0] += to_string(i);
		buffer[0] += ".csv";
		block[0].open(buffer[0], ios::in | ios::out);
		if(block[0].is_open()){
			buffer[0] ="";
			buffer[0] +="./name_salary/";
			buffer[0] += to_string(i);
			buffer[0] += ".csv";
			//cout << buffer[0] <<'\n';
			block[1].open(buffer[0], ios::in | ios::out);
			if(block[1].is_open()){
				while(getline(block[0], buffer[1])){
					temp0.set_name_age(buffer[1]);
					while(getline(block[1], buffer[1])){
						temp1.set_name_salary(buffer[1]);
						if(temp0.name == temp1.name){
							buffer[2] = make_tuple(temp0.name, temp0.age, temp1.salary);
							output << buffer[2];
							break;
						}
					}
				}
			}
			block[1].close();
		}
		block[0].close();
	}
	/*********************************************************************************/


	output.close();
}
