#include<iostream>
#include <string>
using namespace std;
class DFA{
  private: 
    int dfa=0; //0=start
    void start(char c){ 
      switch(c){
        case '0':
          dfa = 0;
          break;
        case '1':
          dfa = 1;
          break;
        default: //for anything other than 0/1
          dfa = -1;
          break;

      }
    }
    void state1(char c){ //this is also the final state
      switch(c){
        case '0':
          dfa = 2;
          break;
        case '1':
          dfa = 3;
          break;
        default:
          dfa = -1;
          break;
      }
    }
    void state2(char c){
      switch(c){
        case '0':
          dfa = 4;
          break;
        case '1':
          dfa = 0;
          break;
        default:
          dfa = -1;
          break;
      }
    }
    void state3(char c){
      switch(c){
        case '0':
          dfa = 1;
          break;
        case '1':
          dfa = 2;
          break;
        default:
          dfa = -1;
          break;
      }
    }
    void state4(char c){
      switch(c){
        case '0':
          dfa = 3;
          break;
        case '1':
          dfa = 4;
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
          case 4:
            state4(input.at(i));
            break;
          default:
            //cout<<"state does not exist";
            break;
        }       
      }
      if(dfa==0)
        return 1;
      else 
        return 0;
    }
  public:
   void checkString(string input){
    int result = isAccepted(input);
    if(result==1)
      cout<<"\nACCEPTED : This number is divisible by 5";
    else
      cout<<"\nNOT ACCEPTED : This number is not divisible by 5";
   }
};
int main(){
  int ch=1;
  while(ch==1){
    string inputString;
    cout<<"Enter a binary number: ";
    cin>>inputString;
    DFA dfa;
    dfa.checkString(inputString);
    cout<<"\nPress 1 to continue ";
    cin>>ch;
    }
  
  return 0;
}
