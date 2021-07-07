#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include "DictionaryTrie.hpp"
#include "util.hpp"

using namespace std;

/**
 * IMPORTANT! You should use the following lines of code to match the correct output:
 * 
 * cout << "This program needs exactly one argument!" << endl;
 * cout << "Reading file: " << file << endl;
 * cout << "Enter a prefix/pattern to search for:" << endl;
 * cout << "Enter a number of completions:" << endl;
 * cout << completion << endl;
 * cout << "Continue? (y/n)" << endl;
 * 
 */
int main(int argc, char** argv)
{
    if (argc != 2)
    {
        cout << "This program requires 1 argument!" << endl;
        return 1;
    }

    DictionaryTrie* dt = new DictionaryTrie();;

    // Read all the tokens of the file in order to get every word
    cout << "Reading file: " << argv[1] << endl;

    ifstream in;
    in.open(argv[1], ios::binary);
    string word;


    Utils::load_dict(*dt, in);
    in.close();


    char cont = 'y';
    unsigned int numberOfCompletions;
    while (cont == 'y')
    {
        cout << "Enter a prefix/pattern to search for:" << endl;
        getline(cin, word);
        cout << "Enter a number of completions:" << endl;
        cin >> numberOfCompletions;

        vector<string> completions;
        completions = dt->predictCompletions(word, numberOfCompletions);

        for (string s : completions)
        {
            cout << s << endl;
        }

        cout << "Continue? (y/n)" << endl;
        cin >> cont;
        cin.ignore();
    }
    delete dt;
    return 0;
}
