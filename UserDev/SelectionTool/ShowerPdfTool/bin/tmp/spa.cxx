#ifndef SELECTIONTOOL_SPALGO_CLASS_NAME_CXX
#define SELECTIONTOOL_SPALGO_CLASS_NAME_CXX

#include "SPAlgo_Class_Name.h"

namespace sptool {

  SPAlgo_Class_Name::SPAlgo_Class_Name() : SPAlgoBase()
  {
    _name     = "SPAlgo_Class_Name";
    _nshowers = 1;
  }

  float SPAlgo_Class_Name::Select(const std::vector<const larlite::shower*> &data)
  { return 1; }

  void SPAlgo_Class_Name::Fill(const std::vector<const larlite::shower*> &data)
  {}

  void SPAlgo_Class_Name::Fill(const std::vector<const larlite::mcshower*> &data)
  {}

  void SPAlgo_Class_Name::Fit(TFile* fout)
  {}

}

#endif
