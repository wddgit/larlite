import sys
from larlite import larlite as fmwk
from ROOT import *

man=fmwk.storage_manager()
man.set_io_mode(man.kREAD)
man.add_in_filename("trialpy.root")
man.set_verbosity(fmwk.msg.kDEBUG)
man.open()

while man.next_event() :
    my_hit_v = man.get_data(fmwk.data.kHit1,"test")
    print my_hit_v.name()
    print my_hit_v.product().at(0).RMS()
    print my_hit_v.at(1).RMS()
    my_wrapped_int = man.get_data(fmwk.data.kInt,"test")
    print my_wrapped_int.productRef()
man.close()
