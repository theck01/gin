#include "../../include/base/meta.hpp"

base::Meta::Meta(){
  references = 1;
}

base::Meta * base::Meta::release(){
  if(--references == 0){
    delete this;
    return NULL;
  }
  else return this;
}

base::Meta * base::Meta::retain(){
  references++;
  return this;
}

uint32_t base::Meta::referenceCount(){
  return references;
}
