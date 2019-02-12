#ifndef VVGOD_H_
#define VVGOD_H_
#include "VioletVrain.h"
#include "jp/ggaf/lib/DefaultGod.h"

#include "scene/VvSpacetime.h"

#undef P_GOD
#define P_GOD ((VioletVrain::VvGod*)GgafCore::God::_pGod)

namespace VioletVrain {

/**
 * 神 .
 * @version 1.00
 * @since 2012/02/16
 * @author Masatoshi Tsuge
 */
class VvGod : public GgafLib::DefaultGod {

public:
    /**
     * コンストラクタ .
     */
    VvGod();

    /**
     * この世生成方法の実装 .
     * 神クラスを作成するには、「この世」の生成方法を実装する必要があります。
     * @return 生成した「この世」
     */
    GgafCore::Spacetime* createSpacetime() override;

    virtual VvSpacetime* getSpacetime() override {  //共変の戻り値
        return (VvSpacetime*)_pSpacetime;
    }

    virtual ~VvGod();
};

}
#endif /*VVGOD_H_*/
