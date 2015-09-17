#include "DataFormat/storage_manager.h"

void simple_read() {

  larlite::storage_manager man;
  man.set_io_mode(man.kREAD);
  man.add_in_filename("trialpy.root");
  man.set_verbosity(larlite::msg::kDEBUG);
    //man.open()

    //while man.next_event() :
    //  print "event wdd"
    //  my_hit_v = man.get_data(fmwk.data.kHit1,"test")
    //  print my_hit_v.name()
    // print my_hit_v.at(0).RMS()
    // print my_hit_v.at(1).RMS()
  man.close();
}

