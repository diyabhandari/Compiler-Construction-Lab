#include <iostream>
#include <vector>
#include <string>
#include <stack>
using namespace std;

//vector of vectors makes a table
//ive kept blank as "", on getting blank string for production we will print error
string id = "id";
//for ease of parsing, Tprime is U, Eprime is G
vector<vector<string>> parsing_table = {
    {"b",id,"*","+","(",")","$"}, //word blank denotes first row, of terminals
    {"E","TG","","","TG","",""},      //E -> TG 
    {"G","","","+TG","","0","0"},     //G -> +TG | ε
    {"T","FU","","","FU","",""},      //T -> FU
    {"U","","*FU","0","","0","0"},    //U -> *FU | ε
    {"F",id,"","","(E)","",""}        //F -> id | (E)
};
int isTerminal(string inputSymbol){
    if(inputSymbol == "*" || inputSymbol == "+" || inputSymbol == "$" || inputSymbol == "(" || inputSymbol == ")" || inputSymbol == "id"){
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

int getColumnIndex(string symbol) {
    if(symbol == "id") return 1;
    if(symbol == "*") return 2;
    if(symbol == "+") return 3;
    if(symbol == "(") return 4;
    if(symbol == ")") return 5;
    if(symbol == "$") return 6;
    return -1;
}

int getRowIndex(string symbol) {
    if(symbol == "E") return 1;
    if(symbol == "G") return 2;
    if(symbol == "T") return 3;
    if(symbol == "U") return 4;
    if(symbol == "F") return 5;
    return -1;
}

void pushProductionReverse(string production, stack<string>& inputStack) {
    if(production == "0") return; // epsilon production
    //id is being kept as 1 symbol "id"
    if(production == "id") {
        inputStack.push("id");
        return;
    }
    for(int j = production.length() - 1; j >= 0; j--) {
        string symbol = production.substr(j, 1);
        inputStack.push(symbol);
    }
}
void print_parsing_table(vector<vector<string>> parsing_table){
    for(int i = 0; i < parsing_table.size(); i++){
        for(int j = 0; j < parsing_table[i].size(); j++){
            if(i == 0){ //adding more space between columns of first row
                cout<<parsing_table[i][j]<<"       ";
            }
            else{
                cout<<parsing_table[i][j]<<"        ";
            }
            
        }
        cout<<"\n";
    }
}

int main(){
    print_parsing_table(parsing_table);
    string input = "";
    stack<string> inputStack;
    //push $ and the start symbol to stack
    inputStack.push("$");
    inputStack.push("E");
    cout<<"The grammar is : \n";
    cout<<"E->E+T/T \nT->T*F/F \nF->(E)/id\n";
    cout<<"Enter a string to check if it belongs to this grammar : ";
    cin>>input;
    input += "$"; 
    int i = 0; //iterator for input string
    
    while(!inputStack.empty()) {
        string top = inputStack.top();
        string currentInput = (i+1 < input.length() && input[i] == 'i' && input[i+1] == 'd') ? "id" : input.substr(i, 1);
        
        //cout << "\nStack top: " << top << ", Input at " << i << ": " << currentInput; debugging
        if(top == "$" && currentInput == "$") {
            cout << "\nParsing successful";
            return 0;
        }
        else if(top == currentInput) { //TOS matches input symbol, pop
            inputStack.pop();
            i += (currentInput == "id") ? 2 : 1;
        }
        else if(isNonTerminal(top)) {
            int row = getRowIndex(top);
            int col = getColumnIndex(currentInput);
            if(col == -1) { //input does not have a column in the table
                return 0;
            }
            string production = parsing_table[row][col]; 
            
            if(production == "") { //parsing failed
                return 0;
            }
            inputStack.pop(); //production found in table for M(A,a)
            pushProductionReverse(production, inputStack);
        }
        
        else {
            cout << "\nParsing failed - mismatch";
            return 0;
        }
    }
    
    cout << "\nParsing failed - stack emptied without reaching $";
    return 0;
}