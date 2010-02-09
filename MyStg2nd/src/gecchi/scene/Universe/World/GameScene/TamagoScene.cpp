#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

TamagoScene::TamagoScene(const char* prm_name) : DefaultScene(prm_name) {
    orderActorToFactory(100000001, EnemyTamago01, "gyoku");
//    orderActorToFactory(100000002, EnemyTamago01, "gyoku");
//    orderActorToFactory(100000003, EnemyTamago01, "gyoku");
//    orderActorToFactory(100000004, EnemyTamago01, "gyoku");
//    orderActorToFactory(100000005, EnemyTamago01, "gyoku");
//    orderActorToFactory(100000006, EnemyTamago01, "gyoku");
//    orderActorToFactory(100000007, EnemyTamago01, "gyoku");
//    orderActorToFactory(100000008, EnemyTamago01, "gyoku");
//    orderActorToFactory(100000009, EnemyTamago01, "gyoku");
//    orderActorToFactory(100000010, EnemyTamago01, "gyoku");
//    orderActorToFactory(100000011, EnemyTamago01, "gyoku");
//    orderActorToFactory(100000012, EnemyTamago01, "gyoku");
//    orderActorToFactory(100000013, EnemyTamago01, "gyoku");
//    orderActorToFactory(100000014, EnemyTamago01, "gyoku");
//    orderActorToFactory(100000015, EnemyTamago01, "gyoku");
//    orderActorToFactory(100000016, EnemyTamago01, "gyoku");

}

void TamagoScene::reset() {
}
void TamagoScene::ready() {
}

void TamagoScene::initialize() {
}

void TamagoScene::processBehavior() {
//    for (int i = 1; i <= 16; i++) {
//        if (getBehaveingFrame() == i*8) {
//            getLordActor()->addSubGroup(obtainActorFromFactory(100000000+i));
//        }
//    }
}

void TamagoScene::processFinal() {
}

TamagoScene::~TamagoScene() {
}
