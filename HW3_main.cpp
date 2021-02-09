//
//  main.cpp
//  Assignment 3
//
//  Created by Mahima Bhargava on 11/12/19.
//  Copyright © 2019 Mahima Bhargava. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <set>
#include <map>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include <ctime>
#include <iomanip>
using namespace std;
time_t start,check;
double maxTime = 30;
//cout << "Time taken by program is : " << fixed << time_taken << setprecision(5);
//cout << " sec " << endl;
int num_queries,num_sen;
struct predicate
{
    string name;
    int is_negated;
    vector<string> args;
    
  bool operator<(const predicate& t) const
    {
          return (this->name < t.name);
       }
   
};

bool comparator(predicate const& c1, predicate const& c2)
{
    return c1.name > c2.name;
}
typedef vector<predicate > sentence;
vector<sentence > KB;
map<string,vector<int>> kbmap;
vector<predicate > querylist;
//vector<sentence > currKB;
int argcount=1;
int size;
int isvar(string &var)
{
    if(var[0] >='a' && var[0] <='z')
        return 1;
    else
        return 0;
}
struct CompareLength {
    bool operator()(sentence const& p1, sentence const& p2)
    {
        // return "true" if "p1" is ordered
        // before "p2", for example:
        return p1.size() > p2.size();
    }
};
void printTheta(unordered_map<string,string> &theta)
{
    for (auto x : theta)
    cout << x.first << " " << x.second << endl;
}
void printS(sentence s1) //done
{
    sentence::iterator it;
    cout<<"Sentence ";
    string toprint="";
    for (it = s1.begin(); it != s1.end(); it++)
    {
        // print in ascending order as required.
        toprint+="v "+(*it).name + "(";
        for(int c=0;c<(*it).args.size();c++)
            toprint+=(*it).args[c]+ " ";
        toprint+=") ";
       
    }
        toprint=toprint.substr(1);
        cout<< toprint;
        cout<<endl;
}
void showpq(priority_queue<sentence, vector<sentence >, CompareLength> pq)
 {
     priority_queue<sentence, vector<sentence >, CompareLength> g = pq;
     while (!g.empty())
     {
         cout << '\t' ;
         sentence t=g.top();
         printS(t);
         g.pop();
     }
     cout << '\n';
 }
