#include "StageDebugPartController.h"

#include "jp/ggaf/core/actor/SceneMediator.h"
#include "jp/ggaf/dx/sound/BgmConductor.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/actor/VVEnemysHeader.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "../StageDebug.h"
#include "part/StageDebugPart01.h"
#include "part/StageDebugPart02.h"
#include "part/StageDebugPart03.h"
#include "part/StageDebugPartClimax.h"
#include "part/StageDebugPartWall.h"



using namespace GgafLib;
using namespace VioletVreath;

enum {
    PHASE_INIT   ,
    PHASE_FAINAL ,
    PHASE_BANPEI,
};

StageDebugPartController::StageDebugPartController(const char* prm_name) : StagePartController(prm_name) {
    _class_name = "StageDebugPartController";

    // 以下の gen01 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen01 start
	frame f[] = {1,5,25,45,65,85,100,105,125,145,165,185,200,205,225,245,265,285,300,305,325,345,365,385,400,405,425,445,465,485,500,505,525,545,565,585,600,605,625,645,665,685,700,705,725,745,765,785,800,805,825,845,865,885,900,905,925,945,965,985,1000,1005,1025,1045,1065,1085,1100,1105,1125,1145,1165,1185,1200,1205,1225,1245,1265,1285,1300,1305,1325,1345,1365,1385,1400,1405,1425,1445,1465,1485,1500,1505,1525,1545,1565,1585,1600,1605,1625,1645,1665,1685,1700,1705,1725,1745,1765,1785,1800,1805,1825,1845,1865,1885,1900,1905,1925,1945,1965,1985,2000,2005,2025,2045,2065,2085,2105,2125,2145,2165,2185,2205,2225,2245,2265,2285,2305,2325,2345,2365,2385,2405,2425,2445,2465,2485,2500,2505,2525,2545,2565,2585,2605,2625,2645,2665,2685,2705,2725,2745,2765,2785,2805,2825,2845,2865,2885,2905,2925,2945,2965,2985,3005,3025,3045,3065,3085,3105,3125,3145,3165,3185,3205,3225,3245,3265,3285,3305,3325,3345,3365,3385,3405,3425,3445,3465,3485,3505,3525,3545,3565,3585,3605,3625,3645,3665,3685,3705,3725,3745,3765,3785,3805,3825,3845,3865,3885,3900,3905,3925,3945,3965,3985,4005,4025,4045,4065,4085,4105,4125,4145,4165,4185,4205,4225,4245,4265,4285,4305,4325,4345,4365,4385,4405,4425,4445,4465,4485,4500,4505,4525,4545,4565,4585,4605,4625,4645,4665,4685,4705,4725,4745,4765,4785,4805,4825,4845,4865,4885,4905,4925,4945,4965,4985,5005,5025,5045,5065,5085,5100,5105,5125,5145,5165,5185,5205,5225,5245,5265,5285,5305,5325,5345,5365,5385,5405,5425,5445,5465,5485,5505,5525,5545,5565,5585,5605,5625,5645,5665,5685,5705,5725,5745,5765,5785,5805,5825,5845,5865,5885,5900,5905,5925,5945,5965,5985,6000,6005,6025,6045,6065,6085,6105,6125,6145,6165,6185,6205,6225,6245,6265,6285,6305,6325,6345,6365,6385,6405,6425,6445,6465,6485,6500,6505,6525,6545,6565,6585,6605,6625,6645,6665,6685,6705,6725,6745,6765,6785,6805,6825,6845,6865,6885,6905,6925,6945,6965,6985,7005,7025,7045,7065,7085,7105,7125,7145,7165,7185,7200,7205,7225,7245,7265,7285,7305,7325,7345,7365,7385,7405,7425,7445,7465,7485,7505,7525,7545,7565,7585,7605,7625,7645,7665,7685,7705,7725,7745,7765,7785,7805,7825,7845,7865,7885,7900,7905,7925,7945,7965,7985,8005,8025,8045,8065,8085,8100,8105,8125,8145,8165,8185,8205,8225,8245,8265,8285,8305,8325,8345,8365,8385,8405,8425,8445,8465,8485,8500,8505,8525,8545,8565,8585,8605,8625,8645,8665,8685,8705,8725,8745,8765,8785,8805,8825,8845,8865,8885,8905,8925,8945,8965,8985,9005,9025,9045,9065,9085,9105,9125,9145,9165,9185,9205,9225,9245,9265,9285,9305,9325,9345,9365,9385,9405,9425,9445,9465,9485,9505,9525,9545,9565,9585,9605,9625,9645,9665,9685,9705,9725,9745,9765,9785,9805,9825,9845,9865,9885,9900,9905,9925,9945,9965,9985,10005,10025,10045,10065,10085,10105,10125,10145,10165,10185,10205,10225,10245,10265,10285,10305,10325,10345,10365,10385,10405,10425,10445,10465,10485,10500,10505,10525,10545,10565,10585,10605,10625,10645,10665,10685,10705,10725,10745,10765,10785,10805,10825,10845,10865,10885,10905,10925,10945,10965,10985,11005,11025,11045,11065,11085,11105,11125,11145,11165,11185,11205,11225,11245,11265,11285,11305,11325,11345,11365,11385,11405,11425,11445,11465,11485,11505,11525,11545,11565,11585,11605,11625,11645,11665,11685,11705,11725,11745,11765,11785,11805,11825,11845,11865,11885,11900,11905,11925,11945,11965,11985,12005,12025,12045,12065,12085,12105,12125,12145,12165,12185,12205,12225,12245,12265,12285,12305,12325,12345,12365,12385,12405,12425,12445,12465,12485,12500,12505,12525,12545,12565,12585,12605,12625,12645,12665,12685,12705,12725,12745,12765,12785,12805,12825,12845,12865,12885,12905,12925,12945,12965,12985,13005,13025,13045,13065,13085,13105,13125,13145,13165,13185,13205,13225,13245,13265,13285,13305,13325,13345,13365,13385,13405,13425,13445,13465,13485,13505,13525,13545,13565,13585,13605,13625,13645,13665,13685,13705,13725,13745,13765,13785,13805,13825,13845,13865,13885,13900,13905,13925,13945,13965,13985,14005,14025,14045,14065,14085,14105,14125,14145,14165,14185,14205,14225,14245,14265,14285,14305,14325,14345,14365,14385,14405,14425,14445,14465,14485,14500,14505,14525,14545,14565,14585,14605,14625,14645,14665,14685,14705,14725,14745,14765,14785,14805,14825,14845,14865,14885,14905,14925,14945,14965,14985,15005,15025,15045,15065,15085,15105,15125,15145,15165,15185,15205,15225,15245,15265,15285,15305,15325,15345,15365,15385,15405,15425,15445,15465,15485,15505,15525,15545,15565,15585,15605,15625,15645,15665,15685,15705,15725,15745,15765,15785,15805,15825,15845,15865,15885,15900,15905,15925,15945,15965,15985,16005,16025,16045,16065,16085,16105,16125,16145,16165,16185,16205,16225,16245,16265,16285,16305,16325,16345,16365,16385,16405,16425,16445,16465,16485,16500,16505,16525,16545,16565,16585,16605,16625,16645,16665,16685,16705,16725,16745,16765,16785,16805,16825,16845,16865,16885,16905,16925,16945,16965,16985,17005,17025,17045,17065,17085,17105,17125,17145,17165,17185,17205,17225,17245,17265,17285,17305,17325,17345,17365,17385,17405,17425,17445,17465,17485,17505,17525,17545,17565,17585,17605,17625,17645,17665,17685,17705,17725,17745,17765,17785,17805,17825,17845,17865,17885,17900,17905,17925,17945,17965,17985,18005,18025,18045,18065,18085,18105,18125,18145,18165,18185,18205,18225,18245,18265,18285,18305,18325,18345,18365,18385,18405,18425,18445,18465,18485,18500,18505,18525,18545,18565,18585,18605,18625,18645,18665,18685,18705,18725,18745,18765,18785,18805,18825,18845,18865,18885,18905,18925,18945,18965,18985,19005,19025,19045,19065,19085,19105,19125,19145,19165,19185,19205,19225,19245,19265,19285,19305,19325,19345,19365,19385,19400,19405,19425,19445,19465,19485,19505,19525,19545,19565,19585,19605,19625,19645,19665,19685,19700,19705,19725,19745,19765,19785,19805,19825,19845,19865,19885,19900,19905,19925,19945,19965,19985,20000,20005,20025,20045,20065,20085,20105,20125,20145,20165,20185,20205,20225,20245,20265,20285,20300,20305,20325,20345,20365,20385,20405,20425,20445,20465,20485,20500,20505,20525,20545,20565,20585,20605,20625,20645,20665,20685,20705,20725,20745,20765,20785,20805,20825,20845,20865,20885,20905,20925,20945,20965,20985,21005,21025,21045,21065,21085,21100,21105,21125,21145,21165,21185,21205,21225,21245,21265,21285,21305,21325,21345,21365,21385,21405,21425,21445,21465,21485,21505,21525,21545,21565,21585,21605,21625,21645,21665,21685,21705,21725,21745,21765,21785,21805,21825,21845,21865,21885,21900,21905,21925,21945,21965,21985,22000,22500,23900,24500,25900,26500,27900,28500,29900,30500,31900,32500,33900,34500,35900,36500,37900,38500,39700,39900,40300,40500,41900,42500,43900,44500,45900,46500,47900,48500,49900,50500,51900,52500,53900,54500,55900,56500,57900,58500};
	_paFrame_NextEvent = new frame[1190];
	memcpy(_paFrame_NextEvent, f, sizeof(f));
	_event_num = 1190;
	requestActor(10000004, EnemyOebiusController002, "EnemyOebiusController002-10000004");
	requestActor(10000005, EnemyOebiusController002, "EnemyOebiusController002-10000005");
	requestActor(10000020, EnemyErelmanController002, "EnemyErelmanController002-10000020");
	requestActor(10000021, EnemyErelmanController001, "EnemyErelmanController001-10000021");
	requestActor(10000022, EnemyErmione, "EnemyErmione-10000022");
	requestActor(10000025, EnemyEtis, "EnemyEtis-10000025");
	requestActor(10000026, EnemyEtis, "EnemyEtis-10000026");
	requestActor(10000027, EnemyEtis, "EnemyEtis-10000027");
	requestActor(10000028, EnemyEtis, "EnemyEtis-10000028");
	requestActor(10000029, EnemyEtis, "EnemyEtis-10000029");
	requestActor(10000030, EnemyEtis, "EnemyEtis-10000030");
	requestActor(10000031, EnemyEtis, "EnemyEtis-10000031");
	requestActor(10000032, EnemyEtis, "EnemyEtis-10000032");
	requestActor(10000033, EnemyEtis, "EnemyEtis-10000033");
	requestActor(10000034, EnemyEtis, "EnemyEtis-10000034");
	requestActor(10000035, EnemyEtis, "EnemyEtis-10000035");
	requestActor(10000036, EnemyEtis, "EnemyEtis-10000036");
	requestActor(10000037, EnemyEtis, "EnemyEtis-10000037");
	requestActor(10000038, EnemyEtis, "EnemyEtis-10000038");
	requestActor(10000039, EnemyEtis, "EnemyEtis-10000039");
	requestActor(10000040, EnemyEtis, "EnemyEtis-10000040");
	requestActor(10000041, EnemyEtis, "EnemyEtis-10000041");
	requestActor(10000042, EnemyEtis, "EnemyEtis-10000042");
	requestActor(10000043, EnemyEtis, "EnemyEtis-10000043");
	requestActor(10000044, EnemyEtis, "EnemyEtis-10000044");
	requestActor(10000045, EnemyEtis, "EnemyEtis-10000045");
	requestActor(10000046, EnemyEtis, "EnemyEtis-10000046");
	requestActor(10000047, EnemyEtis, "EnemyEtis-10000047");
	requestActor(10000048, EnemyEtis, "EnemyEtis-10000048");
	requestActor(10000049, EnemyEtis, "EnemyEtis-10000049");
	requestActor(10000050, EnemyEtis, "EnemyEtis-10000050");
	requestActor(10000051, EnemyEtis, "EnemyEtis-10000051");
	requestActor(10000052, EnemyEtis, "EnemyEtis-10000052");
	requestActor(10000053, EnemyEtis, "EnemyEtis-10000053");
	requestActor(10000054, EnemyEtis, "EnemyEtis-10000054");
	requestActor(10001125, EnemyDrastea, "EnemyDrastea-10001125");
	requestActor(10001155, VarietyRatislavia002, "VarietyRatislavia002-10001155");
    // gen01 end
}

void StageDebugPartController::initialize() {
    getPhase()->reset(PHASE_INIT);
}

