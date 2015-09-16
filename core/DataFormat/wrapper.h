/**
 * \file wrapper.h
 *
 * \ingroup DataFormat
 * 
 * \brief Wraps data stored in ROOT
 *
 * @author W. David Dagenhart - Fermilab 2015
 */

/** \addtogroup DataFormat

    @{*/

#ifndef LARLITE_core_DataFormat_wrapper_H
#define LARLITE_core_DataFormat_wrapper_H

#include "data_base.h"

namespace larlite {

  template <typename T>
  class wrapper : public event_base {
  public:

  private:
    T obj;
  };
}
#endif
