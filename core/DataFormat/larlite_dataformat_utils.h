/**
 * \file larlite_dataformat_utils.h
 *
 * \ingroup DataFormat
 * 
 * \brief DataFormat utility typedefs
 *
 * @author Kazu - Nevis 2013
 */

/** \addtogroup DataFormat

    @{*/
#ifndef LARLITE_DATAFORMAT_UTILS_H
#define LARLITE_DATAFORMAT_UTILS_H

#include <vector>
#include <map>

#include "Base/DataFormatConstants.h"
#include "product_id.h"

namespace larlite{

  /// Represents one => X (1 or many) association in terms of vector index number
  typedef std::vector<unsigned int> AssUnit_t;
  /// Represents a set of AssUnit_t ... association @ event_X data product level
  typedef std::vector<AssUnit_t > AssSet_t;

  /// Invalid association
  const AssSet_t kEMPTY_ASS;

  /// Invalid run, subrun, and event ID values
  const unsigned int kINVALID_RUN    = data::kINVALID_UINT;
  const unsigned int kINVALID_SUBRUN = data::kINVALID_UINT;
  const unsigned int kINVALID_EVENT  = data::kINVALID_UINT;

  /// ID key to retrieve an association information
  typedef unsigned int AssID_t;
  /// Invalid AssID_t key value
  const AssID_t kINVALID_ASS = data::kINVALID_UINT;

  /// Association data type meant to be stored within event_X data product
  typedef std::map<product_id,AssSet_t> AssMap_t;

}
#endif
/** @} */ // end of doxygen group 
