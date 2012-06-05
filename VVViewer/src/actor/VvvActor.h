#ifndef SMPACTOR_H_
#define SMPACTOR_H_
namespace VVViewer {

/**
 * テストキャラ .
 * @version 1.00
 * @since 2012/06/05
 * @author Masatoshi Tsuge
 */
class VvvActor : public GgafLib::DefaultMeshActor {

public:
    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    VvvActor(const char* prm_name);

    /**
     * キャラの初期処理 .
     */
    void initialize() override;

    /**
     * キャラの振る舞い処理 .
     */
    void processBehavior() override;

    virtual ~VvvActor();
};

}
#endif /*SMPACTOR_H_*/

