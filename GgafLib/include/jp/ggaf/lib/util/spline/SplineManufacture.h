#ifndef GGAFLIB_SPLINEMANUFACTURE_H_
#define GGAFLIB_SPLINEMANUFACTURE_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/core/GgafObject.h"

#include <string>

namespace GgafLib {

/**
 * スプライン曲線移動のための情報セット .
 * 全てのアクターに共通するスプラインの情報はここに集約。<BR>
 * オブジェクトの関係<BR>
 * SplineLeader 各アクター毎に生成される。
 *                    アクターに対する、スプライン曲線上の現在の補完点の位置・時間・距離等の管理を行い、
 *                    黒衣(Kuroko)に指示を出してアクターを移動させる。
 *                    １つの SplineManufacture オブジェクトに対して N 個の SplineLeader オブジェクトが参照している。
 *                    スプラインの座標点間の距離に影響の無い情報はココで保持する。
 *                    つまりスプライン曲線の座標点の軸平行移動オフセット、
 *                    X,Y,Zの正負入れ替え情報。（TODO:将来は、回転情報もココに）
 *
 * SplineManufacture  スプライン曲線の座標点セットの拡大縮小情報、またそれに伴うSplineKurokoLeaderの実装クラスの情報を保持。
 *                    拡大縮小により、各補完点毎の距離等の情報を予め計算して保持している。
 *                    拡大縮小率を変更する場合は、このオブジェクトのフィールドも再計算が必要となる。
 *                    １つの SplineSource オブジェクトに対して N 個の SplineSourceオブジェクトが参照している。
 *                    (※splファイルの情報に相当する。)
 *
 * SplineSource       スプライン曲線の座標点セットの情報を保持するオブジェクト。
 *                    SplineSource は生成と同時に、引数のファイル名の外部ファイルを読み込み、
 *                    座標の補完点を計算し、内部保持する。
 *                    (※datファイルの情報に相当する。)
 *
 * @version 1.00
 * @since 2011/08/05
 * @author Masatoshi Tsuge
 */
class SplineManufacture : public GgafCore::GgafObject {

public:
    SplineSourceConnection* _pSplSrcCon;
    /** [r]座標情報(datファイル情報に相当)*/
    SplineSource* _pSpl;
    /** [r]スプライン座標情報ファイル名(splファイル) */
    std::string _spl_file;
    /** X軸方向補正割合 */
    double _rate_x;
    /** Y軸方向補正割合 */
    double _rate_y;
    /** Z軸方向補正割合 */
    double _rate_z;
    /** [r]次の補完点までの距離のテーブル */
    coord* _paDistance_to;
    /** [r]距離の合計 _paDistance_to[0] 〜 _paDistance_to[n]  */
    coord _total_distance;
    /** [r]計算済みであるかどうか */
    bool _is_calculated;
public:
    /**
     * コンストラクタ .
     * @param prm_coord_data_file スプライン座標情報ファイル(splファイル)
     */
    explicit SplineManufacture(const char* prm_coord_data_file);
    /**
     * コンストラクタ .
     * @param prm_pSplSrc スプライン座標情報オブジェクト
     */
    SplineManufacture(SplineSource* prm_pSpl);

    /**
     * 各補完点を、X軸方向、Y軸方向、Z軸方向それぞれに割合を乗じ、補正します .
     * デフォルトは adjustAxisRate(1.0, 1.0, 1.0) となります。<BR>
     * <b>[注意]</b><BR>
     * このメソッドを実行した場合、点の点の距離が変わるため、<BR>
     * 下位クラスの実装によっては、内部保持テーブル情報を更新するために、<BR>
     * ※calculate() を実行しないと反映しません。
     * @param prm_rate_x X軸方向補正割合
     * @param prm_rate_y Y軸方向補正割合
     * @param prm_rate_z Z軸方向補正割合
     */
    virtual void adjustAxisRate(double prm_rate_x, double prm_rate_y, double prm_rate_z);

    /**
     * 初期化（計算）処理 .
     * _paDistance_to[] と _total_distance を計算します。<BR>
     * プロパティを変更した場合、内部テーブル情報を更新するために
     * 一度実行する必要があります。
     * 下位で呼び出しして下さい。
     */
    virtual void calculate();

    /**
     * SplineLeader オブジェクトの生成 .
     * 設定した黒衣を、操作しますので注意して下さい。<br>
     * 本メソッドで作成した SplineLeader は、呼び元で deleteする必要があります。<br>
     * @param prm_pKuroko 対象のアクターの黒衣
     * @return
     */
    virtual SplineLeader* createKurokoLeader(GgafDxCore::GgafDxKuroko* prm_pKuroko);

    virtual SplineLeader* createAxesMoverLeader(GgafDxCore::GgafDxAxesMover* prm_pAxesMover);

    virtual ~SplineManufacture();
};

}
#endif /*GGAFLIB_SPLINEMANUFACTURE_H_*/
