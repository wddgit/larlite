import sys
from larlite import larlite as fmwk
from ROOT import *

man=fmwk.storage_manager()
man.set_io_mode(man.kREAD)
man.add_in_filename("trialpy.root")
man.set_verbosity(fmwk.msg.kDEBUG)
man.open()

while man.next_event() :

    # test reading a vector<hit1>
    my_hit_v = man.get_data(fmwk.data.kHit1,"test")
    print my_hit_v.name()
    print my_hit_v.product().at(0).RMS()
    print my_hit_v.at(1).RMS()
    for i in my_hit_v.product() :
      print i.RMS()

    # test reading a map<int, double>
    my_wrapped_mapIntDouble = man.get_data(fmwk.data.kMapIntDouble,"test")
    # This is commented out because it fails with ROOT 5, but it
    # should work nicely with ROOT 6
    #print my_wrapped_mapIntDouble.at(31)
    #for key, value in my_wrapped_mapIntDouble.product() :
    #  print key, value

    # test reading an int
    my_wrapped_int = man.get_data(fmwk.data.kInt,"test")
    # for builtin types only, need to add [0] for pyROOT which is strange
    print my_wrapped_int.product()[0]

man.close()
