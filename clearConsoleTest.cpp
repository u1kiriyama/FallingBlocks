#include <iostream>
#include <cstdlib>

int main(int argc, char* argv[]){
  for(int idx=0; idx<10; idx++){
    std::cout << idx << std::endl;
  }
  //コンソールの表示内容をクリアする
  std::system("reset");
  std::cout << "abc" << std::endl;
  std::cin.get();
}