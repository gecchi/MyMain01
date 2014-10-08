#include "God.h"

#include "jp/ggaf/lib/util/VirtualButton.h"
#include "jp/ggaf/lib/util/VBReplayRecorder.h"
#include "jp/gecchi/VioletVreath/manager/DepositoryManager.h"
#include "jp/gecchi/VioletVreath/manager/SplineLineManager.h"
#include "jp/gecchi/VioletVreath/manager/XpmManager.h"
#include "jp/gecchi/VioletVreath/Properties.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

VirtualButton* God::pVbtn_PLAY_ = nullptr;
VirtualButton* God::pVbtn_UI_ = nullptr;
VirtualButton* God::pVbtn_active_ = nullptr;
VirtualButton* God::pVbtn_active_next_frame_ = nullptr;
bool God::g_should_reboot_ = false;

God::God() :
      DefaultGod() {
    pDepoManager_ = NEW DepositoryManager("DepositoryManager");
    pSpl3DManager_ = NEW SplineLineManager("SplineLineManager");
    pXpmManager_ = NEW XpmManager("XpmManager");
    God::pVbtn_PLAY_ = NEW VirtualButton(FILE_INPUT_PLAY_REPLAY);
    God::pVbtn_UI_   = NEW VirtualButton(FILE_INPUT_UI_REPLAY);
#ifdef MY_DEBUG
    pVbtn_PLAY_->_pRpy->setRealtimeOutputFile(FILE_REALTIME_OUTPUT_PLAY_REPLAY);
    pVbtn_UI_->_pRpy->setRealtimeOutputFile(FILE_REALTIME_OUTPUT_UI_REPLAY);
    _TRACE_("�f�o�b�O���A���^�C�����v���C�L�^���[�h��");
#endif
    God::pVbtn_active_ = God::pVbtn_UI_;
    God::pVbtn_active_next_frame_ = God::pVbtn_UI_;

    if (pVbtn_PLAY_->_is_replaying && pVbtn_UI_->_is_replaying) {
        _TRACE_("�v���C���v���C��񁛁AUI���v���C���");
        _TRACE_("�����v���C�Đ����[�h�ł��B");
    } else if (!pVbtn_PLAY_->_is_replaying && pVbtn_UI_->_is_replaying) {
        _TRACE_("�v���C���v���C���~�AUI���v���C���");
        _TRACE_("��UI�̂ݍĐ����[�h�ł��B���Ă������Ӗ�����̂�H");
    } else if (pVbtn_PLAY_->_is_replaying && !pVbtn_UI_->_is_replaying) {
        _TRACE_("�v���C���v���C��񁛁AUI���v���C���~");
        _TRACE_("�����v���C�Đ����[�h�ł��B�A���A�v���C���v���C���� PAUSE����؂���܂��B");
        //�v���C���v���C����A����UI���v���C�����̏ꍇ�̂݁A�v���C���v���C��PAUSE������������
        VBReplayRecorder* pRepPlay = pVbtn_PLAY_->_pRpy;
        VBReplayRecorder::VBRecordNote* pRecNote = pRepPlay->_pFirstVBNote;
        vbsta vb_pause_not_mask = ~((vbsta)VB_PAUSE);
        while (pRecNote) {
            pRecNote->_state = (pRecNote->_state & vb_pause_not_mask);
            pRecNote = pRecNote->_pNext;
        }
    } else {
        _TRACE_("�v���C���v���C���~�AUI���v���C���~");
        _TRACE_("���v���C�o�^���[�h�ł��B");
    }

    //�����L���O���ǂݍ���
    G_RANKING_TABLE.init();
    initVB();
}

