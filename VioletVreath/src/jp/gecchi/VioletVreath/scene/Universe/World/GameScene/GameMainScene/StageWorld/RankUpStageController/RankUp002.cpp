#include "RankUp002.h"

#include "jp/ggaf/core/actor/GgafSceneDirector.h"
#include "jp/gecchi/VioletVreath/actor/VVEnemysHeader.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

RankUp002::RankUp002(const char* prm_name) : RankUpStage(prm_name) {
    _class_name = "RankUp002";

    // �ȉ��� gen01 start �` end ��Excel�}�N���ɂ�莩���������ꂽ�R�[�h�ł��B
    // �R�[�h�̕ύX�́u�V�[��Creater.xls�v����s�����Ƃ���i�������m�ۂ̂��߁j�B
    // gen01 start
    frame f[] = {1,20,80,140,200,260,320,380,440,500,560,620,680,740,800,860,920,980,1040,1100,1160,1220,1280,1340,1400,1460,1520,1580,1640,1700,1760,1820,1880,1940,2000};
    _paFrame_NextEvent = new frame[35];
    memcpy(_paFrame_NextEvent, f, sizeof(f));
    _event_num = 35;
    orderActorToFactory(90000000, EnemyTamago01, "EnemyTamago01-1");
    orderActorToFactory(90000001, EnemyTamago01, "EnemyTamago01-2");
    orderActorToFactory(90000002, EnemyTamago01, "EnemyTamago01-3");
    orderActorToFactory(90000003, EnemyTamago01, "EnemyTamago01-4");
    orderActorToFactory(90000004, EnemyTamago01, "EnemyTamago01-5");
    orderActorToFactory(90000005, EnemyTamago01, "EnemyTamago01-6");
    orderActorToFactory(90000006, EnemyTamago01, "EnemyTamago01-7");
    orderActorToFactory(90000007, EnemyTamago01, "EnemyTamago01-8");
    orderActorToFactory(90000008, EnemyTamago01, "EnemyTamago01-9");
    orderActorToFactory(90000009, EnemyTamago01, "EnemyTamago01-10");
    orderActorToFactory(90000010, EnemyTamago01, "EnemyTamago01-11");
    orderActorToFactory(90000011, EnemyTamago01, "EnemyTamago01-12");
    orderActorToFactory(90000012, EnemyTamago01, "EnemyTamago01-13");
    orderActorToFactory(90000013, EnemyTamago01, "EnemyTamago01-14");
    orderActorToFactory(90000014, EnemyTamago01, "EnemyTamago01-15");
    orderActorToFactory(90000015, EnemyTamago01, "EnemyTamago01-16");
    orderActorToFactory(90000016, EnemyTamago01, "EnemyTamago01-17");
    orderActorToFactory(90000017, EnemyTamago01, "EnemyTamago01-18");
    orderActorToFactory(90000018, EnemyTamago01, "EnemyTamago01-19");
    orderActorToFactory(90000019, EnemyTamago01, "EnemyTamago01-20");
    orderActorToFactory(90000020, EnemyTamago01, "EnemyTamago01-21");
    orderActorToFactory(90000021, EnemyTamago01, "EnemyTamago01-22");
    orderActorToFactory(90000022, EnemyTamago01, "EnemyTamago01-23");
    orderActorToFactory(90000023, EnemyTamago01, "EnemyTamago01-24");
    orderActorToFactory(90000024, EnemyTamago01, "EnemyTamago01-25");
    orderActorToFactory(90000025, EnemyTamago01, "EnemyTamago01-26");
    orderActorToFactory(90000026, EnemyTamago01, "EnemyTamago01-27");
    // gen01 end
}

void RankUp002::initialize() {
    RankUpStage::initialize();
}

