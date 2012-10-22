#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

VirtualButton* God::pVbtn_PLAY_ = NULL;
VirtualButton* God::pVbtn_UI_ = NULL;
VirtualButton* God::pVbtn_Active_ = NULL;
VirtualButton* God::pVbtn_Active_next_frame_ = NULL;

God::God(HINSTANCE prm_hInstance, HWND prm_pHWndPrimary, HWND prm_pHWndSecondary) :
      DefaultGod(prm_hInstance, prm_pHWndPrimary, prm_pHWndSecondary) {
    pDepoManager_ = NEW DepositoryManager("DepositoryManager");
    pSpl3DManager_ = NEW SplineLineManager("SplineLineManager");
    God::pVbtn_PLAY_ = NEW VirtualButton("VB_PLAY.rep");
    God::pVbtn_UI_   = NEW VirtualButton("VB_UI.rep");
#ifdef MY_DEBUG
    pVbtn_PLAY_->_pRpy->setRealtimeOutputFile("VB_PLAY_LAST_REALTIME.rep");
    pVbtn_UI_->_pRpy->setRealtimeOutputFile("VB_UI_LAST_REALTIME.rep");
#endif
    God::pVbtn_Active_ = God::pVbtn_UI_;
    God::pVbtn_Active_next_frame_ = God::pVbtn_UI_;

    if (pVbtn_PLAY_->_is_replaying && pVbtn_UI_->_is_replaying) {
        _TRACE_("�v���C���v���C��񁛁AUI���v���C���");
        _TRACE_("���v���C�Đ����[�h�ł��B");
    } else if (!pVbtn_PLAY_->_is_replaying && pVbtn_UI_->_is_replaying) {
        _TRACE_("�v���C���v���C���~�AUI���v���C���");
    } else if (pVbtn_PLAY_->_is_replaying && !pVbtn_UI_->_is_replaying) {
        _TRACE_("�v���C���v���C��񁛁AUI���v���C���~");
        _TRACE_("���v���C�Đ����[�h�ł��B");
        _TRACE_("�A���A�v���C���v���C���� PAUSE����؂���܂��B");
        //�v���C���v���C����A����UI���v���C�����̏ꍇ�̂݁A�v���C���v���C��PAUSE������������
        VBReplayRecorder* pRepPlay = pVbtn_PLAY_->_pRpy;
        VBReplayRecorder::VBRecordNote* pRecNote = pRepPlay->_pFirstVBNote;
        while (pRecNote) {
            pRecNote->_state = pRecNote->_state & ~((vbsta)VB_PAUSE);
            pRecNote = pRecNote->_pNext;
        }
    } else {
        _TRACE_("�v���C���v���C���~�AUI���v���C���~");
        _TRACE_("���v���C�o�^���[�h�ł��B");
    }

    //�����L���O���ǂݍ���
    GameGlobal::qryRanking_.init();

    //���z�{�^����{�Q�[���p�ɏ㏑�����čĒ�`
    VirtualButton::_tagKeymap.BUTTON1    = VirtualButton::_mapDIK[ GGAF_PROPERTY(MY_KEY_SHOT1)      ];
    VirtualButton::_tagKeymap.BUTTON2    = VirtualButton::_mapDIK[ GGAF_PROPERTY(MY_KEY_SHOT2)      ];
    VirtualButton::_tagKeymap.BUTTON3    = VirtualButton::_mapDIK[ GGAF_PROPERTY(MY_KEY_OPTION)     ];
    VirtualButton::_tagKeymap.BUTTON4    = VirtualButton::_mapDIK[ GGAF_PROPERTY(MY_KEY_VIEW)       ];
    VirtualButton::_tagKeymap.BUTTON5    = VirtualButton::_mapDIK[ GGAF_PROPERTY(MY_KEY_TURBO)      ];
    VirtualButton::_tagKeymap.BUTTON6    = VirtualButton::_mapDIK[ GGAF_PROPERTY(MY_KEY_POWERUP)    ];
    VirtualButton::_tagKeymap.BUTTON7    = VirtualButton::_mapDIK[ GGAF_PROPERTY(MY_KEY_BUTTON7)    ];
    VirtualButton::_tagKeymap.BUTTON8    = VirtualButton::_mapDIK[ GGAF_PROPERTY(MY_KEY_BUTTON8)    ];
    VirtualButton::_tagKeymap.PAUSE      = VirtualButton::_mapDIK[ GGAF_PROPERTY(MY_KEY_PAUSE)      ];
    VirtualButton::_tagKeymap.UP         = VirtualButton::_mapDIK[ GGAF_PROPERTY(MY_KEY_UP)         ];
    VirtualButton::_tagKeymap.DOWN       = VirtualButton::_mapDIK[ GGAF_PROPERTY(MY_KEY_DOWN)       ];
    VirtualButton::_tagKeymap.LEFT       = VirtualButton::_mapDIK[ GGAF_PROPERTY(MY_KEY_LEFT)       ];
    VirtualButton::_tagKeymap.RIGHT      = VirtualButton::_mapDIK[ GGAF_PROPERTY(MY_KEY_RIGHT)      ];
    VirtualButton::_tagKeymap.UI_UP      = VirtualButton::_mapDIK[ GGAF_PROPERTY(MY_KEY_UI_UP)      ];
    VirtualButton::_tagKeymap.UI_DOWN    = VirtualButton::_mapDIK[ GGAF_PROPERTY(MY_KEY_UI_DOWN)    ];
    VirtualButton::_tagKeymap.UI_LEFT    = VirtualButton::_mapDIK[ GGAF_PROPERTY(MY_KEY_UI_LEFT)    ];
    VirtualButton::_tagKeymap.UI_RIGHT   = VirtualButton::_mapDIK[ GGAF_PROPERTY(MY_KEY_UI_RIGHT)   ];
    VirtualButton::_tagKeymap.UI_EXECUTE = VirtualButton::_mapDIK[ GGAF_PROPERTY(MY_KEY_UI_EXECUTE) ];
    VirtualButton::_tagKeymap.UI_CANCEL  = VirtualButton::_mapDIK[ GGAF_PROPERTY(MY_KEY_UI_CANCEL)  ];
    VirtualButton::_tagKeymap.UI_DEBUG   = VirtualButton::_mapDIK[ GGAF_PROPERTY(MY_KEY_UI_DEBUG)   ];

    VirtualButton::_tagJoymap.BUTTON1    = VirtualButton::_mapDIK[ GGAF_PROPERTY(MY_JOY_SHOT1)      ];
    VirtualButton::_tagJoymap.BUTTON2    = VirtualButton::_mapDIK[ GGAF_PROPERTY(MY_JOY_SHOT2)      ];
    VirtualButton::_tagJoymap.BUTTON3    = VirtualButton::_mapDIK[ GGAF_PROPERTY(MY_JOY_OPTION)     ];
    VirtualButton::_tagJoymap.BUTTON4    = VirtualButton::_mapDIK[ GGAF_PROPERTY(MY_JOY_VIEW)       ];
    VirtualButton::_tagJoymap.BUTTON5    = VirtualButton::_mapDIK[ GGAF_PROPERTY(MY_JOY_TURBO)      ];
    VirtualButton::_tagJoymap.BUTTON6    = VirtualButton::_mapDIK[ GGAF_PROPERTY(MY_JOY_POWERUP)    ];
    VirtualButton::_tagJoymap.BUTTON7    = VirtualButton::_mapDIK[ GGAF_PROPERTY(MY_JOY_BUTTON7)    ];
    VirtualButton::_tagJoymap.BUTTON8    = VirtualButton::_mapDIK[ GGAF_PROPERTY(MY_JOY_BUTTON8)    ];
    VirtualButton::_tagJoymap.PAUSE      = VirtualButton::_mapDIK[ GGAF_PROPERTY(MY_JOY_PAUSE)      ];
    VirtualButton::_tagJoymap.UI_EXECUTE = VirtualButton::_mapDIK[ GGAF_PROPERTY(MY_JOY_UI_EXECUTE) ];
    VirtualButton::_tagJoymap.UI_CANCEL  = VirtualButton::_mapDIK[ GGAF_PROPERTY(MY_JOY_UI_CANCEL)  ];

    GgafRepeatSeq::create("CH_bomb1", 0, 20);
    GgafRepeatSeq::create("CH_yume_Sbend", 0, 18);
    GgafRepeatSeq::create("CH_yume_shototsu", 0, 20);
    GgafRepeatSeq::create("CH_break_glass01", 0, 20);
    GgafRepeatSeq::create("CH_a_shot", 0, 5);
    GgafRepeatSeq::create("CH_laser001", 0, 8); //�I�v�V�������[�U�[
    GgafRepeatSeq::create("CH_cm-22", 0, 8); //Juno���ˉ�
    GgafRepeatSeq::create("CH_bom10", 0, 20); //Metis����
    GgafRepeatSeq::create("CH_explos3", 0, 3); //Romulus����
    GgafRepeatSeq::create("CH_humei10", 0, 1); //Lockon
    GgafRepeatSeq::create("CH_fire01", 0, 16); //���@�V���b�g
    GgafRepeatSeq::create("CH_torpedo", 0, 5); //�~�T�C��
    GgafRepeatSeq::create("CH_warp", 0, 4); //�n�b�`�I�[�v��
    GgafRepeatSeq::create("CH_yume_organ_01", 0, 4); //�n�b�`�N���[�Y
}

