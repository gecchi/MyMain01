#ifndef GGAFDX9UNIVERSE_H_
#define GGAFDX9UNIVERSE_H_

#define pCAM GgafDx9Universe::_pCamera

namespace GgafDx9Core {

#define MAX_DRAW_DEPTH_LEVEL 1000

/**
 * GgafDx9Core���O��Ԃ̂��̐��N���X.
 * GgafDx9Core���O��ԓ��ł́A���̃N���X�����̂��̐��N���X�Ƃ��܂��B<BR>
 */
class GgafDx9Universe : public GgafCore::GgafUniverse {

public:

    /** �J���� */
    static GgafDx9Camera* _pCamera;

    /** �A�N�^�[���������_�����O�̂��߂̉����ʂ̃O���[�v */
    static GgafDx9DrawableActor* _apAlphaActorList_DrawDepthLevel[];
    /** �A�N�^�[���������_�����O�ŉ��O���[�v(��ԍŏ��Ƀ����_�����O) */
    static GgafDx9DrawableActor* _pActors_DrawMaxDrawDepth;
    static GgafDx9DrawableActor* _pActor_DrawActive;
    GgafDx9Universe(const char* prm_name);

    virtual ~GgafDx9Universe();

    /**
     * �t���[�����̕`�揈�� .
     * �i�K�����_�����O���s�Ȃ����� void GgafElement<T>::drawMain() ���I�[�o�[���C�h�B<BR>
     * �{�N���X(GgafUniverse)�͒��_�̃V�[���ł��邽�߁A���̑��̃A�N�^�[��V�[���̑S�ẮA<BR>
     * void GgafElement<T>::drawMain() ���Ă΂�邱�Ƃ������ł��傤�B<BR>
     */
    virtual void drawMain();

    /**
     * �`�惌�x���i�����j��o�^ .
     * ���Ȃǔ������͂�����ɓo�^���������A������x�O��֌W���������\�������B
     * @param prm_draw_depth_level ���x��
     * @param prm_pActor �A�N�^�[
     */
    static void setDrawDepthLevel(int prm_draw_depth_level, GgafDx9DrawableActor* prm_pActor);

    /**
     * �`�惌�x���i�����j���ŉ��œo�^.
     * �s�����ȃI�u�W�F�N�g�͋ɗ͂�����œo�^����
     * @param prm_pActor �A�N�^�[
     */
    static void setDrawDepthMaxLevel(GgafDx9DrawableActor* prm_pActor);
};

}
#endif /*GGAFDX9UNIVERSE_H_*/
