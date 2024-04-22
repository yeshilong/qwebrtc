#ifndef RTCI420BUFFER_H
#define RTCI420BUFFER_H

#include "rtcyuvplanarbuffer.h"

/**
 * @brief Provides methods for handling I420 data.
 */
class IRTCI420Buffer : public IRTCYUVPlanarBuffer
{
};

/**
 * @brief Implements the IRTCI420Buffer interface.
 */
class RTCI420Buffer : public IRTCI420Buffer
{
  public:
    RTCI420Buffer();
};

#endif // RTCI420BUFFER_H
