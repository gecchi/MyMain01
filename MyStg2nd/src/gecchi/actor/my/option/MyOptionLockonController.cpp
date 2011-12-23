#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;


MyOptionLockonController::MyOptionLockonController(const char* prm_name) :
        GgafDummyActor(prm_name, NULL) {
    _class_name = "MyOptionLockonController";
    _pRingTarget = NEW GgafLinkedListRing<GgafDxCore::GgafDxGeometricActor>();
    _pMainLockonEffect = NEW EffectLockon001_Main("MAIN");
    _pMainLockonEffect->inactivateImmediately();
    addSubLast(_pMainLockonEffect);
    for (int i = 1; i < MyOption::_max_lockon_num; i++) {
        stringstream name;
        name <<  "SUB["<<i<<"]";
        EffectLockon001_Sub* pSubLockon = NEW EffectLockon001_Sub(name.str().c_str());
        pSubLockon->inactivateImmediately();
        addSubLast(pSubLockon);
    }
}

void MyOptionLockonController::initialize() {
}
void MyOptionLockonController::onReset() {
    GgafMainActor* pLockonEffect_Active = getSubFirst();
    int n = _pRingTarget->length();
    for (int i = 0; i < n; i++) {
        _pRingTarget->remove();
        ((EffectLockon001*)pLockonEffect_Active)->releaseLockon();
        pLockonEffect_Active->getPrev()->moveLastImmediately();
    }
}

void MyOptionLockonController::processBehavior() {
    //���b�N�I���^�[�Q�b�g�����m�F
    GgafDxGeometricActor* pMainLockonTarget = _pRingTarget->getCurrent(); //���C�����b�N�I���̃^�[�Q�b�g
    GgafDxGeometricActor* pTarget = _pRingTarget->getCurrent(); //�^�[�Q�b�g�J�[�\��
    GgafMainActor* pLockonEffect_Active = getSubFirst();         //���b�N�I���G�t�F�N�g�J�[�\��
    int n = _pRingTarget->length();
    for (int i = 0; i < n; i++) {
        if (pTarget->isActiveInTheTree() && pTarget->_pStatus->get(STAT_Stamina) > 0) {
            //�^�[�Q�b�g�������Ȃ��
            //�G�t�F�N�g�A�N�^�[�̃^�[�Q�b�g�X�V�A�G�t�F�N�g���Y�����Ƃ��܂�
            ((EffectLockon001*)pLockonEffect_Active)->lockon(pTarget);
            if (!pLockonEffect_Active->isActiveInTheTree()) {
                pLockonEffect_Active->activate();
            }
            pLockonEffect_Active = pLockonEffect_Active->getNext(); //���񏈗����b�N�I���G�t�F�N�g�A�N�^�[����
            pTarget = _pRingTarget->next();                         //���񏈗��^�[�Q�b�g������
        } else {
            //�^�[�Q�b�g�����S��
            if (pTarget == pMainLockonTarget) {
                //���S�^�[�Q�b�g�����C�����b�N�I���̃^�[�Q�b�g�ł������ꍇ
                if (_pRingTarget->length() == 1) {
                    //���S�^�[�Q�b�g�����C�����b�N�I���̃^�[�Q�b�g�Ń����O�̍Ō�̈�̏ꍇ
                    _pRingTarget->remove();                                    //�^�[�Q�b�g�����o��
                    ((EffectLockon001*)pLockonEffect_Active)->releaseLockon(); //���b�N�I���G�t�F�N�g�������[�X���s
                    pTarget = NULL;
                    break;
                } else {
                    //���S�^�[�Q�b�g�����C�����b�N�I���̃^�[�Q�b�g�Ń����O�̍Ō�̈�ł͖����ꍇ
                    _pRingTarget->remove();               //�^�[�Q�b�g�����o��
                    pTarget = _pRingTarget->getCurrent(); //���񏈗��^�[�Q�b�g�����ցiremove()�ɂ�莟�̃^�[�Q�b�g��getCurrent()�ƂȂ�j
                    pMainLockonTarget = pTarget;          //���C�����b�N�I���̃^�[�Q�b�g���X�V
                    //���C�����b�N�I���G�t�F�N�g�𒼋߃��b�N�I���֖߂���
                    //���C�����b�N�I���G�t�F�N�g�̎��̃G�t�F�N�g���������Ƃ��������������
                    ((EffectLockon001*)pLockonEffect_Active->getNext())->releaseLockon(); //���̃��b�N�I���G�t�F�N�g�������[�X���s
                    pLockonEffect_Active->getNext()->moveLastImmediately();               //���̃��b�N�I���G�t�F�N�g�𖖔���
                    //�u���񏈗����b�N�I���G�t�F�N�g�A�N�^�[���ցv�̏����Ώۈړ��͕s�v�B���ɏ������������b�N�I���G�t�F�N�g�A�N�^�[���̂܂܂ł��邽�߁B
                }
            } else {
                //���S�^�[�Q�b�g���T�u���b�N�I���̃^�[�Q�b�g�ł������ꍇ
                _pRingTarget->remove();               //�^�[�Q�b�g�����o��
                pTarget = _pRingTarget->getCurrent(); //���񏈗��^�[�Q�b�g�����ցiremove()�ɂ�莟�̃^�[�Q�b�g��getCurrent()�ƂȂ�j
                ((EffectLockon001*)pLockonEffect_Active)->releaseLockon(); //���b�N�I���G�t�F�N�g�������[�X���s
                pLockonEffect_Active = pLockonEffect_Active->getNext();    //���񏈗����b�N�I���G�t�F�N�g�A�N�^�[����
                pLockonEffect_Active->getPrev()->moveLastImmediately();    //���񏈗����b�N�I���G�t�F�N�g�A�N�^�[�𖖔���
            }
        }
    }

    if (GgafDxInput::isBeingPressedKey(DIK_I)) {
        dumpTarget(_pRingTarget->getCurrent());
        dump();
    }


}

