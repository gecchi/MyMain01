#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

int MyOptionLockonController::_max_lockon_num = 5;

MyOptionLockonController::MyOptionLockonController(const char* prm_name) : GgafDummyActor(prm_name) {
    _class_name = "MyOptionLockonController";
    _now_lockon_num = 0;


    _pRingTarget = NEW GgafLinkedListRing<GgafDx9Core::GgafDx9GeometricActor>();
    _pMainTarget = NULL;

    EffectLockon001_Main* _pMainLockonEffect = NEW EffectLockon001_Main("LOCKON_MARK");
    _pMainLockonEffect->inactivateImmediately();
    addSubLast(_pMainLockonEffect);
    for (int i = 1; i < _max_lockon_num; i++) {
        EffectLockon001_Sub* pSubLockon = NEW EffectLockon001_Sub("SUB_LOCKON_MARK");
        pSubLockon->inactivateImmediately();
        addSubLast(pSubLockon);
    }

    setProgress(MyOptionLockonController_PROG_NOTHING);
}

void MyOptionLockonController::initialize() {
}


void MyOptionLockonController::processBehavior() {
    //���b�N�I���^�[�Q�b�g�����m�F
    GgafDx9GeometricActor* pTarget = _pRingTarget->getCurrent();
    _pMainTarget = pTarget;

    GgafMainActor* pLockonEffect = getSubFirst();

    for (int i = 0; i < _pRingTarget->length(); i++) {

        if (pTarget->isActive() && pTarget->_pStatus->get(STAT_Stamina) > 0) {
            //OK
            pTarget = _pRingTarget->next(); //����
        } else {
            pTarget = _pRingTarget->remove(); //�����o��
            if (_pMainTarget == pTarget) {
                //���C���X�V
                _pMainTarget = _pRingTarget->getCurrent();
            }
            //�Y���̃��b�N�I���G�t�F�N�g���C���A�N�e�B�u�ɂ���
            GgafMainActor* pLockonEffect = getSubFirst();
            for (int j = 0; j < i; j++) {
                pLockonEffect = pLockonEffect->getNext();
            }
            pLockonEffect->moveLastImmediately(); //������
            ((EffectLockon001*)pLockonEffect)->releaseLockon();

            pTarget = _pRingTarget->getCurrent(); //���ցiremove()�����̂Ŏ����I�Ɏ��ɂȂ��Ă���)
        }
    }

}

void MyOptionLockonController::processJudgement() {
}


