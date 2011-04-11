#ifndef GGAFDX9PUPPETEER_H_
#define GGAFDX9PUPPETEER_H_

namespace GgafDx9Core {

/**
 * パペッター(操り人形遣い) .
 * パペッターは、糸で吊るされたパペット(GgafDx9D3DXAniMeshActor)を操り棒で操り、<BR>
 * 様々な芸(アニメーション)を演じさせることが出来る人(オブジェクト)です。<BR>
 * 残念ながら、パペットは同時に2種類の芸までしか演じさせる事が出来ません。<BR>
 * 理由は、パペッターの腕が２本しか無いからです。しかたないですね。<BR>
 * 両手を駆使して、パペットをうまく操ってください。<BR>
 * <BR>
 * 内部的には、このクラスは、ID3DXAnimationController のラッパークラスです。<BR>
 * 最大トラック数は 2 です。
 * 主な特徴は、<BR>
 * �@ アニメーション「スピード」及び「重み」は、本来アニメーショントラックが持つ属性値だが、<BR>
 *    これを、AnimationSet 毎に紐付けて管理。<BR>
 *    アニメーション切替時に、アニメーションに紐づく「スピード」及び「重み」を
 *    トラックに設定するようにしている。<BR>
 * �A 逆再生、ループ等の機能実装<BR>
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
        /** アニメーションセット */
        LPD3DXANIMATIONSET _pAnimationSet;
        /** １ループの時間 */
        double _time_of_one_loop;
        /** ローカルタイム */
        double _local_time;
        /** 目標ループ回数(1.5回などの指定も可能) */
        double _target_loop;
        /** 目標到達スピード割合(1.0で通常スピード、負で逆アニメーション) */
        double _target_speed;
        /** 現在のスピード割合 */
        double _speed;
        /** スピード割合の加算値 */
        double _inc_speed;
        /** スピード割合を加算中ならば true */
        bool   _is_shifting_speed;
        /** 目標到達重み 0.0〜1.0(負は不可) */
        double _target_weight;
        /** 現在の重み */
        double _weight;
        /** 重みの加算値 */
        double _inc_weight;
        /** 重みを加算中ならば true */
        bool   _is_shifting_weight;
        /** ループ方法 */
        GgafDx9PuppeteerPlayMethod _method;
    };

    /** パペッターの操り棒 */
    struct Stick {
        UINT _no;
        Performance* _pPerformance;
    };

    /** パペットのモデル */
    GgafDx9D3DXAniMeshModel* _pModel;
    /** パペットのアニメーションコントローラー */
    ID3DXAnimationController* _pAc;

public:
    /** パペット */
    GgafDx9D3DXAniMeshActor* _pPuppet;
    /** パペットの持ちネタ(芸) */
    Performance* _paPerformances;
    /** パペットの持ちネタ(芸)の数 */
    UINT _num_perform;
    /** 左手用、右手用のパペッターの操り棒  [0]:左手用／[1]:右手用  */
    Stick _aStick[2];

    /**
     * コンストラクタ .
     * @param prm_pActor 操られる者
     * @return
     */
    GgafDx9Puppeteer(GgafDx9D3DXAniMeshActor* prm_pPuppet);


    /**
     * プレイしてもらう（＝パペットが操られる） .
     * @param prm_handed プレイするパペッターの操り棒 (LEFT_HAND or RIGHT_HAND)
     * @param prm_prm_performance_no プレイする芸番号（アニメーションコントローラーのアニメーションセットIDに一致する）
     * @param prm_loopnum その芸のループ回数 0.0 〜 (１回半ループを1.5というようにも指定可能。負の数指定(-1)で無限ループアニメーション)
     * @param prm_target_speed 目標スピード割合 通常は -1.0 〜 0.0 〜 1.0 (1.0で通常スピード、それ以上も可能。負の値指定で逆アニメーションになる)
     * @param prm_frame_duaration_of_shift_speed 目標スピード割合への到達フレーム数。徐々にスピード変化します。(0 を指定で即時 prm_target_speed になる)
     * @param prm_target_weight 目標重み（＝アニメーション合成割合） 0.0 〜 1.0 (負の数不可)
     * @param prm_frame_duaration_of_shift_weight 目標重へみ到達フレーム数、徐々に重みが変化する。(0 を指定で即時 prm_target_weight になる)
     * @param prm_method
     */
    void play(GgafDx9PuppeteerStick prm_handed,
              UINT prm_prm_performance_no,
              double prm_loopnum,
              double prm_target_speed,
              frame prm_frame_duaration_of_shift_speed,
              double prm_target_weight,
              frame prm_frame_duaration_of_shift_weight,
              GgafDx9PuppeteerPlayMethod prm_method = NO_CHENGE
    );

    /**
     * パペッターの右手芸と左手芸を交換 .
     */
    void exchangPerformance();

    void unpause(GgafDx9PuppeteerStick prm_handed);
    void pause(GgafDx9PuppeteerStick prm_handed);
    void stop();

    virtual void behave();
    virtual void work();
    virtual ~GgafDx9Puppeteer();

};

}
#endif /*GGAFDX9PUPPETEER_H_*/