void RankUp002::processBehavior() {
    RankUpStage::processBehavior();

    // �ȉ��� gen02 start �` end ��Excel�}�N���ɂ�莩���������ꂽ�R�[�h�ł��B
    // �R�[�h�̕ύX�́u�V�[��Creater.xls�v����s�����Ƃ���i�������m�ۂ̂��߁j�B
    // gen02 start
    if (getBehaveingFrame() == _paFrame_NextEvent[_cnt_event]) {
        switch (getBehaveingFrame()) {
            case 1: {
                break;
            }
            case 20: {
                orderActorToFactory(90000027, EnemyTamago01, "EnemyTamago01-28");
                break;
            }
            case 80: {
                orderActorToFactory(90000028, EnemyTamago01, "EnemyTamago01-29");
                break;
            }
            case 140: {
                orderActorToFactory(90000029, EnemyTamago01, "EnemyTamago01-30");
                break;
            }
            case 200: {
                EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000000);
                getSceneDirector()->addSubGroup(pActor);
                all_hit_num_ ++;
                orderActorToFactory(90000030, EnemyTamago01, "EnemyTamago01-31");
                break;
            }
            case 260: {
                EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000001);
                getSceneDirector()->addSubGroup(pActor);
                all_hit_num_ ++;
                break;
            }
            case 320: {
                EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000002);
                getSceneDirector()->addSubGroup(pActor);
                all_hit_num_ ++;
                break;
            }
            case 380: {
                EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000003);
                getSceneDirector()->addSubGroup(pActor);
                all_hit_num_ ++;
                break;
            }
            case 440: {
                EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000004);
                getSceneDirector()->addSubGroup(pActor);
                all_hit_num_ ++;
                break;
            }
            case 500: {
                EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000005);
                getSceneDirector()->addSubGroup(pActor);
                all_hit_num_ ++;
                break;
            }
            case 560: {
                EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000006);
                getSceneDirector()->addSubGroup(pActor);
                all_hit_num_ ++;
                break;
            }
            case 620: {
                EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000007);
                getSceneDirector()->addSubGroup(pActor);
                all_hit_num_ ++;
                break;
            }
            case 680: {
                EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000008);
                getSceneDirector()->addSubGroup(pActor);
                all_hit_num_ ++;
                break;
            }
            case 740: {
                EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000009);
                getSceneDirector()->addSubGroup(pActor);
                all_hit_num_ ++;
                break;
            }
            case 800: {
                EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000010);
                getSceneDirector()->addSubGroup(pActor);
                all_hit_num_ ++;
                break;
            }
            case 860: {
                EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000011);
                getSceneDirector()->addSubGroup(pActor);
                all_hit_num_ ++;
                break;
            }
            case 920: {
                EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000012);
                getSceneDirector()->addSubGroup(pActor);
                all_hit_num_ ++;
                break;
            }
            case 980: {
                EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000013);
                getSceneDirector()->addSubGroup(pActor);
                all_hit_num_ ++;
                break;
            }
            case 1040: {
                EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000014);
                getSceneDirector()->addSubGroup(pActor);
                all_hit_num_ ++;
                break;
            }
            case 1100: {
                EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000015);
                getSceneDirector()->addSubGroup(pActor);
                all_hit_num_ ++;
                break;
            }
            case 1160: {
                EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000016);
                getSceneDirector()->addSubGroup(pActor);
                all_hit_num_ ++;
                break;
            }
            case 1220: {
                EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000017);
                getSceneDirector()->addSubGroup(pActor);
                all_hit_num_ ++;
                break;
            }
            case 1280: {
                EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000018);
                getSceneDirector()->addSubGroup(pActor);
                all_hit_num_ ++;
                break;
            }
            case 1340: {
                EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000019);
                getSceneDirector()->addSubGroup(pActor);
                all_hit_num_ ++;
                break;
            }
            case 1400: {
                EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000020);
                getSceneDirector()->addSubGroup(pActor);
                all_hit_num_ ++;
                break;
            }
            case 1460: {
                EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000021);
                getSceneDirector()->addSubGroup(pActor);
                all_hit_num_ ++;
                break;
            }
            case 1520: {
                EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000022);
                getSceneDirector()->addSubGroup(pActor);
                all_hit_num_ ++;
                break;
            }
            case 1580: {
                EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000023);
                getSceneDirector()->addSubGroup(pActor);
                all_hit_num_ ++;
                break;
            }
            case 1640: {
                EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000024);
                getSceneDirector()->addSubGroup(pActor);
                all_hit_num_ ++;
                break;
            }
            case 1700: {
                EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000025);
                getSceneDirector()->addSubGroup(pActor);
                all_hit_num_ ++;
                break;
            }
            case 1760: {
                EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000026);
                getSceneDirector()->addSubGroup(pActor);
                all_hit_num_ ++;
                break;
            }
            case 1820: {
                EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000027);
                getSceneDirector()->addSubGroup(pActor);
                all_hit_num_ ++;
                break;
            }
            case 1880: {
                EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000028);
                getSceneDirector()->addSubGroup(pActor);
                all_hit_num_ ++;
                break;
            }
            case 1940: {
                EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000029);
                getSceneDirector()->addSubGroup(pActor);
                all_hit_num_ ++;
                break;
            }
            case 2000: {
                EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000030);
                getSceneDirector()->addSubGroup(pActor);
                all_hit_num_ ++;
                break;
            }
            default :
                break;
        }
        _cnt_event = (_cnt_event < 35-1 ? _cnt_event+1 : _cnt_event);
    }
    // gen02 end

    SceneProgress* pProg = getProgress();
    switch (pProg->get()) {
        case RankUpStage::PROG_PLAYING: {
            if (pProg->isJustChanged()) {
                _TRACE_("RankUp002::processBehavior() RankUpStage::PROG_PLAYING �ɂȂ�܂����I");
            }

            if (pProg->arriveAtFrameOf(_paFrame_NextEvent[_event_num-1]+600)) {
                _TRACE_("RankUp002::processBehavior() RankUpStage::PROG_PLAYING �������");
                pProg->change(RankUpStage::PROG_RESULT); //RankUpStage�̋��ʏ�����
            }
            break;
        }
    }

}

void RankUp002::processJudgement() {
}


void RankUp002::onCatchEvent(hashval prm_no, void* prm_pSource) {
}


RankUp002::~RankUp002() {

}
