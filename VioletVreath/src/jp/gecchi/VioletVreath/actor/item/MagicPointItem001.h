#ifndef MAGICPOINTITEM001_H_
#define MAGICPOINTITEM001_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/item/MagicPointItem.h"

namespace VioletVreath {

/**
 * MPâÒïúÉAÉCÉeÉÄè¨ .
 * @version 1.00
 * @since 2011/02/04
 * @author Masatoshi Tsuge
 */
class MagicPointItem001 : public MagicPointItem {

public:
    MagicPointItem001(const char* prm_name);

    void initialize() override;

    virtual ~MagicPointItem001();
};

}
#endif /*MAGICPOINTITEM001_H_*/

