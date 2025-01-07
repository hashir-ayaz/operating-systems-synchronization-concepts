#include <thread>
#include <string>
#include <iostream>

using namespace std;

struct family{
	int dad_age;
	int mom_age;
	int child_age;
	int total_age;
};

void sum(family& f){
	int total_ages = f.dad_age+f.mom_age+f.child_age;
	std::cout<<"the total age is "<<total_ages<<std::endl;
	f.total_age=total_ages;

}

int main()
{
	family f ={10,20,30};
	thread t1(sum,ref(f));

	t1.join();
	
	cout<<"the total age in main is "<<f.total_age<<endl;

	return 0;
}