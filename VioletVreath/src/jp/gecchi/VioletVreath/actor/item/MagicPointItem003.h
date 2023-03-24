#ifndef MAGICPOINTITEM003_H_
#define MAGICPOINTITEM003_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/item/MagicPointItem.h"

namespace VioletVreath {

/**
 * MP‰ñ•œƒAƒCƒeƒ€ ‘å .
 * @version 1.00
 * @since 2013/09/05
 * @author Masatoshi Tsuge
 */
class MagicPointItem003 : public MagicPointItem {

public:
    MagicPointItem003(const char* prm_name);

    void onActive() override;

    void initialize() override;

    virtual ~MagicPointItem003();
};

}
#endif /*MAGICPOINTITEM003_H_*/

