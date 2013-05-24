#ifndef GGAFDXPOINTSPRITEACTOR_H_
#define GGAFDXPOINTSPRITEACTOR_H_
#include "jp/ggaf/dxcore/actor/GgafDxDrawableActor.h"

namespace GgafDxCore {

/**
 * ポイントスプライトアクター.
 * GgafDxDrawableActor を継承し、ポイントスプライト表示機能を備えたアクター<BR>
 * 次の例ようなポイントスプライト表示機能を備える。
 * （※px相当＝画面上pxとほぼ一致）
 * <pre>
 * ＜例＞
 *
 * 【テクスチャ】
 * Pattern.png
 *
 * <---256px--->
 *
 * +--+--+--+--+    ^
 * | 0| 1| 3| 4|    |
 * +--+--+--+--+    |
 * | 5| 6| 7| 8|    |
 * +--+--+--+--+    256px (正方形であること！
 * | 9|10|11|12|    |      ピクセル数は自由。例では256*256px)
 * +--+--+--+--+    |
 * |13|14|15|16|    |
 * +--+--+--+--+    v
 *
 *
 * 【読み込むXファイル】
 * ポイントスプライト専用の定義Xファイル(拡張子psprx)を読み込む。
 *
 * -----------------------------------------
 * xof 0303txt 0032
 * PointSpriteDef Test {
 *   32.0;                                  //← ポイントに表示するスプライトの１辺のpx相当幅。テクスチャの１パターンの１辺のpxではない。
 *                                          //   (例は32px相当画面表示にするという意味)
 *   "Pattern.png";                         //← テクスチャ
 *   4;                                     //← テクスチャ縦横の分割数。1は「分割無し」、2は「縦横２分割して 4パターンアニメーション」
 *                                          //   例では、上記のようなテクスチャなので、4を指定して縦横４分割で4*4の16パターンとなる。
 *                                          //   したがって、このときテクスチャの１パターンの１辺のpxは256/4で64pxと決まる。
 *   3;                                     //← 頂点数（＝スプライト数）例は３個の頂点を指定。以下にデータで続く
 *                                          //   頂点座標、オブジェクトカラー、初期パターン番号、初期倍率のデータ数が
 *                                          //   全て一致する必要がある。
 *   -20.000000;-21.000000;-22.000000;,     //← ポイントスプライト頂点XYZ座標情報。DirectXの座標で指定。
 *   3.000000;2.000000;1.000000;,
 *   11.000000;12.000000;13.000000;;
 *
 *   1.000000;0.100000;0.100000;1.000000;,  //← 各ポイントスプライトのRGBA初期カラー（テクスチャと合成される）
 *   0.100000;1.000000;0.100000;1.000000;,
 *   0.100000;0.100000;1.000000;1.000000;;
 *
 *   0,                                     //← 各ポイントスプライトの初期アニメーションパターン番号オフセット
 *   5,
 *   15;
 *
 *   1.0,                                   //← 各ポイントスプライトの初期スケール倍率
 *   2.0,
 *   1.0;
 * }
 * -----------------------------------
 *
 *
 * 【上記Xファイルの初期表示画面イメージ】
 * 左手座標系、画面中心が (0,0,0) 。
 * 上がX軸の正、右がY軸の正、奥がZ軸の正
 *
 * +-----------------------------------------------------------------+
 * |                                                                 |
 * |                                                                 |
 * |                                                                 |
 * |                                     �B                          |
 * |                                      ++                         |
 * |                                      ++                         |
 * |                           �A +----+                             |
 * |                              | 5  |                             |
 * |                              |    |                             |
 * |                              +----+                             |
 * |                                                                 |
 * |                   �@                                            |
 * |                      +----+                                     |
 * |                      | 0  |                                     |
 * |                      |    |                                     |
 * |                      +----+                                     |
 * |                                                                 |
 * +-----------------------------------------------------------------+
 *
 * �@ DirectXの座標(-20.000000,-21.000000,-22.000000)
 *    表示アニメーションパターン番号０番
 *    赤っぽく表示
 *    -220px相当の距離手前になるので、少し拡大されて表示される。
 *    手前、奥による拡大縮小はワールド変換後にカメラとの距離などから自動計算。
 *    他のメッシュオブジェクトとの率は画面中心付近で一致する。
 *    但し、単純に拡大縮小しているため画面の端に行くほど差が出る。
 *
 * �A DirectXの座標(3.000000,2.000000,1.000000);
 *    表示アニメーションパターン番号５番
 *    画面上 (30px,20px)あたりで緑っぽく表示。
 *    （「あたり」という表現はワールド変換するのでズレるため）
 *    僅かに奥のため、ほんの少しの縮小が行われる。
 *    Z座標が 1.000000 (10px相当)と 0 に近いため、ほぼテクスチャのpx相当の幅で見える。
 *    10px奥の分ほんの少し縮小。
 *    初期スケール倍率が2.0としているため (256/4)*2.0 = 128 で
 *    128*128pxの10px奥の分ほんの少し縮小で画面上で見える。
 *    奥行が初期表示でZ=0の場合、テクスチャのピクセルの大きさにほぼ一致するようにカメラを引いている。
 *    この距離を初期カメラZ距離と呼ぶ。
 *    px相当とは、初期カメラZ距離離れた位置にカメラを置いて表示した場合の
 *    画面に見えるオブジェクトの幅のことである。
 *    DirectX座標の「1」は約10ピクセルに相当するようになっている。
 *
 * �B DirectXの座標(11.000000, 12.000000, 13.000000)
 *    表示アニメーションパターン番号１５番
 *    青っぽく表示
 *    130px相当の距離奥のため、やや縮小が行われる。
 *    アニメーションパターン番号１５番であるが、
 *    アクター側のロジックで、アニメーションパターンを１つ進めると
 *    �Bのアニメーションパターン番号は０番に変わる（ループする）
 * </pre>
 * @version 1.00
 * @since 2010/02/26
 * @author Masatoshi Tsuge
 */
class GgafDxPointSpriteActor : public GgafDxDrawableActor {

public:
    /** [r]モデル資源 */
    GgafDxPointSpriteModel* _pPointSpriteModel;
    /** [r]エフェクト資源 */
    GgafDxPointSpriteEffect* _pPointSpriteEffect;
    /** [r]UVフリッパー(パラパラアニメ) */
    GgafDxUvFlipper* _pUvFlipper;

public:
    /**
     * コンストラクタ
     * @param prm_name モデル名称（デバッグログで表示、なんでも良い）
     * @param prm_model_id モデル定義名。末尾に ".psprx" をつけてXファイル名になること。
     * @param prm_effect_id エフェクト定義名。末尾に ".fx" をつけてエフェクトファイル名になること。
     * @param prm_technique エフェクトのテクニック名
     * @param prm_pStat 使用するステータスオブジェクト(使用しない時 nullptrでよい)
     * @param prm_pChecker 使用するチェッカーオブジェクト（チェッカー未使用時はnullptrでよい）
     */
    GgafDxPointSpriteActor(const char* prm_name,
                            const char* prm_model_id,
                            const char* prm_effect_id,
                            const char* prm_technique,
                            GgafCore::GgafStatus* prm_pStat,
                            GgafDxChecker* prm_pChecker );

    virtual void processDraw() override;

    /**
     * α設定.
     * @param prm_alpha
     */
    virtual void setAlpha(float prm_alpha) override;

    /**
     * α加算 .
     * @param prm_alpha
     */
    virtual void addAlpha(float prm_alpha) override;


    virtual ~GgafDxPointSpriteActor(); //デストラクタ
};

}
#endif /*GGAFDXPOINTSPRITEACTOR_H_*/
