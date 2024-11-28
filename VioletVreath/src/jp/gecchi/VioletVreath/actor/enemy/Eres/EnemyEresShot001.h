#ifndef ENEMYCELESSHOT001_H_
#define ENEMYCELESSHOT001_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/VvEnemyActor.hpp"
#include "jp/ggaf/lib/actor/DefaultMeshSetActor.h"

namespace VioletVreath {

/**
 * 3D�G�e001 .
 * 1)�����悭�ݒ�����ɔ�яo��<BR>
 * 2)���X�ɐ����͒x���Ȃ�A���@�̕����ɕ����]��<BR>
 * 3)���̌㎩�@���߂����Ē����ړ��B�ĉ������Ă���<BR>
 * �y�㏑���\�ȃ����o�[�z
 *
 */
class EnemyEresShot001 : public VvEnemyActor<GgafLib::DefaultMeshSetActor> {

public:
    //�{Actor�̃J�X�^���v���p�e�B --->
    /** �o�����̏��� */
    int velo1st_;
    /** �o�����̉����x�i���Œx���Ȃ� */
    int iMoveAcce_1st_;
    /** ���g���o�����Ă���A���@�̕����ɕ����]�����J�n����t���[�� */
    frame frame_TurnBegin_;
    /** �ړ����x��� */
    int veloTop_;
    /** �Œ�ۏ؈ړ����x */
    int veloBottom_;
    /** �����]���ɔ�₷���Ƃ��ł���t���[���� */
    frame frame_TurnInterval_;
    /** �����]�����̊p���x�A���O���l */
    angle angVelo_Turn_;
    /** �����]�����J�n�iframe_TurnBegin_�j����Đݒ肳�������x */
    int iMoveAcce_2nd_;
    //<--- �{Actor�̃J�X�^���v���p�e�B

public:
    EnemyEresShot001(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onInactive() override;

    virtual ~EnemyEresShot001();
};

}
#endif /*ENEMYCELESSHOT001_H_*/

