#ifndef HGRCARETAKER_H_
#define HGRCARETAKER_H_
#include "Hogera.h"
#include "jp/ggaf/lib/DefaultCaretaker.h"

#include "scene/HgrSpacetime.h"

#undef pCARETAKER
#define pCARETAKER ((Hogera::HgrCaretaker*)GgafCore::Caretaker::_pCaretaker)

namespace Hogera {

/**
 * 管理者の雛形 .
 * GgafLib::DefaultCaretaker を継承し、管理者クラスを作成して下さい。<BR>
 * その際、GgafCore::Spacetime* createSpacetime() をオーバーライド＆実装して下さい。<BR>
 * @version 1.00
 * @since 2012/02/16
 * @author Masatoshi Tsuge
 */
class HgrCaretaker : public GgafLib::DefaultCaretaker {

public:
    /**
     * コンストラクタ .
     */
    HgrCaretaker();

    /**
     * この世生成方法の実装 .
     * 管理者クラスを作成するには、「この世」の生成方法を実装する必要があります。
     * @return 生成した「この世」
     */
    GgafCore::Spacetime* createSpacetime() override;

    virtual HgrSpacetime* getSpacetime() override {  //共変の戻り値
        return (HgrSpacetime*)_pSpacetime;
    }

    virtual ~HgrCaretaker();
};

}
#endif /*HGRCARETAKER_H_*/