void MyOptionLockonController::processJudgement() {
}


void MyOptionLockonController::lockon(GgafDxGeometricActor* prm_pTarget) {
    if (_pRingTarget->indexOf(prm_pTarget) == -1) { //���b�N�I���ς݂ɖ������

        if (_pRingTarget->length() >= MyOption::_lockon_num) {
            //�^�[�Q�b�g�̃��X�g�����ɖ����̏ꍇ
            //���b�N�I���^�[�Q�b�g���[�e�[�g
            _pRingTarget->prev();
            _pRingTarget->set(prm_pTarget);
            //���b�N�I���G�t�F�N�g�A�N�^�[�͂��̂܂�
            //����ɂ��AprocessBehavior() �̃^�[�Q�b�g�������̂����ɂ��
            //�Y���b�Ƃ����B
        } else {
            //�^�[�Q�b�g�̃��X�g�����ɖ����ł͖����i�ǉ��\�ȏꍇ�j
            //�^�[�Q�b�g���[�e�[�g
            _pRingTarget->addPrev(prm_pTarget, false);
            _pRingTarget->prev();
            //���b�N�I���G�t�F�N�g
            if (_pRingTarget->length() == 1) {
                //�ŏ��̃��b�N�I���^�[�Q�b�g�ǉ����i���C�����b�N�I���^�[�Q�b�g�j
                GgafMainActor* pLockonEffect = getSubFirst(); //���C�����b�N�I�G�t�F�N�g
                pLockonEffect->activate();
                ((EffectLockon001*)pLockonEffect)->lockon(prm_pTarget);
                //�ŏ��̃��b�N�I���^�[�Q�b�g�ȊO�̒ǉ����i�T�u���b�N�I���^�[�Q�b�g�ǉ����j
            } else if (_pRingTarget->length() > 1) {
                //Sub���b�N�I���ǉ���
                if (_pRingTarget->length() >= 3) {
                    //�R�ڂ̈ȍ~�^�[�Q�b�g�ǉ����i�Q�ڈȍ~�̃T�u���b�N�I���^�[�Q�b�g�ǉ����j
                    //���b�N�I���G�t�F�N�g�̓���ȃ��[�e�[�g���s���B�i���Ō�̃R�����g���ǉ��̏ꍇ���Q�Ɓj
                    //Last��؂�o��
                    GgafMainActor* pLockonEffect = getSubFirst()->getPrev(); //Last
                    GgafMainActor* pLockonEffect_Next = pLockonEffect->getNext(); //Main���b�N�I���ƂȂ�
                    GgafMainActor* pLockonEffect_Prev = pLockonEffect->getPrev();
                    pLockonEffect_Prev->_pNext = pLockonEffect_Next;
                    pLockonEffect_Next->_pPrev = pLockonEffect_Prev;
                    pLockonEffect_Prev->_is_last_flg = true;
                    pLockonEffect->_is_last_flg = false;
                    //First->Next �̊Ԃɓ����
                    GgafMainActor* pMainLockonEffect = getSubFirst();
                    GgafMainActor* pMainLockonEffect_Next = getSubFirst()->getNext();
                    pMainLockonEffect->_pNext = pLockonEffect;
                    pLockonEffect->_pPrev = pMainLockonEffect;
                    pLockonEffect->_pNext = pMainLockonEffect_Next;
                    pMainLockonEffect_Next->_pPrev = pLockonEffect;
                    pLockonEffect->activate(); //�T�u���b�N�I���L����
                    //�T�u���b�N�I���G�t�F�N�g���b�N�I���I
                    ((EffectLockon001*)pLockonEffect)->lockon(_pRingTarget->getNext());
                } else {
                    //�Q�ڂ̃^�[�Q�b�g�ǉ����i�ŏ��̃T�u���b�N�I���^�[�Q�b�g�ǉ����j
                    GgafMainActor* pLockonEffect = getSubFirst()->getPrev(); //�Q�Ȃ̂Ō���Next�̈ʒu
                    pLockonEffect->activate(); //�T�u���b�N�I���L����
                    ((EffectLockon001*)pLockonEffect)->lockon(_pRingTarget->getNext());
                }
            }
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
    DELETE_IMPOSSIBLE_NULL(_pRingTarget);
}


void MyOptionLockonController::dumpTarget(GgafDxGeometricActor* pMain) {

    if (_pRingTarget->getFromFirst(0) == NULL) {
        _TEXT_("NULL\n");
        return;
    } else {
        _TEXT_("��");
    }
    for (int i = 0; i < _pRingTarget->length(); i++) {
        if (_pRingTarget->getFromFirst(i) == pMain) {
            _TEXT_("�I");
        }
        _TEXT_(_pRingTarget->getFromFirst(i)->getName()<<"["<<i<<"]��");
    }
    _TEXT_(" ... avtive="<<_pRingTarget->getCurrent()->getName()<<"\n");
}

//�y���Y�^�z
//�u���b�N�I���^�[�Q�b�g�ƃ��b�N�I���G�t�F�N�g�̊֌W�v(2010/09/14)
//
//���b�N�I�����A���b�N�I�������[�X����
//���b�N�I���^�[�Q�b�g�ƃ��b�N�I���G�t�F�N�g�̊֌W�������Ƃ��Ďc���B
//
//�l      �c ���C�����b�N�I���G�t�F�N�g
//S0�`S3  �c �T�u���b�N�I���G�t�F�N�g
//t1�`t5  �c ���b�N�I���^�[�Q�b�g
//
//���C�����b�N�I���G�t�F�N�g(�l)�̏ꏊ�Ɉʒu���郍�b�N�I���^�[�Q�b�g��
//�u���C�����b�N�I���^�[�Q�b�g�v
//�T�u���b�N�I���G�t�F�N�g(S0�`S3)�̏ꏊ�Ɉʒu���郍�b�N�I���^�[�Q�b�g��
//�u�T�u���b�N�I���^�[�Q�b�g�v
//�ƌĂԂ��Ƃɂ���B

//���ǉ��̏ꍇ��
// �̂l��S0��S1��S2��S3��    �E�E�E�G�t�F�N�g�A�N�^�[
//          ��            t1�ǉ�
// ��t1��
// �G�t�F�N�g�A�N�^�[�ω�����
//          ��            t2�ǉ�
// ��t2��t1��
// �̂l��S3��S0��S1��S2��
//          ��            t3�ǉ�
// ��t3��t2��t1��
// �̂l��S2��S3��S0��S1��
//          ��            t4�ǉ�
// ��t4��t3��t2��t1��
// �̂l��S1��S2��S3��S0��
//          ��            t5�ǉ�
// ��t5��t4��t3��t2��t1��
// �̂l��S0��S1��S2��S3��

// �������Œǉ��̏ꍇ��
// �̂l��S0��S1��S2��S3��    �E�E�E�G�t�F�N�g�A�N�^�[�͑���s�v
//
// ��t5��t4��t3��t2��t1��
// ��t6��t5��t4��t3��t2��   �Y����
// ��t7��t6��t5��t4��t3��   �Y����
// ��t8��t7��t6��t5��t4��   �Y����
// ��t9��t8��t7��t6��t5��   �Y�����Ƃ��܂�

//�����S�̏ꍇ��
// �̂l��S0��S1��S2��S3��    �E�E�E�G�t�F�N�g�A�N�^�[
// ��t5��t4��t3��t2��t1��
//          ��    remove(t1)
// ��t5��t4��t3��t2��
// �̂l��S0��S1��S2��S3��    �E�E�E�ω������iS3�������ցj�ړ�����lockonRelase()

// �̂l��S0��S1��S2��S3��    �E�E�E�G�t�F�N�g�A�N�^�[
// ��t5��t4��t3��t2��t1��
//          ��    remove(t2)
// ��t5��t4��t3��t1��
// �̂l��S0��S1��S3��S2��    �E�E�ES2�������ֈړ�����lockonRelase()

// �̂l��S0��S1��S2��S3��    �E�E�E�G�t�F�N�g�A�N�^�[
// ��t5��t4��t3��t2��t1��
//          ��    remove(t3)
// ��t5��t4��t2��t1��
// �̂l��S0��S2��S3��S1��    �E�E�ES1�������ֈړ�����lockonRelase()

// �̂l��S0��S1��S2��S3��    �E�E�E�G�t�F�N�g�A�N�^�[
// ��t5��t4��t3��t2��t1��
//          ��    remove(t4)
// ��t5��t3��t2��t1��
// �̂l��S2��S3��S1��S0��    �E�E�ES0�������ֈړ�����lockonRelase()

// �̂l��S0��S1��S2��S3��    �E�E�E�G�t�F�N�g�A�N�^�[
// ��t5��t4��t3��t2��t1��
//          ��    remove(t5)
// ��t4��t3��t2��t1��
// �̂l��S1��S2��S3��S0��    �E�E�E S0�������ցi���Ӂj�ړ�����lockonRelase()



//���؂��ꍇ2��
// �̂l��S0��S1��S2��S3��    �E�E�E�G�t�F�N�g�A�N�^�[
// ��t4��t3��t2��t1��
//          ��    remove(t1)
// ��t4��t3��t1��
// �̂l��S0��S1��S3��S2��    �E�E�ES2�������ցi�����ȗ��H�j�ړ�����lockonRelase()

// �̂l��S0��S1��S2��S3��    �E�E�E�G�t�F�N�g�A�N�^�[
// ��t4��t3��t2��t1��
//          ��    remove(t2)
// ��t4��t3��t1��
// �̂l��S0��S2��S3��S1��    �E�E�ES1�������ֈړ�����lockonRelase()

// �̂l��S0��S1��S2��S3��    �E�E�E�G�t�F�N�g�A�N�^�[
// ��t4��t3��t2��t1��
//          ��    remove(t3)
// ��t4��t2��t1��
// �̂l��S1��S2��S3��S0��    �E�E�ES0�������ֈړ�����lockonRelase()

// �̂l��S0��S1��S2��S3��    �E�E�E�G�t�F�N�g�A�N�^�[
// ��t4��t3��t2��t1��
//          ��    remove(t4)
// ��t3��t2��t1��
// �̂l��S1��S2��S3��S0��    �E�E�ES0�������ցi���Ӂj�ړ�����lockonRelase()



//���؂��ꍇ3��
// �̂l��S0��S1��S2��S3��    �E�E�E�G�t�F�N�g�A�N�^�[
// ��t3��t2��t1��
//          ��    remove(t1)
// ��t3��t2��
// �̂l��S0��S2��S3��S1��    �E�E�ES1�������ցi�����ȗ��H�j�ړ�����lockonRelase()

// �̂l��S0��S1��S2��S3��    �E�E�E�G�t�F�N�g�A�N�^�[
// ��t3��t2��t1��
//          ��    remove(t2)
// ��t3��t1��
// �̂l��S1��S2��S3��S0��    �E�E�ES0�������ֈړ�����lockonRelase()

// �̂l��S0��S1��S2��S3��    �E�E�E�G�t�F�N�g�A�N�^�[
// ��t3��t2��t1��
//          ��    remove(t3)
// ��t2��t1��
// �̂l��S1��S2��S3��S0��    �E�E�ES0�������ֈړ�����lockonRelase()



//���؂��ꍇ4��
// �̂l��S0��S1��S2��S3��    �E�E�E�G�t�F�N�g�A�N�^�[
// ��t2��t1��
//          ��    remove(t1)
// ��t2��
// �̂l��S1��S2��S3��S0��    �E�E�ES0�������ցi�����ȗ��H�j�ړ�����lockonRelase()

// �̂l��S0��S1��S2��S3��    �E�E�E�G�t�F�N�g�A�N�^�[
// ��t2��t1��
//          ��    remove(t2)
// ��t2��t1��
// �̂l��S1��S2��S3��S0��    �E�E�ES0�������w�ړ�����lockonRelase()


//���؂��ꍇ5��
// �̂l��S0��S1��S2��S3��    �E�E�E�G�t�F�N�g�A�N�^�[
// ��t1��
//          ��    remove(t1)
//
// �̂l��S1��S2��S3��S0��    �E�E�E�ω�������M��lockonRelase()
