#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

Stage01_02::Stage01_02(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "Stage01_02";
    // 以下の gen01 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen01 start
	frame f[] = {1,100,200,500,700,1000,1200,1500,1700,2000,2200,2500,2700,3000,3200,3500,3700,4000,4200,4500,4700,5000,5200,5500,5700,6000,6200,6500,6700,7000,7200,7500,7700,8000,8200,8500,8700,9000,9200,9500,9700,10000,10200,10500,10700,11000,11200,11500,11700,12000,12200,12500,12700,13000,13200,13500,13700,14000,14200,14500,14700,15000,15200,15500,15700,16000,16200,16500,16700,17000,17200,17500,17700,18000,18200,18500,18700,19000,19200,19500,19700,20000,20200,20500,20700,21000,21200,21500,21700,22000,22200,22201,22231,22261,22291,22321,22351,22381,22411,22441,22471,22500,22501,22531,22561,22591,22621,22651,22681,22711,22741,22771,22801,22831,22861,22891,22921,22951,22981,23000,23011,23041,23071,23101,23131,23161,23191,23221,23251,23281,23311,23341,23371,23401,23431,23461,23491,23500,23521,23551,23581,23611,23641,23671,23701,23731,23761,23791,23821,23851,23881,23911,23941,23971,24000,24001,24031,24061,24091,24121,24151,24181,24211,24241,24271,24301,24331,24361,24391,24421,24451,24481,24511,24541,24571,24601,24631,24661,24691,24721,24751,24781,24811,24841,24871,24901,24931,24961,24991,25021,25051,25081,25111,25141,25171,25201,25231,25261,25291,25321,25351,25381,25411,25441,25471,25501,25531,25561,25591,25621,25651,25681,25711,25741,25771,25801,25831,25861,25891,25921,25951,25981,26011,26041,26071,26101,26131,26161,26191,26221,26251,26281,26311,26341,26371,26401,26431,26461,26491,26521,26551,26581,26611,26641,26671,26701,26731,26761,26791,26821,26851,26881,26911,26941,26971,27001,27031,27061,27091,27121,27151,27181,27211,27241,27271,27301,27331,27361,27391,27421,27451,27481,27511,27541,27571,27601,27631,27661,27691,27721,27751,27781,27811,27841,27871,27901,27931,27961,27991,28021,28051,28081,28111,28141,28171,28201,28231,28261,28291,28321,28351,28381,28411,28441,28471,28501,28531,28561,28591,28621,28651,28681,28711,28741,28771,28801,28831,28861,28891,28921,28951,28981,29011,29041,29071,29101,29131,29161,29191,29221,29251,29281,29311,29341,29371,29401,29431,29461,29491,29521,29551,29581,29611,29641,29671,29701,29731,29761,29791,29821,29851,29881,29911,29941,29971,30001,30031,30061,30091,30121,30151,30181,30211,30241,30271,30301,30331,30361,30391,30421,30451,30481,30511,30541,30571,30601,30631,30661,30691,30721,30751,30781,30811,30841,30871,30901,30931,30961,30991,31021,31051,31081,31111,31141,31171,31201,31231,31261,31291,31321,31351,31381,31411,31441,31471,31501,31531,31561,31591,31621,31651,31681,31711,31741,31771,31801,31831,31861,31891,31921,31951,31981,32011,32041,32071,32101,32131,32161,32191,32221,32251,32281,32311,32341,32371,32401,32431,32461,32491,32521,32551,32581,32611,32641,32671,32701,32731,32761,32791,32821,32851,32881,32911,32941,32971,33001,33031,33061,33091,33121,33151,33181,33211,33241,33271,33301,33331,33361,33391,33421,33451,33481,33511,33541,33571,33601,33631,33661,33691,33721,33751,33781,33811,33841,33871,33901,33931,33961,33991,34021,34051,34081,34111,34141,34171,34201,34231,34261,34291,34321,34351,34381,34411,34441,34471,34501,34531,34561,34591,34621,34651,34681,34711,34741,34771,34801,34831,34861,34891,34921,34951,34981,35011,35041,35071,35101,35131,35161,35191,35221,35251,35281,35311,35341,35371,35401,35431,35461,35491,35521,35551,35581,35611,35641,35671,35701,35731,35761,35791,35821,35851,35881,35911,35941,35971,36001,36031,36061,36091,36121,36151,36181,36211,36241,36271,36301,36331,36361,36391,36421,36451,36481,36511,36541,36571,36601,36631,36661,36691,36721,36751,36781,36811,36841,36871,36901,36931,36961,36991,37021,37051,37081,37111,37141,37171,37201,37231,37261,37291,37321,37351,37381,37411,37441,37471,37501,37531,37561,37591,37621,37651,37681,37711,37741,37771,37801,37831,37861,37891,37921,37951,37981,38011,38041,38071,38101,38131,38161,38191,38221,38251,38281,38311,38341,38371,38401,38431,38461,38491,38521,38551,38581,38611,38641,38671,38701,38731,38761,38791,38821,38851,38881,38911,38941,38971,39001,39031,39061,39091,39121,39151,39181,39211,39241,39271,39301,39331,39361,39391,39421,39451,39481,39511,39541,39571,39601,39631,39661,39691,39721,39751,39781,39811,39841,39871,39901,39931,39961,39991,40021,40051,40081,40111,40141,40171,40201,40231,40261,40291,40321,40351,40381,40411,40441,40471,40501,40531,40561,40591,40621,40651,40681,40711,40741,40771,40801,40831,40861,40891,40921,40951,40981,41011,41041,41071,41101,41131,41161,41191,41221,41251,41281,41311,41341,41371,41401,41431,41461,41491,41521,41551,41581,41611,41641,41671,41701,41731,41761,41791,41821,41851,41881,41911,41941,41971,42001,42031,42061,42091,42121,42151,42181,42211,42241,42271,42301,42331,42361,42391,42421,42451,42481,42511,42541,42571,42601,42631,42661,42691,42721,42751,42781,42811,42841,42871,42901,42931,42961,42991,43021,43051,43081,43111,43141,43171,43201,43231,43261,43291,43321,43351,43381,43411,43441,43471,43501,43531,43561,43591,43621,43651,43681,43711,43741,43771,43801,43831,43861,43891,43921,43951,43981,44011,44041,44071,44101,44131,44161,44191,44221,44251,44281,44311,44341,44371,44401,44431,44461,44491,44521,44551,44581,44611,44641,44671,44701,44731,44761,44791,44821,44851,44881,44911,44941,44971,45001,45031,45061,45091,45121,45151,45181,45211,45241,45271,45301,45331,45361,45391,45421,45451,45481,45511,45541,45571,45601,45631,45661,45691,45721,45751,45781,45811,45841,45871,45901,45931,45961,45991,46021,46051,46081,46111,46141,46171,46201,46231,46261,46291,46321,46351,46381,46411,46441,46471,46501,46531,46561,46591,46621,46651,46681,46711,46741,46771,46801,46831,46861,46891,46921,46951,46981,47011,47041,47071,47101,47131,47161,47191,47221,47251,47281,47311,47341,47371,47401,47431,47461,47491,47521,47551,47581,47611,47641,47671,47701,47731,47761,47791,47821,47851,47881,47911,47941,47971,48001,48031,48061,48091,48121,48151,48181,48211,48241,48271,48301,48331,48361,48391,48421,48451,48481,48511,48541,48571,48601,48631,48661,48691,48721,48751,48781,48811,48841,48871,48901,48931,48961,48991,49021,49051,49081,49111,49141,49171,49201,49231,49261,49291,49321,49351,49381,49411,49441,49471,49501,49531,49561,49591,49621,49651,49681,49711,49741,49771,49801,49831,49861,49891,49921,49951,49981,50011,50041,50071,50101,50131,50161,50191,50221,50251,50281,50311,50341,50371,50401,50431,50461,50491,50521,50551,50581,50611,50641,50671,50701,50731,50761,50791,50821,50851,50881,50911,50941,50971,51001,51031,51061,51091,51121,51151,51181,51211,51241,51271,51301,51331,51361,51391,51421,51451,51481,51511,51541,51571,51601,51631,51661,51691,51721,51751,51781,51811,51841,51871,51901,51931,51961,51991,52021,52051,52081,52111,52141,52171,52201,52231,52261,52291,52321,52351,52381,52411,52441,52471,52501,52531,52561,52591,52621,52651,52681,52711,52741,52771,52801,52831,52861,52891,52921,52951,52981,53011,53041,53071,53101,53131,53161,53191,53221,53251,53281,53311,53341,53371,53401,53431,53461,53491,53521,53551,53581,53611,53641,53671,53701,53731,53761,53791,53821,53851,53881,53911,53941,53971,54001,54031,54061,54091,54121,54151,54181,54211,54241,54271,54301,54331,54361,54391,54421,54451,54481,54511,54541,54571,54601,54631,54661,54691,54721,54751,54781,54811,54841,54871,54901,54931,54961,54991,55021,55051,55081,55111,55141,55171,55201,55231,55261,55291,55321,55351,55381,55411,55441,55471,55501,55531,55561,55591,55621,55651,55681,55711,55741,55771,55801,55831,55861,55891,55921,55951,55981,56011,56041,56071,56101,56131,56161,56191,56221,56251,56281,56311,56341,56371,56401,56431,56461,56491,56521,56551,56581,56611,56641,56671,56701,56731,56761,56791,56821,56851,56881,56911,56941,56971,57001,57031,57061,57091,57121,57151,57181,57211,57241,57271,57301,57331,57361,57391,57421,57451,57481,57511,57541,57571,57601,57631,57661,57691,57721,57751,57781,57811,57841,57871,57901,57931,57961,57991,58021,58051,58081,58111,58141,58171,58201,58231,58261,58291,58321,58351,58381,58411,58441,58471,58501,58531,58561,58591,58621,58651,58681,58711,58741,58771,58801,58831,58861,58891,58921,58951,58981,59011,59041,59071,59101,59131,59161,59191,59221,59251,59281,59311,59341,59371,59401,59431,59461,59491,59521,59551,59581,59611,59641,59671,59701,59731,59761,59791,59821,59851,59881,59911,59941,59971,60001,60031,60061,60091,60121,60151,60181,60211,60241,60271,60301,60331,60361,60391,60421,60451,60481,60511,60541,60571,60601,60631,60661,60691,60721,60751,60781,60811,60841,60871,60901,60931,60961,60991,61021,61051,61081,61111,61141,61171,61201,61231,61261,61291,61321,61351,61381,61411,61441,61471,61501,61531,61561,61591,61621,61651,61681,61711,61741,61771,61801,61831,61861,61891,61921,61951,61981};
	_paFrame_NextEvent = new frame[1422];
	memcpy(_paFrame_NextEvent, f, sizeof(f));
	_event_num = 1422;
	orderActorToFactory(40000000, EnemyAstraea, "Astraea_1");
	
	orderActorToFactory(40000002, FormationPallas001a, "F001a_Pallas_2");
	orderActorToFactory(40000003, FormationPallas001b, "F001b_Pallas_3");
	orderActorToFactory(40000004, FormationPallas001c, "F001c_Pallas_4");
	orderActorToFactory(40000005, FormationPallas001d, "F001d_Pallas_5");
	orderActorToFactory(40000006, FormationPallas001a, "F001a_Pallas_6");
	orderActorToFactory(40000007, FormationPallas001d, "F001d_Pallas_7");
	orderActorToFactory(40000008, FormationPallas001b, "F001b_Pallas_8");
	orderActorToFactory(40000009, FormationPallas001c, "F001c_Pallas_9");
	orderActorToFactory(40000010, FormationPallas001a, "F001a_Pallas_10");
	orderActorToFactory(40000011, FormationPallas001d, "F001d_Pallas_11");
	orderActorToFactory(40000012, FormationPallas001b, "F001b_Pallas_12");
	orderActorToFactory(40000013, FormationPallas001c, "F001c_Pallas_13");
	orderActorToFactory(40000014, EnemyAstraea, "Astraea_14");
	orderActorToFactory(40000015, EnemyAstraea, "Astraea_15");
	orderActorToFactory(40000021, EnemyMetis, "Metis_16");
	orderActorToFactory(40000022, EnemyMetis, "Metis_17");
    // gen01 end
}

void Stage01_02::initialize() {

}

