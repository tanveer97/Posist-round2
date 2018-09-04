/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
C#, VB, Perl, Swift, Prolog, Javascript, Pascal, HTML, CSS, JS
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <bits/stdc++.h>
using namespace std;

typedef struct NodeData{
	string ownerId;
	float value;
	string ownerName;
}NodeData;

typedef struct Node{
	float timestamp;
	NodeData data;
	int nodeNum;
	Node* nodeId;
	Node* refId;
	vector<Node *> childRefId;
	Node* genId;

}Node;

float getTimestamp(){
	time_t timer;
	struct tm y2k = {0};
	double seconds;
	y2k.tm_hour = 0;   y2k.tm_min = 0; y2k.tm_sec = 0;
	y2k.tm_year = 100; y2k.tm_mon = 0; y2k.tm_mday = 1;
	time(&timer);
	seconds = difftime(timer,mktime(&y2k));
	return seconds;
}
int insertNode(int parent, Node * curr, unordered_map<int, Node*> &mp, unordered_map<int, int> &rem){
	Node * ref = mp[parent];
	int remain = rem[parent];
	curr->refId = ref;
	if(curr->data.value<=remain){
		ref->childRefId.push_back(curr);
		rem[parent]-=curr->data.value;
		return 1;
	}
	else return -1;
}

int main() {
	cout<<"Create list of records"<<endl;
	int num=0;
	Node *gen=NULL;
	unordered_map<int, Node*> mp;  //hash map to store node number and its address
	unordered_map<int, int> remaining; // hash map to store node number and remaining sum it's children can have
	int ownid, val, par;
	string name;
	char inpt;
	while(1){           //create nodes till user wants to
		Node *temp = new Node;
		temp->timestamp=getTimestamp();
		cout<<"Node id is : "<<&temp<<" and Node number is : "<<num;
		cout<<"Enter owner id :"; cin>>ownid;
		cout<<"Enter value :"; cin>>val;
		cout<<"Owner Name :"; cin>>name;
		temp->data.ownerId=ownid;
		temp->data.value=val;
		temp->data.ownerName=name;
		temp->nodeId=temp;
		temp->nodeNum = num;
		mp.insert({num,temp});
		remaining.insert({num,val});
		if(num==0) {
			gen = temp;
			temp->refId = NULL;
		}
		else{
			cout<<"Enter parent node number : "; cin>>par;
			int res = insertNode(par, temp, mp, remaining);
			if(res==-1){
				cout<<"Error!";
				remaining.erase(num);
				num--;
			}
		}
		temp->genId = gen;
		num++;
		cout<<"Insert more? (Y/N)"; cin>>inpt;
		if(inpt!='Y')break;
	}
	cout<<num;
	return 0;
}