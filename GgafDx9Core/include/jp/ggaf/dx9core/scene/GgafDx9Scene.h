#ifndef GGAFDX9SCENE_H_
#define GGAFDX9SCENE_H_
namespace GgafDx9Core {

#define MAX_BGM_PER_ACTOR 3

/**
 * GgafDx9Core���O��ԁA���V�[���N���X.
 * GgafMainScene ���p�����������ł��B<BR>
 * GgafDx9Core���O��ԓ��ł́A���̃N���X�����V�[���Ƃ��܂��B<BR>
 * @version 1.00
 * @since 2008/01/24
 * @author Masatoshi Tsuge
 */
class GgafDx9Scene : public GgafCore::GgafMainScene {
private :
    /**
     * draw()�̎g�p�֎~ .
     * ���E(GgafDx9Universe)���S�Ă̕`����s���d�g�݂ɂȂ�܂����B
     * GgafDx9Universe::draw() ���Q�Ƃ���B
     * �m�[�h�c���[�p draw ���\�b�h�����ʂŎg���Ȃ��悤�ɂ��邽��private�Ŏ����B
     */
    void draw() override {
    }

    void processPreJudgement() override;

public :
    /** �s�v�c�ȃ��J�[�e�� */
    GgafDx9AlphaCurtain* _pAlphaCurtain;
    /** BGM���t�� */
    GgafDx9BgmPerformer* _pBgmPerformer;
    GgafDx9Scene(const char* prm_name);

    void fadeinAlpha(int prm_frame_fade);

    void fadeoutAlpha(int prm_frame_fade);

    virtual ~GgafDx9Scene();
};

}
#endif /*GGAFDX9SCENE_H_*/
