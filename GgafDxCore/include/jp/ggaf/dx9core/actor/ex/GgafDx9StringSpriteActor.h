#ifndef GGAFDX9STRINGSPRITEACTOR_H_
#define GGAFDX9STRINGSPRITEACTOR_H_
namespace GgafDx9Core {

/**
 * 座標未変換文字表示クラス（現在作成中で、未使用！）
 */
class GgafDx9StringSpriteActor : public GgafDx9SpriteSetActor {
    /** 文字数50文字まで */
    char* _buf;
    char* _draw_string;
    int _len;
public:
    /** [rw]各文字間隔(px) */
    float _aWidthPx[256];


    /**
     *
     * @param prm_name
     * @param prm_model 文字セットテクスチャのモデル
     * @return
     */
    GgafDx9StringSpriteActor(const char* prm_name, const char* prm_model, GgafCore::GgafStatus* prm_pStat);

    virtual void onCreateModel() override;

    virtual void processDraw() override;

    virtual void processAfterDraw() override {
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

    virtual ~GgafDx9StringSpriteActor();

};

}
#endif /*GGAFDX9STRINGSPRITEACTOR_H_*/
