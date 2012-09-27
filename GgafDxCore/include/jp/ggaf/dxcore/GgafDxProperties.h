#ifndef GGAFDXPROPERTIES_H_
#define GGAFDXPROPERTIES_H_

#ifdef GGAF_PROPERTY
    #undef GGAF_PROPERTY
#endif
#define GGAF_PROPERTY(X) (GgafDxCore::GgafDxProperties::X)

namespace GgafDxCore {

class GgafDxProperties: public GgafCore::GgafProperties {
public:
    /** [r] フルスクリーンモードであるかどうか */
    static bool FULL_SCREEN;
    /** [r] ２画面モードであるかどうか */
    static bool DUAL_VIEW;
    /** [r] ゲーム空間領域幅の基準値 */
    static pixcoord GAME_BUFFER_WIDTH;
    /** [r] ゲーム空間領域高さ基準値 */
    static pixcoord GAME_BUFFER_HEIGHT;
    /** [r] ゲーム空間領域深さ割合の基準値 */
    static double GAME_SPACE_DEPTH;
    /** [r] 射影変換を正射影で行う場合はtrue。デフォルトはfalse */
    static bool PRJ_2D_MODE;
    /** [r] 描画先サーフェイス幅のピクセルサイズ */
    static pixcoord RENDER_TARGET_BUFFER_WIDTH;
    /** [r] 描画先サーフェイス高さのピクセルサイズ */
    static pixcoord RENDER_TARGET_BUFFER_HEIGHT;
    /** [r] １画面ウィンドウモードだった場合のウィンドウの初期幅サイズ */
    static pixcoord SINGLE_VIEW_WINDOW_WIDTH;
    /** [r] １画面ウィンドウモードだった場合のウィンドウの初期高さサイズ */
    static pixcoord SINGLE_VIEW_WINDOW_HEIGHT;
    /** [r] ２画面ウィンドウモードだった場合の１画面目のウィンドウの初期幅サイズ */
    static pixcoord DUAL_VIEW_WINDOW1_WIDTH;
    /** [r] ２画面ウィンドウモードだった場合の１画面目のウィンドウの初期高さサイズ */
    static pixcoord DUAL_VIEW_WINDOW1_HEIGHT;
    /** [r] ２画面ウィンドウモードだった場合の２画面目のウィンドウの初期幅サイズ */
    static pixcoord DUAL_VIEW_WINDOW2_WIDTH;
    /** [r] ２画面ウィンドウモードだった場合の２画面目のウィンドウの初期高さサイズ */
    static pixcoord DUAL_VIEW_WINDOW2_HEIGHT;
    /** [r] １画面フルスクリーンモードだった場合のスクリーンの解像度(横) */
    static pixcoord SINGLE_VIEW_FULL_SCREEN_WIDTH;
    /** [r] １画面フルスクリーンモードだった場合のスクリーンの解像度(縦) */
    static pixcoord SINGLE_VIEW_FULL_SCREEN_HEIGHT;
    /** [r] ２画面フルスクリーンモードだった場合の１画面目スクリーンの解像度(横) */
    static pixcoord DUAL_VIEW_FULL_SCREEN1_WIDTH;
    /** [r] ２画面フルスクリーンモードだった場合の１画面目スクリーンの解像度(縦) */
    static pixcoord DUAL_VIEW_FULL_SCREEN1_HEIGHT;
    /** [r] ２画面フルスクリーンモードだった場合の２画面目スクリーンの解像度(横) */
    static pixcoord DUAL_VIEW_FULL_SCREEN2_WIDTH;
    /** [r] ２画面フルスクリーンモードだった場合の２画面目スクリーンの解像度(縦) */
    static pixcoord DUAL_VIEW_FULL_SCREEN2_HEIGHT;
    /** [r] ２画面フルスクリーンモードだった場合の両画面のスクリーンの解像度(横) */
    static pixcoord DUAL_VIEW_FULL_SCREEN_WIDTH;
    /** [r] ２画面フルスクリーンモードだった場合の両画面のスクリーンの解像度(縦) */
    static pixcoord DUAL_VIEW_FULL_SCREEN_HEIGHT;
    /** [r/w] ゲーム表示領域アスペクト比を固定するかどうか */
    static bool FIXED_GAME_VIEW_ASPECT;
    /** [r/w] ２画面モード時、１画面目と２画面目を入れ替えるかどうか */
    static bool SWAP_GAME_VIEW;
    /** [r/w] １画面モード時かつゲーム表示領域アスペクト比を固定時、表示領域場所を指定(場所＝テンキーの数値) */
    static int SINGLE_VIEW_DRAW_POSITION;
    /** [r/w] ２画面モード時かつゲーム表示領域アスペクト比を固定時、１画面目の表示領域場所を指定(場所＝テンキーの数値) */
    static int DUAL_VIEW_DRAW_POSITION1;
    /** [r/w] ２画面モード時かつゲーム表示領域アスペクト比を固定時、２画面目の表示領域場所を指定(場所＝テンキーの数値) */
    static int DUAL_VIEW_DRAW_POSITION2;
    /** [r/w] アスペクト比固定の場合、ゲーム表示領域の横幅調整乗率（１画面目） */
    static double VIEW1_WIDTH_RATIO;
    /** [r/w] アスペクト比固定の場合、ゲーム表示領域の高さ調整乗率（１画面目） */
    static double VIEW1_HEIGHT_RATIO;
    /** [r/w] アスペクト比固定の場合、ゲーム表示領域の横幅調整乗率（２画面目） */
    static double VIEW2_WIDTH_RATIO;
    /** [r/w] アスペクト比固定の場合、ゲーム表示領域の高さ調整乗率（２画面目） */
    static double VIEW2_HEIGHT_RATIO;

