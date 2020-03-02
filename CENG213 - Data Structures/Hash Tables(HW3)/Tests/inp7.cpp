#include "hw3.h"

using namespace std;

/*
    This input file tests the basic working
    pipeline of the expanding.

    Need to expand table 2 times.

    Also checks the addUser function.
*/

int main()
{
  AccessControl ac1(3, 3);

  ac1.addUser("melek", "yilmaz") ;
  ac1.addUser("seytan", "yilmaz") ;
  ac1.addUser("Orion", "orionspass") ;
  ac1.addUser("Orion", "orionspass") ;



  ac1.changePass("Orion", "orionspass", "kelam");

  std::vector<std::string> oldPass;
  ac1.delUser("Orion", oldPass);
  for(int i = 0; i < oldPass.size(); i++)
    std::cout << oldPass[i] << ' ';
    std::cout << "" << '\n';
  ac1.delUser("Orion", oldPass);
  for(int i = 0; i < oldPass.size(); i++)
    std::cout << oldPass[i] << ' ';
    std::cout << "" << '\n';




  ac1.printPasswords();
  return 0;
}
