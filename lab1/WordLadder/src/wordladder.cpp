// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include "queue.h"
#include "stack.h"
#include "console.h"
#include "lexicon.h"

using namespace std;

int main()
{
    cout << "Welcome to CS 106B Word Ladder.\nPlease give me two English words, and I will change the\nfirst into the second by changing one letter at a time.\n";
    string txt = "Dictionary file name?";
    cout << txt;
    cin >> txt;
    string a, b;
    int c = 0;
    Lexicon all;
    Lexicon ladders;
    all.addWordsFromFile(txt);
    cout << "Word #1 (or Enter to quit):";
    cin >> a;
    if (all.contains(a)){
        cout << "Word #2 (or Enter to quit):";
        cin >> b;
        if (all.contains(b) && b.length() == a.length() && a != b)
            c = 1;
    }
    Stack <string> stack1;
    int k = 0;
    if (c == 1){
        cout << "A ladder from " << b << " back to " << a << ":" << endl;
        Queue <Stack<string>> way;
        stack1.push(a);
        way.enqueue(stack1);
        while (!way.isEmpty()){
            string word = way.peek().peek();
            int l = word.size();
            for (int i = 0;i < l;i++){
                for (int x = 'a';x < 'z';x++){
                    string word2;
                    if (word[i] != x){
                        word2 = word;
                        word2[i] = x;
                        if (all.contains(word2) && !ladders.contains(word2)){
                            ladders.add(word2);
                            if (word2 == b){
                                if(k == 0){
                                    stack1 = way.peek();
                                    k++;
                                }
                                else{
                                    if (way.peek().size() < stack1.size())
                                        stack1 = way.peek();
                                }
                            }
                            else{
                                Stack<string> stack2;
                                stack2 = way.peek();
                                stack2.push(word2);
                                way.enqueue(stack2);
                            }
                        }
                    }
                }
            }
            way.dequeue();
        }
    }
    if (c == 1){
        int j = stack1.size();
        cout << b << " ";
        for (int i = 0;i < j;i++)
            cout << stack1.pop() << " ";
    }
    if (c == 0)
        cout << "Have a nice day." << endl;
    return 0;
}
