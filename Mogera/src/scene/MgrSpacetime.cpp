#include "MgrSpacetime.h"

#include "jp/ggaf/core/actor/SceneChief.h"
#include "jp/ggaf/core/scene/Scene.h"
#include "jp/ggaf/lib/util/VirtualButton.h"

#include "actor/camera/MgrCameraWorker.h"
#include "actor/PointerTest.h"
#include "MgrCaretaker.h"
#include "scene/MgrSpacetime/MgrWorld.h"
#include "util/MgrUtil.h"

using namespace GgafCore;
using namespace GgafDx;
using namespace GgafLib;
using namespace Mogera;


std::ofstream pOs_("C:/gnuplot/xxxxxx.txt");


MgrSpacetime::MgrSpacetime(const char* prm_name, MgrCamera* prm_pCam) :
        GgafLib::DefaultSpacetime(prm_name, prm_pCam) {
    pWorld_ = nullptr;
    UTIL::left_top_x_ = CONFIG::NUMBER_OF_SCREENS_USED > 1 ? PX_C(pCARETAKER->_aRectRenderBufferSource[SCREEN01].left) :
                                            PX_C(pCARETAKER->_aRectRenderBufferSource[SCREEN01].left);
    UTIL::left_top_y_ = CONFIG::NUMBER_OF_SCREENS_USED > 1 ? PX_C(pCARETAKER->_aRectRenderBufferSource[SCREEN01].top) :
                                            PX_C(pCARETAKER->_aRectRenderBufferSource[SCREEN01].top);
    UTIL::center_x_ = PX_C(CONFIG::RENDER_TARGET_BUFFER_WIDTH / 2);
    UTIL::center_y_ = PX_C(CONFIG::RENDER_TARGET_BUFFER_HEIGHT / 2);

    pActiveCamWorker_ = NEW MgrCameraWorker("MgrCameraWorker", prm_pCam);
    getSceneChief()->appendChild(pActiveCamWorker_); //基底デフォルトカメラワーク

    pVb_ = NEW VirtualButton();
    pVb_->remapK(0, VB_UI_DEBUG, VBK_Q     );
    pVb_->remapK(0, VB_PAUSE   , VBK_ESCAPE);
    pVb_->remap(0, VB_UP     , VBK_UP   , VBJ_P1_Y_POS_MINUS);  //VB_UP      = キーボード↑ または、Y軸－ とする。
    pVb_->remap(0, VB_DOWN   , VBK_DOWN , VBJ_P1_Y_POS_PLUS );  //VB_DOWN    = キーボード↓ または、Y軸＋ とする。
    pVb_->remap(0, VB_LEFT   , VBK_LEFT , VBJ_P1_X_POS_MINUS);  //VB_LEFT    = キーボード← または、X軸－ とする。
    pVb_->remap(0, VB_RIGHT  , VBK_RIGHT, VBJ_P1_X_POS_PLUS );  //VB_RIGHT   = キーボード→ または、X軸＋ とする。
    pVb_->remap(0, VB_BUTTON1, VBK_SPACE, VBJ_P1_BUTTON_01  );  //VB_BUTTON1 = スペースキー または ジョイスティックボタン１ とする。
    _TRACE_("Spacetime Bound = X("<<_x_bound_left<<" ~ "<<_x_bound_right<<") Y("<<_y_bound_bottom<<" ~ "<<_y_bound_top<<") Z("<<_z_bound_near<<" ~ "<<_z_bound_far<<")");
}

