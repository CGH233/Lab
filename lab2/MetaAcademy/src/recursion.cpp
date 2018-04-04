/* 
 * TODO: put your own comments here. Also you should leave comments on
 * each of your methods.
 */

#include <math.h>
#include "recursion.h"
#include "map.h"
#include "vector.h"
#include "set.h"
#include "gwindow.h"
#include "gobjects.h"
#include "tokenscanner.h"
using namespace std;

int gcd(int a, int b) {
    if (b != 0){
        cout << "gcd(" << a << ", " << b << ") = gcd(" << b << ", " << a%b << ")\n";
        return gcd(b, a%b);
    }
    else{
        cout << "gcd(" << a << ", " << b << ") = " << a << endl;
        return a;
     }
}

void serpinskii(GWindow &w, int leftX, int leftY, int size, int order){
    if (0 < order){
        w.drawLine(leftX,leftY,leftX+size,leftY);
        w.drawLine(leftX+size,leftY,leftX+size/2,leftY+(size*1.732)/2);
        w.drawLine(leftX+size/2,leftY+(size*1.732)/2,leftX,leftY);
        serpinskii(w, leftX, leftY, size/2, order - 1);
        serpinskii(w, leftX + size/2, leftY, size/2, order - 1);
        serpinskii(w, leftX + size/4, leftY + (size * 1.732) /4, size/2, order - 1);
    }
}


int floodFill(GBufferedImage& image, int x, int y, int newColor) {
    if (image.getRGB(x,y) != newColor && image.inBounds(x,y)){
        int k = image.getRGB(x,y);
        image.setRGB(x,y,newColor);
        for (int i = -1;i < 2;i+=2){
            if (image.inBounds(x+i,y) && (image.getRGB(x+i,y) == k)){
                floodFill(image,x+i,y,newColor);
            }
            if (image.inBounds(x,y+i) && (image.getRGB(x,y+i) == k)){
                floodFill(image,x,y+i,newColor);
            }
        }
    }
    else
        return 0;
    return 0;
}

Vector<string> print;

void personalCurriculum(Map<string, Vector<string>> & prereqMap,string goal) { 
    for (int i = 0;i < print.size();i++){
        if (print[i] != goal && i == print.size() - 1)
            print.add(goal);
    }
    cout << print << endl;
}

string generate(Map<string, Vector<string> > & grammar, string symbol) {
    // your code here
    cout << "[recursion generate called]" << endl;
    return "";
}
