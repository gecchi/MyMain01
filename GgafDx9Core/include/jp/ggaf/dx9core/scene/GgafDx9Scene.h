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
     * 逆にGgafDx9AlphaCurtainとGgafDx9BgmPerformerの機能を使用しない事が明らかなシーンは、<BR>
     * オーバーライドして潰すことにより、僅かにパフォーマンス改善できるかも知れません<BR>
     */
    virtual void processSettlementBehavior() override;


    /**
     * 自ツリーシーンのアクターをフェードインさせる .
     * @param prm_frame_fade アルファ値が 1.0 になるまでの実行フレーム数(0～)
     */
    void fadeinSceneTree(int prm_frame_fade);

    /**
     * 自シーンのアクターをフェードインさせる .
     * @param prm_frame_fade アルファ値が 1.0 になるまでの実行フレーム数(0～)
     */
    void fadeinScene(int prm_frame_fade);

    /**
     * 自ツリーシーンのアクターをフェードアウトさせる .
     * @param prm_frame_fade アルファ値が 0.0 になるまでの実行フレーム数(0～)
     */
    void fadeoutSceneTree(int prm_frame_fade);

    /**
      * 自シーンのアクターをフェードアウトさせる .
     * @param prm_frame_fade アルファ値が 0.0 になるまでの実行フレーム数(0～)
     */
    void fadeoutScene(int prm_frame_fade);


    virtual ~GgafDx9Scene();
};

}
#endif /*GGAFDX9SCENE_H_*/
