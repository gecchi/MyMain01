#ifndef GOD_H_
#define GOD_H_
namespace SimpleSample {

/**
 * 神の雛形 .
 * GgafLib::DefaultGod を継承し、神クラスを作成して下さい。<BR>
 * その際、GgafCore::GgafUniverse* createUniverse() をオーバーライドし、実装して下さい。<BR>
 * @version 1.00
 * @since 2012/02/16
 * @author Masatoshi Tsuge
 */
class God : public GgafLib::DefaultGod {

public:
    /**
     * コンストラクタ .
     * @param prm_hInstance インスタンスハンドル
     * @param prm_hWnd1 １画面目ウインドウハンドル
     * @param prm_hWnd2 ２画面目ウインドウハンドル
     */
    God(HINSTANCE prm_hInstance, HWND prm_hWnd1, HWND prm_hWnd2);

    /**
     * この世生成方法の実装 .
     * 神クラスを作成するには、「この世」の生成方法を実装する必要があります。
     * @return 生成した「この世」
     */
    GgafCore::GgafUniverse* createUniverse() override;

    virtual ~God();
};

}
#endif /*GOD_H_*/
