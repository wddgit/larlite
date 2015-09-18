#include <TSystem.h>
#include <TVector3.h>
#include "DataFormat/storage_manager.h"
#include "DataFormat/hit1.h"
#include "DataFormat/track.h"
#include "DataFormat/wrapper.h"
int main(){

  //
  // A simple routine to read a data file and perform an event loop.
  // This is a test routine for storage_manager class which interacts
  // decoder output root file. 
  //

  larlite::storage_manager my_storage;

  // If you wish, change the message level to DEBUG.
  // Commented out by default.
  //my_storage.set_verbosity(larlight::MSG::DEBUG);

  // Step 0: Set I/O mode: we are reading in, so "READ"
  my_storage.set_io_mode(larlite::storage_manager::kWRITE);

  // Step 1: Set output file 
  my_storage.set_out_filename("trial.root");

  // Step 2: Open a file.
  my_storage.open();

  // Step 3: Check if a file is opened.
  if(!my_storage.is_open()) {
    std::cerr << "File open failed!" << std::endl;
    return 0;
  }
  
  // Step 4: Check if it's ready to perform I/O
  if(!my_storage.is_ready_io()) {
    std::cerr << "I/O preparation failed!" << std::endl;
  }

  // Let's fill event_track for 100 events.
  //auto my_event_track = my_storage.get_data<larlite::event_track>("test");
  auto my_event_track = (::larlite::event_track*)(my_storage.get_data(larlite::data::kTrack,"test"));
  auto my_v_hit1 = (::larlite::wrapper<std::vector<larlite::hit1> >*)(my_storage.get_data(larlite::data::kHit1,"test"));
  int run_id = 1;
  int subrun_id = 1;
  for( int i=0; i<100; i++){
    std::cout<<my_storage.get_entries_written()<<std::endl;
    int event_id = i;
    my_storage.set_id(run_id, subrun_id, event_id);

    // Let's make 2 tracks!
    for( int j=0; j<2; j++){
      larlite::track t;
      t.set_track_id(j); 

      // Let's make a track with 20 fake space points
      for(int k=0; k<20; k++){
	t.add_vertex    ( TVector3( (double)k,(double)k,(double)k ) );
	t.add_momentum  ( 1.);
	t.add_direction ( TVector3( (double)k,(double)k,(double)k ) );
      }

      // Append to the event track array
      my_event_track->push_back(t);

      larlite::hit1 h;
      // The argument value is arbitrary, just writing something
      // so that I can read it back later and check that I read
      // what I wrote.
      h.set_rms(11.0 + j);
      my_v_hit1->product()->push_back(h);
    }

    larlite::AssSet_t ass;
    ass.push_back(larlite::AssUnit_t(1,0));

    // Commented this out because it fails to compile
    // I do not know why it was here or what it was supposed to do.
    // my_event_track->set_association(larlite::data::kHit,"test",ass);

    // Store event
    my_storage.next_event();

  }

  my_storage.close();
  return 1;
}
