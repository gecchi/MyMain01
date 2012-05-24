#ifndef GGAFDXUNIVERSE_H_
#define GGAFDXUNIVERSE_H_

namespace GgafDxCore {

#ifdef P_UNIVERSE
    #define P_CAM (P_UNIVERSE->_pCamera)
#else
    #error P_UNIVERSE isnt define
#endif

/**
 * GgafDxCore���O��Ԃ̂��̐��N���X.
 * GgafDxCore���O��ԓ��ł́A���̃N���X�����̂��̐��N���X�Ƃ��܂��B<BR>
 * (��GgafDxWorldBound)
 * @version 1.00
 * @since 2008/07/30
 * @author Masatoshi Tsuge
 */
class GgafDxUniverse : public GgafCore::GgafUniverse {

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
        GgafDxSe* _apSe[MAX_SE_AT_ONCE];
        int _volume[MAX_SE_AT_ONCE];
        float _pan[MAX_SE_AT_ONCE];
        float _rate_frequency[MAX_SE_AT_ONCE];

        SeArray();

        void add(GgafDxSe* prm_pSe, int prm_volume, float prm_pan, float prm_rate_frequency);

        void play(int index);
    };
    GgafCore::GgafLinkedListRing<SeArray>* _pRing_pSeArray;

public:

    /** �J���� */
    GgafDxCamera* _pCamera;

    /** �A�N�^�[���������_�����O�̂��߂̉����ʂ̃O���[�v */
    static GgafDxDrawableActor* _apAlphaActorFirstList_DrawDepthLevel[];
    static GgafDxDrawableActor* _apAlphaActorLastList_DrawDepthLevel[];
    /** �A�N�^�[���������_�����O�ŉ��O���[�v(��ԍŏ��Ƀ����_�����O) */
    static GgafDxDrawableActor* _pActors_DrawMaxDrawDepth;
    static GgafDxDrawableActor* _pActor_DrawActive;


    static coord _X_goneLeft;
    static coord _X_goneRight;
    static coord _Y_goneTop;
    static coord _Y_goneBottom;
    static coord _Z_goneFar;
    static coord _Z_goneNear;

//    GgafDxTextureManager* _pCubeMapTextureManager;


    GgafDxUniverse(const char* prm_name, GgafDxCamera* prm_pCamera);

    virtual void processSettlementBehavior() override;

    virtual ~GgafDxUniverse();



    /**
     * �`�惌�x���i�����j��o�^ .
     * ���Ȃǔ������͂�����ɓo�^���������A������x�O��֌W���������\�������B
     * @param prm_draw_depth_level ���x��
     * @param prm_pActor �A�N�^�[
     */
    static int setDrawDepthLevel(int prm_draw_depth_level, GgafDxDrawableActor* prm_pActor);


    void registSe(GgafDxSe* prm_pSe, int prm_volume, float prm_pan, float prm_rate_frequency, int prm_delay );

//    /**
//     * �`�惌�x���i�����j���ŉ��œo�^.
//     * �s�����ȃI�u�W�F�N�g�͋ɗ͂�����œo�^����
//     * @param prm_pActor �A�N�^�[
//     */
//    static void setDrawDepthMaxLevel(GgafDxDrawableActor* prm_pActor);
};

}
#endif /*GGAFDXUNIVERSE_H_*/
