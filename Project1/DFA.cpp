#include "DFA.hpp"
#include <fstream>
#include <cmath> // for std::pow
#include <algorithm> // for std::reverse

DFA::DFA(int n) : alphabet{'a', 'b', 'c', 'd'} {
    transitions.resize(1366, std::vector<int>(4)); 
    count.resize(1366);
    length = n;
    //states[1365] = "dead state";
    //states[0] = ""; // starting state

    for (auto i : alphabet)
        std::cout << i << ' ';

    std::cout << '\n';

    /*set_states();

    std::ofstream ofile("test.txt");

    for (const auto &state : states)
        ofile << state.first << " : " << state.second << '\n';
    
    ofile.close(); */

    std::ofstream file("test3.txt");

    for (int i = 0; i < transitions.size(); i++)
        transition_function(i);

    for (int i = 0; i < transitions.size(); i++) {
        file << i << " : " << decode(i) << '\t';

        for (const auto &j : transitions[i]) {
            file << j << ' ';
        }
        file << '\n';
    }

    file.close();

    for (int i = 0; i < count.size() - 1; i++)
        count[i] = 1;

    count[1365] = 0;

    for (int i = 0; i < count.size(); i++)
        std::cout << i << ": " << count[i] << '\n';

}

/*void DFA::set_states() {
    int MAX_LENGTH = 5; // max number of characters for each state
    int actual = std::min(length, MAX_LENGTH);

    for (int i = 1; i <= actual; i++)
        get_states("", i);
    
}

void DFA::get_states(std::string prefix, int k) {
    // Base case: k is 0,
    // print prefix
    if (k == 0) {
        std::ofstream ofile("test2.txt", std::ofstream::app);

        int key = encode(prefix);
        states[key] = prefix;

        ofile << key << " : " << prefix << '\t' << decode(key) << '\n';
        ofile.close();
        return;
    }
 
    // One by one add all characters
    // from set and recursively
    // call for k equals to k-1
    for (int i = 0; i < a_SIZE; i++) {
        std::string newPrefix;
         
        // Next character of input added
        newPrefix = prefix + alphabet[i];
         
        // k is decreased, because
        // we have added a new character
        get_states(newPrefix, k - 1);
    }
} */

int DFA::encode(std::string str) {
    int value = 0;
    int j = 0;

    for (int i = str.size() - 1; i >= 0; i--) 
        value += (int(str[i]) - 96) * std::pow(4, j++); 

    return value;
}

std::string DFA::decode(int value) {
    std::string str;

    while (value > 0) {
        char c = (value % 4) + 96;

        if (c == 96) { 
            c = 100;
            value--;
        }   
        
        str += c;
        value /= 4;
    }

    std::reverse(str.begin(), str.end());
    return str; 
}

void DFA::transition_function(int value) {
    std::string state = decode(value);

    // dead state always transitions to dead state
    if (value == 1365) {
        for (int j = 0; j < 4; j++) {
            transitions[value][j] = value;
        }

        return;
    }

    // will always transition to an accepting state
    if (state.length() < 5) {
        for (int j = 0; j < 4; j++) {
            //char c = char(j + 97);
            std::string nextState = state + char(j + 97);
            std::cout << "^^^^ " << nextState << '\n';
            transitions[value][j] = encode(nextState);
        }

        return;
    }
    
    // if state has 5 characters in it
    for (int j = 0; j < 4; j++) {
        std::string nextState = state + char(j + 97);
        
        transitions[value][j] = is_valid(nextState) 
            ? encode(nextState.substr(1, nextState.size() - 1))
            : 1365; // dead state

        
        //nextState = nextState.substr(1, nextState.size() - 1);
        std::cout << "%$#%$# " << nextState << '\t';

        //if (A && B && C && D)
           // std::cout << "good";

        std::cout << std::endl;

        

    }

    std::cout << transitions.size() << "  ^^^^\n";
}

bool DFA::is_valid(std::string str) {

    bool A = false, B = false, C = false, D = false;

        for (int k = 0; k < str.size(); k++) {
            switch(str[k]) {
                case 'a':
                    A = true;
                    break;
                case 'b':
                    B = true;
                    break;
                case 'c':
                    C = true;
                    break;
                case 'd':
                    D = true;
                    break;
            }
        }

        return (A && B && C && D);
}

void DFA::num_strings_accepted() {
    for (int k = 0; k < length; k++) {
        std::vector<BigUnsigned> previous = count;
        for (int i = 0; i < count.size(); i++) {
            BigUnsigned nextCount;
            for (int j = 0; j < 4; j++) {
                int t_state = transitions[i][j];
                std::cout << i << ": " << t_state << '\t';
                nextCount += previous[t_state];
                //count[i] = nextCount;
            }
            std::cout << '\n';
            count[i] = nextCount;
            std::cout << nextCount << " &&&\n";
        }
    }

    
    std::cout << count[0] << '\n';
    // return std::numeric_limits<int>::max();
}
