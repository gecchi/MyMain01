#ifndef MGRCARETAKER_H_
#define MGRCARETAKER_H_
#include "Mogera.h"
#include "jp/ggaf/lib/DefaultCaretaker.h"

#include "scene/MgrSpacetime.h"

#undef pCARETAKER
#define pCARETAKER ((Mogera::MgrCaretaker*)GgafCore::Caretaker::_pCaretaker)

namespace Mogera {

/**
 * 管理者の雛形 .
 * GgafLib::DefaultCaretaker を継承し、管理者クラスを作成して下さい。<BR>
 * その際、GgafCore::Spacetime* createSpacetime() をオーバーライド＆実装して下さい。<BR>
 * @version 1.00
 * @since 2012/02/16
 * @author Masatoshi Tsuge
 */
class MgrCaretaker : public GgafLib::DefaultCaretaker {

public:
    /**
     * コンストラクタ .
     */
    MgrCaretaker();

    /**
     * この世生成方法の実装 .
     * 管理者クラスを作成するには、「この世」の生成方法を実装する必要があります。
     * @return 生成した「この世」
     */
    GgafCore::Spacetime* createSpacetime() override;

    virtual MgrSpacetime* getSpacetime() override {  //共変の戻り値
        return (MgrSpacetime*)_pSpacetime;
    }

    virtual ~MgrCaretaker();
};

}
#endif /*MGRCARETAKER_H_*/
