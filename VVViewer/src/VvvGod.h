#ifndef VVVGOD_H_
#define VVVGOD_H_
#include "jp/ggaf/lib/DefaultGod.h"


#undef P_GOD
#define P_GOD ((VVViewer::VvvGod*)VVViewer::VvvGod::_pGod)

namespace VVViewer {

/**
 * VVViewer神 .
 * @version 1.00
 * @since 2012/06/05
 * @author Masatoshi Tsuge
 */
class VvvGod : public GgafLib::DefaultGod {

public:
    static bool is_wm_dropfiles_;
    static char dropfiles_[2048];

public:
    /**
     * コンストラクタ .
     * @param prm_hInstance インスタンスハンドル
     * @param prm_hWnd1 １画面目ウインドウハンドル
     * @param prm_hWnd2 ２画面目ウインドウハンドル
     */
    VvvGod(HINSTANCE prm_hInstance, HWND prm_hWnd1, HWND prm_hWnd2);

    /**
     * この世生成方法の実装 .
     * 神クラスを作成するには、「この世」の生成方法を実装する必要があります。
     * @return 生成した「この世」
     */
    GgafCore::GgafUniverse* createUniverse() override;

    virtual ~VvvGod();
};

}
#endif /*VVVGOD_H_*/
