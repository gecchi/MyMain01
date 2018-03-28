#ifndef VVGOD_H_
#define VVGOD_H_
#include "VioletVrain.h"
#include "jp/ggaf/lib/DefaultGod.h"

#include "scene/VvSpacetime.h"

#undef P_GOD
#define P_GOD ((VioletVrain::VvGod*)GgafCore::GgafGod::_pGod)

namespace VioletVrain {

/**
 * 神の雛形 .
 * GgafLib::DefaultGod を継承し、神クラスを作成して下さい。<BR>
 * その際、GgafCore::GgafSpacetime* createSpacetime() をオーバーライド＆実装して下さい。<BR>
 * @version 1.00
 * @since 2012/02/16
 * @author Masatoshi Tsuge
 */
class VvGod : public GgafLib::DefaultGod {

public:
    /**
     * コンストラクタ .
     * @param prm_hInstance インスタンスハンドル
     * @param prm_hWnd1 １画面目ウインドウハンドル
     * @param prm_hWnd2 ２画面目ウインドウハンドル
     */
    VvGod();

    /**
     * この世生成方法の実装 .
     * 神クラスを作成するには、「この世」の生成方法を実装する必要があります。
     * @return 生成した「この世」
     */
    GgafCore::GgafSpacetime* createSpacetime() override;

    virtual VvSpacetime* getSpacetime() override {  //共変の戻り値
        return (VvSpacetime*)_pSpacetime;
    }

    virtual ~VvGod();
};

}
#endif /*VVGOD_H_*/
