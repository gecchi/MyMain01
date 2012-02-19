#ifndef WORLD_H_
#define WORLD_H_
namespace SimpleSample {

/**
 * 世界シーンの雛形 .
 * GgafLib::DefaultScene を継承してシーンクラスを作成して下さい。<BR>
 * 本サンプルでは「世界」シーンと名づけました。<BR>
 * processBehavior() をオーバーライドし、毎フレームの処理を記述します。<BR>
 * @version 1.00
 * @since 2012/02/16
 * @author Masatoshi Tsuge
 */
class World : public GgafLib::DefaultScene {

public:
    /** 入力受付 */
    GgafLib::VirtualButton _vb;
    /** テストキャラ */
    TestActor* _pActor;

    /**
     * コンストラクタ .
     * @param prm_name 名称
     */
    World(const char* prm_name);

    /**
     * 世界シーンの初期処理 .
     */
    void initialize() override {}

    /**
     * 世界シーンの振る舞い処理 .
     */
    void processBehavior() override;

    virtual ~World();
};

}
#endif /*WORLD_H_*/
