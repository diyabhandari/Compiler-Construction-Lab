//we used 0 as epsilon 

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

class Production {
public:
    string lhs;
    vector<string> rhs; //cuz Non-t can have many RHS productions
};

vector<Production> productions; //all input productions will be stored here
map<string, set<char>> firstSet; //we use sets to represent the elements in first and follow because sets dont allow duplicates
map<string, set<char>> followSet;

bool isNonTerminal(char symbol) { //separated this for clearing up the code
    return isupper(symbol);
}

void computeFirst(string symbol) {
    if (firstSet.find(symbol) != firstSet.end()) { //find is a map method thats used to check whether a key is present 
        return; //if found, we already computed for that symbol or Non-t/t
    }

    set<char> first;

    for (auto& prod : productions) { //going through each production in list one by one
        if (prod.lhs == symbol) {
            for (auto& rhs : prod.rhs) { //go through each production for a Non-t
                int i = 0;
                while (i < rhs.length()) {
                    char currentSymbol = rhs[i]; //go through production symbol by symbol

                    if (currentSymbol == '0') { // Epsilon
                        first.insert('0');
                        break; //cuz epsilon cant derive anything further
                    } else if (!isNonTerminal(currentSymbol)) { //case of Terminal
                        first.insert(currentSymbol);
                        break; //cant go further after t obtained
                    } else { //case of Non-t
                        //we have to go through the productions of this Non-t, recursively
                        computeFirst(string(1, currentSymbol)); //currentSymbol conv to string, 1-> write char only once 
                        set<char> currentFirst = firstSet[string(1, currentSymbol)]; //first of current Non-t that we calculated recursivelyS

                        // Add all symbols from currentFirst except epsilon, cuz for A->BC, first(a) = first(b) - epsilon
                        for (char ch : currentFirst) {
                            if (ch != '0') {
                                first.insert(ch);
                            }
                        }

                        //if epsilon 
                        if (currentFirst.find('0') == currentFirst.end()) {
                            break;
                        }
                    }
                    i++; //next symbol in rhs cuz while loop not broken
                }

                //we reached one ahead of the last symbol of rhs, which means entire rhs -> epsilon, for which we have to add epsilon to first
                if (i == rhs.length()) {
                    first.insert('0');
                }
            }
        }
    }

    firstSet[symbol] = first; //when if cond for symbols break the loop, this is executed
}

void computeFollow(string symbol) {
    if (followSet.find(symbol) != followSet.end()) {
        return; 
    }

    set<char> follow;

    //if start symbol, add $ to follow
    if (symbol == productions[0].lhs) {
        follow.insert('$');
    }

    for (auto& prod : productions) { //each non-t
        for (auto& rhs : prod.rhs) { //each production of non-t
            int pos = rhs.find(symbol); //return the position of given symbol
            if (pos != -1) { // Check if symbol is found in rhs
                //in A->aBC, follow of B is first of C, so we add 1 to pos
                int nextPos = pos + 1;
                while (nextPos < rhs.length()) {
                    char nextSymbol = rhs[nextPos]; //extract C

                    if (!isNonTerminal(nextSymbol)) {
                        follow.insert(nextSymbol); //case of terminal
                        break;
                    } else { //case of non-t
                        computeFirst(string(1, nextSymbol)); //first of C ( A->aBC)
                        set<char> nextFirst = firstSet[string(1, nextSymbol)]; //we had already calc first

                        //adding all symbols from first to follow, leaving epsilon, epsilon is never added to follow
                        for (char ch : nextFirst) {
                            if (ch != '0') {
                                follow.insert(ch);
                            }
                        }

                        //stop if C doesnt resolve to epsilon 
                        if (nextFirst.find('0') == nextFirst.end()) {
                            break;
                        }
                    }
                    nextPos++; //will be executed if C does resolve to epsilon
                }

                //in A -> aBC, if in finding follow(B) , C-> epsilon, copy follow(A) to follow(B)
                if (nextPos == rhs.length()) { //rhs all null
                    if (prod.lhs != symbol) { //avoid calculating follow for same symbol, just in case production is like A->aA
                    //prod.lhs refers to the lhs of the production with the symbol we were finding follow for 
                        computeFollow(prod.lhs);
                        set<char> lhsFollow = followSet[prod.lhs];
                        follow.insert(lhsFollow.begin(), lhsFollow.end()); //store follow(a) in follow(b)
                    }
                }
            }
        }
    }
    followSet[symbol] = follow;
}

int main() {
    int num_of_rhs, num_of_prod;
    string parent, rhs;

    //input the start symbol and its productions
    cout << "\nEnter start symbol: ";
    cin >> parent;

    Production start;
    start.lhs = parent;
    cout << "\nEnter how many RHS productions are there for this parent non-terminal: ";
    cin >> num_of_rhs;
    for (int i = 0; i < num_of_rhs; i++) {
        cout << "\nEnter production: ";
        cin >> rhs;
        start.rhs.push_back(rhs);
    }
    productions.push_back(start);

    //input rest of the productions
    cout << "\nEnter number of productions to add: ";
    cin >> num_of_prod;
    for (int i = 0; i < num_of_prod; i++) {
        Production prod;
        cout << "\nEnter the parent non-terminal: ";
        cin >> prod.lhs;
        cout << "\nEnter the number of RHS productions for this non-terminal: ";
        cin >> num_of_rhs;
        for (int j = 0; j < num_of_rhs; j++) {
            cout << "\nEnter production: ";
            cin >> rhs;
            prod.rhs.push_back(rhs);
        }
        productions.push_back(prod);
    }

    //calc first for all Non-t
    for (auto& prod : productions) {
        computeFirst(prod.lhs);
    }

    //follow
    for (auto& prod : productions) {
        computeFollow(prod.lhs);
    }

    //display first and follow sets
    cout << "\nFIRST sets:\n";
    for (auto& entry : firstSet) {
        cout << "FIRST(" << entry.first << ") = { ";
        for (auto& symbol : entry.second) {
            cout << symbol << " ";
        }
        cout << "}\n";
    }

    cout << "\nFOLLOW sets:\n";
    for (auto& entry : followSet) {
        cout << "FOLLOW(" << entry.first << ") = { ";
        for (auto& symbol : entry.second) {
            cout << symbol << " ";
        }
        cout << "}\n";
    }

    return 0;
}