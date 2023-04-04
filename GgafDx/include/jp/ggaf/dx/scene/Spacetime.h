#ifndef GGAF_DX_SPACETIME_H_
#define GGAF_DX_SPACETIME_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/core/scene/Spacetime.h"

#include "jp/ggaf/dx/Config.h"
#include "jp/ggaf/dx/actor/camera/Camera.h"

/** �i�K�����_�����O�̒i�K���� */
#define ALL_RENDER_DEPTH_INDEXS_NUM  (CONFIG::RENDER_DEPTH_INDEXS_NUM_EX_NEAR + CONFIG::RENDER_DEPTH_INDEXS_NUM + CONFIG::RENDER_DEPTH_INDEXS_NUM_EX_FAR)

#define RENDER_DEPTH_NEAR_INDEX      (CONFIG::RENDER_DEPTH_INDEXS_NUM_EX_NEAR)  //�ʏ�̍őO��
#define RENDER_DEPTH_FAR_INDEX       (CONFIG::RENDER_DEPTH_INDEXS_NUM_EX_FAR + CONFIG::RENDER_DEPTH_INDEXS_NUM - 1) //�ʏ�̍Ŕw��

 /** �őO�ʂ���O�̓��ʂȕ\���[�x���x��(0�`5  0:RENDER_DEPTH_NEAR_INDEX�Ɠ����A5:�őO��) */
#define RENDER_DEPTH_INDEX_SP_FRONT(X)  (RENDER_DEPTH_NEAR_INDEX - (X))

 /** �őO�ʂ�艜�̓��ʂȕ\���[�x���x��(0�`5  0:RENDER_DEPTH_FAR_INDEX�Ɠ����A5:�Ŕw��) */
#define RENDER_DEPTH_INDEX_SP_BACK(X)  (RENDER_DEPTH_FAR_INDEX + (X))

namespace GgafDx {

typedef GgafCore::LinearOctree<GgafCore::Actor> WorldOctree;
typedef GgafCore::LinearOctreeRounder<GgafCore::Actor> WorldOctreeRounder;
typedef GgafCore::LinearQuadtree<GgafCore::Actor> WorldQuadtree;
typedef GgafCore::LinearQuadtreeRounder<GgafCore::Actor> WorldQuadtreeRounder;

typedef GgafCore::LinearQuadtree<GgafCore::Actor> ViewQuadtree;
typedef GgafCore::LinearQuadtreeRounder<GgafCore::Actor> ViewQuadtreeRounder;

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
        bool _can_looping[64];
        GeometricActor* _apActor[64];
        SeArray();

        void add(Se* prm_pSe, int prm_volume, float prm_pan, float prm_frequency_rate, bool prm_can_looping, GeometricActor* prm_pActor);

        void play(int index);
    };
    GgafCore::RingLinkedList<SeArray>* _pRing_pSeArray;

public:
    /** �J���� */
    Camera* _pCamera;

    /** �����_�����O�����z��ɓo�^����Ă���e�A�N�^�[���X�g�̐擪�̃A�N�^�[�̔z�� */
    FigureActor** _papFirstRenderActor;
    /** �����_�����O�����z��ɓo�^����Ă���e�A�N�^�[���X�g�̖����̃A�N�^�[�̔z�� */
    FigureActor** _papLastRenderActor;

    static int render_depth_index_active;
    /** [r]�A�v���P�[�V�����̈�(�q�b�g�`�F�b�N�\���W�̈�)�AX���W�̍ŏ��l */
    const coord _x_bound_left;
    /** [r]�A�v���P�[�V�����̈�(�q�b�g�`�F�b�N�\���W�̈�)�AX���W�̍ő�l */
    const coord _x_bound_right;
    /** [r]�A�v���P�[�V�����̈�(�q�b�g�`�F�b�N�\���W�̈�)�AY���W�̍ŏ��l */
    const coord _y_bound_bottom;
    /** [r]�A�v���P�[�V�����̈�(�q�b�g�`�F�b�N�\���W�̈�)�AY���W�̍ő�l */
    const coord _y_bound_top;
    /** [r]�A�v���P�[�V�����̈�(�q�b�g�`�F�b�N�\���W�̈�)�AZ���W�̍ŏ��l */
    const coord _z_bound_near;
    /** [r]�A�v���P�[�V�����̈�(�q�b�g�`�F�b�N�\���W�̈�)�AZ���W�̍ő�l */
    const coord _z_bound_far;

    /** [r]�A�v���P�[�V�����̈�(�q�b�g�`�F�b�N�\���W�̈�)(Board�p)�AX���W�̍ŏ��l */
    const coord _x_bound_left_b;
    /** [r]�A�v���P�[�V�����̈�(�q�b�g�`�F�b�N�\���W�̈�)(Board�p)�AX���W�̍ő�l */
    const coord _x_bound_right_b;
    /** [r]�A�v���P�[�V�����̈�(�q�b�g�`�F�b�N�\���W�̈�)(Board�p)�AY���W�̍ŏ��l */
    const coord _y_bound_bottom_b;
    /** [r]�A�v���P�[�V�����̈�(�q�b�g�`�F�b�N�\���W�̈�)(Board�p)�AY���W�̍ő�l */
    const coord _y_bound_top_b;


    static std::string _seqkey_se_delay;

    /** �I�u�W�F�N�g�̃J��������̉���(pixcoord)�ɑ΂���A�i�K�����_�����O�C���f�b�N�X�̔z�� */
    int* _paDep2Lv;
    /** �i�K�����_�����O���L���ȃJ�����i�n�_����j���牜�ւ̋��� */
    dxcoord _dep_resolution;


    double _w_r;
    double _h_r;

    /** [r] �`��p�o�b�N�o�b�t�@��`�̈�̓��A�Q�[���ɕ\�������`�̍�����W��X���W(����) */
    pixcoord _primary_buffer_source_left;
    /** [r] �`��p�o�b�N�o�b�t�@��`�̈�̓��A�Q�[���ɕ\�������`�̍�����W��Y���W(����) */
    pixcoord _primary_buffer_source_top;
    /** [r] �`��p�o�b�N�o�b�t�@��`�̈�̓��A�Q�[���ɕ\�������`�̍�����W��̕�(����) */
    pixcoord _primary_buffer_source_width;
    /** [r] �`��p�o�b�N�o�b�t�@��`�̈�̓��A�Q�[���ɕ\�������`�̍�����W��̍���(����) */
    pixcoord _primary_buffer_source_height;

    /** [r] �`��p�o�b�N�o�b�t�@��`�̈�̓��A�Q�[���ɕ\�������`�̍�����W��X���W(�����) */
    pixcoord _secondary_buffer_source_left;
    /** [r] �`��p�o�b�N�o�b�t�@��`�̈�̓��A�Q�[���ɕ\�������`�̍�����W��Y���W(�����) */
    pixcoord _secondary_buffer_source_top;
    /** [r] �`��p�o�b�N�o�b�t�@��`�̈�̓��A�Q�[���ɕ\�������`�̍�����W��̕�(�����) */
    pixcoord _secondary_buffer_source_width;
    /** [r] �`��p�o�b�N�o�b�t�@��`�̈�̓��A�Q�[���ɕ\�������`�̍�����W��̍���(�����) */
    pixcoord _secondary_buffer_source_height;

    static WorldOctree* _pWorldOctree;
    static WorldOctreeRounder* _pWorldOctreeRounder;
    static WorldQuadtree* _pWorldQuadtree;
    static WorldQuadtreeRounder* _pWorldQuadtreeRounder;

    static ViewQuadtree* _pViewQuadtree;
    static ViewQuadtreeRounder* _pViewQuadtreeRounder;

