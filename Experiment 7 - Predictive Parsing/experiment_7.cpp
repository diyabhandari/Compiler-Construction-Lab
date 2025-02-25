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
string id = "id";
//for ease of parsing, Tprime is U, Eprime is G
vector<vector<string>> parsing_table = {
  {"blank",id,"*","+","(",")","$"}, //word blank denotes first row, of terminals
  {"E","TG","","","TG","",""},
  {"G","","","+TG","","0","0"}, //0 is epsilon
  {"T","FU","","","FU","",""},
  {"U","","*FU","0","","0","0"},
  {"F",id,"","","(E)","",""}
};
int isTerminal(string inputSymbol){
    if(inputSymbol == "*" || inputSymbol == "+" || inputSymbol == "$" || inputSymbol == "(" || inputSymbol == ")"){
        return 1;
    }
    else return 0;
}
int isNonTerminal(string inputSymbol){
    if(inputSymbol == "E" || inputSymbol == "G" || inputSymbol == "T" || inputSymbol == "U" || inputSymbol == "F"){
        return 1;
    }
    else return 0;
}
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
  int i = 0; //iterator for input string
  while(inputStack.size()>=1){ //it'll always be atleast 1, as $ will be on stack till end
    
   if(input[i]=='i' && input[i+1] == 'd'){ //id is there in input string
    if(inputStack.top() == id){
        inputStack.pop();
        i+=2; //id is 2 characters, advance input
    }
    else if(isNonTerminal(inputStack.top())){
        //check table
        //if "", parsing failed (compare with id global var)
        //if not "", pop from stack and then push reverse of stored production
    }
   }
   else{
    string inputSymbol = input.substr(i,1); //copy 1 char of input, ie the one at i, using this instead of input[i] as that returns a char and our functions are for string
    if(isTerminal(inputStack.top()) && isTerminal(inputSymbol)){
        if(inputStack.top() == inputSymbol){
            inputStack.pop();
            i++; //advance input
        }
        else{
            cout<<"\nParsing failed";
        }
    }
    else if(isNonTerminal(inputStack.top()) && isTerminal(inputSymbol)){
        //check table
        //if "", parsing failed 
        //if not "", pop from stack and then push reverse of stored production       
    }
    if(inputStack.top() == "$" && input[i] == '$'){
        cout<<"\nParsing successful";
    }
   }
  }
  return 0;
}