void StageDebugPartController::processBehavior() {
    // 以下の gen02 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen02 start
	if (getBehaveingFrame() == _paFrame_NextEvent[_cnt_event]) {
		switch (getBehaveingFrame()) {
			case 1: {
				break;
			}
			case 5: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000025);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000055, EnemyEtis, "EnemyEtis-10000055");
				break;
			}
			case 25: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000026);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000056, EnemyEtis, "EnemyEtis-10000056");
				break;
			}
			case 45: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000027);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000057, EnemyEtis, "EnemyEtis-10000057");
				break;
			}
			case 65: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000028);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000058, EnemyEtis, "EnemyEtis-10000058");
				break;
			}
			case 85: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000029);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000059, EnemyEtis, "EnemyEtis-10000059");
				break;
			}
			case 100: {
				requestScene(10000000, StageDebugPart01, "StageDebugPart01-10000000");
				EnemyOebiusController002* p2 = (EnemyOebiusController002*)receiveActor(10000004);
				bringSceneMediator()->appendGroupChild(p2);
				p2->setPosition(PX_C(800), 0, 0);
				requestActor(10000013, EnemyOebiusController001, "EnemyOebiusController001-10000013");
				VarietyRatislavia002* pRatislavia = (VarietyRatislavia002*)receiveActor(10001155);
				bringSceneMediator()->appendGroupChild(pRatislavia);
				break;
			}
			case 105: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000030);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000060, EnemyEtis, "EnemyEtis-10000060");
				break;
			}
			case 125: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000031);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000061, EnemyEtis, "EnemyEtis-10000061");
				break;
			}
			case 145: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000032);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000062, EnemyEtis, "EnemyEtis-10000062");
				break;
			}
			case 165: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000033);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000063, EnemyEtis, "EnemyEtis-10000063");
				break;
			}
			case 185: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000034);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000064, EnemyEtis, "EnemyEtis-10000064");
				break;
			}
			case 200: {
				requestActor(10000006, EnemyOebiusController002, "EnemyOebiusController002-10000006");
				break;
			}
			case 205: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000035);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000065, EnemyEtis, "EnemyEtis-10000065");
				break;
			}
			case 225: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000036);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000066, EnemyEtis, "EnemyEtis-10000066");
				break;
			}
			case 245: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000037);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000067, EnemyEtis, "EnemyEtis-10000067");
				break;
			}
			case 265: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000038);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000068, EnemyEtis, "EnemyEtis-10000068");
				break;
			}
			case 285: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000039);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000069, EnemyEtis, "EnemyEtis-10000069");
				break;
			}
			case 300: {
				requestActor(10000014, EnemyOebiusController001, "EnemyOebiusController001-10000014");
				EnemyErmione* pE = (EnemyErmione*)receiveActor(10000022);
				bringSceneMediator()->appendGroupChild(pE);
				pE->_x = RND(1000000,4000000);
				pE->_y = RND(-6000000,6000000);
				pE->_z = RND(-6000000,6000000);
				break;
			}
			case 305: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000040);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000070, EnemyEtis, "EnemyEtis-10000070");
				break;
			}
			case 325: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000041);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000071, EnemyEtis, "EnemyEtis-10000071");
				break;
			}
			case 345: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000042);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000072, EnemyEtis, "EnemyEtis-10000072");
				break;
			}
			case 365: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000043);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000073, EnemyEtis, "EnemyEtis-10000073");
				break;
			}
			case 385: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000044);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000074, EnemyEtis, "EnemyEtis-10000074");
				break;
			}
			case 400: {
				requestActor(10000007, EnemyOebiusController002, "EnemyOebiusController002-10000007");
				EnemyErelmanController002* pE1 = (EnemyErelmanController002*)receiveActor(10000020);
				bringSceneMediator()->appendGroupChild(pE1);
				pE1->setPosition(PX_C(3400), PX_C(0), PX_C(3400));
				break;
			}
			case 405: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000045);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000075, EnemyEtis, "EnemyEtis-10000075");
				break;
			}
			case 425: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000046);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000076, EnemyEtis, "EnemyEtis-10000076");
				break;
			}
			case 445: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000047);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000077, EnemyEtis, "EnemyEtis-10000077");
				break;
			}
			case 465: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000048);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000078, EnemyEtis, "EnemyEtis-10000078");
				break;
			}
			case 485: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000049);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000079, EnemyEtis, "EnemyEtis-10000079");
				break;
			}
			case 500: {
				requestActor(10000015, EnemyOebiusController001, "EnemyOebiusController001-10000015");
				EnemyErelmanController001* pE2 = (EnemyErelmanController001*)receiveActor(10000021);
				bringSceneMediator()->appendGroupChild(pE2);
				pE2->setPosition(PX_C(3400), PX_C(0), PX_C(0) );
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(10001125);
				bringSceneMediator()->appendGroupChild(p);
				break;
			}
			case 505: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000050);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000080, EnemyEtis, "EnemyEtis-10000080");
				break;
			}
			case 525: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000051);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000081, EnemyEtis, "EnemyEtis-10000081");
				break;
			}
			case 545: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000052);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000082, EnemyEtis, "EnemyEtis-10000082");
				break;
			}
			case 565: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000053);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000083, EnemyEtis, "EnemyEtis-10000083");
				break;
			}
			case 585: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000054);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000084, EnemyEtis, "EnemyEtis-10000084");
				break;
			}
			case 600: {
				EnemyOebiusController002* p2 = (EnemyOebiusController002*)receiveActor(10000005);
				bringSceneMediator()->appendGroupChild(p2);
				p2->setPosition(RND_ABOUT(PX_C(800), PX_C(2000)), RND_ABOUT(0, PX_C(2000)), RND(0, PX_C(5000)) );
				requestActor(10000008, EnemyOebiusController002, "EnemyOebiusController002-10000008");
				break;
			}
			case 605: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000055);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000085, EnemyEtis, "EnemyEtis-10000085");
				break;
			}
			case 625: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000056);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000086, EnemyEtis, "EnemyEtis-10000086");
				break;
			}
			case 645: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000057);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000087, EnemyEtis, "EnemyEtis-10000087");
				break;
			}
			case 665: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000058);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000088, EnemyEtis, "EnemyEtis-10000088");
				break;
			}
			case 685: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000059);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000089, EnemyEtis, "EnemyEtis-10000089");
				break;
			}
			case 700: {
				EnemyOebiusController001* p3 = (EnemyOebiusController001*)receiveActor(10000013);
				bringSceneMediator()->appendGroupChild(p3);
				p3->setPosition(RND_ABOUT(PX_C(800), PX_C(2000)), RND_ABOUT(0, PX_C(2000)), RND(0, PX_C(5000)) );
				requestActor(10000016, EnemyOebiusController001, "EnemyOebiusController001-10000016");
				break;
			}
			case 705: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000060);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000090, EnemyEtis, "EnemyEtis-10000090");
				break;
			}
			case 725: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000061);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000091, EnemyEtis, "EnemyEtis-10000091");
				break;
			}
			case 745: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000062);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000092, EnemyEtis, "EnemyEtis-10000092");
				break;
			}
			case 765: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000063);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000093, EnemyEtis, "EnemyEtis-10000093");
				break;
			}
			case 785: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000064);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000094, EnemyEtis, "EnemyEtis-10000094");
				break;
			}
			case 800: {
				EnemyOebiusController002* p2 = (EnemyOebiusController002*)receiveActor(10000006);
				bringSceneMediator()->appendGroupChild(p2);
				p2->setPosition(RND_ABOUT(PX_C(800), PX_C(2000)), RND_ABOUT(0, PX_C(2000)), RND(0, PX_C(5000)) );
				requestActor(10000009, EnemyOebiusController002, "EnemyOebiusController002-10000009");
				break;
			}
			case 805: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000065);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000095, EnemyEtis, "EnemyEtis-10000095");
				break;
			}
			case 825: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000066);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000096, EnemyEtis, "EnemyEtis-10000096");
				break;
			}
			case 845: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000067);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000097, EnemyEtis, "EnemyEtis-10000097");
				break;
			}
			case 865: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000068);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000098, EnemyEtis, "EnemyEtis-10000098");
				break;
			}
			case 885: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000069);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000099, EnemyEtis, "EnemyEtis-10000099");
				break;
			}
			case 900: {
				EnemyOebiusController001* p3 = (EnemyOebiusController001*)receiveActor(10000014);
				bringSceneMediator()->appendGroupChild(p3);
				p3->setPosition(RND_ABOUT(PX_C(800), PX_C(2000)), RND_ABOUT(0, PX_C(2000)), RND(0, PX_C(5000)) );
				requestActor(10000017, EnemyOebiusController001, "EnemyOebiusController001-10000017");
				break;
			}
			case 905: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000070);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000100, EnemyEtis, "EnemyEtis-10000100");
				break;
			}
			case 925: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000071);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000101, EnemyEtis, "EnemyEtis-10000101");
				break;
			}
			case 945: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000072);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000102, EnemyEtis, "EnemyEtis-10000102");
				break;
			}
			case 965: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000073);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000103, EnemyEtis, "EnemyEtis-10000103");
				break;
			}
			case 985: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000074);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000104, EnemyEtis, "EnemyEtis-10000104");
				break;
			}
			case 1000: {
				appendChild(receiveScene(10000000));
				EnemyOebiusController002* p2 = (EnemyOebiusController002*)receiveActor(10000007);
				bringSceneMediator()->appendGroupChild(p2);
				p2->setPosition(RND_ABOUT(PX_C(800), PX_C(2000)), RND_ABOUT(0, PX_C(2000)), RND(0, PX_C(5000)) );
				requestActor(10000010, EnemyOebiusController002, "EnemyOebiusController002-10000010");
				break;
			}
			case 1005: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000075);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000105, EnemyEtis, "EnemyEtis-10000105");
				break;
			}
			case 1025: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000076);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000106, EnemyEtis, "EnemyEtis-10000106");
				break;
			}
			case 1045: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000077);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000107, EnemyEtis, "EnemyEtis-10000107");
				break;
			}
			case 1065: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000078);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000108, EnemyEtis, "EnemyEtis-10000108");
				break;
			}
			case 1085: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000079);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000109, EnemyEtis, "EnemyEtis-10000109");
				break;
			}
			case 1100: {
				EnemyOebiusController001* p3 = (EnemyOebiusController001*)receiveActor(10000015);
				bringSceneMediator()->appendGroupChild(p3);
				p3->setPosition(RND_ABOUT(PX_C(800), PX_C(2000)), RND_ABOUT(0, PX_C(2000)), RND(0, PX_C(5000)) );
				requestActor(10000018, EnemyOebiusController001, "EnemyOebiusController001-10000018");
				break;
			}
			case 1105: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000080);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000110, EnemyEtis, "EnemyEtis-10000110");
				break;
			}
			case 1125: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000081);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000111, EnemyEtis, "EnemyEtis-10000111");
				break;
			}
			case 1145: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000082);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000112, EnemyEtis, "EnemyEtis-10000112");
				break;
			}
			case 1165: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000083);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000113, EnemyEtis, "EnemyEtis-10000113");
				break;
			}
			case 1185: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000084);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000114, EnemyEtis, "EnemyEtis-10000114");
				break;
			}
			case 1200: {
				EnemyOebiusController002* p2 = (EnemyOebiusController002*)receiveActor(10000008);
				bringSceneMediator()->appendGroupChild(p2);
				p2->setPosition(RND_ABOUT(PX_C(800), PX_C(2000)), RND_ABOUT(0, PX_C(2000)), RND(0, PX_C(5000)) );
				requestActor(10000011, EnemyOebiusController002, "EnemyOebiusController002-10000011");
				break;
			}
			case 1205: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000085);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000115, EnemyEtis, "EnemyEtis-10000115");
				break;
			}
			case 1225: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000086);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000116, EnemyEtis, "EnemyEtis-10000116");
				break;
			}
			case 1245: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000087);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000117, EnemyEtis, "EnemyEtis-10000117");
				break;
			}
			case 1265: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000088);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000118, EnemyEtis, "EnemyEtis-10000118");
				break;
			}
			case 1285: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000089);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000119, EnemyEtis, "EnemyEtis-10000119");
				break;
			}
			case 1300: {
				EnemyOebiusController001* p3 = (EnemyOebiusController001*)receiveActor(10000016);
				bringSceneMediator()->appendGroupChild(p3);
				p3->setPosition(RND_ABOUT(PX_C(800), PX_C(2000)), RND_ABOUT(0, PX_C(2000)), RND(0, PX_C(5000)) );
				requestActor(10000019, EnemyOebiusController001, "EnemyOebiusController001-10000019");
				break;
			}
			case 1305: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000090);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000120, EnemyEtis, "EnemyEtis-10000120");
				break;
			}
			case 1325: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000091);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000121, EnemyEtis, "EnemyEtis-10000121");
				break;
			}
			case 1345: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000092);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000122, EnemyEtis, "EnemyEtis-10000122");
				break;
			}
			case 1365: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000093);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000123, EnemyEtis, "EnemyEtis-10000123");
				break;
			}
			case 1385: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000094);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000124, EnemyEtis, "EnemyEtis-10000124");
				break;
			}
			case 1400: {
				EnemyOebiusController002* p2 = (EnemyOebiusController002*)receiveActor(10000009);
				bringSceneMediator()->appendGroupChild(p2);
				p2->setPosition(RND_ABOUT(PX_C(800), PX_C(2000)), RND_ABOUT(0, PX_C(2000)), RND(0, PX_C(5000)) );
				requestActor(10000012, EnemyOebiusController002, "EnemyOebiusController002-10000012");
				break;
			}
			case 1405: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000095);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000125, EnemyEtis, "EnemyEtis-10000125");
				break;
			}
			case 1425: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000096);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000126, EnemyEtis, "EnemyEtis-10000126");
				break;
			}
			case 1445: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000097);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000127, EnemyEtis, "EnemyEtis-10000127");
				break;
			}
			case 1465: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000098);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000128, EnemyEtis, "EnemyEtis-10000128");
				break;
			}
			case 1485: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000099);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000129, EnemyEtis, "EnemyEtis-10000129");
				break;
			}
			case 1500: {
				EnemyOebiusController001* p3 = (EnemyOebiusController001*)receiveActor(10000017);
				bringSceneMediator()->appendGroupChild(p3);
				p3->setPosition(RND_ABOUT(PX_C(800), PX_C(2000)), RND_ABOUT(0, PX_C(2000)), RND(0, PX_C(5000)) );
				break;
			}
			case 1505: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000100);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000130, EnemyEtis, "EnemyEtis-10000130");
				break;
			}
			case 1525: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000101);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000131, EnemyEtis, "EnemyEtis-10000131");
				break;
			}
			case 1545: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000102);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000132, EnemyEtis, "EnemyEtis-10000132");
				break;
			}
			case 1565: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000103);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000133, EnemyEtis, "EnemyEtis-10000133");
				break;
			}
			case 1585: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000104);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000134, EnemyEtis, "EnemyEtis-10000134");
				break;
			}
			case 1600: {
				EnemyOebiusController002* p2 = (EnemyOebiusController002*)receiveActor(10000010);
				bringSceneMediator()->appendGroupChild(p2);
				p2->setPosition(RND_ABOUT(PX_C(800), PX_C(2000)), RND_ABOUT(0, PX_C(2000)), RND(0, PX_C(5000)) );
				break;
			}
			case 1605: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000105);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000135, EnemyEtis, "EnemyEtis-10000135");
				break;
			}
			case 1625: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000106);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000136, EnemyEtis, "EnemyEtis-10000136");
				break;
			}
			case 1645: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000107);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000137, EnemyEtis, "EnemyEtis-10000137");
				break;
			}
			case 1665: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000108);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000138, EnemyEtis, "EnemyEtis-10000138");
				break;
			}
			case 1685: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000109);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000139, EnemyEtis, "EnemyEtis-10000139");
				break;
			}
			case 1700: {
				EnemyOebiusController001* p3 = (EnemyOebiusController001*)receiveActor(10000018);
				bringSceneMediator()->appendGroupChild(p3);
				p3->setPosition(RND_ABOUT(PX_C(800), PX_C(2000)), RND_ABOUT(0, PX_C(2000)), RND(0, PX_C(5000)) );
				break;
			}
			case 1705: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000110);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000140, EnemyEtis, "EnemyEtis-10000140");
				break;
			}
			case 1725: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000111);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000141, EnemyEtis, "EnemyEtis-10000141");
				break;
			}
			case 1745: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000112);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000142, EnemyEtis, "EnemyEtis-10000142");
				break;
			}
			case 1765: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000113);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000143, EnemyEtis, "EnemyEtis-10000143");
				break;
			}
			case 1785: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000114);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000144, EnemyEtis, "EnemyEtis-10000144");
				break;
			}
			case 1800: {
				EnemyOebiusController002* p2 = (EnemyOebiusController002*)receiveActor(10000011);
				bringSceneMediator()->appendGroupChild(p2);
				p2->setPosition(RND_ABOUT(PX_C(800), PX_C(2000)), RND_ABOUT(0, PX_C(2000)), RND(0, PX_C(5000)) );
				break;
			}
			case 1805: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000115);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000145, EnemyEtis, "EnemyEtis-10000145");
				break;
			}
			case 1825: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000116);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000146, EnemyEtis, "EnemyEtis-10000146");
				break;
			}
			case 1845: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000117);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000147, EnemyEtis, "EnemyEtis-10000147");
				break;
			}
			case 1865: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000118);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000148, EnemyEtis, "EnemyEtis-10000148");
				break;
			}
			case 1885: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000119);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000149, EnemyEtis, "EnemyEtis-10000149");
				break;
			}
			case 1900: {
				EnemyOebiusController001* p3 = (EnemyOebiusController001*)receiveActor(10000019);
				bringSceneMediator()->appendGroupChild(p3);
				p3->setPosition(RND_ABOUT(PX_C(800), PX_C(2000)), RND_ABOUT(0, PX_C(2000)), RND(0, PX_C(5000)) );
				requestActor(10001126, EnemyDrastea, "EnemyDrastea-10001126");
				break;
			}
			case 1905: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000120);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000150, EnemyEtis, "EnemyEtis-10000150");
				break;
			}
			case 1925: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000121);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000151, EnemyEtis, "EnemyEtis-10000151");
				break;
			}
			case 1945: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000122);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000152, EnemyEtis, "EnemyEtis-10000152");
				break;
			}
			case 1965: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000123);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000153, EnemyEtis, "EnemyEtis-10000153");
				break;
			}
			case 1985: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000124);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000154, EnemyEtis, "EnemyEtis-10000154");
				break;
			}
			case 2000: {
				EnemyOebiusController002* p2 = (EnemyOebiusController002*)receiveActor(10000012);
				bringSceneMediator()->appendGroupChild(p2);
				p2->setPosition(RND_ABOUT(PX_C(800), PX_C(2000)), RND_ABOUT(0, PX_C(2000)), RND(0, PX_C(5000)) );
				break;
			}
			case 2005: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000125);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000155, EnemyEtis, "EnemyEtis-10000155");
				break;
			}
			case 2025: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000126);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000156, EnemyEtis, "EnemyEtis-10000156");
				break;
			}
			case 2045: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000127);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000157, EnemyEtis, "EnemyEtis-10000157");
				break;
			}
			case 2065: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000128);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000158, EnemyEtis, "EnemyEtis-10000158");
				break;
			}
			case 2085: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000129);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000159, EnemyEtis, "EnemyEtis-10000159");
				break;
			}
			case 2105: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000130);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000160, EnemyEtis, "EnemyEtis-10000160");
				break;
			}
			case 2125: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000131);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000161, EnemyEtis, "EnemyEtis-10000161");
				break;
			}
			case 2145: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000132);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000162, EnemyEtis, "EnemyEtis-10000162");
				break;
			}
			case 2165: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000133);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000163, EnemyEtis, "EnemyEtis-10000163");
				break;
			}
			case 2185: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000134);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000164, EnemyEtis, "EnemyEtis-10000164");
				break;
			}
			case 2205: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000135);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000165, EnemyEtis, "EnemyEtis-10000165");
				break;
			}
			case 2225: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000136);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000166, EnemyEtis, "EnemyEtis-10000166");
				break;
			}
			case 2245: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000137);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000167, EnemyEtis, "EnemyEtis-10000167");
				break;
			}
			case 2265: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000138);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000168, EnemyEtis, "EnemyEtis-10000168");
				break;
			}
			case 2285: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000139);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000169, EnemyEtis, "EnemyEtis-10000169");
				break;
			}
			case 2305: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000140);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000170, EnemyEtis, "EnemyEtis-10000170");
				break;
			}
			case 2325: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000141);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000171, EnemyEtis, "EnemyEtis-10000171");
				break;
			}
			case 2345: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000142);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000172, EnemyEtis, "EnemyEtis-10000172");
				break;
			}
			case 2365: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000143);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000173, EnemyEtis, "EnemyEtis-10000173");
				break;
			}
			case 2385: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000144);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000174, EnemyEtis, "EnemyEtis-10000174");
				break;
			}
			case 2405: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000145);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000175, EnemyEtis, "EnemyEtis-10000175");
				break;
			}
			case 2425: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000146);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000176, EnemyEtis, "EnemyEtis-10000176");
				break;
			}
			case 2445: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000147);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000177, EnemyEtis, "EnemyEtis-10000177");
				break;
			}
			case 2465: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000148);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000178, EnemyEtis, "EnemyEtis-10000178");
				break;
			}
			case 2485: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000149);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000179, EnemyEtis, "EnemyEtis-10000179");
				break;
			}
			case 2500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(10001126);
				bringSceneMediator()->appendGroupChild(p);
				break;
			}
			case 2505: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000150);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000180, EnemyEtis, "EnemyEtis-10000180");
				break;
			}
			case 2525: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000151);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000181, EnemyEtis, "EnemyEtis-10000181");
				break;
			}
			case 2545: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000152);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000182, EnemyEtis, "EnemyEtis-10000182");
				break;
			}
			case 2565: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000153);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000183, EnemyEtis, "EnemyEtis-10000183");
				break;
			}
			case 2585: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000154);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000184, EnemyEtis, "EnemyEtis-10000184");
				break;
			}
			case 2605: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000155);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000185, EnemyEtis, "EnemyEtis-10000185");
				break;
			}
			case 2625: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000156);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000186, EnemyEtis, "EnemyEtis-10000186");
				break;
			}
			case 2645: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000157);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000187, EnemyEtis, "EnemyEtis-10000187");
				break;
			}
			case 2665: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000158);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000188, EnemyEtis, "EnemyEtis-10000188");
				break;
			}
			case 2685: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000159);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000189, EnemyEtis, "EnemyEtis-10000189");
				break;
			}
			case 2705: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000160);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000190, EnemyEtis, "EnemyEtis-10000190");
				break;
			}
			case 2725: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000161);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000191, EnemyEtis, "EnemyEtis-10000191");
				break;
			}
			case 2745: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000162);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000192, EnemyEtis, "EnemyEtis-10000192");
				break;
			}
			case 2765: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000163);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000193, EnemyEtis, "EnemyEtis-10000193");
				break;
			}
			case 2785: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000164);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000194, EnemyEtis, "EnemyEtis-10000194");
				break;
			}
			case 2805: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000165);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000195, EnemyEtis, "EnemyEtis-10000195");
				break;
			}
			case 2825: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000166);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000196, EnemyEtis, "EnemyEtis-10000196");
				break;
			}
			case 2845: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000167);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000197, EnemyEtis, "EnemyEtis-10000197");
				break;
			}
			case 2865: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000168);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000198, EnemyEtis, "EnemyEtis-10000198");
				break;
			}
			case 2885: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000169);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000199, EnemyEtis, "EnemyEtis-10000199");
				break;
			}
			case 2905: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000170);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000200, EnemyEtis, "EnemyEtis-10000200");
				break;
			}
			case 2925: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000171);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000201, EnemyEtis, "EnemyEtis-10000201");
				break;
			}
			case 2945: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000172);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000202, EnemyEtis, "EnemyEtis-10000202");
				break;
			}
			case 2965: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000173);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000203, EnemyEtis, "EnemyEtis-10000203");
				break;
			}
			case 2985: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000174);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000204, EnemyEtis, "EnemyEtis-10000204");
				break;
			}
			case 3005: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000175);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000205, EnemyEtis, "EnemyEtis-10000205");
				break;
			}
			case 3025: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000176);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000206, EnemyEtis, "EnemyEtis-10000206");
				break;
			}
			case 3045: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000177);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000207, EnemyEtis, "EnemyEtis-10000207");
				break;
			}
			case 3065: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000178);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000208, EnemyEtis, "EnemyEtis-10000208");
				break;
			}
			case 3085: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000179);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000209, EnemyEtis, "EnemyEtis-10000209");
				break;
			}
			case 3105: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000180);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000210, EnemyEtis, "EnemyEtis-10000210");
				break;
			}
			case 3125: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000181);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000211, EnemyEtis, "EnemyEtis-10000211");
				break;
			}
			case 3145: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000182);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000212, EnemyEtis, "EnemyEtis-10000212");
				break;
			}
			case 3165: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000183);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000213, EnemyEtis, "EnemyEtis-10000213");
				break;
			}
			case 3185: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000184);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000214, EnemyEtis, "EnemyEtis-10000214");
				break;
			}
			case 3205: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000185);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000215, EnemyEtis, "EnemyEtis-10000215");
				break;
			}
			case 3225: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000186);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000216, EnemyEtis, "EnemyEtis-10000216");
				break;
			}
			case 3245: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000187);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000217, EnemyEtis, "EnemyEtis-10000217");
				break;
			}
			case 3265: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000188);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000218, EnemyEtis, "EnemyEtis-10000218");
				break;
			}
			case 3285: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000189);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000219, EnemyEtis, "EnemyEtis-10000219");
				break;
			}
			case 3305: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000190);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000220, EnemyEtis, "EnemyEtis-10000220");
				break;
			}
			case 3325: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000191);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000221, EnemyEtis, "EnemyEtis-10000221");
				break;
			}
			case 3345: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000192);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000222, EnemyEtis, "EnemyEtis-10000222");
				break;
			}
			case 3365: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000193);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000223, EnemyEtis, "EnemyEtis-10000223");
				break;
			}
			case 3385: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000194);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000224, EnemyEtis, "EnemyEtis-10000224");
				break;
			}
			case 3405: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000195);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000225, EnemyEtis, "EnemyEtis-10000225");
				break;
			}
			case 3425: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000196);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000226, EnemyEtis, "EnemyEtis-10000226");
				break;
			}
			case 3445: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000197);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000227, EnemyEtis, "EnemyEtis-10000227");
				break;
			}
			case 3465: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000198);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000228, EnemyEtis, "EnemyEtis-10000228");
				break;
			}
			case 3485: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000199);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000229, EnemyEtis, "EnemyEtis-10000229");
				break;
			}
			case 3505: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000200);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000230, EnemyEtis, "EnemyEtis-10000230");
				break;
			}
			case 3525: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000201);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000231, EnemyEtis, "EnemyEtis-10000231");
				break;
			}
			case 3545: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000202);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000232, EnemyEtis, "EnemyEtis-10000232");
				break;
			}
			case 3565: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000203);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000233, EnemyEtis, "EnemyEtis-10000233");
				break;
			}
			case 3585: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000204);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000234, EnemyEtis, "EnemyEtis-10000234");
				break;
			}
			case 3605: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000205);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000235, EnemyEtis, "EnemyEtis-10000235");
				break;
			}
			case 3625: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000206);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000236, EnemyEtis, "EnemyEtis-10000236");
				break;
			}
			case 3645: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000207);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000237, EnemyEtis, "EnemyEtis-10000237");
				break;
			}
			case 3665: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000208);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000238, EnemyEtis, "EnemyEtis-10000238");
				break;
			}
			case 3685: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000209);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000239, EnemyEtis, "EnemyEtis-10000239");
				break;
			}
			case 3705: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000210);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000240, EnemyEtis, "EnemyEtis-10000240");
				break;
			}
			case 3725: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000211);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000241, EnemyEtis, "EnemyEtis-10000241");
				break;
			}
			case 3745: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000212);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000242, EnemyEtis, "EnemyEtis-10000242");
				break;
			}
			case 3765: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000213);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000243, EnemyEtis, "EnemyEtis-10000243");
				break;
			}
			case 3785: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000214);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000244, EnemyEtis, "EnemyEtis-10000244");
				break;
			}
			case 3805: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000215);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000245, EnemyEtis, "EnemyEtis-10000245");
				break;
			}
			case 3825: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000216);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000246, EnemyEtis, "EnemyEtis-10000246");
				break;
			}
			case 3845: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000217);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000247, EnemyEtis, "EnemyEtis-10000247");
				break;
			}
			case 3865: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000218);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000248, EnemyEtis, "EnemyEtis-10000248");
				break;
			}
			case 3885: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000219);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000249, EnemyEtis, "EnemyEtis-10000249");
				break;
			}
			case 3900: {
				requestActor(10001127, EnemyDrastea, "EnemyDrastea-10001127");
				break;
			}
			case 3905: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000220);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000250, EnemyEtis, "EnemyEtis-10000250");
				break;
			}
			case 3925: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000221);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000251, EnemyEtis, "EnemyEtis-10000251");
				break;
			}
			case 3945: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000222);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000252, EnemyEtis, "EnemyEtis-10000252");
				break;
			}
			case 3965: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000223);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000253, EnemyEtis, "EnemyEtis-10000253");
				break;
			}
			case 3985: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000224);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000254, EnemyEtis, "EnemyEtis-10000254");
				break;
			}
			case 4005: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000225);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000255, EnemyEtis, "EnemyEtis-10000255");
				break;
			}
			case 4025: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000226);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000256, EnemyEtis, "EnemyEtis-10000256");
				break;
			}
			case 4045: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000227);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000257, EnemyEtis, "EnemyEtis-10000257");
				break;
			}
			case 4065: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000228);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000258, EnemyEtis, "EnemyEtis-10000258");
				break;
			}
			case 4085: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000229);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000259, EnemyEtis, "EnemyEtis-10000259");
				break;
			}
			case 4105: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000230);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000260, EnemyEtis, "EnemyEtis-10000260");
				break;
			}
			case 4125: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000231);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000261, EnemyEtis, "EnemyEtis-10000261");
				break;
			}
			case 4145: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000232);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000262, EnemyEtis, "EnemyEtis-10000262");
				break;
			}
			case 4165: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000233);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000263, EnemyEtis, "EnemyEtis-10000263");
				break;
			}
			case 4185: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000234);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000264, EnemyEtis, "EnemyEtis-10000264");
				break;
			}
			case 4205: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000235);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000265, EnemyEtis, "EnemyEtis-10000265");
				break;
			}
			case 4225: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000236);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000266, EnemyEtis, "EnemyEtis-10000266");
				break;
			}
			case 4245: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000237);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000267, EnemyEtis, "EnemyEtis-10000267");
				break;
			}
			case 4265: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000238);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000268, EnemyEtis, "EnemyEtis-10000268");
				break;
			}
			case 4285: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000239);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000269, EnemyEtis, "EnemyEtis-10000269");
				break;
			}
			case 4305: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000240);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000270, EnemyEtis, "EnemyEtis-10000270");
				break;
			}
			case 4325: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000241);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000271, EnemyEtis, "EnemyEtis-10000271");
				break;
			}
			case 4345: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000242);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000272, EnemyEtis, "EnemyEtis-10000272");
				break;
			}
			case 4365: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000243);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000273, EnemyEtis, "EnemyEtis-10000273");
				break;
			}
			case 4385: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000244);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000274, EnemyEtis, "EnemyEtis-10000274");
				break;
			}
			case 4405: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000245);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000275, EnemyEtis, "EnemyEtis-10000275");
				break;
			}
			case 4425: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000246);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000276, EnemyEtis, "EnemyEtis-10000276");
				break;
			}
			case 4445: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000247);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000277, EnemyEtis, "EnemyEtis-10000277");
				break;
			}
			case 4465: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000248);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000278, EnemyEtis, "EnemyEtis-10000278");
				break;
			}
			case 4485: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000249);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000279, EnemyEtis, "EnemyEtis-10000279");
				break;
			}
			case 4500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(10001127);
				bringSceneMediator()->appendGroupChild(p);
				break;
			}
			case 4505: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000250);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000280, EnemyEtis, "EnemyEtis-10000280");
				break;
			}
			case 4525: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000251);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000281, EnemyEtis, "EnemyEtis-10000281");
				break;
			}
			case 4545: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000252);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000282, EnemyEtis, "EnemyEtis-10000282");
				break;
			}
			case 4565: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000253);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000283, EnemyEtis, "EnemyEtis-10000283");
				break;
			}
			case 4585: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000254);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000284, EnemyEtis, "EnemyEtis-10000284");
				break;
			}
			case 4605: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000255);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000285, EnemyEtis, "EnemyEtis-10000285");
				break;
			}
			case 4625: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000256);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000286, EnemyEtis, "EnemyEtis-10000286");
				break;
			}
			case 4645: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000257);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000287, EnemyEtis, "EnemyEtis-10000287");
				break;
			}
			case 4665: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000258);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000288, EnemyEtis, "EnemyEtis-10000288");
				break;
			}
			case 4685: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000259);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000289, EnemyEtis, "EnemyEtis-10000289");
				break;
			}
			case 4705: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000260);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000290, EnemyEtis, "EnemyEtis-10000290");
				break;
			}
			case 4725: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000261);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000291, EnemyEtis, "EnemyEtis-10000291");
				break;
			}
			case 4745: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000262);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000292, EnemyEtis, "EnemyEtis-10000292");
				break;
			}
			case 4765: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000263);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000293, EnemyEtis, "EnemyEtis-10000293");
				break;
			}
			case 4785: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000264);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000294, EnemyEtis, "EnemyEtis-10000294");
				break;
			}
			case 4805: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000265);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000295, EnemyEtis, "EnemyEtis-10000295");
				break;
			}
			case 4825: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000266);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000296, EnemyEtis, "EnemyEtis-10000296");
				break;
			}
			case 4845: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000267);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000297, EnemyEtis, "EnemyEtis-10000297");
				break;
			}
			case 4865: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000268);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000298, EnemyEtis, "EnemyEtis-10000298");
				break;
			}
			case 4885: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000269);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000299, EnemyEtis, "EnemyEtis-10000299");
				break;
			}
			case 4905: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000270);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000300, EnemyEtis, "EnemyEtis-10000300");
				break;
			}
			case 4925: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000271);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000301, EnemyEtis, "EnemyEtis-10000301");
				break;
			}
			case 4945: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000272);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000302, EnemyEtis, "EnemyEtis-10000302");
				break;
			}
			case 4965: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000273);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000303, EnemyEtis, "EnemyEtis-10000303");
				break;
			}
			case 4985: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000274);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000304, EnemyEtis, "EnemyEtis-10000304");
				break;
			}
			case 5005: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000275);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000305, EnemyEtis, "EnemyEtis-10000305");
				break;
			}
			case 5025: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000276);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000306, EnemyEtis, "EnemyEtis-10000306");
				break;
			}
			case 5045: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000277);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000307, EnemyEtis, "EnemyEtis-10000307");
				break;
			}
			case 5065: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000278);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000308, EnemyEtis, "EnemyEtis-10000308");
				break;
			}
			case 5085: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000279);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000309, EnemyEtis, "EnemyEtis-10000309");
				break;
			}
			case 5100: {
				requestScene(10000001, StageDebugPart02, "StageDebugPart02-10000001");
				break;
			}
			case 5105: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000280);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000310, EnemyEtis, "EnemyEtis-10000310");
				break;
			}
			case 5125: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000281);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000311, EnemyEtis, "EnemyEtis-10000311");
				break;
			}
			case 5145: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000282);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000312, EnemyEtis, "EnemyEtis-10000312");
				break;
			}
			case 5165: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000283);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000313, EnemyEtis, "EnemyEtis-10000313");
				break;
			}
			case 5185: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000284);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000314, EnemyEtis, "EnemyEtis-10000314");
				break;
			}
			case 5205: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000285);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000315, EnemyEtis, "EnemyEtis-10000315");
				break;
			}
			case 5225: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000286);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000316, EnemyEtis, "EnemyEtis-10000316");
				break;
			}
			case 5245: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000287);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000317, EnemyEtis, "EnemyEtis-10000317");
				break;
			}
			case 5265: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000288);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000318, EnemyEtis, "EnemyEtis-10000318");
				break;
			}
			case 5285: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000289);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000319, EnemyEtis, "EnemyEtis-10000319");
				break;
			}
			case 5305: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000290);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000320, EnemyEtis, "EnemyEtis-10000320");
				break;
			}
			case 5325: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000291);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000321, EnemyEtis, "EnemyEtis-10000321");
				break;
			}
			case 5345: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000292);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000322, EnemyEtis, "EnemyEtis-10000322");
				break;
			}
			case 5365: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000293);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000323, EnemyEtis, "EnemyEtis-10000323");
				break;
			}
			case 5385: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000294);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000324, EnemyEtis, "EnemyEtis-10000324");
				break;
			}
			case 5405: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000295);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000325, EnemyEtis, "EnemyEtis-10000325");
				break;
			}
			case 5425: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000296);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000326, EnemyEtis, "EnemyEtis-10000326");
				break;
			}
			case 5445: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000297);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000327, EnemyEtis, "EnemyEtis-10000327");
				break;
			}
			case 5465: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000298);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000328, EnemyEtis, "EnemyEtis-10000328");
				break;
			}
			case 5485: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000299);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000329, EnemyEtis, "EnemyEtis-10000329");
				break;
			}
			case 5505: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000300);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000330, EnemyEtis, "EnemyEtis-10000330");
				break;
			}
			case 5525: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000301);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000331, EnemyEtis, "EnemyEtis-10000331");
				break;
			}
			case 5545: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000302);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000332, EnemyEtis, "EnemyEtis-10000332");
				break;
			}
			case 5565: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000303);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000333, EnemyEtis, "EnemyEtis-10000333");
				break;
			}
			case 5585: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000304);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000334, EnemyEtis, "EnemyEtis-10000334");
				break;
			}
			case 5605: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000305);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000335, EnemyEtis, "EnemyEtis-10000335");
				break;
			}
			case 5625: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000306);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000336, EnemyEtis, "EnemyEtis-10000336");
				break;
			}
			case 5645: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000307);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000337, EnemyEtis, "EnemyEtis-10000337");
				break;
			}
			case 5665: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000308);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000338, EnemyEtis, "EnemyEtis-10000338");
				break;
			}
			case 5685: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000309);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000339, EnemyEtis, "EnemyEtis-10000339");
				break;
			}
			case 5705: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000310);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000340, EnemyEtis, "EnemyEtis-10000340");
				break;
			}
			case 5725: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000311);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000341, EnemyEtis, "EnemyEtis-10000341");
				break;
			}
			case 5745: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000312);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000342, EnemyEtis, "EnemyEtis-10000342");
				break;
			}
			case 5765: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000313);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000343, EnemyEtis, "EnemyEtis-10000343");
				break;
			}
			case 5785: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000314);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000344, EnemyEtis, "EnemyEtis-10000344");
				break;
			}
			case 5805: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000315);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000345, EnemyEtis, "EnemyEtis-10000345");
				break;
			}
			case 5825: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000316);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000346, EnemyEtis, "EnemyEtis-10000346");
				break;
			}
			case 5845: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000317);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000347, EnemyEtis, "EnemyEtis-10000347");
				break;
			}
			case 5865: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000318);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000348, EnemyEtis, "EnemyEtis-10000348");
				break;
			}
			case 5885: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000319);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000349, EnemyEtis, "EnemyEtis-10000349");
				break;
			}
			case 5900: {
				requestActor(10001128, EnemyDrastea, "EnemyDrastea-10001128");
				break;
			}
			case 5905: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000320);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000350, EnemyEtis, "EnemyEtis-10000350");
				break;
			}
			case 5925: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000321);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000351, EnemyEtis, "EnemyEtis-10000351");
				break;
			}
			case 5945: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000322);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000352, EnemyEtis, "EnemyEtis-10000352");
				break;
			}
			case 5965: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000323);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000353, EnemyEtis, "EnemyEtis-10000353");
				break;
			}
			case 5985: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000324);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000354, EnemyEtis, "EnemyEtis-10000354");
				break;
			}
			case 6000: {
				appendChild(receiveScene(10000001));
				break;
			}
			case 6005: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000325);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000355, EnemyEtis, "EnemyEtis-10000355");
				break;
			}
			case 6025: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000326);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000356, EnemyEtis, "EnemyEtis-10000356");
				break;
			}
			case 6045: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000327);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000357, EnemyEtis, "EnemyEtis-10000357");
				break;
			}
			case 6065: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000328);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000358, EnemyEtis, "EnemyEtis-10000358");
				break;
			}
			case 6085: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000329);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000359, EnemyEtis, "EnemyEtis-10000359");
				break;
			}
			case 6105: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000330);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000360, EnemyEtis, "EnemyEtis-10000360");
				break;
			}
			case 6125: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000331);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000361, EnemyEtis, "EnemyEtis-10000361");
				break;
			}
			case 6145: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000332);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000362, EnemyEtis, "EnemyEtis-10000362");
				break;
			}
			case 6165: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000333);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000363, EnemyEtis, "EnemyEtis-10000363");
				break;
			}
			case 6185: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000334);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000364, EnemyEtis, "EnemyEtis-10000364");
				break;
			}
			case 6205: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000335);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000365, EnemyEtis, "EnemyEtis-10000365");
				break;
			}
			case 6225: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000336);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000366, EnemyEtis, "EnemyEtis-10000366");
				break;
			}
			case 6245: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000337);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000367, EnemyEtis, "EnemyEtis-10000367");
				break;
			}
			case 6265: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000338);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000368, EnemyEtis, "EnemyEtis-10000368");
				break;
			}
			case 6285: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000339);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000369, EnemyEtis, "EnemyEtis-10000369");
				break;
			}
			case 6305: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000340);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000370, EnemyEtis, "EnemyEtis-10000370");
				break;
			}
			case 6325: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000341);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000371, EnemyEtis, "EnemyEtis-10000371");
				break;
			}
			case 6345: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000342);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000372, EnemyEtis, "EnemyEtis-10000372");
				break;
			}
			case 6365: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000343);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000373, EnemyEtis, "EnemyEtis-10000373");
				break;
			}
			case 6385: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000344);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000374, EnemyEtis, "EnemyEtis-10000374");
				break;
			}
			case 6405: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000345);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000375, EnemyEtis, "EnemyEtis-10000375");
				break;
			}
			case 6425: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000346);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000376, EnemyEtis, "EnemyEtis-10000376");
				break;
			}
			case 6445: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000347);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000377, EnemyEtis, "EnemyEtis-10000377");
				break;
			}
			case 6465: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000348);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000378, EnemyEtis, "EnemyEtis-10000378");
				break;
			}
			case 6485: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000349);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000379, EnemyEtis, "EnemyEtis-10000379");
				break;
			}
			case 6500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(10001128);
				bringSceneMediator()->appendGroupChild(p);
				break;
			}
			case 6505: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000350);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000380, EnemyEtis, "EnemyEtis-10000380");
				break;
			}
			case 6525: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000351);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000381, EnemyEtis, "EnemyEtis-10000381");
				break;
			}
			case 6545: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000352);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000382, EnemyEtis, "EnemyEtis-10000382");
				break;
			}
			case 6565: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000353);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000383, EnemyEtis, "EnemyEtis-10000383");
				break;
			}
			case 6585: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000354);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000384, EnemyEtis, "EnemyEtis-10000384");
				break;
			}
			case 6605: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000355);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000385, EnemyEtis, "EnemyEtis-10000385");
				break;
			}
			case 6625: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000356);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000386, EnemyEtis, "EnemyEtis-10000386");
				break;
			}
			case 6645: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000357);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000387, EnemyEtis, "EnemyEtis-10000387");
				break;
			}
			case 6665: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000358);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000388, EnemyEtis, "EnemyEtis-10000388");
				break;
			}
			case 6685: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000359);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000389, EnemyEtis, "EnemyEtis-10000389");
				break;
			}
			case 6705: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000360);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000390, EnemyEtis, "EnemyEtis-10000390");
				break;
			}
			case 6725: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000361);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000391, EnemyEtis, "EnemyEtis-10000391");
				break;
			}
			case 6745: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000362);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000392, EnemyEtis, "EnemyEtis-10000392");
				break;
			}
			case 6765: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000363);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000393, EnemyEtis, "EnemyEtis-10000393");
				break;
			}
			case 6785: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000364);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000394, EnemyEtis, "EnemyEtis-10000394");
				break;
			}
			case 6805: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000365);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000395, EnemyEtis, "EnemyEtis-10000395");
				break;
			}
			case 6825: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000366);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000396, EnemyEtis, "EnemyEtis-10000396");
				break;
			}
			case 6845: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000367);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000397, EnemyEtis, "EnemyEtis-10000397");
				break;
			}
			case 6865: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000368);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000398, EnemyEtis, "EnemyEtis-10000398");
				break;
			}
			case 6885: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000369);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000399, EnemyEtis, "EnemyEtis-10000399");
				break;
			}
			case 6905: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000370);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000400, EnemyEtis, "EnemyEtis-10000400");
				break;
			}
			case 6925: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000371);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000401, EnemyEtis, "EnemyEtis-10000401");
				break;
			}
			case 6945: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000372);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000402, EnemyEtis, "EnemyEtis-10000402");
				break;
			}
			case 6965: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000373);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000403, EnemyEtis, "EnemyEtis-10000403");
				break;
			}
			case 6985: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000374);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000404, EnemyEtis, "EnemyEtis-10000404");
				break;
			}
			case 7005: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000375);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000405, EnemyEtis, "EnemyEtis-10000405");
				break;
			}
			case 7025: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000376);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000406, EnemyEtis, "EnemyEtis-10000406");
				break;
			}
			case 7045: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000377);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000407, EnemyEtis, "EnemyEtis-10000407");
				break;
			}
			case 7065: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000378);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000408, EnemyEtis, "EnemyEtis-10000408");
				break;
			}
			case 7085: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000379);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000409, EnemyEtis, "EnemyEtis-10000409");
				break;
			}
			case 7105: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000380);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000410, EnemyEtis, "EnemyEtis-10000410");
				break;
			}
			case 7125: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000381);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000411, EnemyEtis, "EnemyEtis-10000411");
				break;
			}
			case 7145: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000382);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000412, EnemyEtis, "EnemyEtis-10000412");
				break;
			}
			case 7165: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000383);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000413, EnemyEtis, "EnemyEtis-10000413");
				break;
			}
			case 7185: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000384);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000414, EnemyEtis, "EnemyEtis-10000414");
				break;
			}
			case 7200: {
				requestScene(10000002, StageDebugPart03, "StageDebugPart03-10000002");
				break;
			}
			case 7205: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000385);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000415, EnemyEtis, "EnemyEtis-10000415");
				break;
			}
			case 7225: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000386);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000416, EnemyEtis, "EnemyEtis-10000416");
				break;
			}
			case 7245: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000387);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000417, EnemyEtis, "EnemyEtis-10000417");
				break;
			}
			case 7265: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000388);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000418, EnemyEtis, "EnemyEtis-10000418");
				break;
			}
			case 7285: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000389);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000419, EnemyEtis, "EnemyEtis-10000419");
				break;
			}
			case 7305: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000390);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000420, EnemyEtis, "EnemyEtis-10000420");
				break;
			}
			case 7325: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000391);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000421, EnemyEtis, "EnemyEtis-10000421");
				break;
			}
			case 7345: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000392);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000422, EnemyEtis, "EnemyEtis-10000422");
				break;
			}
			case 7365: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000393);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000423, EnemyEtis, "EnemyEtis-10000423");
				break;
			}
			case 7385: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000394);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000424, EnemyEtis, "EnemyEtis-10000424");
				break;
			}
			case 7405: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000395);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000425, EnemyEtis, "EnemyEtis-10000425");
				break;
			}
			case 7425: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000396);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000426, EnemyEtis, "EnemyEtis-10000426");
				break;
			}
			case 7445: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000397);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000427, EnemyEtis, "EnemyEtis-10000427");
				break;
			}
			case 7465: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000398);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000428, EnemyEtis, "EnemyEtis-10000428");
				break;
			}
			case 7485: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000399);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000429, EnemyEtis, "EnemyEtis-10000429");
				break;
			}
			case 7505: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000400);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000430, EnemyEtis, "EnemyEtis-10000430");
				break;
			}
			case 7525: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000401);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000431, EnemyEtis, "EnemyEtis-10000431");
				break;
			}
			case 7545: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000402);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000432, EnemyEtis, "EnemyEtis-10000432");
				break;
			}
			case 7565: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000403);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000433, EnemyEtis, "EnemyEtis-10000433");
				break;
			}
			case 7585: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000404);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000434, EnemyEtis, "EnemyEtis-10000434");
				break;
			}
			case 7605: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000405);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000435, EnemyEtis, "EnemyEtis-10000435");
				break;
			}
			case 7625: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000406);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000436, EnemyEtis, "EnemyEtis-10000436");
				break;
			}
			case 7645: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000407);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000437, EnemyEtis, "EnemyEtis-10000437");
				break;
			}
			case 7665: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000408);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000438, EnemyEtis, "EnemyEtis-10000438");
				break;
			}
			case 7685: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000409);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000439, EnemyEtis, "EnemyEtis-10000439");
				break;
			}
			case 7705: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000410);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000440, EnemyEtis, "EnemyEtis-10000440");
				break;
			}
			case 7725: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000411);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000441, EnemyEtis, "EnemyEtis-10000441");
				break;
			}
			case 7745: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000412);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000442, EnemyEtis, "EnemyEtis-10000442");
				break;
			}
			case 7765: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000413);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000443, EnemyEtis, "EnemyEtis-10000443");
				break;
			}
			case 7785: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000414);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000444, EnemyEtis, "EnemyEtis-10000444");
				break;
			}
			case 7805: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000415);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000445, EnemyEtis, "EnemyEtis-10000445");
				break;
			}
			case 7825: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000416);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000446, EnemyEtis, "EnemyEtis-10000446");
				break;
			}
			case 7845: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000417);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000447, EnemyEtis, "EnemyEtis-10000447");
				break;
			}
			case 7865: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000418);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000448, EnemyEtis, "EnemyEtis-10000448");
				break;
			}
			case 7885: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000419);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000449, EnemyEtis, "EnemyEtis-10000449");
				break;
			}
			case 7900: {
				requestActor(10001129, EnemyDrastea, "EnemyDrastea-10001129");
				break;
			}
			case 7905: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000420);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000450, EnemyEtis, "EnemyEtis-10000450");
				break;
			}
			case 7925: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000421);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000451, EnemyEtis, "EnemyEtis-10000451");
				break;
			}
			case 7945: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000422);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000452, EnemyEtis, "EnemyEtis-10000452");
				break;
			}
			case 7965: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000423);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000453, EnemyEtis, "EnemyEtis-10000453");
				break;
			}
			case 7985: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000424);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000454, EnemyEtis, "EnemyEtis-10000454");
				break;
			}
			case 8005: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000425);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000455, EnemyEtis, "EnemyEtis-10000455");
				break;
			}
			case 8025: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000426);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000456, EnemyEtis, "EnemyEtis-10000456");
				break;
			}
			case 8045: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000427);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000457, EnemyEtis, "EnemyEtis-10000457");
				break;
			}
			case 8065: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000428);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000458, EnemyEtis, "EnemyEtis-10000458");
				break;
			}
			case 8085: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000429);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000459, EnemyEtis, "EnemyEtis-10000459");
				break;
			}
			case 8100: {
				appendChild(receiveScene(10000002));
				break;
			}
			case 8105: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000430);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000460, EnemyEtis, "EnemyEtis-10000460");
				break;
			}
			case 8125: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000431);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000461, EnemyEtis, "EnemyEtis-10000461");
				break;
			}
			case 8145: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000432);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000462, EnemyEtis, "EnemyEtis-10000462");
				break;
			}
			case 8165: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000433);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000463, EnemyEtis, "EnemyEtis-10000463");
				break;
			}
			case 8185: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000434);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000464, EnemyEtis, "EnemyEtis-10000464");
				break;
			}
			case 8205: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000435);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000465, EnemyEtis, "EnemyEtis-10000465");
				break;
			}
			case 8225: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000436);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000466, EnemyEtis, "EnemyEtis-10000466");
				break;
			}
			case 8245: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000437);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000467, EnemyEtis, "EnemyEtis-10000467");
				break;
			}
			case 8265: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000438);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000468, EnemyEtis, "EnemyEtis-10000468");
				break;
			}
			case 8285: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000439);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000469, EnemyEtis, "EnemyEtis-10000469");
				break;
			}
			case 8305: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000440);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000470, EnemyEtis, "EnemyEtis-10000470");
				break;
			}
			case 8325: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000441);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000471, EnemyEtis, "EnemyEtis-10000471");
				break;
			}
			case 8345: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000442);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000472, EnemyEtis, "EnemyEtis-10000472");
				break;
			}
			case 8365: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000443);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000473, EnemyEtis, "EnemyEtis-10000473");
				break;
			}
			case 8385: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000444);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000474, EnemyEtis, "EnemyEtis-10000474");
				break;
			}
			case 8405: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000445);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000475, EnemyEtis, "EnemyEtis-10000475");
				break;
			}
			case 8425: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000446);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000476, EnemyEtis, "EnemyEtis-10000476");
				break;
			}
			case 8445: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000447);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000477, EnemyEtis, "EnemyEtis-10000477");
				break;
			}
			case 8465: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000448);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000478, EnemyEtis, "EnemyEtis-10000478");
				break;
			}
			case 8485: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000449);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000479, EnemyEtis, "EnemyEtis-10000479");
				break;
			}
			case 8500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(10001129);
				bringSceneMediator()->appendGroupChild(p);
				break;
			}
			case 8505: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000450);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000480, EnemyEtis, "EnemyEtis-10000480");
				break;
			}
			case 8525: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000451);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000481, EnemyEtis, "EnemyEtis-10000481");
				break;
			}
			case 8545: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000452);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000482, EnemyEtis, "EnemyEtis-10000482");
				break;
			}
			case 8565: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000453);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000483, EnemyEtis, "EnemyEtis-10000483");
				break;
			}
			case 8585: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000454);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000484, EnemyEtis, "EnemyEtis-10000484");
				break;
			}
			case 8605: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000455);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000485, EnemyEtis, "EnemyEtis-10000485");
				break;
			}
			case 8625: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000456);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000486, EnemyEtis, "EnemyEtis-10000486");
				break;
			}
			case 8645: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000457);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000487, EnemyEtis, "EnemyEtis-10000487");
				break;
			}
			case 8665: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000458);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000488, EnemyEtis, "EnemyEtis-10000488");
				break;
			}
			case 8685: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000459);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000489, EnemyEtis, "EnemyEtis-10000489");
				break;
			}
			case 8705: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000460);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000490, EnemyEtis, "EnemyEtis-10000490");
				break;
			}
			case 8725: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000461);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000491, EnemyEtis, "EnemyEtis-10000491");
				break;
			}
			case 8745: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000462);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000492, EnemyEtis, "EnemyEtis-10000492");
				break;
			}
			case 8765: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000463);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000493, EnemyEtis, "EnemyEtis-10000493");
				break;
			}
			case 8785: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000464);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000494, EnemyEtis, "EnemyEtis-10000494");
				break;
			}
			case 8805: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000465);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000495, EnemyEtis, "EnemyEtis-10000495");
				break;
			}
			case 8825: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000466);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000496, EnemyEtis, "EnemyEtis-10000496");
				break;
			}
			case 8845: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000467);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000497, EnemyEtis, "EnemyEtis-10000497");
				break;
			}
			case 8865: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000468);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000498, EnemyEtis, "EnemyEtis-10000498");
				break;
			}
			case 8885: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000469);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000499, EnemyEtis, "EnemyEtis-10000499");
				break;
			}
			case 8905: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000470);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000500, EnemyEtis, "EnemyEtis-10000500");
				break;
			}
			case 8925: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000471);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000501, EnemyEtis, "EnemyEtis-10000501");
				break;
			}
			case 8945: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000472);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000502, EnemyEtis, "EnemyEtis-10000502");
				break;
			}
			case 8965: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000473);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000503, EnemyEtis, "EnemyEtis-10000503");
				break;
			}
			case 8985: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000474);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000504, EnemyEtis, "EnemyEtis-10000504");
				break;
			}
			case 9005: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000475);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000505, EnemyEtis, "EnemyEtis-10000505");
				break;
			}
			case 9025: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000476);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000506, EnemyEtis, "EnemyEtis-10000506");
				break;
			}
			case 9045: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000477);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000507, EnemyEtis, "EnemyEtis-10000507");
				break;
			}
			case 9065: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000478);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000508, EnemyEtis, "EnemyEtis-10000508");
				break;
			}
			case 9085: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000479);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000509, EnemyEtis, "EnemyEtis-10000509");
				break;
			}
			case 9105: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000480);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000510, EnemyEtis, "EnemyEtis-10000510");
				break;
			}
			case 9125: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000481);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000511, EnemyEtis, "EnemyEtis-10000511");
				break;
			}
			case 9145: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000482);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000512, EnemyEtis, "EnemyEtis-10000512");
				break;
			}
			case 9165: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000483);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000513, EnemyEtis, "EnemyEtis-10000513");
				break;
			}
			case 9185: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000484);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000514, EnemyEtis, "EnemyEtis-10000514");
				break;
			}
			case 9205: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000485);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000515, EnemyEtis, "EnemyEtis-10000515");
				break;
			}
			case 9225: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000486);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000516, EnemyEtis, "EnemyEtis-10000516");
				break;
			}
			case 9245: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000487);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000517, EnemyEtis, "EnemyEtis-10000517");
				break;
			}
			case 9265: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000488);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000518, EnemyEtis, "EnemyEtis-10000518");
				break;
			}
			case 9285: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000489);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000519, EnemyEtis, "EnemyEtis-10000519");
				break;
			}
			case 9305: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000490);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000520, EnemyEtis, "EnemyEtis-10000520");
				break;
			}
			case 9325: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000491);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000521, EnemyEtis, "EnemyEtis-10000521");
				break;
			}
			case 9345: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000492);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000522, EnemyEtis, "EnemyEtis-10000522");
				break;
			}
			case 9365: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000493);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000523, EnemyEtis, "EnemyEtis-10000523");
				break;
			}
			case 9385: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000494);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000524, EnemyEtis, "EnemyEtis-10000524");
				break;
			}
			case 9405: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000495);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000525, EnemyEtis, "EnemyEtis-10000525");
				break;
			}
			case 9425: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000496);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000526, EnemyEtis, "EnemyEtis-10000526");
				break;
			}
			case 9445: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000497);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000527, EnemyEtis, "EnemyEtis-10000527");
				break;
			}
			case 9465: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000498);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000528, EnemyEtis, "EnemyEtis-10000528");
				break;
			}
			case 9485: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000499);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000529, EnemyEtis, "EnemyEtis-10000529");
				break;
			}
			case 9505: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000500);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000530, EnemyEtis, "EnemyEtis-10000530");
				break;
			}
			case 9525: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000501);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000531, EnemyEtis, "EnemyEtis-10000531");
				break;
			}
			case 9545: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000502);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000532, EnemyEtis, "EnemyEtis-10000532");
				break;
			}
			case 9565: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000503);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000533, EnemyEtis, "EnemyEtis-10000533");
				break;
			}
			case 9585: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000504);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000534, EnemyEtis, "EnemyEtis-10000534");
				break;
			}
			case 9605: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000505);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000535, EnemyEtis, "EnemyEtis-10000535");
				break;
			}
			case 9625: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000506);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000536, EnemyEtis, "EnemyEtis-10000536");
				break;
			}
			case 9645: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000507);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000537, EnemyEtis, "EnemyEtis-10000537");
				break;
			}
			case 9665: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000508);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000538, EnemyEtis, "EnemyEtis-10000538");
				break;
			}
			case 9685: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000509);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000539, EnemyEtis, "EnemyEtis-10000539");
				break;
			}
			case 9705: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000510);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000540, EnemyEtis, "EnemyEtis-10000540");
				break;
			}
			case 9725: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000511);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000541, EnemyEtis, "EnemyEtis-10000541");
				break;
			}
			case 9745: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000512);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000542, EnemyEtis, "EnemyEtis-10000542");
				break;
			}
			case 9765: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000513);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000543, EnemyEtis, "EnemyEtis-10000543");
				break;
			}
			case 9785: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000514);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000544, EnemyEtis, "EnemyEtis-10000544");
				break;
			}
			case 9805: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000515);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000545, EnemyEtis, "EnemyEtis-10000545");
				break;
			}
			case 9825: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000516);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000546, EnemyEtis, "EnemyEtis-10000546");
				break;
			}
			case 9845: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000517);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000547, EnemyEtis, "EnemyEtis-10000547");
				break;
			}
			case 9865: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000518);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000548, EnemyEtis, "EnemyEtis-10000548");
				break;
			}
			case 9885: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000519);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000549, EnemyEtis, "EnemyEtis-10000549");
				break;
			}
			case 9900: {
				requestActor(10001130, EnemyDrastea, "EnemyDrastea-10001130");
				break;
			}
			case 9905: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000520);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000550, EnemyEtis, "EnemyEtis-10000550");
				break;
			}
			case 9925: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000521);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000551, EnemyEtis, "EnemyEtis-10000551");
				break;
			}
			case 9945: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000522);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000552, EnemyEtis, "EnemyEtis-10000552");
				break;
			}
			case 9965: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000523);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000553, EnemyEtis, "EnemyEtis-10000553");
				break;
			}
			case 9985: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000524);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000554, EnemyEtis, "EnemyEtis-10000554");
				break;
			}
			case 10005: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000525);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000555, EnemyEtis, "EnemyEtis-10000555");
				break;
			}
			case 10025: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000526);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000556, EnemyEtis, "EnemyEtis-10000556");
				break;
			}
			case 10045: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000527);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000557, EnemyEtis, "EnemyEtis-10000557");
				break;
			}
			case 10065: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000528);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000558, EnemyEtis, "EnemyEtis-10000558");
				break;
			}
			case 10085: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000529);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000559, EnemyEtis, "EnemyEtis-10000559");
				break;
			}
			case 10105: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000530);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000560, EnemyEtis, "EnemyEtis-10000560");
				break;
			}
			case 10125: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000531);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000561, EnemyEtis, "EnemyEtis-10000561");
				break;
			}
			case 10145: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000532);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000562, EnemyEtis, "EnemyEtis-10000562");
				break;
			}
			case 10165: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000533);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000563, EnemyEtis, "EnemyEtis-10000563");
				break;
			}
			case 10185: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000534);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000564, EnemyEtis, "EnemyEtis-10000564");
				break;
			}
			case 10205: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000535);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000565, EnemyEtis, "EnemyEtis-10000565");
				break;
			}
			case 10225: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000536);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000566, EnemyEtis, "EnemyEtis-10000566");
				break;
			}
			case 10245: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000537);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000567, EnemyEtis, "EnemyEtis-10000567");
				break;
			}
			case 10265: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000538);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000568, EnemyEtis, "EnemyEtis-10000568");
				break;
			}
			case 10285: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000539);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000569, EnemyEtis, "EnemyEtis-10000569");
				break;
			}
			case 10305: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000540);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000570, EnemyEtis, "EnemyEtis-10000570");
				break;
			}
			case 10325: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000541);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000571, EnemyEtis, "EnemyEtis-10000571");
				break;
			}
			case 10345: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000542);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000572, EnemyEtis, "EnemyEtis-10000572");
				break;
			}
			case 10365: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000543);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000573, EnemyEtis, "EnemyEtis-10000573");
				break;
			}
			case 10385: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000544);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000574, EnemyEtis, "EnemyEtis-10000574");
				break;
			}
			case 10405: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000545);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000575, EnemyEtis, "EnemyEtis-10000575");
				break;
			}
			case 10425: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000546);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000576, EnemyEtis, "EnemyEtis-10000576");
				break;
			}
			case 10445: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000547);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000577, EnemyEtis, "EnemyEtis-10000577");
				break;
			}
			case 10465: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000548);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000578, EnemyEtis, "EnemyEtis-10000578");
				break;
			}
			case 10485: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000549);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000579, EnemyEtis, "EnemyEtis-10000579");
				break;
			}
			case 10500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(10001130);
				bringSceneMediator()->appendGroupChild(p);
				break;
			}
			case 10505: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000550);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000580, EnemyEtis, "EnemyEtis-10000580");
				break;
			}
			case 10525: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000551);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000581, EnemyEtis, "EnemyEtis-10000581");
				break;
			}
			case 10545: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000552);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000582, EnemyEtis, "EnemyEtis-10000582");
				break;
			}
			case 10565: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000553);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000583, EnemyEtis, "EnemyEtis-10000583");
				break;
			}
			case 10585: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000554);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000584, EnemyEtis, "EnemyEtis-10000584");
				break;
			}
			case 10605: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000555);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000585, EnemyEtis, "EnemyEtis-10000585");
				break;
			}
			case 10625: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000556);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000586, EnemyEtis, "EnemyEtis-10000586");
				break;
			}
			case 10645: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000557);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000587, EnemyEtis, "EnemyEtis-10000587");
				break;
			}
			case 10665: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000558);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000588, EnemyEtis, "EnemyEtis-10000588");
				break;
			}
			case 10685: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000559);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000589, EnemyEtis, "EnemyEtis-10000589");
				break;
			}
			case 10705: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000560);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000590, EnemyEtis, "EnemyEtis-10000590");
				break;
			}
			case 10725: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000561);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000591, EnemyEtis, "EnemyEtis-10000591");
				break;
			}
			case 10745: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000562);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000592, EnemyEtis, "EnemyEtis-10000592");
				break;
			}
			case 10765: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000563);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000593, EnemyEtis, "EnemyEtis-10000593");
				break;
			}
			case 10785: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000564);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000594, EnemyEtis, "EnemyEtis-10000594");
				break;
			}
			case 10805: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000565);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000595, EnemyEtis, "EnemyEtis-10000595");
				break;
			}
			case 10825: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000566);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000596, EnemyEtis, "EnemyEtis-10000596");
				break;
			}
			case 10845: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000567);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000597, EnemyEtis, "EnemyEtis-10000597");
				break;
			}
			case 10865: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000568);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000598, EnemyEtis, "EnemyEtis-10000598");
				break;
			}
			case 10885: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000569);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000599, EnemyEtis, "EnemyEtis-10000599");
				break;
			}
			case 10905: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000570);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000600, EnemyEtis, "EnemyEtis-10000600");
				break;
			}
			case 10925: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000571);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000601, EnemyEtis, "EnemyEtis-10000601");
				break;
			}
			case 10945: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000572);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000602, EnemyEtis, "EnemyEtis-10000602");
				break;
			}
			case 10965: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000573);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000603, EnemyEtis, "EnemyEtis-10000603");
				break;
			}
			case 10985: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000574);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000604, EnemyEtis, "EnemyEtis-10000604");
				break;
			}
			case 11005: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000575);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000605, EnemyEtis, "EnemyEtis-10000605");
				break;
			}
			case 11025: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000576);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000606, EnemyEtis, "EnemyEtis-10000606");
				break;
			}
			case 11045: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000577);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000607, EnemyEtis, "EnemyEtis-10000607");
				break;
			}
			case 11065: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000578);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000608, EnemyEtis, "EnemyEtis-10000608");
				break;
			}
			case 11085: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000579);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000609, EnemyEtis, "EnemyEtis-10000609");
				break;
			}
			case 11105: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000580);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000610, EnemyEtis, "EnemyEtis-10000610");
				break;
			}
			case 11125: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000581);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000611, EnemyEtis, "EnemyEtis-10000611");
				break;
			}
			case 11145: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000582);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000612, EnemyEtis, "EnemyEtis-10000612");
				break;
			}
			case 11165: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000583);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000613, EnemyEtis, "EnemyEtis-10000613");
				break;
			}
			case 11185: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000584);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000614, EnemyEtis, "EnemyEtis-10000614");
				break;
			}
			case 11205: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000585);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000615, EnemyEtis, "EnemyEtis-10000615");
				break;
			}
			case 11225: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000586);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000616, EnemyEtis, "EnemyEtis-10000616");
				break;
			}
			case 11245: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000587);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000617, EnemyEtis, "EnemyEtis-10000617");
				break;
			}
			case 11265: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000588);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000618, EnemyEtis, "EnemyEtis-10000618");
				break;
			}
			case 11285: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000589);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000619, EnemyEtis, "EnemyEtis-10000619");
				break;
			}
			case 11305: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000590);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000620, EnemyEtis, "EnemyEtis-10000620");
				break;
			}
			case 11325: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000591);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000621, EnemyEtis, "EnemyEtis-10000621");
				break;
			}
			case 11345: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000592);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000622, EnemyEtis, "EnemyEtis-10000622");
				break;
			}
			case 11365: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000593);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000623, EnemyEtis, "EnemyEtis-10000623");
				break;
			}
			case 11385: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000594);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000624, EnemyEtis, "EnemyEtis-10000624");
				break;
			}
			case 11405: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000595);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000625, EnemyEtis, "EnemyEtis-10000625");
				break;
			}
			case 11425: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000596);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000626, EnemyEtis, "EnemyEtis-10000626");
				break;
			}
			case 11445: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000597);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000627, EnemyEtis, "EnemyEtis-10000627");
				break;
			}
			case 11465: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000598);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000628, EnemyEtis, "EnemyEtis-10000628");
				break;
			}
			case 11485: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000599);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000629, EnemyEtis, "EnemyEtis-10000629");
				break;
			}
			case 11505: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000600);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000630, EnemyEtis, "EnemyEtis-10000630");
				break;
			}
			case 11525: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000601);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000631, EnemyEtis, "EnemyEtis-10000631");
				break;
			}
			case 11545: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000602);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000632, EnemyEtis, "EnemyEtis-10000632");
				break;
			}
			case 11565: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000603);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000633, EnemyEtis, "EnemyEtis-10000633");
				break;
			}
			case 11585: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000604);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000634, EnemyEtis, "EnemyEtis-10000634");
				break;
			}
			case 11605: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000605);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000635, EnemyEtis, "EnemyEtis-10000635");
				break;
			}
			case 11625: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000606);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000636, EnemyEtis, "EnemyEtis-10000636");
				break;
			}
			case 11645: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000607);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000637, EnemyEtis, "EnemyEtis-10000637");
				break;
			}
			case 11665: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000608);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000638, EnemyEtis, "EnemyEtis-10000638");
				break;
			}
			case 11685: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000609);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000639, EnemyEtis, "EnemyEtis-10000639");
				break;
			}
			case 11705: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000610);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000640, EnemyEtis, "EnemyEtis-10000640");
				break;
			}
			case 11725: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000611);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000641, EnemyEtis, "EnemyEtis-10000641");
				break;
			}
			case 11745: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000612);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000642, EnemyEtis, "EnemyEtis-10000642");
				break;
			}
			case 11765: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000613);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000643, EnemyEtis, "EnemyEtis-10000643");
				break;
			}
			case 11785: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000614);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000644, EnemyEtis, "EnemyEtis-10000644");
				break;
			}
			case 11805: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000615);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000645, EnemyEtis, "EnemyEtis-10000645");
				break;
			}
			case 11825: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000616);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000646, EnemyEtis, "EnemyEtis-10000646");
				break;
			}
			case 11845: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000617);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000647, EnemyEtis, "EnemyEtis-10000647");
				break;
			}
			case 11865: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000618);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000648, EnemyEtis, "EnemyEtis-10000648");
				break;
			}
			case 11885: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000619);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000649, EnemyEtis, "EnemyEtis-10000649");
				break;
			}
			case 11900: {
				requestActor(10001131, EnemyDrastea, "EnemyDrastea-10001131");
				break;
			}
			case 11905: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000620);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000650, EnemyEtis, "EnemyEtis-10000650");
				break;
			}
			case 11925: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000621);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000651, EnemyEtis, "EnemyEtis-10000651");
				break;
			}
			case 11945: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000622);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000652, EnemyEtis, "EnemyEtis-10000652");
				break;
			}
			case 11965: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000623);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000653, EnemyEtis, "EnemyEtis-10000653");
				break;
			}
			case 11985: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000624);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000654, EnemyEtis, "EnemyEtis-10000654");
				break;
			}
			case 12005: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000625);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000655, EnemyEtis, "EnemyEtis-10000655");
				break;
			}
			case 12025: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000626);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000656, EnemyEtis, "EnemyEtis-10000656");
				break;
			}
			case 12045: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000627);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000657, EnemyEtis, "EnemyEtis-10000657");
				break;
			}
			case 12065: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000628);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000658, EnemyEtis, "EnemyEtis-10000658");
				break;
			}
			case 12085: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000629);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000659, EnemyEtis, "EnemyEtis-10000659");
				break;
			}
			case 12105: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000630);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000660, EnemyEtis, "EnemyEtis-10000660");
				break;
			}
			case 12125: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000631);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000661, EnemyEtis, "EnemyEtis-10000661");
				break;
			}
			case 12145: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000632);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000662, EnemyEtis, "EnemyEtis-10000662");
				break;
			}
			case 12165: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000633);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000663, EnemyEtis, "EnemyEtis-10000663");
				break;
			}
			case 12185: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000634);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000664, EnemyEtis, "EnemyEtis-10000664");
				break;
			}
			case 12205: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000635);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000665, EnemyEtis, "EnemyEtis-10000665");
				break;
			}
			case 12225: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000636);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000666, EnemyEtis, "EnemyEtis-10000666");
				break;
			}
			case 12245: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000637);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000667, EnemyEtis, "EnemyEtis-10000667");
				break;
			}
			case 12265: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000638);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000668, EnemyEtis, "EnemyEtis-10000668");
				break;
			}
			case 12285: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000639);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000669, EnemyEtis, "EnemyEtis-10000669");
				break;
			}
			case 12305: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000640);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000670, EnemyEtis, "EnemyEtis-10000670");
				break;
			}
			case 12325: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000641);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000671, EnemyEtis, "EnemyEtis-10000671");
				break;
			}
			case 12345: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000642);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000672, EnemyEtis, "EnemyEtis-10000672");
				break;
			}
			case 12365: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000643);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000673, EnemyEtis, "EnemyEtis-10000673");
				break;
			}
			case 12385: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000644);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000674, EnemyEtis, "EnemyEtis-10000674");
				break;
			}
			case 12405: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000645);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000675, EnemyEtis, "EnemyEtis-10000675");
				break;
			}
			case 12425: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000646);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000676, EnemyEtis, "EnemyEtis-10000676");
				break;
			}
			case 12445: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000647);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000677, EnemyEtis, "EnemyEtis-10000677");
				break;
			}
			case 12465: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000648);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000678, EnemyEtis, "EnemyEtis-10000678");
				break;
			}
			case 12485: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000649);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000679, EnemyEtis, "EnemyEtis-10000679");
				break;
			}
			case 12500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(10001131);
				bringSceneMediator()->appendGroupChild(p);
				break;
			}
			case 12505: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000650);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000680, EnemyEtis, "EnemyEtis-10000680");
				break;
			}
			case 12525: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000651);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000681, EnemyEtis, "EnemyEtis-10000681");
				break;
			}
			case 12545: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000652);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000682, EnemyEtis, "EnemyEtis-10000682");
				break;
			}
			case 12565: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000653);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000683, EnemyEtis, "EnemyEtis-10000683");
				break;
			}
			case 12585: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000654);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000684, EnemyEtis, "EnemyEtis-10000684");
				break;
			}
			case 12605: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000655);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000685, EnemyEtis, "EnemyEtis-10000685");
				break;
			}
			case 12625: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000656);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000686, EnemyEtis, "EnemyEtis-10000686");
				break;
			}
			case 12645: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000657);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000687, EnemyEtis, "EnemyEtis-10000687");
				break;
			}
			case 12665: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000658);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000688, EnemyEtis, "EnemyEtis-10000688");
				break;
			}
			case 12685: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000659);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000689, EnemyEtis, "EnemyEtis-10000689");
				break;
			}
			case 12705: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000660);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000690, EnemyEtis, "EnemyEtis-10000690");
				break;
			}
			case 12725: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000661);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000691, EnemyEtis, "EnemyEtis-10000691");
				break;
			}
			case 12745: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000662);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000692, EnemyEtis, "EnemyEtis-10000692");
				break;
			}
			case 12765: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000663);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000693, EnemyEtis, "EnemyEtis-10000693");
				break;
			}
			case 12785: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000664);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000694, EnemyEtis, "EnemyEtis-10000694");
				break;
			}
			case 12805: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000665);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000695, EnemyEtis, "EnemyEtis-10000695");
				break;
			}
			case 12825: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000666);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000696, EnemyEtis, "EnemyEtis-10000696");
				break;
			}
			case 12845: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000667);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000697, EnemyEtis, "EnemyEtis-10000697");
				break;
			}
			case 12865: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000668);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000698, EnemyEtis, "EnemyEtis-10000698");
				break;
			}
			case 12885: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000669);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000699, EnemyEtis, "EnemyEtis-10000699");
				break;
			}
			case 12905: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000670);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000700, EnemyEtis, "EnemyEtis-10000700");
				break;
			}
			case 12925: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000671);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000701, EnemyEtis, "EnemyEtis-10000701");
				break;
			}
			case 12945: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000672);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000702, EnemyEtis, "EnemyEtis-10000702");
				break;
			}
			case 12965: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000673);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000703, EnemyEtis, "EnemyEtis-10000703");
				break;
			}
			case 12985: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000674);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000704, EnemyEtis, "EnemyEtis-10000704");
				break;
			}
			case 13005: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000675);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000705, EnemyEtis, "EnemyEtis-10000705");
				break;
			}
			case 13025: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000676);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000706, EnemyEtis, "EnemyEtis-10000706");
				break;
			}
			case 13045: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000677);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000707, EnemyEtis, "EnemyEtis-10000707");
				break;
			}
			case 13065: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000678);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000708, EnemyEtis, "EnemyEtis-10000708");
				break;
			}
			case 13085: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000679);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000709, EnemyEtis, "EnemyEtis-10000709");
				break;
			}
			case 13105: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000680);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000710, EnemyEtis, "EnemyEtis-10000710");
				break;
			}
			case 13125: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000681);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000711, EnemyEtis, "EnemyEtis-10000711");
				break;
			}
			case 13145: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000682);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000712, EnemyEtis, "EnemyEtis-10000712");
				break;
			}
			case 13165: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000683);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000713, EnemyEtis, "EnemyEtis-10000713");
				break;
			}
			case 13185: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000684);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000714, EnemyEtis, "EnemyEtis-10000714");
				break;
			}
			case 13205: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000685);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000715, EnemyEtis, "EnemyEtis-10000715");
				break;
			}
			case 13225: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000686);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000716, EnemyEtis, "EnemyEtis-10000716");
				break;
			}
			case 13245: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000687);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000717, EnemyEtis, "EnemyEtis-10000717");
				break;
			}
			case 13265: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000688);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000718, EnemyEtis, "EnemyEtis-10000718");
				break;
			}
			case 13285: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000689);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000719, EnemyEtis, "EnemyEtis-10000719");
				break;
			}
			case 13305: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000690);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000720, EnemyEtis, "EnemyEtis-10000720");
				break;
			}
			case 13325: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000691);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000721, EnemyEtis, "EnemyEtis-10000721");
				break;
			}
			case 13345: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000692);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000722, EnemyEtis, "EnemyEtis-10000722");
				break;
			}
			case 13365: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000693);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000723, EnemyEtis, "EnemyEtis-10000723");
				break;
			}
			case 13385: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000694);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000724, EnemyEtis, "EnemyEtis-10000724");
				break;
			}
			case 13405: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000695);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000725, EnemyEtis, "EnemyEtis-10000725");
				break;
			}
			case 13425: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000696);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000726, EnemyEtis, "EnemyEtis-10000726");
				break;
			}
			case 13445: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000697);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000727, EnemyEtis, "EnemyEtis-10000727");
				break;
			}
			case 13465: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000698);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000728, EnemyEtis, "EnemyEtis-10000728");
				break;
			}
			case 13485: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000699);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000729, EnemyEtis, "EnemyEtis-10000729");
				break;
			}
			case 13505: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000700);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000730, EnemyEtis, "EnemyEtis-10000730");
				break;
			}
			case 13525: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000701);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000731, EnemyEtis, "EnemyEtis-10000731");
				break;
			}
			case 13545: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000702);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000732, EnemyEtis, "EnemyEtis-10000732");
				break;
			}
			case 13565: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000703);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000733, EnemyEtis, "EnemyEtis-10000733");
				break;
			}
			case 13585: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000704);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000734, EnemyEtis, "EnemyEtis-10000734");
				break;
			}
			case 13605: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000705);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000735, EnemyEtis, "EnemyEtis-10000735");
				break;
			}
			case 13625: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000706);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000736, EnemyEtis, "EnemyEtis-10000736");
				break;
			}
			case 13645: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000707);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000737, EnemyEtis, "EnemyEtis-10000737");
				break;
			}
			case 13665: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000708);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000738, EnemyEtis, "EnemyEtis-10000738");
				break;
			}
			case 13685: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000709);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000739, EnemyEtis, "EnemyEtis-10000739");
				break;
			}
			case 13705: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000710);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000740, EnemyEtis, "EnemyEtis-10000740");
				break;
			}
			case 13725: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000711);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000741, EnemyEtis, "EnemyEtis-10000741");
				break;
			}
			case 13745: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000712);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000742, EnemyEtis, "EnemyEtis-10000742");
				break;
			}
			case 13765: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000713);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000743, EnemyEtis, "EnemyEtis-10000743");
				break;
			}
			case 13785: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000714);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000744, EnemyEtis, "EnemyEtis-10000744");
				break;
			}
			case 13805: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000715);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000745, EnemyEtis, "EnemyEtis-10000745");
				break;
			}
			case 13825: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000716);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000746, EnemyEtis, "EnemyEtis-10000746");
				break;
			}
			case 13845: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000717);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000747, EnemyEtis, "EnemyEtis-10000747");
				break;
			}
			case 13865: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000718);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000748, EnemyEtis, "EnemyEtis-10000748");
				break;
			}
			case 13885: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000719);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000749, EnemyEtis, "EnemyEtis-10000749");
				break;
			}
			case 13900: {
				requestActor(10001132, EnemyDrastea, "EnemyDrastea-10001132");
				break;
			}
			case 13905: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000720);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000750, EnemyEtis, "EnemyEtis-10000750");
				break;
			}
			case 13925: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000721);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000751, EnemyEtis, "EnemyEtis-10000751");
				break;
			}
			case 13945: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000722);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000752, EnemyEtis, "EnemyEtis-10000752");
				break;
			}
			case 13965: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000723);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000753, EnemyEtis, "EnemyEtis-10000753");
				break;
			}
			case 13985: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000724);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000754, EnemyEtis, "EnemyEtis-10000754");
				break;
			}
			case 14005: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000725);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000755, EnemyEtis, "EnemyEtis-10000755");
				break;
			}
			case 14025: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000726);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000756, EnemyEtis, "EnemyEtis-10000756");
				break;
			}
			case 14045: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000727);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000757, EnemyEtis, "EnemyEtis-10000757");
				break;
			}
			case 14065: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000728);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000758, EnemyEtis, "EnemyEtis-10000758");
				break;
			}
			case 14085: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000729);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000759, EnemyEtis, "EnemyEtis-10000759");
				break;
			}
			case 14105: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000730);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000760, EnemyEtis, "EnemyEtis-10000760");
				break;
			}
			case 14125: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000731);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000761, EnemyEtis, "EnemyEtis-10000761");
				break;
			}
			case 14145: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000732);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000762, EnemyEtis, "EnemyEtis-10000762");
				break;
			}
			case 14165: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000733);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000763, EnemyEtis, "EnemyEtis-10000763");
				break;
			}
			case 14185: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000734);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000764, EnemyEtis, "EnemyEtis-10000764");
				break;
			}
			case 14205: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000735);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000765, EnemyEtis, "EnemyEtis-10000765");
				break;
			}
			case 14225: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000736);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000766, EnemyEtis, "EnemyEtis-10000766");
				break;
			}
			case 14245: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000737);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000767, EnemyEtis, "EnemyEtis-10000767");
				break;
			}
			case 14265: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000738);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000768, EnemyEtis, "EnemyEtis-10000768");
				break;
			}
			case 14285: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000739);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000769, EnemyEtis, "EnemyEtis-10000769");
				break;
			}
			case 14305: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000740);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000770, EnemyEtis, "EnemyEtis-10000770");
				break;
			}
			case 14325: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000741);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000771, EnemyEtis, "EnemyEtis-10000771");
				break;
			}
			case 14345: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000742);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000772, EnemyEtis, "EnemyEtis-10000772");
				break;
			}
			case 14365: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000743);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000773, EnemyEtis, "EnemyEtis-10000773");
				break;
			}
			case 14385: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000744);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000774, EnemyEtis, "EnemyEtis-10000774");
				break;
			}
			case 14405: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000745);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000775, EnemyEtis, "EnemyEtis-10000775");
				break;
			}
			case 14425: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000746);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000776, EnemyEtis, "EnemyEtis-10000776");
				break;
			}
			case 14445: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000747);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000777, EnemyEtis, "EnemyEtis-10000777");
				break;
			}
			case 14465: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000748);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000778, EnemyEtis, "EnemyEtis-10000778");
				break;
			}
			case 14485: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000749);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000779, EnemyEtis, "EnemyEtis-10000779");
				break;
			}
			case 14500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(10001132);
				bringSceneMediator()->appendGroupChild(p);
				break;
			}
			case 14505: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000750);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000780, EnemyEtis, "EnemyEtis-10000780");
				break;
			}
			case 14525: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000751);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000781, EnemyEtis, "EnemyEtis-10000781");
				break;
			}
			case 14545: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000752);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000782, EnemyEtis, "EnemyEtis-10000782");
				break;
			}
			case 14565: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000753);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000783, EnemyEtis, "EnemyEtis-10000783");
				break;
			}
			case 14585: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000754);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000784, EnemyEtis, "EnemyEtis-10000784");
				break;
			}
			case 14605: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000755);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000785, EnemyEtis, "EnemyEtis-10000785");
				break;
			}
			case 14625: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000756);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000786, EnemyEtis, "EnemyEtis-10000786");
				break;
			}
			case 14645: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000757);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000787, EnemyEtis, "EnemyEtis-10000787");
				break;
			}
			case 14665: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000758);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000788, EnemyEtis, "EnemyEtis-10000788");
				break;
			}
			case 14685: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000759);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000789, EnemyEtis, "EnemyEtis-10000789");
				break;
			}
			case 14705: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000760);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000790, EnemyEtis, "EnemyEtis-10000790");
				break;
			}
			case 14725: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000761);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000791, EnemyEtis, "EnemyEtis-10000791");
				break;
			}
			case 14745: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000762);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000792, EnemyEtis, "EnemyEtis-10000792");
				break;
			}
			case 14765: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000763);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000793, EnemyEtis, "EnemyEtis-10000793");
				break;
			}
			case 14785: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000764);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000794, EnemyEtis, "EnemyEtis-10000794");
				break;
			}
			case 14805: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000765);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000795, EnemyEtis, "EnemyEtis-10000795");
				break;
			}
			case 14825: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000766);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000796, EnemyEtis, "EnemyEtis-10000796");
				break;
			}
			case 14845: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000767);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000797, EnemyEtis, "EnemyEtis-10000797");
				break;
			}
			case 14865: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000768);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000798, EnemyEtis, "EnemyEtis-10000798");
				break;
			}
			case 14885: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000769);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000799, EnemyEtis, "EnemyEtis-10000799");
				break;
			}
			case 14905: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000770);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000800, EnemyEtis, "EnemyEtis-10000800");
				break;
			}
			case 14925: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000771);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000801, EnemyEtis, "EnemyEtis-10000801");
				break;
			}
			case 14945: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000772);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000802, EnemyEtis, "EnemyEtis-10000802");
				break;
			}
			case 14965: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000773);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000803, EnemyEtis, "EnemyEtis-10000803");
				break;
			}
			case 14985: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000774);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000804, EnemyEtis, "EnemyEtis-10000804");
				break;
			}
			case 15005: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000775);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000805, EnemyEtis, "EnemyEtis-10000805");
				break;
			}
			case 15025: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000776);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000806, EnemyEtis, "EnemyEtis-10000806");
				break;
			}
			case 15045: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000777);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000807, EnemyEtis, "EnemyEtis-10000807");
				break;
			}
			case 15065: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000778);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000808, EnemyEtis, "EnemyEtis-10000808");
				break;
			}
			case 15085: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000779);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000809, EnemyEtis, "EnemyEtis-10000809");
				break;
			}
			case 15105: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000780);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000810, EnemyEtis, "EnemyEtis-10000810");
				break;
			}
			case 15125: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000781);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000811, EnemyEtis, "EnemyEtis-10000811");
				break;
			}
			case 15145: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000782);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000812, EnemyEtis, "EnemyEtis-10000812");
				break;
			}
			case 15165: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000783);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000813, EnemyEtis, "EnemyEtis-10000813");
				break;
			}
			case 15185: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000784);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000814, EnemyEtis, "EnemyEtis-10000814");
				break;
			}
			case 15205: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000785);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000815, EnemyEtis, "EnemyEtis-10000815");
				break;
			}
			case 15225: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000786);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000816, EnemyEtis, "EnemyEtis-10000816");
				break;
			}
			case 15245: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000787);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000817, EnemyEtis, "EnemyEtis-10000817");
				break;
			}
			case 15265: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000788);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000818, EnemyEtis, "EnemyEtis-10000818");
				break;
			}
			case 15285: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000789);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000819, EnemyEtis, "EnemyEtis-10000819");
				break;
			}
			case 15305: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000790);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000820, EnemyEtis, "EnemyEtis-10000820");
				break;
			}
			case 15325: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000791);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000821, EnemyEtis, "EnemyEtis-10000821");
				break;
			}
			case 15345: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000792);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000822, EnemyEtis, "EnemyEtis-10000822");
				break;
			}
			case 15365: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000793);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000823, EnemyEtis, "EnemyEtis-10000823");
				break;
			}
			case 15385: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000794);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000824, EnemyEtis, "EnemyEtis-10000824");
				break;
			}
			case 15405: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000795);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000825, EnemyEtis, "EnemyEtis-10000825");
				break;
			}
			case 15425: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000796);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000826, EnemyEtis, "EnemyEtis-10000826");
				break;
			}
			case 15445: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000797);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000827, EnemyEtis, "EnemyEtis-10000827");
				break;
			}
			case 15465: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000798);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000828, EnemyEtis, "EnemyEtis-10000828");
				break;
			}
			case 15485: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000799);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000829, EnemyEtis, "EnemyEtis-10000829");
				break;
			}
			case 15505: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000800);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000830, EnemyEtis, "EnemyEtis-10000830");
				break;
			}
			case 15525: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000801);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000831, EnemyEtis, "EnemyEtis-10000831");
				break;
			}
			case 15545: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000802);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000832, EnemyEtis, "EnemyEtis-10000832");
				break;
			}
			case 15565: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000803);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000833, EnemyEtis, "EnemyEtis-10000833");
				break;
			}
			case 15585: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000804);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000834, EnemyEtis, "EnemyEtis-10000834");
				break;
			}
			case 15605: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000805);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000835, EnemyEtis, "EnemyEtis-10000835");
				break;
			}
			case 15625: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000806);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000836, EnemyEtis, "EnemyEtis-10000836");
				break;
			}
			case 15645: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000807);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000837, EnemyEtis, "EnemyEtis-10000837");
				break;
			}
			case 15665: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000808);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000838, EnemyEtis, "EnemyEtis-10000838");
				break;
			}
			case 15685: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000809);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000839, EnemyEtis, "EnemyEtis-10000839");
				break;
			}
			case 15705: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000810);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000840, EnemyEtis, "EnemyEtis-10000840");
				break;
			}
			case 15725: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000811);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000841, EnemyEtis, "EnemyEtis-10000841");
				break;
			}
			case 15745: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000812);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000842, EnemyEtis, "EnemyEtis-10000842");
				break;
			}
			case 15765: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000813);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000843, EnemyEtis, "EnemyEtis-10000843");
				break;
			}
			case 15785: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000814);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000844, EnemyEtis, "EnemyEtis-10000844");
				break;
			}
			case 15805: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000815);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000845, EnemyEtis, "EnemyEtis-10000845");
				break;
			}
			case 15825: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000816);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000846, EnemyEtis, "EnemyEtis-10000846");
				break;
			}
			case 15845: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000817);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000847, EnemyEtis, "EnemyEtis-10000847");
				break;
			}
			case 15865: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000818);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000848, EnemyEtis, "EnemyEtis-10000848");
				break;
			}
			case 15885: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000819);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000849, EnemyEtis, "EnemyEtis-10000849");
				break;
			}
			case 15900: {
				requestActor(10001133, EnemyDrastea, "EnemyDrastea-10001133");
				break;
			}
			case 15905: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000820);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000850, EnemyEtis, "EnemyEtis-10000850");
				break;
			}
			case 15925: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000821);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000851, EnemyEtis, "EnemyEtis-10000851");
				break;
			}
			case 15945: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000822);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000852, EnemyEtis, "EnemyEtis-10000852");
				break;
			}
			case 15965: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000823);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000853, EnemyEtis, "EnemyEtis-10000853");
				break;
			}
			case 15985: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000824);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000854, EnemyEtis, "EnemyEtis-10000854");
				break;
			}
			case 16005: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000825);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000855, EnemyEtis, "EnemyEtis-10000855");
				break;
			}
			case 16025: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000826);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000856, EnemyEtis, "EnemyEtis-10000856");
				break;
			}
			case 16045: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000827);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000857, EnemyEtis, "EnemyEtis-10000857");
				break;
			}
			case 16065: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000828);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000858, EnemyEtis, "EnemyEtis-10000858");
				break;
			}
			case 16085: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000829);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000859, EnemyEtis, "EnemyEtis-10000859");
				break;
			}
			case 16105: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000830);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000860, EnemyEtis, "EnemyEtis-10000860");
				break;
			}
			case 16125: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000831);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000861, EnemyEtis, "EnemyEtis-10000861");
				break;
			}
			case 16145: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000832);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000862, EnemyEtis, "EnemyEtis-10000862");
				break;
			}
			case 16165: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000833);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000863, EnemyEtis, "EnemyEtis-10000863");
				break;
			}
			case 16185: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000834);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000864, EnemyEtis, "EnemyEtis-10000864");
				break;
			}
			case 16205: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000835);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000865, EnemyEtis, "EnemyEtis-10000865");
				break;
			}
			case 16225: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000836);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000866, EnemyEtis, "EnemyEtis-10000866");
				break;
			}
			case 16245: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000837);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000867, EnemyEtis, "EnemyEtis-10000867");
				break;
			}
			case 16265: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000838);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000868, EnemyEtis, "EnemyEtis-10000868");
				break;
			}
			case 16285: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000839);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000869, EnemyEtis, "EnemyEtis-10000869");
				break;
			}
			case 16305: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000840);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000870, EnemyEtis, "EnemyEtis-10000870");
				break;
			}
			case 16325: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000841);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000871, EnemyEtis, "EnemyEtis-10000871");
				break;
			}
			case 16345: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000842);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000872, EnemyEtis, "EnemyEtis-10000872");
				break;
			}
			case 16365: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000843);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000873, EnemyEtis, "EnemyEtis-10000873");
				break;
			}
			case 16385: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000844);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000874, EnemyEtis, "EnemyEtis-10000874");
				break;
			}
			case 16405: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000845);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000875, EnemyEtis, "EnemyEtis-10000875");
				break;
			}
			case 16425: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000846);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000876, EnemyEtis, "EnemyEtis-10000876");
				break;
			}
			case 16445: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000847);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000877, EnemyEtis, "EnemyEtis-10000877");
				break;
			}
			case 16465: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000848);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000878, EnemyEtis, "EnemyEtis-10000878");
				break;
			}
			case 16485: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000849);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000879, EnemyEtis, "EnemyEtis-10000879");
				break;
			}
			case 16500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(10001133);
				bringSceneMediator()->appendGroupChild(p);
				break;
			}
			case 16505: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000850);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000880, EnemyEtis, "EnemyEtis-10000880");
				break;
			}
			case 16525: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000851);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000881, EnemyEtis, "EnemyEtis-10000881");
				break;
			}
			case 16545: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000852);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000882, EnemyEtis, "EnemyEtis-10000882");
				break;
			}
			case 16565: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000853);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000883, EnemyEtis, "EnemyEtis-10000883");
				break;
			}
			case 16585: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000854);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000884, EnemyEtis, "EnemyEtis-10000884");
				break;
			}
			case 16605: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000855);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000885, EnemyEtis, "EnemyEtis-10000885");
				break;
			}
			case 16625: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000856);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000886, EnemyEtis, "EnemyEtis-10000886");
				break;
			}
			case 16645: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000857);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000887, EnemyEtis, "EnemyEtis-10000887");
				break;
			}
			case 16665: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000858);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000888, EnemyEtis, "EnemyEtis-10000888");
				break;
			}
			case 16685: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000859);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000889, EnemyEtis, "EnemyEtis-10000889");
				break;
			}
			case 16705: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000860);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000890, EnemyEtis, "EnemyEtis-10000890");
				break;
			}
			case 16725: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000861);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000891, EnemyEtis, "EnemyEtis-10000891");
				break;
			}
			case 16745: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000862);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000892, EnemyEtis, "EnemyEtis-10000892");
				break;
			}
			case 16765: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000863);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000893, EnemyEtis, "EnemyEtis-10000893");
				break;
			}
			case 16785: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000864);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000894, EnemyEtis, "EnemyEtis-10000894");
				break;
			}
			case 16805: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000865);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000895, EnemyEtis, "EnemyEtis-10000895");
				break;
			}
			case 16825: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000866);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000896, EnemyEtis, "EnemyEtis-10000896");
				break;
			}
			case 16845: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000867);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000897, EnemyEtis, "EnemyEtis-10000897");
				break;
			}
			case 16865: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000868);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000898, EnemyEtis, "EnemyEtis-10000898");
				break;
			}
			case 16885: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000869);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000899, EnemyEtis, "EnemyEtis-10000899");
				break;
			}
			case 16905: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000870);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000900, EnemyEtis, "EnemyEtis-10000900");
				break;
			}
			case 16925: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000871);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000901, EnemyEtis, "EnemyEtis-10000901");
				break;
			}
			case 16945: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000872);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000902, EnemyEtis, "EnemyEtis-10000902");
				break;
			}
			case 16965: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000873);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000903, EnemyEtis, "EnemyEtis-10000903");
				break;
			}
			case 16985: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000874);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000904, EnemyEtis, "EnemyEtis-10000904");
				break;
			}
			case 17005: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000875);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000905, EnemyEtis, "EnemyEtis-10000905");
				break;
			}
			case 17025: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000876);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000906, EnemyEtis, "EnemyEtis-10000906");
				break;
			}
			case 17045: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000877);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000907, EnemyEtis, "EnemyEtis-10000907");
				break;
			}
			case 17065: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000878);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000908, EnemyEtis, "EnemyEtis-10000908");
				break;
			}
			case 17085: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000879);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000909, EnemyEtis, "EnemyEtis-10000909");
				break;
			}
			case 17105: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000880);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000910, EnemyEtis, "EnemyEtis-10000910");
				break;
			}
			case 17125: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000881);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000911, EnemyEtis, "EnemyEtis-10000911");
				break;
			}
			case 17145: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000882);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000912, EnemyEtis, "EnemyEtis-10000912");
				break;
			}
			case 17165: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000883);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000913, EnemyEtis, "EnemyEtis-10000913");
				break;
			}
			case 17185: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000884);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000914, EnemyEtis, "EnemyEtis-10000914");
				break;
			}
			case 17205: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000885);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000915, EnemyEtis, "EnemyEtis-10000915");
				break;
			}
			case 17225: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000886);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000916, EnemyEtis, "EnemyEtis-10000916");
				break;
			}
			case 17245: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000887);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000917, EnemyEtis, "EnemyEtis-10000917");
				break;
			}
			case 17265: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000888);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000918, EnemyEtis, "EnemyEtis-10000918");
				break;
			}
			case 17285: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000889);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000919, EnemyEtis, "EnemyEtis-10000919");
				break;
			}
			case 17305: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000890);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000920, EnemyEtis, "EnemyEtis-10000920");
				break;
			}
			case 17325: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000891);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000921, EnemyEtis, "EnemyEtis-10000921");
				break;
			}
			case 17345: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000892);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000922, EnemyEtis, "EnemyEtis-10000922");
				break;
			}
			case 17365: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000893);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000923, EnemyEtis, "EnemyEtis-10000923");
				break;
			}
			case 17385: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000894);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000924, EnemyEtis, "EnemyEtis-10000924");
				break;
			}
			case 17405: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000895);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000925, EnemyEtis, "EnemyEtis-10000925");
				break;
			}
			case 17425: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000896);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000926, EnemyEtis, "EnemyEtis-10000926");
				break;
			}
			case 17445: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000897);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000927, EnemyEtis, "EnemyEtis-10000927");
				break;
			}
			case 17465: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000898);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000928, EnemyEtis, "EnemyEtis-10000928");
				break;
			}
			case 17485: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000899);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000929, EnemyEtis, "EnemyEtis-10000929");
				break;
			}
			case 17505: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000900);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000930, EnemyEtis, "EnemyEtis-10000930");
				break;
			}
			case 17525: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000901);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000931, EnemyEtis, "EnemyEtis-10000931");
				break;
			}
			case 17545: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000902);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000932, EnemyEtis, "EnemyEtis-10000932");
				break;
			}
			case 17565: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000903);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000933, EnemyEtis, "EnemyEtis-10000933");
				break;
			}
			case 17585: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000904);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000934, EnemyEtis, "EnemyEtis-10000934");
				break;
			}
			case 17605: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000905);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000935, EnemyEtis, "EnemyEtis-10000935");
				break;
			}
			case 17625: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000906);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000936, EnemyEtis, "EnemyEtis-10000936");
				break;
			}
			case 17645: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000907);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000937, EnemyEtis, "EnemyEtis-10000937");
				break;
			}
			case 17665: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000908);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000938, EnemyEtis, "EnemyEtis-10000938");
				break;
			}
			case 17685: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000909);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000939, EnemyEtis, "EnemyEtis-10000939");
				break;
			}
			case 17705: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000910);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000940, EnemyEtis, "EnemyEtis-10000940");
				break;
			}
			case 17725: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000911);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000941, EnemyEtis, "EnemyEtis-10000941");
				break;
			}
			case 17745: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000912);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000942, EnemyEtis, "EnemyEtis-10000942");
				break;
			}
			case 17765: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000913);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000943, EnemyEtis, "EnemyEtis-10000943");
				break;
			}
			case 17785: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000914);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000944, EnemyEtis, "EnemyEtis-10000944");
				break;
			}
			case 17805: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000915);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000945, EnemyEtis, "EnemyEtis-10000945");
				break;
			}
			case 17825: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000916);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000946, EnemyEtis, "EnemyEtis-10000946");
				break;
			}
			case 17845: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000917);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000947, EnemyEtis, "EnemyEtis-10000947");
				break;
			}
			case 17865: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000918);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000948, EnemyEtis, "EnemyEtis-10000948");
				break;
			}
			case 17885: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000919);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000949, EnemyEtis, "EnemyEtis-10000949");
				break;
			}
			case 17900: {
				requestActor(10001134, EnemyDrastea, "EnemyDrastea-10001134");
				break;
			}
			case 17905: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000920);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000950, EnemyEtis, "EnemyEtis-10000950");
				break;
			}
			case 17925: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000921);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000951, EnemyEtis, "EnemyEtis-10000951");
				break;
			}
			case 17945: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000922);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000952, EnemyEtis, "EnemyEtis-10000952");
				break;
			}
			case 17965: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000923);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000953, EnemyEtis, "EnemyEtis-10000953");
				break;
			}
			case 17985: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000924);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000954, EnemyEtis, "EnemyEtis-10000954");
				break;
			}
			case 18005: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000925);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000955, EnemyEtis, "EnemyEtis-10000955");
				break;
			}
			case 18025: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000926);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000956, EnemyEtis, "EnemyEtis-10000956");
				break;
			}
			case 18045: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000927);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000957, EnemyEtis, "EnemyEtis-10000957");
				break;
			}
			case 18065: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000928);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000958, EnemyEtis, "EnemyEtis-10000958");
				break;
			}
			case 18085: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000929);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000959, EnemyEtis, "EnemyEtis-10000959");
				break;
			}
			case 18105: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000930);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000960, EnemyEtis, "EnemyEtis-10000960");
				break;
			}
			case 18125: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000931);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000961, EnemyEtis, "EnemyEtis-10000961");
				break;
			}
			case 18145: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000932);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000962, EnemyEtis, "EnemyEtis-10000962");
				break;
			}
			case 18165: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000933);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000963, EnemyEtis, "EnemyEtis-10000963");
				break;
			}
			case 18185: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000934);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000964, EnemyEtis, "EnemyEtis-10000964");
				break;
			}
			case 18205: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000935);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000965, EnemyEtis, "EnemyEtis-10000965");
				break;
			}
			case 18225: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000936);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000966, EnemyEtis, "EnemyEtis-10000966");
				break;
			}
			case 18245: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000937);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000967, EnemyEtis, "EnemyEtis-10000967");
				break;
			}
			case 18265: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000938);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000968, EnemyEtis, "EnemyEtis-10000968");
				break;
			}
			case 18285: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000939);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000969, EnemyEtis, "EnemyEtis-10000969");
				break;
			}
			case 18305: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000940);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000970, EnemyEtis, "EnemyEtis-10000970");
				break;
			}
			case 18325: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000941);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000971, EnemyEtis, "EnemyEtis-10000971");
				break;
			}
			case 18345: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000942);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000972, EnemyEtis, "EnemyEtis-10000972");
				break;
			}
			case 18365: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000943);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000973, EnemyEtis, "EnemyEtis-10000973");
				break;
			}
			case 18385: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000944);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000974, EnemyEtis, "EnemyEtis-10000974");
				break;
			}
			case 18405: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000945);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000975, EnemyEtis, "EnemyEtis-10000975");
				break;
			}
			case 18425: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000946);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000976, EnemyEtis, "EnemyEtis-10000976");
				break;
			}
			case 18445: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000947);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000977, EnemyEtis, "EnemyEtis-10000977");
				break;
			}
			case 18465: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000948);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000978, EnemyEtis, "EnemyEtis-10000978");
				break;
			}
			case 18485: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000949);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000979, EnemyEtis, "EnemyEtis-10000979");
				break;
			}
			case 18500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(10001134);
				bringSceneMediator()->appendGroupChild(p);
				break;
			}
			case 18505: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000950);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000980, EnemyEtis, "EnemyEtis-10000980");
				break;
			}
			case 18525: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000951);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000981, EnemyEtis, "EnemyEtis-10000981");
				break;
			}
			case 18545: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000952);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000982, EnemyEtis, "EnemyEtis-10000982");
				break;
			}
			case 18565: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000953);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000983, EnemyEtis, "EnemyEtis-10000983");
				break;
			}
			case 18585: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000954);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000984, EnemyEtis, "EnemyEtis-10000984");
				break;
			}
			case 18605: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000955);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000985, EnemyEtis, "EnemyEtis-10000985");
				break;
			}
			case 18625: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000956);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000986, EnemyEtis, "EnemyEtis-10000986");
				break;
			}
			case 18645: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000957);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000987, EnemyEtis, "EnemyEtis-10000987");
				break;
			}
			case 18665: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000958);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000988, EnemyEtis, "EnemyEtis-10000988");
				break;
			}
			case 18685: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000959);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000989, EnemyEtis, "EnemyEtis-10000989");
				break;
			}
			case 18705: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000960);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000990, EnemyEtis, "EnemyEtis-10000990");
				break;
			}
			case 18725: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000961);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000991, EnemyEtis, "EnemyEtis-10000991");
				break;
			}
			case 18745: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000962);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000992, EnemyEtis, "EnemyEtis-10000992");
				break;
			}
			case 18765: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000963);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000993, EnemyEtis, "EnemyEtis-10000993");
				break;
			}
			case 18785: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000964);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000994, EnemyEtis, "EnemyEtis-10000994");
				break;
			}
			case 18805: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000965);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000995, EnemyEtis, "EnemyEtis-10000995");
				break;
			}
			case 18825: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000966);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000996, EnemyEtis, "EnemyEtis-10000996");
				break;
			}
			case 18845: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000967);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000997, EnemyEtis, "EnemyEtis-10000997");
				break;
			}
			case 18865: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000968);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000998, EnemyEtis, "EnemyEtis-10000998");
				break;
			}
			case 18885: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000969);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000999, EnemyEtis, "EnemyEtis-10000999");
				break;
			}
			case 18905: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000970);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001000, EnemyEtis, "EnemyEtis-10001000");
				break;
			}
			case 18925: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000971);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001001, EnemyEtis, "EnemyEtis-10001001");
				break;
			}
			case 18945: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000972);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001002, EnemyEtis, "EnemyEtis-10001002");
				break;
			}
			case 18965: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000973);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001003, EnemyEtis, "EnemyEtis-10001003");
				break;
			}
			case 18985: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000974);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001004, EnemyEtis, "EnemyEtis-10001004");
				break;
			}
			case 19005: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000975);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001005, EnemyEtis, "EnemyEtis-10001005");
				break;
			}
			case 19025: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000976);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001006, EnemyEtis, "EnemyEtis-10001006");
				break;
			}
			case 19045: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000977);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001007, EnemyEtis, "EnemyEtis-10001007");
				break;
			}
			case 19065: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000978);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001008, EnemyEtis, "EnemyEtis-10001008");
				break;
			}
			case 19085: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000979);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001009, EnemyEtis, "EnemyEtis-10001009");
				break;
			}
			case 19105: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000980);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001010, EnemyEtis, "EnemyEtis-10001010");
				break;
			}
			case 19125: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000981);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001011, EnemyEtis, "EnemyEtis-10001011");
				break;
			}
			case 19145: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000982);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001012, EnemyEtis, "EnemyEtis-10001012");
				break;
			}
			case 19165: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000983);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001013, EnemyEtis, "EnemyEtis-10001013");
				break;
			}
			case 19185: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000984);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001014, EnemyEtis, "EnemyEtis-10001014");
				break;
			}
			case 19205: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000985);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001015, EnemyEtis, "EnemyEtis-10001015");
				break;
			}
			case 19225: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000986);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001016, EnemyEtis, "EnemyEtis-10001016");
				break;
			}
			case 19245: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000987);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001017, EnemyEtis, "EnemyEtis-10001017");
				break;
			}
			case 19265: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000988);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001018, EnemyEtis, "EnemyEtis-10001018");
				break;
			}
			case 19285: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000989);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001019, EnemyEtis, "EnemyEtis-10001019");
				break;
			}
			case 19305: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000990);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001020, EnemyEtis, "EnemyEtis-10001020");
				break;
			}
			case 19325: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000991);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001021, EnemyEtis, "EnemyEtis-10001021");
				break;
			}
			case 19345: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000992);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001022, EnemyEtis, "EnemyEtis-10001022");
				break;
			}
			case 19365: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000993);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001023, EnemyEtis, "EnemyEtis-10001023");
				break;
			}
			case 19385: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000994);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001024, EnemyEtis, "EnemyEtis-10001024");
				break;
			}
			case 19400: {
				requestActor(10001156, VarietyRatislavia001, "VarietyRatislavia001-10001156");
				break;
			}
			case 19405: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000995);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001025, EnemyEtis, "EnemyEtis-10001025");
				break;
			}
			case 19425: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000996);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001026, EnemyEtis, "EnemyEtis-10001026");
				break;
			}
			case 19445: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000997);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001027, EnemyEtis, "EnemyEtis-10001027");
				break;
			}
			case 19465: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000998);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001028, EnemyEtis, "EnemyEtis-10001028");
				break;
			}
			case 19485: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000999);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001029, EnemyEtis, "EnemyEtis-10001029");
				break;
			}
			case 19505: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001000);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001030, EnemyEtis, "EnemyEtis-10001030");
				break;
			}
			case 19525: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001001);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001031, EnemyEtis, "EnemyEtis-10001031");
				break;
			}
			case 19545: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001002);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001032, EnemyEtis, "EnemyEtis-10001032");
				break;
			}
			case 19565: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001003);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001033, EnemyEtis, "EnemyEtis-10001033");
				break;
			}
			case 19585: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001004);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001034, EnemyEtis, "EnemyEtis-10001034");
				break;
			}
			case 19605: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001005);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001035, EnemyEtis, "EnemyEtis-10001035");
				break;
			}
			case 19625: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001006);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001036, EnemyEtis, "EnemyEtis-10001036");
				break;
			}
			case 19645: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001007);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001037, EnemyEtis, "EnemyEtis-10001037");
				break;
			}
			case 19665: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001008);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001038, EnemyEtis, "EnemyEtis-10001038");
				break;
			}
			case 19685: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001009);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001039, EnemyEtis, "EnemyEtis-10001039");
				break;
			}
			case 19700: {
				requestActor(10000023, EnemyErmione, "EnemyErmione-10000023");
				break;
			}
			case 19705: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001010);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001040, EnemyEtis, "EnemyEtis-10001040");
				break;
			}
			case 19725: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001011);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001041, EnemyEtis, "EnemyEtis-10001041");
				break;
			}
			case 19745: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001012);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001042, EnemyEtis, "EnemyEtis-10001042");
				break;
			}
			case 19765: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001013);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001043, EnemyEtis, "EnemyEtis-10001043");
				break;
			}
			case 19785: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001014);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001044, EnemyEtis, "EnemyEtis-10001044");
				break;
			}
			case 19805: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001015);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001045, EnemyEtis, "EnemyEtis-10001045");
				break;
			}
			case 19825: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001016);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001046, EnemyEtis, "EnemyEtis-10001046");
				break;
			}
			case 19845: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001017);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001047, EnemyEtis, "EnemyEtis-10001047");
				break;
			}
			case 19865: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001018);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001048, EnemyEtis, "EnemyEtis-10001048");
				break;
			}
			case 19885: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001019);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001049, EnemyEtis, "EnemyEtis-10001049");
				break;
			}
			case 19900: {
				requestActor(10001135, EnemyDrastea, "EnemyDrastea-10001135");
				break;
			}
			case 19905: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001020);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001050, EnemyEtis, "EnemyEtis-10001050");
				break;
			}
			case 19925: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001021);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001051, EnemyEtis, "EnemyEtis-10001051");
				break;
			}
			case 19945: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001022);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001052, EnemyEtis, "EnemyEtis-10001052");
				break;
			}
			case 19965: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001023);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001053, EnemyEtis, "EnemyEtis-10001053");
				break;
			}
			case 19985: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001024);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001054, EnemyEtis, "EnemyEtis-10001054");
				break;
			}
			case 20000: {
				VarietyRatislavia001* pRatislavia = (VarietyRatislavia001*)receiveActor(10001156);
				bringSceneMediator()->appendGroupChild(pRatislavia);
				break;
			}
			case 20005: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001025);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001055, EnemyEtis, "EnemyEtis-10001055");
				break;
			}
			case 20025: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001026);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001056, EnemyEtis, "EnemyEtis-10001056");
				break;
			}
			case 20045: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001027);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001057, EnemyEtis, "EnemyEtis-10001057");
				break;
			}
			case 20065: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001028);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001058, EnemyEtis, "EnemyEtis-10001058");
				break;
			}
			case 20085: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001029);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001059, EnemyEtis, "EnemyEtis-10001059");
				break;
			}
			case 20105: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001030);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001060, EnemyEtis, "EnemyEtis-10001060");
				break;
			}
			case 20125: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001031);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001061, EnemyEtis, "EnemyEtis-10001061");
				break;
			}
			case 20145: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001032);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001062, EnemyEtis, "EnemyEtis-10001062");
				break;
			}
			case 20165: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001033);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001063, EnemyEtis, "EnemyEtis-10001063");
				break;
			}
			case 20185: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001034);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001064, EnemyEtis, "EnemyEtis-10001064");
				break;
			}
			case 20205: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001035);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001065, EnemyEtis, "EnemyEtis-10001065");
				break;
			}
			case 20225: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001036);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001066, EnemyEtis, "EnemyEtis-10001066");
				break;
			}
			case 20245: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001037);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001067, EnemyEtis, "EnemyEtis-10001067");
				break;
			}
			case 20265: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001038);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001068, EnemyEtis, "EnemyEtis-10001068");
				break;
			}
			case 20285: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001039);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001069, EnemyEtis, "EnemyEtis-10001069");
				break;
			}
			case 20300: {
				EnemyErmione* pE = (EnemyErmione*)receiveActor(10000023);
				bringSceneMediator()->appendGroupChild(pE);
				pE->_x = RND(1000000,4000000);
				pE->_y = RND(-6000000,6000000);
				pE->_z = RND(-6000000,6000000);
				break;
			}
			case 20305: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001040);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001070, EnemyEtis, "EnemyEtis-10001070");
				break;
			}
			case 20325: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001041);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001071, EnemyEtis, "EnemyEtis-10001071");
				break;
			}
			case 20345: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001042);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001072, EnemyEtis, "EnemyEtis-10001072");
				break;
			}
			case 20365: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001043);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001073, EnemyEtis, "EnemyEtis-10001073");
				break;
			}
			case 20385: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001044);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001074, EnemyEtis, "EnemyEtis-10001074");
				break;
			}
			case 20405: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001045);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001075, EnemyEtis, "EnemyEtis-10001075");
				break;
			}
			case 20425: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001046);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001076, EnemyEtis, "EnemyEtis-10001076");
				break;
			}
			case 20445: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001047);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001077, EnemyEtis, "EnemyEtis-10001077");
				break;
			}
			case 20465: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001048);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001078, EnemyEtis, "EnemyEtis-10001078");
				break;
			}
			case 20485: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001049);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001079, EnemyEtis, "EnemyEtis-10001079");
				break;
			}
			case 20500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(10001135);
				bringSceneMediator()->appendGroupChild(p);
				break;
			}
			case 20505: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001050);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001080, EnemyEtis, "EnemyEtis-10001080");
				break;
			}
			case 20525: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001051);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001081, EnemyEtis, "EnemyEtis-10001081");
				break;
			}
			case 20545: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001052);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001082, EnemyEtis, "EnemyEtis-10001082");
				break;
			}
			case 20565: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001053);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001083, EnemyEtis, "EnemyEtis-10001083");
				break;
			}
			case 20585: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001054);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001084, EnemyEtis, "EnemyEtis-10001084");
				break;
			}
			case 20605: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001055);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001085, EnemyEtis, "EnemyEtis-10001085");
				break;
			}
			case 20625: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001056);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001086, EnemyEtis, "EnemyEtis-10001086");
				break;
			}
			case 20645: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001057);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001087, EnemyEtis, "EnemyEtis-10001087");
				break;
			}
			case 20665: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001058);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001088, EnemyEtis, "EnemyEtis-10001088");
				break;
			}
			case 20685: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001059);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001089, EnemyEtis, "EnemyEtis-10001089");
				break;
			}
			case 20705: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001060);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001090, EnemyEtis, "EnemyEtis-10001090");
				break;
			}
			case 20725: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001061);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001091, EnemyEtis, "EnemyEtis-10001091");
				break;
			}
			case 20745: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001062);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001092, EnemyEtis, "EnemyEtis-10001092");
				break;
			}
			case 20765: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001063);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001093, EnemyEtis, "EnemyEtis-10001093");
				break;
			}
			case 20785: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001064);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001094, EnemyEtis, "EnemyEtis-10001094");
				break;
			}
			case 20805: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001065);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001095, EnemyEtis, "EnemyEtis-10001095");
				break;
			}
			case 20825: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001066);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001096, EnemyEtis, "EnemyEtis-10001096");
				break;
			}
			case 20845: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001067);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001097, EnemyEtis, "EnemyEtis-10001097");
				break;
			}
			case 20865: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001068);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001098, EnemyEtis, "EnemyEtis-10001098");
				break;
			}
			case 20885: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001069);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001099, EnemyEtis, "EnemyEtis-10001099");
				break;
			}
			case 20905: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001070);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001100, EnemyEtis, "EnemyEtis-10001100");
				break;
			}
			case 20925: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001071);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001101, EnemyEtis, "EnemyEtis-10001101");
				break;
			}
			case 20945: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001072);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001102, EnemyEtis, "EnemyEtis-10001102");
				break;
			}
			case 20965: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001073);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001103, EnemyEtis, "EnemyEtis-10001103");
				break;
			}
			case 20985: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001074);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001104, EnemyEtis, "EnemyEtis-10001104");
				break;
			}
			case 21005: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001075);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001105, EnemyEtis, "EnemyEtis-10001105");
				break;
			}
			case 21025: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001076);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001106, EnemyEtis, "EnemyEtis-10001106");
				break;
			}
			case 21045: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001077);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001107, EnemyEtis, "EnemyEtis-10001107");
				break;
			}
			case 21065: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001078);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001108, EnemyEtis, "EnemyEtis-10001108");
				break;
			}
			case 21085: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001079);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001109, EnemyEtis, "EnemyEtis-10001109");
				break;
			}
			case 21100: {
				requestScene(10000003, StageDebugPartClimax, "StageDebugPartClimax-10000003");
				break;
			}
			case 21105: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001080);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001110, EnemyEtis, "EnemyEtis-10001110");
				break;
			}
			case 21125: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001081);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001111, EnemyEtis, "EnemyEtis-10001111");
				break;
			}
			case 21145: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001082);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001112, EnemyEtis, "EnemyEtis-10001112");
				break;
			}
			case 21165: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001083);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001113, EnemyEtis, "EnemyEtis-10001113");
				break;
			}
			case 21185: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001084);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001114, EnemyEtis, "EnemyEtis-10001114");
				break;
			}
			case 21205: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001085);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001115, EnemyEtis, "EnemyEtis-10001115");
				break;
			}
			case 21225: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001086);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001116, EnemyEtis, "EnemyEtis-10001116");
				break;
			}
			case 21245: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001087);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001117, EnemyEtis, "EnemyEtis-10001117");
				break;
			}
			case 21265: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001088);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001118, EnemyEtis, "EnemyEtis-10001118");
				break;
			}
			case 21285: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001089);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001119, EnemyEtis, "EnemyEtis-10001119");
				break;
			}
			case 21305: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001090);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001120, EnemyEtis, "EnemyEtis-10001120");
				break;
			}
			case 21325: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001091);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001121, EnemyEtis, "EnemyEtis-10001121");
				break;
			}
			case 21345: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001092);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001122, EnemyEtis, "EnemyEtis-10001122");
				break;
			}
			case 21365: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001093);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001123, EnemyEtis, "EnemyEtis-10001123");
				break;
			}
			case 21385: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001094);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10001124, EnemyEtis, "EnemyEtis-10001124");
				break;
			}
			case 21405: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001095);
				bringSceneMediator()->appendGroupChild(pEtis);
				break;
			}
			case 21425: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001096);
				bringSceneMediator()->appendGroupChild(pEtis);
				break;
			}
			case 21445: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001097);
				bringSceneMediator()->appendGroupChild(pEtis);
				break;
			}
			case 21465: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001098);
				bringSceneMediator()->appendGroupChild(pEtis);
				break;
			}
			case 21485: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001099);
				bringSceneMediator()->appendGroupChild(pEtis);
				break;
			}
			case 21505: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001100);
				bringSceneMediator()->appendGroupChild(pEtis);
				break;
			}
			case 21525: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001101);
				bringSceneMediator()->appendGroupChild(pEtis);
				break;
			}
			case 21545: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001102);
				bringSceneMediator()->appendGroupChild(pEtis);
				break;
			}
			case 21565: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001103);
				bringSceneMediator()->appendGroupChild(pEtis);
				break;
			}
			case 21585: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001104);
				bringSceneMediator()->appendGroupChild(pEtis);
				break;
			}
			case 21605: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001105);
				bringSceneMediator()->appendGroupChild(pEtis);
				break;
			}
			case 21625: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001106);
				bringSceneMediator()->appendGroupChild(pEtis);
				break;
			}
			case 21645: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001107);
				bringSceneMediator()->appendGroupChild(pEtis);
				break;
			}
			case 21665: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001108);
				bringSceneMediator()->appendGroupChild(pEtis);
				break;
			}
			case 21685: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001109);
				bringSceneMediator()->appendGroupChild(pEtis);
				break;
			}
			case 21705: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001110);
				bringSceneMediator()->appendGroupChild(pEtis);
				break;
			}
			case 21725: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001111);
				bringSceneMediator()->appendGroupChild(pEtis);
				break;
			}
			case 21745: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001112);
				bringSceneMediator()->appendGroupChild(pEtis);
				break;
			}
			case 21765: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001113);
				bringSceneMediator()->appendGroupChild(pEtis);
				break;
			}
			case 21785: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001114);
				bringSceneMediator()->appendGroupChild(pEtis);
				break;
			}
			case 21805: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001115);
				bringSceneMediator()->appendGroupChild(pEtis);
				break;
			}
			case 21825: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001116);
				bringSceneMediator()->appendGroupChild(pEtis);
				break;
			}
			case 21845: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001117);
				bringSceneMediator()->appendGroupChild(pEtis);
				break;
			}
			case 21865: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001118);
				bringSceneMediator()->appendGroupChild(pEtis);
				break;
			}
			case 21885: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001119);
				bringSceneMediator()->appendGroupChild(pEtis);
				break;
			}
			case 21900: {
				requestActor(10001136, EnemyDrastea, "EnemyDrastea-10001136");
				break;
			}
			case 21905: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001120);
				bringSceneMediator()->appendGroupChild(pEtis);
				break;
			}
			case 21925: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001121);
				bringSceneMediator()->appendGroupChild(pEtis);
				break;
			}
			case 21945: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001122);
				bringSceneMediator()->appendGroupChild(pEtis);
				break;
			}
			case 21965: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001123);
				bringSceneMediator()->appendGroupChild(pEtis);
				break;
			}
			case 21985: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001124);
				bringSceneMediator()->appendGroupChild(pEtis);
				break;
			}
			case 22000: {
				appendChild(receiveScene(10000003));
				break;
			}
			case 22500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(10001136);
				bringSceneMediator()->appendGroupChild(p);
				break;
			}
			case 23900: {
				requestActor(10001137, EnemyDrastea, "EnemyDrastea-10001137");
				break;
			}
			case 24500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(10001137);
				bringSceneMediator()->appendGroupChild(p);
				break;
			}
			case 25900: {
				requestActor(10001138, EnemyDrastea, "EnemyDrastea-10001138");
				break;
			}
			case 26500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(10001138);
				bringSceneMediator()->appendGroupChild(p);
				break;
			}
			case 27900: {
				requestActor(10001139, EnemyDrastea, "EnemyDrastea-10001139");
				break;
			}
			case 28500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(10001139);
				bringSceneMediator()->appendGroupChild(p);
				break;
			}
			case 29900: {
				requestActor(10001140, EnemyDrastea, "EnemyDrastea-10001140");
				break;
			}
			case 30500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(10001140);
				bringSceneMediator()->appendGroupChild(p);
				break;
			}
			case 31900: {
				requestActor(10001141, EnemyDrastea, "EnemyDrastea-10001141");
				break;
			}
			case 32500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(10001141);
				bringSceneMediator()->appendGroupChild(p);
				break;
			}
			case 33900: {
				requestActor(10001142, EnemyDrastea, "EnemyDrastea-10001142");
				break;
			}
			case 34500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(10001142);
				bringSceneMediator()->appendGroupChild(p);
				break;
			}
			case 35900: {
				requestActor(10001143, EnemyDrastea, "EnemyDrastea-10001143");
				break;
			}
			case 36500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(10001143);
				bringSceneMediator()->appendGroupChild(p);
				break;
			}
			case 37900: {
				requestActor(10001144, EnemyDrastea, "EnemyDrastea-10001144");
				break;
			}
			case 38500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(10001144);
				bringSceneMediator()->appendGroupChild(p);
				break;
			}
			case 39700: {
				requestActor(10000024, EnemyErmione, "EnemyErmione-10000024");
				break;
			}
			case 39900: {
				requestActor(10001145, EnemyDrastea, "EnemyDrastea-10001145");
				break;
			}
			case 40300: {
				EnemyErmione* pE = (EnemyErmione*)receiveActor(10000024);
				bringSceneMediator()->appendGroupChild(pE);
				pE->_x = RND(1000000,4000000);
				pE->_y = RND(-6000000,6000000);
				pE->_z = RND(-6000000,6000000);
				break;
			}
			case 40500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(10001145);
				bringSceneMediator()->appendGroupChild(p);
				break;
			}
			case 41900: {
				requestActor(10001146, EnemyDrastea, "EnemyDrastea-10001146");
				break;
			}
			case 42500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(10001146);
				bringSceneMediator()->appendGroupChild(p);
				break;
			}
			case 43900: {
				requestActor(10001147, EnemyDrastea, "EnemyDrastea-10001147");
				break;
			}
			case 44500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(10001147);
				bringSceneMediator()->appendGroupChild(p);
				break;
			}
			case 45900: {
				requestActor(10001148, EnemyDrastea, "EnemyDrastea-10001148");
				break;
			}
			case 46500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(10001148);
				bringSceneMediator()->appendGroupChild(p);
				break;
			}
			case 47900: {
				requestActor(10001149, EnemyDrastea, "EnemyDrastea-10001149");
				break;
			}
			case 48500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(10001149);
				bringSceneMediator()->appendGroupChild(p);
				break;
			}
			case 49900: {
				requestActor(10001150, EnemyDrastea, "EnemyDrastea-10001150");
				break;
			}
			case 50500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(10001150);
				bringSceneMediator()->appendGroupChild(p);
				break;
			}
			case 51900: {
				requestActor(10001151, EnemyDrastea, "EnemyDrastea-10001151");
				break;
			}
			case 52500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(10001151);
				bringSceneMediator()->appendGroupChild(p);
				break;
			}
			case 53900: {
				requestActor(10001152, EnemyDrastea, "EnemyDrastea-10001152");
				break;
			}
			case 54500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(10001152);
				bringSceneMediator()->appendGroupChild(p);
				break;
			}
			case 55900: {
				requestActor(10001153, EnemyDrastea, "EnemyDrastea-10001153");
				break;
			}
			case 56500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(10001153);
				bringSceneMediator()->appendGroupChild(p);
				break;
			}
			case 57900: {
				requestActor(10001154, EnemyDrastea, "EnemyDrastea-10001154");
				break;
			}
			case 58500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(10001154);
				bringSceneMediator()->appendGroupChild(p);
				break;
			}
			default :
				break;
		}
		_cnt_event = (_cnt_event < 1190-1 ? _cnt_event+1 : _cnt_event);
	}
    // gen02 end

    ScenePhase* pPhase = getPhase();
    switch (pPhase->getCurrent()) {
        case PHASE_FAINAL: {
            if (pPhase->hasJustChanged()) {
                //STGDBGClimax_終焉の処理
                _TRACE_("STGDBGClimax_終焉のStageDebugPartController::PHASE_FAINALきた");
            }

            if (pPhase->hasArrivedFrameAt(60)) {
                fadeoutSceneWithBgm(300);
                throwEventUpperTree(EVENT_STAGEDEBUG_PART_CTRLER_WAS_END); //ステージエンドを上位に伝える
            }
            //イベント発生待ち
            break;
        }
        default :
            break;
    }
}

