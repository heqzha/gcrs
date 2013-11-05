/*
 * GCRSBaseComVin.h
 *
 *  Created on: Aug 1, 2013
 *      Author: tony
 */

#ifndef GCRSBASECOMVIN_H_
#define GCRSBASECOMVIN_H_

class GCRSBaseComVin {
public:
    typedef long VinL3Type;
    /** @brief Broadcast vin for L3. */
    static const VinL3Type VINL3BROADCAST;
    /** @brief NULL vin for L3. */
    static const VinL3Type VINL3NULL;

public:
    static inline bool isVinL3Broadcast(const VinL3Type& pSrcVin) {
        return pSrcVin == VINL3BROADCAST;
    }
    static inline bool isVinL3NULL(const VinL3Type& pSrcVin) {
        return pSrcVin == VINL3NULL;
    }
};

#endif /* GCRSBASECOMVIN_H_ */
