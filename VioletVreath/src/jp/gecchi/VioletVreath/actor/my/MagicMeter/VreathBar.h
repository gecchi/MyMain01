#ifndef VREATHBAR_H_
#define VREATHBAR_H_
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/GraphBar.h"

namespace VioletVreath {

/**
 * VreathBar .
 * @version 1.00
 * @since 2012/05/11
 * @author Masatoshi Tsuge
 */
class VreathBar :  public GraphBar {

public:
    /**
     *
     * @param prm_name
     * @param prm_pAmount config済みの AmountGraphオブジェクトの参照
     */
    VreathBar(const char* prm_name, GgafLib::AmountGraph* prm_pAmount);

    void initialize() override;

    void addVal(double prm_val);

    virtual ~VreathBar();
};

}
#endif /*VREATHBAR_H_*/

