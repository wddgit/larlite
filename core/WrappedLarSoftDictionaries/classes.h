#include "DataFormat/wrapper.h"
#include "lardatalite/RecoBase/Hit.h"

namespace DataFormats_Common {
  struct dictionary {
    larlite::wrapper<std::vector<recob::Hit> > dummywh;
  };
}

