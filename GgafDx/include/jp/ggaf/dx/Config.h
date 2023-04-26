#ifndef GGAF_DX_CONFIG_H_
#define GGAF_DX_CONFIG_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/core/Config.h"

#ifdef CONFIG
    #undef CONFIG
#endif
#define CONFIG GgafDx::Config

#define MAX_SCREENS 2
#define PRIMARY_SCREEN 0
#define SECONDARY_SCREEN 1

namespace GgafDx {



class Config: public GgafCore::Config {
public:
    template <class T>
    struct GGAFRECT {
      T LEFT;
      T TOP;
      T WIDTH;
      T HEIGHT;
    };
    template <class T>
    struct GGAFSIZE {
      T WIDTH;
      T HEIGHT;
    };

    /** [r] フルスクリーンモードであるかどうかConfig */
    static bool FULL_SCREEN;
    /** [r] ２画面モードであるかどうか */
//    static bool DUAL_SCREEN;
    static int NUMBER_OF_SCREENS_USED;
    /** [r] ゲーム空間領域幅の基準値 */
    static pixcoord GAME_BUFFER_WIDTH;
    /** [r] ゲーム空間領域高さ基準値 */
    static pixcoord GAME_BUFFER_HEIGHT;
    /** [r] ゲーム空間領域深さ割合の基準値 */
    static double GAME_SPACE_DEPTH;
    /** [r] 通常の段階レンダリング深度の数(デフォルト256) */
    static int RENDER_DEPTH_INDEXS_NUM;
    /** [r] 特別に前面に描画する段階レンダリング深度の数(デフォルト10) */
    static int RENDER_DEPTH_INDEXS_NUM_EX_NEAR;
    /** [r] 特別に背面に描画する段階レンダリング深度の数(デフォルト10) */
    static int RENDER_DEPTH_INDEXS_NUM_EX_FAR;
    /** [r]  通常の段階レンダリングを開始するカメラから最遠点の距離の割合 */
    static double RENDER_DEPTH_STAGE_RATIO;
    /** [r] 射影変換を正射影で行う場合はtrue。デフォルトはfalse */
    static bool PRJ_2D_MODE;
    /** [r] 描画先サーフェイス幅のピクセルサイズ */
    static pixcoord RENDER_TARGET_BUFFER_WIDTH;
    /** [r] 描画先サーフェイス高さのピクセルサイズ */
    static pixcoord RENDER_TARGET_BUFFER_HEIGHT;

    static int SCREEN_DISPLAY_NO[MAX_SCREENS];
    /** [r/w] フルスクリーンモード時、１画面目のデイスプレイ番号(0～) */
    static int& PRIMARY_SCREEN_DISPLAY_NO;
    /** [r/w] フルスクリーンモード時、２画面目のデイスプレイ番号(0～) */
    static int& SECONDARY_SCREEN_DISPLAY_NO;
    /** [r/w] フルスクリーンモード時、３画面目のデイスプレイ番号(0～) */
//    static int TERTIARY_SCREEN_DISPLAY_NO;

    static GGAFRECT<pixcoord> SCREEN_RENDER_BUFFER_SOURCE[MAX_SCREENS];
    /** [r] 描画先サーフェイス（RENDER_TARGET_BUFFER）の中から、実際にゲームに表示するコピー元バッファのクリッピング領域 */
    static pixcoord& PRIMARY_SCREEN_RENDER_BUFFER_SOURCE_LEFT;
    static pixcoord& PRIMARY_SCREEN_RENDER_BUFFER_SOURCE_TOP;
    static pixcoord& PRIMARY_SCREEN_RENDER_BUFFER_SOURCE_WIDTH;
    static pixcoord& PRIMARY_SCREEN_RENDER_BUFFER_SOURCE_HEIGHT;
    /** [r] 描画先サーフェイス（RENDER_TARGET_BUFFER）の中から、実際にゲームに表示するコピー元バッファのクリッピング領域 */
    static pixcoord& SECONDARY_SCREEN_RENDER_BUFFER_SOURCE_LEFT;
    static pixcoord& SECONDARY_SCREEN_RENDER_BUFFER_SOURCE_TOP;
    static pixcoord& SECONDARY_SCREEN_RENDER_BUFFER_SOURCE_WIDTH;
    static pixcoord& SECONDARY_SCREEN_RENDER_BUFFER_SOURCE_HEIGHT;
    /** [r] 描画先サーフェイス（RENDER_TARGET_BUFFER）の中から、実際にゲームに表示するコピー元バッファのクリッピング領域 */
//    static pixcoord TERTIARY_SCREEN_RENDER_BUFFER_SOURCE_LEFT;
//    static pixcoord TERTIARY_SCREEN_RENDER_BUFFER_SOURCE_TOP;
//    static pixcoord TERTIARY_SCREEN_RENDER_BUFFER_SOURCE_WIDTH;
//    static pixcoord TERTIARY_SCREEN_RENDER_BUFFER_SOURCE_HEIGHT;

