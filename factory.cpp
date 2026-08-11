#include<iostream>
using namespace std;

class Hero {
    // By default, if no access specifier is written, members are PRIVATE
    int health;       
};                    
int main() {
    Hero h1; // Object creation
    cout << sizeof(h1); 
    return 0;
}