void printP(predicate p1)
{
    string toprint=p1.name+"(";
    for (int it =0;it<p1.args.size(); it++)
    {
        
        toprint+=p1.args[it]+ " ";
       
    }
      toprint+=")";
    cout<<toprint;
}
void printKB() //done
{
    sentence::iterator it;
    cout<<"\n \n KB is \n \n";
    for(int i=0;i<KB.size();i++)
    {
        cout<<"Sentence "<<i+1<<" ";
        string toprint="";
    for (it = KB[i].begin(); it != KB[i].end(); it++)
    {
        toprint+="v "+(*it).name + "(";
        for(int c=0;c<(*it).args.size();c++)
            toprint+=(*it).args[c]+ " ";
        toprint+=") ";
    }
        toprint=toprint.substr(1);
        cout<< toprint;
        cout<<endl;
    }
}
void printKB1(vector<sentence > &KB1) //done
{
    sentence::iterator it;
    cout<<"\n \n KB1 is \n \n";
    for(int i=0;i<KB1.size();i++)
    {
        cout<<"Sentence "<<i+1<<" ";
        string toprint="";
    for (it = KB1[i].begin(); it != KB1[i].end(); it++)
    {
        toprint+="v "+(*it).name + "(";
        for(int c=0;c<(*it).args.size();c++)
            toprint+=(*it).args[c]+ " ";
        toprint+=") ";
    }
        toprint=toprint.substr(1);
        cout<< toprint;
        cout<<endl;
    }
}
void printqueries() //done
{
    cout<<"\n \n Querylist is \n \n";
    for(int i=0;i<querylist.size();i++)
    {
        cout<<"Query "<<i+1<<" ";
        cout << querylist[i].name <<"(";
        string toprint;
        for (int j=0; j<querylist[i].args.size(); j++)
           {
               toprint+=","+querylist[i].args[j];
           }
         toprint+=")";
        toprint=toprint.substr(1);
        cout<<toprint;
        cout<<endl;
    }
}
predicate negate_predicate(predicate pred) //edited
{
    if(pred.is_negated==1)
    {
        pred.is_negated=0;
        pred.name=pred.name.substr(1);
    }
    else
    {
        pred.is_negated=1;
        pred.name= "~"+ pred.name;
    }
    return pred;
}
sentence negate_sentence(sentence s)
{
    for(int it=0;it<s.size();it++)
    {
    if(s[it].is_negated==1)
    {
        s[it].is_negated=0;
        s[it].name=s[it].name.substr(1);
    }
    else
    {
        s[it].is_negated=1;
        s[it].name= "~"+ s[it].name;
    }
    }
    return s;
}
predicate make_predicate(string predstr) //checked
{
    predicate pred;
    unsigned long pos,pos2;
    if(isspace(predstr[0]))
        predstr= predstr.substr(1);
    pos=predstr.find("(");
    pos2=predstr.find(")");
    if(predstr[0]=='~')
    {
        pred.is_negated=1;
        pred.name=predstr.substr(0,pos);
    }
    else
    {
        pred.is_negated=0;
        pred.name=predstr.substr(0,pos);
    }

    string p=predstr.substr(pos+1,pos2-pos-1); //arguments separated by commas
    stringstream check1(p);
    string intermediate;
    while(getline(check1, intermediate,','))
    {
        pred.args.push_back(intermediate);
      
    }
    return pred;
}
sentence standardise(sentence s)
{
    map<string, string> stdvar;
    sentence s1;
    std::vector<predicate >::iterator it = s.begin();
    predicate p;
    // Iterate till the end of set
    while (it != s.end())
    {
        p=(*it);
       
        for(int j=0;j<p.args.size();j++)
        {
            if(isvar(p.args[j])) // check if arg is variablle
            {
            map<string, string>::iterator it;
           
            it = stdvar.find(p.args[j]);
           
            if (it != stdvar.end()) // if element exists
            {
                // Access the Value from iterator
                p.args[j] = it->second;
                //cout << "key = " << it->first << " :: Value = " << p.args[j] << endl;
            }
            else
            {
        
            stdvar.insert({p.args[j],"x"+to_string(argcount)});
            p.args[j]="x"+to_string(argcount);
            argcount++;
            }
        }
        }
        s1.push_back(p);
       
        it++;
    }
    return s1;
}
void to_CNF_query(string inquery)
{
    predicate mypred=make_predicate(inquery);
  
    querylist.push_back(mypred); // push query predicate into querylist
}
void to_CNF(string inputsen,int index) //convert sentence to CNF and add to KB
{
    predicate mypred,temp;
    sentence s;
    std::size_t found = inputsen.find("=>");
    if(found!=std::string::npos)
    {
        string p=inputsen.substr(0,found); //premise substring
        string rem=inputsen.substr(found+2,inputsen.length()-found-1); //conclusion
        mypred=make_predicate(rem);//convert conclusion to predicate
        s.push_back(mypred); //insert conclusion predicate to the sentence set
        if(kbmap.find(mypred.name) == kbmap.end())
        {
            vector<int> sList;
            sList.push_back(index);
            kbmap[mypred.name] = sList;
        }
        else
        {
            vector<int> sList =kbmap[mypred.name];
            sList.push_back(index);
            kbmap[mypred.name] = sList;
        }
        stringstream check1(p);
        string intermediate;
        while(getline(check1, intermediate, '&')) // separating predicates
        {
            //cout<<intermediate<<"is predicate\n";
            mypred=make_predicate(intermediate);
            temp=negate_predicate(mypred);
            s.push_back(temp); // insert negated premise predicate to the sentence
            if(kbmap.find(temp.name) == kbmap.end())
            {
                vector<int> sList;
                sList.push_back(index);
                kbmap[temp.name] = sList;
            }
            else
            {
                vector<int> sList =kbmap[temp.name];
                sList.push_back(index);
                kbmap[temp.name] = sList;
            }
        }
    }
    else
    {
        mypred=make_predicate(inputsen); // make predicate a predicate sentence
        s.push_back(mypred); // insert conslusion predicate to the sentence
        if(kbmap.find(mypred.name) == kbmap.end())
        {
            vector<int> sList;
            sList.push_back(index);
            kbmap[mypred.name] = sList;
        }
        else
        {
            vector<int> sList =kbmap[mypred.name];
            sList.push_back(index);
            kbmap[mypred.name] = sList;
        }
    }
    sentence in=standardise(s);
    sort(in.begin(), in.end(), comparator);
    KB.push_back(in); //push sentence into the KB
}
int areEqual(predicate p1,predicate p2)
{
    if (p1.args.size() != p2.args.size()) //if size of arg lists are not equal
        return 0;
    for(int i=0;i<p1.args.size();i++)
    {
       
        if(p1.args[i].compare(p2.args[i]) != 0) //arguments are not same
            return 0;
      
    
    }
    return 1;
}
int areEqualS(predicate p1,predicate p2)
{
    if (p1.args.size() != p2.args.size()) //if size of arg lists are not equal
        return 0;
    int checker1=0,checker2=0;
    for(int i=0;i<p1.args.size();i++)
    {
        if(isvar(p1.args[i])) ///////////////// ADDED THIS SENTENCE TO CHECK; MAY NOT BE CORRECT
            checker1++;
        if(isvar(p2.args[i]))
            checker2++;
    
    
    }
    return 1;
}
int areNegatedPreds(predicate pred1, predicate pred2)
{
    if ((pred1.name.compare("~" + pred2.name))==0)
        return 1;
    else if ((pred2.name.compare("~" + pred1.name))==0)
        return 1;
    return false;
}
void addToKB(sentence news)
{
    KB.push_back(news);
    int newind= num_sen;
    num_sen++;
    sentence::iterator iter= news.begin();
    predicate mypred=(*iter);
    if(kbmap.find(mypred.name) == kbmap.end())
        {
            vector<int> sList;
            sList.push_back(newind);
            kbmap[mypred.name] = sList;
        }
    else
    {
            vector<int> sList =kbmap[mypred.name];
            sList.push_back(newind);
            kbmap[mypred.name] = sList;
    }
    
}
void addTotempKB(vector<sentence > &KB1,sentence news)
{
    int newind= (int) KB1.size();
    KB1.push_back(news);
    sentence::iterator iter= news.begin();
    predicate mypred=(*iter);
    if(kbmap.find(mypred.name) == kbmap.end())
        {
            vector<int> sList;
            sList.push_back(newind);
            kbmap[mypred.name] = sList;
        }
    else
    {
            vector<int> sList =kbmap[mypred.name];
            sList.push_back(newind);
            kbmap[mypred.name] = sList;
    }
    
}
//Substitutes argumentList with substitution list theta
vector<string> substitute(vector<string > &arglist, unordered_map<string, string> &theta)
{
    for (int i = 0; i < arglist.size(); i++) {
        //Check if argument is substitutable using theta
        while (theta.count(arglist[i]) > 0) // check this statement
            arglist[i] = theta[arglist[i]];
    }
    return arglist;
}

