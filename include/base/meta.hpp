#ifndef GAME_META_HPP
#define GAME_META_HPP

#include "../stdlibs.hpp"

namespace base {
  class Meta;
}

class base::Meta {
  private:
    uint32_t references;

  public:
    Meta();
    base::Meta * release();
    base::Meta * retain();
    uint32_t referenceCount();
};

#endif
