#ifndef UNIVERSE_H_
#define UNIVERSE_H_
namespace SimpleSample {

/**
 * 「この世」の雛形 .
 * GgafLib::DefaultUniverse を継承し「この世」クラスを作成して下さい。<BR>
 * @version 1.00
 * @since 2012/02/16
 * @author Masatoshi Tsuge
 */
class Universe : public GgafLib::DefaultUniverse {

public:

    /**
     * コンストラクタ .
     * @param prm_name 名称
     * @param prm_pCam カメラオブジェクト
     */
    Universe(const char* prm_name, Camera* prm_pCam);

    /**
     * 「この世」の初期処理 .
     */
    void initialize() override;

    /**
     * 「この世」の振る舞い処理 .
     */
    void processBehavior() override {}

    virtual ~Universe();
};

}
#endif /*UNIVERSE_H_*/
