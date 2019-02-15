#include "MyLockonController.h"

#include "LockonCursor001_Main.h"
#include "LockonCursor001_Sub.h"
#include "jp/gecchi/VioletVreath/actor/my/MyLockonController.h"



using namespace GgafLib;
using namespace VioletVreath;

/** �P�I�v�V����������̍ő�\���b�N�I���� */
const int MyLockonController::max_lockon_num_ = 8;
int MyLockonController::lockon_num_ = 0;

MyLockonController::MyLockonController(const char* prm_name) :
        GgafCore::DestructActor(prm_name) {
    _class_name = "MyLockonController";
    pRingTarget_ = NEW GgafCore::LinkedListRing<GgafDx::GeometricActor>();
    pMainLockonEffect_ = NEW LockonCursor001_Main("MAIN");
    pMainLockonEffect_->inactivate();
    appendChild(pMainLockonEffect_);
    for (int i = 1; i < MyLockonController::max_lockon_num_; i++) {
        std::string name = "ChildLockon("+XTOS(i)+")";
        LockonCursor001_Sub* pChildLockon = NEW LockonCursor001_Sub(name.c_str());
        pChildLockon->inactivate();
        appendChild(pChildLockon);
    }
}

void MyLockonController::initialize() {
}
void MyLockonController::onReset() {
    //���b�N�I���^�[�Q�b�g�̃��X�g����ɂ���
    pRingTarget_->removeAll();
    //���b�N�I���A�N�^�[�̃��Z�b�g
    LockonCursor001* pLockonCursor001;
    for (int i = 0; i < MyLockonController::max_lockon_num_; i++) {
        pLockonCursor001 = (LockonCursor001*)(getChild(i));
        pLockonCursor001->releaseLockon();
        pLockonCursor001->inactivate();
    }
}

void MyLockonController::onActive() {
    onReset();
}


void MyLockonController::processBehavior() {
    //���b�N�I���^�[�Q�b�g�����m�F
    GgafDx::GeometricActor* pMainLockonTarget = pRingTarget_->getCurrent(); //���C�����b�N�I���̃^�[�Q�b�g
    GgafDx::GeometricActor* pTarget = pRingTarget_->getCurrent();  //�^�[�Q�b�g�J�[�\��
    GgafCore::MainActor* pLockonEffect_Active = (GgafCore::MainActor*)getChildFirst();         //���b�N�I���G�t�F�N�g�J�[�\��
    int n = pRingTarget_->length();
    for (int i = 0; i < n; i++) {
        if (pTarget->isActiveInTheTree() && pTarget->getStatus()->get(STAT_Stamina) > 0) {
            //�^�[�Q�b�g�������Ȃ��
            //�G�t�F�N�g�A�N�^�[�̃^�[�Q�b�g�X�V�A�G�t�F�N�g���Y�����Ƃ��܂�
            ((LockonCursor001*)pLockonEffect_Active)->lockon(pTarget);
            if (!pLockonEffect_Active->isActiveInTheTree()) {
                pLockonEffect_Active->activate();
            }
            pLockonEffect_Active = pLockonEffect_Active->getNext(); //���񏈗����b�N�I���G�t�F�N�g�A�N�^�[����
            pTarget = pRingTarget_->next();                         //���񏈗��^�[�Q�b�g������
        } else {
            //�^�[�Q�b�g�����S��
            if (pTarget == pMainLockonTarget) {
                //���S�^�[�Q�b�g�����C�����b�N�I���̃^�[�Q�b�g�ł������ꍇ
                if (pRingTarget_->length() == 1) {
                    //���S�^�[�Q�b�g�����C�����b�N�I���̃^�[�Q�b�g�Ń����O�̍Ō�̈�̏ꍇ
                    pRingTarget_->remove();                                    //�^�[�Q�b�g�����o��
                    ((LockonCursor001*)pLockonEffect_Active)->releaseLockon(); //���b�N�I���G�t�F�N�g�������[�X���s
                    pTarget = nullptr;
                    break;
                } else {
                    //���S�^�[�Q�b�g�����C�����b�N�I���̃^�[�Q�b�g�Ń����O�̍Ō�̈�ł͖����ꍇ
                    pRingTarget_->remove();               //�^�[�Q�b�g�����o��
                    pTarget = pRingTarget_->getCurrent(); //���񏈗��^�[�Q�b�g�����ցiremove()�ɂ�莟�̃^�[�Q�b�g��getCurrent()�ƂȂ�j
                    pMainLockonTarget = pTarget;          //���C�����b�N�I���̃^�[�Q�b�g���X�V
                    //���C�����b�N�I���G�t�F�N�g�𒼋߃��b�N�I���֖߂���
                    //���C�����b�N�I���G�t�F�N�g�̎��̃G�t�F�N�g���������Ƃ��������������
                    ((LockonCursor001*)pLockonEffect_Active->getNext())->releaseLockon(); //�u���v�̃��b�N�I���G�t�F�N�g�������[�X���s
                    pLockonEffect_Active->getNext()->moveLast();               //���̃��b�N�I���G�t�F�N�g�𖖔���
                    //�u���񏈗����b�N�I���G�t�F�N�g�A�N�^�[���ցv�̏����Ώۈړ��͕s�v�B���ɏ������������b�N�I���G�t�F�N�g�A�N�^�[���̂܂܂ł��邽�߁B
                }
            } else {
                //���S�^�[�Q�b�g���T�u���b�N�I���̃^�[�Q�b�g�ł������ꍇ
                pRingTarget_->remove();               //�^�[�Q�b�g�����o��
                pTarget = pRingTarget_->getCurrent(); //���񏈗��^�[�Q�b�g�����ցiremove()�ɂ�莟�̃^�[�Q�b�g��getCurrent()�ƂȂ�j
                ((LockonCursor001*)pLockonEffect_Active)->releaseLockon(); //���b�N�I���G�t�F�N�g�������[�X���s
                pLockonEffect_Active = pLockonEffect_Active->getNext();    //���񏈗����b�N�I���G�t�F�N�g�A�N�^�[����
                pLockonEffect_Active->getPrev()->moveLast();    //���񏈗����b�N�I���G�t�F�N�g�A�N�^�[�𖖔���
            }
        }
    }
}

