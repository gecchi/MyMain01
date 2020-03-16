#ifndef GGAF_DX_PUPPETEER_H_
#define GGAF_DX_PUPPETEER_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/core/Object.h"
#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/core/util/AccelerationValue.hpp"
#include <vector>
#include <d3dx9.h>
#include <d3dx9anim.h>
#ifdef __GNUG__
    #undef __in
    #undef __out
#endif

namespace GgafDx {

/**
 * パペッター(操り人形遣い) .
 * パペッターは、糸で吊るされたパペット(BoneAniMeshActor)を操り棒で操り、<BR>
 * 様々な芸(アニメーション)を演じさせることが出来る人(オブジェクト)です。<BR>
 * 残念ながら、パペットは同時に2種類の芸までしか演じさせる事が出来ません。<BR>
 * 理由は、パペッターの腕が２本しか無いからです。しかたないですね。<BR>
 * 両手を駆使して、パペットをうまく操ってください。<BR>
 * <BR>
 * 内部的には、このクラスは、ID3DXAnimationController のラッパークラスです。<BR>
 * 最大トラック数は 2 です。
 * 主な特徴は、<BR>
 * ① アニメーション「スピード」及び「重み」は、本来アニメーショントラックが持つ属性値だが、<BR>
 *    これを、AnimationSet 毎に紐付けて管理。<BR>
 *    アニメーション切替時に、アニメーションに紐づく「スピード」及び「重み」を
 *    トラックに設定するようにしている。<BR>
 * ② 逆再生、ループ等の機能実装<BR>
 * です。
 * @version 1.00
 * @since 2011/02/22
 * @author Masatoshi Tsuge
 */
class Puppeteer : public GgafCore::Object {
private:
    /** [r]パペットのアニメーションコントローラー */
    ID3DXAnimationController* _pAc;
//    FLOAT _track_speed;
    /**
     * 芸(モーション) .
     */
    class Performance {
    public:
        /** アニメーションセット */
        LPD3DXANIMATIONSET _pAnimationSet;
        UINT _animation_set_index;
        double _period;
        /** １ループの時間 */
        frame _one_loop_frames;
        /** ローカルタイム */
        GgafCore::AccelerationValue<double> _local_time;
//        double _local_time_inc;
        /** 目標ループ回数(1.5回などの指定も可能) */
        double _target_loop;

        double _loop_count;
        GgafCore::AccelerationValue<double> _weight;
        /** ループ方法 */
        PuppeteerMethod _method;
    public:
        Performance();
        void setAnimationSet(LPD3DXANIMATIONSET prm_pAnimationSet, UINT prm_animation_set_index);
        virtual ~Performance();
    };

    /** パペッターの操り棒 */
    struct Stick {
        /** 操り棒番号(アニメーショントラック番号) */
        UINT _tno;
        /** モーションブレンド有効無効 */
        BOOL _enable_motion_blend;
        /** パペッターの操り棒の先にくっついてる持ちネタ(芸) */
        Performance* _pPerformance;
    };

public:
    /** [r/w]パペットの持ちネタ(芸) */
    Performance* _paPerformances;
    /** [r]パペットの持ちネタ(芸)の数 */
    UINT _num_perform;
    /** [r/w]左手用、右手用のパペッターの操り棒(アニメーショントラック)  [0]:左手用／[1]:右手用  */
    Stick _aStick[2];
    ID3DXAnimationSet* _paAs[2];
public:
    /**
     * コンストラクタ .
     * @param prm_pPuppet 操られる者
     * @return
     */
    explicit Puppeteer(ID3DXAnimationController* prm_pAc_cloned);

//    void restore(ID3DXAnimationController* prm_pAc_cloned);

    /**
     * プレイしてもらう（＝パペットが操られる） .
     * @param prm_handed プレイするパペッターの操り棒 (LEFT_HAND or RIGHT_HAND)
     * @param prm_performance_no プレイする芸番号（アニメーションコントローラーのアニメーションセットIDに一致する）
     * @param prm_loopnum その芸のループ回数 0.0 ～ (１回半ループを1.5というようにも指定可能。負の数指定(-1)で無限ループアニメーション)
     * @param prm_target_speed 目標スピード割合 通常は -1.0 ～ 0.0 ～ 1.0 (1.0で通常スピード、それ以上も可能。負の値指定で逆アニメーションになる)
     * @param prm_shift_speed_frames 目標スピード割合への到達フレーム数。徐々にスピード変化します。(0 を指定で即時 prm_target_speed になる)
     * @param prm_target_weight 目標重み（＝アニメーション合成割合） 0.0 ～ 1.0 (負の数不可)
     * @param prm_shift_weight_frames 目標重へみ到達フレーム数、徐々に重みが変化する。(0 を指定で即時 prm_target_weight になる)
     * @param prm_method
     */


    /**
     *プレイしてもらう（＝パペットが操られる） .
     * @param prm_handed プレイするパペッターの操り棒 (LEFT_HAND or RIGHT_HAND)
     * @param prm_performance_no プレイする芸番号（アニメーションコントローラーのアニメーションセットIDに一致する）
     * @param prm_one_loop_frames その芸の１ループに費やすフレーム数
     * @param prm_loopnum その芸のループ回数 0.0 ～ (１回半ループを1.5というようにも指定可能。負の数指定(-1)で無限ループアニメーション)
     * @param prm_method
     */
    void play(PuppeteerStick prm_handed,
              UINT prm_performance_no,
              frame prm_one_loop_frames,
              double prm_loopnum,
              PuppeteerMethod prm_method = PLAY_LOOPING
    );

    /**
     * パペッターの右手芸と左手芸を交換 .
     */
    void exchangPerformance();

    void stop();

    virtual void behave();
    virtual void updateAnimationTrack();

    virtual int getPerformanceNum() {
        return _num_perform;
    }

    virtual ~Puppeteer();

};

}
#endif /*GGAF_DX_PUPPETEER_H_*/
