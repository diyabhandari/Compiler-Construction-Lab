#include <iostream>
using namespace std;

void T();
void Eprime();
void Tprime();
void F();

char* input; //input points to a character array, by default it points to first character

//we write the functions as per the productions, we call the function for the NT and compare with input for a terminal
void E() { 
    T();
    Eprime();
}

void Eprime() {
    if (*input == '+') { //checking the character that input currently points to
        input++; //moving the input to the next character
        T();
        Eprime();
    }
}

void T() {
    F();
    Tprime();
}

void Tprime() {
    if (*input == '*') {
        input++; 
        F();
        Tprime();
    }
}

void F() {
    if (*input == 'i' && *(input+1) == 'd') { 
        input += 2;
    }
    else if (*input == '(') {
        input++;
        E();
    }
    else if (*input == ')') {
            input++;
    }
}

int main() {
    char* test_inputs[] = {
        "id+id*id$",
        "((id+id)*id$",
        "id$"
    };

    for (int i = 0; i < 3; i++) {
        input = test_inputs[i];
        E();
        
        if (*input == '$') {
            cout<<"\nParsing succesful for : "<< test_inputs[i];
        } else {
            cout<<"\nParsing failed for : "<< test_inputs[i];
        }
    }

    return 0;
}