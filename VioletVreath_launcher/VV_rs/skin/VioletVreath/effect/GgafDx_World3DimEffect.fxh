#include "GgafDx_Effect.fxh"


/** モデルのView変換行列 */
float4x4 g_matView;
/** 射影変換行列 */
float4x4 g_matProj;

/** 現在の射影変換行列要素のzf。カメラから遠くのクリップ面までの距離(どこまでの距離が表示対象か）> zn */
float g_zf;
/** カメラの初期位置のZ座標( < 0) */
float g_cameraZ_org;
/** フォグ開始のzf距離割合。-1.0 or 0.0～1.0。遠くでも表示を強制したい場合に 負の値 が代入される。*/
float g_fog_starts_far_rate;



float getFogRate(float posModel_proj_z) {
    // 最遠の g_fog_starts_far_rate よりさらに奥の場合徐々に透明に
    //  z : g_fog_starts_far_rate*g_zf ～ 1.0*g_zf  → α : 1.0 ～ 0.0  となるようにするには
    if (posModel_proj_z < g_fog_starts_far_rate) {
        return 1.0;
    } else {
        return (posModel_proj_z-g_zf)/((g_fog_starts_far_rate-1)*g_zf);
    }

}
//( (min_b-max_b)*a - (max_a*min_b) + (max_b*min_a) ) / (min_a-max_a);
//min_a=g_zf*g_fog_starts_far_rate
//max_a=g_zf*1.0
//a=posModel_proj_z
//min_b=0
//max_b=1.0;
//=( (0-1.0)*posModel_proj_z - ((g_zf*1.0)*0) + (1.0*(g_zf*g_fog_starts_far_rate)) ) / ((g_zf*g_fog_starts_far_rate)-(g_zf*1.0))
//=-(posModel_proj_z-g_fog_starts_far_rate*g_zf)/((g_fog_starts_far_rate-1)*g_zf)
//よって
//→ 1.0-(-(posModel_proj_z-g_fog_starts_far_rate*g_zf)/((g_fog_starts_far_rate-1)*g_zf))
//→ (posModel_proj_z-g_zf)/((g_fog_starts_far_rate-1)*g_zf)
