#ifndef GGAFDXSTRINGSPRITEACTOR_H_
#define GGAFDXSTRINGSPRITEACTOR_H_
namespace GgafDxCore {

/**
 * 座標未変換文字表示クラス（現在作成中で、未使用！）
 */
class GgafDxStringSpriteActor : public GgafDxSpriteSetActor {
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
     * @param prm_model  文字セットテクスチャのモデル
     * @param prm_pStat
     */
    GgafDxStringSpriteActor(const char* prm_name, const char* prm_model, GgafCore::GgafStatus* prm_pStat);

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

    virtual ~GgafDxStringSpriteActor();

};

}
#endif /*GGAFDXSTRINGSPRITEACTOR_H_*/
