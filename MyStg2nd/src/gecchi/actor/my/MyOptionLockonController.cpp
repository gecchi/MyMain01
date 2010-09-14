#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

int MyOptionLockonController::_max_lockon_num = 9;

MyOptionLockonController::MyOptionLockonController(const char* prm_name) : GgafDummyActor(prm_name) {
    _class_name = "MyOptionLockonController";
    _now_lockon_num = 0;
    _pRingTarget = NEW GgafLinkedListRing<GgafDx9Core::GgafDx9GeometricActor>();
    EffectLockon001_Main* _pMainLockonEffect = NEW EffectLockon001_Main("MAIN");
    _pMainLockonEffect->inactivateImmediately();
    addSubLast(_pMainLockonEffect);
    for (int i = 1; i < _max_lockon_num; i++) {
        stringstream name;
        name <<  "SUB["<<i<<"]";
        EffectLockon001_Sub* pSubLockon = NEW EffectLockon001_Sub(name.str().c_str());
        pSubLockon->inactivateImmediately();
        addSubLast(pSubLockon);
    }

    setProgress(MyOptionLockonController_PROG_NOTHING);
}

void MyOptionLockonController::initialize() {
}


void MyOptionLockonController::processBehavior() {
    //���b�N�I���^�[�Q�b�g�����m�F
    GgafDx9GeometricActor* pMainLockonTarget = _pRingTarget->getCurrent();
    GgafDx9GeometricActor* pTarget = _pRingTarget->getCurrent(); //�^�[�Q�b�g�J�[�\��
    GgafMainActor* pLockonEffect_Active = getSubFirst();         //���b�N�I���G�t�F�N�g�J�[�\��
    int n = _pRingTarget->length();
    for (int i = 0; i < n; i++) {
//_TRACE_("<<<"<<i<<">>>");
        if (pTarget->isActive() && pTarget->_pStatus->get(STAT_Stamina) > 0) {
//            _TRACE_("---------------------------------");
//            _TRACE_("�G�t�F�N�g�A�N�^�[�̃^�[�Q�b�g�X�V  BEFORE");
//            dumpTarget(_pRingTarget->getCurrent());
//            dump();

            //OK
            //�G�t�F�N�g�A�N�^�[�̃^�[�Q�b�g�X�V                    //�G�t�F�N�g���Y�����Ƃ��܂�
            ((EffectLockon001*)pLockonEffect_Active)->lockon(pTarget);
            pLockonEffect_Active = pLockonEffect_Active->getNext();//�G�t�F�N�g�A�N�^�[����
            pTarget = _pRingTarget->next(); //����

//            _TRACE_("�G�t�F�N�g�A�N�^�[�̃^�[�Q�b�g�X�V AFTER");
//            dumpTarget(_pRingTarget->getCurrent());
//            dump();
        } else {

            //�؂��ꍇ
//            _TRACE_("---------------------------------");
//            _TRACE_("�؂�� BEFORE");
//            dumpTarget();
//            dump();
            if (pTarget == pMainLockonTarget) {
                //���C�����b�N�I��������
                if (_pRingTarget->length() == 1) {
                    _TRACE_("---------------------------------");
                    _TRACE_("�Ō�̈�Ń��C�����b�N�I���؂�� BEFORE");
                    dumpTarget(_pRingTarget->getCurrent());
                    dump();


                    //�Ō�̈�Ń��C�����b�N�I��
                    _pRingTarget->remove(); //�����o��
                    //�Ō�̈��
                    ((EffectLockon001*)pLockonEffect_Active)->releaseLockon(); //���b�N�I�������[�X
                    pTarget = NULL;

                    _TRACE_("�Ō�̈�Ń��C�����b�N�I���؂�� AFTER");
                    dumpTarget(_pRingTarget->getCurrent());
                    dump();

                    break;
//                    _pMainTarget = NULL;
                } else {
                    _TRACE_("---------------------------------");
                    _TRACE_("���C�����b�N�I���؂�� BEFORE");
                    dumpTarget(_pRingTarget->getCurrent());
                    dump();



                    _pRingTarget->remove(); //�����o��
                    pTarget = _pRingTarget->getCurrent(); //Target����
                    pMainLockonTarget = pTarget;
                    //�A�N�e�B�u�����֏����͕s�v�Aremove()�����̂Ŏ����I�Ɏ��ɂȂ��Ă���B
//                    _pMainTarget = _pRingTarget->getCurrent();

                    //���C�����b�N�I���G�t�F�N�g�𒼋߃��b�N�I���֖߂� �͕s�v�A
                    //((EffectLockon001*)pLockonEffect_Active)->lockon(pTarget);
                    //���̂���
                    //���C�����b�N�I���G�t�F�N�g�̎��̃G�t�F�N�g�����
                    ((EffectLockon001*)pLockonEffect_Active->getNext())->releaseLockon();
                    pLockonEffect_Active->getNext()->moveLastImmediately(); //������

                    //pLockonEffect_Active->getNext()->releaseLockon();//inactivate(); //���
                    //���C�����b�N�I���G�t�F�N�g�A�N�^�[�̃^�[�Q�b�g�X�V�A�Y�����Ɩ߂�܂�
                    //((EffectLockon001*)pLockonEffect_Active)->_pTarget = _pRingTarget->getCurrent();

                    //pLockonEffect_Active = pLockonEffect_Active->getNext();//���ւ�
                    //���ւ͂��Ȃ��ėǂ�
                    //���R�͎��̂悤�ɂȂ邩��A����         Metis_85  �ł��邽��
//  5601092 <DEBUG> ���C�����b�N�I���؂�� BEFORE
//  �́IMetis_36[0]��Metis_85[1]�� ... avtive=Metis_36
//  5601095 <DEBUG>                                 MyOptionLockonController(08A06F18)[Lockon001]@4628/4628/4628,1,11,0(0)0,0(0)0,0(4294967295),1(1),0000
//  5601096 <DEBUG>                                 �bEffectLockon001_Main(08A07298)[MAIN] Target=Metis_36 @278/4628/4628,1,11,0(0)0,0(0)0,0(4294967295),2(2),0000
//  5601096 <DEBUG>                                 �bEffectLockon001_Sub(08A0C360)[SUB[8]] Target=Metis_85 @214/4628/4628,1,11,0(0)0,0(0)0,0(4294967295),2(2),0000
//  5601097 <DEBUG>                                 �bEffectLockon001_Sub(08A07D40)[SUB[1]] Target=NULL @4628/4628/4628,1,10,0(0)0,0(0)0,0(4294967295),-3(-3),0000
//  5601097 <DEBUG>                                 �bEffectLockon001_Sub(08A08760)[SUB[2]] Target=NULL @4628/4628/4628,1,10,0(0)0,0(0)0,0(4294967295),-3(-3),0000
//  5601098 <DEBUG>                                 �bEffectLockon001_Sub(08A09160)[SUB[3]] Target=NULL @4628/4628/4628,1,10,0(0)0,0(0)0,0(4294967295),-3(-3),0000
//  5601098 <DEBUG>                                 �bEffectLockon001_Sub(08A09B60)[SUB[4]] Target=NULL @4628/4628/4628,1,10,0(0)0,0(0)0,0(4294967295),-3(-3),0000
//  5601099 <DEBUG>                                 �bEffectLockon001_Sub(08A0A560)[SUB[5]] Target=NULL @4628/4628/4628,1,10,0(0)0,0(0)0,0(4294967295),-3(-3),0000
//  5601099 <DEBUG>                                 �bEffectLockon001_Sub(08A0AF60)[SUB[6]] Target=NULL @4628/4628/4628,1,10,0(0)0,0(0)0,0(4294967295),-3(-3),0000
//  5601100 <DEBUG>                                 �bEffectLockon001_Sub(08A0B960)[SUB[7]] Target=NULL @4628/4628/4628,1,10,0(0)0,0(0)0,0(4294967295),-3(-3),0000
//  5601100 <DEBUG>                                 ����
//  5601101 <DEBUG> ���C�����b�N�I���؂�� AFTER
//  �́IMetis_85[0]�� ... avtive=Metis_85
//  5601103 <DEBUG>                                 MyOptionLockonController(08A06F18)[Lockon001]@4628/4628/4628,1,11,0(0)0,0(0)0,0(4294967295),1(1),0000
//  5601103 <DEBUG>                                 �bEffectLockon001_Main(08A07298)[MAIN] Target=Metis_85 @278/4628/4628,1,11,0(0)0,0(0)0,0(4294967295),2(2),0000
//  5601104 <DEBUG>                                 �bEffectLockon001_Sub(08A07D40)[SUB[1]] Target=NULL @4628/4628/4628,1,10,0(0)0,0(0)0,0(4294967295),-3(-3),0000
//  5601104 <DEBUG>                                 �bEffectLockon001_Sub(08A08760)[SUB[2]] Target=NULL @4628/4628/4628,1,10,0(0)0,0(0)0,0(4294967295),-3(-3),0000
//  5601105 <DEBUG>                                 �bEffectLockon001_Sub(08A09160)[SUB[3]] Target=NULL @4628/4628/4628,1,10,0(0)0,0(0)0,0(4294967295),-3(-3),0000
//  5601105 <DEBUG>                                 �bEffectLockon001_Sub(08A09B60)[SUB[4]] Target=NULL @4628/4628/4628,1,10,0(0)0,0(0)0,0(4294967295),-3(-3),0000
//  5601105 <DEBUG>                                 �bEffectLockon001_Sub(08A0A560)[SUB[5]] Target=NULL @4628/4628/4628,1,10,0(0)0,0(0)0,0(4294967295),-3(-3),0000
//  5601106 <DEBUG>                                 �bEffectLockon001_Sub(08A0AF60)[SUB[6]] Target=NULL @4628/4628/4628,1,10,0(0)0,0(0)0,0(4294967295),-3(-3),0000
//  5601106 <DEBUG>                                 �bEffectLockon001_Sub(08A0B960)[SUB[7]] Target=NULL @4628/4628/4628,1,10,0(0)0,0(0)0,0(4294967295),-3(-3),0000
//  5601107 <DEBUG>                                 �bEffectLockon001_Sub(08A0C360)[SUB[8]] Target=NULL @214/4628/4628,1,11,0(0)0,0(0)0,0(4294967295),2(3),0000
//  5601107 <DEBUG>                                 ����


                    _TRACE_("���C�����b�N�I���؂�� AFTER");
                    dumpTarget(_pRingTarget->getCurrent());
                    dump();
                }
            } else {

                _TRACE_("---------------------------------");
                _TRACE_("�T�u���b�N�I���؂�� BEFORE");
                dumpTarget(_pRingTarget->getCurrent());
                dump();

                //�T�u���b�N�I��������

                _pRingTarget->remove(); //�^�[�Q�b�g�����o��
                pTarget = _pRingTarget->getCurrent(); //Target����
                //�A�N�e�B�u�����֏����͕s�v�Aremove()�����̂Ŏ����I�Ɏ��ɂȂ��Ă���B

                ((EffectLockon001*)pLockonEffect_Active)->releaseLockon(); //���b�N�I�������[�X
                pLockonEffect_Active = pLockonEffect_Active->getNext();//��Ɏ���
                pLockonEffect_Active->getPrev()->moveLastImmediately(); //����releaseLockon()�𖖔���

                //pLockonEffect_Active->_pTarget �͍X�V���Ȃ��Ă��ω����ĂȂ��̂ŕs�v�B�Ƃ����݌v�B

                _TRACE_("�؂�� AFTER");
                dumpTarget(_pRingTarget->getCurrent());
                dump();

            }
//            _TRACE_("�؂�� AFTER");
//            dumpTarget();
//            dump();

        }
    }
//    _pMainLockOnTarget = _pRingTarget->getCurrent();
    //_TRACE_("_pRingTarget->getCurrent()="<<(_pRingTarget->getCurrent()==NULL?"NULL":_pRingTarget->getCurrent()->getName()));
}

