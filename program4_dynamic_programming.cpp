#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>

using namespace std;

// A utility function that returns
// maximum of two integers
int max(int a, int b)
{ 
    return (a > b) ? a : b; 
}
 
// Returns the maximum value that
// can be put in a knapsack of capacity W
int knapSack(int W, int wt[], int val[], int n)
{
    int i, w;
    int K[n + 1][W + 1];
    string planet[] = {"planet_A","planet_B","planet_C","planet_D","planet_E","planet_F","planet_G","planet_H","planet_I","planet_J"};
    // Build table K[][] in bottom up manner
    for (i = 0; i <= n; i++) 
    {   
        for (w = 0; w <= W; w++) 
        {
            if (i == 0 || w == 0)
                K[i][w] = 0;
            else if (wt[i - 1] <= w)
                K[i][w] = max(val[i - 1]+ K[i - 1][w - wt[i - 1]],K[i - 1][w]);
            else
                K[i][w] = K[i - 1][w];  
        }
    }
    for(int i=0; i<=n; i++)
        {   
            //cout<< "+-------+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+" <<endl;
            cout<<"k = "<< i << "\t";
        for(int j=0; j<=W; j++)
                {
                        cout<<K[i][j]<<" ";
                }
                cout<<"\n";
        }
    //cout<< "+-------+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+" <<endl;
    // stores the result of Knapsack 
    int res = K[n][W];     

    cout<< "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n| \tChosen planet\t\t|";
    cout<< "\n|Planet_? |\tweight\t|profit\t|\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
    w = W; 
    int total = 0;
    for (i = n; i > 0 && res > 0; i--) { 

        // either the result comes from the top 
        // (K[i-1][w]) or from (val[i-1] + K[i-1] 
        // [w-wt[i-1]]) as in Knapsack table. If 
        // it comes from the latter one/ it means  
        // the item is included. 
        if (res == K[i - 1][w])  
            continue;         
        else { 
  
            // This item is included. 
            cout<<"|"<<planet[i-1]<<" |\t"<< wt[i - 1] <<"\t| "<< val[i-1]<< "\t|"<<endl; 
            total += wt[i-1];
            // Since this weight is included its  
            // value is deducted 
            res = res - val[i - 1]; 
            w = w - wt[i - 1]; 
        } 

    } 
    cout<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n| Maximum profit gained: " << K[n][W];
    cout << "\t| \n| Total weight : " << total <<"\t\t|\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
    return K[n][W];
}

void splitString(const string &str, vector<string> &output)
{
    string::size_type start = 0; // Where to start
    string::size_type last = str.find_first_of(" "); // Finds the first space

    // npos means that the find_first_of wasn't able to find what it was looking for
    // in this case it means it couldn't find another space so we are at the end of the
    // words in the string.
    while (last != string::npos)
    {
        // If last is greater then start we have a word ready
        if (last > start)
        {
            output.push_back(str.substr(start, last - start)); // Puts the word into a vector look into how the method substr() works
        }

        start = ++last; // Reset start to the first character of the next word
        last = str.find_first_of(" ", last); // This means find the first space and we start searching at the first character of the next word
    }

    // This will pickup the last word in the file since it won't be added to the vector inside our loop
    output.push_back(str.substr(start));
}

int main(){
    vector<string> words,id,weight,profit,dataStructure;
    string line;
    ifstream file;
    file.open("A2planets.txt");
    if (file.is_open()) {
        while(getline(file,line)){
        dataStructure.push_back(line);
        }

        for(vector<string>::size_type i = 0; i < dataStructure.size(); i++){
        splitString(dataStructure[i],words);
        }

        for (auto i = 0; i < 10; ++i){
            int index = i*6;
            int index_weight = index+4;
            int index_profit = index+5;
            id.push_back(words[index]);
            weight.push_back(words[index_weight]);
            profit.push_back(words[index_profit]);
            cout<< dataStructure[i]<<endl;
        }
        file.close();
    }else {
        cout<<"unable to open file";
    }

    int intWeight[10],intProfit[10];
    for (int i=0; i<= 9; i++){
        int num = atoi(weight.at(i).c_str());
        intWeight[i]=num;
        int num2 = atoi(profit.at(i).c_str());
        intProfit[i]=num2;
    }
    int n = sizeof(intProfit) / sizeof(intProfit[0]);
    cout<< "Maximum capacity is : 80 tons \n\nThe 0/1 knapsack matrix is : \n";
    knapSack(80, intWeight, intProfit,n);
}