    static GGAFSIZE<pixcoord> SCREEN_WINDOW[MAX_SCREENS];
    /** [r] ２画面ウィンドウモードだった場合の１画面目のウィンドウの初期幅サイズ */
    static pixcoord& PRIMARY_SCREEN_WINDOW_WIDTH;
    /** [r] ２画面ウィンドウモードだった場合の１画面目のウィンドウの初期高さサイズ */
    static pixcoord& PRIMARY_SCREEN_WINDOW_HEIGHT;
    /** [r] ２画面ウィンドウモードだった場合の２画面目のウィンドウの初期幅サイズ */
    static pixcoord& SECONDARY_SCREEN_WINDOW_WIDTH;
    /** [r] ２画面ウィンドウモードだった場合の２画面目のウィンドウの初期高さサイズ */
    static pixcoord& SECONDARY_SCREEN_WINDOW_HEIGHT;

    static GGAFSIZE<pixcoord> SCREEN_FULL_SCREEN[MAX_SCREENS];
    /** [r] ２画面フルスクリーンモードだった場合の１画面目スクリーンの画面解像度(横) */
    static pixcoord& PRIMARY_SCREEN_FULL_SCREEN_WIDTH;
    /** [r] ２画面フルスクリーンモードだった場合の１画面目スクリーンの画面解像度(縦) */
    static pixcoord& PRIMARY_SCREEN_FULL_SCREEN_HEIGHT;
    /** [r] ２画面フルスクリーンモードだった場合の２画面目スクリーンの画面解像度(横) */
    static pixcoord& SECONDARY_SCREEN_FULL_SCREEN_WIDTH;
    /** [r] ２画面フルスクリーンモードだった場合の２画面目スクリーンの画面解像度(縦) */
    static pixcoord& SECONDARY_SCREEN_FULL_SCREEN_HEIGHT;


    static bool SCREEN_ASPECT_RATIO_FIXED[MAX_SCREENS];
    /** [r/w] １画面目表示領域アスペクト比をゲームバッファの縦横比で固定にするかどうか(true=固定/false=固定にしない) */
    static bool& PRIMARY_SCREEN_ASPECT_RATIO_FIXED;
    /** [r/w] ２画面目表示領域アスペクト比をゲームバッファの縦横比で固定にするかどうか(true=固定/false=固定にしない) */
    static bool& SECONDARY_SCREEN_ASPECT_RATIO_FIXED;

    /** [r/w] ２画面モード時、１画面目と２画面目を入れ替えるかどうか */
    static bool SWAP_SCREEN;

    static int SCREEN_PRESENT_POSITION[MAX_SCREENS];
    /** [r] ２画面モード時かつゲーム表示領域アスペクト比を固定時、１画面目の表示領域場所を指定(場所＝テンキーの数値) */
    static int& PRIMARY_SCREEN_PRESENT_POSITION;
    /** [r] ２画面モード時かつゲーム表示領域アスペクト比を固定時、２画面目の表示領域場所を指定(場所＝テンキーの数値) */
    static int& SECONDARY_SCREEN_PRESENT_POSITION;

