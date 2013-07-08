#ifndef FORMATIONGERIA_H_
#define FORMATIONGERIA_H_
#include "jp/ggaf/lib/actor/DefaultGeometricActor.h"

namespace VioletVreath {

/**
 * フォーメーションアクタークラス .
 * 自身は出現ポイントの中心
 */
class FormationGeria : public GgafLib::DefaultGeometricActor {
    /** ゲリアストック */
    GgafCore::GgafActorDepository* pDepo_EnemyGeria_;
    DepositoryConnection* pDepoConnection_;

public:
    /** 出現範囲幅BOX */
    int X1_app_, Y1_app_, Z1_app_, X2_app_, Y2_app_, Z2_app_;
    int frame_app_interval_;

public:
    /**
     * コンストラクタ .
     * Geriaフォーメーションを定義します。
     * @param prm_name           フォーメーション名（デバッグ用）
     * @param prm_X1_app         Geria出現範囲AAB(軸平行直方体：Axis-Aligned Box)の左上手前X座標（中心からのオフセット＝ローカル座標）
     * @param prm_Y1_app         Geria出現範囲AABの左上手前Y座標（ローカル座標）
     * @param prm_Z1_app         Geria出現範囲AABの左上手前Z座標（ローカル座標）
     * @param prm_X2_app         Geria出現範囲AABの右下奥X座標（ローカル座標）
     * @param prm_Y2_app         Geria出現範囲AABの右下奥Y座標（ローカル座標）
     * @param prm_Z2_app         Geria出現範囲AABの右下奥Z座標（ローカル座標）
     * @param prm_X              Geria出現範囲AABの中心X座標（絶対座標）
     * @param prm_Y              Geria出現範囲AABの中心Y座標（絶対座標）
     * @param prm_Z              Geria出現範囲AABの中心Z座標（絶対座標）
     * @param prm_veloMv_App     Geria出現範囲AAB全体の移動速度
     * @param prm_angRzMv_AppBox Geria出現範囲AAB全体の移動方角のZ軸回転角
     * @param prm_angRyMv_AppBox Geria出現範囲AAB全体の移動方角のY軸回転角
     * @param prm_veloMv_Geria    各Geriaの移動速度初期値
     * @param prm_angRzMv_GeriaMv 各Geriaの移動方角のZ軸回転角初期値
     * @param prm_angRyMv_GeriaMv 各Geriaの移動方角のY軸回転角初期値
     * @param prm_nGeriaStock     Geriaのストック数(バッファ数)
     * @param prm_frame_app_interval Geriaの出現間隔
     * @return
     */
    FormationGeria(const char* prm_name,
            int prm_X1_app, int prm_Y1_app, int prm_Z1_app,
            int prm_X2_app, int prm_Y2_app, int prm_Z2_app,
            int prm_X, int prm_Y, int prm_Z,
            velo prm_veloMv_App,
            angle prm_angRzMv_AppBox, angle prm_angRyMv_AppBox,
            velo prm_veloMv_Geria,
            angle prm_angRzMv_GeriaMv, angle prm_angRyMv_GeriaMv,
            int prm_nGeriaStock,
            int prm_frame_app_interval);

    virtual void initialize() override;

    virtual void processBehavior() override;

    virtual ~FormationGeria();
};

}
#endif /*FORMATIONGERIA_H_*/
