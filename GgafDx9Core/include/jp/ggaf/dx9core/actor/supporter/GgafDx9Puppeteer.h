#ifndef GGAFDX9PUPPETEER_H_
#define GGAFDX9PUPPETEER_H_
namespace GgafDx9Core {

/**
 * パペッター(操り人形遣い) .
 * パペット(GgafDx9D3DXAniMeshActor)を糸で操り、モーションを演じさせます。<BR>
 * パペットに対して同時に2種類のモーションまでしか出来ません(＝最大トラックは2)<BR>
 * 人形遣いさんも腕は２本しか無いので、そこはしかたないですネ。<BR>
 * 両手を駆使して、パペットをうまく操ってください。<BR>
 * つまり、ID3DXAnimationController ラッパークラスです。<BR>
 * @version 1.00
 * @since 2011/02/22
 * @author Masatoshi Tsuge
 */
class GgafDx9Puppeteer : public GgafCore::GgafObject {
private:

public:
    /** 操られる者 */
    GgafDx9D3DXAniMeshActor* _pPuppet;
    GgafDx9D3DXAniMeshModel* _pModel;
    ID3DXAnimationController* _pAc;

    LPD3DXANIMATIONSET* _papAnimationSet;
    double* _pa_as_anime_time;
    float* _pa_as_anime_speed;
    float* _pa_as_weight;

    UINT _num_animation_set;
    UINT _num_tracks;

    /** アクティブな手 0:右手／1:左手 */
    UINT _hand;

    double _advance_time_per_draw;

    /**
     * コンストラクタ .
     * @param prm_pActor 操られる者
     * @return
     */
    GgafDx9Puppeteer(GgafDx9D3DXAniMeshActor* prm_pPuppet);


    virtual ~GgafDx9Puppeteer();

    void play(UINT anim_set_id);
    void play();
    void stop();


    virtual void behave();
    virtual void work();


};

}
#endif /*GGAFDX9PUPPETEER_H_*/
