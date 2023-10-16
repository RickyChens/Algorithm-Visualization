#include <iostream>
#include <vector>
#include "rogueutil.h"

using namespace std;
using namespace rogueutil;

int g_comparisonCount = 0;
int g_swapCount = 0;

void sort_swap(vector <int> &v, int firstIndex, int secondIndex);
int sort_comparison(int x, int y, int firstIndex, int secondIndex);
void updateLine(int x, int count);
void draw_initial(vector <int> &v);
void sort_insertion(vector <int> &v); 
void sort_selection(vector <int> &v);
void sort_bubble(vector <int> &v);
void sort_quicksort(vector <int> &v, int L, int R);
int partition(vector <int> &v, int L, int R);
void resetScreen(vector <int> &v, vector <int> &copy);

int main()
{
    hidecursor();
    srand(time(nullptr));

    vector <int> num;
    vector <int> copy;

    while (num.size() < (tcols())) {
        if (rand() % 2 == 0) {
            num.push_back(rand() % (trows() - 5));
            copy.push_back(rand() % (trows() - 5));
        }
    }



    cls();
    setColor(WHITE);
    draw_initial(num);


    sort_insertion(num);  
    resetScreen(num, copy);
    draw_initial(num);
    sort_selection(num);
    resetScreen(num, copy);
    draw_initial(num);
    sort_bubble(num);
    resetScreen(num, copy);
    draw_initial(num);
    sort_quicksort(num, 0, num.size()-1);
    resetScreen(num, copy);

    showcursor();

    return 0;
}

void sort_swap(vector <int> &v, int firstIndex, int secondIndex) {
    g_swapCount++;
    gotoxy(1,2);
    cout << "Swaps: " << g_swapCount << "    ";
    
    setColor(LIGHTRED);
    updateLine(firstIndex, v[secondIndex]);
    updateLine(secondIndex, v[firstIndex]);

    cout.flush();
    msleep(10);

    swap(v[firstIndex], v[secondIndex]);

    setColor(WHITE);
    gotoxy(firstIndex + 1, 5);
    cout << 'V';
    gotoxy(secondIndex + 1, 5);
    cout << 'V';

    msleep(10);

    gotoxy(firstIndex + 1, 5);
    cout << ' ';
    gotoxy(secondIndex + 1, 5);
    cout << ' ';

    updateLine(firstIndex, v[firstIndex]);
    updateLine(secondIndex, v[secondIndex]);

    cout.flush();
    msleep(10);
}

int sort_comparison(int x, int y, int firstIndex, int secondIndex)
{
    gotoxy(1,1);
    cout << "Comparisons: " << g_comparisonCount << "      ";

    gotoxy(firstIndex + 1, 5);
    cout << 'V';
    gotoxy(secondIndex + 1, 5);
    cout << 'V';
    
    msleep(10);

    gotoxy(firstIndex + 1, 5);
    cout << ' ';
    gotoxy(secondIndex + 1, 5);
    cout << ' ';

    setColor(LIGHTGREEN);
    updateLine(firstIndex, x);
    updateLine(secondIndex, y);

    msleep(10);

    setColor(WHITE);
    updateLine(firstIndex, x);
    updateLine(secondIndex, y);

    g_comparisonCount += 1;
    return x - y;
}

void updateLine(int x, int count){
    for (int i = 0; i < trows() - 6; i++){
        gotoxy(x + 1, i + 6);
        cout << ((i < count) ? '#' : ' ');
    }
    cout.flush();
}

void draw_initial(vector <int> &v){
    for (int x = 0; x < v.size(); x++){
        updateLine(x, v[x]);
    }
}

void sort_insertion(vector <int> &v) {
    for (int i = 0; i < v.size(); i++) {
        int j = i;
        while (j > 0 && (sort_comparison(v[j], v[j - 1], j, j - 1) < 0)) {
            sort_swap(v, j, j - 1);
            j--;
        }
    }
}

void sort_selection(vector <int> &v) {
    for (int i = 0; i < v.size(); i++) {
        int smaller = i;
        for (int j = i + 1; j < v.size(); j++){
            if (sort_comparison(v[j], v[smaller], j, smaller) < 0) {
                smaller = j;
            }
        }

        sort_swap(v, i, smaller);
    }
}

void sort_bubble(vector <int> &v) {
    for (int i = 0; i < v.size() - 1; i++) {
        for (int j = 0; j < v.size() - 1; j++) {
            if (sort_comparison(v[j], v[j+1], j, j+1) > 0) {
                sort_swap(v, j, j+1);
            }
        }
    }
}

int partition(vector <int> &v, int L, int R) {
    int result;
    int i = L - 1;
    int j = R + 1;
    int pivot = v[R];
    for (;;) {
        while (sort_comparison(v[++i], pivot, i, R) < 0);
        while (sort_comparison(v[--j], pivot, j, R) > 0);
        if (i < j) {
            sort_swap(v, i, j);
        }
        else {
            result = i;
            break;
        }
    }

    return result;
}

void sort_quicksort(vector <int> &v, int L, int R){
    if (L < R) {
        int p = partition(v, L, R);
        sort_quicksort(v, L, p-1);
        sort_quicksort(v, p, R);
    }
}

void resetScreen(vector <int> &v, vector <int> &copy){
    setColor(WHITE);
    v = copy;
    gotoxy(1, trows());
    anykey("Press a key to Continue");
    printXY(1, trows(), "                       ");
    g_comparisonCount = 0;
    g_swapCount = 0;

    gotoxy(1,1);
    cout << "Comparisons: " << g_comparisonCount << "      ";

    gotoxy(1,2);
    cout << "Swaps: " << g_swapCount << "    ";

}
