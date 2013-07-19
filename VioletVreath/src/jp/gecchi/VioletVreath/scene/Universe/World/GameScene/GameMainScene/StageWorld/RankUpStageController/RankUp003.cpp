#include "stdafx.h"
#include "RankUp003.h"

#include "jp/ggaf/core/actor/GgafSceneDirector.h"
#include "jp/gecchi/VioletVreath/actor/VVEnemysHeader.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

RankUp003::RankUp003(const char* prm_name) : RankUpStage(prm_name) {
    _class_name = "RankUp003";

    // �ȉ��� gen01 start �` end ��Excel�}�N���ɂ�莩���������ꂽ�R�[�h�ł��B
    // �R�[�h�̕ύX�́u�V�[��Creater.xls�v����s�����Ƃ���i�������m�ۂ̂��߁j�B
    // gen01 start
	frame f[] = {1,20,80,140,200,260,320,380,440,500,560,620,680,740,800,860,920,980,1040,1100,1160,1220,1280,1340,1400,1460,1520,1580,1640,1700,1760,1820,1880,1940,2000};
	_paFrame_NextEvent = new frame[35];
	memcpy(_paFrame_NextEvent, f, sizeof(f));
	_event_num = 35;
	orderActorToFactory(100000000, EnemyTamago01, "EnemyTamago01-1");
	orderActorToFactory(100000001, EnemyTamago01, "EnemyTamago01-2");
	orderActorToFactory(100000002, EnemyTamago01, "EnemyTamago01-3");
	orderActorToFactory(100000003, EnemyTamago01, "EnemyTamago01-4");
	orderActorToFactory(100000004, EnemyTamago01, "EnemyTamago01-5");
	orderActorToFactory(100000005, EnemyTamago01, "EnemyTamago01-6");
	orderActorToFactory(100000006, EnemyTamago01, "EnemyTamago01-7");
	orderActorToFactory(100000007, EnemyTamago01, "EnemyTamago01-8");
	orderActorToFactory(100000008, EnemyTamago01, "EnemyTamago01-9");
	orderActorToFactory(100000009, EnemyTamago01, "EnemyTamago01-10");
	orderActorToFactory(100000010, EnemyTamago01, "EnemyTamago01-11");
	orderActorToFactory(100000011, EnemyTamago01, "EnemyTamago01-12");
	orderActorToFactory(100000012, EnemyTamago01, "EnemyTamago01-13");
	orderActorToFactory(100000013, EnemyTamago01, "EnemyTamago01-14");
	orderActorToFactory(100000014, EnemyTamago01, "EnemyTamago01-15");
	orderActorToFactory(100000015, EnemyTamago01, "EnemyTamago01-16");
	orderActorToFactory(100000016, EnemyTamago01, "EnemyTamago01-17");
	orderActorToFactory(100000017, EnemyTamago01, "EnemyTamago01-18");
	orderActorToFactory(100000018, EnemyTamago01, "EnemyTamago01-19");
	orderActorToFactory(100000019, EnemyTamago01, "EnemyTamago01-20");
	orderActorToFactory(100000020, EnemyTamago01, "EnemyTamago01-21");
	orderActorToFactory(100000021, EnemyTamago01, "EnemyTamago01-22");
	orderActorToFactory(100000022, EnemyTamago01, "EnemyTamago01-23");
	orderActorToFactory(100000023, EnemyTamago01, "EnemyTamago01-24");
	orderActorToFactory(100000024, EnemyTamago01, "EnemyTamago01-25");
	orderActorToFactory(100000025, EnemyTamago01, "EnemyTamago01-26");
	orderActorToFactory(100000026, EnemyTamago01, "EnemyTamago01-27");
    // gen01 end
}

void RankUp003::initialize() {
    RankUpStage::initialize();
}