int isUnifiable(unordered_map<string,string> &theta,vector<string > &list1,vector<string > &list2) {
   // cout<<"in isunificable"<<endl;
    if (list1.size() != list2.size()) //if size of arg lists are not equal
        return 0;
    for (int i = 0; i < list1.size(); i++)
    {
        if (list1[i] != list2[i])
        {
            if (isvar(list1[i]))
            {
               // cout<<"list1[i] is " <<list1[i]<<endl;
               // cout<<"list2[i] is "<<list2[i]<<endl;
                theta[list1[i]] = list2[i];
                list1= substitute(list1,theta);
                list2= substitute(list2,theta);
            }
            else if (isvar(list2[i]))
            {
                //cout<<"list2[i] is " <<list2[i]<<endl;
               // cout<<"list1[i] is "<<list1[i]<<endl;
                theta[list2[i]] = list1[i];
                list1 = substitute(list1,theta);
                list2= substitute(list2,theta);
            }
            else // are different constants
                return 0;
        }
    }
   // cout<<"true"<<endl;
    return 1;
}
int check_tautology(sentence s)
{
    if(s.size()==0)
        return 0;
    for(int i=0;i<s.size()-1;i++)
    {
        predicate curr=negate_predicate(s[i]); //curr is the negation of current predicate
        for(int j=i+1;j<s.size();j++)
        {
            if(curr.name.compare(s[j].name)==0 && areEqual(curr,s[j]))
                return 1;
        }
    }
    return 0;
}
int EqualSentences(sentence s1,sentence s2)
{
    if(s1.size()!=s2.size())
        return 0;
    else
    {
        if(s1.size()==1 && s1[0].name.compare(s2[0].name)==0)
        {
            
        }
    }
    int counter=0;
    
    for(int i=0;i<s1.size();i++)
    {
        for(int j=0;j<s2.size();j++)
        {
            if(s1[i].name.compare(s2[j].name)==0 && areEqual(s1[i],s2[j]))
            {
                counter++;
            }
                                                
        }
    }
   
    if(counter== s1.size())
        return 1;
    else
        return 0;
}

