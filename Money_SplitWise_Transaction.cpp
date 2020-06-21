#include <iostream>
#include<set>
using namespace std;
//splitwise algorithm
int main() {

    //declare number of friends and total number of transactions
    int no_of_transactions,friends;
    
    //input no_of_tranactions and friends
    cin>>no_of_transactions>>friends;
    
    //declare x-from y-to amount
    int x,y,amount;

    //declare an 1-d array to store the net amount each person will have to take at the end
    int net[100000]={0};

    while(no_of_transactions--)
    {
        cin>>x>>y>>amount;
        net[x]-=amount;
        net[y]+=amount;
    }

    //declare the multi set so that net differences of transactions should be in the sorted order and duplicate values can be present(multiple values can be same).

    multiset<int> m;
    
    //initialize a list and to be sorted ==> multiset
    for(int i=0;i<friends;i++)
    {
        if(net[i]!=0)  //means there exists a transaction
        {
            m.insert(net[i]);
        }
    }
    //each settlement is counted as a transaction
    int cnt=0;

    //pop out two person from left and right and try to settle them
    while(!m.empty())
    {
        auto low=m.begin();
        auto high=prev(m.end());

        int debit=*low; //person can give upto that money
        int credit=*high;//person can take upto that money

        //erase or remove the element from the multiset
        m.erase(low);
        m.erase(high);

        //settlement
        int settlement_amount=min(-debit,credit);
         
        cnt++;  //transaction count is incremented

        //settlement_amount from donor to acceptor
        debit+=settlement_amount;
        credit-=settlement_amount;
        //after this one of them will be zero i.e the amount which is not zero will get inserted again in the multiset

        if(debit!=0)
           m.insert(debit);
        if(credit!=0)
           m.insert(credit);        
    }
    cout<<cnt<<endl;
    return 0;
}
