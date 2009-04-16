#ifndef GGAFDX9WORLD_H_
#define GGAFDX9WORLD_H_
namespace GgafDx9Core {

#define MAX_DRAW_DEPTH_LEVEL 10000

/**
 * GgafDx9Core���O��Ԃ̐��E�N���X.
 * GgafDx9Core���O��ԓ��ł́A���̃N���X�����̐��E�N���X�Ƃ��܂��B<BR>
 */
class GgafDx9World : public GgafCore::GgafWorld {

public:

    /** �J���� */
    static GgafDx9Camera* _pCamera;

    /** �A�N�^�[���������_�����O�̂��߂̉����ʂ̃O���[�v */
    static GgafCore::GgafActor* _apAlphaActorList_DrawDepthLevel[];
    /** �A�N�^�[���������_�����O�ŉ��O���[�v(��ԍŏ��Ƀ����_�����O) */
    static GgafCore::GgafActor* _pActors_DrawMaxDrawDepth;

    GgafDx9World(const char* prm_name);

    virtual ~GgafDx9World();

    /**
     * �t���[�����̕`�揈��<BR>
     */
    virtual void drawMain();

    /**
     * �`�惌�x���i�����j��o�^ .
     * ���Ȃǔ������͂�����ɓo�^���������A������x�O��֌W���������\�������B
     * @param prm_draw_depth_level ���x��
     * @param prm_pActor �A�N�^�[
     */
    static void setDrawDepthLevel(int prm_draw_depth_level, GgafCore::GgafActor* prm_pActor);

    /**
     * �`�惌�x���i�����j���ŉ��œo�^.
     * �s�����ȃI�u�W�F�N�g�͋ɗ͂�����œo�^����
     * @param prm_pActor �A�N�^�[
     */
    static void setDrawDepthMaxLevel(GgafCore::GgafActor* prm_pActor);
};

}
#endif /*GGAFDX9WORLD_H_*/
