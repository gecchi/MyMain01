#ifndef SMPGOD_H_
#define SMPGOD_H_
#include "SimpleSample.h"
#include "jp/ggaf/lib/DefaultGod.h"

#include "jp/ggaf/lib/util/VirtualButton.h"

#undef pGOD
#define pGOD ((SimpleSample::SmpGod*)GgafCore::God::ask())

namespace SimpleSample {

/**
 * 神の雛形 .
 * GgafLib::DefaultGod を継承し、神クラスを作成して下さい。<BR>
 * その際、GgafCore::Spacetime* createSpacetime() をオーバーライドし、実装して下さい。<BR>
 * @version 1.00
 * @since 2012/02/16
 * @author Masatoshi Tsuge
 */
class SmpGod : public GgafLib::DefaultGod {

public:
    /** 仮想ボタンオブジェクト */
    GgafLib::VirtualButton vb_;

    /**
     * コンストラクタ .
     */
    SmpGod();

    /**
     * この世生成方法の実装 .
     * 神クラスを作成するには、「この世」の生成方法を実装する必要があります。
     * @return 生成した「この世」
     */
    GgafCore::Spacetime* createSpacetime() override;

    /**
     * 仮想ボタンオブジェクトを返す .
     * @return 仮想ボタン
     */
    GgafLib::VirtualButton* getVB() {
        return &vb_;
    }

    virtual ~SmpGod();
};

}
#endif /*SMPGOD_H_*/
