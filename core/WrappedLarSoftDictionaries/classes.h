#include "DataFormat/wrapper.h"
#include "RecoBase/Hit.h"

namespace DataFormats_Common {
  struct dictionary {
    larlite::wrapper<std::vector<recob::Hit> > dummywh;
  };
}

