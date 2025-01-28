#include<iostream>
#include <string>
using namespace std;
class DFA{
  private: 
    int dfa=0;
    //each state has its own function to define the transition to next state on input
    //depending on char received, we move to corresponding state of DFA
    void start(char c){ 
      switch(c){
        case 'a':
          dfa = 2;
          break;
        case 'b':
          dfa = 1;
          break;
        default: //for anything other than a/b
          dfa = -1;
          break;

      }
    }
    void state1(char c){ //this is also the final state
      switch(c){
        case 'a':
          dfa = 3;
          break;
        case 'b':
          dfa = 0;
          break;
        default:
          dfa = -1;
          break;
      }
    }
    void state2(char c){
      switch(c){
        case 'a':
          dfa = 0;
          break;
        case 'b':
          dfa = 3;
          break;
        default:
          dfa = -1;
          break;
      }
    }
    void state3(char c){
      switch(c){
        case 'a':
          dfa = 1;
          break;
        case 'b':
          dfa = 2;
          break;
        default:
          dfa = -1;
          break;
      }
    }
    int isAccepted(string input){
      int len = input.size();
      for(int i=0;i<len;i++){
        switch(dfa){
          case 0:
            start(input.at(i));
            break;
          case 1:
            state1(input.at(i));
            break;
          case 2:
            state2(input.at(i));
            break;
          case 3:
            state3(input.at(i));
            break;
          default:
            cout<<"state does not exist";
            break;
        }       
      }
      if(dfa==1)
        return 1;
      else 
        return 0;
    }
  public:
   void checkString(string input){
    int result = isAccepted(input);
    if(result==1)
      cout<<"\nACCEPTED : string has even number of a's and odd number of b's";
    else
      cout<<"\nNOT ACCEPTED : string does not have even number of a's and odd number of b's";
   }
};
int main(){
  int ch=1;
  while(ch==1){
    string inputString;
    cout<<"Enter a string: ";
    cin>>inputString;
    DFA dfa;
    dfa.checkString(inputString);
    cout<<"\nPress 1 to continue ";
    cin>>ch;
  }
  return 0;
}
