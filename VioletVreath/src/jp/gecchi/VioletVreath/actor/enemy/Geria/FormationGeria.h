#ifndef FORMATIONGERIA_H_
#define FORMATIONGERIA_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultGeometricActor.h"

namespace VioletVreath {

/**
 * フォーメーションアクタークラス .
 * 自身は出現ポイントの中心
 */
class FormationGeria : public GgafLib::DefaultGeometricActor {


public:
    /** ゲリアストック */
    GgafCore::GgafActorDepository* pDepo_;

//    /** 出現範囲幅BOX */
//    int X1_app_, Y1_app_, Z1_app_, X2_app_, Y2_app_, Z2_app_;
//    int frame_app_interval_;

public:

    FormationGeria(const char* prm_name, int prm_nGeriaStock);


    EnemyGeria* summonGeria();

//    /**
//     * コンストラクタ .
//     * Geriaフォーメーションを定義します。
//     * @param prm_name           フォーメーション名（デバッグ用）
//     * @param prm_X1_app         Geria出現範囲AAB(軸平行直方体：Axis-Aligned Box)の左上手前X座標（中心からのオフセット＝ローカル座標）
//     * @param prm_Y1_app         Geria出現範囲AABの左上手前Y座標（ローカル座標）
//     * @param prm_Z1_app         Geria出現範囲AABの左上手前Z座標（ローカル座標）
//     * @param prm_X2_app         Geria出現範囲AABの右下奥X座標（ローカル座標）
//     * @param prm_Y2_app         Geria出現範囲AABの右下奥Y座標（ローカル座標）
//     * @param prm_Z2_app         Geria出現範囲AABの右下奥Z座標（ローカル座標）
//     * @param prm_x              Geria出現範囲AABの中心X座標（絶対座標）
//     * @param prm_y              Geria出現範囲AABの中心Y座標（絶対座標）
//     * @param prm_z              Geria出現範囲AABの中心Z座標（絶対座標）
//     * @param prm_velo_mv_App     Geria出現範囲AAB全体の移動速度
//     * @param prm_rz_mv_AppBox Geria出現範囲AAB全体の移動方角のZ軸回転角
//     * @param prm_ry_mv_AppBox Geria出現範囲AAB全体の移動方角のY軸回転角
//     * @param prm_velo_mv_Geria    各Geriaの移動速度初期値
//     * @param prm_rz_mv_GeriaMv 各Geriaの移動方角のZ軸回転角初期値
//     * @param prm_ry_mv_GeriaMv 各Geriaの移動方角のY軸回転角初期値
//     * @param prm_nGeriaStock     Geriaのストック数(バッファ数)
//     * @param prm_frame_app_interval Geriaの出現間隔
//     * @return
//     */
//    FormationGeria(const char* prm_name,
//            int prm_X1_app, int prm_Y1_app, int prm_Z1_app,
//            int prm_X2_app, int prm_Y2_app, int prm_Z2_app,
//            int prm_x, int prm_y, int prm_z,
//            velo prm_velo_mv_App,
//            angle prm_rz_mv_AppBox, angle prm_ry_mv_AppBox,
//            velo prm_velo_mv_Geria,
//            angle prm_rz_mv_GeriaMv, angle prm_ry_mv_GeriaMv,
//            int prm_nGeriaStock,
//            int prm_frame_app_interval);

    virtual ~FormationGeria();
};

}
#endif /*FORMATIONGERIA_H_*/
