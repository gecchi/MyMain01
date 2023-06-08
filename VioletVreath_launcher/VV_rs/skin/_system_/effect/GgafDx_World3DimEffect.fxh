#include "GgafDx_Effect.fxh"

/** -1.0 or 0.0～1.0。遠くでも表示を強制したい場合に 負の値 が代入される。*/
//float g_far_rate_alpha_fog;

/** 現在の射影変換行列要素のzf。カメラから遠くのクリップ面までの距離(どこまでの距離が表示対象か）> zn */
float g_zf;

/** モデルのView変換行列 */
float4x4 g_matView;
/** 射影変換行列 */
float4x4 g_matProj;

/*
float adjustDotByDot(floatz posModel_proj_z) {
    //遠方時の表示方法。
    if (g_far_rate_alpha_fog < 0.0) {
        //負の場合、どんな遠方でも表示する
        if (posModel_proj_z > g_zf*0.999) {
            //本来視野外のZでも、描画を強制するため、射影後のZ座標を上書き、
            out_vs.posModel_Proj.z = g_zf*0.999; //本来視野外のZでも、描画を強制するため g_zf*0.999 に上書き、
        }
    } else {
        //αフォグ
        if (out_vs.posModel_Proj.z > g_zf*g_far_rate) {   // 最遠の g_far_rate よりさらに奥の場合徐々に透明に
            //  z : g_far_rate*g_zf ～ 1.0*g_zf  → α : 1.0 ～ 0.0  となるようにするには
            //  α = ( (0-1)*z - (g_zf*0) + (1* (far_rate*g_zf)) ) / ((far_rate*g_zf)-g_zf)
            //  α = (far_rate*g_zf - z) / (far_rate*g_zf - g_zf)
            out_vs.color.a *= (  (g_far_rate*g_zf - out_vs.posModel_Proj.z) / ((g_far_rate-1.0)*g_zf) );
        }
    }
}
*/