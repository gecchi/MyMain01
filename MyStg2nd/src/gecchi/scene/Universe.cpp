#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

Universe::Universe(const char* prm_name) : DefaultUniverse(prm_name) {
    _TRACE_("Universe::Universe()");

    GgafRepeatSeq::create("CH_bomb1", 0, 10);
    GgafRepeatSeq::create("CH_yume_Sbend", 0, 8);
    GgafRepeatSeq::create("CH_yume_shototsu", 0, 2);
    GgafRepeatSeq::create("CH_break_glass01", 0, 10);
    GgafRepeatSeq::create("CH_a_shot", 0, 3);
    GgafRepeatSeq::create("CH_laser001", 0, 8); //�I�v�V�������[�U�[
	GgafRepeatSeq::create("CH_cm-22", 0, 8); //Juno���ˉ�
	GgafRepeatSeq::create("CH_bom10", 0, 3); //Metis����
    GgafRepeatSeq::create("CH_explos3", 0, 3); //Vesta����
    GgafRepeatSeq::create("CH_humei10", 0, 1); //LockOn
    //�y�߂��z
    //������Actor��Scene��NEW���͂��Ă͂Ȃ�Ȃ��B
    //�܂��͂��̐�����邱�Ƃ�D�悵�Ȃ��ƁA���낢��ƕs�s��������B
}

void Universe::initialize() {
    _pWorld = NEW World("WORLD");
    addSubLast(_pWorld);

    _TRACE_("Universe::initialize()");
}

void Universe::processJudgement() {
    DefaultUniverse::processJudgement();
}

void Universe::processBehavior() {
    DefaultUniverse::processBehavior();
}

Universe::~Universe() {
}
