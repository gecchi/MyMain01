#ifndef GGAFDX9SCENE_H_
#define GGAFDX9SCENE_H_
namespace GgafDx9Core {

#define MAX_BGM_PER_ACTOR 3

/**
 * GgafDx9Core名前空間、基底シーンクラス.
 * GgafMainScene を継承しただけです。<BR>
 * GgafDx9Core名前空間内では、このクラスを基底シーンとします。<BR>
 * @version 1.00
 * @since 2008/01/24
 * @author Masatoshi Tsuge
 */
class GgafDx9Scene : public GgafCore::GgafMainScene {
private :
    /**
     * draw()の使用禁止 .
     * 世界(GgafDx9Universe)が全ての描画を行う仕組みになりました。
     * GgafDx9Universe::draw() を参照せよ。
     * ノードツリー用 draw メソッドを下位で使えないようにするためprivateで実装。
     */
    void draw() override {
    }

    void processPreJudgement() override;

public :
    /** 不思議なαカーテン */
    GgafDx9AlphaCurtain* _pAlphaCurtain;
    /** BGM演奏者 */
    GgafDx9BgmPerformer* _pBgmPerformer;
    GgafDx9Scene(const char* prm_name);

    void fadeinAlpha(int prm_frame_fade);

    void fadeoutAlpha(int prm_frame_fade);

    virtual ~GgafDx9Scene();
};

}
#endif /*GGAFDX9SCENE_H_*/
