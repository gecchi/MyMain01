#ifndef GGAFDX9PUPPETEER_H_
#define GGAFDX9PUPPETEER_H_

#define LEFT_HANDED 0
#define RIGHT_HANDED 1

namespace GgafDx9Core {

/**
 * パペッター(操り人形遣い) .
 * パペッターは、糸で吊るされたパペット(GgafDx9D3DXAniMeshActor)を操り棒で操り、<BR>
 * 様々な芸(アニメーション)を演じさせることが出来る人です。<BR>
 * 残念ながら、パペットは同時に2種類の芸までしか演じる事が出来ません。<BR>
 * 理由は、パペッターの腕が２本しか無いからです。しかたないですね。<BR>
 * 両手を駆使して、パペットをうまく操ってください。<BR>
 * <BR>
 * そして、このクラスは、ID3DXAnimationController のラッパークラスです。<BR>
 * 最大トラック数は 2 です。
 * 主な特徴は、<BR>
 * ① トラックが持つ属性値を、AnimationSet 毎に持たせるようにした。<BR>
 * ② 逆再生、ループ無し、等の機能<BR>
 * です。
 * @version 1.00
 * @since 2011/02/22
 * @author Masatoshi Tsuge
 */
class GgafDx9Puppeteer : public GgafCore::GgafObject {
private:
    /**
     * 芸(モーション) .
     */
    struct Performance {
        LPD3DXANIMATIONSET _pAnimationSet;
        GgafDx9MotionMethod _method;
        bool _is_playing;
        double _total_time;
        double _local_time;
        double _target_time;
        double _speed;
        double _weight;
    };

    struct Stick {
        UINT _no;
        Performance* _pPerformance;
    };
public:
    /** パペット */
    GgafDx9D3DXAniMeshActor* _pPuppet;
    GgafDx9D3DXAniMeshModel* _pModel;
    ID3DXAnimationController* _pAc;

    /** 持ちネタ芸 */
    Performance* _paPerformances;
    UINT _num_tricks;
    /** パペッターの操り棒  [0]:左手用／[1]:右手用  */
    Stick _aStick[2];
    /** アクティブな操り棒 */
    Stick* _pStickActive;

    double _advance_time_per_draw;

    /**
     * コンストラクタ .
     * @param prm_pActor 操られる者
     * @return
     */
    GgafDx9Puppeteer(GgafDx9D3DXAniMeshActor* prm_pPuppet);


    virtual ~GgafDx9Puppeteer();

    void setStickSpeed(double prm_speed);

    void play(UINT performance_no, GgafDx9MotionMethod method);

    void play();
    void stop();


    virtual void behave();
    virtual void work();


};

}
#endif /*GGAFDX9PUPPETEER_H_*/