void MyLockonController::processJudgement() {
}

void MyLockonController::onInactive() {
    onReset();
}

void MyLockonController::lockon(GgafDx::GeometricActor* prm_pTarget) {
    if (MyLockonController::lockon_num_ == 0) {
        return; //���݂̃��b�N�I���\����0
    }

    if (pRingTarget_->indexOf(prm_pTarget) == -1) {
        //���b�N�I���ς݂ɖ����̂ŁA���b�N�I������
        if (pRingTarget_->length() >= MyLockonController::lockon_num_) { //�^�[�Q�b�g���X�g�����ɖ����̏ꍇ
            //���b�N�I���^�[�Q�b�g���[�e�[�g
            pRingTarget_->prev();           //�J�����g���ŏI�v�f��
            pRingTarget_->set(prm_pTarget, false); //�ŏI�v�f�������Ƃ���Ƀ��C���^�[�Q�b�g�㏑��
            //���b�N�I���G�t�F�N�g�A�N�^�[�͂��̂܂�
            //����ɂ��AprocessBehavior() �̃^�[�Q�b�g�������̂����ɂ��
            //�Y���b�Ƃ����B
        } else {   //�܂��^�[�Q�b�g���X�g�ɉ����Ȃ��A�����͗]�T������i�ǉ��\�ȏꍇ�j
            //�^�[�Q�b�g���[�e�[�g
            pRingTarget_->addPrev(prm_pTarget, false);
            pRingTarget_->prev();
            //���b�N�I���G�t�F�N�g
            if (pRingTarget_->length() == 1) {
                //�ŏ��̃��b�N�I���^�[�Q�b�g�ǉ����i���C�����b�N�I���^�[�Q�b�g�j
                GgafCore::MainActor* pLockonEffect = (GgafCore::MainActor*)getChildFirst(); //���C�����b�N�I�G�t�F�N�g
                pLockonEffect->activate();
                ((LockonCursor001*)pLockonEffect)->lockon(prm_pTarget);

                //�ŏ��̃��b�N�I���^�[�Q�b�g�ȊO�̒ǉ����i�T�u���b�N�I���^�[�Q�b�g�ǉ����j
            } else if (pRingTarget_->length() > 1) {
                //Child���b�N�I���ǉ���
                if (pRingTarget_->length() >= 3) {
                    //�R�ڂ̈ȍ~�^�[�Q�b�g�ǉ����i�Q�ڈȍ~�̃T�u���b�N�I���^�[�Q�b�g�ǉ����j
                    //���b�N�I���G�t�F�N�g�̓���ȃ��[�e�[�g���s���B�i���Ō�̃R�����g���ǉ��̏ꍇ���Q�Ɓj
                    //Last��؂�o��
                    GgafCore::MainActor* pLockonEffect = (GgafCore::MainActor*)getChildFirst()->getPrev(); //Last
                    GgafCore::MainActor* pLockonEffect_Next = pLockonEffect->getNext(); //Main���b�N�I���ƂȂ�
                    GgafCore::MainActor* pLockonEffect_Prev = pLockonEffect->getPrev();
                    pLockonEffect_Prev->_pNext = pLockonEffect_Next;
                    pLockonEffect_Next->_pPrev = pLockonEffect_Prev;
                    pLockonEffect_Prev->_is_last_flg = true;
                    pLockonEffect->_is_last_flg = false;
                    //First->Next �̊Ԃɓ����
                    GgafCore::MainActor* pMainLockonEffect = (GgafCore::MainActor*)getChildFirst();
                    GgafCore::MainActor* pMainLockonEffect_Next = (GgafCore::MainActor*)getChildFirst()->getNext();
                    pMainLockonEffect->_pNext = pLockonEffect;
                    pLockonEffect->_pPrev = pMainLockonEffect;
                    pLockonEffect->_pNext = pMainLockonEffect_Next;
                    pMainLockonEffect_Next->_pPrev = pLockonEffect;
                    pLockonEffect->activate(); //�T�u���b�N�I���L����
                    //�T�u���b�N�I���G�t�F�N�g���b�N�I���I
                    ((LockonCursor001*)pLockonEffect)->lockon(pRingTarget_->getNext());
                } else {
                    //�Q�ڂ̃^�[�Q�b�g�ǉ����i�ŏ��̃T�u���b�N�I���^�[�Q�b�g�ǉ����j
                    GgafCore::MainActor* pLockonEffect = (GgafCore::MainActor*)getChildFirst()->getPrev(); //�Q�Ȃ̂Ō���Next�̈ʒu
                    pLockonEffect->activate(); //�T�u���b�N�I���L����
                    ((LockonCursor001*)pLockonEffect)->lockon(pRingTarget_->getNext());
                }
            }
        }
    } else {
        //prm_pTarget �͊��Ƀ��b�N�I���ς�
    }
}

