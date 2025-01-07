/*
2. Multiple Threads Operating on a Shared Structure
Create a program where multiple threads operate on a shared structure that contains an array of integers. 
Each thread calculates the sum of a portion of the array and updates a shared total sum field in the structure. Use a mutex to ensure synchronization.
*/

#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
using namespace std;

mutex mtx;

void sum(vector<int>& arr,int start,int end,int& total_sum){
	int sum=0;
	for(int i=start;i<end;i++){
		sum+=arr[i];
	}

	// implement mutex here
	{
	unique_lock<mutex> lock(mtx);
	total_sum+=sum;

	}// automatically unlocks as soon as mutex leaves scope

	
}

int main(){

	int total_sum=0;	

	vector<int> arr={1,4,5,7,2,7};

	thread t1(sum,ref(arr),0,3,ref(total_sum));
	thread t2(sum,ref(arr),3,6,ref(total_sum));

	t1.join();
	t2.join();

	cout<<"the final total value is "<<total_sum<<endl;


	return 0;
}