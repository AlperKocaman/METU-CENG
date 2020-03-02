#include "hw3.h"
#include "hw3.cpp"

int main()
{

    AccessControl a(7,11);

    
    a.addUser("1","1");
    a.addUser("2","2");
    a.addUser("3","3");
    a.addUser("8","8");
    a.printPasswords();
    
    //cout<<a.get("8")<<endl;
    
    return 0;
}
