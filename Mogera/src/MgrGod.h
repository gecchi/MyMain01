#ifndef MGRGOD_H_
#define MGRGOD_H_
#include "Mogera.h"
#include "jp/ggaf/lib/DefaultGod.h"

#include "scene/MgrSpacetime.h"

#undef pGOD
#define pGOD ((Mogera::MgrGod*)GgafCore::God::_pGod)

namespace Mogera {

/**
 * 神の雛形 .
 * GgafLib::DefaultGod を継承し、神クラスを作成して下さい。<BR>
 * その際、GgafCore::Spacetime* createSpacetime() をオーバーライド＆実装して下さい。<BR>
 * @version 1.00
 * @since 2012/02/16
 * @author Masatoshi Tsuge
 */
class MgrGod : public GgafLib::DefaultGod {

public:
    /**
     * コンストラクタ .
     * @param prm_hInstance インスタンスハンドル
     * @param prm_hWnd1 １画面目ウインドウハンドル
     * @param prm_hWnd2 ２画面目ウインドウハンドル
     */
    MgrGod();

    /**
     * この世生成方法の実装 .
     * 神クラスを作成するには、「この世」の生成方法を実装する必要があります。
     * @return 生成した「この世」
     */
    GgafCore::Spacetime* createSpacetime() override;

    virtual MgrSpacetime* getSpacetime() override {  //共変の戻り値
        return (MgrSpacetime*)_pSpacetime;
    }

    virtual ~MgrGod();
};

}
#endif /*MGRGOD_H_*/
