#include <bits/stdc++.h>
using namespace std;

class bank {
public:
    string name;
    int netAmount;
};

int getMinIndex(bank listOfNetAmounts[], int numBanks) {
    int min = INT_MAX, minIndex = -1;
    for (int i = 0; i < numBanks; i++) {
        if (listOfNetAmounts[i].netAmount < min) {
            minIndex = i;
            min = listOfNetAmounts[i].netAmount;
        }
    }
    return minIndex;
}

int getMaxIndex(bank listOfNetAmounts[], int numBanks) {
    int max = INT_MIN, maxIndex = -1;
    for (int i = 0; i < numBanks; i++) {
        if (listOfNetAmounts[i].netAmount > max) {
            maxIndex = i;
            max = listOfNetAmounts[i].netAmount;
        }
    }
    return maxIndex;
}

void printAns(vector<vector<int>>& ansGraph, int numBanks, bank input[]) {
    cout << "\nThe transactions for minimum cash flow are as follows : \n\n";
    for (int i = 0; i < numBanks; i++) {
        for (int j = 0; j < numBanks; j++) {
            if (ansGraph[i][j] != 0) {
                cout << input[i].name << " pays Rs " << ansGraph[i][j] << " to " << input[j].name << endl;
            }
        }
    }
    cout << "\n";
}

void minimizeCashFlow(int numBanks, bank input[], unordered_map<string, int>& indexOf, int numTransactions, vector<vector<int>>& graph) {
    bank listOfNetAmounts[numBanks];
    
    for (int b = 0; b < numBanks; b++) {
        listOfNetAmounts[b].name = input[b].name;
        
        int amount = 0;
        for (int i = 0; i < numBanks; i++) {
            amount += graph[i][b];
        }
        
        for (int j = 0; j < numBanks; j++) {
            amount += (-1) * graph[b][j];
        }
        
        listOfNetAmounts[b].netAmount = amount;
    }
    
    vector<vector<int>> ansGraph(numBanks, vector<int>(numBanks, 0));
    
    while (true) {
        int minIndex = getMinIndex(listOfNetAmounts, numBanks);
        int maxIndex = getMaxIndex(listOfNetAmounts, numBanks);
        
        if (listOfNetAmounts[minIndex].netAmount == 0 && listOfNetAmounts[maxIndex].netAmount == 0)
            break;
        
        int transactionAmount = min(-listOfNetAmounts[minIndex].netAmount, listOfNetAmounts[maxIndex].netAmount);
        
        listOfNetAmounts[minIndex].netAmount += transactionAmount;
        listOfNetAmounts[maxIndex].netAmount -= transactionAmount;
        
        ansGraph[minIndex][maxIndex] += transactionAmount;
    }
    
    printAns(ansGraph, numBanks, input);
}

int main() {
	
    cout << "This system minimizes the number of transactions among multiple persons in the different corners of the world. \n\n";
    cout << "Enter the number of persons participating in the transactions.\n";
    int numBanks;
    cin >> numBanks;
    
    bank input[numBanks];
    unordered_map<string, int> indexOf;
    
    cout << "Enter the details of the Persons and transactions as stated:\n";
    cout << "Person Name \n";
    
    for (int i = 0; i < numBanks; i++) {
        
        cout <<"Person " << i+1<<" : ";
        
        cin >> input[i].name;
        string name = input[i].name;
        transform(name.begin(), name.end(), name.begin(), ::tolower);
        indexOf[input[i].name] = i;
    }
    
    cout << "Enter number of transactions.\n";
    int numTransactions;
    cin >> numTransactions;
    
    vector<vector<int>> graph(numBanks, vector<int>(numBanks, 0));
    
    cout << "Enter the details of each transaction as stated:";
    cout << "Debtor Person, creditor Person and amount\n";  // creditor person is the person that gives the loan and debtor person is the person that takes the loan
    for (int i = 0; i < numTransactions; i++) {
        cout << i+1 << " th transaction : ";
        string s1, s2;
        int amount;
        cin >> s1 >> s2 >> amount;
        
        transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
        transform(s2.begin(), s2.end(), s2.begin(), ::tolower);
        
        graph[indexOf[s1]][indexOf[s2]] = amount;
    }
     
    minimizeCashFlow(numBanks, input, indexOf, numTransactions, graph);
    return 0;
}


