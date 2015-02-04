#ifndef GGAFLIB_STEPPEDCOORDSPLINEKUROKOLEADER_H_
#define GGAFLIB_STEPPEDCOORDSPLINEKUROKOLEADER_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/lib/util/spline/SplineKurokoLeader.h"

namespace GgafLib {

/**
 * スプライン曲線移動 .
 * 単純に、フレーム毎に順番に補完点座標へ移動。
 * @version 1.00
 * @since 2009/10/28
 * @author Masatoshi Tsuge
 */
class SteppedCoordSplineKurokoLeader : public SplineKurokoLeader {

public:
    SteppedCoordSplineManufacture* _pSteppedSplManuf;

    /** [r]補完点(基準点も含む)の数 */
    int _point_index;
    /** start()からの経過フレーム数 */
    frame _leading_frames;

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
     * @return
     */
    SteppedCoordSplineKurokoLeader(GgafDxCore::GgafDxKuroko* const prm_pKuroko,
                                    SplineLine* prm_sp);


    virtual void restart() override;
    /**
     * 毎フレームの振る舞いメソッド .
     * 利用者は毎フレームこのメソッドを呼び出す必要があります。
     */
    virtual void behave() override;

    virtual ~SteppedCoordSplineKurokoLeader();
};

}
#endif /*GGAFLIB_FIXEDVELOCITYSPLINEKUROKOLEADER_H_*/