void God::initVB() {
    //���z�{�^����{�Q�[���p�ɏ㏑�����čĒ�`
    VirtualButton::_keyboardmap.BUTTON1    = VirtualButton::_mapStr2Dik[ PROPERTY::MY_KEY_SHOT1      ];
    VirtualButton::_keyboardmap.BUTTON2    = VirtualButton::_mapStr2Dik[ PROPERTY::MY_KEY_SHOT2      ];
    VirtualButton::_keyboardmap.BUTTON3    = VirtualButton::_mapStr2Dik[ PROPERTY::MY_KEY_OPTION     ];
    VirtualButton::_keyboardmap.BUTTON4    = VirtualButton::_mapStr2Dik[ PROPERTY::MY_KEY_VIEW       ];
    VirtualButton::_keyboardmap.BUTTON5    = VirtualButton::_mapStr2Dik[ PROPERTY::MY_KEY_TURBO      ];
    VirtualButton::_keyboardmap.BUTTON6    = VirtualButton::_mapStr2Dik[ PROPERTY::MY_KEY_POWERUP    ];
    VirtualButton::_keyboardmap.BUTTON7    = VirtualButton::_mapStr2Dik[ PROPERTY::MY_KEY_BUTTON7    ];
    VirtualButton::_keyboardmap.BUTTON8    = VirtualButton::_mapStr2Dik[ PROPERTY::MY_KEY_BUTTON8    ];
    VirtualButton::_keyboardmap.PAUSE      = VirtualButton::_mapStr2Dik[ PROPERTY::MY_KEY_PAUSE      ];
    VirtualButton::_keyboardmap.UP         = VirtualButton::_mapStr2Dik[ PROPERTY::MY_KEY_UP         ];
    VirtualButton::_keyboardmap.DOWN       = VirtualButton::_mapStr2Dik[ PROPERTY::MY_KEY_DOWN       ];
    VirtualButton::_keyboardmap.LEFT       = VirtualButton::_mapStr2Dik[ PROPERTY::MY_KEY_LEFT       ];
    VirtualButton::_keyboardmap.RIGHT      = VirtualButton::_mapStr2Dik[ PROPERTY::MY_KEY_RIGHT      ];
    VirtualButton::_keyboardmap.UI_UP      = VirtualButton::_mapStr2Dik[ PROPERTY::MY_KEY_UI_UP      ];
    VirtualButton::_keyboardmap.UI_DOWN    = VirtualButton::_mapStr2Dik[ PROPERTY::MY_KEY_UI_DOWN    ];
    VirtualButton::_keyboardmap.UI_LEFT    = VirtualButton::_mapStr2Dik[ PROPERTY::MY_KEY_UI_LEFT    ];
    VirtualButton::_keyboardmap.UI_RIGHT   = VirtualButton::_mapStr2Dik[ PROPERTY::MY_KEY_UI_RIGHT   ];
    VirtualButton::_keyboardmap.UI_EXECUTE = VirtualButton::_mapStr2Dik[ PROPERTY::MY_KEY_UI_EXECUTE ];
    VirtualButton::_keyboardmap.UI_CANCEL  = VirtualButton::_mapStr2Dik[ PROPERTY::MY_KEY_UI_CANCEL  ];
    VirtualButton::_keyboardmap.UI_DEBUG   = VirtualButton::_mapStr2Dik[ PROPERTY::MY_KEY_UI_DEBUG   ];

    VirtualButton::_joystickmap.BUTTON1    = VirtualButton::_mapStr2JoyBtn[ PROPERTY::MY_JOY_SHOT1      ];
    VirtualButton::_joystickmap.BUTTON2    = VirtualButton::_mapStr2JoyBtn[ PROPERTY::MY_JOY_SHOT2      ];
    VirtualButton::_joystickmap.BUTTON3    = VirtualButton::_mapStr2JoyBtn[ PROPERTY::MY_JOY_OPTION     ];
    VirtualButton::_joystickmap.BUTTON4    = VirtualButton::_mapStr2JoyBtn[ PROPERTY::MY_JOY_VIEW       ];
    VirtualButton::_joystickmap.BUTTON5    = VirtualButton::_mapStr2JoyBtn[ PROPERTY::MY_JOY_TURBO      ];
    VirtualButton::_joystickmap.BUTTON6    = VirtualButton::_mapStr2JoyBtn[ PROPERTY::MY_JOY_POWERUP    ];
    VirtualButton::_joystickmap.BUTTON7    = VirtualButton::_mapStr2JoyBtn[ PROPERTY::MY_JOY_BUTTON7    ];
    VirtualButton::_joystickmap.BUTTON8    = VirtualButton::_mapStr2JoyBtn[ PROPERTY::MY_JOY_BUTTON8    ];
    VirtualButton::_joystickmap.PAUSE      = VirtualButton::_mapStr2JoyBtn[ PROPERTY::MY_JOY_PAUSE      ];
    VirtualButton::_joystickmap.UI_EXECUTE = VirtualButton::_mapStr2JoyBtn[ PROPERTY::MY_JOY_UI_EXECUTE ];
    VirtualButton::_joystickmap.UI_CANCEL  = VirtualButton::_mapStr2JoyBtn[ PROPERTY::MY_JOY_UI_CANCEL  ];
}

GgafUniverse* God::createUniverse() {
    Camera* pCamera = NEW Camera("CAMERA");
    Universe* pUniverse = NEW Universe("MYUNIVERSE", pCamera);
    return (GgafUniverse*)pUniverse;
}

void God::clean() {
    if (!_was_cleaned) {
        if (VB_PLAY->_is_replaying) {
#ifdef MY_DEBUG
            VB_PLAY->_pRpy->outputFile("VB_PLAY_LAST_REPADD.rep");
#endif
        } else {
            VB_PLAY->_pRpy->outputFile(FILE_OUTPUT_PLAY_REPLAY);
        }
        if (VB_UI->_is_replaying) {
#ifdef MY_DEBUG
            VB_PLAY->_pRpy->outputFile("VB_UI_LAST_REPADD.rep");
#endif
        } else {
            VB_UI->_pRpy->outputFile(FILE_OUTPUT_UI_REPLAY);
        }
        _TRACE_("God::clean() begin");
        DefaultGod::clean();
        GGAF_DELETE(pVbtn_PLAY_);
        GGAF_DELETE(pVbtn_UI_);
        GGAF_DELETE(pDepoManager_);
        GGAF_DELETE(pSpl3DManager_);
        GGAF_DELETE(pXpmManager_);
        _TRACE_("God::clean() end");
    }
}

void God::reboot() {
    God::g_should_reboot_ = true; //�ċN���t���O�Z�b�g
    ::PostQuitMessage(0); //�I���I
}

void God::oops() {
    VB_PLAY->_pRpy->outputFile("VB_PLAY_LAST_Oops.rep");
    VB_UI->_pRpy->outputFile("VB_UI_LAST_Oops.rep");
    DefaultGod::oops(); //��ʂ́u���܂����I�v��
}

God::~God() {
    if (P_WORLD) {
        P_WORLD->throwEventLowerTree(EVENT_GOD_WILL_DIE); //�S�V�[���ɒʒm
    }
    clean();
    _was_cleaned = true;
}

