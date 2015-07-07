#ifndef GGAFDXCORE_GGAFDXSPACETIME_H_
#define GGAFDXCORE_GGAFDXSPACETIME_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/core/scene/GgafSpacetime.h"

#include "jp/ggaf/dxcore/actor/camera/GgafDxCamera.h"

namespace GgafDxCore {

/**
 * GgafDxCore���O��Ԃ̂��̐��N���X.
 * GgafDxCore���O��ԓ��ł́A���̃N���X�����̂��̐��N���X�Ƃ��܂��B<BR>
 * (��GgafDxWorldBound)
 * @version 1.00
 * @since 2008/07/30
 * @author Masatoshi Tsuge
 */
class GgafDxSpacetime : public GgafCore::GgafSpacetime {

private:
    /**
     * �t���[�����̕`�揈�� .
     * �i�K�����_�����O���s�Ȃ����� void GgafElement<T>::draw() ���I�[�o�[���C�h�B<BR>
     * �{�N���X(GgafSpacetime)�͒��_�̃V�[���ł��邽�߁A���̑��̃A�N�^�[��V�[���̑S�ẮA<BR>
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
    static GgafDxFigureActor* _apFirstActor_draw_depth_level[];
    /** �����_�����O�����z��ɓo�^����Ă���e�A�N�^�[���X�g�̖����̃A�N�^�[�̔z�� */
    static GgafDxFigureActor* _apLastActor_draw_depth_level[];

    /** �`��A�N�^�[�̃J�[�\�� */
    static GgafDxFigureActor* _pActor_draw_active;


    static int _FUNC_DRAW_DEP[];

    /** [r]�A�v���P�[�V�����̈�AX���W�̍ŏ��l */
    const coord _x_bound_left;
    /** [r]�A�v���P�[�V�����̈�AX���W�̍ő�l */
    const coord _x_bound_right;
    /** [r]�A�v���P�[�V�����̈�AY���W�̍ŏ��l */
    const coord _y_bound_bottom;
    /** [r]�A�v���P�[�V�����̈�AY���W�̍ő�l */
    const coord _y_bound_top;
    /** [r]�A�v���P�[�V�����̈�AZ���W�̍ŏ��l */
    const coord _z_bound_near;
    /** [r]�A�v���P�[�V�����̈�AZ���W�̍ő�l */
    const coord _z_bound_far;

    static std::string _seqkey_se_delay;

//    D3DCOLORVALUE _colFog;


public:
    GgafDxSpacetime(const char* prm_name, GgafDxCamera* prm_pCamera);

    virtual void processSettlementBehavior() override;

    virtual ~GgafDxSpacetime();

    virtual GgafDxCamera* getCamera() {
        return _pCamera;
    }

    /**
     * �`�惌�x���i�����j��o�^ .
     * ���Ȃǔ������͂�����ɓo�^���������A������x�O��֌W���������\�������B
     * @param prm_draw_depth_level ���x��
     * @param prm_pActor �A�N�^�[
     */
    static int setDrawDepthLevel(int prm_draw_depth_level, GgafDxFigureActor* prm_pActor);

    void registerSe(GgafDxSe* prm_pSe,
                    int prm_volume,
                    float prm_pan,
                    float prm_rate_frequency,
                    int prm_delay,
                    GgafDxGeometricActor* prm_pActor);

};

}
#endif /*GGAFDXCORE_GGAFDXSPACETIME_H_*/
