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

void windowsadd (Vector <string> windows, Vector <string> all, int N, int a, int j ,int w)
{
    int k = 0;
    for (;k < N - 1;k++){
        if ((j + k) < a + w)
            windows.add(all[j + k]);
        else
            windows.add(all[j + k - w]);
    }
}

void mapsadd (Map <Vector<string>,Vector<string>> maps,Vector <string> windows,Vector <string> value,Vector <string> all,int j, int w, int N, int a)
{
    int k = 0;
    windowsadd(windows,all,N,a,j,w);
    if (!maps.containsKey(windows)){
        if ((j + k) < a + w)
            value.add(all[j + k]);
        else
            value.add(all[j + k - w]);
        maps.put(windows,value);
    }
    else{
        if ((j + k) < a + w)
            maps[windows].add(all[j + k]);
        else
            maps[windows].add(all[j + k - w]);
    }
    windows.clear();
    value.clear();
}

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
    if (w == 0)
        cout << "Exiting.";
    Vector <string> windows;
    Vector <string> value;
    Map <Vector<string>,Vector<string>> maps;
    srand((unsigned)time(NULL));
    a = ((1 + rand()) % all.size());
    if (a >= (all.size() - w))
        a = a - w;
    for (int j = 0;j < (all.size() - w);j++){
        if (j > a && j < a + w){
            words.add(all[j]);
            mapsadd(maps,windows,value,all,j,w,N,a);
        }
        else{
            if (j == a + w){
                srand((unsigned)time(NULL));
                int b = ((rand()) % (w - 2));
                cout << "...";
                windowsadd(windows,all,N,a,a+b,w);
                int q = 0;
                cout << maps;
                while (q < w && (maps.containsKey(windows) == 1)){
                    value.addAll(maps.get(windows));
                    int c = 0;
                    if (value.size() == 1){
                        maps.remove(windows);
                    }
                    else{
                        srand((unsigned)time(NULL));
                        c = ((0 + rand()) % (value.size() - 1));
                        maps[windows].remove(c);
                    }
                    windows.clear();
                    for (int i = 0;i < words.size();i++){
                        if (words[i] == value[c]){
                            windowsadd(windows,all,N,a,a+i,w);
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
    return 0;
}
