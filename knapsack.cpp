#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Object {
    int p;
    int w;
    double pw;
};

//Comparing pi/wi 
bool compare(Object a, Object b) {
    return a.pw > b.pw;
}

int main() {
    int n, M;
    cout<<"Enter number of objects: ";
    cin >> n;
    cout<<"Enter size of Knapsack: ";
    cin>>M;

    vector<Object> objects(n);
    for (int i = 0; i < n; i++) {
    	cout<<endl<<"Enter Profit of "<<i+1<<" : ";
        cin >> objects[i].p;
        cout<<endl<<"Enter Weight of "<<i+1<<" : ";
        cin >> objects[i].w;
        objects[i].pw = (double)objects[i].p / objects[i].w;
    }

	cout<<endl;
	
	//sorting 
    sort(objects.begin(), objects.end(), compare);

    double profit = 0.0;
    double k = 0.0;
    int i = 0;
    
    //knapsack
    while (M > 0 && i < n) {
        if (M >= objects[i].w) {
            profit += objects[i].p;
            M -= objects[i].w;
            cout<<"Optimal Solution of: "<<objects[i].p<<"/"<<objects[i].w<<" = 1"<<endl;
        } else {
        	k = (double)  M / objects[i].w ;
        	cout<<"Optimal Solution of: "<<objects[i].p<<"/"<<objects[i].w<<" = "<<k<<endl;
            profit += M * objects[i].pw;
            M = 0;
        }
        i++;
    }

	cout<<endl;
	for(i=0; i<n; i++){
		cout<<"pi/wi of "<<objects[i].p<<"/"<<objects[i].w<<" : "<<objects[i].pw;
		cout<<endl;
	}
	
    cout << endl << "Maximum Profit: " << profit << endl;

    return 0;
}