void RankUp003::processBehavior() {
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
				orderActorToFactory(100000027, EnemyTamago01, "EnemyTamago01-28");
				break;
			}
			case 80: {
				orderActorToFactory(100000028, EnemyTamago01, "EnemyTamago01-29");
				break;
			}
			case 140: {
				orderActorToFactory(100000029, EnemyTamago01, "EnemyTamago01-30");
				break;
			}
			case 200: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(100000000);
				getSceneDirector()->addSubGroup(pActor);
				all_hit_num_ ++;
				orderActorToFactory(100000030, EnemyTamago01, "EnemyTamago01-31");
				break;
			}
			case 260: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(100000001);
				getSceneDirector()->addSubGroup(pActor);
				all_hit_num_ ++;
				break;
			}
			case 320: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(100000002);
				getSceneDirector()->addSubGroup(pActor);
				all_hit_num_ ++;
				break;
			}
			case 380: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(100000003);
				getSceneDirector()->addSubGroup(pActor);
				all_hit_num_ ++;
				break;
			}
			case 440: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(100000004);
				getSceneDirector()->addSubGroup(pActor);
				all_hit_num_ ++;
				break;
			}
			case 500: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(100000005);
				getSceneDirector()->addSubGroup(pActor);
				all_hit_num_ ++;
				break;
			}
			case 560: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(100000006);
				getSceneDirector()->addSubGroup(pActor);
				all_hit_num_ ++;
				break;
			}
			case 620: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(100000007);
				getSceneDirector()->addSubGroup(pActor);
				all_hit_num_ ++;
				break;
			}
			case 680: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(100000008);
				getSceneDirector()->addSubGroup(pActor);
				all_hit_num_ ++;
				break;
			}
			case 740: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(100000009);
				getSceneDirector()->addSubGroup(pActor);
				all_hit_num_ ++;
				break;
			}
			case 800: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(100000010);
				getSceneDirector()->addSubGroup(pActor);
				all_hit_num_ ++;
				break;
			}
			case 860: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(100000011);
				getSceneDirector()->addSubGroup(pActor);
				all_hit_num_ ++;
				break;
			}
			case 920: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(100000012);
				getSceneDirector()->addSubGroup(pActor);
				all_hit_num_ ++;
				break;
			}
			case 980: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(100000013);
				getSceneDirector()->addSubGroup(pActor);
				all_hit_num_ ++;
				break;
			}
			case 1040: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(100000014);
				getSceneDirector()->addSubGroup(pActor);
				all_hit_num_ ++;
				break;
			}
			case 1100: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(100000015);
				getSceneDirector()->addSubGroup(pActor);
				all_hit_num_ ++;
				break;
			}
			case 1160: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(100000016);
				getSceneDirector()->addSubGroup(pActor);
				all_hit_num_ ++;
				break;
			}
			case 1220: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(100000017);
				getSceneDirector()->addSubGroup(pActor);
				all_hit_num_ ++;
				break;
			}
			case 1280: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(100000018);
				getSceneDirector()->addSubGroup(pActor);
				all_hit_num_ ++;
				break;
			}
			case 1340: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(100000019);
				getSceneDirector()->addSubGroup(pActor);
				all_hit_num_ ++;
				break;
			}
			case 1400: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(100000020);
				getSceneDirector()->addSubGroup(pActor);
				all_hit_num_ ++;
				break;
			}
			case 1460: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(100000021);
				getSceneDirector()->addSubGroup(pActor);
				all_hit_num_ ++;
				break;
			}
			case 1520: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(100000022);
				getSceneDirector()->addSubGroup(pActor);
				all_hit_num_ ++;
				break;
			}
			case 1580: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(100000023);
				getSceneDirector()->addSubGroup(pActor);
				all_hit_num_ ++;
				break;
			}
			case 1640: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(100000024);
				getSceneDirector()->addSubGroup(pActor);
				all_hit_num_ ++;
				break;
			}
			case 1700: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(100000025);
				getSceneDirector()->addSubGroup(pActor);
				all_hit_num_ ++;
				break;
			}
			case 1760: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(100000026);
				getSceneDirector()->addSubGroup(pActor);
				all_hit_num_ ++;
				break;
			}
			case 1820: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(100000027);
				getSceneDirector()->addSubGroup(pActor);
				all_hit_num_ ++;
				break;
			}
			case 1880: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(100000028);
				getSceneDirector()->addSubGroup(pActor);
				all_hit_num_ ++;
				break;
			}
			case 1940: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(100000029);
				getSceneDirector()->addSubGroup(pActor);
				all_hit_num_ ++;
				break;
			}
			case 2000: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(100000030);
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


    switch (_pProg->get()) {
        case RankUpStage::PROG_PLAYING: {
            if (_pProg->isJustChanged()) {
                _TRACE_("RankUp003::processBehavior() RankUpStage::PROG_PLAYING �ɂȂ�܂����I");
            }

            if (_pProg->getFrameInProgress() == _paFrame_NextEvent[_event_num-1]+600) {
                _TRACE_("RankUp003::processBehavior() RankUpStage::PROG_PLAYING �������");
                _pProg->change(RankUpStage::PROG_RESULT); //RankUpStage�̋��ʏ�����
            }
            break;
        }
    }

}

void RankUp003::processJudgement() {
}


void RankUp003::onCatchEvent(hashval prm_no, void* prm_pSource) {
}


RankUp003::~RankUp003() {

}
