#ifndef GGAFDXCORE_GGAFDXUNIVERSE_H_
#define GGAFDXCORE_GGAFDXUNIVERSE_H_
#include "jp/ggaf/core/scene/GgafUniverse.h"

#include "jp/ggaf/dxcore/GgafDxGod.h"
#include "jp/ggaf/dxcore/actor/GgafDxCamera.h"

#ifdef P_GOD
    #undef P_UNIVERSE
    #define P_UNIVERSE ((GgafDxCore::GgafDxUniverse*)(P_GOD->_pUniverse))
    #undef P_CAM
    #define P_CAM (P_UNIVERSE->_pCamera)
#else
    #undef P_UNIVERSE
    #undef P_CAM
#endif

namespace GgafDxCore {

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
        GgafDxSe* _apSe[64];
        int _volume[64];
        float _pan[64];
        float _rate_frequency[64];
        GgafDxGeometricActor* _apActor[64];
        SeArray();

        void add(GgafDxSe* prm_pSe, int prm_volume, float prm_pan, float prm_rate_frequency, GgafDxGeometricActor* prm_pActor);

        void play(int index);
    };
    GgafCore::GgafLinkedListRing<SeArray>* _pRing_pSeArray;

public:
    /** �J���� */
    GgafDxCamera* _pCamera;

    /** �����_�����O�����z��ɓo�^����Ă���e�A�N�^�[���X�g�̐擪�̃A�N�^�[�̔z�� */
    static GgafDxDrawableActor* _apAlphaActorFirstList_DrawDepthLevel[];
    /** �����_�����O�����z��ɓo�^����Ă���e�A�N�^�[���X�g�̖����̃A�N�^�[�̔z�� */
    static GgafDxDrawableActor* _apAlphaActorLastList_DrawDepthLevel[];

    /** �`��A�N�^�[�̃J�[�\�� */
    static GgafDxDrawableActor* _pActor_DrawActive;

    /** [r]�A�v���P�[�V�����̈�AX���W�̍ŏ��l */
    static coord _X_gone_left;
    /** [r]�A�v���P�[�V�����̈�AX���W�̍ő�l */
    static coord _X_gone_right;
    /** [r]�A�v���P�[�V�����̈�AY���W�̍ő�l */
    static coord _Y_gone_top;
    /** [r]�A�v���P�[�V�����̈�AY���W�̍ŏ��l */
    static coord _Y_gone_bottom;
    /** [r]�A�v���P�[�V�����̈�AZ���W�̍ő�l */
    static coord _Z_gone_far;
    /** [r]�A�v���P�[�V�����̈�AZ���W�̍ŏ��l */
    static coord _Z_gone_near;
    static std::string _seqkey_se_delay;

//    D3DCOLORVALUE _colFog;


public:
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

    void registerSe(GgafDxSe* prm_pSe,
                    int prm_volume,
                    float prm_pan,
                    float prm_rate_frequency,
                    int prm_delay,
                    GgafDxGeometricActor* prm_pActor);

};

}
#endif /*GGAFDXCORE_GGAFDXUNIVERSE_H_*/