void StageDebugPartController::onCatchEvent(eventval prm_event_val, void* prm_pSource) {
    ScenePhase* pPhase = getPhase();
    if (prm_event_val == EVENT_STAGEDEBUG_PART_01_WAS_FINISHED) {
        _TRACE_(FUNC_NAME<<" EVENT_STAGEDEBUG_PART_01_WAS_FINISHED");
        ((DefaultScene*)prm_pSource)->sayonara(SEC_F(60));
    } else if (prm_event_val == EVENT_STAGEDEBUG_PART_02_WAS_FINISHED) {
        _TRACE_(FUNC_NAME<<" EVENT_STAGEDEBUG_PART_02_WAS_FINISHED");
        ((DefaultScene*)prm_pSource)->sayonara(SEC_F(60));
    } else if (prm_event_val == EVENT_STAGEDEBUG_PART_03_WAS_FINISHED) {
        _TRACE_(FUNC_NAME<<" EVENT_STAGEDEBUG_PART_03_WAS_FINISHED");
        ((DefaultScene*)prm_pSource)->sayonara(SEC_F(60));
    } else if (prm_event_val == EVENT_STAGEDEBUG_PART_WALL_WAS_FINISHED) {
        _TRACE_(FUNC_NAME<<" EVENT_STAGEDEBUG_PART_WALL_WAS_FINISHED");
        ((DefaultScene*)prm_pSource)->sayonara(SEC_F(60));
    } else if (prm_event_val == EVENT_STAGEDEBUG_PART_CLIMAX_WAS_FINISHED) {
        _TRACE_(FUNC_NAME<<" EVENT_STAGEDEBUG_PART_CLIMAX_WAS_FINISHED");
        ((DefaultScene*)prm_pSource)->sayonara(SEC_F(60));
        pPhase->change(PHASE_FAINAL); //フェーズをStageDebugPartController::PHASE_FAINALに切り替える
    } else {

    }

}

StageDebugPartController::~StageDebugPartController() {

}
