#ifndef MAGICPOINTITEM002_H_
#define MAGICPOINTITEM002_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/item/MagicPointItem.h"

namespace VioletVreath {

/**
 * MP‰ñ•œƒAƒCƒeƒ€ ’† .
 * @version 1.00
 * @since 2011/11/21
 * @author Masatoshi Tsuge
 */
class MagicPointItem002 : public MagicPointItem {

public:
    MagicPointItem002(const char* prm_name);

    void onActive() override;

    void initialize() override;

    virtual ~MagicPointItem002();
};

}
#endif /*MAGICPOINTITEM002_H_*/