GgafUniverse* God::createUniverse() {
    Camera* pCamera = NEW Camera("CAMERA");    //FovX����p80�x�A�[���~GAME_SPACE_DEPTH
    Universe* pUniverse = NEW Universe("MYUNIVERSE", pCamera);
    return (GgafUniverse*)pUniverse;
}

void God::clean() {
    if (!_was_cleaned) {
        if (VB_PLAY->_is_replaying) {
            //VB_PLAY->_pRpy->outputFile("VB_PLAY_LAST_REPADD.rep");
        } else {
            _TRACE_("write VB_PLAY_LAST.rep");
            VB_PLAY->_pRpy->outputFile("VB_PLAY_LAST.rep");
        }
        if (VB_UI->_is_replaying) {
            //VB_PLAY->_pRpy->outputFile("VB_PLAY_LAST_REPADD.rep");
        } else {
            _TRACE_("write VB_UI_LAST.rep");
            VB_UI->_pRpy->outputFile("VB_UI_LAST.rep");
        }
        _TRACE_("God::clean() begin");
        DefaultGod::clean();
        DELETE_IMPOSSIBLE_NULL(pVbtn_PLAY_);
        DELETE_IMPOSSIBLE_NULL(pVbtn_UI_);
        DELETE_IMPOSSIBLE_NULL(pDepoManager_);
        DELETE_IMPOSSIBLE_NULL(pSpl3DManager_);
        _TRACE_("God::clean() end");
    }
}

void God::oops() {
    VB_PLAY->_pRpy->outputFile("VB_PLAY_LAST_Oops.rep");
    VB_UI->_pRpy->outputFile("VB_UI_LAST_Oops.rep");
    DefaultGod::oops(); //��ʂ́u���܂����I�v��
}

God::~God() {
    if (P_WORLD) {
        P_WORLD->throwEventToLowerTree(EVENT_GOD_WILL_DIE); //�S�V�[���ɒʒm
    }
    clean();
    _was_cleaned = true;
}