void MyOptionLockonController::lockon(GgafDx9GeometricActor* prm_pTarget) {
    //tM
    //tM, t1
    //tM, t2, t1
    //tM, t3, t2, t1
    //tM, t4, t3, t2, t1
    //t5, t4, t3, t2, tM
    //t5, t4, t3, tM, t6
    //t5, t4, tM, t7, t6
    //t5, tM, t8, t7, t6
    //tM, t9, t8, t7, t6
    if (_pRingTarget->indexOf(prm_pTarget) == -1) { //���b�N�I���ς݂ɖ������
        if (_pRingTarget->length() > _max_lockon_num) {
            //�^�[�Q�b�g���[�e�[�g
            //���b�N����MAX�Ȃ�΁A��ԌÂ����ɏ㏑���ŏ�����Ă�������
            //  t2  t1  tM  t4  t3
            //�́��́��́��́��́���
            //      ��  prev()
            //  t2  tM  t5  t4  t3
            //�́��́��́��́��́���
            //      ��  set(��)   ����prm_pTarget
            //  t2  tM  t5  t4  t3
            //�́��́��́��́��́���
            _pRingTarget->prev();
            _pRingTarget->set(prm_pTarget);
            _pMainTarget = prm_pTarget;

            //���b�N�I���G�t�F�N�g���[�e�[�g
            ����
        } else {
            //�^�[�Q�b�g���[�e�[�g
            //  t1  tM  t3  t2
            //�́��́��́��́���
            //      ��  addPrev(��)   ����prm_pTarget
            //  t1  New tM  t3  t2
            //�́��́��́��́��́���
            //      ��  prev()
            //  t1  tM  t4  t3  t2
            //�́��́��́��́��́���
            //(�h��ׂ��̓A�N�e�B�u�v�f)

            _pRingTarget->addPrev(prm_pTarget, false);
            _pRingTarget->prev();
            _pMainTarget = prm_pTarget;

            //���b�N�I���G�t�F�N�g���[�e�[�g
            ����

        }



            // �G  �G  �G  �G  �G  �G  �G  �G                 t2  t1  tM  t4  t3
            //     �@  �l                                   �́��́��́��́��́���
            //                                                �@  �A  �l  �C  �B
            // �G  �G  �G  �G  �G  �G  �G  �G
            //     �@  �A  �l

            // �����ŕ`��T�u�A�N�^�[��������������
            // �̂l��S0��S1��S2��S3��    �E�E�E�G�t�F�N�g�A�N�^�[

            // �̃A�̃C�́~�́~�́~��
            //
            // �̐V�̃A�̃C�́~�́~��


            //  t1  tM  t3  t2
            //�́��́��́��́���
            //      ��  addPrev(��)   ����prm_pTarget
            //  t1  New tM  t3  t2
            //�́��́��́��́��́���
            //      ��  prev()
            //  t1  tM  t4  t3  t2
            //�́��́��́��́��́���
            //(�h��ׂ��̓A�N�e�B�u�v�f)


            // �G  �G  �G  �G  �G  �G  �G  �G                 t2  t1  tM  t4  t3
            //     �@  �A  �B  �C  �l                       �́��́��́��́��́���
            //                                                �@  �A  �l  �C  �B

            // �G  �G  �G  �G  �G  �G  �G  �G
            //         �@  �A  �B  �C  �l                   �́��́��́��́��́���
            //                                                t2  t1  tM  t4  t3
            //                                             �� �A  �@  �l  �C  �B
            //                                                ��  ��  ��  ��  ��
            //                                             �V �@  �l  �C  �B  �A

                                                           //t1  tM  t4  t3  t2
            //  �����ŕ`��T�u�A�N�^�[��������������
            //  �̂l�� S0�� S1�� S2�� S3��    �E�E�E�G�t�F�N�g�A�N�^�[
            //    �l   �@   �A   �B   �C _pTarget��
            //    ��   ��   ��   ��   ��
            //�V=���C ���l ���@ ���A ���B _pTarget�s�̂悤�ɍX�V����Ă��܂�

            //���z��
            //    �l   �@   �A   �B   �C _pTarget��
            //    ��   ��   ��   ��   ��
            //�V=���C ���l ���@ ���A ���B _pTarget�s�̂悤�ɍX�V����Ă��܂�

            // first �� moveLast�ŗǂ��H




            //   t1  tM  t4  t3  t2  �`�揇�� �����Ȃ�΂���
            //tM=prm_pTarget

            //tM, t4, t3, t2, t1
            //t5, t4, t3, t2, tM
            //t5, t4, t3, tM, t6
            //t5, t4, tM, t7, t6
            //t5, tM, t8, t7, t6
            //tM, t9, t8, t7, t6

            //���b�N����MAX�Ȃ�΁A��ԌÂ����ɏ㏑���ŏ�����Ă�������
            //  t2  t1  tM  t4  t3
            //�́��́��́��́��́���
            //      ��  prev()
            //  t2  tM  t5  t4  t3
            //�́��́��́��́��́���
            //      ��  set(��)   ����prm_pTarget
            //  t2  tM  t5  t4  t3
            //�́��́��́��́��́���


            //���b�N�I���G�t�F�N�g���A�N�e�B�u�ɂ���

            //  t2  t1  tM  t4  t3
            //  t1  tM  t4  t3  t2

            //��tM��t1��t2��t3��t4�� �����Ȃ�

            //��tM��t2��t3��t4��t5�� ��������
            //��tM��t3��t4��t5��t6��
            //��tM��t4��t5��t6��t7��




        } else {
            //tM=prm_pTarget

            //tM
            //tM, t1
            //tM, t2, t1
            //tM, t3, t2, t1
            //tM, t4, t3, t2, t1


            //t1, tM, t2
            //t1, tM, t3, t2

            //  t1  tM  t3  t2
            //�́��́��́��́���
            //      ��  addPrev(��)   ����prm_pTarget
            //  t1  New tM  t3  t2
            //�́��́��́��́��́���
            //      ��  prev()
            //  t1  tM  t4  t3  t2
            //�́��́��́��́��́���
            //(�h��ׂ��̓A�N�e�B�u�v�f)

            _pRingTarget->addPrev(prm_pTarget, false);
            _pRingTarget->prev();
            _pMainTarget = prm_pTarget;



            //���b�N�I���G�t�F�N�g���A�N�e�B�u�ɂ���
                //tM�� x�� x�� x�� x�� x   (x��inactive)
                //tM��t1�� x�� x�� x�� x   (x��inactive)
                //tM��t1��t2�� x�� x�� x   (x��inactive)
                //tM��t1��t2��t3�� x�� x   (x��inactive)
                //tM��t1��t2��t3��t4�� x   (x��inactive)
                //tM��t1��t2��t3��t4��t5

            GgafMainActor* pLockonEffect = getSubFirst();
            for (int i = 0; i < _pRingTarget->length()-1; i++) {
                pLockonEffect = pLockonEffect->getNext();
            }
            pLockonEffect->activate();
            ((EffectLockon001*)pLockonEffect)->lockon(prm_pTarget);

        }

    }
}



void MyOptionLockonController::releaseAllLockon() {
    while (_pRingTarget->length() > 0) {
        _pRingTarget->remove();
    }

    //���b�N�I���G�t�F�N�g���C���A�N�e�B�u�ɂ���
    GgafMainActor* pLockonEffect = getSubFirst();
    while (true) {
        ((EffectLockon001*)pLockonEffect)->releaseLockon();
        if (pLockonEffect->isLast()) {
            break;
        } else {
            pLockonEffect = pLockonEffect->getNext();
        }
    }
}


MyOptionLockonController::~MyOptionLockonController() {
}
