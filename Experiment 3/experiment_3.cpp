//should be for all cases of left recursion
#include <iostream>
#include <string>
#include <vector>
using namespace std;
class LeftRecursion{
  //method that accepts the productions would be public, for each entered production 
  //we'll then call the function to check if its left recursive, and if it is,
  //we'll call the function to print the correct productions

  //enter production rules of grammar in the form [NonT,Production1,Production2..]
  //compare first char of p1,p2.. with NonT
  //if same, apply removal of left recursion and create a new array
  //iterate through array to print in the form of A->B/C etc
  //user can check and fix one production at a time
  public:
    void removeLeftRecursion(vector<string> production){
      vector<string> fixedProduction;
      string beta ="";
      string alpha ="";
      int i;
      char NT = production[0][0]; //[] -> string [][]-> char
      for(i=1;i<production.size();i++){
        if(production[i][0]==NT){
          cout<<"\nThe production "<<NT<<"->"<<production[i]<<" is left recursive.";
          //fix later, hardcoded
          beta = production[i+1];
          alpha = production[i].substr(1); //drops first char, which is NT
          break;
        }
      }
      //change the production where its left recursive in original production,
      //add a new production for NT'
      production[i]= beta+NT+"'";
      //remove string at production i+1
      cout<<"\nAfter removing left recursion from the given production : ";
      
    }
    void enterProduction(){
      vector<string> production;
      string input="";
      cout<<"\nInputting the production rules for a single parent nonterminal at a time";
      int ch=1,num;
      while(ch==1){
        cout<<"\nEnter parent nonterminal : ";
        cin>>input;
        production.push_back(input);
        cout<<"\nEnter number of productions : ";
        cin>>num;
        for(int i=0;i<num;i++){
          cout<<"\nEnter the production : ";
          cin>>input;
          production.push_back(input);
        }
        removeLeftRecursion(production);
        cout<<"\nPress 1 to enter another production rule : ";
      }
    }

};