// 単純な反射ベクトル（m0を直線方向で反転）
D3DXVECTOR3 calculateUnifiedHermiteEndTangent(const D3DXVECTOR3& p0,
    const D3DXVECTOR3& m0,
    const D3DXVECTOR3& p1) {
    // m0の長さ
    float m0_len = D3DXVec3Length(&m0);
    if (m0_len == 0) return D3DXVECTOR3(0, 0, 0);

    // 単位ベクトルに正規化
    D3DXVECTOR3 m0_dir = m0;
    D3DXVec3Normalize(&m0_dir, &m0_dir);

    // 発射元からターゲットへの方向
    D3DXVECTOR3 to_target = p1 - p0;
    D3DXVec3Normalize(&to_target, &to_target);

    // m0 の反転ベクトルを to_target 方向に投影して、回り込む方向を得る
    D3DXVECTOR3 m1_dir = -m0_dir + 2 * D3DXVec3Dot(&to_target, &m0_dir) * to_target;
    D3DXVec3Normalize(&m1_dir, &m1_dir);

    return m1_dir * m0_len;
}
//
//// Hermite補間関数
//D3DXVECTOR3 Hermite(
//    const D3DXVECTOR3& p0, const D3DXVECTOR3& m0,
//    const D3DXVECTOR3& p1, const D3DXVECTOR3& m1,
//    float t)
//{
//    float t2 = t * t;
//    float t3 = t2 * t;
//
//    float h00 = 2 * t3 - 3 * t2 + 1;
//    float h10 = t3 - 2 * t2 + t;
//    float h01 = -2 * t3 + 3 * t2;
//    float h11 = t3 - t2;
//
//    return p0 * h00 + m0 * h10 + p1 * h01 + m1 * h11;
//}
//
//// 指定区間のHermite曲線を生成
//std::vector<D3DXVECTOR3> GenerateHermiteCurvePoints(
//    const D3DXVECTOR3& startPoint,
//    const D3DXVECTOR3& startTangent,
//    const D3DXVECTOR3& endPoint,
//    const D3DXVECTOR3& endTangent,
//    int samples)
//{
//    std::vector<D3DXVECTOR3> points;
//
//    for (int i = 0; i <= samples; ++i)
//    {
//        float t = i / static_cast<float>(samples);
//        points.push_back(Hermite(startPoint, startTangent, endPoint, endTangent, t));
//    }
//
//    return points;
//}
// 3次ベジェ曲線1点計算
// Bezier 曲線上の1点を計算する関数（3次）
// ベジェ曲線上の点を計算


//// 滑らかなホーミング用の m1 を自動生成
//D3DXVECTOR3 ComputeSmoothM1(const D3DXVECTOR3& p0, const D3DXVECTOR3& m0, const D3DXVECTOR3& p1)
//{
//    // m0 の長さ（維持する）
//    float m0_length = D3DXVec3Length(&m0);
//    if (m0_length < 1e-6f) return D3DXVECTOR3(0, 0, 0);  // 無効な m0
//
//    // 自機から敵機への方向ベクトル
//    D3DXVECTOR3 toEnemy = p1 - p0;
//    D3DXVec3Normalize(&toEnemy, &toEnemy);
//
//    // m0 の反転ベクトル
//    D3DXVECTOR3 m0_neg = -m0;
//    D3DXVec3Normalize(&m0_neg, &m0_neg);
//
//    // m0_neg と toEnemy の中間方向（鋭角を避ける）
//    D3DXVECTOR3 midDir = m0_neg + toEnemy;
//    D3DXVec3Normalize(&midDir, &midDir);
//
//    // m0 の長さを保持して m1 を構築
//    D3DXVECTOR3 m1 = midDir * m0_length;
//
//    return m1;
//}
//
D3DXVECTOR3 ComputeNaturalM1(const D3DXVECTOR3& p0, const D3DXVECTOR3& m0, const D3DXVECTOR3& p1)
{
    float m0_length = D3DXVec3Length(&m0);
    if (m0_length < 1e-6f) return D3DXVECTOR3(0, 0, 0);

    // ターゲット方向
    D3DXVECTOR3 toEnemy = p1 - p0;
    D3DXVec3Normalize(&toEnemy, &toEnemy);

    // m0 方向
    D3DXVECTOR3 m0_dir = m0;
    D3DXVec3Normalize(&m0_dir, &m0_dir);

    float cosTheta = D3DXVec3Dot(&m0_dir, &toEnemy);

    const float cosThreshold = 0.5f;

    D3DXVECTOR3 m1_dir;

    if (cosTheta >= cosThreshold) {
        m1_dir = toEnemy;
    }
    else {
        float t = (cosTheta + 1.0f) / (1.0f + cosThreshold);
        if (t < 0.0f) t = 0.0f;
        else if (t > 1.0f) t = 1.0f;

        D3DXVECTOR3 blendDir = (1.0f - t) * m0_dir + t * toEnemy;
        D3DXVec3Normalize(&blendDir, &blendDir);

        // 修正ポイント：方向が正しいか確認
        if (D3DXVec3Dot(&blendDir, &toEnemy) < 0.0f) {
            blendDir *= -1.0f; // 敵と逆方向なら反転
        }

        m1_dir = blendDir;
    }

    return m1_dir * m0_length;
}



