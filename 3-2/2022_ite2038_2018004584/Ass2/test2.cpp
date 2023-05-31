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

void age_hash(char c, string s){
	ofstream fin;
	string file_name;
	file_name += "age_";
	file_name += c;
	file_name += ".csv";
	fin.open(file_name, ios::out | ios::app);
	fin << s << '\n';
}

void salary_hash(char c, string s){
	ofstream fin;
	string file_name;
	file_name += "salary_";
	file_name += c;
	file_name += ".csv";
	fin.open(file_name, ios::out | ios::app);
	fin << s << '\n';
}

int main(){

	string buffer[2];
	name_age temp0;
	name_salary temp1;
	fstream block[12];
	ofstream output;

	output.open("./output2.csv");

	if(output.fail())
	{
		cout << "output file opening fail.\n";
	}


	/******************************************************************/

	// write codes here.
	for(int i=0; i<1000; i++){
		buffer[0] ="";
		buffer[0] += "./name_age/";
		buffer[0] += to_string(i);
		buffer[0] += ".csv";
		block[0].open(buffer[0], ios::in | ios::out);
		if(block[0].is_open()){
			while(getline(block[0], buffer[1])){
				temp0.set_name_age(buffer[1]);
				age_hash(temp0.name[0], buffer[1]);
			}
		}
		block[0].close();
	}
	for(int j=0; j<1000; j++){
		buffer[0] ="";
		buffer[0] += "./name_salary/";
		buffer[0] += to_string(j);
		buffer[0] += ".csv";
		block[0].open(buffer[0], ios::in | ios::out);
		if(block[0].is_open()){
			while(getline(block[0], buffer[1])){
				temp0.set_name_age(buffer[1]);
				salary_hash(temp0.name[0], buffer[1]);
			}
		}
		block[0].close();
	}
	for(int i=0; i<10; i++){
		buffer[0] ="";
		buffer[0] += "age_";
		buffer[0] += 'a'+i;
		buffer[0] += ".csv";
		// cout << buffer[0] << '\n';
		block[0].open(buffer[0], ios::in | ios::out);
		if(block[0].is_open()){
			while(getline(block[0], buffer[1])){
				// cout << buffer[1] << '\n';
				buffer[0] ="";
				buffer[0] +="salary_";
				buffer[0] += 'a'+i;
				buffer[0] += ".csv";
				block[1].open(buffer[0], ios::in | ios::out);
				// cout << buffer[0] << '\n';
				if(block[1].is_open()){
					temp0.set_name_age(buffer[1]);
					while(getline(block[1], buffer[1])){
						temp1.set_name_salary(buffer[1]);
						if(temp0.name == temp1.name){
							buffer[2] = make_tuple(temp0.name, temp0.age, temp1.salary);
							//cout << buffer[2];
							output << buffer[2];
							break;
						}
					}
				}
				block[1].close();
			}
		}
		block[0].close();
	}
	/******************************************************************/

	output.close();

	
}
