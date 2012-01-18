#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;

World::World(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "World";
    _TRACE_("World::World");
    _is_create_GameScene = false;
    _pLabel_Debug = NULL;
    _pLabel_Aster = NULL;
    _pLabel_Title = NULL;
    //�y�߂��z
    //������Actor��Scene��NEW���͂��Ă͂Ȃ�Ȃ��B
    //�܂��͂��̐�����邱�Ƃ�D�悵�Ȃ��ƁA���낢��ƕs�s��������B
}

void World::initialize() {
    _TRACE_("World::initialize()");
    pixcoord cx = CFG_PROPERTY(GAME_BUFFER_WIDTH)/2;
    pixcoord cy = CFG_PROPERTY(GAME_BUFFER_HEIGHT)/2;
    orderActorToFactory(0, LabelGecchi16Font, "STR01");
    _pLabel_Title = (LabelGecchi16Font*)obtainActorFromFactory(0);
    getDirector()->addSubGroup(_pLabel_Title);
    _pLabel_Title->update(PX2CO(cx), PX2CO(cy - 16),
                            "[ VIOLET VREATH ]", ALIGN_CENTER, VALIGN_MIDDLE);

    orderActorToFactory(0, LabelGecchi16Font, "STR01");
    _pLabel_Wait = (LabelGecchi16Font*)obtainActorFromFactory(0);
    getDirector()->addSubGroup(_pLabel_Wait);
    _pLabel_Wait->update(PX2CO(cx), PX2CO(cy + 16),
                            "WATE A MOMENT PLASE...", ALIGN_CENTER, VALIGN_MIDDLE);

    orderActorToFactory(0, LabelGecchi16Font, "ASTER");
    _pLabel_Aster = (LabelGecchi16Font*)obtainActorFromFactory(0);
    getDirector()->addSubGroup(_pLabel_Aster);
    _pLabel_Aster->update(PX2CO(CFG_PROPERTY(GAME_BUFFER_WIDTH)), 0, "*", ALIGN_RIGHT, VALIGN_TOP);
    _pLabel_Aster->_pFader->beat(60, 30, 0, 0, -1); //�`�J�`�J�_��
#ifdef MY_DEBUG
    ColliAABActor::get();     //�����蔻��̈�\���p�����́A�v�����[�h
    ColliAAPrismActor::get(); //�����蔻��̈�\���p�v���Y���A�v�����[�h
    ColliSphereActor::get();  //�����蔻��̈�\���p���A�v�����[�h
#endif
    orderActorToFactory(0, LabelGecchi16Font, "DebugStr");
    _pLabel_Debug = (LabelGecchi16Font*)obtainActorFromFactory(0);
    getDirector()->addSubGroup(_pLabel_Debug);

    orderSceneToFactory(1, PreDrawScene, "PreDraw");
    orderSceneToFactory(2, GameScene, "Game");
}

void World::processBehavior() {
    if (_is_create_GameScene) {
        //GameScene�쐬����
        VB->update(); //���͏��X�V
#ifdef MY_DEBUG
        if (P_GOD->_sync_frame_time) {
            _TEXT_("z");
        }
#endif
        if (GgafDxInput::isBeingPressedKey(DIK_Q)) {
            //TODO:�I������
        }
    } else {
        //GameScene�쐬�����܂ő҂�
        if (GgafFactory::chkProgress(1) == 2 && GgafFactory::chkProgress(2) == 2) {
            _pPreDrawScene = (PreDrawScene*)obtainSceneFromFactory(1);
            addSubLast(_pPreDrawScene);
            _pGameScene = (GameScene*)obtainSceneFromFactory(2);
            addSubLast(_pGameScene);
            _is_create_GameScene = true;
            _pLabel_Title->end();
            _pLabel_Wait->end();
            _pLabel_Aster->end();
        } else {
            //�҂��ڂ���
            _pLabel_Aster->_pFader->behave();
        }
    }

#ifdef MY_DEBUG
    sprintf(_aBufDebug, "%05uDRAW / %06uCHK / %07uF / %03.1fFPS / NEW=%d",
            GgafGod::_num_actor_drawing,
            CollisionChecker::_num_check,
            (unsigned int)askGod()->_frame_of_God,
            askGod()->_fps,
//            ((GgafFactory::CREATING_ORDER->_progress==1) ? GgafFactory::CREATING_ORDER->_pObject_Creation->toString() : "NOTHING"),
            ((GgafFactory::CREATING_ORDER->_progress==1) ? GgafFactory::CREATING_ORDER->_id : 0)
            );
    _pLabel_Debug->update(PX2CO(1), PX2CO(1), _aBufDebug);
    if (getActivePartFrame() % 60 == 0) {
        _TRACE_("_aBufDebug="<<_aBufDebug);
    }
#else
    sprintf(_aBufDebug, "%05uDRAW / %06uCHK / %07uF / %03.1fFPS / NEW=%d",
            GgafGod::_num_actor_drawing,
            CollisionChecker::_num_check,
            (unsigned int)askGod()->_frame_of_God,
            askGod()->_fps,
            ((GgafFactory::CREATING_ORDER->_progress==1)  ? GgafFactory::CREATING_ORDER->_id : 0)
            );
    _pLabel_Debug->update(PX2CO(1), PX2CO(1), _aBufDebug);
#endif


}

void World::processJudgement() {
}

World::~World() {
}

