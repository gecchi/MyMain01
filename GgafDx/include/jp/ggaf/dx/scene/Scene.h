#ifndef GGAF_DX_SCENE_H_
#define GGAF_DX_SCENE_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/core/scene/MainScene.h"
#include "jp/ggaf/core/util/Curtain.hpp"

namespace GgafDx {

/**
 * Core名前空間、基底シーンクラス.
 * 次の機能をシーンクラスに追加しています。<BR>
 * ・BGM演奏<BR>
 * ・BGMフェードイン・フェードアウト<BR>
 * ・シーン所属の描画オブジェクトのフェードイン・フェードアウト<BR>
 * Core名前空間内では、このクラスを基底シーンとします。<BR>
 * @version 1.00
 * @since 2008/01/24
 * @author Masatoshi Tsuge
 */
class Scene : public GgafCore::MainScene {
private :

    /**
     * draw() のオーバーライド禁止 .
     * 世界(Spacetime)が全ての描画を行う仕組みになりました。<BR>
     * したがって、オーバーライドしてもフレームワークより呼び出されることはありません。<BR>
     * 誤ってオーバーライドしないために private で実装。<BR>
     * Spacetime::draw() を参照せよ。<BR>
     */
    void draw() override {
    }

public :
    /** [r]シーンのフェードイン・アウト用カーテン（デフォルトではαカーテン） */
    SceneCurtain* _pCurtain;
    /** [r]BGM演奏者 */
    BgmConductor* _pConductor;
    /** [r]シーンのα */
    float _scene_alpha;
    float _scene_alpha_from_top;
public:
    /**
     * コンストラクタ .
     * @param prm_name
     * @return
     */
    Scene(const char* prm_name, GgafCore::SceneMediator* prm_pSceneMediator = nullptr);

    void setSceneAlpha(float prm_scene_alpha);
    float getSceneAlpha();
    void addSceneAlpha(float prm_scene_alpha);

    void setSceneAlphaFromTop(float prm_scene_alpha_from_top);
    float getSceneAlphaFromTop();

    /**
     * カーテンを付け替える .
     * @param prm_pCurtain_new 新しいカーテン
     */
    void chengeCurtain(SceneCurtain* prm_pCurtain_new);

    SceneCurtain* getSceneCurtain() {
        return _pCurtain;
    }

    virtual void processSettlementBehavior() override;

    virtual void pause() override;

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
     * BGMは、シーンメンバーの _pConductor(BgmConductorオブジェクト) で
     * 演奏されていることが前提。
     * @param prm_frame_fade フェードアウトフレーム数
     */
    void fadeoutSceneWithBgm(int prm_frame_fade);

    /**
     * 自ツリーシーンのアクターをフェードアウトさせると同時に、BGMもフェードアウトさせる .
     * BGMは、シーンメンバーの _pConductor(BgmConductorオブジェクト) で
     * 演奏されていることが前提。
     * @param prm_frame_fade フェードアウトフレーム数
     */
    void fadeoutSceneWithBgmTree(int prm_frame_fade);


    inline BgmConductor* getBgmConductor() {
        return _pConductor;
    }

    virtual void onEnd() override;

    virtual ~Scene();
};

}
#endif /*GGAF_DX_SCENE_H_*/
