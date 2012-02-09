#ifndef GGAFDXSCENE_H_
#define GGAFDXSCENE_H_
namespace GgafDxCore {

#define MAX_BGM_PER_ACTOR 3

/**
 * GgafDxCore名前空間、基底シーンクラス.
 * 次の機能をシーンクラスに追加しています。<BR>
 * ・BGM演奏<BR>
 * ・BGMフェードイン・フェードアウト<BR>
 * ・シーン所属の描画オブジェクトのフェードイン・フェードアウト<BR>
 * GgafDxCore名前空間内では、このクラスを基底シーンとします。<BR>
 * @version 1.00
 * @since 2008/01/24
 * @author Masatoshi Tsuge
 */
class GgafDxScene : public GgafCore::GgafMainScene {
private :
    /**
     * 下位で使用禁止 .
     */
    void processFinal() override {
    }
    /**
     * draw() のオーバーライド禁止 .
     * 世界(GgafDxUniverse)が全ての描画を行う仕組みになりました。<BR>
     * したがって、オーバーライドしてもフレームワークより呼び出されることはありません。<BR>
     * 誤ってオーバーライドしないために private で実装。<BR>
     * GgafDxUniverse::draw() を参照せよ。<BR>
     */
    void draw() override {
    }

public :
    /** αカーテン */
    GgafDxAlphaCurtain* _pAlphaCurtain;
    /** BGM演奏者 */
    GgafDxBgmPerformer* _pBgmPerformer;

    /**
     * コンストラクタ .
     * @param prm_name
     * @return
     */
    GgafDxScene(const char* prm_name);

    /**
     * 画面フェード、BGMフェード処理 .
     * 本クラスのprocessSettlementBehavior()で、 GgafDxAlphaCurtainとGgafDxBgmPerformerを<BR>
     * behave() しています。オーバーライドすると、画面フェード、BGMフェードが働きません。<BR>
     * オーバーライドする場合は、必ず処理中で上位メソッドを呼び出して下さい。<BR>
     * 逆にGgafDxAlphaCurtainとGgafDxBgmPerformerの機能を使用しない事が明らかなシーンは、<BR>
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


    virtual ~GgafDxScene();
};

}
#endif /*GGAFDXSCENE_H_*/
