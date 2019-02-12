#ifndef GGAF_DX_SPACETIME_H_
#define GGAF_DX_SPACETIME_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/core/scene/Spacetime.h"

#include "jp/ggaf/dx/Config.h"
#include "jp/ggaf/dx/actor/camera/Camera.h"


#define EX_RENDER_DEPTH_INDEXS_FRONT_NUM   (5)
#define REGULAR_RENDER_DEPTH_INDEXS_NUM    (CONFIG::RENDER_DEPTH_INDEXS_NUM)  //�i�K�����_�[����\
#define EX_RENDER_DEPTH_INDEXS_BACK_NUM    (5)
#define ALL_RENDER_DEPTH_INDEXS_NUM        (EX_RENDER_DEPTH_INDEXS_FRONT_NUM+REGULAR_RENDER_DEPTH_INDEXS_NUM+EX_RENDER_DEPTH_INDEXS_BACK_NUM)

#define RENDER_DEPTH_INDEX_FRONT      (EX_RENDER_DEPTH_INDEXS_FRONT_NUM)  //�ʏ�̍őO��
#define RENDER_DEPTH_INDEX_BACK       (EX_RENDER_DEPTH_INDEXS_FRONT_NUM + REGULAR_RENDER_DEPTH_INDEXS_NUM - 1) //�ʏ�̍Ŕw��

 /** �őO�ʂ���O�̓��ʂȕ\���[�x���x��(0�`5  0:RENDER_DEPTH_INDEX_FRONT�Ɠ����A5:�őO��) */
#define RENDER_DEPTH_INDEX_SP_FRONT(X)  (RENDER_DEPTH_INDEX_FRONT - (X))

 /** �őO�ʂ�艜�̓��ʂȕ\���[�x���x��(0�`5  0:RENDER_DEPTH_INDEX_BACK�Ɠ����A5:�Ŕw��) */
#define RENDER_DEPTH_INDEX_SP_BACK(X)  (RENDER_DEPTH_INDEX_BACK + (X))

namespace GgafDx {

/**
 * Core���O��Ԃ̂��̐��N���X.
 * Core���O��ԓ��ł́A���̃N���X�����̂��̐��N���X�Ƃ��܂��B<BR>
 * (��WorldBound)
 * @version 1.00
 * @since 2008/07/30
 * @author Masatoshi Tsuge
 */
class Spacetime : public GgafCore::Spacetime {

private:
    /**
     * �t���[�����̕`�揈�� .
     * �i�K�����_�����O���s�Ȃ����� void GgafCore::Element<T>::draw() ���I�[�o�[���C�h�B<BR>
     * �{�N���X(GgafCore::Spacetime)�͒��_�̃V�[���ł��邽�߁A���̑��̃A�N�^�[��V�[���̑S�ẮA<BR>
     * void GgafCore::Element<T>::draw() ���Ă΂�邱�Ƃ������ł��傤�B<BR>
     */
    virtual void draw() override;

public:
    class SeArray {
    public:
        int _p;
        Se* _apSe[64];
        int _volume[64];
        float _pan[64];
        float _frequency_rate[64];
        GeometricActor* _apActor[64];
        SeArray();

        void add(Se* prm_pSe, int prm_volume, float prm_pan, float prm_frequency_rate, GeometricActor* prm_pActor);

        void play(int index);
    };
    GgafCore::LinkedListRing<SeArray>* _pRing_pSeArray;

public:
    /** �J���� */
    Camera* _pCamera;

    /** �����_�����O�����z��ɓo�^����Ă���e�A�N�^�[���X�g�̐擪�̃A�N�^�[�̔z�� */
    FigureActor** _papFirstActor_in_render_depth;
    /** �����_�����O�����z��ɓo�^����Ă���e�A�N�^�[���X�g�̖����̃A�N�^�[�̔z�� */
    FigureActor** _papLastActor_in_render_depth;

    /** �`��A�N�^�[�̃J�[�\�� */
    static FigureActor* _pActor_draw_active;
    static int render_depth_index_active;
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

    /** �I�u�W�F�N�g�̃J��������̉���(pixcoord)�ɑ΂���A�i�K�����_�����O�C���f�b�N�X�̔z�� */
    int* _paDep2Lv;
    /** �i�K�����_�����O���L���ȃJ�����i�n�_����j���牜�ւ̋��� */
    dxcoord _dep_resolution;


public:
    Spacetime(const char* prm_name, Camera* prm_pCamera);

    virtual void processSettlementBehavior() override;

    virtual ~Spacetime();

    virtual Camera* getCamera() {
        return _pCamera;
    }

    /**
     * ���̐��ɃA�N�^�[��o�^(2D�I�u�W�F�N�g�p) .
     * �o�^����ƁA���̐��ɕ`�悳��邱�ƂƂȂ�B
     * @param prm_pActor �ΏۃA�N�^�[
     * @return �o�^���ꂽ�`�揇���[�x���x��
     */
    int registerFigureActor2D(FigureActor* prm_pActor);

    /**
     * ���̐��ɃA�N�^�[��o�^(3D�I�u�W�F�N�g�p) .
     * �o�^����ƁA���̐��ɕ`�悳��邱�ƂƂȂ�B
     * ���Ȃǔ������͂�����ɓo�^���������A������x�O��֌W���������\�������B
     * @param prm_pActor �ΏۃA�N�^�[
     * @return �o�^���ꂽ�`�揇���[�x���x��
     */
    int registerFigureActor3D(FigureActor* prm_pActor);

    /**
     * ���̐��Ɍ��ʉ��I�u�W�F�N�g��o�^���� .
     * �o�^����ƁA���̐��Ɍ��ʉ������������B
     * �������ɓ������ʉ������x���o�^����ƁA���ʒ��ˏオ��h�~�̈�
     * ����ɂ΂�����Ĕ���������B
     * @param prm_pSe ���ʉ��I�u�W�F�N�g
     * @param prm_volume �{�����[��(0 �` 1000)
     * @param prm_pan    �p��(left:-1.0 �` center:0 �` right:1.0)
     * @param prm_frequency_rate ���̎��g���ɏ悸�闦
     * @param prm_delay  �x���t���[��
     * @param prm_pActor ���ʉ��������A�N�^�[
     */
    void registerSe(Se* prm_pSe,
                    int prm_volume,
                    float prm_pan,
                    float prm_frequency_rate,
                    int prm_delay,
                    GeometricActor* prm_pActor);
};

}
#endif /*GGAF_DX_SPACETIME_H_*/