void MyOptionLockonController::processJudgement() {
}


void MyOptionLockonController::lockon(GgafDx9GeometricActor* prm_pTarget) {
    // �ǉ��̏ꍇ�G�t�F�N�g�A�N�^�[�͑���s�v

    if (_pRingTarget->indexOf(prm_pTarget) == -1) { //���b�N�I���ς݂ɖ������

        if (_pRingTarget->length() >= _max_lockon_num) {
            _TRACE_("---------------------------------");
            _TRACE_("������ �Y���� lockon("<<prm_pTarget->getName()<<") BEFORE");
            dumpTarget(_pRingTarget->getCurrent());
            dump();
            // �̂l��S0��S1��S2��S3��    �E�E�E�G�t�F�N�g�A�N�^�[
            //
            // ��t5��t4��t3��t2��t1��
            // ��t6��t5��t4��t3��t2��   �Y����
            // ��t7��t6��t5��t4��t3��   �Y����
            // ��t8��t7��t6��t5��t4��   �Y����
            // ��t9��t8��t7��t6��t5��   �Y�����Ƃ��܂�
            //�^�[�Q�b�g���[�e�[�g
            _pRingTarget->prev();
            _pRingTarget->set(prm_pTarget);
            //_pMainTarget = prm_pTarget;

            //���b�N�I���G�t�F�N�g���[�e�[�g
            //����s�v


            //���b�N�I���G�t�F�N�g ���b�N�I��
            //�t�����b�N�I����Ԃł��邽�ߕK�v�Ȃ�
            _TRACE_("������ �Y���� lockon("<<prm_pTarget->getName()<<") AFTER");
            dumpTarget(_pRingTarget->getCurrent());
            dump();
        } else {
            _TRACE_("---------------------------------");
            _TRACE_("�����ł͖��� lockon("<<prm_pTarget->getName()<<") BEFORE");
            dumpTarget(_pRingTarget->getCurrent());
            dump();
            // �̂l��S0��S1��S2��S3��    �E�E�E�G�t�F�N�g�A�N�^�[
            //
            // ��t1��
            // �G�t�F�N�g�A�N�^�[�ω�����
            //
            // ��t2��t1��
            // �̂l��S3��S0��S1��S2��
            //
            // ��t3��t2��t1��
            // �̂l��S2��S3��S0��S1��
            //
            // ��t4��t3��t2��t1��
            // �̂l��S1��S2��S3��S0��
            //
            // ��t5��t4��t3��t2��t1��
            // �̂l��S0��S1��S2��S3��

            //�^�[�Q�b�g���[�e�[�g
            _pRingTarget->addPrev(prm_pTarget, false);
            _pRingTarget->prev();
            //_pMainTarget = prm_pTarget;

            //���b�N�I���G�t�F�N�g
            if (_pRingTarget->length() == 1) {
                //�ŏ��� Mian���b�N�I���ǉ���
                GgafMainActor* pLockonEffect = getSubFirst();
                pLockonEffect->activate();
                ((EffectLockon001*)pLockonEffect)->lockon(prm_pTarget);


                _TRACE_("�����ł͖��� �ŏ��� Mian���b�N�I���ǉ��� lockon("<<prm_pTarget->getName()<<") AFTER");

            } else if (_pRingTarget->length() > 1) {
                //Sub���b�N�I���ǉ���
                if (_max_lockon_num >= 3) {
                    //����ȃ��[�e�[�g
                    //��؂�o��
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
                    //���b�N�I���I
                    ((EffectLockon001*)pLockonEffect)->lockon(_pRingTarget->getNext());

                    _TRACE_("�����ł͖��� Sub���b�N�I���ǉ��� ����ȃ��[�e�[�g lockon("<<prm_pTarget->getName()<<") AFTER");

                } else {
                    GgafMainActor* pLockonEffect = getSubFirst()->getPrev(); //�Q�Ȃ̂Ō���Next�̈ʒu
                    pLockonEffect->activate(); //�T�u���b�N�I���L����
                    ((EffectLockon001*)pLockonEffect)->lockon(_pRingTarget->getNext());

                    _TRACE_("�����ł͖��� Sub���b�N�I���ǉ��� �Q�Ȃ̂Ō���Next�̈ʒu lockon("<<prm_pTarget->getName()<<") AFTER");


                }

                //_pMainTarget = prm_pTarget;
            }
        }

        ((EffectLockon001*)getSubFirst())->_pTarget = prm_pTarget;
        dumpTarget(_pRingTarget->getCurrent());
        dump();
    }
//	_pMainLockOnTarget = _pRingTarget->getCurrent(); //processBehavior() �ōX�V��
}

        // ���؂ꖳ���ꍇ�� �G�t�F�N�g�A�N�^�[�͑���s�v
        // �̂l��S0��S1��S2��S3��    �E�E�E�G�t�F�N�g�A�N�^�[
        // ��t1��
        // ��t2��t1��
        // ��t3��t2��t1��
        // ��t4��t3��t2��t1��
        // ��t5��t4��t3��t2��t1��
        // ��t6��t5��t4��t3��t2��   �Y����
        // ��t7��t6��t5��t4��t3��   �Y����
        // ��t8��t7��t6��t5��t4��   �Y����
        // ��t9��t8��t7��t6��t5��   �Y�����Ƃ��܂�

        //���؂��ꍇ��
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
//
//
//
//
//        } else {
//            //tM=prm_pTarget
//
//            //tM
//            //tM, t1
//            //tM, t2, t1
//            //tM, t3, t2, t1
//            //tM, t4, t3, t2, t1
//
//
//            //t1, tM, t2
//            //t1, tM, t3, t2
//
//            //  t1  tM  t3  t2
//            //�́��́��́��́���
//            //      ��  addPrev(��)   ����prm_pTarget
//            //  t1  New tM  t3  t2
//            //�́��́��́��́��́���
//            //      ��  prev()
//            //  t1  tM  t4  t3  t2
//            //�́��́��́��́��́���
//            //(�h��ׂ��̓A�N�e�B�u�v�f)
//
//            _pRingTarget->addPrev(prm_pTarget, false);
//            _pRingTarget->prev();
//            _pMainTarget = prm_pTarget;
//
//
//
//            //���b�N�I���G�t�F�N�g���A�N�e�B�u�ɂ���
//                //tM�� x�� x�� x�� x�� x   (x��inactive)
//                //tM��t1�� x�� x�� x�� x   (x��inactive)
//                //tM��t1��t2�� x�� x�� x   (x��inactive)
//                //tM��t1��t2��t3�� x�� x   (x��inactive)
//                //tM��t1��t2��t3��t4�� x   (x��inactive)
//                //tM��t1��t2��t3��t4��t5
//
//            GgafMainActor* pLockonEffect = getSubFirst();
//            for (int i = 0; i < _pRingTarget->length()-1; i++) {
//                pLockonEffect = pLockonEffect->getNext();
//            }
//            pLockonEffect->activate();
//            ((EffectLockon001*)pLockonEffect)->lockon(prm_pTarget);
//
//        }
//
//    }



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




void MyOptionLockonController::dumpTarget(GgafDx9GeometricActor* pMain) {

    if (_pRingTarget->getNextFromFirst(0) == NULL) {
        _TEXT_("NULL\n");
        return;
    } else {
        _TEXT_("��");
    }
    for (int i = 0; i < _pRingTarget->length(); i++) {
        if (_pRingTarget->getNextFromFirst(i) == pMain) {
            _TEXT_("�I");
        }
        _TEXT_(_pRingTarget->getNextFromFirst(i)->getName()<<"["<<i<<"]��");
    }
    _TEXT_(" ... avtive="<<_pRingTarget->getCurrent()->getName()<<"\n");
}


