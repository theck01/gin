#include "../../include/base/Meta.hpp"

int main(){

  uint32_t i;
  base::Meta * a = new base::Meta();

  for(i=0; i<5; i++){
    assert(i == a->referenceCount()-1);
    a->retain();
  }

  for(i=0; i<5; i++) assert(a->release() != NULL);

  assert(a->release() == NULL);

  std::cout << "base::Meta -- TESTS PASSED" << std::endl;
}

