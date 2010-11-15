#ifndef GGAFDX9SCENE_H_
#define GGAFDX9SCENE_H_
namespace GgafDx9Core {

#define MAX_BGM_PER_ACTOR 3

/**
 * GgafDx9Core名前空間、基底シーンクラス.
 * 次の機能をシーンクラスに追加しています。<BR>
 * ・BGM演奏<BR>
 * ・BGMフェードイン・フェードアウト<BR>
 * ・シーン所属の描画オブジェクトのフェードイン・フェードアウト<BR>
 * GgafDx9Core名前空間内では、このクラスを基底シーンとします。<BR>
 * @version 1.00
 * @since 2008/01/24
 * @author Masatoshi Tsuge
 */
class GgafDx9Scene : public GgafCore::GgafMainScene {
private :
    /**
     * draw() のオーバーライド禁止 .
     * 世界(GgafDx9Universe)が全ての描画を行う仕組みになりました。<BR>
     * したがって、オーバーライドしてもフレームワークより呼び出されることはありません。<BR>
     * 誤ってオーバーライドしないために private で実装。<BR>
     * GgafDx9Universe::draw() を参照せよ。<BR>
     */
    void draw() override {
    }

public :
    /** αカーテン */
    GgafDx9AlphaCurtain* _pAlphaCurtain;
    /** BGM演奏者 */
    GgafDx9BgmPerformer* _pBgmPerformer;

    /**
     * コンストラクタ .
     * @param prm_name
     * @return
     */
    GgafDx9Scene(const char* prm_name);

    /**
     * 画面フェード、BGMフェード処理 .
     * 本クラスのprocessSettlementBehavior()で、 GgafDx9AlphaCurtainとGgafDx9BgmPerformerを<BR>
     * behave() しています。オーバーライドすると、画面フェード、BGMフェードが働きません。<BR>
     * オーバーライドする場合は、必ず処理中で上位メソッドを呼び出して下さい。<BR>
     */
    virtual void processSettlementBehavior() override;


    /**
     * 自ツリーシーンをフェードインさせる .
     * 自シーンを含む配下全てのシーンについて、シーン所属オブジェクトのフェードインを行います。<BR>
     * フェードインは具体的には、シーン所属オブジェクトに対して、<BR>
     * 描画時にα値に0.0～1.0を変化させなが乗算する事を行います。<BR>
     * サブシーンに影響を与えず、自シーンのみのフェードインを行うには<BR>
     * <pre>
     * _pAlphaCurtain->open(1.0 / prm_frame_fade); //αカーテンオープン
     * </pre>
     * とすることで可能です。<BR>
     * @param prm_frame_fade 0% -> 100%になるまでの実行フレーム数
     */
    void fadeinSceneTree(int prm_frame_fade);

    /**
     * 自シーンのみのフェードイン .
     * @param prm_frame_fade 0% -> 100%になるまでの実行フレーム数
     */
    void fadeinScene(int prm_frame_fade);

    /**
     * 自ツリーシーンをフェードアウトさせる .
     * 自シーンを含む配下全てのシーンについて、シーン所属オブジェクトのフェードアウトを行います。<BR>
     * フェードアウトは具体的には、シーン所属オブジェクトに対して、<BR>
     * 描画時にα値に1.0～0.0を変化させなが乗算する事を行います。<BR>
     * サブシーンに影響を与えず、自シーンのみフェードアウトさせるには<BR>
     * <pre>
     * _pAlphaCurtain->close(1.0 / prm_frame_fade); //αカーテンクローズ
     * </pre>
     * とすることで可能です。<BR>
     * @param prm_frame_fade 100% -> 0%になるまでの実行フレーム数
     */
    void fadeoutSceneTree(int prm_frame_fade);

    /**
     * 自シーンのみのフェードアウト .
     * @param prm_frame_fade 100% -> 0%になるまでの実行フレーム数
     */
    void fadeoutScene(int prm_frame_fade);

    /**
     * 暗転
     */
    void blackoutScene();

    virtual ~GgafDx9Scene();
};

}
#endif /*GGAFDX9SCENE_H_*/
