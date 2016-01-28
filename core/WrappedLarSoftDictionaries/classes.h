#include "DataFormat/wrapper.h"
#include "lardatalite/RecoBase/Hit.h"
#include "lardatalite/RecoBase/Cluster.h"

namespace DataFormats_Common {
  struct dictionary {
    larlite::wrapper<std::vector<recob::Hit> > dummywh;
    larlite::wrapper<std::vector<recob::Cluster> > dummywc;
  };
}

