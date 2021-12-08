#ifndef GGAF_DX_PUPPETEER_H_
#define GGAF_DX_PUPPETEER_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/core/Object.h"
#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/core/util/TransitionValue.hpp"
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
class Puppeteer : public GgafCore::Object {
private:
    /** [r]パペットのアニメーションコントローラー */
    ID3DXAnimationController* _pAc;
    /**
     * 芸(モーション) .
     * ID3DXAnimationSetラッパー
     */
    class Performance {
    public:
        /** アニメーションセット */
        LPD3DXANIMATIONSET _pAnimationSet;
        UINT _animation_set_index;
        double _period;
        /** ローカルタイム */
//        GgafCore::TrapezoidalVeloValue<double> _local_time;
        double _p1;
        double _p2;
        /** 目標ループ回数(1.5回などの指定も可能) */
        double _target_loop;

        double _loop_count;
//        GgafCore::TrapezoidalVeloValue<double> _weight;
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
        /** パペッターの操り棒の先にくっついてる持ちネタ(芸) */
        Performance* _pPerformance;

        GgafCore::TransitionValue<double> _weight;
    };

public:
    /** [r/w]パペットの持ちネタ(芸) */
    Performance* _paPerformances;
    /** [r]パペットの持ちネタ(芸)の数、AnimationSet の数 */
    UINT _num_perform;
    /** [r/w]左手用、右手用のパペッターの操り棒(アニメーショントラック)  [0]:左手用／[1]:右手用  */
    Stick*  _pStickMain;
    Stick*  _pStickSub;
    Stick* _apStick[2];
    /** [r]現在のトラックに設定されているアニメーションセット。未設定の場合はnullptr。[0]:トラック0／[1]トラック1 */
   ID3DXAnimationSet* _paAs[2];

    /** アニメーションコントローラのデフォルトの１フレームあたりのアニメーションフレーム */
    double _ani_time_delta;

    double _advance_time;
public:
    /**
     * コンストラクタ .
     * @param prm_pPuppet 操られる者
     * @return
     */
    explicit Puppeteer(ID3DXAnimationController* prm_pAc_cloned,
                       double prm_ani_time_delta = 60.0 / 4800);


//    void perform(UINT prm_performance_no, double prm_loopnum);

    /**
     * プレイしてもらう（＝パペットが操られる） .
     * @param prm_performance_no プレイする芸番号（アニメーションコントローラーのアニメーションセットIDに一致する）
     */
    void play(UINT prm_performance_no);



    void switchTo(UINT prm_performance_no, frame prm_switch_frames = 120);


    void playPartly(UINT prm_performance_no, frame prm_spend_frames = 180);
    void playPartly2(UINT prm_performance_no, int prm_loop);

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
