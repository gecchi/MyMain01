#ifndef SMPUNIVERSE_H_
#define SMPUNIVERSE_H_
namespace SimpleSample {

/**
 * 「この世」の雛形 .
 * GgafLib::DefaultUniverse を継承し「この世」クラスを作成して下さい。
 * @version 1.00
 * @since 2012/02/16
 * @author Masatoshi Tsuge
 */
class SmpUniverse : public GgafLib::DefaultUniverse {

public:
    /**
     * コンストラクタ .
     * @param prm_name 名称
     * @param prm_pCam カメラオブジェクト
     */
    SmpUniverse(const char* prm_name, SmpCamera* prm_pCam);

    /**
     * 「この世」の初期処理 .
     */
    void initialize() override;

    /**
     * 「この世」の振る舞い処理 .
     */
    void processBehavior() override {}

    virtual ~SmpUniverse();
};

}
#endif /*SMPUNIVERSE_H_*/