    static GGAFSIZE<double> SCREEN_RATIO[MAX_SCREENS];
    /** [r/w] アスペクト比固定の場合、ゲーム表示領域の横幅調整乗率（１画面目） */
    static double& PRIMARY_SCREEN_WIDTH_RATIO;
    /** [r/w] アスペクト比固定の場合、ゲーム表示領域の高さ調整乗率（１画面目） */
    static double& PRIMARY_SCREEN_HEIGHT_RATIO;
    /** [r/w] アスペクト比固定の場合、ゲーム表示領域の横幅調整乗率（２画面目） */
    static double& SECONDARY_SCREEN_WIDTH_RATIO;
    /** [r/w] アスペクト比固定の場合、ゲーム表示領域の高さ調整乗率（２画面目） */
    static double& SECONDARY_SCREEN_HEIGHT_RATIO;

    /** [r/w] ゲーム表示領域アスペクト比を固定時、ゲーム表示領域外の背景色 */
    static std::string BORDER_COLOR;
    /** [r/w] ゲーム表示領域内の背景色 */
    static std::string BG_COLOR;
    /** [r/w] マスターボリューム(GGAF_MIN_VOLUME ～ GGAF_MAX_VOLUME) */
    static int MASTER_VOLUME;
    /** [r/w] BGM ボリューム(GGAF_MIN_VOLUME ～ GGAF_MAX_VOLUME) */
    static int BGM_VOLUME;
    /** [r/w] SoundEffect ボリューム(GGAF_MIN_VOLUME ～ GGAF_MAX_VOLUME) */
    static int SE_VOLUME;
    /** [r/w] SE最大同時発声数(1～64) */
    static int MAX_SE_AT_ONCE;
    /** [r/w] ゲーム空間でカメラからの最遠距離(zf)のに位置したアクターのSE発声遅延ミリ秒数 */
    static int SE_DELAY_MSEC_MAX_DEPTH;
    /** [r/w] ゲーム空間でカメラからの最遠距離(zf)のに位置したアクターのSE発声ボリュームの減衰割合 */
    static double SE_VOLUME_RATE_MAX_DEPTH;

    /** [r] 3Dモデルの定義ファイル(modelxファイル)の格納ディレクトリ名 */
    static std::string DIRNAME_RESOURCE_SKIN_XXX_MODEL;
    /** [r] 3Dメッシュモ定義ファイル(Xファイル)の格納ディレクトリ名 */
    static std::string DIRNAME_RESOURCE_SKIN_XXX_MESH;
    /** [r] 3Dポイントスプライト定義ファイル(Xファイル)の格納ディレクトリ名 */
    static std::string DIRNAME_RESOURCE_SKIN_XXX_POINT_SPRITE3D;
    /** [r] 2Dスプライトモデルの定義ファイル(sprx)の格納ディレクトリ名 */
    static std::string DIRNAME_RESOURCE_SKIN_XXX_SPRITE;
    /** [r] テクスチャファイルの格納ディレクトリ名 */
    static std::string DIRNAME_RESOURCE_SKIN_XXX_TEXTURE;
    /** [r] エフェクトファイル(fxファイル)の格納ディレクトリ名 */
    static std::string DIRNAME_RESOURCE_SKIN_XXX_EFFECT;
    /** [r] BGMファイル(oggファイル)の格納ディレクトリ名 */
    static std::string DIRNAME_RESOURCE_SKIN_XXX_BGM;
    /** [r] SoundEffectファイル(waveファイル)の格納ディレクトリ名 */
    static std::string DIRNAME_RESOURCE_SKIN_XXX_SE;

    /** [r] エフェクトファイル(fxファイル)を実行時にコンパイルするかどうか */
    static bool REALTIME_EFFECT_COMPILE;

