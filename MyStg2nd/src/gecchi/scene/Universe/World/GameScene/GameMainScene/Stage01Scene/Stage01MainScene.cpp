#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

Stage01MainScene::Stage01MainScene(const char* prm_name) : DefaultScene(prm_name) {

    _pDispatcher = NEW GgafActorDispatcher("RotEnemyMeshS001");
    EnemyMeshShot001* pEnemyMeshShot;
    for (int i = 0; i < 100; i++) {
        Sleep(1);
        pEnemyMeshShot = NEW EnemyMeshShot001("EnemyMeshShot");
        pEnemyMeshShot->inactivateTreeImmediately(); //最初非表示
        _pDispatcher->addSubLast(pEnemyMeshShot);
    }
    getLordActor()->addSubGroup(KIND_ENEMY_SHOT_CHOKI, _pDispatcher);

    // 以下の gen01 start ～ end はExcelマクロにより自動生成されたコードです。
    // コード変更は「シーンCreater.xls」を開いて、そこから行う。
    // gen01 start
	DWORD dw[] = {1,2,10,100,110,210,310,410,500,510,530,560,590,610,620,650,710,810,910,1000,1010,1110,1210,1310,1410,1500,1510,1530,1560,1590,1610,1620,1650,1710,1810,1910,2000,2010,2110,2210,2310,2410,2510,2610,2710,2810,2900,2910,3000,3010,3110,3210,3310,3410,3500,3510,3610,3710,3810,3910,4000,4010,4110,4210,4310,4410,4500,4510,4530,4560,4590,4610,4620,4650,4710,4810,4900,4910,5000,5002,5010,5110,5210,5310,5410,5500,5510,5530,5560,5590,5610,5620,5650,5710,5810,5910,6000,6010,6110,6210,6310,6410,6500,6510,6610,6710,6810,6910,7000,7010,7110,7210,7310,7410,7510,7610,7710,7810,7900,7910,8000,8002,8010,8110,8210,8310,8410,8500,8510,8530,8560,8590,8610,8620,8650,8710,8810,8910,9000,9010,9110,9210,9310,9400,9410,9500,9510,9530,9560,9590,9610,9620,9650,9710,9810,9900,9910,10000,10010,10110,10210,10310,10410,10510,10610,10710,10810,10910,11000,11010,11110,11210,11310,11410,11500,11510,11610,11710,11810,11910,12000,12010,12110,12210,12310,12400,12410,12500,12510,12530,12560,12590,12610,12620,12650,12710,12810,12900,12910,13000,13002,13010,13110,13210,13310,13410,13500,13510,13530,13560,13590,13610,13620,13650,13710,13810,13910,14000,14010,14110,14210,14310,14400,14410,14510,14610,14710,14810,14900,14910,15000,15010,15110,15210,15310,15410,15510,15610,15710,15810,15910,16000,16002,16010,16110,16210,16310,16410,16500,16510,16530,16560,16590,16610,16620,16650,16710,16810,16910,17000,17010,17110,17210,17310,17400,17410,17510,17610,17710,17810,17900,17910,18010,18110,18210,18310,18410,18510,18610,18710,18810,18910,19000,19010,19110,19210,19310,19410,19510,19610,19710,19810,19910,20000,20010,20110,20210,20310,20410,20510,20610,20710,20810,20910,21010,21110,21210,21310,21410,21510,21610,21710,21810,21910,22010,22110,22210,22310,22410,22510,22610,22710,22810,22910,23010,23110,23210,23310,23410,23510,23610,23710,23810,23910,24010,24110,24210,24310,24410,24510,24610,24710,24810,24910,25010,25110,25210,25310,25410,25510,25610,25710,25810,25910,26010,26110,26210,26310,26410,26510,26610,26710,26810,26910,27010,27110,27210,27310,27410,27510,27610,27710,27810,27910,28010,28110,28210,28310,28410,28510,28610,28710,28810,28910,29010,29110,29210,29310,29410,29510,29610,29710,29810,29910,30010,30110,30210,30310,30410,30510,30610,30710,30810,30910,31010,31110,31210,31310,31410,31510,31610,31710,31810,31910};
	_paFrame_NextEvent = new DWORD[414];
	for (int i = 0; i < 414; i++) {
		_paFrame_NextEvent[i] = dw[i];
	}
	orderActorToFactory(110263000, VarietyTorus001, "VarietyTorus001_1");
	orderActorToFactory(1109710, EnemyMetis, "Metis_2");
	orderActorToFactory(11097110, EnemyMetis, "Metis_3");
	orderActorToFactory(11097210, EnemyMetis, "Metis_4");
	orderActorToFactory(11097310, EnemyMetis, "Metis_5");
	orderActorToFactory(11097410, EnemyMetis, "Metis_6");
	orderActorToFactory(11097510, EnemyMetis, "Metis_7");
	orderActorToFactory(11097610, EnemyMetis, "Metis_8");
	orderActorToFactory(11097710, EnemyMetis, "Metis_9");
	orderActorToFactory(11097810, EnemyMetis, "Metis_10");
	orderActorToFactory(11097910, EnemyMetis, "Metis_11");
	orderActorToFactory(110971010, EnemyMetis, "Metis_12");
	orderActorToFactory(110971110, EnemyMetis, "Metis_13");
	orderActorToFactory(110971210, EnemyMetis, "Metis_14");
	orderActorToFactory(110971310, EnemyMetis, "Metis_15");
	orderActorToFactory(110971410, EnemyMetis, "Metis_16");
	orderActorToFactory(110971510, EnemyMetis, "Metis_17");
	orderActorToFactory(110971610, EnemyMetis, "Metis_18");
	orderActorToFactory(110971710, EnemyMetis, "Metis_19");
	orderActorToFactory(110971810, EnemyMetis, "Metis_20");
	orderActorToFactory(110971910, EnemyMetis, "Metis_21");
	orderActorToFactory(110972010, EnemyMetis, "Metis_22");
	orderActorToFactory(110972110, EnemyMetis, "Metis_23");
	orderActorToFactory(110972210, EnemyMetis, "Metis_24");
	orderActorToFactory(110972310, EnemyMetis, "Metis_25");
	orderActorToFactory(110972410, EnemyMetis, "Metis_26");
	orderActorToFactory(110972510, EnemyMetis, "Metis_27");
	orderActorToFactory(110972610, EnemyMetis, "Metis_28");
	orderActorToFactory(110972710, EnemyMetis, "Metis_29");
	orderActorToFactory(110972810, EnemyMetis, "Metis_30");
	orderActorToFactory(110972910, EnemyMetis, "Metis_31");
	orderActorToFactory(11117100, EnemyAstraea, "Astraea_32");
	orderActorToFactory(111372900, EnemyAstraea, "Astraea_33");
	orderActorToFactory(112071500, EnemyAstraea, "Astraea_34");
	orderActorToFactory(1128710, FormationIris001, "F001_Iris_35");
	orderActorToFactory(112872010, FormationIris001, "F001_Iris_36");
	orderActorToFactory(112971000, FormationIris002, "F002_Iris_37");
	orderActorToFactory(112973000, FormationIris002, "F002_Iris_38");
	orderActorWithDpToFactory(11317500, EnemyCeres, "Ceres_39", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
	orderActorWithDpToFactory(11327530, EnemyCeres, "Ceres_40", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
	orderActorWithDpToFactory(11337560, EnemyCeres, "Ceres_41", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
	orderActorWithDpToFactory(11347590, EnemyCeres, "Ceres_42", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
	orderActorWithDpToFactory(11357620, EnemyCeres, "Ceres_43", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
	orderActorWithDpToFactory(11367650, EnemyCeres, "Ceres_44", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
	orderActorToFactory(113872, FormationJuno001, "F002_Juno_45");
    // gen01 end
}

void Stage01MainScene::initialize() {

}

void Stage01MainScene::processBehavior() {
    // 以下の gen02 start ～ end はマクロにより自動生成されたコードです。
    // gen02 start
	if (getPartFrame() == _paFrame_NextEvent[_iCnt_Event]) {
		switch (getPartFrame()) {
			case 1:
				break;
			case 2:
				{
				FormationJuno001* pFormationActor = (FormationJuno001*)obtainActorFromFactory(113872);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 10:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109710));
				orderActorToFactory(110973010, EnemyMetis, "Metis_46");
				{
				FormationIris001* pFormationActor = (FormationIris001*)obtainActorFromFactory(1128710);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 100:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(11117100);
				getLordActor()->addSubGroup(pActor);
				pActor->_X = 8000000;
				pActor->_Z = -200000;
				pActor->_Y = -300000;
				}
				break;
			case 110:
				getLordActor()->addSubGroup(obtainActorFromFactory(11097110));
				orderActorToFactory(110973110, EnemyMetis, "Metis_47");
				break;
			case 210:
				getLordActor()->addSubGroup(obtainActorFromFactory(11097210));
				orderActorToFactory(110973210, EnemyMetis, "Metis_48");
				break;
			case 310:
				getLordActor()->addSubGroup(obtainActorFromFactory(11097310));
				orderActorToFactory(110973310, EnemyMetis, "Metis_49");
				break;
			case 410:
				getLordActor()->addSubGroup(obtainActorFromFactory(11097410));
				orderActorToFactory(110973410, EnemyMetis, "Metis_50");
				break;
			case 500:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11317500);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 510:
				getLordActor()->addSubGroup(obtainActorFromFactory(11097510));
				orderActorToFactory(110973510, EnemyMetis, "Metis_51");
				break;
			case 530:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11327530);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 560:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11337560);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 590:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11347590);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 610:
				getLordActor()->addSubGroup(obtainActorFromFactory(11097610));
				orderActorToFactory(110973610, EnemyMetis, "Metis_52");
				break;
			case 620:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11357620);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 650:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11367650);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 710:
				getLordActor()->addSubGroup(obtainActorFromFactory(11097710));
				orderActorToFactory(110973710, EnemyMetis, "Metis_53");
				break;
			case 810:
				getLordActor()->addSubGroup(obtainActorFromFactory(11097810));
				orderActorToFactory(110973810, EnemyMetis, "Metis_54");
				break;
			case 910:
				getLordActor()->addSubGroup(obtainActorFromFactory(11097910));
				orderActorToFactory(110973910, EnemyMetis, "Metis_55");
				break;
			case 1000:
				{
				FormationIris002* pFormationActor = (FormationIris002*)obtainActorFromFactory(112971000);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 1010:
				getLordActor()->addSubGroup(obtainActorFromFactory(110971010));
				orderActorToFactory(110974010, EnemyMetis, "Metis_56");
				orderActorToFactory(112874010, FormationIris001, "F001_Iris_57");
				break;
			case 1110:
				getLordActor()->addSubGroup(obtainActorFromFactory(110971110));
				orderActorToFactory(110974110, EnemyMetis, "Metis_58");
				break;
			case 1210:
				getLordActor()->addSubGroup(obtainActorFromFactory(110971210));
				orderActorToFactory(110974210, EnemyMetis, "Metis_59");
				break;
			case 1310:
				getLordActor()->addSubGroup(obtainActorFromFactory(110971310));
				orderActorToFactory(110974310, EnemyMetis, "Metis_60");
				break;
			case 1410:
				getLordActor()->addSubGroup(obtainActorFromFactory(110971410));
				orderActorToFactory(110974410, EnemyMetis, "Metis_61");
				break;
			case 1500:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(112071500);
				getLordActor()->addSubGroup(pActor);
				pActor->_X = 9000000;
				pActor->_Z = 920000;
				pActor->_Y = -250000;
				}
				orderActorWithDpToFactory(113174500, EnemyCeres, "Ceres_62", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 1510:
				getLordActor()->addSubGroup(obtainActorFromFactory(110971510));
				orderActorToFactory(110974510, EnemyMetis, "Metis_63");
				break;
			case 1530:
				orderActorWithDpToFactory(113274530, EnemyCeres, "Ceres_64", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 1560:
				orderActorWithDpToFactory(113374560, EnemyCeres, "Ceres_65", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 1590:
				orderActorWithDpToFactory(113474590, EnemyCeres, "Ceres_66", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 1610:
				getLordActor()->addSubGroup(obtainActorFromFactory(110971610));
				orderActorToFactory(110974610, EnemyMetis, "Metis_67");
				break;
			case 1620:
				orderActorWithDpToFactory(113574620, EnemyCeres, "Ceres_68", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 1650:
				orderActorWithDpToFactory(113674650, EnemyCeres, "Ceres_69", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 1710:
				getLordActor()->addSubGroup(obtainActorFromFactory(110971710));
				orderActorToFactory(110974710, EnemyMetis, "Metis_70");
				break;
			case 1810:
				getLordActor()->addSubGroup(obtainActorFromFactory(110971810));
				orderActorToFactory(110974810, EnemyMetis, "Metis_71");
				break;
			case 1910:
				getLordActor()->addSubGroup(obtainActorFromFactory(110971910));
				orderActorToFactory(110974910, EnemyMetis, "Metis_72");
				break;
			case 2000:
				orderActorToFactory(112975000, FormationIris002, "F002_Iris_73");
				break;
			case 2010:
				getLordActor()->addSubGroup(obtainActorFromFactory(110972010));
				orderActorToFactory(110975010, EnemyMetis, "Metis_74");
				{
				FormationIris001* pFormationActor = (FormationIris001*)obtainActorFromFactory(112872010);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 2110:
				getLordActor()->addSubGroup(obtainActorFromFactory(110972110));
				orderActorToFactory(110975110, EnemyMetis, "Metis_75");
				break;
			case 2210:
				getLordActor()->addSubGroup(obtainActorFromFactory(110972210));
				orderActorToFactory(110975210, EnemyMetis, "Metis_76");
				break;
			case 2310:
				getLordActor()->addSubGroup(obtainActorFromFactory(110972310));
				orderActorToFactory(110975310, EnemyMetis, "Metis_77");
				break;
			case 2410:
				getLordActor()->addSubGroup(obtainActorFromFactory(110972410));
				orderActorToFactory(110975410, EnemyMetis, "Metis_78");
				break;
			case 2510:
				getLordActor()->addSubGroup(obtainActorFromFactory(110972510));
				orderActorToFactory(110975510, EnemyMetis, "Metis_79");
				break;
			case 2610:
				getLordActor()->addSubGroup(obtainActorFromFactory(110972610));
				orderActorToFactory(110975610, EnemyMetis, "Metis_80");
				break;
			case 2710:
				getLordActor()->addSubGroup(obtainActorFromFactory(110972710));
				orderActorToFactory(110975710, EnemyMetis, "Metis_81");
				break;
			case 2810:
				getLordActor()->addSubGroup(obtainActorFromFactory(110972810));
				orderActorToFactory(110975810, EnemyMetis, "Metis_82");
				break;
			case 2900:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(111372900);
				getLordActor()->addSubGroup(pActor);
				pActor->_X = 9000000;
				pActor->_Z = -900000;
				pActor->_Y = -100000;
				}
				break;
			case 2910:
				getLordActor()->addSubGroup(obtainActorFromFactory(110972910));
				orderActorToFactory(110975910, EnemyMetis, "Metis_83");
				break;
			case 3000:
				getLordActor()->addSubGroup(obtainActorFromFactory(110263000));
				{
				FormationIris002* pFormationActor = (FormationIris002*)obtainActorFromFactory(112973000);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 3010:
				getLordActor()->addSubGroup(obtainActorFromFactory(110973010));
				orderActorToFactory(110976010, EnemyMetis, "Metis_84");
				orderActorToFactory(112876010, FormationIris001, "F001_Iris_85");
				break;
			case 3110:
				getLordActor()->addSubGroup(obtainActorFromFactory(110973110));
				orderActorToFactory(110976110, EnemyMetis, "Metis_86");
				break;
			case 3210:
				getLordActor()->addSubGroup(obtainActorFromFactory(110973210));
				orderActorToFactory(110976210, EnemyMetis, "Metis_87");
				break;
			case 3310:
				getLordActor()->addSubGroup(obtainActorFromFactory(110973310));
				orderActorToFactory(110976310, EnemyMetis, "Metis_88");
				break;
			case 3410:
				getLordActor()->addSubGroup(obtainActorFromFactory(110973410));
				orderActorToFactory(110976410, EnemyMetis, "Metis_89");
				break;
			case 3500:
				orderActorToFactory(112076500, EnemyAstraea, "Astraea_90");
				break;
			case 3510:
				getLordActor()->addSubGroup(obtainActorFromFactory(110973510));
				orderActorToFactory(110976510, EnemyMetis, "Metis_91");
				break;
			case 3610:
				getLordActor()->addSubGroup(obtainActorFromFactory(110973610));
				orderActorToFactory(110976610, EnemyMetis, "Metis_92");
				break;
			case 3710:
				getLordActor()->addSubGroup(obtainActorFromFactory(110973710));
				orderActorToFactory(110976710, EnemyMetis, "Metis_93");
				break;
			case 3810:
				getLordActor()->addSubGroup(obtainActorFromFactory(110973810));
				orderActorToFactory(110976810, EnemyMetis, "Metis_94");
				break;
			case 3910:
				getLordActor()->addSubGroup(obtainActorFromFactory(110973910));
				orderActorToFactory(110976910, EnemyMetis, "Metis_95");
				break;
			case 4000:
				orderActorToFactory(112977000, FormationIris002, "F002_Iris_96");
				break;
			case 4010:
				getLordActor()->addSubGroup(obtainActorFromFactory(110974010));
				orderActorToFactory(110977010, EnemyMetis, "Metis_97");
				{
				FormationIris001* pFormationActor = (FormationIris001*)obtainActorFromFactory(112874010);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 4110:
				getLordActor()->addSubGroup(obtainActorFromFactory(110974110));
				orderActorToFactory(110977110, EnemyMetis, "Metis_98");
				break;
			case 4210:
				getLordActor()->addSubGroup(obtainActorFromFactory(110974210));
				orderActorToFactory(110977210, EnemyMetis, "Metis_99");
				break;
			case 4310:
				getLordActor()->addSubGroup(obtainActorFromFactory(110974310));
				orderActorToFactory(110977310, EnemyMetis, "Metis_100");
				break;
			case 4410:
				getLordActor()->addSubGroup(obtainActorFromFactory(110974410));
				orderActorToFactory(110977410, EnemyMetis, "Metis_101");
				break;
			case 4500:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113174500);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 4510:
				getLordActor()->addSubGroup(obtainActorFromFactory(110974510));
				orderActorToFactory(110977510, EnemyMetis, "Metis_102");
				break;
			case 4530:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113274530);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 4560:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113374560);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 4590:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113474590);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 4610:
				getLordActor()->addSubGroup(obtainActorFromFactory(110974610));
				orderActorToFactory(110977610, EnemyMetis, "Metis_103");
				break;
			case 4620:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113574620);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 4650:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113674650);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 4710:
				getLordActor()->addSubGroup(obtainActorFromFactory(110974710));
				orderActorToFactory(110977710, EnemyMetis, "Metis_104");
				break;
			case 4810:
				getLordActor()->addSubGroup(obtainActorFromFactory(110974810));
				orderActorToFactory(110977810, EnemyMetis, "Metis_105");
				break;
			case 4900:
				orderActorToFactory(111377900, EnemyAstraea, "Astraea_106");
				break;
			case 4910:
				getLordActor()->addSubGroup(obtainActorFromFactory(110974910));
				orderActorToFactory(110977910, EnemyMetis, "Metis_107");
				break;
			case 5000:
				{
				FormationIris002* pFormationActor = (FormationIris002*)obtainActorFromFactory(112975000);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 5002:
				orderActorToFactory(113878002, FormationJuno001, "F002_Juno_108");
				break;
			case 5010:
				getLordActor()->addSubGroup(obtainActorFromFactory(110975010));
				orderActorToFactory(110978010, EnemyMetis, "Metis_109");
				orderActorToFactory(112878010, FormationIris001, "F001_Iris_110");
				break;
			case 5110:
				getLordActor()->addSubGroup(obtainActorFromFactory(110975110));
				orderActorToFactory(110978110, EnemyMetis, "Metis_111");
				break;
			case 5210:
				getLordActor()->addSubGroup(obtainActorFromFactory(110975210));
				orderActorToFactory(110978210, EnemyMetis, "Metis_112");
				break;
			case 5310:
				getLordActor()->addSubGroup(obtainActorFromFactory(110975310));
				orderActorToFactory(110978310, EnemyMetis, "Metis_113");
				break;
			case 5410:
				getLordActor()->addSubGroup(obtainActorFromFactory(110975410));
				orderActorToFactory(110978410, EnemyMetis, "Metis_114");
				break;
			case 5500:
				orderActorWithDpToFactory(113178500, EnemyCeres, "Ceres_115", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 5510:
				getLordActor()->addSubGroup(obtainActorFromFactory(110975510));
				orderActorToFactory(110978510, EnemyMetis, "Metis_116");
				break;
			case 5530:
				orderActorWithDpToFactory(113278530, EnemyCeres, "Ceres_117", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 5560:
				orderActorWithDpToFactory(113378560, EnemyCeres, "Ceres_118", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 5590:
				orderActorWithDpToFactory(113478590, EnemyCeres, "Ceres_119", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 5610:
				getLordActor()->addSubGroup(obtainActorFromFactory(110975610));
				orderActorToFactory(110978610, EnemyMetis, "Metis_120");
				break;
			case 5620:
				orderActorWithDpToFactory(113578620, EnemyCeres, "Ceres_121", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 5650:
				orderActorWithDpToFactory(113678650, EnemyCeres, "Ceres_122", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 5710:
				getLordActor()->addSubGroup(obtainActorFromFactory(110975710));
				orderActorToFactory(110978710, EnemyMetis, "Metis_123");
				break;
			case 5810:
				getLordActor()->addSubGroup(obtainActorFromFactory(110975810));
				orderActorToFactory(110978810, EnemyMetis, "Metis_124");
				break;
			case 5910:
				getLordActor()->addSubGroup(obtainActorFromFactory(110975910));
				orderActorToFactory(110978910, EnemyMetis, "Metis_125");
				break;
			case 6000:
				orderActorToFactory(112979000, FormationIris002, "F002_Iris_126");
				break;
			case 6010:
				getLordActor()->addSubGroup(obtainActorFromFactory(110976010));
				orderActorToFactory(110979010, EnemyMetis, "Metis_127");
				{
				FormationIris001* pFormationActor = (FormationIris001*)obtainActorFromFactory(112876010);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 6110:
				getLordActor()->addSubGroup(obtainActorFromFactory(110976110));
				orderActorToFactory(110979110, EnemyMetis, "Metis_128");
				break;
			case 6210:
				getLordActor()->addSubGroup(obtainActorFromFactory(110976210));
				orderActorToFactory(110979210, EnemyMetis, "Metis_129");
				break;
			case 6310:
				getLordActor()->addSubGroup(obtainActorFromFactory(110976310));
				orderActorToFactory(110979310, EnemyMetis, "Metis_130");
				break;
			case 6410:
				getLordActor()->addSubGroup(obtainActorFromFactory(110976410));
				orderActorToFactory(110979410, EnemyMetis, "Metis_131");
				break;
			case 6500:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(112076500);
				getLordActor()->addSubGroup(pActor);
				pActor->_X = 9000000;
				pActor->_Z = 920000;
				pActor->_Y = -250000;
				}
				break;
			case 6510:
				getLordActor()->addSubGroup(obtainActorFromFactory(110976510));
				orderActorToFactory(110979510, EnemyMetis, "Metis_132");
				break;
			case 6610:
				getLordActor()->addSubGroup(obtainActorFromFactory(110976610));
				orderActorToFactory(110979610, EnemyMetis, "Metis_133");
				break;
			case 6710:
				getLordActor()->addSubGroup(obtainActorFromFactory(110976710));
				orderActorToFactory(110979710, EnemyMetis, "Metis_134");
				break;
			case 6810:
				getLordActor()->addSubGroup(obtainActorFromFactory(110976810));
				orderActorToFactory(110979810, EnemyMetis, "Metis_135");
				break;
			case 6910:
				getLordActor()->addSubGroup(obtainActorFromFactory(110976910));
				orderActorToFactory(110979910, EnemyMetis, "Metis_136");
				break;
			case 7000:
				orderActorToFactory(1103610000, VarietyTorus002, "VarietyTorus002_137");
				orderActorToFactory(1104610000, VarietyTorus003, "VarietyTorus003_138");
				{
				FormationIris002* pFormationActor = (FormationIris002*)obtainActorFromFactory(112977000);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 7010:
				getLordActor()->addSubGroup(obtainActorFromFactory(110977010));
				orderActorToFactory(1109710010, EnemyMetis, "Metis_139");
				orderActorToFactory(1128710010, FormationIris001, "F001_Iris_140");
				break;
			case 7110:
				getLordActor()->addSubGroup(obtainActorFromFactory(110977110));
				orderActorToFactory(1109710110, EnemyMetis, "Metis_141");
				break;
			case 7210:
				getLordActor()->addSubGroup(obtainActorFromFactory(110977210));
				orderActorToFactory(1109710210, EnemyMetis, "Metis_142");
				break;
			case 7310:
				getLordActor()->addSubGroup(obtainActorFromFactory(110977310));
				orderActorToFactory(1109710310, EnemyMetis, "Metis_143");
				break;
			case 7410:
				getLordActor()->addSubGroup(obtainActorFromFactory(110977410));
				orderActorToFactory(1109710410, EnemyMetis, "Metis_144");
				break;
			case 7510:
				getLordActor()->addSubGroup(obtainActorFromFactory(110977510));
				orderActorToFactory(1109710510, EnemyMetis, "Metis_145");
				break;
			case 7610:
				getLordActor()->addSubGroup(obtainActorFromFactory(110977610));
				orderActorToFactory(1109710610, EnemyMetis, "Metis_146");
				break;
			case 7710:
				getLordActor()->addSubGroup(obtainActorFromFactory(110977710));
				orderActorToFactory(1109710710, EnemyMetis, "Metis_147");
				break;
			case 7810:
				getLordActor()->addSubGroup(obtainActorFromFactory(110977810));
				orderActorToFactory(1109710810, EnemyMetis, "Metis_148");
				break;
			case 7900:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(111377900);
				getLordActor()->addSubGroup(pActor);
				pActor->_X = 9000000;
				pActor->_Z = -900000;
				pActor->_Y = -100000;
				}
				break;
			case 7910:
				getLordActor()->addSubGroup(obtainActorFromFactory(110977910));
				orderActorToFactory(1109710910, EnemyMetis, "Metis_149");
				break;
			case 8000:
				orderActorToFactory(1125711000, EnemyAstraea, "Astraea_150");
				orderActorToFactory(1129711000, FormationIris002, "F002_Iris_151");
				break;
			case 8002:
				{
				FormationJuno001* pFormationActor = (FormationJuno001*)obtainActorFromFactory(113878002);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 8010:
				getLordActor()->addSubGroup(obtainActorFromFactory(110978010));
				orderActorToFactory(1109711010, EnemyMetis, "Metis_152");
				{
				FormationIris001* pFormationActor = (FormationIris001*)obtainActorFromFactory(112878010);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 8110:
				getLordActor()->addSubGroup(obtainActorFromFactory(110978110));
				orderActorToFactory(1109711110, EnemyMetis, "Metis_153");
				break;
			case 8210:
				getLordActor()->addSubGroup(obtainActorFromFactory(110978210));
				orderActorToFactory(1109711210, EnemyMetis, "Metis_154");
				break;
			case 8310:
				getLordActor()->addSubGroup(obtainActorFromFactory(110978310));
				orderActorToFactory(1109711310, EnemyMetis, "Metis_155");
				break;
			case 8410:
				getLordActor()->addSubGroup(obtainActorFromFactory(110978410));
				orderActorToFactory(1109711410, EnemyMetis, "Metis_156");
				break;
			case 8500:
				orderActorToFactory(1120711500, EnemyAstraea, "Astraea_157");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113178500);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 8510:
				getLordActor()->addSubGroup(obtainActorFromFactory(110978510));
				orderActorToFactory(1109711510, EnemyMetis, "Metis_158");
				break;
			case 8530:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113278530);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 8560:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113378560);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 8590:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113478590);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 8610:
				getLordActor()->addSubGroup(obtainActorFromFactory(110978610));
				orderActorToFactory(1109711610, EnemyMetis, "Metis_159");
				break;
			case 8620:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113578620);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 8650:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113678650);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 8710:
				getLordActor()->addSubGroup(obtainActorFromFactory(110978710));
				orderActorToFactory(1109711710, EnemyMetis, "Metis_160");
				break;
			case 8810:
				getLordActor()->addSubGroup(obtainActorFromFactory(110978810));
				orderActorToFactory(1109711810, EnemyMetis, "Metis_161");
				break;
			case 8910:
				getLordActor()->addSubGroup(obtainActorFromFactory(110978910));
				orderActorToFactory(1109711910, EnemyMetis, "Metis_162");
				break;
			case 9000:
				{
				FormationIris002* pFormationActor = (FormationIris002*)obtainActorFromFactory(112979000);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 9010:
				getLordActor()->addSubGroup(obtainActorFromFactory(110979010));
				orderActorToFactory(1109712010, EnemyMetis, "Metis_163");
				orderActorToFactory(1128712010, FormationIris001, "F001_Iris_164");
				break;
			case 9110:
				getLordActor()->addSubGroup(obtainActorFromFactory(110979110));
				orderActorToFactory(1109712110, EnemyMetis, "Metis_165");
				break;
			case 9210:
				getLordActor()->addSubGroup(obtainActorFromFactory(110979210));
				orderActorToFactory(1109712210, EnemyMetis, "Metis_166");
				break;
			case 9310:
				getLordActor()->addSubGroup(obtainActorFromFactory(110979310));
				orderActorToFactory(1109712310, EnemyMetis, "Metis_167");
				break;
			case 9400:
				orderActorToFactory(1118712400, EnemyAstraea, "Astraea_168");
				break;
			case 9410:
				getLordActor()->addSubGroup(obtainActorFromFactory(110979410));
				orderActorToFactory(1109712410, EnemyMetis, "Metis_169");
				break;
			case 9500:
				orderActorWithDpToFactory(1131712500, EnemyCeres, "Ceres_170", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 9510:
				getLordActor()->addSubGroup(obtainActorFromFactory(110979510));
				orderActorToFactory(1109712510, EnemyMetis, "Metis_171");
				break;
			case 9530:
				orderActorWithDpToFactory(1132712530, EnemyCeres, "Ceres_172", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 9560:
				orderActorWithDpToFactory(1133712560, EnemyCeres, "Ceres_173", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 9590:
				orderActorWithDpToFactory(1134712590, EnemyCeres, "Ceres_174", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 9610:
				getLordActor()->addSubGroup(obtainActorFromFactory(110979610));
				orderActorToFactory(1109712610, EnemyMetis, "Metis_175");
				break;
			case 9620:
				orderActorWithDpToFactory(1135712620, EnemyCeres, "Ceres_176", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 9650:
				orderActorWithDpToFactory(1136712650, EnemyCeres, "Ceres_177", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 9710:
				getLordActor()->addSubGroup(obtainActorFromFactory(110979710));
				orderActorToFactory(1109712710, EnemyMetis, "Metis_178");
				break;
			case 9810:
				getLordActor()->addSubGroup(obtainActorFromFactory(110979810));
				orderActorToFactory(1109712810, EnemyMetis, "Metis_179");
				break;
			case 9900:
				orderActorToFactory(1113712900, EnemyAstraea, "Astraea_180");
				break;
			case 9910:
				getLordActor()->addSubGroup(obtainActorFromFactory(110979910));
				orderActorToFactory(1109712910, EnemyMetis, "Metis_181");
				break;
			case 10000:
				getLordActor()->addSubGroup(obtainActorFromFactory(1103610000));
				getLordActor()->addSubGroup(obtainActorFromFactory(1104610000));
				orderActorToFactory(1129713000, FormationIris002, "F002_Iris_182");
				break;
			case 10010:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109710010));
				orderActorToFactory(1109713010, EnemyMetis, "Metis_183");
				{
				FormationIris001* pFormationActor = (FormationIris001*)obtainActorFromFactory(1128710010);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 10110:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109710110));
				orderActorToFactory(1109713110, EnemyMetis, "Metis_184");
				break;
			case 10210:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109710210));
				orderActorToFactory(1109713210, EnemyMetis, "Metis_185");
				break;
			case 10310:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109710310));
				orderActorToFactory(1109713310, EnemyMetis, "Metis_186");
				break;
			case 10410:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109710410));
				orderActorToFactory(1109713410, EnemyMetis, "Metis_187");
				break;
			case 10510:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109710510));
				orderActorToFactory(1109713510, EnemyMetis, "Metis_188");
				break;
			case 10610:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109710610));
				orderActorToFactory(1109713610, EnemyMetis, "Metis_189");
				break;
			case 10710:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109710710));
				orderActorToFactory(1109713710, EnemyMetis, "Metis_190");
				break;
			case 10810:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109710810));
				orderActorToFactory(1109713810, EnemyMetis, "Metis_191");
				break;
			case 10910:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109710910));
				orderActorToFactory(1109713910, EnemyMetis, "Metis_192");
				break;
			case 11000:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1125711000);
				getLordActor()->addSubGroup(pActor);
				pActor->_X = 9000005;
				pActor->_Z = 920005;
				pActor->_Y = -750005;
				}
				{
				FormationIris002* pFormationActor = (FormationIris002*)obtainActorFromFactory(1129711000);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 11010:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109711010));
				orderActorToFactory(1109714010, EnemyMetis, "Metis_193");
				orderActorToFactory(1128714010, FormationIris001, "F001_Iris_194");
				break;
			case 11110:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109711110));
				orderActorToFactory(1109714110, EnemyMetis, "Metis_195");
				break;
			case 11210:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109711210));
				orderActorToFactory(1109714210, EnemyMetis, "Metis_196");
				break;
			case 11310:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109711310));
				orderActorToFactory(1109714310, EnemyMetis, "Metis_197");
				break;
			case 11410:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109711410));
				orderActorToFactory(1109714410, EnemyMetis, "Metis_198");
				break;
			case 11500:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1120711500);
				getLordActor()->addSubGroup(pActor);
				pActor->_X = 9000000;
				pActor->_Z = 920000;
				pActor->_Y = -250000;
				}
				break;
			case 11510:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109711510));
				orderActorToFactory(1109714510, EnemyMetis, "Metis_199");
				break;
			case 11610:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109711610));
				orderActorToFactory(1109714610, EnemyMetis, "Metis_200");
				break;
			case 11710:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109711710));
				orderActorToFactory(1109714710, EnemyMetis, "Metis_201");
				break;
			case 11810:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109711810));
				orderActorToFactory(1109714810, EnemyMetis, "Metis_202");
				break;
			case 11910:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109711910));
				orderActorToFactory(1109714910, EnemyMetis, "Metis_203");
				break;
			case 12000:
				orderActorToFactory(1129715000, FormationIris002, "F002_Iris_204");
				break;
			case 12010:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109712010));
				orderActorToFactory(1109715010, EnemyMetis, "Metis_205");
				{
				FormationIris001* pFormationActor = (FormationIris001*)obtainActorFromFactory(1128712010);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 12110:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109712110));
				orderActorToFactory(1109715110, EnemyMetis, "Metis_206");
				break;
			case 12210:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109712210));
				orderActorToFactory(1109715210, EnemyMetis, "Metis_207");
				break;
			case 12310:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109712310));
				orderActorToFactory(1109715310, EnemyMetis, "Metis_208");
				break;
			case 12400:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1118712400);
				getLordActor()->addSubGroup(pActor);
				pActor->_X = 9000005;
				pActor->_Z = -900005;
				pActor->_Y = -700005;
				}
				break;
			case 12410:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109712410));
				orderActorToFactory(1109715410, EnemyMetis, "Metis_209");
				break;
			case 12500:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1131712500);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 12510:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109712510));
				orderActorToFactory(1109715510, EnemyMetis, "Metis_210");
				break;
			case 12530:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1132712530);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 12560:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1133712560);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 12590:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1134712590);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 12610:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109712610));
				orderActorToFactory(1109715610, EnemyMetis, "Metis_211");
				break;
			case 12620:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1135712620);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 12650:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1136712650);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 12710:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109712710));
				orderActorToFactory(1109715710, EnemyMetis, "Metis_212");
				break;
			case 12810:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109712810));
				orderActorToFactory(1109715810, EnemyMetis, "Metis_213");
				break;
			case 12900:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1113712900);
				getLordActor()->addSubGroup(pActor);
				pActor->_X = 9000000;
				pActor->_Z = -900000;
				pActor->_Y = -100000;
				}
				break;
			case 12910:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109712910));
				orderActorToFactory(1109715910, EnemyMetis, "Metis_214");
				break;
			case 13000:
				orderActorToFactory(1125716000, EnemyAstraea, "Astraea_215");
				{
				FormationIris002* pFormationActor = (FormationIris002*)obtainActorFromFactory(1129713000);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 13002:
				orderActorToFactory(1138716002, FormationJuno001, "F002_Juno_216");
				break;
			case 13010:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109713010));
				orderActorToFactory(1109716010, EnemyMetis, "Metis_217");
				orderActorToFactory(1128716010, FormationIris001, "F001_Iris_218");
				break;
			case 13110:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109713110));
				orderActorToFactory(1109716110, EnemyMetis, "Metis_219");
				break;
			case 13210:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109713210));
				orderActorToFactory(1109716210, EnemyMetis, "Metis_220");
				break;
			case 13310:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109713310));
				orderActorToFactory(1109716310, EnemyMetis, "Metis_221");
				break;
			case 13410:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109713410));
				orderActorToFactory(1109716410, EnemyMetis, "Metis_222");
				break;
			case 13500:
				orderActorToFactory(1120716500, EnemyAstraea, "Astraea_223");
				orderActorWithDpToFactory(1131716500, EnemyCeres, "Ceres_224", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 13510:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109713510));
				orderActorToFactory(1109716510, EnemyMetis, "Metis_225");
				break;
			case 13530:
				orderActorWithDpToFactory(1132716530, EnemyCeres, "Ceres_226", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 13560:
				orderActorWithDpToFactory(1133716560, EnemyCeres, "Ceres_227", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 13590:
				orderActorWithDpToFactory(1134716590, EnemyCeres, "Ceres_228", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 13610:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109713610));
				orderActorToFactory(1109716610, EnemyMetis, "Metis_229");
				break;
			case 13620:
				orderActorWithDpToFactory(1135716620, EnemyCeres, "Ceres_230", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 13650:
				orderActorWithDpToFactory(1136716650, EnemyCeres, "Ceres_231", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 13710:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109713710));
				orderActorToFactory(1109716710, EnemyMetis, "Metis_232");
				break;
			case 13810:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109713810));
				orderActorToFactory(1109716810, EnemyMetis, "Metis_233");
				break;
			case 13910:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109713910));
				orderActorToFactory(1109716910, EnemyMetis, "Metis_234");
				break;
			case 14000:
				orderActorToFactory(1129717000, FormationIris002, "F002_Iris_235");
				break;
			case 14010:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109714010));
				orderActorToFactory(1109717010, EnemyMetis, "Metis_236");
				{
				FormationIris001* pFormationActor = (FormationIris001*)obtainActorFromFactory(1128714010);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 14110:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109714110));
				orderActorToFactory(1109717110, EnemyMetis, "Metis_237");
				break;
			case 14210:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109714210));
				orderActorToFactory(1109717210, EnemyMetis, "Metis_238");
				break;
			case 14310:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109714310));
				orderActorToFactory(1109717310, EnemyMetis, "Metis_239");
				break;
			case 14400:
				orderActorToFactory(1118717400, EnemyAstraea, "Astraea_240");
				break;
			case 14410:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109714410));
				orderActorToFactory(1109717410, EnemyMetis, "Metis_241");
				break;
			case 14510:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109714510));
				orderActorToFactory(1109717510, EnemyMetis, "Metis_242");
				break;
			case 14610:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109714610));
				orderActorToFactory(1109717610, EnemyMetis, "Metis_243");
				break;
			case 14710:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109714710));
				orderActorToFactory(1109717710, EnemyMetis, "Metis_244");
				break;
			case 14810:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109714810));
				orderActorToFactory(1109717810, EnemyMetis, "Metis_245");
				break;
			case 14900:
				orderActorToFactory(1113717900, EnemyAstraea, "Astraea_246");
				break;
			case 14910:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109714910));
				orderActorToFactory(1109717910, EnemyMetis, "Metis_247");
				break;
			case 15000:
				{
				FormationIris002* pFormationActor = (FormationIris002*)obtainActorFromFactory(1129715000);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 15010:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109715010));
				orderActorToFactory(1109718010, EnemyMetis, "Metis_248");
				orderActorToFactory(1128718010, FormationIris001, "F001_Iris_249");
				break;
			case 15110:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109715110));
				orderActorToFactory(1109718110, EnemyMetis, "Metis_250");
				break;
			case 15210:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109715210));
				orderActorToFactory(1109718210, EnemyMetis, "Metis_251");
				break;
			case 15310:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109715310));
				orderActorToFactory(1109718310, EnemyMetis, "Metis_252");
				break;
			case 15410:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109715410));
				orderActorToFactory(1109718410, EnemyMetis, "Metis_253");
				break;
			case 15510:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109715510));
				orderActorToFactory(1109718510, EnemyMetis, "Metis_254");
				break;
			case 15610:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109715610));
				orderActorToFactory(1109718610, EnemyMetis, "Metis_255");
				break;
			case 15710:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109715710));
				orderActorToFactory(1109718710, EnemyMetis, "Metis_256");
				break;
			case 15810:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109715810));
				orderActorToFactory(1109718810, EnemyMetis, "Metis_257");
				break;
			case 15910:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109715910));
				orderActorToFactory(1109718910, EnemyMetis, "Metis_258");
				break;
			case 16000:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1125716000);
				getLordActor()->addSubGroup(pActor);
				pActor->_X = 9000005;
				pActor->_Z = 920005;
				pActor->_Y = -750005;
				}
				orderActorToFactory(1129719000, FormationIris002, "F002_Iris_259");
				break;
			case 16002:
				{
				FormationJuno001* pFormationActor = (FormationJuno001*)obtainActorFromFactory(1138716002);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 16010:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109716010));
				orderActorToFactory(1109719010, EnemyMetis, "Metis_260");
				{
				FormationIris001* pFormationActor = (FormationIris001*)obtainActorFromFactory(1128716010);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 16110:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109716110));
				orderActorToFactory(1109719110, EnemyMetis, "Metis_261");
				break;
			case 16210:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109716210));
				orderActorToFactory(1109719210, EnemyMetis, "Metis_262");
				break;
			case 16310:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109716310));
				orderActorToFactory(1109719310, EnemyMetis, "Metis_263");
				break;
			case 16410:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109716410));
				orderActorToFactory(1109719410, EnemyMetis, "Metis_264");
				break;
			case 16500:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1120716500);
				getLordActor()->addSubGroup(pActor);
				pActor->_X = 9000000;
				pActor->_Z = 920000;
				pActor->_Y = -250000;
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1131716500);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 16510:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109716510));
				orderActorToFactory(1109719510, EnemyMetis, "Metis_265");
				break;
			case 16530:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1132716530);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 16560:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1133716560);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 16590:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1134716590);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 16610:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109716610));
				orderActorToFactory(1109719610, EnemyMetis, "Metis_266");
				break;
			case 16620:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1135716620);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 16650:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1136716650);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 16710:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109716710));
				orderActorToFactory(1109719710, EnemyMetis, "Metis_267");
				break;
			case 16810:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109716810));
				orderActorToFactory(1109719810, EnemyMetis, "Metis_268");
				break;
			case 16910:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109716910));
				orderActorToFactory(1109719910, EnemyMetis, "Metis_269");
				break;
			case 17000:
				orderActorToFactory(1106620000, VarietyTorus004, "VarietyTorus004_270");
				{
				FormationIris002* pFormationActor = (FormationIris002*)obtainActorFromFactory(1129717000);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 17010:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109717010));
				orderActorToFactory(1109720010, EnemyMetis, "Metis_271");
				break;
			case 17110:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109717110));
				orderActorToFactory(1109720110, EnemyMetis, "Metis_272");
				break;
			case 17210:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109717210));
				orderActorToFactory(1109720210, EnemyMetis, "Metis_273");
				break;
			case 17310:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109717310));
				orderActorToFactory(1109720310, EnemyMetis, "Metis_274");
				break;
			case 17400:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1118717400);
				getLordActor()->addSubGroup(pActor);
				pActor->_X = 9000005;
				pActor->_Z = -900005;
				pActor->_Y = -700005;
				}
				break;
			case 17410:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109717410));
				orderActorToFactory(1109720410, EnemyMetis, "Metis_275");
				break;
			case 17510:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109717510));
				orderActorToFactory(1109720510, EnemyMetis, "Metis_276");
				break;
			case 17610:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109717610));
				orderActorToFactory(1109720610, EnemyMetis, "Metis_277");
				break;
			case 17710:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109717710));
				orderActorToFactory(1109720710, EnemyMetis, "Metis_278");
				break;
			case 17810:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109717810));
				orderActorToFactory(1109720810, EnemyMetis, "Metis_279");
				break;
			case 17900:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1113717900);
				getLordActor()->addSubGroup(pActor);
				pActor->_X = 9000000;
				pActor->_Z = -900000;
				pActor->_Y = -100000;
				}
				break;
			case 17910:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109717910));
				orderActorToFactory(1109720910, EnemyMetis, "Metis_280");
				break;
			case 18010:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109718010));
				orderActorToFactory(1109721010, EnemyMetis, "Metis_281");
				{
				FormationIris001* pFormationActor = (FormationIris001*)obtainActorFromFactory(1128718010);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 18110:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109718110));
				orderActorToFactory(1109721110, EnemyMetis, "Metis_282");
				break;
			case 18210:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109718210));
				orderActorToFactory(1109721210, EnemyMetis, "Metis_283");
				break;
			case 18310:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109718310));
				orderActorToFactory(1109721310, EnemyMetis, "Metis_284");
				break;
			case 18410:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109718410));
				orderActorToFactory(1109721410, EnemyMetis, "Metis_285");
				break;
			case 18510:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109718510));
				orderActorToFactory(1109721510, EnemyMetis, "Metis_286");
				break;
			case 18610:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109718610));
				orderActorToFactory(1109721610, EnemyMetis, "Metis_287");
				break;
			case 18710:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109718710));
				orderActorToFactory(1109721710, EnemyMetis, "Metis_288");
				break;
			case 18810:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109718810));
				orderActorToFactory(1109721810, EnemyMetis, "Metis_289");
				break;
			case 18910:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109718910));
				orderActorToFactory(1109721910, EnemyMetis, "Metis_290");
				break;
			case 19000:
				{
				FormationIris002* pFormationActor = (FormationIris002*)obtainActorFromFactory(1129719000);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 19010:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109719010));
				orderActorToFactory(1109722010, EnemyMetis, "Metis_291");
				break;
			case 19110:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109719110));
				orderActorToFactory(1109722110, EnemyMetis, "Metis_292");
				break;
			case 19210:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109719210));
				orderActorToFactory(1109722210, EnemyMetis, "Metis_293");
				break;
			case 19310:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109719310));
				orderActorToFactory(1109722310, EnemyMetis, "Metis_294");
				break;
			case 19410:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109719410));
				orderActorToFactory(1109722410, EnemyMetis, "Metis_295");
				break;
			case 19510:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109719510));
				orderActorToFactory(1109722510, EnemyMetis, "Metis_296");
				break;
			case 19610:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109719610));
				orderActorToFactory(1109722610, EnemyMetis, "Metis_297");
				break;
			case 19710:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109719710));
				orderActorToFactory(1109722710, EnemyMetis, "Metis_298");
				break;
			case 19810:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109719810));
				orderActorToFactory(1109722810, EnemyMetis, "Metis_299");
				break;
			case 19910:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109719910));
				orderActorToFactory(1109722910, EnemyMetis, "Metis_300");
				break;
			case 20000:
				getLordActor()->addSubGroup(obtainActorFromFactory(1106620000));
				break;
			case 20010:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109720010));
				orderActorToFactory(1109723010, EnemyMetis, "Metis_301");
				break;
			case 20110:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109720110));
				orderActorToFactory(1109723110, EnemyMetis, "Metis_302");
				break;
			case 20210:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109720210));
				orderActorToFactory(1109723210, EnemyMetis, "Metis_303");
				break;
			case 20310:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109720310));
				orderActorToFactory(1109723310, EnemyMetis, "Metis_304");
				break;
			case 20410:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109720410));
				orderActorToFactory(1109723410, EnemyMetis, "Metis_305");
				break;
			case 20510:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109720510));
				orderActorToFactory(1109723510, EnemyMetis, "Metis_306");
				break;
			case 20610:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109720610));
				orderActorToFactory(1109723610, EnemyMetis, "Metis_307");
				break;
			case 20710:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109720710));
				orderActorToFactory(1109723710, EnemyMetis, "Metis_308");
				break;
			case 20810:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109720810));
				orderActorToFactory(1109723810, EnemyMetis, "Metis_309");
				break;
			case 20910:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109720910));
				orderActorToFactory(1109723910, EnemyMetis, "Metis_310");
				break;
			case 21010:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109721010));
				orderActorToFactory(1109724010, EnemyMetis, "Metis_311");
				break;
			case 21110:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109721110));
				orderActorToFactory(1109724110, EnemyMetis, "Metis_312");
				break;
			case 21210:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109721210));
				orderActorToFactory(1109724210, EnemyMetis, "Metis_313");
				break;
			case 21310:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109721310));
				orderActorToFactory(1109724310, EnemyMetis, "Metis_314");
				break;
			case 21410:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109721410));
				orderActorToFactory(1109724410, EnemyMetis, "Metis_315");
				break;
			case 21510:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109721510));
				orderActorToFactory(1109724510, EnemyMetis, "Metis_316");
				break;
			case 21610:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109721610));
				orderActorToFactory(1109724610, EnemyMetis, "Metis_317");
				break;
			case 21710:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109721710));
				orderActorToFactory(1109724710, EnemyMetis, "Metis_318");
				break;
			case 21810:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109721810));
				orderActorToFactory(1109724810, EnemyMetis, "Metis_319");
				break;
			case 21910:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109721910));
				orderActorToFactory(1109724910, EnemyMetis, "Metis_320");
				break;
			case 22010:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109722010));
				orderActorToFactory(1109725010, EnemyMetis, "Metis_321");
				break;
			case 22110:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109722110));
				orderActorToFactory(1109725110, EnemyMetis, "Metis_322");
				break;
			case 22210:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109722210));
				orderActorToFactory(1109725210, EnemyMetis, "Metis_323");
				break;
			case 22310:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109722310));
				orderActorToFactory(1109725310, EnemyMetis, "Metis_324");
				break;
			case 22410:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109722410));
				orderActorToFactory(1109725410, EnemyMetis, "Metis_325");
				break;
			case 22510:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109722510));
				orderActorToFactory(1109725510, EnemyMetis, "Metis_326");
				break;
			case 22610:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109722610));
				orderActorToFactory(1109725610, EnemyMetis, "Metis_327");
				break;
			case 22710:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109722710));
				orderActorToFactory(1109725710, EnemyMetis, "Metis_328");
				break;
			case 22810:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109722810));
				orderActorToFactory(1109725810, EnemyMetis, "Metis_329");
				break;
			case 22910:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109722910));
				orderActorToFactory(1109725910, EnemyMetis, "Metis_330");
				break;
			case 23010:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109723010));
				orderActorToFactory(1109726010, EnemyMetis, "Metis_331");
				break;
			case 23110:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109723110));
				orderActorToFactory(1109726110, EnemyMetis, "Metis_332");
				break;
			case 23210:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109723210));
				orderActorToFactory(1109726210, EnemyMetis, "Metis_333");
				break;
			case 23310:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109723310));
				orderActorToFactory(1109726310, EnemyMetis, "Metis_334");
				break;
			case 23410:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109723410));
				orderActorToFactory(1109726410, EnemyMetis, "Metis_335");
				break;
			case 23510:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109723510));
				orderActorToFactory(1109726510, EnemyMetis, "Metis_336");
				break;
			case 23610:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109723610));
				orderActorToFactory(1109726610, EnemyMetis, "Metis_337");
				break;
			case 23710:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109723710));
				orderActorToFactory(1109726710, EnemyMetis, "Metis_338");
				break;
			case 23810:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109723810));
				orderActorToFactory(1109726810, EnemyMetis, "Metis_339");
				break;
			case 23910:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109723910));
				orderActorToFactory(1109726910, EnemyMetis, "Metis_340");
				break;
			case 24010:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109724010));
				orderActorToFactory(1109727010, EnemyMetis, "Metis_341");
				break;
			case 24110:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109724110));
				orderActorToFactory(1109727110, EnemyMetis, "Metis_342");
				break;
			case 24210:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109724210));
				orderActorToFactory(1109727210, EnemyMetis, "Metis_343");
				break;
			case 24310:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109724310));
				orderActorToFactory(1109727310, EnemyMetis, "Metis_344");
				break;
			case 24410:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109724410));
				orderActorToFactory(1109727410, EnemyMetis, "Metis_345");
				break;
			case 24510:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109724510));
				orderActorToFactory(1109727510, EnemyMetis, "Metis_346");
				break;
			case 24610:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109724610));
				orderActorToFactory(1109727610, EnemyMetis, "Metis_347");
				break;
			case 24710:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109724710));
				orderActorToFactory(1109727710, EnemyMetis, "Metis_348");
				break;
			case 24810:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109724810));
				orderActorToFactory(1109727810, EnemyMetis, "Metis_349");
				break;
			case 24910:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109724910));
				orderActorToFactory(1109727910, EnemyMetis, "Metis_350");
				break;
			case 25010:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109725010));
				orderActorToFactory(1109728010, EnemyMetis, "Metis_351");
				break;
			case 25110:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109725110));
				orderActorToFactory(1109728110, EnemyMetis, "Metis_352");
				break;
			case 25210:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109725210));
				orderActorToFactory(1109728210, EnemyMetis, "Metis_353");
				break;
			case 25310:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109725310));
				orderActorToFactory(1109728310, EnemyMetis, "Metis_354");
				break;
			case 25410:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109725410));
				orderActorToFactory(1109728410, EnemyMetis, "Metis_355");
				break;
			case 25510:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109725510));
				orderActorToFactory(1109728510, EnemyMetis, "Metis_356");
				break;
			case 25610:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109725610));
				orderActorToFactory(1109728610, EnemyMetis, "Metis_357");
				break;
			case 25710:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109725710));
				orderActorToFactory(1109728710, EnemyMetis, "Metis_358");
				break;
			case 25810:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109725810));
				orderActorToFactory(1109728810, EnemyMetis, "Metis_359");
				break;
			case 25910:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109725910));
				orderActorToFactory(1109728910, EnemyMetis, "Metis_360");
				break;
			case 26010:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109726010));
				orderActorToFactory(1109729010, EnemyMetis, "Metis_361");
				break;
			case 26110:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109726110));
				orderActorToFactory(1109729110, EnemyMetis, "Metis_362");
				break;
			case 26210:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109726210));
				orderActorToFactory(1109729210, EnemyMetis, "Metis_363");
				break;
			case 26310:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109726310));
				orderActorToFactory(1109729310, EnemyMetis, "Metis_364");
				break;
			case 26410:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109726410));
				orderActorToFactory(1109729410, EnemyMetis, "Metis_365");
				break;
			case 26510:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109726510));
				orderActorToFactory(1109729510, EnemyMetis, "Metis_366");
				break;
			case 26610:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109726610));
				orderActorToFactory(1109729610, EnemyMetis, "Metis_367");
				break;
			case 26710:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109726710));
				orderActorToFactory(1109729710, EnemyMetis, "Metis_368");
				break;
			case 26810:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109726810));
				orderActorToFactory(1109729810, EnemyMetis, "Metis_369");
				break;
			case 26910:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109726910));
				orderActorToFactory(1109729910, EnemyMetis, "Metis_370");
				break;
			case 27010:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109727010));
				orderActorToFactory(1109730010, EnemyMetis, "Metis_371");
				break;
			case 27110:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109727110));
				orderActorToFactory(1109730110, EnemyMetis, "Metis_372");
				break;
			case 27210:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109727210));
				orderActorToFactory(1109730210, EnemyMetis, "Metis_373");
				break;
			case 27310:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109727310));
				orderActorToFactory(1109730310, EnemyMetis, "Metis_374");
				break;
			case 27410:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109727410));
				orderActorToFactory(1109730410, EnemyMetis, "Metis_375");
				break;
			case 27510:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109727510));
				orderActorToFactory(1109730510, EnemyMetis, "Metis_376");
				break;
			case 27610:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109727610));
				orderActorToFactory(1109730610, EnemyMetis, "Metis_377");
				break;
			case 27710:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109727710));
				orderActorToFactory(1109730710, EnemyMetis, "Metis_378");
				break;
			case 27810:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109727810));
				orderActorToFactory(1109730810, EnemyMetis, "Metis_379");
				break;
			case 27910:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109727910));
				orderActorToFactory(1109730910, EnemyMetis, "Metis_380");
				break;
			case 28010:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109728010));
				orderActorToFactory(1109731010, EnemyMetis, "Metis_381");
				break;
			case 28110:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109728110));
				orderActorToFactory(1109731110, EnemyMetis, "Metis_382");
				break;
			case 28210:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109728210));
				orderActorToFactory(1109731210, EnemyMetis, "Metis_383");
				break;
			case 28310:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109728310));
				orderActorToFactory(1109731310, EnemyMetis, "Metis_384");
				break;
			case 28410:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109728410));
				orderActorToFactory(1109731410, EnemyMetis, "Metis_385");
				break;
			case 28510:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109728510));
				orderActorToFactory(1109731510, EnemyMetis, "Metis_386");
				break;
			case 28610:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109728610));
				orderActorToFactory(1109731610, EnemyMetis, "Metis_387");
				break;
			case 28710:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109728710));
				orderActorToFactory(1109731710, EnemyMetis, "Metis_388");
				break;
			case 28810:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109728810));
				orderActorToFactory(1109731810, EnemyMetis, "Metis_389");
				break;
			case 28910:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109728910));
				orderActorToFactory(1109731910, EnemyMetis, "Metis_390");
				break;
			case 29010:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109729010));
				break;
			case 29110:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109729110));
				break;
			case 29210:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109729210));
				break;
			case 29310:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109729310));
				break;
			case 29410:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109729410));
				break;
			case 29510:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109729510));
				break;
			case 29610:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109729610));
				break;
			case 29710:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109729710));
				break;
			case 29810:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109729810));
				break;
			case 29910:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109729910));
				break;
			case 30010:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109730010));
				break;
			case 30110:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109730110));
				break;
			case 30210:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109730210));
				break;
			case 30310:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109730310));
				break;
			case 30410:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109730410));
				break;
			case 30510:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109730510));
				break;
			case 30610:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109730610));
				break;
			case 30710:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109730710));
				break;
			case 30810:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109730810));
				break;
			case 30910:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109730910));
				break;
			case 31010:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109731010));
				break;
			case 31110:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109731110));
				break;
			case 31210:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109731210));
				break;
			case 31310:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109731310));
				break;
			case 31410:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109731410));
				break;
			case 31510:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109731510));
				break;
			case 31610:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109731610));
				break;
			case 31710:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109731710));
				break;
			case 31810:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109731810));
				break;
			case 31910:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109731910));
				break;
			default :
				break;
		}
		_iCnt_Event = (_iCnt_Event < 414-1 ? _iCnt_Event+1 : _iCnt_Event);
	}
    // gen02 end

    if (getBehaveingFrame() == 2) {

        _TRACE_("Stage01MainScene::processBehavior はいはいDemoさんありがとう、私も起動しましたよ");
        // 共通シーンを配下に移動
        addSubLast(GameGlobal::_pSceneCommon->extract());

    }

}

void Stage01MainScene::processFinal() {
    //	if (getBehaveingFrame() == 1) {
    //		_TRACE_("Stage01MainScene::processFinally 私はいきなり停止します。GameMainSceneが解除してくれるはずー");
    //		this->inactivateTree(); //GameMainSceneが解除してくれる
    //	}
}

Stage01MainScene::~Stage01MainScene() {
    //NEWからprocessBehaviorまでの間に強制終了された場合、
    //_pDispatcherはどのツリーにも所属していない。
    if (_pDispatcher->getParent() == NULL) {
        _TRACE_("_pDispatcherが未所属のため独自delete");
        DELETE_IMPOSSIBLE_NULL(_pDispatcher);
    }
}