public:
    Spacetime(const char* prm_name, Camera* prm_pCamera);

    virtual void processSettlementBehavior() override;

    virtual ~Spacetime();

    virtual Camera* getCamera() {
        return _pCamera;
    }

    /**
     * ���̐��ɃA�N�^�[��o�^ .
     * �o�^����ƁA���̐��ɕ`�悳��邱�ƂƂȂ�B
     * @param prm_pActor �ΏۃA�N�^�[
     * @return �o�^���ꂽ�`�揇���[�x���x��
     */
    int registerDrawActor(FigureActor* prm_pActor);

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
                    bool prm_can_looping,
                    GeometricActor* prm_pActor);

    /**
     * �r���[���W�����[���h���W�ɕϊ����� .
     * @param prm_view_x �r���[���WX���v�f
     * @param prm_view_y �r���[���WY���v�f
     * @param prm_depth �J�������_����̋���
     * @param out_world_x �Ή����郏�[���h���WX���v�f
     * @param out_world_y �Ή����郏�[���h���WY���v�f
     * @param out_world_z �Ή����郏�[���h���WZ���v�f
     */
    void cnvViewCoordToWorld(coord prm_view_x, coord prm_view_y, coord prm_depth,
                             coord& out_world_x, coord& out_world_y, coord& out_world_z);

    /**
     * ���[���h���W���r���[���W�ϊ����� .
     * @param prm_world_x ���[���h���WX���v�f
     * @param prm_world_y ���[���h���WY���v�f
     * @param prm_world_z ���[���h���WZ���v�f
     * @param out_view_x �Ή�����r���[���WX���v�f
     * @param out_view_y �Ή�����r���[���WY���v�f
     */
    void cnvWorldCoordToView(coord prm_world_x, coord prm_world_y, coord prm_world_z,
                             coord& out_view_x, coord& out_view_y);


    /**
      * ���[���h���W��̃A�N�^�[�́u���A�O���[�v �� ���B�O���[�v�v�� �q�b�g�`�F�b�N ���s��  .
      * �R�����i�W���؁j or �Q�����i�S���؁j
      * processJudgement() �ŌĂԕK�v����B�iprocessSettlementBehavior() �� �c���[�ɓo�^���Ă���ׁj<BR>
      * @param prm_kind_groupA �A�N�^�[���A�O���[�v
      * @param prm_kind_groupB �A�N�^�[���B�O���[�v
      */
     virtual void executeWorldHitCheck(kind_t prm_kind_groupA, kind_t prm_kind_groupB);

     /**
      * �r���[���W��̃A�N�^�[�́u���A�O���[�v �� ���B�O���[�v�v�� �q�b�g�`�F�b�N ���s��  .
      * processJudgement() �ŌĂԕK�v����B�iprocessSettlementBehavior() �� �c���[�ɓo�^���Ă���ׁj<BR>
      * @param prm_kind_groupA �A�N�^�[���A�O���[�v
      * @param prm_kind_groupB �A�N�^�[���B�O���[�v
      */
     virtual void executeViewHitCheck(kind_t prm_kind_groupA, kind_t prm_kind_groupB);

     virtual void processFinal() override;

    /**
     * �f�o�b�O�F�`�揇�\��
     */
    void dumpRenderDepthOrder();


};

}
#endif /*GGAF_DX_SPACETIME_H_*/
