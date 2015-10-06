import sys
from larlite import larlite as fmwk

import ROOT
ROOT.gSystem.Load( "libCintex" )
ROOT.Cintex.Enable()
#import PyCintex

ROOT.gSystem.Load('libRecoBase.so')
ROOT.gSystem.Load('libRecoBase_dict.so')
ROOT.gSystem.Load('libRecoBase_map.so')
ROOT.gSystem.Load('libLArLite_WrappedLarSoftDictionaries.so')

man=fmwk.storage_manager()
man.set_io_mode(man.kWRITE)
man.set_out_filename("trialpy.root")
man.set_verbosity(fmwk.msg.kDEBUG)
man.open()

run,subrun,event=(0,0,0)
for x in xrange(10):

    if x%5==0: run=x/5
    subrun = (x%5)/3
    event = x - run*5 - subrun*3

    for y in xrange(fmwk.data.kDATA_TYPE_MAX):

        if y in [fmwk.data.kUndefined,
                 fmwk.data.kSeed,
                 fmwk.data.kEvent,
                 fmwk.data.kMCTrajectory,
                 fmwk.data.kMCNeutrino,
                 fmwk.data.kDATA_TYPE_MAX]:
            continue

        wrapped = man.get_data(y,"test")
        if y == fmwk.data.kHit1 :
          print dir(wrapped.product())
          h = fmwk.hit1()
          h.set_rms(11.0)
          wrapped.product().push_back(h)
          h2 = fmwk.hit1()
          h2.set_rms(12.0)
          wrapped.product().push_back(h2)

        if y == fmwk.data.kInt :
          wrapped.set(21)

        if y == fmwk.data.kLarSoftHit :

          h11 = ROOT.recob.Hit()
          #h = recob.Hit(raw.InvalidChannelID, 0, 0, 0., -1., 221.0 + j, 0., -1., 0., 0., -1., 0, -1, 0., -1, geo.kUnknown, geo.kMysteryType, geo.WireID())
          print dir(wrapped.product())
          wrapped.product().push_back(h11)

        # This is commented out because it does not work in ROOT 5
        # but it will work ROOT 6.
        #if y == fmwk.data.kMapIntDouble :
        #  wrapped.insert(std.pair('const int,double')(31,101.0))

    for y in xrange(fmwk.data.kSUBRUNDATA_TYPE_MAX):

        if y in [fmwk.data.kSUBRUNDATA_Undefined]:
            continue

        man.get_subrundata(y,"test")

    for y in xrange(fmwk.data.kRUNDATA_TYPE_MAX):

        if y in [fmwk.data.kRUNDATA_Undefined]:
            continue

        man.get_rundata(y,"test")

    man.set_id(run,subrun,event)
    man.next_event()

man.close()
