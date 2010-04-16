#ifndef GGAFDX9STRINGBOARDACTOR_H_
#define GGAFDX9STRINGBOARDACTOR_H_
namespace GgafDx9Core {

/**
 * 文字表示クラス(座標変換済み).
 * GgafDx9BoardActor を継承し、文字セットテクスチャーから文字表示機能を追加したアクターです。
 * @version 1.00
 * @since 2009/04/09
 * @author Masatoshi Tsuge
 */
class GgafDx9StringBoardActor : public GgafDx9BoardSetActor {
    /** 文字数50文字まで */
    char* _buf;
    char* _draw_string;
    int _len;
public:
    /**
     *
     * @param prm_name
     * @param prm_model 文字セットテクスチャのモデル
     * @return
     */
    GgafDx9StringBoardActor(const char* prm_name, const char* prm_model);

    virtual void onCreateModel() override {
    }

    virtual void initialize() override {
    }

    virtual void processBehavior() override {
    }

    virtual void processJudgement() override {
    }

    virtual void processDraw() override; //オーバーライド

    virtual void processAfterDraw() override {
    }

    virtual void processHappen(int prm_no) override {
    }

    virtual void processFinal() override {
    }

    virtual bool processHitChkLogic(GgafCore::GgafActor* prm_pOtherActor) {
        return false;
    }

    virtual void onHit(GgafCore::GgafActor* prm_pOtherActor) {
    }


    virtual void update(float prm_x, float prm_y, const char* prm_str);
    virtual void update(float prm_x, float prm_y, char* prm_str);
    virtual void update(float prm_x, float prm_y, float prm_z, const char* prm_str);
    virtual void update(float prm_x, float prm_y, float prm_z, char* prm_str);
    virtual void update(const char* prm_str);
    virtual void update(char* prm_str);

    virtual ~GgafDx9StringBoardActor();

};

}
#endif /*GGAFDX9STRINGBOARDACTOR_H_*/