void Stage01_02::processBehavior() {
    // 以下の gen02 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen02 start
	if (getActivePartFrame() == _paFrame_NextEvent[_iCnt_Event]) {
		switch (getActivePartFrame()) {
			case 1: {
				break;
			}
			case 100: {
				EnemyAstraea* pAstraea = (EnemyAstraea*)obtainActorFromFactory(40000000);
				getLordActor()->addSubGroup(pAstraea);
				pAstraea->_Z = -1800000;
				pAstraea->_Y = -100000;
				{
				ActorTableScene* ta = NEW ActorTableScene("TableScene_40000001");
				ta->setMaxPerformFrame(2500);
				addSubLast(ta);
				ta->addToTable(((FormationPallas001a*)obtainActorFromFactory(40000002)), 400);
				ta->addToTable(((FormationPallas001b*)obtainActorFromFactory(40000003)), 400);
				ta->addToTable(((FormationPallas001c*)obtainActorFromFactory(40000004)), 400);
				ta->addToTable(((FormationPallas001d*)obtainActorFromFactory(40000005)), 400);
				ta->addToTable(((FormationPallas001a*)obtainActorFromFactory(40000006)), 1);
				ta->addToTable(((FormationPallas001d*)obtainActorFromFactory(40000007)), 400);
				ta->addToTable(((FormationPallas001b*)obtainActorFromFactory(40000008)), 1);
				ta->addToTable(((FormationPallas001c*)obtainActorFromFactory(40000009)), 400);
				ta->addToTable(((FormationPallas001a*)obtainActorFromFactory(40000010)), 1);
				ta->addToTable(((FormationPallas001d*)obtainActorFromFactory(40000011)), 1);
				ta->addToTable(((FormationPallas001b*)obtainActorFromFactory(40000012)), 1);
				ta->addToTable(((FormationPallas001c*)obtainActorFromFactory(40000013)), 400);
				}
				break;
			}
			case 200: {
				orderActorToFactory(40000023, EnemyMetis, "Metis_18");
				orderActorToFactory(40001339, FormationThalia, "FormationThalia_19");
				break;
			}
			case 500: {
				EnemyAstraea* pAstraea2 = (EnemyAstraea*)obtainActorFromFactory(40000014);
				getLordActor()->addSubGroup(pAstraea2);
				pAstraea2->_Z = -1800000;
				pAstraea2->_Y = -100000;
				break;
			}
			case 700: {
				orderActorToFactory(40000016, EnemyAstraea, "Astraea_20");
				orderActorToFactory(40000024, EnemyMetis, "Metis_21");
				break;
			}
			case 1000: {
				EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000021);
				getLordActor()->addSubGroup(pMetis1);
				break;
			}
			case 1200: {
				orderActorToFactory(40000017, VarietyTorus001, "VarietyTorus001_22");
				orderActorToFactory(40000025, EnemyMetis, "Metis_23");
				break;
			}
			case 1500: {
				EnemyAstraea* pAstraea2 = (EnemyAstraea*)obtainActorFromFactory(40000015);
				getLordActor()->addSubGroup(pAstraea2);
				pAstraea2->_Z = -1800000;
				pAstraea2->_Y = -100000;
				EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000022);
				getLordActor()->addSubGroup(pMetis1);
				break;
			}
			case 1700: {
				orderActorToFactory(40000026, EnemyMetis, "Metis_24");
				break;
			}
			case 2000: {
				EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000023);
				getLordActor()->addSubGroup(pMetis1);
				FormationThalia* pF = (FormationThalia*)obtainActorFromFactory(40001339);
				getLordActor()->addSubGroup(pF);
				break;
			}
			case 2200: {
				orderActorToFactory(40000027, EnemyMetis, "Metis_25");
				orderActorToFactory(40001337, FormationIris002, "F002_Iris_26");
				break;
			}
			case 2500: {
				EnemyAstraea* pAstraea2 = (EnemyAstraea*)obtainActorFromFactory(40000016);
				getLordActor()->addSubGroup(pAstraea2);
				pAstraea2->_Z = -1800000;
				pAstraea2->_Y = -100000;
				EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000024);
				getLordActor()->addSubGroup(pMetis1);
				break;
			}
			case 2700: {
				orderActorToFactory(40000028, EnemyMetis, "Metis_27");
				orderActorToFactory(40001338, FormationIris002, "F002_Iris_28");
				break;
			}
			case 3000: {
				VarietyTorus001* pTorus = (VarietyTorus001*)obtainActorFromFactory(40000017);
				getLordActor()->addSubGroup(pTorus);
				EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000025);
				getLordActor()->addSubGroup(pMetis1);
				break;
			}
			case 3200: {
				orderActorToFactory(40000029, EnemyMetis, "Metis_29");
				orderActorToFactory(40001335, FormationJuno001, "F002_Juno_30");
				break;
			}
			case 3500: {
				EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000026);
				getLordActor()->addSubGroup(pMetis1);
				break;
			}
			case 3700: {
				orderActorToFactory(40000030, EnemyMetis, "Metis_31");
				break;
			}
			case 4000: {
				EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000027);
				getLordActor()->addSubGroup(pMetis1);
				FormationIris002* pF1 = (FormationIris002*)obtainActorFromFactory(40001337);
				getLordActor()->addSubGroup(pF1);
				break;
			}
			case 4200: {
				orderActorToFactory(40000031, EnemyMetis, "Metis_32");
				break;
			}
			case 4500: {
				EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000028);
				getLordActor()->addSubGroup(pMetis1);
				FormationIris002* pF2 = (FormationIris002*)obtainActorFromFactory(40001338);
				getLordActor()->addSubGroup(pF2);
				break;
			}
			case 4700: {
				orderActorToFactory(40000032, EnemyMetis, "Metis_33");
				break;
			}
			case 5000: {
				EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000029);
				getLordActor()->addSubGroup(pMetis1);
				FormationJuno001* pF = (FormationJuno001*)obtainActorFromFactory(40001335);
				getLordActor()->addSubGroup(pF);
				break;
			}
			case 5200: {
				orderActorToFactory(40000033, EnemyMetis, "Metis_34");
				break;
			}
			case 5500: {
				EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000030);
				getLordActor()->addSubGroup(pMetis1);
				break;
			}
			case 5700: {
				orderActorToFactory(40000034, EnemyMetis, "Metis_35");
				break;
			}
			case 6000: {
				EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000031);
				getLordActor()->addSubGroup(pMetis1);
				break;
			}
			case 6200: {
				orderActorToFactory(40000035, EnemyMetis, "Metis_36");
				break;
			}
			case 6500: {
				EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000032);
				getLordActor()->addSubGroup(pMetis1);
				break;
			}
			case 6700: {
				orderActorToFactory(40000036, EnemyMetis, "Metis_37");
				break;
			}
			case 7000: {
				EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000033);
				getLordActor()->addSubGroup(pMetis1);
				break;
			}
			case 7200: {
				orderActorToFactory(40000037, EnemyMetis, "Metis_38");
				break;
			}
			case 7500: {
				EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000034);
				getLordActor()->addSubGroup(pMetis1);
				break;
			}
			case 7700: {
				orderActorToFactory(40000038, EnemyMetis, "Metis_39");
				break;
			}
			case 8000: {
				EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000035);
				getLordActor()->addSubGroup(pMetis1);
				break;
			}
			case 8200: {
				orderActorToFactory(40000018, VarietyTorus002, "VarietyTorus002_40");
				orderActorToFactory(40000019, VarietyTorus003, "VarietyTorus003_41");
				orderActorToFactory(40000039, EnemyMetis, "Metis_42");
				break;
			}
			case 8500: {
				EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000036);
				getLordActor()->addSubGroup(pMetis1);
				break;
			}
			case 8700: {
				orderActorToFactory(40000040, EnemyMetis, "Metis_43");
				break;
			}
			case 9000: {
				EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000037);
				getLordActor()->addSubGroup(pMetis1);
				break;
			}
			case 9200: {
				orderActorToFactory(40000041, EnemyMetis, "Metis_44");
				break;
			}
			case 9500: {
				EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000038);
				getLordActor()->addSubGroup(pMetis1);
				break;
			}
			case 9700: {
				orderActorToFactory(40000042, EnemyMetis, "Metis_45");
				break;
			}
			case 10000: {
				VarietyTorus002* pTorusA = (VarietyTorus002*)obtainActorFromFactory(40000018);
				getLordActor()->addSubGroup(pTorusA);
				VarietyTorus003* pTorusB = (VarietyTorus003*)obtainActorFromFactory(40000019);
				getLordActor()->addSubGroup(pTorusB);
				EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000039);
				getLordActor()->addSubGroup(pMetis1);
				break;
			}
			case 10200: {
				orderActorToFactory(40000043, EnemyMetis, "Metis_46");
				break;
			}
			case 10500: {
				EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000040);
				getLordActor()->addSubGroup(pMetis1);
				break;
			}
			case 10700: {
				orderActorToFactory(40000044, EnemyMetis, "Metis_47");
				break;
			}
			case 11000: {
				EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000041);
				getLordActor()->addSubGroup(pMetis1);
				break;
			}
			case 11200: {
				orderActorToFactory(40000045, EnemyMetis, "Metis_48");
				orderActorToFactory(40001336, FormationJuno001, "F002_Juno_49");
				break;
			}
			case 11500: {
				EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000042);
				getLordActor()->addSubGroup(pMetis1);
				break;
			}
			case 11700: {
				orderActorToFactory(40000046, EnemyMetis, "Metis_50");
				break;
			}
			case 12000: {
				EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000043);
				getLordActor()->addSubGroup(pMetis1);
				break;
			}
			case 12200: {
				orderActorToFactory(40000047, EnemyMetis, "Metis_51");
				break;
			}
			case 12500: {
				EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000044);
				getLordActor()->addSubGroup(pMetis1);
				break;
			}
			case 12700: {
				orderActorToFactory(40000048, EnemyMetis, "Metis_52");
				break;
			}
			case 13000: {
				EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000045);
				getLordActor()->addSubGroup(pMetis1);
				FormationJuno001* pF = (FormationJuno001*)obtainActorFromFactory(40001336);
				getLordActor()->addSubGroup(pF);
				break;
			}
			case 13200: {
				orderActorToFactory(40000049, EnemyMetis, "Metis_53");
				break;
			}
			case 13500: {
				EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000046);
				getLordActor()->addSubGroup(pMetis1);
				break;
			}
			case 13700: {
				orderActorToFactory(40000050, EnemyMetis, "Metis_54");
				break;
			}
			case 14000: {
				EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000047);
				getLordActor()->addSubGroup(pMetis1);
				break;
			}
			case 14200: {
				orderActorToFactory(40000051, EnemyMetis, "Metis_55");
				break;
			}
			case 14500: {
				EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000048);
				getLordActor()->addSubGroup(pMetis1);
				break;
			}
			case 14700: {
				orderActorToFactory(40000052, EnemyMetis, "Metis_56");
				break;
			}
			case 15000: {
				EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000049);
				getLordActor()->addSubGroup(pMetis1);
				break;
			}
			case 15200: {
				orderActorToFactory(40000053, EnemyMetis, "Metis_57");
				orderActorToFactory(40001340, FormationThalia, "FormationThalia_58");
				break;
			}
			case 15500: {
				EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000050);
				getLordActor()->addSubGroup(pMetis1);
				break;
			}
			case 15700: {
				orderActorToFactory(40000054, EnemyMetis, "Metis_59");
				break;
			}
			case 16000: {
				EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000051);
				getLordActor()->addSubGroup(pMetis1);
				break;
			}
			case 16200: {
				orderActorToFactory(40000055, EnemyMetis, "Metis_60");
				break;
			}
			case 16500: {
				EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000052);
				getLordActor()->addSubGroup(pMetis1);
				break;
			}
			case 16700: {
				orderActorToFactory(40000056, EnemyMetis, "Metis_61");
				break;
			}
			case 17000: {
				EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000053);
				getLordActor()->addSubGroup(pMetis1);
				FormationThalia* pF = (FormationThalia*)obtainActorFromFactory(40001340);
				getLordActor()->addSubGroup(pF);
				break;
			}
			case 17200: {
				orderActorToFactory(40000057, EnemyMetis, "Metis_62");
				orderActorToFactory(40001341, FormationThalia, "FormationThalia_63");
				break;
			}
			case 17500: {
				EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000054);
				getLordActor()->addSubGroup(pMetis1);
				break;
			}
			case 17700: {
				orderActorToFactory(40000058, EnemyMetis, "Metis_64");
				break;
			}
			case 18000: {
				EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000055);
				getLordActor()->addSubGroup(pMetis1);
				break;
			}
			case 18200: {
				orderActorToFactory(40000020, VarietyTorus004, "VarietyTorus004_65");
				orderActorToFactory(40000059, EnemyMetis, "Metis_66");
				break;
			}
			case 18500: {
				EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000056);
				getLordActor()->addSubGroup(pMetis1);
				break;
			}
			case 18700: {
				orderActorToFactory(40000060, EnemyMetis, "Metis_67");
				break;
			}
			case 19000: {
				EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000057);
				getLordActor()->addSubGroup(pMetis1);
				FormationThalia* pF = (FormationThalia*)obtainActorFromFactory(40001341);
				getLordActor()->addSubGroup(pF);
				break;
			}
			case 19200: {
				orderActorToFactory(40000061, EnemyMetis, "Metis_68");
				break;
			}
			case 19500: {
				EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000058);
				getLordActor()->addSubGroup(pMetis1);
				break;
			}
			case 19700: {
				orderActorToFactory(40000062, EnemyMetis, "Metis_69");
				break;
			}
			case 20000: {
				VarietyTorus004* pTorus = (VarietyTorus004*)obtainActorFromFactory(40000020);
				getLordActor()->addSubGroup(pTorus);
				EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000059);
				getLordActor()->addSubGroup(pMetis1);
				break;
			}
			case 20200: {
				orderActorToFactory(40000063, EnemyMetis, "Metis_70");
				break;
			}
			case 20500: {
				EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000060);
				getLordActor()->addSubGroup(pMetis1);
				break;
			}
			case 20700: {
				orderActorToFactory(40000064, EnemyMetis, "Metis_71");
				break;
			}
			case 21000: {
				EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000061);
				getLordActor()->addSubGroup(pMetis1);
				break;
			}
			case 21200: {
				orderActorToFactory(40000065, EnemyMetis, "Metis_72");
				break;
			}
			case 21500: {
				EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000062);
				getLordActor()->addSubGroup(pMetis1);
				break;
			}
			case 21700: {
				orderActorToFactory(40000066, EnemyMetis, "Metis_73");
				break;
			}
			case 22000: {
				EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000063);
				getLordActor()->addSubGroup(pMetis1);
				break;
			}
			case 22200: {
				orderActorToFactory(40000067, EnemyMetis, "Metis_74");
				break;
			}
			case 22201: {
				orderActorToFactory(40000068, EnemyMetis, "Metis_75");
				break;
			}
			case 22231: {
				orderActorToFactory(40000069, EnemyMetis, "Metis_76");
				break;
			}
			case 22261: {
				orderActorToFactory(40000070, EnemyMetis, "Metis_77");
				break;
			}
			case 22291: {
				orderActorToFactory(40000071, EnemyMetis, "Metis_78");
				break;
			}
			case 22321: {
				orderActorToFactory(40000072, EnemyMetis, "Metis_79");
				break;
			}
			case 22351: {
				orderActorToFactory(40000073, EnemyMetis, "Metis_80");
				break;
			}
			case 22381: {
				orderActorToFactory(40000074, EnemyMetis, "Metis_81");
				break;
			}
			case 22411: {
				orderActorToFactory(40000075, EnemyMetis, "Metis_82");
				break;
			}
			case 22441: {
				orderActorToFactory(40000076, EnemyMetis, "Metis_83");
				break;
			}
			case 22471: {
				orderActorToFactory(40000077, EnemyMetis, "Metis_84");
				break;
			}
			case 22500: {
				EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000064);
				getLordActor()->addSubGroup(pMetis1);
				break;
			}
			case 22501: {
				orderActorToFactory(40000078, EnemyMetis, "Metis_85");
				break;
			}
			case 22531: {
				orderActorToFactory(40000079, EnemyMetis, "Metis_86");
				break;
			}
			case 22561: {
				orderActorToFactory(40000080, EnemyMetis, "Metis_87");
				break;
			}
			case 22591: {
				orderActorToFactory(40000081, EnemyMetis, "Metis_88");
				break;
			}
			case 22621: {
				orderActorToFactory(40000082, EnemyMetis, "Metis_89");
				break;
			}
			case 22651: {
				orderActorToFactory(40000083, EnemyMetis, "Metis_90");
				break;
			}
			case 22681: {
				orderActorToFactory(40000084, EnemyMetis, "Metis_91");
				break;
			}
			case 22711: {
				orderActorToFactory(40000085, EnemyMetis, "Metis_92");
				break;
			}
			case 22741: {
				orderActorToFactory(40000086, EnemyMetis, "Metis_93");
				break;
			}
			case 22771: {
				orderActorToFactory(40000087, EnemyMetis, "Metis_94");
				break;
			}
			case 22801: {
				orderActorToFactory(40000088, EnemyMetis, "Metis_95");
				break;
			}
			case 22831: {
				orderActorToFactory(40000089, EnemyMetis, "Metis_96");
				break;
			}
			case 22861: {
				orderActorToFactory(40000090, EnemyMetis, "Metis_97");
				break;
			}
			case 22891: {
				orderActorToFactory(40000091, EnemyMetis, "Metis_98");
				break;
			}
			case 22921: {
				orderActorToFactory(40000092, EnemyMetis, "Metis_99");
				break;
			}
			case 22951: {
				orderActorToFactory(40000093, EnemyMetis, "Metis_100");
				break;
			}
			case 22981: {
				orderActorToFactory(40000094, EnemyMetis, "Metis_101");
				break;
			}
			case 23000: {
				EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000065);
				getLordActor()->addSubGroup(pMetis1);
				break;
			}
			case 23011: {
				orderActorToFactory(40000095, EnemyMetis, "Metis_102");
				break;
			}
			case 23041: {
				orderActorToFactory(40000096, EnemyMetis, "Metis_103");
				break;
			}
			case 23071: {
				orderActorToFactory(40000097, EnemyMetis, "Metis_104");
				break;
			}
			case 23101: {
				orderActorToFactory(40000098, EnemyMetis, "Metis_105");
				break;
			}
			case 23131: {
				orderActorToFactory(40000099, EnemyMetis, "Metis_106");
				break;
			}
			case 23161: {
				orderActorToFactory(40000100, EnemyMetis, "Metis_107");
				break;
			}
			case 23191: {
				orderActorToFactory(40000101, EnemyMetis, "Metis_108");
				break;
			}
			case 23221: {
				orderActorToFactory(40000102, EnemyMetis, "Metis_109");
				break;
			}
			case 23251: {
				orderActorToFactory(40000103, EnemyMetis, "Metis_110");
				break;
			}
			case 23281: {
				orderActorToFactory(40000104, EnemyMetis, "Metis_111");
				break;
			}
			case 23311: {
				orderActorToFactory(40000105, EnemyMetis, "Metis_112");
				break;
			}
			case 23341: {
				orderActorToFactory(40000106, EnemyMetis, "Metis_113");
				break;
			}
			case 23371: {
				orderActorToFactory(40000107, EnemyMetis, "Metis_114");
				break;
			}
			case 23401: {
				orderActorToFactory(40000108, EnemyMetis, "Metis_115");
				break;
			}
			case 23431: {
				orderActorToFactory(40000109, EnemyMetis, "Metis_116");
				break;
			}
			case 23461: {
				orderActorToFactory(40000110, EnemyMetis, "Metis_117");
				break;
			}
			case 23491: {
				orderActorToFactory(40000111, EnemyMetis, "Metis_118");
				break;
			}
			case 23500: {
				EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000066);
				getLordActor()->addSubGroup(pMetis1);
				break;
			}
			case 23521: {
				orderActorToFactory(40000112, EnemyMetis, "Metis_119");
				break;
			}
			case 23551: {
				orderActorToFactory(40000113, EnemyMetis, "Metis_120");
				break;
			}
			case 23581: {
				orderActorToFactory(40000114, EnemyMetis, "Metis_121");
				break;
			}
			case 23611: {
				orderActorToFactory(40000115, EnemyMetis, "Metis_122");
				break;
			}
			case 23641: {
				orderActorToFactory(40000116, EnemyMetis, "Metis_123");
				break;
			}
			case 23671: {
				orderActorToFactory(40000117, EnemyMetis, "Metis_124");
				break;
			}
			case 23701: {
				orderActorToFactory(40000118, EnemyMetis, "Metis_125");
				break;
			}
			case 23731: {
				orderActorToFactory(40000119, EnemyMetis, "Metis_126");
				break;
			}
			case 23761: {
				orderActorToFactory(40000120, EnemyMetis, "Metis_127");
				break;
			}
			case 23791: {
				orderActorToFactory(40000121, EnemyMetis, "Metis_128");
				break;
			}
			case 23821: {
				orderActorToFactory(40000122, EnemyMetis, "Metis_129");
				break;
			}
			case 23851: {
				orderActorToFactory(40000123, EnemyMetis, "Metis_130");
				break;
			}
			case 23881: {
				orderActorToFactory(40000124, EnemyMetis, "Metis_131");
				break;
			}
			case 23911: {
				orderActorToFactory(40000125, EnemyMetis, "Metis_132");
				break;
			}
			case 23941: {
				orderActorToFactory(40000126, EnemyMetis, "Metis_133");
				break;
			}
			case 23971: {
				orderActorToFactory(40000127, EnemyMetis, "Metis_134");
				break;
			}
			case 24000: {
				EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000067);
				getLordActor()->addSubGroup(pMetis1);
				break;
			}
			case 24001: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000068);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000128, EnemyMetis, "Metis_135");
				break;
			}
			case 24031: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000069);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000129, EnemyMetis, "Metis_136");
				break;
			}
			case 24061: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000070);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000130, EnemyMetis, "Metis_137");
				break;
			}
			case 24091: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000071);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000131, EnemyMetis, "Metis_138");
				break;
			}
			case 24121: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000072);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000132, EnemyMetis, "Metis_139");
				break;
			}
			case 24151: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000073);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000133, EnemyMetis, "Metis_140");
				break;
			}
			case 24181: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000074);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000134, EnemyMetis, "Metis_141");
				break;
			}
			case 24211: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000075);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000135, EnemyMetis, "Metis_142");
				break;
			}
			case 24241: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000076);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000136, EnemyMetis, "Metis_143");
				break;
			}
			case 24271: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000077);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000137, EnemyMetis, "Metis_144");
				break;
			}
			case 24301: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000078);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000138, EnemyMetis, "Metis_145");
				break;
			}
			case 24331: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000079);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000139, EnemyMetis, "Metis_146");
				break;
			}
			case 24361: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000080);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000140, EnemyMetis, "Metis_147");
				break;
			}
			case 24391: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000081);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000141, EnemyMetis, "Metis_148");
				break;
			}
			case 24421: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000082);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000142, EnemyMetis, "Metis_149");
				break;
			}
			case 24451: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000083);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000143, EnemyMetis, "Metis_150");
				break;
			}
			case 24481: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000084);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000144, EnemyMetis, "Metis_151");
				break;
			}
			case 24511: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000085);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000145, EnemyMetis, "Metis_152");
				break;
			}
			case 24541: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000086);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000146, EnemyMetis, "Metis_153");
				break;
			}
			case 24571: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000087);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000147, EnemyMetis, "Metis_154");
				break;
			}
			case 24601: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000088);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000148, EnemyMetis, "Metis_155");
				break;
			}
			case 24631: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000089);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000149, EnemyMetis, "Metis_156");
				break;
			}
			case 24661: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000090);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000150, EnemyMetis, "Metis_157");
				break;
			}
			case 24691: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000091);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000151, EnemyMetis, "Metis_158");
				break;
			}
			case 24721: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000092);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000152, EnemyMetis, "Metis_159");
				break;
			}
			case 24751: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000093);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000153, EnemyMetis, "Metis_160");
				break;
			}
			case 24781: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000094);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000154, EnemyMetis, "Metis_161");
				break;
			}
			case 24811: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000095);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000155, EnemyMetis, "Metis_162");
				break;
			}
			case 24841: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000096);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000156, EnemyMetis, "Metis_163");
				break;
			}
			case 24871: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000097);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000157, EnemyMetis, "Metis_164");
				break;
			}
			case 24901: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000098);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000158, EnemyMetis, "Metis_165");
				break;
			}
			case 24931: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000099);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000159, EnemyMetis, "Metis_166");
				break;
			}
			case 24961: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000100);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000160, EnemyMetis, "Metis_167");
				break;
			}
			case 24991: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000101);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000161, EnemyMetis, "Metis_168");
				break;
			}
			case 25021: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000102);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000162, EnemyMetis, "Metis_169");
				break;
			}
			case 25051: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000103);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000163, EnemyMetis, "Metis_170");
				break;
			}
			case 25081: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000104);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000164, EnemyMetis, "Metis_171");
				break;
			}
			case 25111: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000105);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000165, EnemyMetis, "Metis_172");
				break;
			}
			case 25141: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000106);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000166, EnemyMetis, "Metis_173");
				break;
			}
			case 25171: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000107);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000167, EnemyMetis, "Metis_174");
				break;
			}
			case 25201: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000108);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000168, EnemyMetis, "Metis_175");
				break;
			}
			case 25231: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000109);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000169, EnemyMetis, "Metis_176");
				break;
			}
			case 25261: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000110);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000170, EnemyMetis, "Metis_177");
				break;
			}
			case 25291: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000111);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000171, EnemyMetis, "Metis_178");
				break;
			}
			case 25321: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000112);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000172, EnemyMetis, "Metis_179");
				break;
			}
			case 25351: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000113);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000173, EnemyMetis, "Metis_180");
				break;
			}
			case 25381: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000114);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000174, EnemyMetis, "Metis_181");
				break;
			}
			case 25411: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000115);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000175, EnemyMetis, "Metis_182");
				break;
			}
			case 25441: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000116);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000176, EnemyMetis, "Metis_183");
				break;
			}
			case 25471: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000117);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000177, EnemyMetis, "Metis_184");
				break;
			}
			case 25501: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000118);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000178, EnemyMetis, "Metis_185");
				break;
			}
			case 25531: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000119);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000179, EnemyMetis, "Metis_186");
				break;
			}
			case 25561: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000120);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000180, EnemyMetis, "Metis_187");
				break;
			}
			case 25591: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000121);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000181, EnemyMetis, "Metis_188");
				break;
			}
			case 25621: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000122);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000182, EnemyMetis, "Metis_189");
				break;
			}
			case 25651: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000123);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000183, EnemyMetis, "Metis_190");
				break;
			}
			case 25681: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000124);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000184, EnemyMetis, "Metis_191");
				break;
			}
			case 25711: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000125);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000185, EnemyMetis, "Metis_192");
				break;
			}
			case 25741: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000126);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000186, EnemyMetis, "Metis_193");
				break;
			}
			case 25771: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000127);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000187, EnemyMetis, "Metis_194");
				break;
			}
			case 25801: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000128);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000188, EnemyMetis, "Metis_195");
				break;
			}
			case 25831: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000129);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000189, EnemyMetis, "Metis_196");
				break;
			}
			case 25861: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000130);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000190, EnemyMetis, "Metis_197");
				break;
			}
			case 25891: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000131);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000191, EnemyMetis, "Metis_198");
				break;
			}
			case 25921: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000132);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000192, EnemyMetis, "Metis_199");
				break;
			}
			case 25951: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000133);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000193, EnemyMetis, "Metis_200");
				break;
			}
			case 25981: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000134);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000194, EnemyMetis, "Metis_201");
				break;
			}
			case 26011: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000135);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000195, EnemyMetis, "Metis_202");
				break;
			}
			case 26041: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000136);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000196, EnemyMetis, "Metis_203");
				break;
			}
			case 26071: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000137);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000197, EnemyMetis, "Metis_204");
				break;
			}
			case 26101: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000138);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000198, EnemyMetis, "Metis_205");
				break;
			}
			case 26131: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000139);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000199, EnemyMetis, "Metis_206");
				break;
			}
			case 26161: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000140);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000200, EnemyMetis, "Metis_207");
				break;
			}
			case 26191: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000141);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000201, EnemyMetis, "Metis_208");
				break;
			}
			case 26221: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000142);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000202, EnemyMetis, "Metis_209");
				break;
			}
			case 26251: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000143);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000203, EnemyMetis, "Metis_210");
				break;
			}
			case 26281: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000144);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000204, EnemyMetis, "Metis_211");
				break;
			}
			case 26311: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000145);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000205, EnemyMetis, "Metis_212");
				break;
			}
			case 26341: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000146);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000206, EnemyMetis, "Metis_213");
				break;
			}
			case 26371: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000147);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000207, EnemyMetis, "Metis_214");
				break;
			}
			case 26401: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000148);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000208, EnemyMetis, "Metis_215");
				break;
			}
			case 26431: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000149);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000209, EnemyMetis, "Metis_216");
				break;
			}
			case 26461: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000150);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000210, EnemyMetis, "Metis_217");
				break;
			}
			case 26491: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000151);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000211, EnemyMetis, "Metis_218");
				break;
			}
			case 26521: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000152);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000212, EnemyMetis, "Metis_219");
				break;
			}
			case 26551: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000153);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000213, EnemyMetis, "Metis_220");
				break;
			}
			case 26581: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000154);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000214, EnemyMetis, "Metis_221");
				break;
			}
			case 26611: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000155);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000215, EnemyMetis, "Metis_222");
				break;
			}
			case 26641: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000156);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000216, EnemyMetis, "Metis_223");
				break;
			}
			case 26671: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000157);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000217, EnemyMetis, "Metis_224");
				break;
			}
			case 26701: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000158);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000218, EnemyMetis, "Metis_225");
				break;
			}
			case 26731: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000159);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000219, EnemyMetis, "Metis_226");
				break;
			}
			case 26761: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000160);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000220, EnemyMetis, "Metis_227");
				break;
			}
			case 26791: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000161);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000221, EnemyMetis, "Metis_228");
				break;
			}
			case 26821: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000162);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000222, EnemyMetis, "Metis_229");
				break;
			}
			case 26851: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000163);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000223, EnemyMetis, "Metis_230");
				break;
			}
			case 26881: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000164);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000224, EnemyMetis, "Metis_231");
				break;
			}
			case 26911: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000165);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000225, EnemyMetis, "Metis_232");
				break;
			}
			case 26941: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000166);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000226, EnemyMetis, "Metis_233");
				break;
			}
			case 26971: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000167);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000227, EnemyMetis, "Metis_234");
				break;
			}
			case 27001: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000168);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000228, EnemyMetis, "Metis_235");
				break;
			}
			case 27031: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000169);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000229, EnemyMetis, "Metis_236");
				break;
			}
			case 27061: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000170);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000230, EnemyMetis, "Metis_237");
				break;
			}
			case 27091: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000171);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000231, EnemyMetis, "Metis_238");
				break;
			}
			case 27121: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000172);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000232, EnemyMetis, "Metis_239");
				break;
			}
			case 27151: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000173);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000233, EnemyMetis, "Metis_240");
				break;
			}
			case 27181: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000174);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000234, EnemyMetis, "Metis_241");
				break;
			}
			case 27211: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000175);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000235, EnemyMetis, "Metis_242");
				break;
			}
			case 27241: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000176);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000236, EnemyMetis, "Metis_243");
				break;
			}
			case 27271: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000177);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000237, EnemyMetis, "Metis_244");
				break;
			}
			case 27301: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000178);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000238, EnemyMetis, "Metis_245");
				break;
			}
			case 27331: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000179);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000239, EnemyMetis, "Metis_246");
				break;
			}
			case 27361: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000180);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000240, EnemyMetis, "Metis_247");
				break;
			}
			case 27391: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000181);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000241, EnemyMetis, "Metis_248");
				break;
			}
			case 27421: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000182);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000242, EnemyMetis, "Metis_249");
				break;
			}
			case 27451: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000183);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000243, EnemyMetis, "Metis_250");
				break;
			}
			case 27481: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000184);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000244, EnemyMetis, "Metis_251");
				break;
			}
			case 27511: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000185);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000245, EnemyMetis, "Metis_252");
				break;
			}
			case 27541: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000186);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000246, EnemyMetis, "Metis_253");
				break;
			}
			case 27571: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000187);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000247, EnemyMetis, "Metis_254");
				break;
			}
			case 27601: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000188);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000248, EnemyMetis, "Metis_255");
				break;
			}
			case 27631: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000189);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000249, EnemyMetis, "Metis_256");
				break;
			}
			case 27661: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000190);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000250, EnemyMetis, "Metis_257");
				break;
			}
			case 27691: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000191);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000251, EnemyMetis, "Metis_258");
				break;
			}
			case 27721: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000192);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000252, EnemyMetis, "Metis_259");
				break;
			}
			case 27751: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000193);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000253, EnemyMetis, "Metis_260");
				break;
			}
			case 27781: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000194);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000254, EnemyMetis, "Metis_261");
				break;
			}
			case 27811: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000195);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000255, EnemyMetis, "Metis_262");
				break;
			}
			case 27841: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000196);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000256, EnemyMetis, "Metis_263");
				break;
			}
			case 27871: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000197);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000257, EnemyMetis, "Metis_264");
				break;
			}
			case 27901: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000198);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000258, EnemyMetis, "Metis_265");
				break;
			}
			case 27931: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000199);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000259, EnemyMetis, "Metis_266");
				break;
			}
			case 27961: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000200);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000260, EnemyMetis, "Metis_267");
				break;
			}
			case 27991: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000201);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000261, EnemyMetis, "Metis_268");
				break;
			}
			case 28021: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000202);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000262, EnemyMetis, "Metis_269");
				break;
			}
			case 28051: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000203);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000263, EnemyMetis, "Metis_270");
				break;
			}
			case 28081: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000204);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000264, EnemyMetis, "Metis_271");
				break;
			}
			case 28111: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000205);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000265, EnemyMetis, "Metis_272");
				break;
			}
			case 28141: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000206);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000266, EnemyMetis, "Metis_273");
				break;
			}
			case 28171: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000207);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000267, EnemyMetis, "Metis_274");
				break;
			}
			case 28201: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000208);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000268, EnemyMetis, "Metis_275");
				break;
			}
			case 28231: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000209);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000269, EnemyMetis, "Metis_276");
				break;
			}
			case 28261: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000210);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000270, EnemyMetis, "Metis_277");
				break;
			}
			case 28291: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000211);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000271, EnemyMetis, "Metis_278");
				break;
			}
			case 28321: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000212);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000272, EnemyMetis, "Metis_279");
				break;
			}
			case 28351: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000213);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000273, EnemyMetis, "Metis_280");
				break;
			}
			case 28381: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000214);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000274, EnemyMetis, "Metis_281");
				break;
			}
			case 28411: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000215);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000275, EnemyMetis, "Metis_282");
				break;
			}
			case 28441: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000216);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000276, EnemyMetis, "Metis_283");
				break;
			}
			case 28471: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000217);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000277, EnemyMetis, "Metis_284");
				break;
			}
			case 28501: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000218);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000278, EnemyMetis, "Metis_285");
				break;
			}
			case 28531: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000219);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000279, EnemyMetis, "Metis_286");
				break;
			}
			case 28561: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000220);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000280, EnemyMetis, "Metis_287");
				break;
			}
			case 28591: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000221);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000281, EnemyMetis, "Metis_288");
				break;
			}
			case 28621: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000222);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000282, EnemyMetis, "Metis_289");
				break;
			}
			case 28651: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000223);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000283, EnemyMetis, "Metis_290");
				break;
			}
			case 28681: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000224);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000284, EnemyMetis, "Metis_291");
				break;
			}
			case 28711: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000225);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000285, EnemyMetis, "Metis_292");
				break;
			}
			case 28741: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000226);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000286, EnemyMetis, "Metis_293");
				break;
			}
			case 28771: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000227);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000287, EnemyMetis, "Metis_294");
				break;
			}
			case 28801: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000228);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000288, EnemyMetis, "Metis_295");
				break;
			}
			case 28831: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000229);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000289, EnemyMetis, "Metis_296");
				break;
			}
			case 28861: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000230);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000290, EnemyMetis, "Metis_297");
				break;
			}
			case 28891: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000231);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000291, EnemyMetis, "Metis_298");
				break;
			}
			case 28921: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000232);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000292, EnemyMetis, "Metis_299");
				break;
			}
			case 28951: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000233);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000293, EnemyMetis, "Metis_300");
				break;
			}
			case 28981: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000234);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000294, EnemyMetis, "Metis_301");
				break;
			}
			case 29011: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000235);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000295, EnemyMetis, "Metis_302");
				break;
			}
			case 29041: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000236);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000296, EnemyMetis, "Metis_303");
				break;
			}
			case 29071: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000237);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000297, EnemyMetis, "Metis_304");
				break;
			}
			case 29101: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000238);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000298, EnemyMetis, "Metis_305");
				break;
			}
			case 29131: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000239);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000299, EnemyMetis, "Metis_306");
				break;
			}
			case 29161: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000240);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000300, EnemyMetis, "Metis_307");
				break;
			}
			case 29191: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000241);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000301, EnemyMetis, "Metis_308");
				break;
			}
			case 29221: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000242);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000302, EnemyMetis, "Metis_309");
				break;
			}
			case 29251: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000243);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000303, EnemyMetis, "Metis_310");
				break;
			}
			case 29281: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000244);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000304, EnemyMetis, "Metis_311");
				break;
			}
			case 29311: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000245);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000305, EnemyMetis, "Metis_312");
				break;
			}
			case 29341: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000246);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000306, EnemyMetis, "Metis_313");
				break;
			}
			case 29371: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000247);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000307, EnemyMetis, "Metis_314");
				break;
			}
			case 29401: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000248);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000308, EnemyMetis, "Metis_315");
				break;
			}
			case 29431: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000249);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000309, EnemyMetis, "Metis_316");
				break;
			}
			case 29461: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000250);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000310, EnemyMetis, "Metis_317");
				break;
			}
			case 29491: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000251);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000311, EnemyMetis, "Metis_318");
				break;
			}
			case 29521: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000252);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000312, EnemyMetis, "Metis_319");
				break;
			}
			case 29551: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000253);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000313, EnemyMetis, "Metis_320");
				break;
			}
			case 29581: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000254);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000314, EnemyMetis, "Metis_321");
				break;
			}
			case 29611: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000255);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000315, EnemyMetis, "Metis_322");
				break;
			}
			case 29641: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000256);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000316, EnemyMetis, "Metis_323");
				break;
			}
			case 29671: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000257);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000317, EnemyMetis, "Metis_324");
				break;
			}
			case 29701: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000258);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000318, EnemyMetis, "Metis_325");
				break;
			}
			case 29731: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000259);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000319, EnemyMetis, "Metis_326");
				break;
			}
			case 29761: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000260);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000320, EnemyMetis, "Metis_327");
				break;
			}
			case 29791: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000261);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000321, EnemyMetis, "Metis_328");
				break;
			}
			case 29821: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000262);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000322, EnemyMetis, "Metis_329");
				break;
			}
			case 29851: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000263);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000323, EnemyMetis, "Metis_330");
				break;
			}
			case 29881: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000264);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000324, EnemyMetis, "Metis_331");
				break;
			}
			case 29911: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000265);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000325, EnemyMetis, "Metis_332");
				break;
			}
			case 29941: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000266);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000326, EnemyMetis, "Metis_333");
				break;
			}
			case 29971: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000267);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000327, EnemyMetis, "Metis_334");
				break;
			}
			case 30001: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000268);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000328, EnemyMetis, "Metis_335");
				break;
			}
			case 30031: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000269);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000329, EnemyMetis, "Metis_336");
				break;
			}
			case 30061: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000270);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000330, EnemyMetis, "Metis_337");
				break;
			}
			case 30091: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000271);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000331, EnemyMetis, "Metis_338");
				break;
			}
			case 30121: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000272);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000332, EnemyMetis, "Metis_339");
				break;
			}
			case 30151: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000273);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000333, EnemyMetis, "Metis_340");
				break;
			}
			case 30181: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000274);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000334, EnemyMetis, "Metis_341");
				break;
			}
			case 30211: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000275);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000335, EnemyMetis, "Metis_342");
				break;
			}
			case 30241: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000276);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000336, EnemyMetis, "Metis_343");
				break;
			}
			case 30271: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000277);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000337, EnemyMetis, "Metis_344");
				break;
			}
			case 30301: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000278);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000338, EnemyMetis, "Metis_345");
				break;
			}
			case 30331: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000279);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000339, EnemyMetis, "Metis_346");
				break;
			}
			case 30361: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000280);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000340, EnemyMetis, "Metis_347");
				break;
			}
			case 30391: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000281);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000341, EnemyMetis, "Metis_348");
				break;
			}
			case 30421: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000282);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000342, EnemyMetis, "Metis_349");
				break;
			}
			case 30451: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000283);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000343, EnemyMetis, "Metis_350");
				break;
			}
			case 30481: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000284);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000344, EnemyMetis, "Metis_351");
				break;
			}
			case 30511: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000285);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000345, EnemyMetis, "Metis_352");
				break;
			}
			case 30541: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000286);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000346, EnemyMetis, "Metis_353");
				break;
			}
			case 30571: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000287);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000347, EnemyMetis, "Metis_354");
				break;
			}
			case 30601: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000288);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000348, EnemyMetis, "Metis_355");
				break;
			}
			case 30631: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000289);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000349, EnemyMetis, "Metis_356");
				break;
			}
			case 30661: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000290);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000350, EnemyMetis, "Metis_357");
				break;
			}
			case 30691: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000291);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000351, EnemyMetis, "Metis_358");
				break;
			}
			case 30721: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000292);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000352, EnemyMetis, "Metis_359");
				break;
			}
			case 30751: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000293);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000353, EnemyMetis, "Metis_360");
				break;
			}
			case 30781: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000294);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000354, EnemyMetis, "Metis_361");
				break;
			}
			case 30811: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000295);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000355, EnemyMetis, "Metis_362");
				break;
			}
			case 30841: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000296);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000356, EnemyMetis, "Metis_363");
				break;
			}
			case 30871: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000297);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000357, EnemyMetis, "Metis_364");
				break;
			}
			case 30901: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000298);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000358, EnemyMetis, "Metis_365");
				break;
			}
			case 30931: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000299);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000359, EnemyMetis, "Metis_366");
				break;
			}
			case 30961: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000300);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000360, EnemyMetis, "Metis_367");
				break;
			}
			case 30991: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000301);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000361, EnemyMetis, "Metis_368");
				break;
			}
			case 31021: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000302);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000362, EnemyMetis, "Metis_369");
				break;
			}
			case 31051: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000303);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000363, EnemyMetis, "Metis_370");
				break;
			}
			case 31081: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000304);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000364, EnemyMetis, "Metis_371");
				break;
			}
			case 31111: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000305);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000365, EnemyMetis, "Metis_372");
				break;
			}
			case 31141: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000306);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000366, EnemyMetis, "Metis_373");
				break;
			}
			case 31171: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000307);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000367, EnemyMetis, "Metis_374");
				break;
			}
			case 31201: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000308);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000368, EnemyMetis, "Metis_375");
				break;
			}
			case 31231: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000309);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000369, EnemyMetis, "Metis_376");
				break;
			}
			case 31261: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000310);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000370, EnemyMetis, "Metis_377");
				break;
			}
			case 31291: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000311);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000371, EnemyMetis, "Metis_378");
				break;
			}
			case 31321: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000312);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000372, EnemyMetis, "Metis_379");
				break;
			}
			case 31351: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000313);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000373, EnemyMetis, "Metis_380");
				break;
			}
			case 31381: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000314);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000374, EnemyMetis, "Metis_381");
				break;
			}
			case 31411: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000315);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000375, EnemyMetis, "Metis_382");
				break;
			}
			case 31441: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000316);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000376, EnemyMetis, "Metis_383");
				break;
			}
			case 31471: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000317);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000377, EnemyMetis, "Metis_384");
				break;
			}
			case 31501: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000318);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000378, EnemyMetis, "Metis_385");
				break;
			}
			case 31531: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000319);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000379, EnemyMetis, "Metis_386");
				break;
			}
			case 31561: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000320);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000380, EnemyMetis, "Metis_387");
				break;
			}
			case 31591: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000321);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000381, EnemyMetis, "Metis_388");
				break;
			}
			case 31621: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000322);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000382, EnemyMetis, "Metis_389");
				break;
			}
			case 31651: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000323);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000383, EnemyMetis, "Metis_390");
				break;
			}
			case 31681: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000324);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000384, EnemyMetis, "Metis_391");
				break;
			}
			case 31711: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000325);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000385, EnemyMetis, "Metis_392");
				break;
			}
			case 31741: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000326);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000386, EnemyMetis, "Metis_393");
				break;
			}
			case 31771: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000327);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000387, EnemyMetis, "Metis_394");
				break;
			}
			case 31801: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000328);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000388, EnemyMetis, "Metis_395");
				break;
			}
			case 31831: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000329);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000389, EnemyMetis, "Metis_396");
				break;
			}
			case 31861: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000330);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000390, EnemyMetis, "Metis_397");
				break;
			}
			case 31891: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000331);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000391, EnemyMetis, "Metis_398");
				break;
			}
			case 31921: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000332);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000392, EnemyMetis, "Metis_399");
				break;
			}
			case 31951: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000333);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000393, EnemyMetis, "Metis_400");
				break;
			}
			case 31981: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000334);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000394, EnemyMetis, "Metis_401");
				break;
			}
			case 32011: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000335);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000395, EnemyMetis, "Metis_402");
				break;
			}
			case 32041: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000336);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000396, EnemyMetis, "Metis_403");
				break;
			}
			case 32071: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000337);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000397, EnemyMetis, "Metis_404");
				break;
			}
			case 32101: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000338);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000398, EnemyMetis, "Metis_405");
				break;
			}
			case 32131: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000339);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000399, EnemyMetis, "Metis_406");
				break;
			}
			case 32161: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000340);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000400, EnemyMetis, "Metis_407");
				break;
			}
			case 32191: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000341);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000401, EnemyMetis, "Metis_408");
				break;
			}
			case 32221: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000342);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000402, EnemyMetis, "Metis_409");
				break;
			}
			case 32251: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000343);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000403, EnemyMetis, "Metis_410");
				break;
			}
			case 32281: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000344);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000404, EnemyMetis, "Metis_411");
				break;
			}
			case 32311: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000345);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000405, EnemyMetis, "Metis_412");
				break;
			}
			case 32341: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000346);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000406, EnemyMetis, "Metis_413");
				break;
			}
			case 32371: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000347);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000407, EnemyMetis, "Metis_414");
				break;
			}
			case 32401: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000348);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000408, EnemyMetis, "Metis_415");
				break;
			}
			case 32431: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000349);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000409, EnemyMetis, "Metis_416");
				break;
			}
			case 32461: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000350);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000410, EnemyMetis, "Metis_417");
				break;
			}
			case 32491: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000351);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000411, EnemyMetis, "Metis_418");
				break;
			}
			case 32521: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000352);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000412, EnemyMetis, "Metis_419");
				break;
			}
			case 32551: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000353);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000413, EnemyMetis, "Metis_420");
				break;
			}
			case 32581: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000354);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000414, EnemyMetis, "Metis_421");
				break;
			}
			case 32611: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000355);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000415, EnemyMetis, "Metis_422");
				break;
			}
			case 32641: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000356);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000416, EnemyMetis, "Metis_423");
				break;
			}
			case 32671: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000357);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000417, EnemyMetis, "Metis_424");
				break;
			}
			case 32701: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000358);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000418, EnemyMetis, "Metis_425");
				break;
			}
			case 32731: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000359);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000419, EnemyMetis, "Metis_426");
				break;
			}
			case 32761: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000360);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000420, EnemyMetis, "Metis_427");
				break;
			}
			case 32791: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000361);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000421, EnemyMetis, "Metis_428");
				break;
			}
			case 32821: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000362);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000422, EnemyMetis, "Metis_429");
				break;
			}
			case 32851: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000363);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000423, EnemyMetis, "Metis_430");
				break;
			}
			case 32881: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000364);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000424, EnemyMetis, "Metis_431");
				break;
			}
			case 32911: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000365);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000425, EnemyMetis, "Metis_432");
				break;
			}
			case 32941: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000366);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000426, EnemyMetis, "Metis_433");
				break;
			}
			case 32971: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000367);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000427, EnemyMetis, "Metis_434");
				break;
			}
			case 33001: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000368);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000428, EnemyMetis, "Metis_435");
				break;
			}
			case 33031: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000369);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000429, EnemyMetis, "Metis_436");
				break;
			}
			case 33061: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000370);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000430, EnemyMetis, "Metis_437");
				break;
			}
			case 33091: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000371);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000431, EnemyMetis, "Metis_438");
				break;
			}
			case 33121: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000372);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000432, EnemyMetis, "Metis_439");
				break;
			}
			case 33151: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000373);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000433, EnemyMetis, "Metis_440");
				break;
			}
			case 33181: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000374);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000434, EnemyMetis, "Metis_441");
				break;
			}
			case 33211: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000375);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000435, EnemyMetis, "Metis_442");
				break;
			}
			case 33241: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000376);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000436, EnemyMetis, "Metis_443");
				break;
			}
			case 33271: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000377);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000437, EnemyMetis, "Metis_444");
				break;
			}
			case 33301: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000378);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000438, EnemyMetis, "Metis_445");
				break;
			}
			case 33331: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000379);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000439, EnemyMetis, "Metis_446");
				break;
			}
			case 33361: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000380);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000440, EnemyMetis, "Metis_447");
				break;
			}
			case 33391: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000381);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000441, EnemyMetis, "Metis_448");
				break;
			}
			case 33421: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000382);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000442, EnemyMetis, "Metis_449");
				break;
			}
			case 33451: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000383);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000443, EnemyMetis, "Metis_450");
				break;
			}
			case 33481: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000384);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000444, EnemyMetis, "Metis_451");
				break;
			}
			case 33511: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000385);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000445, EnemyMetis, "Metis_452");
				break;
			}
			case 33541: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000386);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000446, EnemyMetis, "Metis_453");
				break;
			}
			case 33571: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000387);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000447, EnemyMetis, "Metis_454");
				break;
			}
			case 33601: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000388);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000448, EnemyMetis, "Metis_455");
				break;
			}
			case 33631: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000389);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000449, EnemyMetis, "Metis_456");
				break;
			}
			case 33661: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000390);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000450, EnemyMetis, "Metis_457");
				break;
			}
			case 33691: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000391);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000451, EnemyMetis, "Metis_458");
				break;
			}
			case 33721: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000392);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000452, EnemyMetis, "Metis_459");
				break;
			}
			case 33751: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000393);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000453, EnemyMetis, "Metis_460");
				break;
			}
			case 33781: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000394);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000454, EnemyMetis, "Metis_461");
				break;
			}
			case 33811: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000395);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000455, EnemyMetis, "Metis_462");
				break;
			}
			case 33841: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000396);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000456, EnemyMetis, "Metis_463");
				break;
			}
			case 33871: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000397);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000457, EnemyMetis, "Metis_464");
				break;
			}
			case 33901: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000398);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000458, EnemyMetis, "Metis_465");
				break;
			}
			case 33931: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000399);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000459, EnemyMetis, "Metis_466");
				break;
			}
			case 33961: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000400);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000460, EnemyMetis, "Metis_467");
				break;
			}
			case 33991: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000401);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000461, EnemyMetis, "Metis_468");
				break;
			}
			case 34021: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000402);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000462, EnemyMetis, "Metis_469");
				break;
			}
			case 34051: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000403);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000463, EnemyMetis, "Metis_470");
				break;
			}
			case 34081: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000404);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000464, EnemyMetis, "Metis_471");
				break;
			}
			case 34111: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000405);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000465, EnemyMetis, "Metis_472");
				break;
			}
			case 34141: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000406);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000466, EnemyMetis, "Metis_473");
				break;
			}
			case 34171: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000407);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000467, EnemyMetis, "Metis_474");
				break;
			}
			case 34201: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000408);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000468, EnemyMetis, "Metis_475");
				break;
			}
			case 34231: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000409);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000469, EnemyMetis, "Metis_476");
				break;
			}
			case 34261: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000410);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000470, EnemyMetis, "Metis_477");
				break;
			}
			case 34291: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000411);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000471, EnemyMetis, "Metis_478");
				break;
			}
			case 34321: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000412);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000472, EnemyMetis, "Metis_479");
				break;
			}
			case 34351: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000413);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000473, EnemyMetis, "Metis_480");
				break;
			}
			case 34381: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000414);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000474, EnemyMetis, "Metis_481");
				break;
			}
			case 34411: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000415);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000475, EnemyMetis, "Metis_482");
				break;
			}
			case 34441: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000416);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000476, EnemyMetis, "Metis_483");
				break;
			}
			case 34471: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000417);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000477, EnemyMetis, "Metis_484");
				break;
			}
			case 34501: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000418);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000478, EnemyMetis, "Metis_485");
				break;
			}
			case 34531: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000419);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000479, EnemyMetis, "Metis_486");
				break;
			}
			case 34561: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000420);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000480, EnemyMetis, "Metis_487");
				break;
			}
			case 34591: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000421);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000481, EnemyMetis, "Metis_488");
				break;
			}
			case 34621: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000422);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000482, EnemyMetis, "Metis_489");
				break;
			}
			case 34651: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000423);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000483, EnemyMetis, "Metis_490");
				break;
			}
			case 34681: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000424);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000484, EnemyMetis, "Metis_491");
				break;
			}
			case 34711: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000425);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000485, EnemyMetis, "Metis_492");
				break;
			}
			case 34741: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000426);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000486, EnemyMetis, "Metis_493");
				break;
			}
			case 34771: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000427);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000487, EnemyMetis, "Metis_494");
				break;
			}
			case 34801: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000428);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000488, EnemyMetis, "Metis_495");
				break;
			}
			case 34831: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000429);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000489, EnemyMetis, "Metis_496");
				break;
			}
			case 34861: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000430);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000490, EnemyMetis, "Metis_497");
				break;
			}
			case 34891: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000431);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000491, EnemyMetis, "Metis_498");
				break;
			}
			case 34921: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000432);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000492, EnemyMetis, "Metis_499");
				break;
			}
			case 34951: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000433);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000493, EnemyMetis, "Metis_500");
				break;
			}
			case 34981: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000434);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000494, EnemyMetis, "Metis_501");
				break;
			}
			case 35011: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000435);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000495, EnemyMetis, "Metis_502");
				break;
			}
			case 35041: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000436);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000496, EnemyMetis, "Metis_503");
				break;
			}
			case 35071: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000437);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000497, EnemyMetis, "Metis_504");
				break;
			}
			case 35101: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000438);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000498, EnemyMetis, "Metis_505");
				break;
			}
			case 35131: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000439);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000499, EnemyMetis, "Metis_506");
				break;
			}
			case 35161: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000440);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000500, EnemyMetis, "Metis_507");
				break;
			}
			case 35191: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000441);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000501, EnemyMetis, "Metis_508");
				break;
			}
			case 35221: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000442);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000502, EnemyMetis, "Metis_509");
				break;
			}
			case 35251: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000443);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000503, EnemyMetis, "Metis_510");
				break;
			}
			case 35281: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000444);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000504, EnemyMetis, "Metis_511");
				break;
			}
			case 35311: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000445);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000505, EnemyMetis, "Metis_512");
				break;
			}
			case 35341: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000446);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000506, EnemyMetis, "Metis_513");
				break;
			}
			case 35371: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000447);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000507, EnemyMetis, "Metis_514");
				break;
			}
			case 35401: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000448);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000508, EnemyMetis, "Metis_515");
				break;
			}
			case 35431: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000449);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000509, EnemyMetis, "Metis_516");
				break;
			}
			case 35461: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000450);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000510, EnemyMetis, "Metis_517");
				break;
			}
			case 35491: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000451);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000511, EnemyMetis, "Metis_518");
				break;
			}
			case 35521: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000452);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000512, EnemyMetis, "Metis_519");
				break;
			}
			case 35551: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000453);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000513, EnemyMetis, "Metis_520");
				break;
			}
			case 35581: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000454);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000514, EnemyMetis, "Metis_521");
				break;
			}
			case 35611: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000455);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000515, EnemyMetis, "Metis_522");
				break;
			}
			case 35641: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000456);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000516, EnemyMetis, "Metis_523");
				break;
			}
			case 35671: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000457);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000517, EnemyMetis, "Metis_524");
				break;
			}
			case 35701: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000458);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000518, EnemyMetis, "Metis_525");
				break;
			}
			case 35731: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000459);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000519, EnemyMetis, "Metis_526");
				break;
			}
			case 35761: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000460);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000520, EnemyMetis, "Metis_527");
				break;
			}
			case 35791: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000461);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000521, EnemyMetis, "Metis_528");
				break;
			}
			case 35821: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000462);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000522, EnemyMetis, "Metis_529");
				break;
			}
			case 35851: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000463);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000523, EnemyMetis, "Metis_530");
				break;
			}
			case 35881: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000464);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000524, EnemyMetis, "Metis_531");
				break;
			}
			case 35911: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000465);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000525, EnemyMetis, "Metis_532");
				break;
			}
			case 35941: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000466);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000526, EnemyMetis, "Metis_533");
				break;
			}
			case 35971: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000467);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000527, EnemyMetis, "Metis_534");
				break;
			}
			case 36001: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000468);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000528, EnemyMetis, "Metis_535");
				break;
			}
			case 36031: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000469);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000529, EnemyMetis, "Metis_536");
				break;
			}
			case 36061: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000470);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000530, EnemyMetis, "Metis_537");
				break;
			}
			case 36091: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000471);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000531, EnemyMetis, "Metis_538");
				break;
			}
			case 36121: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000472);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000532, EnemyMetis, "Metis_539");
				break;
			}
			case 36151: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000473);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000533, EnemyMetis, "Metis_540");
				break;
			}
			case 36181: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000474);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000534, EnemyMetis, "Metis_541");
				break;
			}
			case 36211: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000475);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000535, EnemyMetis, "Metis_542");
				break;
			}
			case 36241: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000476);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000536, EnemyMetis, "Metis_543");
				break;
			}
			case 36271: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000477);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000537, EnemyMetis, "Metis_544");
				break;
			}
			case 36301: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000478);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000538, EnemyMetis, "Metis_545");
				break;
			}
			case 36331: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000479);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000539, EnemyMetis, "Metis_546");
				break;
			}
			case 36361: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000480);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000540, EnemyMetis, "Metis_547");
				break;
			}
			case 36391: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000481);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000541, EnemyMetis, "Metis_548");
				break;
			}
			case 36421: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000482);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000542, EnemyMetis, "Metis_549");
				break;
			}
			case 36451: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000483);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000543, EnemyMetis, "Metis_550");
				break;
			}
			case 36481: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000484);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000544, EnemyMetis, "Metis_551");
				break;
			}
			case 36511: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000485);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000545, EnemyMetis, "Metis_552");
				break;
			}
			case 36541: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000486);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000546, EnemyMetis, "Metis_553");
				break;
			}
			case 36571: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000487);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000547, EnemyMetis, "Metis_554");
				break;
			}
			case 36601: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000488);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000548, EnemyMetis, "Metis_555");
				break;
			}
			case 36631: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000489);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000549, EnemyMetis, "Metis_556");
				break;
			}
			case 36661: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000490);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000550, EnemyMetis, "Metis_557");
				break;
			}
			case 36691: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000491);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000551, EnemyMetis, "Metis_558");
				break;
			}
			case 36721: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000492);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000552, EnemyMetis, "Metis_559");
				break;
			}
			case 36751: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000493);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000553, EnemyMetis, "Metis_560");
				break;
			}
			case 36781: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000494);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000554, EnemyMetis, "Metis_561");
				break;
			}
			case 36811: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000495);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000555, EnemyMetis, "Metis_562");
				break;
			}
			case 36841: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000496);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000556, EnemyMetis, "Metis_563");
				break;
			}
			case 36871: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000497);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000557, EnemyMetis, "Metis_564");
				break;
			}
			case 36901: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000498);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000558, EnemyMetis, "Metis_565");
				break;
			}
			case 36931: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000499);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000559, EnemyMetis, "Metis_566");
				break;
			}
			case 36961: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000500);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000560, EnemyMetis, "Metis_567");
				break;
			}
			case 36991: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000501);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000561, EnemyMetis, "Metis_568");
				break;
			}
			case 37021: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000502);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000562, EnemyMetis, "Metis_569");
				break;
			}
			case 37051: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000503);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000563, EnemyMetis, "Metis_570");
				break;
			}
			case 37081: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000504);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000564, EnemyMetis, "Metis_571");
				break;
			}
			case 37111: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000505);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000565, EnemyMetis, "Metis_572");
				break;
			}
			case 37141: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000506);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000566, EnemyMetis, "Metis_573");
				break;
			}
			case 37171: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000507);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000567, EnemyMetis, "Metis_574");
				break;
			}
			case 37201: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000508);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000568, EnemyMetis, "Metis_575");
				break;
			}
			case 37231: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000509);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000569, EnemyMetis, "Metis_576");
				break;
			}
			case 37261: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000510);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000570, EnemyMetis, "Metis_577");
				break;
			}
			case 37291: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000511);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000571, EnemyMetis, "Metis_578");
				break;
			}
			case 37321: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000512);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000572, EnemyMetis, "Metis_579");
				break;
			}
			case 37351: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000513);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000573, EnemyMetis, "Metis_580");
				break;
			}
			case 37381: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000514);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000574, EnemyMetis, "Metis_581");
				break;
			}
			case 37411: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000515);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000575, EnemyMetis, "Metis_582");
				break;
			}
			case 37441: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000516);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000576, EnemyMetis, "Metis_583");
				break;
			}
			case 37471: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000517);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000577, EnemyMetis, "Metis_584");
				break;
			}
			case 37501: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000518);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000578, EnemyMetis, "Metis_585");
				break;
			}
			case 37531: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000519);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000579, EnemyMetis, "Metis_586");
				break;
			}
			case 37561: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000520);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000580, EnemyMetis, "Metis_587");
				break;
			}
			case 37591: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000521);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000581, EnemyMetis, "Metis_588");
				break;
			}
			case 37621: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000522);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000582, EnemyMetis, "Metis_589");
				break;
			}
			case 37651: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000523);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000583, EnemyMetis, "Metis_590");
				break;
			}
			case 37681: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000524);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000584, EnemyMetis, "Metis_591");
				break;
			}
			case 37711: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000525);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000585, EnemyMetis, "Metis_592");
				break;
			}
			case 37741: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000526);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000586, EnemyMetis, "Metis_593");
				break;
			}
			case 37771: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000527);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000587, EnemyMetis, "Metis_594");
				break;
			}
			case 37801: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000528);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000588, EnemyMetis, "Metis_595");
				break;
			}
			case 37831: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000529);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000589, EnemyMetis, "Metis_596");
				break;
			}
			case 37861: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000530);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000590, EnemyMetis, "Metis_597");
				break;
			}
			case 37891: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000531);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000591, EnemyMetis, "Metis_598");
				break;
			}
			case 37921: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000532);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000592, EnemyMetis, "Metis_599");
				break;
			}
			case 37951: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000533);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000593, EnemyMetis, "Metis_600");
				break;
			}
			case 37981: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000534);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000594, EnemyMetis, "Metis_601");
				break;
			}
			case 38011: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000535);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000595, EnemyMetis, "Metis_602");
				break;
			}
			case 38041: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000536);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000596, EnemyMetis, "Metis_603");
				break;
			}
			case 38071: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000537);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000597, EnemyMetis, "Metis_604");
				break;
			}
			case 38101: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000538);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000598, EnemyMetis, "Metis_605");
				break;
			}
			case 38131: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000539);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000599, EnemyMetis, "Metis_606");
				break;
			}
			case 38161: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000540);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000600, EnemyMetis, "Metis_607");
				break;
			}
			case 38191: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000541);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000601, EnemyMetis, "Metis_608");
				break;
			}
			case 38221: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000542);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000602, EnemyMetis, "Metis_609");
				break;
			}
			case 38251: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000543);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000603, EnemyMetis, "Metis_610");
				break;
			}
			case 38281: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000544);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000604, EnemyMetis, "Metis_611");
				break;
			}
			case 38311: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000545);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000605, EnemyMetis, "Metis_612");
				break;
			}
			case 38341: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000546);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000606, EnemyMetis, "Metis_613");
				break;
			}
			case 38371: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000547);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000607, EnemyMetis, "Metis_614");
				break;
			}
			case 38401: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000548);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000608, EnemyMetis, "Metis_615");
				break;
			}
			case 38431: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000549);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000609, EnemyMetis, "Metis_616");
				break;
			}
			case 38461: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000550);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000610, EnemyMetis, "Metis_617");
				break;
			}
			case 38491: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000551);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000611, EnemyMetis, "Metis_618");
				break;
			}
			case 38521: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000552);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000612, EnemyMetis, "Metis_619");
				break;
			}
			case 38551: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000553);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000613, EnemyMetis, "Metis_620");
				break;
			}
			case 38581: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000554);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000614, EnemyMetis, "Metis_621");
				break;
			}
			case 38611: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000555);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000615, EnemyMetis, "Metis_622");
				break;
			}
			case 38641: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000556);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000616, EnemyMetis, "Metis_623");
				break;
			}
			case 38671: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000557);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000617, EnemyMetis, "Metis_624");
				break;
			}
			case 38701: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000558);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000618, EnemyMetis, "Metis_625");
				break;
			}
			case 38731: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000559);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000619, EnemyMetis, "Metis_626");
				break;
			}
			case 38761: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000560);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000620, EnemyMetis, "Metis_627");
				break;
			}
			case 38791: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000561);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000621, EnemyMetis, "Metis_628");
				break;
			}
			case 38821: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000562);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000622, EnemyMetis, "Metis_629");
				break;
			}
			case 38851: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000563);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000623, EnemyMetis, "Metis_630");
				break;
			}
			case 38881: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000564);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000624, EnemyMetis, "Metis_631");
				break;
			}
			case 38911: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000565);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000625, EnemyMetis, "Metis_632");
				break;
			}
			case 38941: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000566);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000626, EnemyMetis, "Metis_633");
				break;
			}
			case 38971: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000567);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000627, EnemyMetis, "Metis_634");
				break;
			}
			case 39001: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000568);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000628, EnemyMetis, "Metis_635");
				break;
			}
			case 39031: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000569);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000629, EnemyMetis, "Metis_636");
				break;
			}
			case 39061: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000570);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000630, EnemyMetis, "Metis_637");
				break;
			}
			case 39091: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000571);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000631, EnemyMetis, "Metis_638");
				break;
			}
			case 39121: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000572);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000632, EnemyMetis, "Metis_639");
				break;
			}
			case 39151: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000573);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000633, EnemyMetis, "Metis_640");
				break;
			}
			case 39181: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000574);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000634, EnemyMetis, "Metis_641");
				break;
			}
			case 39211: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000575);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000635, EnemyMetis, "Metis_642");
				break;
			}
			case 39241: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000576);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000636, EnemyMetis, "Metis_643");
				break;
			}
			case 39271: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000577);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000637, EnemyMetis, "Metis_644");
				break;
			}
			case 39301: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000578);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000638, EnemyMetis, "Metis_645");
				break;
			}
			case 39331: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000579);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000639, EnemyMetis, "Metis_646");
				break;
			}
			case 39361: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000580);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000640, EnemyMetis, "Metis_647");
				break;
			}
			case 39391: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000581);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000641, EnemyMetis, "Metis_648");
				break;
			}
			case 39421: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000582);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000642, EnemyMetis, "Metis_649");
				break;
			}
			case 39451: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000583);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000643, EnemyMetis, "Metis_650");
				break;
			}
			case 39481: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000584);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000644, EnemyMetis, "Metis_651");
				break;
			}
			case 39511: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000585);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000645, EnemyMetis, "Metis_652");
				break;
			}
			case 39541: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000586);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000646, EnemyMetis, "Metis_653");
				break;
			}
			case 39571: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000587);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000647, EnemyMetis, "Metis_654");
				break;
			}
			case 39601: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000588);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000648, EnemyMetis, "Metis_655");
				break;
			}
			case 39631: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000589);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000649, EnemyMetis, "Metis_656");
				break;
			}
			case 39661: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000590);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000650, EnemyMetis, "Metis_657");
				break;
			}
			case 39691: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000591);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000651, EnemyMetis, "Metis_658");
				break;
			}
			case 39721: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000592);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000652, EnemyMetis, "Metis_659");
				break;
			}
			case 39751: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000593);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000653, EnemyMetis, "Metis_660");
				break;
			}
			case 39781: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000594);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000654, EnemyMetis, "Metis_661");
				break;
			}
			case 39811: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000595);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000655, EnemyMetis, "Metis_662");
				break;
			}
			case 39841: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000596);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000656, EnemyMetis, "Metis_663");
				break;
			}
			case 39871: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000597);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000657, EnemyMetis, "Metis_664");
				break;
			}
			case 39901: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000598);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000658, EnemyMetis, "Metis_665");
				break;
			}
			case 39931: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000599);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000659, EnemyMetis, "Metis_666");
				break;
			}
			case 39961: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000600);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000660, EnemyMetis, "Metis_667");
				break;
			}
			case 39991: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000601);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000661, EnemyMetis, "Metis_668");
				break;
			}
			case 40021: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000602);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000662, EnemyMetis, "Metis_669");
				break;
			}
			case 40051: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000603);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000663, EnemyMetis, "Metis_670");
				break;
			}
			case 40081: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000604);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000664, EnemyMetis, "Metis_671");
				break;
			}
			case 40111: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000605);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000665, EnemyMetis, "Metis_672");
				break;
			}
			case 40141: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000606);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000666, EnemyMetis, "Metis_673");
				break;
			}
			case 40171: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000607);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000667, EnemyMetis, "Metis_674");
				break;
			}
			case 40201: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000608);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000668, EnemyMetis, "Metis_675");
				break;
			}
			case 40231: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000609);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000669, EnemyMetis, "Metis_676");
				break;
			}
			case 40261: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000610);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000670, EnemyMetis, "Metis_677");
				break;
			}
			case 40291: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000611);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000671, EnemyMetis, "Metis_678");
				break;
			}
			case 40321: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000612);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000672, EnemyMetis, "Metis_679");
				break;
			}
			case 40351: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000613);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000673, EnemyMetis, "Metis_680");
				break;
			}
			case 40381: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000614);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000674, EnemyMetis, "Metis_681");
				break;
			}
			case 40411: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000615);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000675, EnemyMetis, "Metis_682");
				break;
			}
			case 40441: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000616);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000676, EnemyMetis, "Metis_683");
				break;
			}
			case 40471: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000617);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000677, EnemyMetis, "Metis_684");
				break;
			}
			case 40501: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000618);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000678, EnemyMetis, "Metis_685");
				break;
			}
			case 40531: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000619);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000679, EnemyMetis, "Metis_686");
				break;
			}
			case 40561: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000620);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000680, EnemyMetis, "Metis_687");
				break;
			}
			case 40591: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000621);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000681, EnemyMetis, "Metis_688");
				break;
			}
			case 40621: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000622);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000682, EnemyMetis, "Metis_689");
				break;
			}
			case 40651: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000623);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000683, EnemyMetis, "Metis_690");
				break;
			}
			case 40681: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000624);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000684, EnemyMetis, "Metis_691");
				break;
			}
			case 40711: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000625);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000685, EnemyMetis, "Metis_692");
				break;
			}
			case 40741: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000626);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000686, EnemyMetis, "Metis_693");
				break;
			}
			case 40771: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000627);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000687, EnemyMetis, "Metis_694");
				break;
			}
			case 40801: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000628);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000688, EnemyMetis, "Metis_695");
				break;
			}
			case 40831: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000629);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000689, EnemyMetis, "Metis_696");
				break;
			}
			case 40861: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000630);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000690, EnemyMetis, "Metis_697");
				break;
			}
			case 40891: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000631);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000691, EnemyMetis, "Metis_698");
				break;
			}
			case 40921: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000632);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000692, EnemyMetis, "Metis_699");
				break;
			}
			case 40951: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000633);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000693, EnemyMetis, "Metis_700");
				break;
			}
			case 40981: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000634);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000694, EnemyMetis, "Metis_701");
				break;
			}
			case 41011: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000635);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000695, EnemyMetis, "Metis_702");
				break;
			}
			case 41041: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000636);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000696, EnemyMetis, "Metis_703");
				break;
			}
			case 41071: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000637);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000697, EnemyMetis, "Metis_704");
				break;
			}
			case 41101: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000638);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000698, EnemyMetis, "Metis_705");
				break;
			}
			case 41131: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000639);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000699, EnemyMetis, "Metis_706");
				break;
			}
			case 41161: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000640);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000700, EnemyMetis, "Metis_707");
				break;
			}
			case 41191: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000641);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000701, EnemyMetis, "Metis_708");
				break;
			}
			case 41221: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000642);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000702, EnemyMetis, "Metis_709");
				break;
			}
			case 41251: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000643);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000703, EnemyMetis, "Metis_710");
				break;
			}
			case 41281: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000644);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000704, EnemyMetis, "Metis_711");
				break;
			}
			case 41311: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000645);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000705, EnemyMetis, "Metis_712");
				break;
			}
			case 41341: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000646);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000706, EnemyMetis, "Metis_713");
				break;
			}
			case 41371: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000647);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000707, EnemyMetis, "Metis_714");
				break;
			}
			case 41401: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000648);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000708, EnemyMetis, "Metis_715");
				break;
			}
			case 41431: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000649);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000709, EnemyMetis, "Metis_716");
				break;
			}
			case 41461: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000650);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000710, EnemyMetis, "Metis_717");
				break;
			}
			case 41491: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000651);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000711, EnemyMetis, "Metis_718");
				break;
			}
			case 41521: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000652);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000712, EnemyMetis, "Metis_719");
				break;
			}
			case 41551: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000653);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000713, EnemyMetis, "Metis_720");
				break;
			}
			case 41581: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000654);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000714, EnemyMetis, "Metis_721");
				break;
			}
			case 41611: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000655);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000715, EnemyMetis, "Metis_722");
				break;
			}
			case 41641: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000656);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000716, EnemyMetis, "Metis_723");
				break;
			}
			case 41671: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000657);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000717, EnemyMetis, "Metis_724");
				break;
			}
			case 41701: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000658);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000718, EnemyMetis, "Metis_725");
				break;
			}
			case 41731: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000659);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000719, EnemyMetis, "Metis_726");
				break;
			}
			case 41761: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000660);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000720, EnemyMetis, "Metis_727");
				break;
			}
			case 41791: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000661);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000721, EnemyMetis, "Metis_728");
				break;
			}
			case 41821: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000662);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000722, EnemyMetis, "Metis_729");
				break;
			}
			case 41851: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000663);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000723, EnemyMetis, "Metis_730");
				break;
			}
			case 41881: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000664);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000724, EnemyMetis, "Metis_731");
				break;
			}
			case 41911: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000665);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000725, EnemyMetis, "Metis_732");
				break;
			}
			case 41941: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000666);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000726, EnemyMetis, "Metis_733");
				break;
			}
			case 41971: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000667);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000727, EnemyMetis, "Metis_734");
				break;
			}
			case 42001: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000668);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000728, EnemyMetis, "Metis_735");
				break;
			}
			case 42031: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000669);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000729, EnemyMetis, "Metis_736");
				break;
			}
			case 42061: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000670);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000730, EnemyMetis, "Metis_737");
				break;
			}
			case 42091: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000671);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000731, EnemyMetis, "Metis_738");
				break;
			}
			case 42121: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000672);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000732, EnemyMetis, "Metis_739");
				break;
			}
			case 42151: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000673);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000733, EnemyMetis, "Metis_740");
				break;
			}
			case 42181: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000674);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000734, EnemyMetis, "Metis_741");
				break;
			}
			case 42211: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000675);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000735, EnemyMetis, "Metis_742");
				break;
			}
			case 42241: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000676);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000736, EnemyMetis, "Metis_743");
				break;
			}
			case 42271: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000677);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000737, EnemyMetis, "Metis_744");
				break;
			}
			case 42301: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000678);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000738, EnemyMetis, "Metis_745");
				break;
			}
			case 42331: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000679);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000739, EnemyMetis, "Metis_746");
				break;
			}
			case 42361: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000680);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000740, EnemyMetis, "Metis_747");
				break;
			}
			case 42391: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000681);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000741, EnemyMetis, "Metis_748");
				break;
			}
			case 42421: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000682);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000742, EnemyMetis, "Metis_749");
				break;
			}
			case 42451: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000683);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000743, EnemyMetis, "Metis_750");
				break;
			}
			case 42481: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000684);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000744, EnemyMetis, "Metis_751");
				break;
			}
			case 42511: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000685);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000745, EnemyMetis, "Metis_752");
				break;
			}
			case 42541: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000686);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000746, EnemyMetis, "Metis_753");
				break;
			}
			case 42571: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000687);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000747, EnemyMetis, "Metis_754");
				break;
			}
			case 42601: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000688);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000748, EnemyMetis, "Metis_755");
				break;
			}
			case 42631: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000689);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000749, EnemyMetis, "Metis_756");
				break;
			}
			case 42661: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000690);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000750, EnemyMetis, "Metis_757");
				break;
			}
			case 42691: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000691);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000751, EnemyMetis, "Metis_758");
				break;
			}
			case 42721: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000692);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000752, EnemyMetis, "Metis_759");
				break;
			}
			case 42751: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000693);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000753, EnemyMetis, "Metis_760");
				break;
			}
			case 42781: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000694);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000754, EnemyMetis, "Metis_761");
				break;
			}
			case 42811: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000695);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000755, EnemyMetis, "Metis_762");
				break;
			}
			case 42841: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000696);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000756, EnemyMetis, "Metis_763");
				break;
			}
			case 42871: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000697);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000757, EnemyMetis, "Metis_764");
				break;
			}
			case 42901: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000698);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000758, EnemyMetis, "Metis_765");
				break;
			}
			case 42931: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000699);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000759, EnemyMetis, "Metis_766");
				break;
			}
			case 42961: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000700);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000760, EnemyMetis, "Metis_767");
				break;
			}
			case 42991: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000701);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000761, EnemyMetis, "Metis_768");
				break;
			}
			case 43021: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000702);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000762, EnemyMetis, "Metis_769");
				break;
			}
			case 43051: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000703);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000763, EnemyMetis, "Metis_770");
				break;
			}
			case 43081: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000704);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000764, EnemyMetis, "Metis_771");
				break;
			}
			case 43111: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000705);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000765, EnemyMetis, "Metis_772");
				break;
			}
			case 43141: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000706);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000766, EnemyMetis, "Metis_773");
				break;
			}
			case 43171: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000707);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000767, EnemyMetis, "Metis_774");
				break;
			}
			case 43201: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000708);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000768, EnemyMetis, "Metis_775");
				break;
			}
			case 43231: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000709);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000769, EnemyMetis, "Metis_776");
				break;
			}
			case 43261: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000710);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000770, EnemyMetis, "Metis_777");
				break;
			}
			case 43291: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000711);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000771, EnemyMetis, "Metis_778");
				break;
			}
			case 43321: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000712);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000772, EnemyMetis, "Metis_779");
				break;
			}
			case 43351: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000713);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000773, EnemyMetis, "Metis_780");
				break;
			}
			case 43381: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000714);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000774, EnemyMetis, "Metis_781");
				break;
			}
			case 43411: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000715);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000775, EnemyMetis, "Metis_782");
				break;
			}
			case 43441: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000716);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000776, EnemyMetis, "Metis_783");
				break;
			}
			case 43471: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000717);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000777, EnemyMetis, "Metis_784");
				break;
			}
			case 43501: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000718);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000778, EnemyMetis, "Metis_785");
				break;
			}
			case 43531: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000719);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000779, EnemyMetis, "Metis_786");
				break;
			}
			case 43561: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000720);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000780, EnemyMetis, "Metis_787");
				break;
			}
			case 43591: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000721);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000781, EnemyMetis, "Metis_788");
				break;
			}
			case 43621: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000722);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000782, EnemyMetis, "Metis_789");
				break;
			}
			case 43651: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000723);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000783, EnemyMetis, "Metis_790");
				break;
			}
			case 43681: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000724);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000784, EnemyMetis, "Metis_791");
				break;
			}
			case 43711: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000725);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000785, EnemyMetis, "Metis_792");
				break;
			}
			case 43741: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000726);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000786, EnemyMetis, "Metis_793");
				break;
			}
			case 43771: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000727);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000787, EnemyMetis, "Metis_794");
				break;
			}
			case 43801: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000728);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000788, EnemyMetis, "Metis_795");
				break;
			}
			case 43831: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000729);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000789, EnemyMetis, "Metis_796");
				break;
			}
			case 43861: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000730);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000790, EnemyMetis, "Metis_797");
				break;
			}
			case 43891: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000731);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000791, EnemyMetis, "Metis_798");
				break;
			}
			case 43921: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000732);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000792, EnemyMetis, "Metis_799");
				break;
			}
			case 43951: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000733);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000793, EnemyMetis, "Metis_800");
				break;
			}
			case 43981: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000734);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000794, EnemyMetis, "Metis_801");
				break;
			}
			case 44011: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000735);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000795, EnemyMetis, "Metis_802");
				break;
			}
			case 44041: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000736);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000796, EnemyMetis, "Metis_803");
				break;
			}
			case 44071: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000737);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000797, EnemyMetis, "Metis_804");
				break;
			}
			case 44101: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000738);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000798, EnemyMetis, "Metis_805");
				break;
			}
			case 44131: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000739);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000799, EnemyMetis, "Metis_806");
				break;
			}
			case 44161: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000740);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000800, EnemyMetis, "Metis_807");
				break;
			}
			case 44191: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000741);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000801, EnemyMetis, "Metis_808");
				break;
			}
			case 44221: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000742);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000802, EnemyMetis, "Metis_809");
				break;
			}
			case 44251: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000743);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000803, EnemyMetis, "Metis_810");
				break;
			}
			case 44281: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000744);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000804, EnemyMetis, "Metis_811");
				break;
			}
			case 44311: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000745);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000805, EnemyMetis, "Metis_812");
				break;
			}
			case 44341: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000746);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000806, EnemyMetis, "Metis_813");
				break;
			}
			case 44371: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000747);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000807, EnemyMetis, "Metis_814");
				break;
			}
			case 44401: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000748);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000808, EnemyMetis, "Metis_815");
				break;
			}
			case 44431: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000749);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000809, EnemyMetis, "Metis_816");
				break;
			}
			case 44461: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000750);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000810, EnemyMetis, "Metis_817");
				break;
			}
			case 44491: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000751);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000811, EnemyMetis, "Metis_818");
				break;
			}
			case 44521: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000752);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000812, EnemyMetis, "Metis_819");
				break;
			}
			case 44551: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000753);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000813, EnemyMetis, "Metis_820");
				break;
			}
			case 44581: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000754);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000814, EnemyMetis, "Metis_821");
				break;
			}
			case 44611: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000755);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000815, EnemyMetis, "Metis_822");
				break;
			}
			case 44641: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000756);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000816, EnemyMetis, "Metis_823");
				break;
			}
			case 44671: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000757);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000817, EnemyMetis, "Metis_824");
				break;
			}
			case 44701: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000758);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000818, EnemyMetis, "Metis_825");
				break;
			}
			case 44731: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000759);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000819, EnemyMetis, "Metis_826");
				break;
			}
			case 44761: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000760);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000820, EnemyMetis, "Metis_827");
				break;
			}
			case 44791: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000761);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000821, EnemyMetis, "Metis_828");
				break;
			}
			case 44821: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000762);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000822, EnemyMetis, "Metis_829");
				break;
			}
			case 44851: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000763);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000823, EnemyMetis, "Metis_830");
				break;
			}
			case 44881: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000764);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000824, EnemyMetis, "Metis_831");
				break;
			}
			case 44911: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000765);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000825, EnemyMetis, "Metis_832");
				break;
			}
			case 44941: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000766);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000826, EnemyMetis, "Metis_833");
				break;
			}
			case 44971: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000767);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000827, EnemyMetis, "Metis_834");
				break;
			}
			case 45001: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000768);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000828, EnemyMetis, "Metis_835");
				break;
			}
			case 45031: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000769);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000829, EnemyMetis, "Metis_836");
				break;
			}
			case 45061: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000770);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000830, EnemyMetis, "Metis_837");
				break;
			}
			case 45091: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000771);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000831, EnemyMetis, "Metis_838");
				break;
			}
			case 45121: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000772);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000832, EnemyMetis, "Metis_839");
				break;
			}
			case 45151: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000773);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000833, EnemyMetis, "Metis_840");
				break;
			}
			case 45181: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000774);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000834, EnemyMetis, "Metis_841");
				break;
			}
			case 45211: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000775);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000835, EnemyMetis, "Metis_842");
				break;
			}
			case 45241: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000776);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000836, EnemyMetis, "Metis_843");
				break;
			}
			case 45271: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000777);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000837, EnemyMetis, "Metis_844");
				break;
			}
			case 45301: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000778);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000838, EnemyMetis, "Metis_845");
				break;
			}
			case 45331: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000779);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000839, EnemyMetis, "Metis_846");
				break;
			}
			case 45361: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000780);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000840, EnemyMetis, "Metis_847");
				break;
			}
			case 45391: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000781);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000841, EnemyMetis, "Metis_848");
				break;
			}
			case 45421: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000782);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000842, EnemyMetis, "Metis_849");
				break;
			}
			case 45451: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000783);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000843, EnemyMetis, "Metis_850");
				break;
			}
			case 45481: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000784);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000844, EnemyMetis, "Metis_851");
				break;
			}
			case 45511: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000785);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000845, EnemyMetis, "Metis_852");
				break;
			}
			case 45541: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000786);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000846, EnemyMetis, "Metis_853");
				break;
			}
			case 45571: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000787);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000847, EnemyMetis, "Metis_854");
				break;
			}
			case 45601: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000788);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000848, EnemyMetis, "Metis_855");
				break;
			}
			case 45631: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000789);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000849, EnemyMetis, "Metis_856");
				break;
			}
			case 45661: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000790);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000850, EnemyMetis, "Metis_857");
				break;
			}
			case 45691: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000791);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000851, EnemyMetis, "Metis_858");
				break;
			}
			case 45721: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000792);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000852, EnemyMetis, "Metis_859");
				break;
			}
			case 45751: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000793);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000853, EnemyMetis, "Metis_860");
				break;
			}
			case 45781: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000794);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000854, EnemyMetis, "Metis_861");
				break;
			}
			case 45811: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000795);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000855, EnemyMetis, "Metis_862");
				break;
			}
			case 45841: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000796);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000856, EnemyMetis, "Metis_863");
				break;
			}
			case 45871: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000797);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000857, EnemyMetis, "Metis_864");
				break;
			}
			case 45901: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000798);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000858, EnemyMetis, "Metis_865");
				break;
			}
			case 45931: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000799);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000859, EnemyMetis, "Metis_866");
				break;
			}
			case 45961: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000800);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000860, EnemyMetis, "Metis_867");
				break;
			}
			case 45991: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000801);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000861, EnemyMetis, "Metis_868");
				break;
			}
			case 46021: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000802);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000862, EnemyMetis, "Metis_869");
				break;
			}
			case 46051: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000803);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000863, EnemyMetis, "Metis_870");
				break;
			}
			case 46081: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000804);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000864, EnemyMetis, "Metis_871");
				break;
			}
			case 46111: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000805);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000865, EnemyMetis, "Metis_872");
				break;
			}
			case 46141: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000806);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000866, EnemyMetis, "Metis_873");
				break;
			}
			case 46171: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000807);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000867, EnemyMetis, "Metis_874");
				break;
			}
			case 46201: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000808);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000868, EnemyMetis, "Metis_875");
				break;
			}
			case 46231: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000809);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000869, EnemyMetis, "Metis_876");
				break;
			}
			case 46261: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000810);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000870, EnemyMetis, "Metis_877");
				break;
			}
			case 46291: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000811);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000871, EnemyMetis, "Metis_878");
				break;
			}
			case 46321: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000812);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000872, EnemyMetis, "Metis_879");
				break;
			}
			case 46351: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000813);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000873, EnemyMetis, "Metis_880");
				break;
			}
			case 46381: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000814);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000874, EnemyMetis, "Metis_881");
				break;
			}
			case 46411: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000815);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000875, EnemyMetis, "Metis_882");
				break;
			}
			case 46441: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000816);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000876, EnemyMetis, "Metis_883");
				break;
			}
			case 46471: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000817);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000877, EnemyMetis, "Metis_884");
				break;
			}
			case 46501: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000818);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000878, EnemyMetis, "Metis_885");
				break;
			}
			case 46531: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000819);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000879, EnemyMetis, "Metis_886");
				break;
			}
			case 46561: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000820);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000880, EnemyMetis, "Metis_887");
				break;
			}
			case 46591: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000821);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000881, EnemyMetis, "Metis_888");
				break;
			}
			case 46621: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000822);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000882, EnemyMetis, "Metis_889");
				break;
			}
			case 46651: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000823);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000883, EnemyMetis, "Metis_890");
				break;
			}
			case 46681: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000824);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000884, EnemyMetis, "Metis_891");
				break;
			}
			case 46711: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000825);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000885, EnemyMetis, "Metis_892");
				break;
			}
			case 46741: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000826);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000886, EnemyMetis, "Metis_893");
				break;
			}
			case 46771: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000827);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000887, EnemyMetis, "Metis_894");
				break;
			}
			case 46801: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000828);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000888, EnemyMetis, "Metis_895");
				break;
			}
			case 46831: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000829);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000889, EnemyMetis, "Metis_896");
				break;
			}
			case 46861: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000830);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000890, EnemyMetis, "Metis_897");
				break;
			}
			case 46891: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000831);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000891, EnemyMetis, "Metis_898");
				break;
			}
			case 46921: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000832);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000892, EnemyMetis, "Metis_899");
				break;
			}
			case 46951: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000833);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000893, EnemyMetis, "Metis_900");
				break;
			}
			case 46981: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000834);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000894, EnemyMetis, "Metis_901");
				break;
			}
			case 47011: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000835);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000895, EnemyMetis, "Metis_902");
				break;
			}
			case 47041: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000836);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000896, EnemyMetis, "Metis_903");
				break;
			}
			case 47071: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000837);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000897, EnemyMetis, "Metis_904");
				break;
			}
			case 47101: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000838);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000898, EnemyMetis, "Metis_905");
				break;
			}
			case 47131: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000839);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000899, EnemyMetis, "Metis_906");
				break;
			}
			case 47161: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000840);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000900, EnemyMetis, "Metis_907");
				break;
			}
			case 47191: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000841);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000901, EnemyMetis, "Metis_908");
				break;
			}
			case 47221: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000842);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000902, EnemyMetis, "Metis_909");
				break;
			}
			case 47251: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000843);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000903, EnemyMetis, "Metis_910");
				break;
			}
			case 47281: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000844);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000904, EnemyMetis, "Metis_911");
				break;
			}
			case 47311: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000845);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000905, EnemyMetis, "Metis_912");
				break;
			}
			case 47341: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000846);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000906, EnemyMetis, "Metis_913");
				break;
			}
			case 47371: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000847);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000907, EnemyMetis, "Metis_914");
				break;
			}
			case 47401: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000848);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000908, EnemyMetis, "Metis_915");
				break;
			}
			case 47431: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000849);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000909, EnemyMetis, "Metis_916");
				break;
			}
			case 47461: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000850);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000910, EnemyMetis, "Metis_917");
				break;
			}
			case 47491: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000851);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000911, EnemyMetis, "Metis_918");
				break;
			}
			case 47521: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000852);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000912, EnemyMetis, "Metis_919");
				break;
			}
			case 47551: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000853);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000913, EnemyMetis, "Metis_920");
				break;
			}
			case 47581: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000854);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000914, EnemyMetis, "Metis_921");
				break;
			}
			case 47611: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000855);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000915, EnemyMetis, "Metis_922");
				break;
			}
			case 47641: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000856);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000916, EnemyMetis, "Metis_923");
				break;
			}
			case 47671: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000857);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000917, EnemyMetis, "Metis_924");
				break;
			}
			case 47701: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000858);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000918, EnemyMetis, "Metis_925");
				break;
			}
			case 47731: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000859);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000919, EnemyMetis, "Metis_926");
				break;
			}
			case 47761: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000860);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000920, EnemyMetis, "Metis_927");
				break;
			}
			case 47791: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000861);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000921, EnemyMetis, "Metis_928");
				break;
			}
			case 47821: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000862);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000922, EnemyMetis, "Metis_929");
				break;
			}
			case 47851: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000863);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000923, EnemyMetis, "Metis_930");
				break;
			}
			case 47881: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000864);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000924, EnemyMetis, "Metis_931");
				break;
			}
			case 47911: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000865);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000925, EnemyMetis, "Metis_932");
				break;
			}
			case 47941: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000866);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000926, EnemyMetis, "Metis_933");
				break;
			}
			case 47971: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000867);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000927, EnemyMetis, "Metis_934");
				break;
			}
			case 48001: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000868);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000928, EnemyMetis, "Metis_935");
				break;
			}
			case 48031: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000869);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000929, EnemyMetis, "Metis_936");
				break;
			}
			case 48061: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000870);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000930, EnemyMetis, "Metis_937");
				break;
			}
			case 48091: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000871);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000931, EnemyMetis, "Metis_938");
				break;
			}
			case 48121: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000872);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000932, EnemyMetis, "Metis_939");
				break;
			}
			case 48151: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000873);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000933, EnemyMetis, "Metis_940");
				break;
			}
			case 48181: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000874);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000934, EnemyMetis, "Metis_941");
				break;
			}
			case 48211: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000875);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000935, EnemyMetis, "Metis_942");
				break;
			}
			case 48241: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000876);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000936, EnemyMetis, "Metis_943");
				break;
			}
			case 48271: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000877);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000937, EnemyMetis, "Metis_944");
				break;
			}
			case 48301: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000878);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000938, EnemyMetis, "Metis_945");
				break;
			}
			case 48331: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000879);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000939, EnemyMetis, "Metis_946");
				break;
			}
			case 48361: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000880);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000940, EnemyMetis, "Metis_947");
				break;
			}
			case 48391: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000881);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000941, EnemyMetis, "Metis_948");
				break;
			}
			case 48421: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000882);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000942, EnemyMetis, "Metis_949");
				break;
			}
			case 48451: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000883);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000943, EnemyMetis, "Metis_950");
				break;
			}
			case 48481: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000884);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000944, EnemyMetis, "Metis_951");
				break;
			}
			case 48511: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000885);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000945, EnemyMetis, "Metis_952");
				break;
			}
			case 48541: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000886);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000946, EnemyMetis, "Metis_953");
				break;
			}
			case 48571: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000887);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000947, EnemyMetis, "Metis_954");
				break;
			}
			case 48601: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000888);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000948, EnemyMetis, "Metis_955");
				break;
			}
			case 48631: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000889);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000949, EnemyMetis, "Metis_956");
				break;
			}
			case 48661: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000890);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000950, EnemyMetis, "Metis_957");
				break;
			}
			case 48691: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000891);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000951, EnemyMetis, "Metis_958");
				break;
			}
			case 48721: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000892);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000952, EnemyMetis, "Metis_959");
				break;
			}
			case 48751: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000893);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000953, EnemyMetis, "Metis_960");
				break;
			}
			case 48781: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000894);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000954, EnemyMetis, "Metis_961");
				break;
			}
			case 48811: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000895);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000955, EnemyMetis, "Metis_962");
				break;
			}
			case 48841: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000896);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000956, EnemyMetis, "Metis_963");
				break;
			}
			case 48871: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000897);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000957, EnemyMetis, "Metis_964");
				break;
			}
			case 48901: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000898);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000958, EnemyMetis, "Metis_965");
				break;
			}
			case 48931: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000899);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000959, EnemyMetis, "Metis_966");
				break;
			}
			case 48961: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000900);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000960, EnemyMetis, "Metis_967");
				break;
			}
			case 48991: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000901);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000961, EnemyMetis, "Metis_968");
				break;
			}
			case 49021: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000902);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000962, EnemyMetis, "Metis_969");
				break;
			}
			case 49051: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000903);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000963, EnemyMetis, "Metis_970");
				break;
			}
			case 49081: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000904);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000964, EnemyMetis, "Metis_971");
				break;
			}
			case 49111: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000905);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000965, EnemyMetis, "Metis_972");
				break;
			}
			case 49141: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000906);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000966, EnemyMetis, "Metis_973");
				break;
			}
			case 49171: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000907);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000967, EnemyMetis, "Metis_974");
				break;
			}
			case 49201: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000908);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000968, EnemyMetis, "Metis_975");
				break;
			}
			case 49231: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000909);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000969, EnemyMetis, "Metis_976");
				break;
			}
			case 49261: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000910);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000970, EnemyMetis, "Metis_977");
				break;
			}
			case 49291: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000911);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000971, EnemyMetis, "Metis_978");
				break;
			}
			case 49321: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000912);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000972, EnemyMetis, "Metis_979");
				break;
			}
			case 49351: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000913);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000973, EnemyMetis, "Metis_980");
				break;
			}
			case 49381: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000914);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000974, EnemyMetis, "Metis_981");
				break;
			}
			case 49411: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000915);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000975, EnemyMetis, "Metis_982");
				break;
			}
			case 49441: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000916);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000976, EnemyMetis, "Metis_983");
				break;
			}
			case 49471: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000917);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000977, EnemyMetis, "Metis_984");
				break;
			}
			case 49501: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000918);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000978, EnemyMetis, "Metis_985");
				break;
			}
			case 49531: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000919);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000979, EnemyMetis, "Metis_986");
				break;
			}
			case 49561: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000920);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000980, EnemyMetis, "Metis_987");
				break;
			}
			case 49591: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000921);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000981, EnemyMetis, "Metis_988");
				break;
			}
			case 49621: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000922);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000982, EnemyMetis, "Metis_989");
				break;
			}
			case 49651: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000923);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000983, EnemyMetis, "Metis_990");
				break;
			}
			case 49681: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000924);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000984, EnemyMetis, "Metis_991");
				break;
			}
			case 49711: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000925);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000985, EnemyMetis, "Metis_992");
				break;
			}
			case 49741: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000926);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000986, EnemyMetis, "Metis_993");
				break;
			}
			case 49771: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000927);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000987, EnemyMetis, "Metis_994");
				break;
			}
			case 49801: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000928);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000988, EnemyMetis, "Metis_995");
				break;
			}
			case 49831: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000929);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000989, EnemyMetis, "Metis_996");
				break;
			}
			case 49861: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000930);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000990, EnemyMetis, "Metis_997");
				break;
			}
			case 49891: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000931);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000991, EnemyMetis, "Metis_998");
				break;
			}
			case 49921: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000932);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000992, EnemyMetis, "Metis_999");
				break;
			}
			case 49951: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000933);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000993, EnemyMetis, "Metis_1000");
				break;
			}
			case 49981: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000934);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000994, EnemyMetis, "Metis_1001");
				break;
			}
			case 50011: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000935);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000995, EnemyMetis, "Metis_1002");
				break;
			}
			case 50041: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000936);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000996, EnemyMetis, "Metis_1003");
				break;
			}
			case 50071: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000937);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000997, EnemyMetis, "Metis_1004");
				break;
			}
			case 50101: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000938);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000998, EnemyMetis, "Metis_1005");
				break;
			}
			case 50131: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000939);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000999, EnemyMetis, "Metis_1006");
				break;
			}
			case 50161: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000940);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001000, EnemyMetis, "Metis_1007");
				break;
			}
			case 50191: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000941);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001001, EnemyMetis, "Metis_1008");
				break;
			}
			case 50221: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000942);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001002, EnemyMetis, "Metis_1009");
				break;
			}
			case 50251: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000943);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001003, EnemyMetis, "Metis_1010");
				break;
			}
			case 50281: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000944);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001004, EnemyMetis, "Metis_1011");
				break;
			}
			case 50311: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000945);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001005, EnemyMetis, "Metis_1012");
				break;
			}
			case 50341: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000946);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001006, EnemyMetis, "Metis_1013");
				break;
			}
			case 50371: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000947);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001007, EnemyMetis, "Metis_1014");
				break;
			}
			case 50401: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000948);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001008, EnemyMetis, "Metis_1015");
				break;
			}
			case 50431: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000949);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001009, EnemyMetis, "Metis_1016");
				break;
			}
			case 50461: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000950);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001010, EnemyMetis, "Metis_1017");
				break;
			}
			case 50491: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000951);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001011, EnemyMetis, "Metis_1018");
				break;
			}
			case 50521: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000952);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001012, EnemyMetis, "Metis_1019");
				break;
			}
			case 50551: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000953);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001013, EnemyMetis, "Metis_1020");
				break;
			}
			case 50581: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000954);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001014, EnemyMetis, "Metis_1021");
				break;
			}
			case 50611: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000955);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001015, EnemyMetis, "Metis_1022");
				break;
			}
			case 50641: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000956);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001016, EnemyMetis, "Metis_1023");
				break;
			}
			case 50671: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000957);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001017, EnemyMetis, "Metis_1024");
				break;
			}
			case 50701: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000958);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001018, EnemyMetis, "Metis_1025");
				break;
			}
			case 50731: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000959);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001019, EnemyMetis, "Metis_1026");
				break;
			}
			case 50761: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000960);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001020, EnemyMetis, "Metis_1027");
				break;
			}
			case 50791: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000961);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001021, EnemyMetis, "Metis_1028");
				break;
			}
			case 50821: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000962);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001022, EnemyMetis, "Metis_1029");
				break;
			}
			case 50851: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000963);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001023, EnemyMetis, "Metis_1030");
				break;
			}
			case 50881: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000964);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001024, EnemyMetis, "Metis_1031");
				break;
			}
			case 50911: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000965);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001025, EnemyMetis, "Metis_1032");
				break;
			}
			case 50941: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000966);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001026, EnemyMetis, "Metis_1033");
				break;
			}
			case 50971: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000967);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001027, EnemyMetis, "Metis_1034");
				break;
			}
			case 51001: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000968);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001028, EnemyMetis, "Metis_1035");
				break;
			}
			case 51031: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000969);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001029, EnemyMetis, "Metis_1036");
				break;
			}
			case 51061: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000970);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001030, EnemyMetis, "Metis_1037");
				break;
			}
			case 51091: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000971);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001031, EnemyMetis, "Metis_1038");
				break;
			}
			case 51121: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000972);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001032, EnemyMetis, "Metis_1039");
				break;
			}
			case 51151: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000973);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001033, EnemyMetis, "Metis_1040");
				break;
			}
			case 51181: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000974);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001034, EnemyMetis, "Metis_1041");
				break;
			}
			case 51211: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000975);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001035, EnemyMetis, "Metis_1042");
				break;
			}
			case 51241: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000976);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001036, EnemyMetis, "Metis_1043");
				break;
			}
			case 51271: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000977);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001037, EnemyMetis, "Metis_1044");
				break;
			}
			case 51301: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000978);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001038, EnemyMetis, "Metis_1045");
				break;
			}
			case 51331: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000979);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001039, EnemyMetis, "Metis_1046");
				break;
			}
			case 51361: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000980);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001040, EnemyMetis, "Metis_1047");
				break;
			}
			case 51391: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000981);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001041, EnemyMetis, "Metis_1048");
				break;
			}
			case 51421: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000982);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001042, EnemyMetis, "Metis_1049");
				break;
			}
			case 51451: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000983);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001043, EnemyMetis, "Metis_1050");
				break;
			}
			case 51481: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000984);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001044, EnemyMetis, "Metis_1051");
				break;
			}
			case 51511: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000985);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001045, EnemyMetis, "Metis_1052");
				break;
			}
			case 51541: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000986);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001046, EnemyMetis, "Metis_1053");
				break;
			}
			case 51571: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000987);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001047, EnemyMetis, "Metis_1054");
				break;
			}
			case 51601: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000988);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001048, EnemyMetis, "Metis_1055");
				break;
			}
			case 51631: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000989);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001049, EnemyMetis, "Metis_1056");
				break;
			}
			case 51661: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000990);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001050, EnemyMetis, "Metis_1057");
				break;
			}
			case 51691: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000991);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001051, EnemyMetis, "Metis_1058");
				break;
			}
			case 51721: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000992);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001052, EnemyMetis, "Metis_1059");
				break;
			}
			case 51751: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000993);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001053, EnemyMetis, "Metis_1060");
				break;
			}
			case 51781: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000994);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001054, EnemyMetis, "Metis_1061");
				break;
			}
			case 51811: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000995);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001055, EnemyMetis, "Metis_1062");
				break;
			}
			case 51841: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000996);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001056, EnemyMetis, "Metis_1063");
				break;
			}
			case 51871: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000997);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001057, EnemyMetis, "Metis_1064");
				break;
			}
			case 51901: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000998);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001058, EnemyMetis, "Metis_1065");
				break;
			}
			case 51931: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000999);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001059, EnemyMetis, "Metis_1066");
				break;
			}
			case 51961: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001000);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001060, EnemyMetis, "Metis_1067");
				break;
			}
			case 51991: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001001);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001061, EnemyMetis, "Metis_1068");
				break;
			}
			case 52021: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001002);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001062, EnemyMetis, "Metis_1069");
				break;
			}
			case 52051: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001003);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001063, EnemyMetis, "Metis_1070");
				break;
			}
			case 52081: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001004);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001064, EnemyMetis, "Metis_1071");
				break;
			}
			case 52111: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001005);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001065, EnemyMetis, "Metis_1072");
				break;
			}
			case 52141: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001006);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001066, EnemyMetis, "Metis_1073");
				break;
			}
			case 52171: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001007);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001067, EnemyMetis, "Metis_1074");
				break;
			}
			case 52201: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001008);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001068, EnemyMetis, "Metis_1075");
				break;
			}
			case 52231: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001009);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001069, EnemyMetis, "Metis_1076");
				break;
			}
			case 52261: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001010);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001070, EnemyMetis, "Metis_1077");
				break;
			}
			case 52291: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001011);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001071, EnemyMetis, "Metis_1078");
				break;
			}
			case 52321: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001012);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001072, EnemyMetis, "Metis_1079");
				break;
			}
			case 52351: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001013);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001073, EnemyMetis, "Metis_1080");
				break;
			}
			case 52381: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001014);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001074, EnemyMetis, "Metis_1081");
				break;
			}
			case 52411: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001015);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001075, EnemyMetis, "Metis_1082");
				break;
			}
			case 52441: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001016);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001076, EnemyMetis, "Metis_1083");
				break;
			}
			case 52471: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001017);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001077, EnemyMetis, "Metis_1084");
				break;
			}
			case 52501: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001018);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001078, EnemyMetis, "Metis_1085");
				break;
			}
			case 52531: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001019);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001079, EnemyMetis, "Metis_1086");
				break;
			}
			case 52561: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001020);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001080, EnemyMetis, "Metis_1087");
				break;
			}
			case 52591: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001021);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001081, EnemyMetis, "Metis_1088");
				break;
			}
			case 52621: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001022);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001082, EnemyMetis, "Metis_1089");
				break;
			}
			case 52651: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001023);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001083, EnemyMetis, "Metis_1090");
				break;
			}
			case 52681: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001024);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001084, EnemyMetis, "Metis_1091");
				break;
			}
			case 52711: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001025);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001085, EnemyMetis, "Metis_1092");
				break;
			}
			case 52741: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001026);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001086, EnemyMetis, "Metis_1093");
				break;
			}
			case 52771: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001027);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001087, EnemyMetis, "Metis_1094");
				break;
			}
			case 52801: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001028);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001088, EnemyMetis, "Metis_1095");
				break;
			}
			case 52831: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001029);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001089, EnemyMetis, "Metis_1096");
				break;
			}
			case 52861: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001030);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001090, EnemyMetis, "Metis_1097");
				break;
			}
			case 52891: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001031);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001091, EnemyMetis, "Metis_1098");
				break;
			}
			case 52921: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001032);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001092, EnemyMetis, "Metis_1099");
				break;
			}
			case 52951: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001033);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001093, EnemyMetis, "Metis_1100");
				break;
			}
			case 52981: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001034);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001094, EnemyMetis, "Metis_1101");
				break;
			}
			case 53011: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001035);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001095, EnemyMetis, "Metis_1102");
				break;
			}
			case 53041: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001036);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001096, EnemyMetis, "Metis_1103");
				break;
			}
			case 53071: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001037);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001097, EnemyMetis, "Metis_1104");
				break;
			}
			case 53101: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001038);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001098, EnemyMetis, "Metis_1105");
				break;
			}
			case 53131: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001039);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001099, EnemyMetis, "Metis_1106");
				break;
			}
			case 53161: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001040);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001100, EnemyMetis, "Metis_1107");
				break;
			}
			case 53191: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001041);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001101, EnemyMetis, "Metis_1108");
				break;
			}
			case 53221: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001042);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001102, EnemyMetis, "Metis_1109");
				break;
			}
			case 53251: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001043);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001103, EnemyMetis, "Metis_1110");
				break;
			}
			case 53281: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001044);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001104, EnemyMetis, "Metis_1111");
				break;
			}
			case 53311: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001045);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001105, EnemyMetis, "Metis_1112");
				break;
			}
			case 53341: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001046);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001106, EnemyMetis, "Metis_1113");
				break;
			}
			case 53371: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001047);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001107, EnemyMetis, "Metis_1114");
				break;
			}
			case 53401: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001048);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001108, EnemyMetis, "Metis_1115");
				break;
			}
			case 53431: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001049);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001109, EnemyMetis, "Metis_1116");
				break;
			}
			case 53461: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001050);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001110, EnemyMetis, "Metis_1117");
				break;
			}
			case 53491: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001051);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001111, EnemyMetis, "Metis_1118");
				break;
			}
			case 53521: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001052);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001112, EnemyMetis, "Metis_1119");
				break;
			}
			case 53551: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001053);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001113, EnemyMetis, "Metis_1120");
				break;
			}
			case 53581: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001054);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001114, EnemyMetis, "Metis_1121");
				break;
			}
			case 53611: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001055);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001115, EnemyMetis, "Metis_1122");
				break;
			}
			case 53641: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001056);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001116, EnemyMetis, "Metis_1123");
				break;
			}
			case 53671: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001057);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001117, EnemyMetis, "Metis_1124");
				break;
			}
			case 53701: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001058);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001118, EnemyMetis, "Metis_1125");
				break;
			}
			case 53731: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001059);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001119, EnemyMetis, "Metis_1126");
				break;
			}
			case 53761: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001060);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001120, EnemyMetis, "Metis_1127");
				break;
			}
			case 53791: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001061);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001121, EnemyMetis, "Metis_1128");
				break;
			}
			case 53821: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001062);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001122, EnemyMetis, "Metis_1129");
				break;
			}
			case 53851: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001063);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001123, EnemyMetis, "Metis_1130");
				break;
			}
			case 53881: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001064);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001124, EnemyMetis, "Metis_1131");
				break;
			}
			case 53911: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001065);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001125, EnemyMetis, "Metis_1132");
				break;
			}
			case 53941: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001066);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001126, EnemyMetis, "Metis_1133");
				break;
			}
			case 53971: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001067);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001127, EnemyMetis, "Metis_1134");
				break;
			}
			case 54001: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001068);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001128, EnemyMetis, "Metis_1135");
				break;
			}
			case 54031: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001069);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001129, EnemyMetis, "Metis_1136");
				break;
			}
			case 54061: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001070);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001130, EnemyMetis, "Metis_1137");
				break;
			}
			case 54091: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001071);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001131, EnemyMetis, "Metis_1138");
				break;
			}
			case 54121: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001072);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001132, EnemyMetis, "Metis_1139");
				break;
			}
			case 54151: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001073);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001133, EnemyMetis, "Metis_1140");
				break;
			}
			case 54181: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001074);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001134, EnemyMetis, "Metis_1141");
				break;
			}
			case 54211: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001075);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001135, EnemyMetis, "Metis_1142");
				break;
			}
			case 54241: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001076);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001136, EnemyMetis, "Metis_1143");
				break;
			}
			case 54271: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001077);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001137, EnemyMetis, "Metis_1144");
				break;
			}
			case 54301: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001078);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001138, EnemyMetis, "Metis_1145");
				break;
			}
			case 54331: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001079);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001139, EnemyMetis, "Metis_1146");
				break;
			}
			case 54361: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001080);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001140, EnemyMetis, "Metis_1147");
				break;
			}
			case 54391: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001081);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001141, EnemyMetis, "Metis_1148");
				break;
			}
			case 54421: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001082);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001142, EnemyMetis, "Metis_1149");
				break;
			}
			case 54451: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001083);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001143, EnemyMetis, "Metis_1150");
				break;
			}
			case 54481: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001084);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001144, EnemyMetis, "Metis_1151");
				break;
			}
			case 54511: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001085);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001145, EnemyMetis, "Metis_1152");
				break;
			}
			case 54541: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001086);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001146, EnemyMetis, "Metis_1153");
				break;
			}
			case 54571: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001087);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001147, EnemyMetis, "Metis_1154");
				break;
			}
			case 54601: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001088);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001148, EnemyMetis, "Metis_1155");
				break;
			}
			case 54631: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001089);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001149, EnemyMetis, "Metis_1156");
				break;
			}
			case 54661: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001090);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001150, EnemyMetis, "Metis_1157");
				break;
			}
			case 54691: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001091);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001151, EnemyMetis, "Metis_1158");
				break;
			}
			case 54721: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001092);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001152, EnemyMetis, "Metis_1159");
				break;
			}
			case 54751: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001093);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001153, EnemyMetis, "Metis_1160");
				break;
			}
			case 54781: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001094);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001154, EnemyMetis, "Metis_1161");
				break;
			}
			case 54811: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001095);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001155, EnemyMetis, "Metis_1162");
				break;
			}
			case 54841: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001096);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001156, EnemyMetis, "Metis_1163");
				break;
			}
			case 54871: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001097);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001157, EnemyMetis, "Metis_1164");
				break;
			}
			case 54901: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001098);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001158, EnemyMetis, "Metis_1165");
				break;
			}
			case 54931: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001099);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001159, EnemyMetis, "Metis_1166");
				break;
			}
			case 54961: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001100);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001160, EnemyMetis, "Metis_1167");
				break;
			}
			case 54991: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001101);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001161, EnemyMetis, "Metis_1168");
				break;
			}
			case 55021: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001102);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001162, EnemyMetis, "Metis_1169");
				break;
			}
			case 55051: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001103);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001163, EnemyMetis, "Metis_1170");
				break;
			}
			case 55081: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001104);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001164, EnemyMetis, "Metis_1171");
				break;
			}
			case 55111: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001105);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001165, EnemyMetis, "Metis_1172");
				break;
			}
			case 55141: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001106);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001166, EnemyMetis, "Metis_1173");
				break;
			}
			case 55171: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001107);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001167, EnemyMetis, "Metis_1174");
				break;
			}
			case 55201: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001108);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001168, EnemyMetis, "Metis_1175");
				break;
			}
			case 55231: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001109);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001169, EnemyMetis, "Metis_1176");
				break;
			}
			case 55261: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001110);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001170, EnemyMetis, "Metis_1177");
				break;
			}
			case 55291: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001111);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001171, EnemyMetis, "Metis_1178");
				break;
			}
			case 55321: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001112);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001172, EnemyMetis, "Metis_1179");
				break;
			}
			case 55351: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001113);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001173, EnemyMetis, "Metis_1180");
				break;
			}
			case 55381: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001114);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001174, EnemyMetis, "Metis_1181");
				break;
			}
			case 55411: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001115);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001175, EnemyMetis, "Metis_1182");
				break;
			}
			case 55441: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001116);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001176, EnemyMetis, "Metis_1183");
				break;
			}
			case 55471: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001117);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001177, EnemyMetis, "Metis_1184");
				break;
			}
			case 55501: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001118);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001178, EnemyMetis, "Metis_1185");
				break;
			}
			case 55531: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001119);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001179, EnemyMetis, "Metis_1186");
				break;
			}
			case 55561: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001120);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001180, EnemyMetis, "Metis_1187");
				break;
			}
			case 55591: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001121);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001181, EnemyMetis, "Metis_1188");
				break;
			}
			case 55621: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001122);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001182, EnemyMetis, "Metis_1189");
				break;
			}
			case 55651: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001123);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001183, EnemyMetis, "Metis_1190");
				break;
			}
			case 55681: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001124);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001184, EnemyMetis, "Metis_1191");
				break;
			}
			case 55711: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001125);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001185, EnemyMetis, "Metis_1192");
				break;
			}
			case 55741: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001126);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001186, EnemyMetis, "Metis_1193");
				break;
			}
			case 55771: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001127);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001187, EnemyMetis, "Metis_1194");
				break;
			}
			case 55801: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001128);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001188, EnemyMetis, "Metis_1195");
				break;
			}
			case 55831: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001129);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001189, EnemyMetis, "Metis_1196");
				break;
			}
			case 55861: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001130);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001190, EnemyMetis, "Metis_1197");
				break;
			}
			case 55891: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001131);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001191, EnemyMetis, "Metis_1198");
				break;
			}
			case 55921: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001132);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001192, EnemyMetis, "Metis_1199");
				break;
			}
			case 55951: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001133);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001193, EnemyMetis, "Metis_1200");
				break;
			}
			case 55981: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001134);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001194, EnemyMetis, "Metis_1201");
				break;
			}
			case 56011: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001135);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001195, EnemyMetis, "Metis_1202");
				break;
			}
			case 56041: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001136);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001196, EnemyMetis, "Metis_1203");
				break;
			}
			case 56071: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001137);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001197, EnemyMetis, "Metis_1204");
				break;
			}
			case 56101: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001138);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001198, EnemyMetis, "Metis_1205");
				break;
			}
			case 56131: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001139);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001199, EnemyMetis, "Metis_1206");
				break;
			}
			case 56161: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001140);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001200, EnemyMetis, "Metis_1207");
				break;
			}
			case 56191: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001141);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001201, EnemyMetis, "Metis_1208");
				break;
			}
			case 56221: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001142);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001202, EnemyMetis, "Metis_1209");
				break;
			}
			case 56251: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001143);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001203, EnemyMetis, "Metis_1210");
				break;
			}
			case 56281: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001144);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001204, EnemyMetis, "Metis_1211");
				break;
			}
			case 56311: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001145);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001205, EnemyMetis, "Metis_1212");
				break;
			}
			case 56341: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001146);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001206, EnemyMetis, "Metis_1213");
				break;
			}
			case 56371: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001147);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001207, EnemyMetis, "Metis_1214");
				break;
			}
			case 56401: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001148);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001208, EnemyMetis, "Metis_1215");
				break;
			}
			case 56431: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001149);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001209, EnemyMetis, "Metis_1216");
				break;
			}
			case 56461: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001150);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001210, EnemyMetis, "Metis_1217");
				break;
			}
			case 56491: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001151);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001211, EnemyMetis, "Metis_1218");
				break;
			}
			case 56521: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001152);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001212, EnemyMetis, "Metis_1219");
				break;
			}
			case 56551: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001153);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001213, EnemyMetis, "Metis_1220");
				break;
			}
			case 56581: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001154);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001214, EnemyMetis, "Metis_1221");
				break;
			}
			case 56611: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001155);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001215, EnemyMetis, "Metis_1222");
				break;
			}
			case 56641: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001156);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001216, EnemyMetis, "Metis_1223");
				break;
			}
			case 56671: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001157);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001217, EnemyMetis, "Metis_1224");
				break;
			}
			case 56701: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001158);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001218, EnemyMetis, "Metis_1225");
				break;
			}
			case 56731: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001159);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001219, EnemyMetis, "Metis_1226");
				break;
			}
			case 56761: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001160);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001220, EnemyMetis, "Metis_1227");
				break;
			}
			case 56791: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001161);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001221, EnemyMetis, "Metis_1228");
				break;
			}
			case 56821: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001162);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001222, EnemyMetis, "Metis_1229");
				break;
			}
			case 56851: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001163);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001223, EnemyMetis, "Metis_1230");
				break;
			}
			case 56881: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001164);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001224, EnemyMetis, "Metis_1231");
				break;
			}
			case 56911: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001165);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001225, EnemyMetis, "Metis_1232");
				break;
			}
			case 56941: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001166);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001226, EnemyMetis, "Metis_1233");
				break;
			}
			case 56971: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001167);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001227, EnemyMetis, "Metis_1234");
				break;
			}
			case 57001: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001168);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001228, EnemyMetis, "Metis_1235");
				break;
			}
			case 57031: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001169);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001229, EnemyMetis, "Metis_1236");
				break;
			}
			case 57061: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001170);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001230, EnemyMetis, "Metis_1237");
				break;
			}
			case 57091: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001171);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001231, EnemyMetis, "Metis_1238");
				break;
			}
			case 57121: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001172);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001232, EnemyMetis, "Metis_1239");
				break;
			}
			case 57151: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001173);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001233, EnemyMetis, "Metis_1240");
				break;
			}
			case 57181: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001174);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001234, EnemyMetis, "Metis_1241");
				break;
			}
			case 57211: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001175);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001235, EnemyMetis, "Metis_1242");
				break;
			}
			case 57241: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001176);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001236, EnemyMetis, "Metis_1243");
				break;
			}
			case 57271: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001177);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001237, EnemyMetis, "Metis_1244");
				break;
			}
			case 57301: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001178);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001238, EnemyMetis, "Metis_1245");
				break;
			}
			case 57331: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001179);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001239, EnemyMetis, "Metis_1246");
				break;
			}
			case 57361: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001180);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001240, EnemyMetis, "Metis_1247");
				break;
			}
			case 57391: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001181);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001241, EnemyMetis, "Metis_1248");
				break;
			}
			case 57421: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001182);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001242, EnemyMetis, "Metis_1249");
				break;
			}
			case 57451: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001183);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001243, EnemyMetis, "Metis_1250");
				break;
			}
			case 57481: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001184);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001244, EnemyMetis, "Metis_1251");
				break;
			}
			case 57511: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001185);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001245, EnemyMetis, "Metis_1252");
				break;
			}
			case 57541: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001186);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001246, EnemyMetis, "Metis_1253");
				break;
			}
			case 57571: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001187);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001247, EnemyMetis, "Metis_1254");
				break;
			}
			case 57601: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001188);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001248, EnemyMetis, "Metis_1255");
				break;
			}
			case 57631: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001189);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001249, EnemyMetis, "Metis_1256");
				break;
			}
			case 57661: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001190);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001250, EnemyMetis, "Metis_1257");
				break;
			}
			case 57691: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001191);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001251, EnemyMetis, "Metis_1258");
				break;
			}
			case 57721: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001192);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001252, EnemyMetis, "Metis_1259");
				break;
			}
			case 57751: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001193);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001253, EnemyMetis, "Metis_1260");
				break;
			}
			case 57781: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001194);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001254, EnemyMetis, "Metis_1261");
				break;
			}
			case 57811: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001195);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001255, EnemyMetis, "Metis_1262");
				break;
			}
			case 57841: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001196);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001256, EnemyMetis, "Metis_1263");
				break;
			}
			case 57871: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001197);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001257, EnemyMetis, "Metis_1264");
				break;
			}
			case 57901: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001198);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001258, EnemyMetis, "Metis_1265");
				break;
			}
			case 57931: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001199);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001259, EnemyMetis, "Metis_1266");
				break;
			}
			case 57961: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001200);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001260, EnemyMetis, "Metis_1267");
				break;
			}
			case 57991: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001201);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001261, EnemyMetis, "Metis_1268");
				break;
			}
			case 58021: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001202);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001262, EnemyMetis, "Metis_1269");
				break;
			}
			case 58051: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001203);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001263, EnemyMetis, "Metis_1270");
				break;
			}
			case 58081: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001204);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001264, EnemyMetis, "Metis_1271");
				break;
			}
			case 58111: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001205);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001265, EnemyMetis, "Metis_1272");
				break;
			}
			case 58141: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001206);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001266, EnemyMetis, "Metis_1273");
				break;
			}
			case 58171: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001207);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001267, EnemyMetis, "Metis_1274");
				break;
			}
			case 58201: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001208);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001268, EnemyMetis, "Metis_1275");
				break;
			}
			case 58231: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001209);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001269, EnemyMetis, "Metis_1276");
				break;
			}
			case 58261: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001210);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001270, EnemyMetis, "Metis_1277");
				break;
			}
			case 58291: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001211);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001271, EnemyMetis, "Metis_1278");
				break;
			}
			case 58321: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001212);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001272, EnemyMetis, "Metis_1279");
				break;
			}
			case 58351: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001213);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001273, EnemyMetis, "Metis_1280");
				break;
			}
			case 58381: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001214);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001274, EnemyMetis, "Metis_1281");
				break;
			}
			case 58411: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001215);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001275, EnemyMetis, "Metis_1282");
				break;
			}
			case 58441: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001216);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001276, EnemyMetis, "Metis_1283");
				break;
			}
			case 58471: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001217);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001277, EnemyMetis, "Metis_1284");
				break;
			}
			case 58501: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001218);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001278, EnemyMetis, "Metis_1285");
				break;
			}
			case 58531: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001219);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001279, EnemyMetis, "Metis_1286");
				break;
			}
			case 58561: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001220);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001280, EnemyMetis, "Metis_1287");
				break;
			}
			case 58591: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001221);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001281, EnemyMetis, "Metis_1288");
				break;
			}
			case 58621: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001222);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001282, EnemyMetis, "Metis_1289");
				break;
			}
			case 58651: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001223);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001283, EnemyMetis, "Metis_1290");
				break;
			}
			case 58681: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001224);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001284, EnemyMetis, "Metis_1291");
				break;
			}
			case 58711: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001225);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001285, EnemyMetis, "Metis_1292");
				break;
			}
			case 58741: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001226);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001286, EnemyMetis, "Metis_1293");
				break;
			}
			case 58771: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001227);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001287, EnemyMetis, "Metis_1294");
				break;
			}
			case 58801: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001228);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001288, EnemyMetis, "Metis_1295");
				break;
			}
			case 58831: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001229);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001289, EnemyMetis, "Metis_1296");
				break;
			}
			case 58861: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001230);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001290, EnemyMetis, "Metis_1297");
				break;
			}
			case 58891: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001231);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001291, EnemyMetis, "Metis_1298");
				break;
			}
			case 58921: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001232);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001292, EnemyMetis, "Metis_1299");
				break;
			}
			case 58951: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001233);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001293, EnemyMetis, "Metis_1300");
				break;
			}
			case 58981: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001234);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001294, EnemyMetis, "Metis_1301");
				break;
			}
			case 59011: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001235);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001295, EnemyMetis, "Metis_1302");
				break;
			}
			case 59041: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001236);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001296, EnemyMetis, "Metis_1303");
				break;
			}
			case 59071: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001237);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001297, EnemyMetis, "Metis_1304");
				break;
			}
			case 59101: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001238);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001298, EnemyMetis, "Metis_1305");
				break;
			}
			case 59131: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001239);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001299, EnemyMetis, "Metis_1306");
				break;
			}
			case 59161: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001240);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001300, EnemyMetis, "Metis_1307");
				break;
			}
			case 59191: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001241);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001301, EnemyMetis, "Metis_1308");
				break;
			}
			case 59221: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001242);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001302, EnemyMetis, "Metis_1309");
				break;
			}
			case 59251: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001243);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001303, EnemyMetis, "Metis_1310");
				break;
			}
			case 59281: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001244);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001304, EnemyMetis, "Metis_1311");
				break;
			}
			case 59311: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001245);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001305, EnemyMetis, "Metis_1312");
				break;
			}
			case 59341: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001246);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001306, EnemyMetis, "Metis_1313");
				break;
			}
			case 59371: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001247);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001307, EnemyMetis, "Metis_1314");
				break;
			}
			case 59401: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001248);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001308, EnemyMetis, "Metis_1315");
				break;
			}
			case 59431: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001249);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001309, EnemyMetis, "Metis_1316");
				break;
			}
			case 59461: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001250);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001310, EnemyMetis, "Metis_1317");
				break;
			}
			case 59491: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001251);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001311, EnemyMetis, "Metis_1318");
				break;
			}
			case 59521: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001252);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001312, EnemyMetis, "Metis_1319");
				break;
			}
			case 59551: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001253);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001313, EnemyMetis, "Metis_1320");
				break;
			}
			case 59581: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001254);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001314, EnemyMetis, "Metis_1321");
				break;
			}
			case 59611: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001255);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001315, EnemyMetis, "Metis_1322");
				break;
			}
			case 59641: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001256);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001316, EnemyMetis, "Metis_1323");
				break;
			}
			case 59671: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001257);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001317, EnemyMetis, "Metis_1324");
				break;
			}
			case 59701: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001258);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001318, EnemyMetis, "Metis_1325");
				break;
			}
			case 59731: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001259);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001319, EnemyMetis, "Metis_1326");
				break;
			}
			case 59761: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001260);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001320, EnemyMetis, "Metis_1327");
				break;
			}
			case 59791: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001261);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001321, EnemyMetis, "Metis_1328");
				break;
			}
			case 59821: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001262);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001322, EnemyMetis, "Metis_1329");
				break;
			}
			case 59851: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001263);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001323, EnemyMetis, "Metis_1330");
				break;
			}
			case 59881: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001264);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001324, EnemyMetis, "Metis_1331");
				break;
			}
			case 59911: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001265);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001325, EnemyMetis, "Metis_1332");
				break;
			}
			case 59941: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001266);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001326, EnemyMetis, "Metis_1333");
				break;
			}
			case 59971: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001267);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001327, EnemyMetis, "Metis_1334");
				break;
			}
			case 60001: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001268);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001328, EnemyMetis, "Metis_1335");
				break;
			}
			case 60031: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001269);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001329, EnemyMetis, "Metis_1336");
				break;
			}
			case 60061: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001270);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001330, EnemyMetis, "Metis_1337");
				break;
			}
			case 60091: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001271);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001331, EnemyMetis, "Metis_1338");
				break;
			}
			case 60121: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001272);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001332, EnemyMetis, "Metis_1339");
				break;
			}
			case 60151: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001273);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001333, EnemyMetis, "Metis_1340");
				break;
			}
			case 60181: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001274);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40001334, EnemyMetis, "Metis_1341");
				break;
			}
			case 60211: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001275);
				getLordActor()->addSubGroup(pMetis2);
				break;
			}
			case 60241: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001276);
				getLordActor()->addSubGroup(pMetis2);
				break;
			}
			case 60271: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001277);
				getLordActor()->addSubGroup(pMetis2);
				break;
			}
			case 60301: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001278);
				getLordActor()->addSubGroup(pMetis2);
				break;
			}
			case 60331: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001279);
				getLordActor()->addSubGroup(pMetis2);
				break;
			}
			case 60361: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001280);
				getLordActor()->addSubGroup(pMetis2);
				break;
			}
			case 60391: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001281);
				getLordActor()->addSubGroup(pMetis2);
				break;
			}
			case 60421: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001282);
				getLordActor()->addSubGroup(pMetis2);
				break;
			}
			case 60451: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001283);
				getLordActor()->addSubGroup(pMetis2);
				break;
			}
			case 60481: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001284);
				getLordActor()->addSubGroup(pMetis2);
				break;
			}
			case 60511: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001285);
				getLordActor()->addSubGroup(pMetis2);
				break;
			}
			case 60541: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001286);
				getLordActor()->addSubGroup(pMetis2);
				break;
			}
			case 60571: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001287);
				getLordActor()->addSubGroup(pMetis2);
				break;
			}
			case 60601: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001288);
				getLordActor()->addSubGroup(pMetis2);
				break;
			}
			case 60631: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001289);
				getLordActor()->addSubGroup(pMetis2);
				break;
			}
			case 60661: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001290);
				getLordActor()->addSubGroup(pMetis2);
				break;
			}
			case 60691: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001291);
				getLordActor()->addSubGroup(pMetis2);
				break;
			}
			case 60721: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001292);
				getLordActor()->addSubGroup(pMetis2);
				break;
			}
			case 60751: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001293);
				getLordActor()->addSubGroup(pMetis2);
				break;
			}
			case 60781: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001294);
				getLordActor()->addSubGroup(pMetis2);
				break;
			}
			case 60811: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001295);
				getLordActor()->addSubGroup(pMetis2);
				break;
			}
			case 60841: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001296);
				getLordActor()->addSubGroup(pMetis2);
				break;
			}
			case 60871: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001297);
				getLordActor()->addSubGroup(pMetis2);
				break;
			}
			case 60901: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001298);
				getLordActor()->addSubGroup(pMetis2);
				break;
			}
			case 60931: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001299);
				getLordActor()->addSubGroup(pMetis2);
				break;
			}
			case 60961: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001300);
				getLordActor()->addSubGroup(pMetis2);
				break;
			}
			case 60991: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001301);
				getLordActor()->addSubGroup(pMetis2);
				break;
			}
			case 61021: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001302);
				getLordActor()->addSubGroup(pMetis2);
				break;
			}
			case 61051: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001303);
				getLordActor()->addSubGroup(pMetis2);
				break;
			}
			case 61081: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001304);
				getLordActor()->addSubGroup(pMetis2);
				break;
			}
			case 61111: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001305);
				getLordActor()->addSubGroup(pMetis2);
				break;
			}
			case 61141: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001306);
				getLordActor()->addSubGroup(pMetis2);
				break;
			}
			case 61171: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001307);
				getLordActor()->addSubGroup(pMetis2);
				break;
			}
			case 61201: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001308);
				getLordActor()->addSubGroup(pMetis2);
				break;
			}
			case 61231: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001309);
				getLordActor()->addSubGroup(pMetis2);
				break;
			}
			case 61261: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001310);
				getLordActor()->addSubGroup(pMetis2);
				break;
			}
			case 61291: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001311);
				getLordActor()->addSubGroup(pMetis2);
				break;
			}
			case 61321: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001312);
				getLordActor()->addSubGroup(pMetis2);
				break;
			}
			case 61351: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001313);
				getLordActor()->addSubGroup(pMetis2);
				break;
			}
			case 61381: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001314);
				getLordActor()->addSubGroup(pMetis2);
				break;
			}
			case 61411: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001315);
				getLordActor()->addSubGroup(pMetis2);
				break;
			}
			case 61441: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001316);
				getLordActor()->addSubGroup(pMetis2);
				break;
			}
			case 61471: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001317);
				getLordActor()->addSubGroup(pMetis2);
				break;
			}
			case 61501: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001318);
				getLordActor()->addSubGroup(pMetis2);
				break;
			}
			case 61531: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001319);
				getLordActor()->addSubGroup(pMetis2);
				break;
			}
			case 61561: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001320);
				getLordActor()->addSubGroup(pMetis2);
				break;
			}
			case 61591: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001321);
				getLordActor()->addSubGroup(pMetis2);
				break;
			}
			case 61621: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001322);
				getLordActor()->addSubGroup(pMetis2);
				break;
			}
			case 61651: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001323);
				getLordActor()->addSubGroup(pMetis2);
				break;
			}
			case 61681: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001324);
				getLordActor()->addSubGroup(pMetis2);
				break;
			}
			case 61711: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001325);
				getLordActor()->addSubGroup(pMetis2);
				break;
			}
			case 61741: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001326);
				getLordActor()->addSubGroup(pMetis2);
				break;
			}
			case 61771: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001327);
				getLordActor()->addSubGroup(pMetis2);
				break;
			}
			case 61801: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001328);
				getLordActor()->addSubGroup(pMetis2);
				break;
			}
			case 61831: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001329);
				getLordActor()->addSubGroup(pMetis2);
				break;
			}
			case 61861: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001330);
				getLordActor()->addSubGroup(pMetis2);
				break;
			}
			case 61891: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001331);
				getLordActor()->addSubGroup(pMetis2);
				break;
			}
			case 61921: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001332);
				getLordActor()->addSubGroup(pMetis2);
				break;
			}
			case 61951: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001333);
				getLordActor()->addSubGroup(pMetis2);
				break;
			}
			case 61981: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001334);
				getLordActor()->addSubGroup(pMetis2);
				break;
			}
			default :
				break;
		}
		_iCnt_Event = (_iCnt_Event < 1422-1 ? _iCnt_Event+1 : _iCnt_Event);
	}
    // gen02 end
}

void Stage01_02::processFinal() {
}

Stage01_02::~Stage01_02() {

}