    /** [r] 不正な場合に代わりに貼り付けられるテクスチャファイル */
    static std::string ILLIGAL_TEXTURE;
    /** [r] 不正な場合に代わりに貼り付けられる環境マップテクスチャファイル */
    static std::string ILLIGAL_CUBEMAP_TEXTURE;
    /** [r] 何も無かった場合に貼り付けられる白無地のテクスチャ */
    static std::string WHITE_TEXTURE;
    /** [r] AABox当たり判定要素表示用のモデル */
    static std::string COLI_AABOX_MODEL;
    /** [r] AAPrism当たり判定要素表示用のモデル */
    static std::string COLI_AAPRISM_MODEL;
    /** [r] AAPyramid当たり判定要素表示用のモデル */
    static std::string COLI_AAPYRAMID_MODEL;
    /** [r] 球の当たり判定要素表示用のモデル */
    static std::string COLI_SPHERE_MODEL;
    static std::string COLI_AABOARDRECT_MODEL;
    ////// 以下は、上記プロパティから生成される読み出し専用プロパティ ////////
    /** [r] 3Dモデル定義ファイル(modelxファイル)の格納ディレクトリ(0:システム/1:ユーザー/2:直下) */
    static std::string DIR_MODEL[3];
    /** [r] 3Dメッシュ定義ファイル(Xファイル)の格納ディレクトリ(0:システム/1:ユーザー/2:直下) */
    static std::string DIR_MESH[3];
    /** [r] 3Dメッシュ定義ファイル(Xファイル)の格納ディレクトリ(0:システム/1:ユーザー/2:直下) */
    static std::string DIR_POINT_SPRITE3D[3];
    /** [r] 2Dスプライト定義ファイル(sprxファイル)の格納ディレクトリ(0:システム/1:ユーザー/2:直下) */
    static std::string DIR_SPRITE[3];
    /** [r] テクスチャファイルの格納ディレクトリ(0:システム/1:ユーザー/2:直下) */
    static std::string DIR_TEXTURE[3];
    /** [r] エフェクトファイル(fxファイル)の格納ディレクトリ(0:システム/1:ユーザー/2:直下) */
    static std::string DIR_EFFECT[3];
    /** [r] BGMファイル(oggファイル)の格納ディレクトリ(0:システム/1:ユーザー/2:直下) */
    static std::string DIR_BGM[3];
    /** [r] SoundEffectファイル(waveファイル)の格納ディレクトリ(0:システム/1:ユーザー/2:直下) */
    static std::string DIR_SE[3];

    /** [r] スプライン曲線座標情報ファイル(datファイル)格納ディレクトリ名 */
    static std::string DIRNAME_RESOURCE_CURVE;
    /** [r] スプライン曲線座標情報ファイル(datファイル)格納ディレクトリ */
    static std::string DIR_CURVE;

    static GGAFSIZE<pixcoord> SCREEN_FULL_SCREEN_BK[MAX_SCREENS];
    /** [r] フルスクリーンモードだった場合の１画面目スクリーンの補正前解像度(横) */
    static pixcoord& PRIMARY_SCREEN_FULL_SCREEN_WIDTH_BK;
    /** [r] フルスクリーンモードだった場合の１画面目スクリーンの補正前解像度(縦) */
    static pixcoord& PRIMARY_SCREEN_FULL_SCREEN_HEIGHT_BK;
    /** [r] フルスクリーンモードだった場合の２画面目スクリーンの補正前解像度(横) */
    static pixcoord& SECONDARY_SCREEN_FULL_SCREEN_WIDTH_BK;
    /** [r] フルスクリーンモードだった場合の２画面目スクリーンの補正前解像度(縦) */
    static pixcoord& SECONDARY_SCREEN_FULL_SCREEN_HEIGHT_BK;

    /** [r] ワールドヒットチェックの八分木空間レベル数 */
    static int WORLD_HIT_CHECK_OCTREE_LEVEL;
    /** [r] ワールドヒットチェックの四分木空間レベル数 */
    static int WORLD_HIT_CHECK_QUADTREE_LEVEL;
    /** [r] ビューヒットチェックの四分木空間レベル数 */
    static int VIEW_HIT_CHECK_QUADTREE_LEVEL;
    /** [r] ヒットチェックに使用する空間分割、true：四分木場合／false：八分木（デフォルト） */
    static bool ENABLE_WORLD_HIT_CHECK_2D;

    static int P1_JOY_STICK_DEVICE_NO;
    static int P2_JOY_STICK_DEVICE_NO;
public:
    static void loadProperties(std::string prm_properties_filename); //shadows
};

}
#endif /*GGAF_DX_CONFIG_H_*/