D3DXVECTOR3 BezierPoint(const D3DXVECTOR3& p0, const D3DXVECTOR3& p1,
    const D3DXVECTOR3& p2, const D3DXVECTOR3& p3, float t)
{
    float u = 1.0f - t;
    float tt = t * t;
    float uu = u * u;
    float uuu = uu * u;
    float ttt = tt * t;

    D3DXVECTOR3 point = uuu * p0;
    point += 3 * uu * t * p1;
    point += 3 * u * tt * p2;
    point += ttt * p3;

    return point;
}

// ベジェ曲線の点を生成して std::vector<D3DXVECTOR3> に格納
void GenerateBezierCurve(const D3DXVECTOR3& p0, const D3DXVECTOR3& m0,
    const D3DXVECTOR3& p1, const D3DXVECTOR3& m1,
    std::vector<D3DXVECTOR3>& curve,
    int numSegments = 100)
{
    curve.clear();
    curve.reserve(numSegments + 1);

    D3DXVECTOR3 cp0 = p0;
    D3DXVECTOR3 cp1 = p0 + m0;
    D3DXVECTOR3 cp2 = p1 + m1;
    D3DXVECTOR3 cp3 = p1;

    for (int i = 0; i <= numSegments; ++i)
    {
        float t = static_cast<float>(i) / numSegments;
        D3DXVECTOR3 point = BezierPoint(cp0, cp1, cp2, cp3, t);
        curve.push_back(point);
    }
}
void MgrSpacetime::initialize() {
    //世界シーン生成し、自シーンの配下に所属させる
    pWorld_ = desireScene(Mogera::MgrWorld);
    appendChild(pWorld_);


    // 始点・始接線・終点・終接線
    D3DXVECTOR3 p0(0, 0, 0);
    D3DXVECTOR3 m0(0, 1, 0); 
    D3DXVECTOR3 p1(1, -3, 0);
    //D3DXVECTOR3 m1(0, 2, 0);
    //D3DXVECTOR3 m1 = calculateUnifiedHermiteEndTangent(p0, m0, p1);
    // 曲線座標を生成
    std::vector<D3DXVECTOR3> curve;
    GenerateBezierCurve(p0, m0, p1, -ComputeNaturalM1(p0, m0, p1), curve, 30);

    // GNUPLOT 形式で出力
    for (std::vector<D3DXVECTOR3>::const_iterator it = curve.begin(); it != curve.end(); ++it)
    {
        _TRACE_( it->x << " " << it->y << " " << it->z );
        pOs_ << it->x << " " << it->y << " " << it->z << std::endl;
    }

    pOs_.close();
}

//set xrange[-10:10]
//set yrange[-10:10]
//set zrange[-10:10]
//set view 60, 30, 1, 1  # zscaleを調整して軸の比率を合わせる
//splot 'xxxxxx.txt' using 1:2 : 3 with points

void MgrSpacetime::processBehavior() {
    pVb_->update(); //入力状況更新

//    bool b1 = pVb_->isPressed(0, VB_UP);
//    bool b2 = pVb_->wasPressedAtLeastOnce(0, VB_UP, 10);
//    bool b3 = pVb_->wasPressedAtLeastOnce(0, VB_UP, 3);
//    _TRACE_(getBehaveingFrame() <<":"<<b1<<":"<<b2<<":"<<b3);
    bool b1 = pVb_->arePushedDownAtOnce3(0, VB_LEFT, VB_UP, VB_RIGHT, 1);
//    bool b2 = pVb_->arePushedDownAtOnce(0, VB_LEFT, VB_UP, VB_RIGHT, 10);
//    bool b3 = pVb_->arePushedDownAtOnce(0, VB_LEFT, VB_UP, VB_RIGHT, 60);
//    _TRACE_(getBehaveingFrame() <<":"<<b1<<":"<<b2<<":"<<b3);
    if (b1) {
        _TRACE_(getBehaveingFrame() <<":"<<b1);
    }

}
void MgrSpacetime::processJudgement() {
}
void MgrSpacetime::processHitCheck() {
    //当たり判定チェック
    executeWorldHitCheck(MGR_MIKATA, MGR_TEKI);
    executeViewHitCheck(MGR_MIKATA, MGR_TEKI);
}

MgrSpacetime::~MgrSpacetime() {
    GGAF_DELETE(pVb_);
}

