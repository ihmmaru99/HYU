#include <bits/stdc++.h>
using namespace std;

class name_grade {
	public:
		string student_name;
		int korean;
		int math;
		int english;
		int science;
		int social;
		int history;

		void set_grade(string tuple)
		{
			stringstream tuplestr(tuple);
			string tempstr;

			getline(tuplestr, student_name, ',');

			getline(tuplestr, tempstr, ',');
			korean = stoi(tempstr);
			
			getline(tuplestr, tempstr, ',');
			math = stoi(tempstr);
			
			getline(tuplestr, tempstr, ',');
			english = stoi(tempstr);
			
			getline(tuplestr, tempstr, ',');
			science = stoi(tempstr);
			
			getline(tuplestr, tempstr, ',');
			social = stoi(tempstr);
			
			getline(tuplestr, tempstr);
			history = stoi(tempstr);
		}
};

class name_number{
	public :
		string student_name;
		string student_number;

		void set_number(string tuple)
		{
			stringstream tuplestr(tuple);
			string tempstr;


			getline(tuplestr, student_name, ',');
			getline(tuplestr, student_number, ',');
		}
};

string make_tuple(string name, string number)
{
	string ret = "";

	ret += name+ "," + number +"\n";

	return ret;
}

void grade1_hash(char c, string s){
	ofstream fin;
	string file_name;
	file_name += "grade1_";
	file_name += c;
	file_name += ".csv";
	fin.open(file_name, ios::out | ios::app);
	fin << s << '\n';
}

void grade2_hash(char c, string s){
	ofstream fin;
	string file_name;
	file_name += "grade2_";
	file_name += c;
	file_name += ".csv";
	fin.open(file_name, ios::out | ios::app);
	fin << s << '\n';
}

void name_hash(char c, string s){
	ofstream fin;
	string file_name;
	file_name += "number_";
	file_name += c;
	file_name += ".csv";
	fin.open(file_name, ios::out | ios::app);
	fin << s << '\n';
}

int main(){

	string buffer[2];
	name_grade temp0;
	name_grade temp1;
	name_number temp2;
	fstream block[12];
	ofstream output;
	ofstream temp_output;
	int cnt = 0;

	output.open("./output3.csv");
	temp_output.open("./temp_output.csv");
	if(output.fail())
	{
		cout << "output file opening fail.\n";
	}

	/*********************************************************************/

	// write codes here.
	for(int i=0; i<1000; i++){
		buffer[0] ="";
		buffer[0] += "./name_grade1/";
		buffer[0] += to_string(i);
		buffer[0] += ".csv";
		block[0].open(buffer[0], ios::in | ios::out);
		if(block[0].is_open()){
			while(getline(block[0], buffer[1])){
				temp0.set_grade(buffer[1]);
				grade1_hash(temp0.student_name[0], buffer[1]);
			}
		}
		block[0].close();
	}
	for(int j=0; j<1000; j++){
		buffer[0] ="";
		buffer[0] += "./name_grade2/";
		buffer[0] += to_string(j);
		buffer[0] += ".csv";
		block[0].open(buffer[0], ios::in | ios::out);
		if(block[0].is_open()){
			while(getline(block[0], buffer[1])){
				temp1.set_grade(buffer[1]);
				grade2_hash(temp1.student_name[0], buffer[1]);
			}
		}
		block[0].close();
	}
	for(int k=0; k<1000; k++){
		buffer[0] ="";
		buffer[0] += "./name_number/";
		buffer[0] += to_string(k);
		buffer[0] += ".csv";
		block[0].open(buffer[0], ios::in | ios::out);
		if(block[0].is_open()){
			while(getline(block[0], buffer[1])){
				temp2.set_number(buffer[1]);
				name_hash(temp2.student_name[0], buffer[1]);
			}
		}
		block[0].close();
	}
	for(int i=0; i<10; i++){
		buffer[0] ="";
		buffer[0] += "grade1_";
		buffer[0] += 'a'+i;
		buffer[0] += ".csv";
		// cout << buffer[0] << '\n';
		block[0].open(buffer[0], ios::in | ios::out);
		if(block[0].is_open()){
			while(getline(block[0], buffer[1])){
				//cout << buffer[1] << '\n';
				buffer[0] ="";
				buffer[0] +="grade2_";
				buffer[0] += 'a'+i;
				buffer[0] += ".csv";
				block[1].open(buffer[0], ios::in | ios::out);
				//cout << buffer[1] << '\n';
				if(block[1].is_open()){
					temp0.set_grade(buffer[1]);
					while(getline(block[1], buffer[1])){
						temp1.set_grade(buffer[1]);
						if(temp0.student_name == temp1.student_name){
							if(temp0.english> temp1.english)
								cnt++;
							if(temp0.history>temp1.history)
								cnt++;
							if(temp0.korean<temp1.history)
								cnt++;
							if(temp0.math<temp1.math)
								cnt++;
							if(temp0.science<temp1.science)
								cnt++;
							if(temp0.social<temp1.social)
								cnt++;
							if(cnt >= 2)
								temp_output << buffer[1] << '\n';
						}
						cnt = 0;
					}
				}
				block[1].close();
			}
		}
		block[0].close();
	}
	temp_output.close();
	block[0].open("temp_output.csv", ios::in | ios::out);
	if(block[0].is_open()){
		for(int i=0; i<10; i++){
			buffer[0] ="";
			buffer[0] += "number_";
			buffer[0] += 'a'+i;
			buffer[0] += ".csv";
			block[1].open(buffer[0], ios::in | ios::out);
			if(block[1].is_open()){
				while(getline(block[0], buffer[1])){
					temp0.set_grade(buffer[1]);
					//cout << buffer[1];
					while(getline(block[1], buffer[1])){
						temp2.set_number(buffer[1]);
						//cout << buffer[1];
						if(temp0.student_name == temp2.student_name){
							buffer[2] = make_tuple(temp2.student_name, temp2.student_number);
							output << buffer[2];
							break;
						}
					}
				}
			}
			block[1].close();
		}
	}
	block[0].close();

	/*********************************************************************/
	output.close();	
}
