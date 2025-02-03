//for this, we go over each NT's prodns and create groups of prodns with similar prefixes. the groups with just 1 rhs are added as is, but for the groups with more than 1 rhs, we perform left factoring, where we replace the rhs's with that common prefix with just the common prefix + NT' , and we create a new prodn NT' -> unique parts of the common prefix rhs

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

class Production {
public:
    string lhs;
    vector<string> rhs;
};

vector<Production> productions;

void removeLeftFactoring() {
    vector<Production> new_productions; //we'll collect all the new productions formed due to left factoring here

    for (auto &prod : productions) { //over all productions
        vector<string> rhs_list = prod.rhs; //storing all rhs productions in a separate list
        sort(rhs_list.begin(), rhs_list.end()); //sorting so that similar productions appear together

        vector<vector<string>> groups; //we'll create groups of rhs {rhs1,rhs2..} that share a common prefix
        vector<string> current_group; //this represents the group we make in each iteration and later add to groups

        if (!rhs_list.empty()) {
            current_group.push_back(rhs_list[0]); //we'll start with first rhs
            string current_prefix = rhs_list[0];

            //going over remaining rhs prodns
            for (int j = 1; j < rhs_list.size(); ++j) { //< static_cast<int>(v.size()) use this if this line causes any issues
                string s = rhs_list[j];
                int len = 0;
                while (len < (current_prefix.size()) && 
                       len < (s.size()) && 
                       current_prefix[len] == s[len]) {
                    len++; //calculate how similar RHS is to RHS0
                }
                if (len > 0) {
                    current_group.push_back(s); //add to group 
                    current_prefix = current_prefix.substr(0, len); //update current prefix as per how many letters were common in the rhs's compared
                } else {
                    groups.push_back(current_group); //no more matches to be expected as its sorted, add the current group tp groups finally
                    current_group.clear();
                    current_group.push_back(s); //the next rhs to take 
                    current_prefix = s;
                }
            }
            groups.push_back(current_group);
        }

        Production new_prod;
        new_prod.lhs = prod.lhs; //the Non-T
        new_prod.rhs.clear();

        for (auto &group : groups) { //going over each group
            if (group.size() == 1) {
                new_prod.rhs.push_back(group[0]); //this means that rhs prod was unique, so we directly add it to the new production rule
            } 
            else { //common prefix found in rhs prodns
                string common_prefix = group[0]; //took out the first prdn in that group
                for (int k = 1; k < (group.size()); ++k) { //going over rhs in group
                    int len = 0;
                    while (len < (common_prefix.size()) && 
                           len < (group[k].size()) && 
                           common_prefix[len] == group[k][len]) {
                        len++; //calculate number of common elements in the RHS's in the group
                    }
                    common_prefix = common_prefix.substr(0, len); //finding the common prefix in that group
                }

                if (common_prefix.empty()) {
                    for (auto &s : group) {
                        new_prod.rhs.push_back(s); //nothing common, directly push all rhs from group to new prod
                    }
                } 
                else {
                    string new_non_terminal = prod.lhs + "'"; //A ko A'
                    bool exists = false;
                    for (auto &np : new_productions) {
                        if (np.lhs == new_non_terminal) {
                            exists = true;
                            break;
                        }
                    }
                    if (!exists) {
                        Production np; //the A' -> .. prodn
                        np.lhs = new_non_terminal;
                        for (auto &s : group) { //going through all rhs in group
                            string suffix = s.substr(common_prefix.size()); //start from after length of common prefix and go till end, thats the unique suffix
                            if (suffix.empty()) {
                                np.rhs.push_back("0"); //epsilon as 0
                            } else {
                                np.rhs.push_back(suffix); //push unique part into new production
                            }
                        }
                        new_productions.push_back(np); //store in collection of all new prodns formed
                    }

                    new_prod.rhs.push_back(common_prefix + new_non_terminal); //the alteration to og prodn, S - > iEtS+S' = iEtSS'
                }
            }
        }

        prod.rhs = new_prod.rhs; //update new rhs after left factoring
    }

    for (auto &np : new_productions) {
        productions.push_back(np); //add all new productions to list of all prodns
    }
}

int main() {
    int num_of_rhs, num_of_prod;
    string parent, rhs;

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

    removeLeftFactoring();

    cout << "\nProductions after left factoring:\n";
    for (auto &prod : productions) {
        cout << prod.lhs << " -> ";
        for (int i = 0; i < (prod.rhs.size()); ++i) {
            if (i > 0) cout << " / ";
            cout << prod.rhs[i];
        }
        cout << endl;
    }

    return 0;
}