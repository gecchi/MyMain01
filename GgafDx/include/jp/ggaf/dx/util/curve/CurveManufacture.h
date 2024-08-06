#ifndef GGAF_DX_CURVEMANUFACTURE_H_
#define GGAF_DX_CURVEMANUFACTURE_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/core/Object.h"

#include <string>

namespace GgafDx {

/**
 * スプライン曲線移動のための情報セット .
 * 全てのアクターに共通するスプラインの情報はここに集約。<BR>
 * オブジェクトの関係<BR>
 * VehicleLeader       各アクター毎に生成される。
 *                    アクターに対する、スプライン曲線上の現在の補完点の位置・時間・距離等の管理を行い、
 *                    移動車両(LocusVehicle)に指示を出してアクターを移動させる。
 *                    １つの CurveManufacture オブジェクトに対して N 個の VehicleLeader オブジェクトが参照している。
 *                    スプラインの座標点間の距離に影響の無い情報はココで保持する。
 *                    つまりスプライン曲線の座標点の軸平行移動オフセット、
 *                    X,Y,Zの正負入れ替え情報。（TODO:将来は、回転情報もココに）
 *
 * CurveManufacture   スプライン曲線の動的編集情報（拡大縮小など）、移動方式クラス（VehicleLeader）の情報等を保持。
 *                    拡大縮小により、各補完点毎の距離等の情報を予め計算して保持している。
 *                    拡大縮小率を変更する場合は、このオブジェクトのフィールドも再計算が必要となる。
 *                    １つの CurveSource オブジェクトに対して N 個の CurveSourceオブジェクトが参照している。
 *                    (※ldrファイルの情報に相当する。)
 *
 * CurveSource        スプライン曲線の座標点セットの情報を保持するオブジェクト。
 *                    CurveSource は生成と同時に、引数のファイル名の外部ファイルを読み込み、
 *                    座標の補完点を計算し、内部保持する。
 *                    (※datファイルの情報に相当する。)
 *
 * @version 1.00
 * @since 2011/08/05
 * @author Masatoshi Tsuge
 */
class CurveManufacture : public GgafCore::Object {

public:

    enum MoveMethod {
        FixedVelocity = 1,
        FixedFrame,
        SteppedCoord,
    };

    enum MoveDriver {
        CoordVehicle = 1,
        LocusVehicle,
    };


    CurveSourceConnection* _pCurveSrcCon;
    /** [r]座標情報(datファイル情報に相当)*/
    CurveSource* _pCurve;
    /** [r]スプライン座標情報ファイル名(ldrファイル) */
    std::string _ldr_file;
    /** X軸方向補正割合 */
    double _rate_x;
    /** Y軸方向補正割合 */
    double _rate_y;
    /** Z軸方向補正割合 */
    double _rate_z;
    /** [r]次の補完点までの距離のテーブル */
    coord* _paDistance_to;
    /** [r]距離の合計 _paDistance_to[0] ～ _paDistance_to[n]  */
    coord _total_distance;
    /** [r]計算済みであるかどうか */
    bool _is_calculated;


    MoveMethod _move_method;
    MoveDriver _move_driver;
public:
    /**
     * コンストラクタ .
     * @param prm_coord_spl_file スプライン座標情報ファイル(splファイル)
     */
    explicit CurveManufacture(const char* prm_coord_spl_file);
    /**
     * コンストラクタ .
     * @param prm_pCurveSrc スプライン座標情報オブジェクト
     */
    CurveManufacture(CurveSource* prm_pCurve);

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


    virtual VehicleLeader* createVehicleLeader(GgafDx::GeometricActor* prm_pActor);

    /**
     * VehicleLeader オブジェクトの生成 .
     * 設定した移動車両を、操作しますので注意して下さい。<br>
     * 本メソッドで作成した VehicleLeader は、呼び元で deleteする必要があります。<br>
     * @param prm_pLocusVehicle 対象のアクターの移動車両
     * @return
     */
    virtual VehicleLeader* createLocusVehicleLeader(GgafDx::LocusVehicle* prm_pLocusVehicle);

    virtual VehicleLeader* createCoordVehicleLeader(GgafDx::CoordVehicle* prm_pCoordVehicle);

    void setMoveMethod(MoveMethod prm_move_method) {
        _move_method = prm_move_method;
    }

    void setMoveDriver(MoveDriver prm_move_driver) {
        _move_driver = prm_move_driver;
    }

    virtual ~CurveManufacture();
};

}
#endif /*GGAF_DX_CURVEMANUFACTURE_H_*/
