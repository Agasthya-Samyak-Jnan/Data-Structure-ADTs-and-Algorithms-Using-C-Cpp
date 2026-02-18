#include<bits/stdc++.h>

using namespace std;

class TopDownParser {

private:
    // First Set, Follow Set, Set of Non-Terminals, Set of Terminals, Start Symbol and Parse Table.
    unordered_map<char,unordered_set<char>> first;
    unordered_map<char,unordered_set<char>> follow;
    unordered_map<char,unordered_map<char,pair<char,string>>> M;
    unordered_map<char,vector<string>> G;
    unordered_set<char> Non_Terminals;
    unordered_set<char> Terminals;
    char start_symbol, EPSILON = 'e', RIGHT_END_MARKER = '$';

    // Checks if a symbol is Terminal or NOT.
    bool isTerminal (char symbol) {
        return symbol < 'A' || symbol > 'Z';
    }

    // FIRST - Grammar Edition
    unordered_set<char> FIRST (char A, unordered_map<char,vector<string>>& productions) {

        // If 'a' is a Terminal , FIRST(a) = a itself.
        if (isTerminal(A)) { return {A}; }

        // EPSILON is reserved for Epsilon Symbol. Cannot use EPSILON elsewhere.
        if (A == EPSILON) { return {EPSILON}; }

        // if FIRST(A) was computed before
        if (!first[A].empty()) { return first[A]; }

        unordered_set<char> ans;
        bool found_epsilon = false;

        // Check for every production of this Non-Terminal.
        for (string& production : productions[A]) {

            // Check for every symbol in the Production.
            int i = 0;
            for (char symbol : production) {

                // If symbol is a Terminal
                if (isTerminal(symbol)) { ans.insert(symbol); }

                // If symbol is a Non-Terminal
                else {
                    unordered_set<char> first = FIRST(symbol,productions);
                    for (char sym : first) { 
                        if (sym == EPSILON) { found_epsilon = true; }
                        else { ans.insert(sym); }
                    }
                }
                // Don't check this production's next symbols if this FIRST(current symbol) doesn't yield an empty string.
                if (!found_epsilon) { break; }

                // If a production of 'A' can yield Empty String , then Epsilon is in FIRST(A).
                i++;
                if (!production[i]) { ans.insert(EPSILON); }
            }
        }

        return first[A] = ans;
    }

    // FIRST - String Edition
    unordered_set<char> FIRST (string B) {

        if (B == "e") { return {EPSILON}; }

        int n = B.length(),i;
        unordered_set<char> ans;
        bool found_epsilon;

        for (i=0;i<n;i++) {
            found_epsilon = false;
            if (isTerminal(B[i])) {  
                ans.insert(B[i]); 
                break;  
            }
            for (char symbol : first[B[i]]) {
                if (symbol == EPSILON) { found_epsilon = true; }
                else { ans.insert(symbol); }
            }
            if (!found_epsilon) { break; }
        }

        if (i == n) { ans.insert(EPSILON); }

        // cout<<"FIRST OF "<<B<<" : ";
        // for (char sym : ans) { cout<<sym<<" "; }
        // cout<<"\n";

        return ans;
    }

