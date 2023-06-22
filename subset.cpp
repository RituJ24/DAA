#include <iostream>
#include <vector>

using namespace std;

//Print original subset
void printSet(const vector<int>& set){
	cout<<endl<<"Original Set:";
	for(int i=0; i<set.size(); i++){
		cout<<set[i]<< " ";
	}
	cout<<endl;
}
//print the subset
void printSubset(const vector<int>& subset) {
    cout <<endl<< "Subset: ";
    for (int i = 0; i < subset.size(); i++) {
        cout << subset[i] << " ";
    }
    cout << endl;
}

// Backtracking function to find the subset with the given sum
void subsetSum(vector<int>& set, vector<int>& subset, int sum, int index) {
    if (sum == 0) {
        printSubset(subset);
        return;
    }

    if (sum < 0 || index >= set.size()) {
        return;
    }

    subset.push_back(set[index]);
    subsetSum(set, subset, sum - set[index], index + 1);

    subset.pop_back();
    subsetSum(set, subset, sum, index + 1);
}

int main() {
    int n;
    cout << "Enter the number of elements in the set: ";
    cin >> n;

    vector<int> set(n);
    for (int i = 0; i < n; i++) {
    	cout<<"Enter "<<i+1<<"th elements of set: ";
        cin >> set[i];
    }

    int sum;
    cout <<endl<< "Enter the target sum: ";
    cin >> sum;

	printSet(set);

    vector<int> subset;
    subsetSum(set, subset, sum, 0);

    return 0;
}