void MyLockonController::releaseAllLockon() {
    if (pRingTarget_->length() == 0) {
        return;
    }
    pRingTarget_->removeAll();
    //���b�N�I���G�t�F�N�g���C���A�N�e�B�u�ɂ���
    GgafCore::MainActor* pLockonEffect = (GgafCore::MainActor*)getChildFirst();
    while (pLockonEffect) {
        ((LockonCursor001*)pLockonEffect)->releaseLockon();
        if (pLockonEffect->isLast()) {
            break;
        } else {
            pLockonEffect = pLockonEffect->getNext();
        }
    }
}

MyLockonController::~MyLockonController() {
    GGAF_DELETE(pRingTarget_);
}

void MyLockonController::dumpTarget(GgafDx::GeometricActor* pMain) {
    if (pRingTarget_->getFromFirst(0) == nullptr) {
        _TRACE_N_("nullptr\n");
        return;
    } else {
        _TRACE_N_("��");
    }
    for (int i = 0; i < pRingTarget_->length(); i++) {
        if (pRingTarget_->getFromFirst(i) == pMain) {
            _TRACE_N_("�I");
        }
        _TRACE_N_(pRingTarget_->getFromFirst(i)->getName()<<"["<<i<<"]��");
    }
    _TRACE_N_(" ... avtive="<<pRingTarget_->getCurrent()->getName()<<"\n");
}

//�y���Y�^�z
//�u���b�N�I���^�[�Q�b�g(�G)�ƃ��b�N�I���G�t�F�N�g(�Ə�)�̊֌W�v(2010/09/14)
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
//          ��            t1���b�N�I��
// ��t1��
// �G�t�F�N�g�A�N�^�[�ω�����
//          ��            t2�ǉ����b�N�I��
// ��t2��t1��
// �̂l��S3��S0��S1��S2��
//          ��            t3�ǉ����b�N�I��
// ��t3��t2��t1��
// �̂l��S2��S3��S0��S1��
//          ��            t4�ǉ����b�N�I��
// ��t4��t3��t2��t1��
// �̂l��S1��S2��S3��S0��
//          ��            t5�ǉ����b�N�I��
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
