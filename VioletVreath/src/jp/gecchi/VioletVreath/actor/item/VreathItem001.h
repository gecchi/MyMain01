#ifndef VREATHITEM001_H_
#define VREATHITEM001_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/item/VreathItem.h"

namespace VioletVreath {

/**
 * VreathâÒïúÉAÉCÉeÉÄè¨ .
 * @version 1.00
 * @since 2011/11/21
 * @author Masatoshi Tsuge
 */
class VreathItem001 : public VreathItem {

public:
    VreathItem001(const char* prm_name);

    void initialize() override;

    virtual ~VreathItem001();
};

}
#endif /*VREATHITEM001_H_*/

