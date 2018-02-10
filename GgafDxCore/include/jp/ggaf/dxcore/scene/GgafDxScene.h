#ifndef GGAFDXCORE_GGAFDXSCENE_H_
#define GGAFDXCORE_GGAFDXSCENE_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/core/scene/GgafMainScene.h"

#include "jp/ggaf/core/util/GgafCurtain.hpp"

namespace GgafDxCore {

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
     * draw() のオーバーライド禁止 .
     * 世界(GgafDxSpacetime)が全ての描画を行う仕組みになりました。<BR>
     * したがって、オーバーライドしてもフレームワークより呼び出されることはありません。<BR>
     * 誤ってオーバーライドしないために private で実装。<BR>
     * GgafDxSpacetime::draw() を参照せよ。<BR>
     */
    void draw() override {
    }

public :
    /** [r]シーンのフェードイン・アウト用カーテン（デフォルトではαカーテン） */
    GgafDxSceneCurtain* _pCurtain;
    /** [r]BGM演奏者 */
    GgafDxBgmConductor* _pConductor;
    /** [r]シーンのα */
    float _scene_alpha;
    float _scene_alpha_from_top;
public:
    /**
     * コンストラクタ .
     * @param prm_name
     * @return
     */
    GgafDxScene(const char* prm_name, GgafCore::GgafSceneMediator* prm_pSceneMediator = nullptr);

    void setSceneAlpha(float prm_scene_alpha);
    float getSceneAlpha();
    void addSceneAlpha(float prm_scene_alpha);

    void setSceneAlphaFromTop(float prm_scene_alpha_from_top);
    float getSceneAlphaFromTop();

    /**
     * カーテンを付け替える .
     * @param prm_pCurtain_new 新しいカーテン
     */
    void chengeCurtain(GgafDxSceneCurtain* prm_pCurtain_new);

    GgafDxSceneCurtain* getSceneCurtain() {
        return _pCurtain;
    }

    virtual void processPreJudgement() override;

    virtual void pauseTree() override;
    virtual void pause() override;

    virtual void unpauseTree() override;
    virtual void unpause() override;

    /**
     * 自シーンのアクターをフェードインさせる .
     * @param prm_frame_fade アルファ値が 1.0 になるまでの実行フレーム数(0～)
     */
    void fadeinScene(int prm_frame_fade);

    /**
      * 自シーンのアクターをフェードアウトさせる .
     * @param prm_frame_fade アルファ値が 0.0 になるまでの実行フレーム数(0～)
     */
    void fadeoutScene(int prm_frame_fade);


    void fadeoutBgm(int prm_frame_fade);
    void fadeoutBgmTree(int prm_frame_fade);

    /**
     * 自シーンのアクターをフェードアウトさせると同時に、BGMもフェードアウトさせる .
     * BGMは、シーンメンバーの _pConductor(GgafDxBgmConductorオブジェクト) で
     * 演奏されていることが前提。
     * @param prm_frame_fade フェードアウトフレーム数
     */
    void fadeoutSceneWithBgm(int prm_frame_fade);

    /**
     * 自ツリーシーンのアクターをフェードアウトさせると同時に、BGMもフェードアウトさせる .
     * BGMは、シーンメンバーの _pConductor(GgafDxBgmConductorオブジェクト) で
     * 演奏されていることが前提。
     * @param prm_frame_fade フェードアウトフレーム数
     */
    void fadeoutSceneWithBgmTree(int prm_frame_fade);


    inline GgafDxBgmConductor* getBgmConductor() {
        return _pConductor;
    }

    virtual void onEnd() override;

    virtual ~GgafDxScene();
};

}
#endif /*GGAFDXCORE_GGAFDXSCENE_H_*/
