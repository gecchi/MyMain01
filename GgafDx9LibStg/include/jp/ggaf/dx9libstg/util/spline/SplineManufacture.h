#ifndef SPLINEMANUFACTURE_H_
#define SPLINEMANUFACTURE_H_
namespace GgafDx9LibStg {

/**
 * スプライン曲線移動のための情報セット .
 * オブジェクトの関係
 * SplineSequence     各アクター毎に生成される。
 *                    アクターに対する、スプライン曲線上の現在の補完点の位置・時間・距離等の管理を行い、
 *                    黒子A(KurokoA)に指示を出してアクターを移動させる。
 *                    １つの SplineManufacture オブジェクトに対して N 個の SplineSequenceオブジェクトが参照している。
 *                    スプラインの座標点間の距離に影響の無い情報はココで保持する。
 *                    つまりスプライン曲線の座標点の軸平行移動オフセット、
 *                    X,Y,Zの正負入れ替え情報。（TODO:将来は、回転情報もココに）
 *
 * SplineManufacture  スプライン曲線の座標点セットの拡大縮小情報、またそれに伴うSplineSequenceの実装クラスの情報を保持。
 *                    拡大縮小により、各補完点毎の距離等の情報を予め計算して保持している。
 *                    拡大縮小率を変更する場合は、このオブジェクトのフィールドも再計算が必要となる。
 *                    １つの SplineSource オブジェクトに対して N 個の SplineSourceオブジェクトが参照している。
 *
 * SplineSource       Spline3D オブジェクトを使いまわすためのSpline3Dラッパークラス。
 *                    SplineSource は生成と同時に、引数のファイル名の外部ファイルを読み込み、
 *                    Spline3Dを生成し、内部保持する。
 *
 * Spline3D           スプライン曲線の座標点セットの情報を保持するオブジェクト。
 *
 * @version 1.00
 * @since 2011/08/05
 * @author Masatoshi Tsuge
 */
class SplineManufacture : public GgafCore::GgafObject {
private:

public:
    SplineSourceConnection* _pSplSrcCon;
    SplineSource* _pSplSrc;

    std::string _source_file;
    /** スプライン曲線の補完点生成、保持するクラス */
    Spline3D* _sp;
    /** X軸方向補正割合 */
    double _rate_X;
    /** Y軸方向補正割合 */
    double _rate_Y;
    /** Z軸方向補正割合 */
    double _rate_Z;

    /**
     * コンストラクタ .
     * @param prm_source_file スプライン座標情報ファイル
     */
    SplineManufacture(const char* prm_source_file);

    SplineManufacture(SplineSource* prm_pSplSrc);


    /**
     * 各補完点を、X軸方向、Y軸方向、Z軸方向それぞれに割合を乗じ、補正します .
     * デフォルトは adjustAxisRate(1.0, 1.0, 1.0) となります。<BR>
     * <b>[注意]</b><BR>
     * このメソッドを実行した場合、点の点の距離が変わるため、<BR>
     * 下位クラスの実装によっては、内部保持テーブル情報を更新するために、<BR>
     * ※calculate() を実行しないと反映しません。
     * @param prm_rate_X X軸方向補正割合
     * @param prm_rate_Y Y軸方向補正割合
     * @param prm_rate_Z Z軸方向補正割合
     */
    virtual void adjustAxisRate(double prm_rate_X, double prm_rate_Y, double prm_rate_Z);

    /**
     * 初期化（計算）処理 .
     * プロパティを変更した場合、内部テーブル情報を更新するために
     * 一度実行する必要があります。
     * 下位で実装して下さい。
     */
    virtual void calculate() = 0;

    /**
     * SplineSequence オブジェクトの生成 .
     * @param prm_pKurokoA 対象のアクター
     * @return
     */
    virtual SplineSequence* createSplineSequence(GgafDx9Core::GgafDx9KurokoA* prm_pKurokoA) = 0;


    virtual ~SplineManufacture();
};

}
#endif /*SPLINEMANUFACTURE_H_*/
