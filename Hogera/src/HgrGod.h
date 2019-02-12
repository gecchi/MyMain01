#ifndef HGRGOD_H_
#define HGRGOD_H_
#include "Hogera.h"
#include "jp/ggaf/lib/DefaultGod.h"

#include "scene/HgrSpacetime.h"

#undef P_GOD
#define P_GOD ((Hogera::HgrGod*)GgafCore::God::_pGod)

namespace Hogera {

/**
 * 神の雛形 .
 * GgafLib::DefaultGod を継承し、神クラスを作成して下さい。<BR>
 * その際、GgafCore::Spacetime* createSpacetime() をオーバーライド＆実装して下さい。<BR>
 * @version 1.00
 * @since 2012/02/16
 * @author Masatoshi Tsuge
 */
class HgrGod : public GgafLib::DefaultGod {

public:
    /**
     * コンストラクタ .
     * @param prm_hInstance インスタンスハンドル
     * @param prm_hWnd1 １画面目ウインドウハンドル
     * @param prm_hWnd2 ２画面目ウインドウハンドル
     */
    HgrGod();

    /**
     * この世生成方法の実装 .
     * 神クラスを作成するには、「この世」の生成方法を実装する必要があります。
     * @return 生成した「この世」
     */
    GgafCore::Spacetime* createSpacetime() override;

    virtual HgrSpacetime* getSpacetime() override {  //共変の戻り値
        return (HgrSpacetime*)_pSpacetime;
    }

    virtual ~HgrGod();
};

}
#endif /*HGRGOD_H_*/
