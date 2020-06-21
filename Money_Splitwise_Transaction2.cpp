#include <iostream>
#include<map>
#include<set>
using namespace std;

class person_compare{
    public:
      bool operator()(pair<string,int> p1,pair<string,int> p2)
      {
          return p1.second<p2.second;
      }
};
//MONEY SPLITWISE ALGORITHM
int main() {
    //should also show transacions
    // we'll use stl(Maps)

    //declare number of friends and total number of transactions
    int no_of_transactions,friends;
    
    //input no_of_tranactions and friends
    cin>>no_of_transactions>>friends;
    
    //declare x-from y-to amount
    string x,y;
    int amount;
    
    //unordered map for the name with debit and credit
    map<string,int> net;
  
    while(no_of_transactions--)
    {
        cin>>x>>y>>amount;
        //check if the person exist or not
        if(net.count(x)==0)
            net[x]=0;
        if(net.count(y)==0)
            net[y]=0;
        net[x]-=amount;
        net[y]+=amount;    
    }

    //declare a multiset for the values
    multiset<pair<string,int>,person_compare> m;
    //Iterate over the persons,add those persons in the multiset who have non zero net
    for(auto p:net)
    {
         string person=p.first;
         int amount=p.second;
         if(net[person]!=0)
         {
             m.insert(make_pair(person,amount)); //in the multiset the comparison takes place according to the first parameter 
             //You can either put amount int front of person name or make a custom comparator 
         }
    }

    //Make settlements
    //start and end pop and settle them
    int cnt=0;
    while(!m.empty())
    {
        auto low=m.begin();
        auto high=prev(m.end());

        //debit amount
        int debit=low->second;
        string debit_person=low->first;

        //credit amount
        int credit=high->second;
        string credit_person=high->first;

        //pop them out
        m.erase(low);
        m.erase(high);

        //settlement amount
        int settled_amount=min(-debit,credit);
        debit+=settled_amount;
        credit-=settled_amount;
           
         cnt++;  
        //print the transaction
        cout<<debit_person<<" will pay "<<settled_amount<<" to "<<credit_person<<endl;
        if(debit!=0)
           m.insert(make_pair(debit_person,debit));
        if(credit!=0)
           m.insert(make_pair(credit_person,credit));    
    }
    cout<<cnt<<endl;


    return 0;
}
