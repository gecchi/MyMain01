#ifndef GGAFLIB_STEPPEDCOORDSPLINEKUROKOLEADER_H_
#define GGAFLIB_STEPPEDCOORDSPLINEKUROKOLEADER_H_
#include "jp/ggaf/lib/util/spline/SplineKurokoLeader.h"

namespace GgafLib {

/**
 * スプライン曲線移動 .
 * 単純に、フレーム毎に順番に補完点座標へ移動。
 * TODO:作成中！使えません！
 * @version 1.00
 * @since 2009/10/28
 * @author Masatoshi Tsuge
 */
class SteppedCoordSplineKurokoLeader : public SplineKurokoLeader {

    void restart();

public:
    SteppedCoordSplineManufacture* _pSteppedSplManuf;

    /** [r]基準速度で移動した場合のスプライン移動時の経過フレーム数 */
    float _leadning_fFrames;
    /** [r]次の変わり目となる補間点(基準点も含む)に到達する_leadning_fFrames */
    float _fFrame_of_next;
    /** [r]補完点(基準点も含む)の数 */
    int _point_index;

    //計算用
    float _sinRzMv_begin;
    float _cosRzMv_begin;
    float _sinRyMv_begin;
    float _cosRyMv_begin;

public:
    /**
     * コンストラクタ .
     * @param prm_pManufacture calculate()済みのSplineManufactureを設定すること
     * @param prm_pKuroko 対象のアクターの黒衣
     */
    SteppedCoordSplineKurokoLeader(SplineManufacture* prm_pManufacture,  GgafDxCore::GgafDxKuroko* const prm_pKuroko);

    /**
     * コンストラクタ .
     * 等速移動のための必要な情報を事前計算し、オブジェクトに溜め込みます。
     * @param prm_pKuroko 対象のアクターの黒衣
     * @param prm_sp 計算済みスプラインオブジェクト
     * @param prm_angveloRzRyMv 1フレームあたりの旋回可能な回転角角速度 (1000 が 1度)
     * @return
     */
    SteppedCoordSplineKurokoLeader(GgafDxCore::GgafDxKuroko* const prm_pKuroko,
                                    SplineLine* prm_sp,
                                    angvelo prm_angveloRzRyMv);


    void start(SplinTraceOption prm_option, int prm_max_loop = 1) override;

    /**
     * 毎フレームの振る舞いメソッド .
     * 利用者は毎フレームこのメソッドを呼び出す必要があります。
     */
    void behave() override;


    virtual ~SteppedCoordSplineKurokoLeader();
};

}
#endif /*GGAFLIB_FIXEDVELOCITYSPLINEKUROKOLEADER_H_*/