    // FOLLOW - Grammar Edition
    unordered_set<char> FOLLOW (char A, unordered_map<char,vector<string>>& productions) {

        if (!follow[A].empty()) { return follow[A]; }

        unordered_set<char> ans, temp;

        for (auto& production : productions) {
            for (auto& body : production.second) {
                int n = body.length();
                for (int i=0;i<n;i++) {
                    if (body[i] == A) {
                        temp = FIRST(body.substr(i+1,n-i-1));
                        if ((!body[i+1] || temp.find(EPSILON) != temp.end()) && A != production.first) { 
                            if (follow[production.first].empty()) { follow[production.first] = FOLLOW(production.first,productions); } 
                            // cout<<A<<" - "<<"FOLLOW("<<production.first<<")"<<"\n"; 
                            for (char sym : follow[production.first]) { ans.insert(sym); }
                            temp.clear();
                        }
                        if (body[i+1] && isTerminal(body[i+1])) { 
                            // cout<<A<<" -> "<<body[i+1]<<"\n"; 
                            ans.insert(body[i+1]); 
                        }
                        else if (body[i+1]) {
                            temp = first[body[i+1]];
                            // cout<<A<<" - "<<"FIRST("<<body[i+1]<<")"<<"\n";
                            for (char sym : temp) { ans.insert(sym); }
                            temp.clear();
                        }
                    }
                }
            }
        }
        if (A == start_symbol) { ans.insert(RIGHT_END_MARKER); }
        ans.erase(EPSILON);

        return follow[A] = ans;
    }

    // PARSE TABLE BUILDING ALGORITHM
    void BUILD_TABLE (unordered_map<char,vector<string>>& productions) {
        
        for (auto production : productions) {
            char head = production.first;
            for (auto body : production.second) {
                unordered_set<char> temp = FIRST(body);
                // FIRST(Body) Rule.
                if (body != "e") {
                    for (auto symbol : temp) {
                        if (symbol == EPSILON) { continue; }
                        M[head][symbol] = {head,body};
                    }
                }
                // if FIRST(body) contains 'Epsilon'.
                if (temp.find(EPSILON) != temp.end()) {
                    for (auto symbol : follow[head]) {
                        M[head][symbol] = {head,body};
                    }
                    if (follow[head].find(RIGHT_END_MARKER) != follow[head].end()) { M[head][RIGHT_END_MARKER] = {head,body}; }
                }
            }
        }
    }

    public:

    TopDownParser (char start_sym, unordered_map<char,vector<string>>& grammar) {

        G = grammar;
        start_symbol = start_sym;

        for (auto production : grammar) { 
            for (auto body : production.second) {
                for (auto symbol : body) {
                    if (isTerminal(symbol)) { Terminals.insert(symbol); }
                    else { Non_Terminals.insert(symbol); }
                }
            }
        }
        Terminals.erase(EPSILON);
        
        for (auto A : Non_Terminals) { first[A] = FIRST(A,G); }
        for (auto A : Non_Terminals) { follow[A] = FOLLOW(A,G); }
        BUILD_TABLE(G);
    }

    void SHOW_PARSER () {

        // Show the Grammar.
        cout<<"Grammar of the Parser : \n";
        cout<<"Start Symbol : "<<start_symbol<<"\n";

        cout<<"Terminals : ";
        for (auto& sym : Terminals) { cout<<sym<<" "; }
        cout<<"\n";

        cout<<"Non-Terminals : ";
        for (auto& sym : Non_Terminals) { cout<<sym<<" "; }
        cout<<"\n\n";

        cout<<"Productions : "<<"\n";
        for (auto& p : G) {
            cout<<p.first<<" -> ";
            for (auto& body : p.second) {
                cout<<body<<" | ";
            }
            cout<<"\n";
        }
        cout<<"\n";


        // Show FIRST for all Non-Terminals.
        for (auto A : Non_Terminals) {
            cout<<"FIRST("<<A<<"): ";
            for (auto symbol : first[A]) {
                cout<<symbol<<"  ";
            }
            cout<<"\n";
        }
        cout<<"\n";
        
        // Show FOLLOW for all Non-Terminals.
        for (auto A : Non_Terminals) {
            cout<<"FOLLOW("<<A<<"): ";
            for (auto symbol : follow[A]) {
                cout<<symbol<<"  ";
            }
            cout<<"\n";
        }
        cout<<"\n";

        // Show Parse Table 'M'
        cout<<"Parse Table : \n";
        for (auto& row : M) {
            for (auto& col : row.second) {
                auto production = col.second;
                cout<<"M["<<row.first<<","<<col.first<<"] = "<<production.first<<"->"<<production.second<<"\n";
            }
        }
        cout<<"\n";
    }

