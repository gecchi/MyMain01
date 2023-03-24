#ifndef VVCARETAKER_H_
#define VVCARETAKER_H_
#include "jp/gecchi/VioletVrain/VioletVrain.h"
#include "jp/ggaf/lib/DefaultCaretaker.h"

#include "scene/VvSpacetime.h"

#undef pCARETAKER
#define pCARETAKER ((VioletVrain::VvCaretaker*)GgafCore::Caretaker::_pCaretaker)

namespace VioletVrain {

/**
 * 管理者 .
 * @version 1.00
 * @since 2012/02/16
 * @author Masatoshi Tsuge
 */
class VvCaretaker : public GgafLib::DefaultCaretaker {

public:
    /**
     * コンストラクタ .
     */
    VvCaretaker();

    /**
     * この世生成方法の実装 .
     * 管理者クラスを作成するには、「この世」の生成方法を実装する必要があります。
     * @return 生成した「この世」
     */
    GgafCore::Spacetime* createSpacetime() override;

    virtual VvSpacetime* getSpacetime() override {  //共変の戻り値
        return (VvSpacetime*)_pSpacetime;
    }

    virtual ~VvCaretaker();
};

}
#endif /*VVCARETAKER_H_*/