int checkINList(vector<sentence > KB1,sentence check)
{
   // cout<<"\n in checklist \n";
   // printS(check);
    for(int i=0;i<KB1.size();i++)
    {
      
        if(EqualSentences(check, KB1[i]))
        {
           // cout <<"found redundant"<<endl;
            return 1;
        }
    }
    return 0;
}

 sentence removeDuplicate(sentence s) {
    //Removes duplicate predicates
    //Set of visited predicates
     if(s.size()==0)
         return s;
     set<int> remove;
     sentence s1;
    // cout<<"\n sentence was ";
    // printS(s);cout<<endl;
    //Vector of predicate indices to remove
    for (int i = 0; i < s.size()-1; i++)
    {
        for(int j=i+1;j<s.size();j++)
        {
           
          if (s[i].name.compare(s[j].name)==0 && areEqual(s[i],s[j]))
          {
            // cout<<"\n removing "<<j<<endl;
              remove.insert(j);
          }
         }
    }
    //Remove marked indices from sentence
    if(remove.size()==0)
    {
        return s;
    }
    for (int i = 0; i < s.size(); i++)
    {
        if(remove.find(i)== remove.end()) // if current index predicate is marked for removal, do not include it
        {
         
            s1.push_back(s[i]);
        }
    }
    // cout<<"now changed to after removing ";
    // printS(s1);cout<<endl;
    return s1;
}
//priority_queue<Person, vector<Person>, CompareHeight> Q;
int resolution(vector<sentence > KB1,sentence query)
{
   // vector<sentence > newKB = KB1;
    KB1.push_back(query); //KB1 = KB ^ ~alpha
   
    priority_queue<sentence, vector<sentence >, CompareLength> Frontier;

    Frontier.push(query);
    while (!Frontier.empty())
    {
        time(&check);
        double time_taken = double(check - start);
            if(time_taken > maxTime)
            {
                cout<<"time out";
                return 0;
            }
   sentence currentQuery = Frontier.top(); // query sentence
      //  sentence currentQuery = Frontier.front();
    //sentence currentQuery=query;
         Frontier.pop();
        sentence::iterator outer;
        int count=-1;
    //ierate through current query sentence
    for (outer = currentQuery.begin(); outer != currentQuery.end(); outer++)
    {
        time(&check);
        double time_taken = double(check - start);
            if(time_taken > maxTime)
            {
                cout<<"time out";
                printKB1(KB1);
                return 0;
            }
    count++;
    //create a resolver predicate by negating the current predicate
    predicate resolver= (*outer);
    predicate key = negate_predicate(resolver);
    //Get resolvableSentences for each predicate in the currentSentence
    //vector<int> senIndices = kbmap[key.name]; //sentences which contain the negated resolver
    for(int i=0;i<KB1.size();i++) // for each matching sentence
    {
        time(&check);
        double time_taken = double(check - start);
            if(time_taken > maxTime)
            {
                cout<<"time out";
                return 0;
            }
        unordered_map<string,string> theta;
      //  int ind=senIndices[i];
        int ind=i;
        sentence current=KB1[ind]; // curent comparator sentence
    
        predicate p;
        // Iterate till the end of comparator sentence
        //  while (inner != current.end())
        
        for(int inner=0;inner<current.size();inner++)
        {
           p=current[inner]; // a predicate in comparator sentence
          
            
           if(key.name.compare(p.name)==0) // if the current sen predicate is equal to the key
           {
            
               vector<string > a= resolver.args; //arg list of the current query pred
               vector<string > b= p.args; //arg list of the current sentence pred
               if(isUnifiable(theta, a, b))
               {
                   //substitute all variables in the sentences if unificable
                  // cout<<"here"<<endl;
                 //  printTheta(theta);
                   sentence s1=currentQuery;
                   sentence s2=current;
                   //vector<predicate >::iterator k = s1.begin();
                   sentence newsen1={};
                   // Iterate till the end of comparator sentence
                    for(int k=0;k<s1.size();k++)
                   {
                     
                       s1[k].args=substitute(s1[k].args, theta);
                    
                      newsen1=s1;
                     
                   }
                
                   sentence newsen2={}; //   while (j != s1.end())
                   for(int j=0;j<s2.size();j++)
                   {
                      
                       s2[j].args=substitute(s2[j].args, theta);
                       //if(j==inner)
                        //  continue;
                   //    newsen2.push_back(s2[j]);
                       newsen2=s2;
                      // j++;
                   }
                   newsen1.erase(newsen1.begin() + count);
                   newsen2.erase(newsen2.begin() + inner);
                   sentence resolventSen;
                  // merge(newsen1.begin(), newsen1.end(),newsen2.begin(), newsen2.end(),inserter(resolventSen,resolventSen.begin()));
                   resolventSen.insert(resolventSen.end(), newsen1.begin(), newsen1.end());
                   resolventSen.insert(resolventSen.end(), newsen2.begin(), newsen2.end());
                  // cout<<endl;
                   resolventSen= removeDuplicate(resolventSen);
                  if(check_tautology(resolventSen))
                       continue;
                  // cout<<endl<<endl;
                   if (resolventSen.size()==0)
                   {
                                       // cout<<"is empty\n";
                                     //   sentence neg= negate_sentence(query);
                                       // printS(neg);
                                      //  addToKB(neg);
                       time(&check);
                       double time_taken = double(check - start);
                       cout << "Time taken by current query is : " << fixed << time_taken << setprecision(5);
                       cout << " sec " << endl;
                       printKB1(KB1);
                                        return 1;
                   }
               
                   if(checkINList(KB1, resolventSen)==0)
                   {
                     
                       resolventSen=standardise(resolventSen);
                       sort(resolventSen.begin(), resolventSen.end(), comparator);
                    
                       KB1.push_back(resolventSen);
                    
                        Frontier.push(resolventSen);
                   //    repeatChecker.insert(resolventSen);
                   }
               
               }//endif
           }//endif
          //  inner++;
           } //endwhile
        }//endfor
    } //endfor
    }//endwhile
printKB1(KB1);
return 0;
}

