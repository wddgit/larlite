/**
 * \file ed_product.h
 *
 * \ingroup DataFormat
 * 
 * \brief Base class of  class that wraps data stored in ROOT
 *
 * @author W. David Dagenhart - Fermilab 2015
 */

/** \addtogroup DataFormat

    @{*/

#ifndef LARLITE_core_DataFormat_ed_product_H
#define LARLITE_core_DataFormat_ed_product_H

#include "product_id.h"

namespace larlite {

  class ed_product {
  public:

    friend class storage_manager;

    ed_product() :

    virtual ~ed_product();


    product_id productID() const { return fProductID; }

    /// run number getter
    unsigned int run      () const;
    /// sub-run number getter
    unsigned int subrun   () const;
    /// event-id getter
    unsigned int event_id () const;

  private:

    /// run number setter
    void set_run      (unsigned int run);
    /// sub-run number setter
    void set_subrun   (unsigned int run);
    /// event-id setter
    void set_event_id (unsigned int id );

    product_id fProductID;

    unsigned int fRunNumber;    ///< Run number
    unsigned int fSubRunNumber; ///< Sub-Run number
    unsigned int fEventID;      ///< Event ID
  };
}
#endif
