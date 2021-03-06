/**
 * \file LightPath.h
 *
 * \ingroup Algorithms
 * 
 * \brief Class def header for a class LightPath
 *
 * @author Rui
 */

/** \addtogroup Algorithms

    @{*/
#ifndef LIGHTPATH_H
#define LIGHTPATH_H

#include <iostream>
#include "OpT0Finder/PhotonLibrary/PhotonVisibilityService.h"
#include "OpT0Finder/Base/OpT0FinderTypes.h"
#include <numeric>
#include "GeoAlgo/GeoAlgo.h"
#include "LArUtil/Geometry.h"
#include <functional>
#include <algorithm>
#include "OpT0Finder/Base/BaseAlgorithm.h"
namespace flashana{
/**
   \class LightPath
   User defined class LightPath ... these comments are used to generate
   doxygen documentation!
 */

  class LightPath : flashana::BaseAlgorithm {
    
  public:
    
    /// Default constructor
    LightPath(const std::string name="LightPath");
    
    /// Default destructor
    ~LightPath(){}

    void Configure(const ::fcllite::PSet &pset);
    
    // Setter function
    bool   TrackStart   ( bool b  ) { _start_bool =b; return _start_bool;}//true, extend track at start
    bool   TrackEnd     ( bool b  ) { _end_bool   =b; return _end_bool;}  //true, extend track at end
    bool   PL_extension ( bool b  ) { _pl_ext = b;    return _pl_ext;}    //true, extend track to Photon Library volume; false to TPC FV
    double Set_Gap      ( double x) { _gap   =x;      return _gap;}
      
    // Getter function
    flashana::QCluster_t FlashHypothesis(const ::geoalgo::Trajectory& trj) const;

    void QCluster(const ::geoalgo::Vector& pt_1,
                  const ::geoalgo::Vector& pt_2,
                  flashana::QCluster_t& Q_cluster) const;
    
    void SetVolume ();

    void SetXOffset(double offset ) { _offset = offset ; }

    /// Setter to use offset (currently it is set to True by default...)
    /// Seems like this should bet set to False if you are not running on cosmics
    void SetUseXOffset(bool aoweifh) { _use_offset = aoweifh; }

  protected:
    bool   _start_bool;
    bool   _end_bool;
    bool   _pl_ext;
    double _gap;
    double _light_yield;
    double _dEdxMIP;
    ::geoalgo::GeoAlgo _geoAlgo;
    ::geoalgo::AABox _vfiducial;
    
    mutable int _n;

    mutable int _offset ;
    bool _use_offset ;
  };
} 

#endif
/** @} */ // end of doxygen group 

