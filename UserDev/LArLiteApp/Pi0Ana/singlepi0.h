/**
 * \file singlepi0.h
 *
 * \ingroup Pi0Ana
 * 
 * \brief Class def header for a class singlepi0
 *
 * @author ryan
 */

/** \addtogroup Pi0Ana

    @{*/

#ifndef LARLITE_SINGLEPI0_H
#define LARLITE_SINGLEPI0_H

#include "Analysis/ana_base.h"
#include "DataFormat/mctruth.h"
#include "DataFormat/mcpart.h"

namespace larlite {
  /**
     \class singlepi0
     User custom analysis class made by SHELL_USER_NAME
   */
  class singlepi0 : public ana_base{
  
  public:

    /// Default constructor
    singlepi0(){ _name="singlepi0"; _fout=0; _Topo=0;}

    /// Default destructor
    virtual ~singlepi0(){}

    /** IMPLEMENT in singlepi0.cc!
        Initialization method to be called before the analysis event loop.
    */ 
    virtual bool initialize();

    /** IMPLEMENT in singlepi0.cc! 
        Analyze a data event-by-event  
    */
    virtual bool analyze(storage_manager* storage);

    /** IMPLEMENT in singlepi0.cc! 
        Finalize method to be called after all events processed.
    */
    virtual bool finalize();

    void SetDefaultParams();


	// change this to string or something as time goes on... or keep a list
	// 0 = inclusive ==> any pi0 that is a final state particle
	// 1 = exclusive no cmeson ==> any pi0 that is a final state particle and has no final state pi+/-
    void SetTopology(int Topo) { _Topo = Topo ; }


  protected:

	int _total_events; 
	int _passed_events; 
	
	int _Topo;

    
  };
}
#endif

//**************************************************************************
// 
// For Analysis framework documentation, read Manual.pdf here:
//
// http://microboone-docdb.fnal.gov:8080/cgi-bin/ShowDocument?docid=3183
//
//**************************************************************************

/** @} */ // end of doxygen group 
