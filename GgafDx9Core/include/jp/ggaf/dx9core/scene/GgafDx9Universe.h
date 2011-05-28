#ifndef GGAFDX9UNIVERSE_H_
#define GGAFDX9UNIVERSE_H_

namespace GgafDx9Core {

#ifdef P_UNIVERSE
    #define P_CAM (P_UNIVERSE->_pCamera)
#else
    #error P_UNIVERSE isnt define
#endif

/**
 * GgafDx9Core���O��Ԃ̂��̐��N���X.
 * GgafDx9Core���O��ԓ��ł́A���̃N���X�����̂��̐��N���X�Ƃ��܂��B<BR>
 * (��GgafDx9WorldBound)
 * @version 1.00
 * @since 2008/07/30
 * @author Masatoshi Tsuge
 */
class GgafDx9Universe : public GgafCore::GgafUniverse {

private:
    /**
     * �t���[�����̕`�揈�� .
     * �i�K�����_�����O���s�Ȃ����� void GgafElement<T>::draw() ���I�[�o�[���C�h�B<BR>
     * �{�N���X(GgafUniverse)�͒��_�̃V�[���ł��邽�߁A���̑��̃A�N�^�[��V�[���̑S�ẮA<BR>
     * void GgafElement<T>::draw() ���Ă΂�邱�Ƃ������ł��傤�B<BR>
     */
    virtual void draw() override;

public:
    class SeArray {
    public:
        int _p;
        GgafDx9Se* _apSe[MAX_SE_AT_ONCE];
        LONG _volume[MAX_SE_AT_ONCE];
        float _pan[MAX_SE_AT_ONCE];
        float _rate_frequency[MAX_SE_AT_ONCE];

        SeArray();

        void add(GgafDx9Se* prm_pSe, LONG prm_volume, float prm_pan, float prm_rate_frequency);

        void play(int index);
    };
    GgafCore::GgafLinkedListRing<SeArray>* _pRing_pSeArray;

public:

    /** �J���� */
    GgafDx9Camera* _pCamera;

    /** �A�N�^�[���������_�����O�̂��߂̉����ʂ̃O���[�v */
    static GgafDx9DrawableActor* _apAlphaActorList_DrawDepthLevel[];
    /** �A�N�^�[���������_�����O�ŉ��O���[�v(��ԍŏ��Ƀ����_�����O) */
    static GgafDx9DrawableActor* _pActors_DrawMaxDrawDepth;
    static GgafDx9DrawableActor* _pActor_DrawActive;


    static int _X_goneLeft;
    static int _X_goneRight;
    static int _Y_goneTop;
    static int _Y_goneBottom;
    static int _Z_goneFar;
    static int _Z_goneNear;

//    GgafDx9TextureManager* _pCubeMapTextureManager;


    GgafDx9Universe(const char* prm_name, GgafDx9Camera* prm_pCamera);

    virtual void processSettlementBehavior() override;

    virtual ~GgafDx9Universe();



    /**
     * �`�惌�x���i�����j��o�^ .
     * ���Ȃǔ������͂�����ɓo�^���������A������x�O��֌W���������\�������B
     * @param prm_draw_depth_level ���x��
     * @param prm_pActor �A�N�^�[
     */
    static int setDrawDepthLevel(int prm_draw_depth_level, GgafDx9DrawableActor* prm_pActor);


    void registSe(GgafDx9Se* prm_pSe, LONG prm_volume, float prm_pan, float prm_rate_frequency, int prm_delay );

//    /**
//     * �`�惌�x���i�����j���ŉ��œo�^.
//     * �s�����ȃI�u�W�F�N�g�͋ɗ͂�����œo�^����
//     * @param prm_pActor �A�N�^�[
//     */
//    static void setDrawDepthMaxLevel(GgafDx9DrawableActor* prm_pActor);
};

}
#endif /*GGAFDX9UNIVERSE_H_*/
