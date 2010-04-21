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
    void processJudgement() override;

public :
    /** 不思議なαカーテン */
    GgafDx9AlphaCurtain* _pAlphaCurtain;
    GgafDx9Scene(const char* prm_name);

    void fadein(float prm_velocity_alpha);

    void fadeinTree(float prm_velocity_alpha);

    void fadeout(float prm_velocity_alpha);

    void fadeoutTree(float prm_velocity_alpha);

    virtual ~GgafDx9Scene();
};

}
#endif /*GGAFDX9SCENE_H_*/