    /** [r/w] ゲーム表示領域アスペクト比を固定時、ゲーム表示領域外の背景色 */
    static std::string BORDER_COLOR;
    /** [r/w] ゲーム表示領域内の背景色 */
    static std::string BG_COLOR;
    /** [r/w] マスターボリューム(0～100) */
    static int MASTER_VOLUME;
    /** [r/w] BGM ボリューム(0～100) */
    static int BGM_VOLUME;
    /** [r/w] SoundEffect ボリューム(0～100) */
    static int SE_VOLUME;

    /** [r] メッシュモデルの定義ファイル(Xファイル)の格納ディレクトリ名 */
    static std::string DIRNAME_RESOURCE_SKIN_XXX_MESH;
    /** [r] 2Dスプライトモデルの定義ファイル(sprx)の格納ディレクトリ名 */
    static std::string DIRNAME_RESOURCE_SKIN_XXX_SPRITE;
    /** [r] テクスチャファイルの格納ディレクトリ名 */
    static std::string DIRNAME_RESOURCE_SKIN_XXX_TEXTURE;
    /** [r] エフェクトファイル(fxファイル)の格納ディレクトリ名 */
    static std::string DIRNAME_RESOURCE_SKIN_XXX_EFFECT;
    /** [r] BGMファイル(oggファイル)の格納ディレクトリ名 */
    static std::string DIRNAME_RESOURCE_SKIN_XXX_OGG;
    /** [r] SoundEffectファイル(waveファイル)の格納ディレクトリ名 */
    static std::string DIRNAME_RESOURCE_SKIN_XXX_WAVE;

    /** [r] メッシュモデルの定義ファイル(Xファイル)の格納ディレクトリ(0:default/1:ユーザー/2:カレント) */
    static std::string DIR_MESH_MODEL[3];
    /** [r] 2Dスプライトモデルの定義ファイル(sprx)の格納ディレクトリ(0:default/1:ユーザー/2:カレント) */
    static std::string DIR_SPRITE_MODEL[3];
    /** [r] テクスチャファイルの格納ディレクトリ(0:default/1:ユーザー/2:カレント) */
    static std::string DIR_TEXTURE[3];
    /** [r] エフェクトファイル(fxファイル)の格納ディレクトリ(0:default/1:ユーザー/2:カレント) */
    static std::string DIR_EFFECT[3];
    /** [r] BGMファイル(oggファイル)の格納ディレクトリ(0:default/1:ユーザー/2:カレント) */
    static std::string DIR_OGG[3];
    /** [r] SoundEffectファイル(waveファイル)の格納ディレクトリ(0:default/1:ユーザー/2:カレント) */
    static std::string DIR_WAVE[3];

    /** [r] エフェクトファイル(fxファイル)を実行時にコンパイルするかどうか */
    static bool REALTIME_EFFECT_COMPILE;

    static void load(std::string prm_properties_filename); //shadows
    static void clean();                            //shadows
};

}
#endif /*GGAFDXPROPERTIES_H_*/

