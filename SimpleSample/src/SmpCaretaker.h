#ifndef SMPCARETAKER_H_
#define SMPCARETAKER_H_
#include "SimpleSample.h"
#include "jp/ggaf/lib/DefaultCaretaker.h"

#undef pCARETAKER
#define pCARETAKER ((SimpleSample::SmpCaretaker*)GgafCore::Caretaker::ask())

namespace SimpleSample {

/**
 * 管理者の雛形 .
 * GgafLib::DefaultCaretaker を継承し、管理者クラスを作成して下さい。<BR>
 * その際、GgafCore::Spacetime* createSpacetime() をオーバーライドし、実装して下さい。<BR>
 * @version 1.00
 * @since 2012/02/16
 * @author Masatoshi Tsuge
 */
class SmpCaretaker : public GgafLib::DefaultCaretaker {

public:
    /**
     * コンストラクタ .
     */
    SmpCaretaker();

    /**
     * この世生成方法の実装 .
     * 管理者クラスを作成するには、「この世」の生成方法を実装する必要があります。
     * @return 生成した「この世」
     */
    GgafCore::Spacetime* createSpacetime() override;

    virtual ~SmpCaretaker();
};

}
#endif /*SMPCARETAKER_H_*/
