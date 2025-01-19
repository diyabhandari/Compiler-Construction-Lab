#include <iostream>
#include <string>
using namespace std;

//there are 2 cases to deal with, the direct one and the indirect one where we can derive the parent non-t to be on the left-most side 
int main()
{
    int choice=1;
    while(choice){
      int n;
      string input="", op1="", op2="", temp; //op1 and op2 are the rewritten productions
      //op1 : A -> BetaA'
      //op2 : A' -> aA' | # 

      string c;
      cout << "Enter the Parent Non-Terminal: " << endl;
      cin >> c;
      input+=c;
      op2 += input + "\'->"; //A'->
      input += "->";
      op1 += input; //A->
      cout << "Enter the number of productions: " << endl;
      cin >> n;
      for (int i = 0; i < n; i++)
      {
          cout << "Enter the production " << i + 1 << ":" << endl;
          cin >> temp;
          input += temp; //A->Aa | Beta
          if (i != n - 1)
          {
              input += "|";
          }
          if(i==n-1){
            input+="#"; //use this as end marker ?
          }
      }
      cout << "Production Rule: " << input << endl;

      int onSameProduction = 0;
      for (int i = 3; i < input.size(); i++) // 0 1 2 is A->
      {
        if(onSameProduction==0 && input[i]==input[0]){
          cout<<"\nLeft recursion detected";
          onSameProduction=1; //we dont want it printing left recursion found for something like B+A
          int j=i+1; //one position after position of left recursion
          while(input[j]!='|'){ //this loop is to add a to op2, nw op2 = A'->a
            op2+=input[j];
            j++;
          }
          op2+= c+"\'|#"; //now op2 = A'->aA'|#
          int k=j+1;
          while(input[k]!='#'){ //because of this, this code only solves for 2 productions per parent non-t
            op1+=input[k]; //to get op1 = A->Beta
            k++;
          }
          op1+=c+'\''; //op1 = A->BetaA'
          cout<<"\nAfter removal of left recursion : ";
          cout << op1 << endl;
          cout << op2 << endl;
        }
      
        if(input[i]=='|'){
          onSameProduction=0; //means we can now check for left recursion again
        }      
      }
      cout << "\nPress 1 to test for another parent non-terminal and its productions : ";
      cin>>choice;
    }
    
    return 0;
}