    // PREDICTIVE PARSING ALGORITHM
    /* 
        A Predictive Parser makes parsing decisions based on : Stack Top Symbol , Current Input String Symbol and Parsing Table. 
        Here, 
            Stack = s 
            Parsing Table = M
            Input String = input
    */
    bool PARSE (string input) {

        // Initialise Stack with Start_Symbol on its top.
        cout<<"Parsing input... \n";
        stack<char> s;
        s.push(start_symbol);
        // Add Input Right End Marker, for the Parser to determine End of Input String.
        input += RIGHT_END_MARKER;

        // Initialise Input Symbol Pointer to start of Input String.
        int i = 0;

        // Stack Becomes Empty Only After Parsing Full Input , otherwise it will go into Error State before Stack becomes Empty.
        while (!s.empty()) {
            // cout<<"Stack Top: "<<s.top()<<" | "<<"Current input :"<<input[i]<<"\n";
            // Stack top Symbol matches Input , remove it from Stack and move on to next Input Symbol.
            if (s.top() == input[i]) { s.pop(); i++; }
            /* if They don't match but Stack top symbol is still a Terminal OR 
            Parsing Table Doesn't have a Production to apply for current situation, 
            Then this input cannot be derived from this Grammar. Stop Parsing. */
            else if (isTerminal(s.top()) || M[s.top()][input[i]].first == '\0') { return false; }
            /* If a Production can be applied for Stack Top Symbol , push its Body onto Stack in Reverse Order (to parse Left->Right) */
            else {
                // Get the Production Rule.
                auto [head,body] = M[s.top()][input[i]];
                // Remove the Current Symbol since we substitute its Production for it.
                s.pop();
                // Push its Body in Reverse Order. A Production is of the form = { Head -> Body String }
                if (body != "e") {
                    int n = body.length();
                    for (int j=n-1;j>=0;j--) { s.push(body[j]); }
                }
                cout<<head<<"->"<<body<<"\n";
            }
        }

        return true;
    }

};

// DRIVER CODE
int main () {

    unordered_map<char,vector<string>> grammar;
    string p, temp, input;
    char start_symbol;

    // Take input Grammar.
    cout<<"What is the Start Symbol?\n";
    cin>>start_symbol;
    cout<<"\n";

    cout<<"Enter Productions as : Non-Terminal->String of Terminals and Non-terminals or Epsilon Only.\n";
    cout<<"Enter \"done\" to Stop Putting Productions.\n";
    while (1) {
        cin>>p;
        if (p == "done") { break; }

        for (int i=3;;i++) { 
            if(p[i] == '|' || !p[i]) { 
                grammar[p[0]].push_back(temp); 
                temp = ""; 
                if (!p[i]) { break; }
                else { continue; }
            }
            temp += p[i]; 
        }
    }
    cout<<"\n\n";

    // Build the Top Down Parser for given Grammar.
    TopDownParser P(start_symbol,grammar);
    P.SHOW_PARSER();

    // Parse User input strings.
    cout<<"Enter your Input Strings to check if they can be Derived from this Grammar.\n";
    cout<<"Enter \"done\" to Stop.\n";
    while (1) {
        cout<<"\n";
        cin>>input;
        if (input == "done") { return 0; }
        if (P.PARSE(input)) { cout<<"\nInput Parsed Successfully. Input CAN be derived from GIVEN Grammar.\n"; }
        else { cout<<"\nError Input.\n"; }
    }
    
    return 0;
}

/*

Example Grammars

1.
Start Symbol = E

E->TW
W->+TW|e
T->iY
Y->[U|e
U->]|X]
X->EZ
Z->,E|e
done

2.
Start Symbol = E

E->TX
X->+TX|e
T->FY   
Y->*FY|e
F->(E)|i
done 

*/