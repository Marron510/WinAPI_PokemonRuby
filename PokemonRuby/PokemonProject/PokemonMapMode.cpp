#include "PreCompile.h"
#include "PokemonMapMode.h"

#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/Level.h>

#include "PokemonMap.h"
#include "TileMap.h"
#include "Flower.h"
#include "Water.h"
#include "Sea.h"


APokemonMapMode::APokemonMapMode()
{

}

APokemonMapMode::~APokemonMapMode()
{

}


void APokemonMapMode::BeginPlay()
{
	{
		AFlower* newflower1 = GetWorld()->SpawnActor<AFlower>();
		AFlower* newflower2 = GetWorld()->SpawnActor<AFlower>();
		AFlower* newflower3 = GetWorld()->SpawnActor<AFlower>();
		AFlower* newflower4 = GetWorld()->SpawnActor<AFlower>();
		AFlower* newflower5 = GetWorld()->SpawnActor<AFlower>();
		AFlower* newflower6 = GetWorld()->SpawnActor<AFlower>();
		AFlower* newflower7 = GetWorld()->SpawnActor<AFlower>();
		AFlower* newflower8 = GetWorld()->SpawnActor<AFlower>();
		AFlower* newflower9 = GetWorld()->SpawnActor<AFlower>();
		AFlower* newflower10 = GetWorld()->SpawnActor<AFlower>();
		AFlower* newflower11 = GetWorld()->SpawnActor<AFlower>();
		AFlower* newflower12 = GetWorld()->SpawnActor<AFlower>();
		AFlower* newflower13 = GetWorld()->SpawnActor<AFlower>();
		AFlower* newflower14 = GetWorld()->SpawnActor<AFlower>();
		newflower1->SetActorLocationTile({ 97,70 });
		newflower2->SetActorLocationTile({ 98,70 });
		newflower3->SetActorLocationTile({ 99,69 });
		newflower4->SetActorLocationTile({ 99,68 });
		newflower5->SetActorLocationTile({ 83,70 });
		newflower6->SetActorLocationTile({ 80,70 });
		newflower7->SetActorLocationTile({ 81,69 });
		newflower8->SetActorLocationTile({ 80,68 });
		newflower9->SetActorLocationTile({ 83,77 });
		newflower10->SetActorLocationTile({ 84,77 });
		newflower11->SetActorLocationTile({ 85,77 });
		newflower12->SetActorLocationTile({ 83,78 });
		newflower13->SetActorLocationTile({ 84,78 });
		newflower14->SetActorLocationTile({ 85,78 });
	}

	{
		AFlower* newflower1 = GetWorld()->SpawnActor<AFlower>();
		AFlower* newflower2 = GetWorld()->SpawnActor<AFlower>();
		AFlower* newflower3 = GetWorld()->SpawnActor<AFlower>();
		AFlower* newflower4 = GetWorld()->SpawnActor<AFlower>();
		AFlower* newflower5 = GetWorld()->SpawnActor<AFlower>();
		AFlower* newflower6 = GetWorld()->SpawnActor<AFlower>();
		AFlower* newflower7 = GetWorld()->SpawnActor<AFlower>();
		
		newflower1->SetActorLocationTile({ 83,25 });
		newflower2->SetActorLocationTile({ 82,26 });
		newflower3->SetActorLocationTile({ 83,27 });
		newflower4->SetActorLocationTile({ 82,28 });
		newflower5->SetActorLocationTile({ 89,29 });
		newflower6->SetActorLocationTile({ 90,30 });
		newflower7->SetActorLocationTile({ 91,28 });
	}
	
	{
		AFlower* newflower1 = GetWorld()->SpawnActor<AFlower>();
		AFlower* newflower2 = GetWorld()->SpawnActor<AFlower>();
		AFlower* newflower3 = GetWorld()->SpawnActor<AFlower>();

		newflower1->SetActorLocationTile({ 63,26 });
		newflower2->SetActorLocationTile({ 63,24 });
		newflower3->SetActorLocationTile({ 62,25 });
	}

	{
		AFlower* newflower1 = GetWorld()->SpawnActor<AFlower>();
		AFlower* newflower2 = GetWorld()->SpawnActor<AFlower>();
		AFlower* newflower3 = GetWorld()->SpawnActor<AFlower>();
		AFlower* newflower4 = GetWorld()->SpawnActor<AFlower>();
		AFlower* newflower5 = GetWorld()->SpawnActor<AFlower>();
		AFlower* newflower6 = GetWorld()->SpawnActor<AFlower>();
		AFlower* newflower7 = GetWorld()->SpawnActor<AFlower>();
		AFlower* newflower8 = GetWorld()->SpawnActor<AFlower>();
		AFlower* newflower9 = GetWorld()->SpawnActor<AFlower>();
		AFlower* newflower10 = GetWorld()->SpawnActor<AFlower>();
		AFlower* newflower11 = GetWorld()->SpawnActor<AFlower>();
		AFlower* newflower12 = GetWorld()->SpawnActor<AFlower>();
		AFlower* newflower13 = GetWorld()->SpawnActor<AFlower>();
		AFlower* newflower14 = GetWorld()->SpawnActor<AFlower>();
		AFlower* newflower15 = GetWorld()->SpawnActor<AFlower>();
		AFlower* newflower16 = GetWorld()->SpawnActor<AFlower>();
		newflower1->SetActorLocationTile({ 17,34 });
		newflower2->SetActorLocationTile({ 14,34 });
		newflower3->SetActorLocationTile({ 14,36 });
		newflower4->SetActorLocationTile({ 9,17 });
		newflower5->SetActorLocationTile({ 8,17 });
		newflower6->SetActorLocationTile({ 8,16 });
		newflower7->SetActorLocationTile({ 9,16 });
		newflower8->SetActorLocationTile({ 4,15 });
		newflower9->SetActorLocationTile({ 4,16 });
		newflower10->SetActorLocationTile({ 4,17 });
		newflower11->SetActorLocationTile({ 5,16 });
		newflower12->SetActorLocationTile({ 5,17 });
		newflower13->SetActorLocationTile({ 23,34 });
		newflower14->SetActorLocationTile({ 23,35 });
		newflower15->SetActorLocationTile({ 24,34 });
		newflower16->SetActorLocationTile({ 24,35 });
	}

	{
		ASea* newsea1 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea2 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea3 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea4 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea5 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea6 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea7 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea8 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea9 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea10 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea11 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea12 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea13 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea14 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea15 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea16 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea17 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea18 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea19 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea20 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea21 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea22 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea23 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea24 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea25 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea26 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea27 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea28 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea29 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea30 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea31 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea32 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea33 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea34 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea35 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea36 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea37 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea38 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea39 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea40 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea41 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea42 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea43 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea44 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea45 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea46 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea47 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea48 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea49 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea50 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea51 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea52 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea53 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea54 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea55 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea56 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea57 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea58 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea59 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea60 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea61 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea62 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea63 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea64 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea65 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea66 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea67 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea68 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea69 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea70 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea71 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea72 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea73 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea74 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea75 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea76 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea77 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea78 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea79 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea80 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea81 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea82 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea83 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea84 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea85 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea86 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea87 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea88 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea89 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea90 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea91 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea92 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea93 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea94 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea95 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea96 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea97 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea98 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea99 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea100 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea101 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea102 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea103 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea104 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea105 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea106 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea107 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea108 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea109 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea110 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea111 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea112 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea113 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea114 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea115 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea116 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea117 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea118 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea119 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea120 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea121 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea122 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea123 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea124 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea125 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea126 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea127 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea128 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea129 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea130 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea131 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea132 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea133 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea134 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea135 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea136 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea137 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea138 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea139 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea140 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea141 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea142 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea143 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea144 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea145 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea146 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea147 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea148 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea149 = GetWorld()->SpawnActor<ASea>();
		ASea* newsea150 = GetWorld()->SpawnActor<ASea>();

		newsea1->SetActorLocationTile({ 106, 00 });
		newsea2->SetActorLocationTile({ 106, 01 });
		newsea3->SetActorLocationTile({ 106, 02 });
		newsea4->SetActorLocationTile({ 106, 03 });
		newsea5->SetActorLocationTile({ 107, 00 });
		newsea6->SetActorLocationTile({ 107, 01 });
		newsea7->SetActorLocationTile({ 107, 02 });
		newsea8->SetActorLocationTile({ 107, 03 });
		newsea9->SetActorLocationTile({ 108, 00 });
		newsea10->SetActorLocationTile({ 108, 01 });
		newsea11->SetActorLocationTile({ 108, 02 });
		newsea12->SetActorLocationTile({ 108, 03 });
		newsea13->SetActorLocationTile({ 109, 00 });
		newsea14->SetActorLocationTile({ 109, 01 });
		newsea15->SetActorLocationTile({ 109, 02 });
		newsea16->SetActorLocationTile({ 109, 03 });
		newsea17->SetActorLocationTile({ 110, 00 });
		newsea18->SetActorLocationTile({ 110, 01 });
		newsea19->SetActorLocationTile({ 110, 02 });
		newsea20->SetActorLocationTile({ 110, 03 });
		newsea21->SetActorLocationTile({ 111, 00 });
		newsea22->SetActorLocationTile({ 111, 01 });
		newsea23->SetActorLocationTile({ 111, 02 });
		newsea24->SetActorLocationTile({ 111, 03 });
		newsea25->SetActorLocationTile({ 106, 15 });
		newsea26->SetActorLocationTile({ 106, 16 });
		newsea27->SetActorLocationTile({ 106, 17 });
		newsea28->SetActorLocationTile({ 106, 18 });
		newsea29->SetActorLocationTile({ 106, 19 });
		newsea30->SetActorLocationTile({ 107, 15 });
		newsea31->SetActorLocationTile({ 107, 16 });
		newsea32->SetActorLocationTile({ 107, 17 });
		newsea33->SetActorLocationTile({ 107, 18 });
		newsea34->SetActorLocationTile({ 107, 19 });
		newsea35->SetActorLocationTile({ 108, 15 });
		newsea36->SetActorLocationTile({ 108, 16 });
		newsea37->SetActorLocationTile({ 108, 17 });
		newsea38->SetActorLocationTile({ 108, 18 });
		newsea39->SetActorLocationTile({ 108, 19 });
		newsea40->SetActorLocationTile({ 109, 15 });
		newsea41->SetActorLocationTile({ 109, 16 });
		newsea42->SetActorLocationTile({ 109, 17 });
		newsea43->SetActorLocationTile({ 109, 18 });
		newsea44->SetActorLocationTile({ 109, 19 });
		newsea45->SetActorLocationTile({ 110, 15 });
		newsea46->SetActorLocationTile({ 110, 16 });
		newsea47->SetActorLocationTile({ 110, 17 });
		newsea48->SetActorLocationTile({ 110, 18 });
		newsea49->SetActorLocationTile({ 110, 19 });
		newsea50->SetActorLocationTile({ 111, 15 });
		newsea51->SetActorLocationTile({ 111, 16 });
		newsea52->SetActorLocationTile({ 111, 17 });
		newsea53->SetActorLocationTile({ 111, 18 });
		newsea54->SetActorLocationTile({ 111, 19 });
		newsea55->SetActorLocationTile({ 104, 04 });
		newsea56->SetActorLocationTile({ 104, 05 });
		newsea57->SetActorLocationTile({ 104, 06 });
		newsea58->SetActorLocationTile({ 104, 07 });
		newsea59->SetActorLocationTile({ 104, 12 });
		newsea60->SetActorLocationTile({ 104, 13 });
		newsea61->SetActorLocationTile({ 104, 14 });
		newsea62->SetActorLocationTile({ 105, 04 });
		newsea63->SetActorLocationTile({ 105, 05 });
		newsea64->SetActorLocationTile({ 105, 06 });
		newsea65->SetActorLocationTile({ 105, 07 });
		newsea66->SetActorLocationTile({ 105, 12 });
		newsea67->SetActorLocationTile({ 105, 13 });
		newsea68->SetActorLocationTile({ 105, 14 });
		newsea69->SetActorLocationTile({ 106, 04 });
		newsea70->SetActorLocationTile({ 106, 05 });
		newsea71->SetActorLocationTile({ 106, 06 });
		newsea72->SetActorLocationTile({ 106, 07 });
		newsea73->SetActorLocationTile({ 106, 12 });
		newsea74->SetActorLocationTile({ 106, 13 });
		newsea75->SetActorLocationTile({ 106, 14 });
		newsea76->SetActorLocationTile({ 107, 04 });
		newsea77->SetActorLocationTile({ 107, 05 });
		newsea78->SetActorLocationTile({ 107, 06 });
		newsea79->SetActorLocationTile({ 107, 07 });
		newsea80->SetActorLocationTile({ 107, 12 });
		newsea81->SetActorLocationTile({ 107, 13 });
		newsea82->SetActorLocationTile({ 107, 14 });
		newsea83->SetActorLocationTile({ 108, 04 });
		newsea84->SetActorLocationTile({ 108, 05 });
		newsea85->SetActorLocationTile({ 108, 06 });
		newsea86->SetActorLocationTile({ 108, 07 });
		newsea87->SetActorLocationTile({ 108, 12 });
		newsea88->SetActorLocationTile({ 108, 13 });
		newsea89->SetActorLocationTile({ 108, 14 });
		newsea90->SetActorLocationTile({ 109, 04 });
		newsea91->SetActorLocationTile({ 109, 05 });
		newsea92->SetActorLocationTile({ 109, 06 });
		newsea93->SetActorLocationTile({ 109, 07 });
		newsea94->SetActorLocationTile({ 109, 12 });
		newsea95->SetActorLocationTile({ 109, 13 });
		newsea96->SetActorLocationTile({ 109, 14 });
		newsea97->SetActorLocationTile({ 110, 04 });
		newsea98->SetActorLocationTile({ 110, 05 });
		newsea99->SetActorLocationTile({ 110, 06 });
		newsea100->SetActorLocationTile({ 110, 07 });
		newsea101->SetActorLocationTile({ 110, 12 });
		newsea102->SetActorLocationTile({ 110, 13 });
		newsea103->SetActorLocationTile({ 110, 14 });
		newsea104->SetActorLocationTile({ 111, 04 });
		newsea105->SetActorLocationTile({ 111, 05 });
		newsea106->SetActorLocationTile({ 111, 06 });
		newsea107->SetActorLocationTile({ 111, 07 });
		newsea108->SetActorLocationTile({ 111, 12 });
		newsea109->SetActorLocationTile({ 111, 13 });
		newsea110->SetActorLocationTile({ 111, 14 });
		newsea111->SetActorLocationTile({ 102, 8 });
		newsea112->SetActorLocationTile({ 102, 9 });
		newsea113->SetActorLocationTile({ 102, 10 });
		newsea114->SetActorLocationTile({ 102, 11 });
		newsea115->SetActorLocationTile({ 103, 8 });
		newsea116->SetActorLocationTile({ 103, 9 });
		newsea117->SetActorLocationTile({ 103, 10 });
		newsea118->SetActorLocationTile({ 103, 11 });
		newsea119->SetActorLocationTile({ 104, 8 });
		newsea120->SetActorLocationTile({ 104, 9 });
		newsea121->SetActorLocationTile({ 104, 10 });
		newsea122->SetActorLocationTile({ 104, 11 });
		newsea123->SetActorLocationTile({ 105, 8 });
		newsea124->SetActorLocationTile({ 105, 9 });
		newsea125->SetActorLocationTile({ 105, 10 });
		newsea126->SetActorLocationTile({ 105, 11 });
		newsea127->SetActorLocationTile({ 106, 8 });
		newsea128->SetActorLocationTile({ 106, 9 });
		newsea129->SetActorLocationTile({ 106, 10 });
		newsea130->SetActorLocationTile({ 106, 11 });
		newsea131->SetActorLocationTile({ 107, 8 });
		newsea132->SetActorLocationTile({ 107, 9 });
		newsea133->SetActorLocationTile({ 107, 10 });
		newsea134->SetActorLocationTile({ 107, 11 });
		newsea135->SetActorLocationTile({ 108, 8 });
		newsea136->SetActorLocationTile({ 108, 9 });
		newsea137->SetActorLocationTile({ 108, 10 });
		newsea138->SetActorLocationTile({ 108, 11 });
		newsea139->SetActorLocationTile({ 109, 8 });
		newsea140->SetActorLocationTile({ 109, 9 });
		newsea141->SetActorLocationTile({ 109, 10 });
		newsea142->SetActorLocationTile({ 109, 11 });
		newsea143->SetActorLocationTile({ 110, 8 });
		newsea144->SetActorLocationTile({ 110, 9 });
		newsea145->SetActorLocationTile({ 110, 10 });
		newsea146->SetActorLocationTile({ 110, 11 });
		newsea147->SetActorLocationTile({ 111, 8 });
		newsea148->SetActorLocationTile({ 111, 9 });
		newsea149->SetActorLocationTile({ 111, 10 });
		newsea150->SetActorLocationTile({ 111, 11 });
	}




	{
		APokemonMap* NewActor = GetWorld()->SpawnActor<APokemonMap>();
		

		{

			FIntPoint TileSize;
			
			GroundTileMap = GetWorld()->SpawnActor<ATileMap>();
			GroundTileMap->Create("TileSet", {113, 82}, { 96, 96 });
			

			for (int y = 0; y < 82; y++)
			{
				for (int x = 0; x < 113; x++)
				{
					GroundTileMap->SetTileIndex({ x,y }, { 0, 0 }, { 96, 96 }, 0);
				}
			}
		}
	}
}

void APokemonMapMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	/*if (true == UEngineInput::GetInst().IsDown('R'))
	{
		UEngineAPICore::GetCore()->OpenLevel("PlayerHouse2");
	}*/

}