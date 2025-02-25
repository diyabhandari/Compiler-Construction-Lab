//parse the user entered string for a grammar
//create table directly on the basis of your knowledge and parse the entered string acc to it 
#include <iostream>
#include <vector>
#include <string>
#include <stack>
using namespace std;
//create a 2D vector to store predictive parsing table. the first row will store all the terminals and the first column will store all the Non-t. that is, each row except the first starts with a Non-t. let the first row start with the string "blank".
//manually enter the productions as strings of the form A -> aB
//then, create a stack, push $E to it (E is the start symbol), append $ to the end of input string, parse the string by comparing top of stack and input symbol, look up the production in table place [top of stack, input symbol] and push that production in reverse order to the stack, replacing the top of stack, if [top of stack, input symbol] is of the form [Non-t,t]
//if tos and input symbol are equal, pop tos and move input by 1 char
//if no entry found in table, stop and print parsing failed
//if [top of stack, input symbol] is $,$ , print string accepted
//try -> instead of storing as Nt -> prodn, store just the prdn and then the logic will be, replace TOS = row[0] with reverse of prdn at [TOS(NT in row beginning),input symbol]

//vector of vectors makes a table
//ive kept blank as "", on getting blank string for production we will print error
vector<vector<string>> parsing_table = {
  {"blank","id","*","+","(",")","$"}, //word blank denotes first row, of terminals
  {"E","TEprime","","","TEprime","",""},
  {"Eprime","","","+TEprime","","0","0"}, //0 is epsilon
  {"T","FTprime","","","FTprime","",""},
  {"Tprime","","*FTprime","0","","0","0"},
  {"F","id","","","(E)","",""}
};

int main(){
  string input = "";
  stack<string> inputStack;
  //push $ and the start symbol to stack
  inputStack.push("$");
  inputStack.push("E");
  cout<<"The grammar is : \n";
  cout<<"E->E+T/T \nT->T*F/F \nF->(E)/id\n";
  cout<<"Enter a string to check if it belongs to this grammar : ";
  cin>>input;
  while(inputStack.size()>=1){ //it'll always be atleast 1, as $ will be on stack till end
    for(int i = 0; i < parsing_table.size(); i++){ //go over each vector in the list of vectors
      //if input symbol and top of stack are the same non-terminal, pop stack and advance input, else parsing failed
      //if top of stack is NT and input symbol is T, check entry in the table M(A,a), whichever production you get, replace the TOS with the reverse of that production and continue, if none parsing failed 
      //$ $ success

    }

  }
}