/**
 * \file product_id.h
 *
 * \ingroup DataFormat
 * 
 * \brief Identifies a product with type and a producer assigned name.
 *
 * @author W. David Dagenhart - Fermilab 2015
 */

/** \addtogroup DataFormat

    @{*/

#ifndef LARLITE_core_DataFormat_product_id_H
#define LARLITE_core_DataFormat_product_id_H

#include "Base/DataFormatConstants.h"

#include <string>

namespace larlite {
  /**
     \class product_id
     A very simple class that has (a) sorting feature and (b) simple constrution
     w/o invoking template specialization for easy usage in python
   */
  class product_id {
  public:

    product_id(unsigned short iType = larlite::data::kDATA_TYPE_MAX,
	       std::string const& iName = "noname") :
      fType(iType),
      fName(iName) {
    }

    /// For sorting
    inline bool operator< ( product_id const& rhs ) const {
      if(fType < rhs.fType) return true;
      else if(fType > rhs.fType) return false;
      return fName < rhs.fName;
    }

    unsigned short type() const { return fType; }
    std::string const& name() const { return fName; }

  private:

    unsigned short fType;
    std::string fName;
  };
}
#endif
