// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include "vector.h"
#include <time.h>
#include "map.h"
#include "console.h"

using namespace std;

int main() {
    cout << "Welcome to CS 106B Random Writer ('N-Grams').\n";
    cout << "This program makes random text based on a document.\n";
    cout << "Give me an input file and an 'N' value for groups\n";
    cout << "of words, and I'll create random text for you.\n";
    string txt;
    cout << "Input file name?";
    cin >> txt;
    ifstream file(txt);
    Vector <string> all;
    Vector <string> words;
    string word;
    while(file >> word){
        all.add(word);
    }
    file.close();
    cout << "Value of N?";
    int N, w, a;
    cin >> N;
    cout << "# of random words to generate (0 to quit)?";
    cin >> w;
    if (w != 0){
        Vector <string> windows;
        Vector <string> value;
        Map <Vector<string>,Vector<string>> maps;
        srand((unsigned)time(NULL));
        a = ((1 + rand()) % all.size());
        if (a >= (all.size() - w))
            a = a - w;
        for (int j = 0;j < (all.size() - w);j++){
            if (j >= a && j < a + w){
                words.add(all[j]);
                if (j > (a + w - N)){
                    int k = 0;
                    for (;k < N - 1;k++){
                        if ((j + k) < a + w)
                            windows.add(all[j + k]);                        
                        else
                            windows.add(all[j + k - w]);
                    }
                    if (!maps.containsKey(windows)){
                        value.add(all[j + k - w]);
                        maps.put(windows,value);
                    }
                    else{
                        maps[windows].add(all[j + k - w]);
                    }                    
                    windows.clear();
                    value.clear();
                }
                else{
                    if (j == (a + w - N)){
                        int k = 0;
                        for (;k < N - 1;k++){
                            windows.add(all[j + k]);
                        }
                        if (!maps.containsKey(windows)){
                            value.add(all[a]);
                            maps.put(windows,value);
                        }
                        else
                            maps[windows].add(all[a]);
                        windows.clear();
                        value.clear();
                    }
                    else{
                        int k = 0;
                        for (;k < N - 1;k++)
                            windows.add(all[j + k]);
                        if (!maps.containsKey(windows)){
                            value.add(all[j + k]);
                            maps.put(windows,value);
                        }
                        else
                            maps[windows].add(all[j + k]);
                        windows.clear();
                        value.clear();
                    }
                }
            }
            else{
                if (j == a + w){
                    srand((unsigned)time(NULL));
                    int b = ((rand()) % (w - 2));
                    cout << "...";
                    if (b <=  w - N + 1){
                        int k = 0;
                        for (;k < N - 1;k++){
                            windows.add(all[a + b + k]);
                        }
                    }
                    else{
                        int k = 0;
                        for (;k < N - 1;k++)
                            if ((b + k) <= (w - 1)){
                                windows.add(all[a + b + k]);
                            }
                            else{
                                windows.add(all[a + b + k - w]);
                            }
                    }
                    int q = 0;
                    //cout << maps.size() << maps << endl;
                    while (q < w && (maps.containsKey(windows) == 1)){
                        value.addAll(maps.get(windows));
                        int c = 0;                      
                        if (value.size() == 1){
                            //cout << windows << "key1" << endl;
                            maps.remove(windows);
                        }
                        else{
                            //cout << windows << "key2" << endl;
                            srand((unsigned)time(NULL));
                            c = ((0 + rand()) % (value.size() - 1));
                            maps[windows].remove(c);
                        }
                        windows.clear();
                        for (int i = 0;i < words.size();i++){
                            if (words[i] == value[c]){
                                int k = 0;
                                for (;k < N - 1;k++){
                                    if ((i + k) < w){
                                        windows.add(words[i + k]);
                                        cout << words[i + k] << " ";
                                    }
                                    else{
                                        windows.add(words[i + k - w]);
                                        cout << words[i + k - w] << " ";
                                    }                                     
                                }
                                i = a + w;
                            }
                        }
                        value.clear();
                        q += (N - 1);
                    }
                    cout << "...";
                    break;
                }
            }
        }
    }
    else{
        if (w == 0)
            cout << "Exiting." << endl;
    }
    return 0;
}