int main() {
    fstream file;
    string line;
    file.open("input26.txt",ios::in);
    
    if(!file)
    {
        cout<<"Error in opening file!!!"<<endl;
        return 0;
    }
    getline(file,line);
    num_queries = stoi(line);
  //  cout<< num_queries<<"\n";
    for(int i=0;i<num_queries;i++)
    {
        getline(file,line);
       // cout<<line<<"\n";
        to_CNF_query(line);
        //querylist.push_back(pred);
    }
    getline(file,line);
    num_sen = stoi(line);
 //   cout<< num_sen<<"\n";
    for(int i=0;i<num_sen;i++)
    {
        getline(file,line);
    
        to_CNF(line,i);
    }
    file.close();
 
    string output;
    for(int i=0;i<num_queries;i++)
   {
       map<int, int> sentenceUsed;
       int ans;
       sentence make;
       make.push_back(negate_predicate(querylist[i])); //sending negated query
       
       size=num_sen;
      
       time(&start);
     
       ans=resolution(KB, make);
       if(ans==1)
       {
         
           output=output+ "TRUE \n";
           sentence toadd;
           toadd.push_back(querylist[i]);
           addToKB(toadd);
           num_sen++;
       }
       else
       {
          
          output=output+ "FALSE \n";
       }
       
   }
    cout<<endl<<endl<<"answers"<<endl;
    fstream outfile;
    cout<<output;
    outfile.open("output.txt",fstream::out);
    outfile <<output;
    outfile.close();
  
    return 0;
}


