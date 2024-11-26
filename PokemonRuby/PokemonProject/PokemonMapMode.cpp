#include "PreCompile.h"
#include "PokemonMapMode.h"

#include <EngineBase/TimeEvent.h>

#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/Level.h>

#include <EngineCore/SpriteRenderer.h>

#include "LaborProfessorBirchMode.h"
#include "PlayerHouse1FloorMode.h"
#include "PlayerHouse2FloorMode.h" 

#include "PokemonMath.h"
#include "PokemonMap.h"
#include "PokemonText.h"
#include "PokemonEnum.h"
#include "TileMap.h"
#include "Flower.h"
#include "Water.h"
#include "Sea.h"
#include "Player.h"
#include "Fade.h"
#include "Truck.h"
#include "Mother.h"

FIntPoint APokemonMapMode::PokemonMapModeChangePos;
APlayer::EPlayerDir APokemonMapMode::PokemonMapModePlayerDir = APlayer::EPlayerDir::DOWN_Left_Arm;

APokemonMapMode::APokemonMapMode()
{
	
}

APokemonMapMode::~APokemonMapMode()
{

}


void APokemonMapMode::BeginPlay()
{
	Super::BeginPlay();
	Player = GetWorld()->GetPawn<APlayer>();
	Player->SetColImage("PokemonMapCollisionTruck.png");
	
	
	ChatText = GetWorld()->SpawnActor<APokemonText>();
	ChatText->SetActorLocation(Player->GetActorLocation());
	ChatText->SetTextSpriteName("TextBlack.png");
	ChatText->SetTextScale({ 100, 100 });
	ChatText->SetOrder(ERenderOrder::FONT);
	ChatText->SetActorLocation(Player->GetActorLocation());


	Mother = GetWorld()->SpawnActor<AMother>();
	FVector2D MotherPosition = { 85 * TileSize.X, 68 * TileSize.Y };
	Mother->SetActorLocation(MotherPosition);
	
	Player->SetDirection(PokemonMapModePlayerDir);

	{
		Fade = GetWorld()->SpawnActor<AFade>();
		Fade->FadeOut();
	}

	{
		NewTruck = GetWorld()->SpawnActor<ATruck>();
	}

	// AFlower
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
	// AFlower
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
	// AFlower
	{
		AFlower* newflower1 = GetWorld()->SpawnActor<AFlower>();
		AFlower* newflower2 = GetWorld()->SpawnActor<AFlower>();
		AFlower* newflower3 = GetWorld()->SpawnActor<AFlower>();

		newflower1->SetActorLocationTile({ 63,26 });
		newflower2->SetActorLocationTile({ 63,24 });
		newflower3->SetActorLocationTile({ 62,25 });
	}
	// AFlower
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
	// Asea
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

	//---------------------------------------------------------
	{
		
	}
	
	
	// AWater
	{
		AWater* newWater1 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater2 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater3 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater4 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater5 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater6 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater7 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater8 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater9 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater10 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater11 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater12 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater13 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater14 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater15 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater16 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater17 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater18 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater19 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater20 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater21 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater22 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater23 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater24 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater25 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater26 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater27 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater28 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater29 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater30 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater31 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater32 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater33 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater34 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater35 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater36 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater37 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater38 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater39 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater40 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater41 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater42 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater43 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater44 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater45 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater46 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater47 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater48 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater49 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater50 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater51 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater52 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater53 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater54 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater55 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater56 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater57 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater58 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater59 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater60 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater61 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater62 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater63 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater64 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater65 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater66 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater67 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater68 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater69 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater70 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater71 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater72 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater73 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater74 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater75 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater76 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater77 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater78 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater79 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater80 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater81 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater82 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater83 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater84 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater85 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater86 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater87 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater88 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater89 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater90 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater91 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater92 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater93 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater94 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater95 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater96 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater97 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater98 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater99 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater100 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater101 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater102 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater103 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater104 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater105 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater106 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater107 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater108 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater109 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater110 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater111 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater112 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater113 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater114 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater115 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater116 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater117 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater118 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater119 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater120 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater121 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater122 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater123 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater124 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater125 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater126 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater127 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater128 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater129 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater130 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater131 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater132 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater133 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater134 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater135 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater136 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater137 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater138 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater139 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater140 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater141 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater142 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater143 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater144 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater145 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater146 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater147 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater148 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater149 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater150 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater151 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater152 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater153 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater154 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater155 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater156 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater157 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater158 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater159 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater160 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater161 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater162 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater163 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater164 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater165 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater166 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater167 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater168 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater169 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater170 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater171 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater172 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater173 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater174 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater175 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater176 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater177 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater178 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater179 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater180 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater181 = GetWorld()->SpawnActor<AWater>();
		AWater* newWater182 = GetWorld()->SpawnActor<AWater>();
	
		newWater1->SetActorLocationTile({ 70, 22 });
		newWater2->SetActorLocationTile({ 70, 23 });
		newWater3->SetActorLocationTile({ 70, 24 });
		newWater4->SetActorLocationTile({ 70, 25 });
		newWater5->SetActorLocationTile({ 70, 26 });
		newWater6->SetActorLocationTile({ 71, 22 });
		newWater7->SetActorLocationTile({ 71, 23 });
		newWater8->SetActorLocationTile({ 71, 24 });
		newWater9->SetActorLocationTile({ 71, 25 });
		newWater10->SetActorLocationTile({ 71, 26 });
		newWater11->SetActorLocationTile({ 72, 22 });
		newWater12->SetActorLocationTile({ 72, 23 });
		newWater13->SetActorLocationTile({ 72, 24 });
		newWater14->SetActorLocationTile({ 72, 25 });
		newWater15->SetActorLocationTile({ 72, 26 });
		newWater16->SetActorLocationTile({ 73, 22 });
		newWater17->SetActorLocationTile({ 73, 23 });
		newWater18->SetActorLocationTile({ 73, 24 });
		newWater19->SetActorLocationTile({ 73, 25 });
		newWater20->SetActorLocationTile({ 73, 26 });
		newWater21->SetActorLocationTile({ 74, 22 });
		newWater22->SetActorLocationTile({ 74, 23 });
		newWater24->SetActorLocationTile({ 74, 24 });
		newWater25->SetActorLocationTile({ 74, 25 });
		newWater26->SetActorLocationTile({ 74, 26 });
		newWater27->SetActorLocationTile({ 75, 22 });
		newWater28->SetActorLocationTile({ 75, 23 });
		newWater29->SetActorLocationTile({ 75, 24 });
		newWater30->SetActorLocationTile({ 75, 25 });
		newWater31->SetActorLocationTile({ 75, 26 });
		newWater32->SetActorLocationTile({ 19, 12 });
		newWater33->SetActorLocationTile({ 19, 13 });
		newWater34->SetActorLocationTile({ 19, 14 });
		newWater35->SetActorLocationTile({ 19, 15 });
		newWater36->SetActorLocationTile({ 19, 16 });
		newWater37->SetActorLocationTile({ 19, 17 });
		newWater38->SetActorLocationTile({ 19, 18 });
		newWater39->SetActorLocationTile({ 19, 19 });
		newWater40->SetActorLocationTile({ 20, 12 });
		newWater41->SetActorLocationTile({ 20, 13 });
		newWater42->SetActorLocationTile({ 20, 14 });
		newWater43->SetActorLocationTile({ 20, 15 });
		newWater44->SetActorLocationTile({ 20, 16 });
		newWater45->SetActorLocationTile({ 20, 17 });
		newWater46->SetActorLocationTile({ 20, 18 });
		newWater47->SetActorLocationTile({ 20, 19 });
		newWater48->SetActorLocationTile({ 21, 12 });
		newWater49->SetActorLocationTile({ 21, 13 });
		newWater50->SetActorLocationTile({ 21, 14 });
		newWater51->SetActorLocationTile({ 21, 15 });
		newWater52->SetActorLocationTile({ 21, 16 });
		newWater53->SetActorLocationTile({ 21, 17 });
		newWater54->SetActorLocationTile({ 21, 18 });
		newWater55->SetActorLocationTile({ 21, 19 });
		newWater56->SetActorLocationTile({ 22, 12 });
		newWater57->SetActorLocationTile({ 22, 13 });
		newWater58->SetActorLocationTile({ 22, 14 });
		newWater59->SetActorLocationTile({ 22, 15 });
		newWater60->SetActorLocationTile({ 22, 16 });
		newWater61->SetActorLocationTile({ 22, 17 });
		newWater62->SetActorLocationTile({ 22, 18 });
		newWater63->SetActorLocationTile({ 22, 19 });
		newWater64->SetActorLocationTile({ 23, 12 });
		newWater65->SetActorLocationTile({ 23, 13 });
		newWater66->SetActorLocationTile({ 23, 14 });
		newWater67->SetActorLocationTile({ 23, 15 });
		newWater68->SetActorLocationTile({ 23, 16 });
		newWater69->SetActorLocationTile({ 23, 17 });
		newWater70->SetActorLocationTile({ 23, 18 });
		newWater71->SetActorLocationTile({ 23, 19 });
		newWater72->SetActorLocationTile({ 24, 12 });
		newWater73->SetActorLocationTile({ 24, 13 });
		newWater74->SetActorLocationTile({ 24, 14 });
		newWater75->SetActorLocationTile({ 24, 15 });
		newWater76->SetActorLocationTile({ 24, 16 });
		newWater77->SetActorLocationTile({ 24, 17 });
		newWater78->SetActorLocationTile({ 24, 18 });
		newWater79->SetActorLocationTile({ 24, 19 });
		newWater80->SetActorLocationTile({ 25, 12 });
		newWater81->SetActorLocationTile({ 25, 13 });
		newWater82->SetActorLocationTile({ 25, 14 });
		newWater83->SetActorLocationTile({ 25, 15 });
		newWater84->SetActorLocationTile({ 25, 16 });
		newWater85->SetActorLocationTile({ 25, 17 });
		newWater86->SetActorLocationTile({ 25, 18 });
		newWater87->SetActorLocationTile({ 25, 19 });
		newWater88->SetActorLocationTile({ 2, 33 });
		newWater89->SetActorLocationTile({ 2, 34 });
		newWater90->SetActorLocationTile({ 2, 35 });
		newWater91->SetActorLocationTile({ 2, 36 });
		newWater92->SetActorLocationTile({ 2, 37 });
		newWater93->SetActorLocationTile({ 3, 33 });
		newWater94->SetActorLocationTile({ 3, 34 });
		newWater95->SetActorLocationTile({ 3, 35 });
		newWater96->SetActorLocationTile({ 3, 36 });
		newWater97->SetActorLocationTile({ 3, 37 });
		newWater98->SetActorLocationTile({ 4, 33 });
		newWater99->SetActorLocationTile({ 4, 34 });
		newWater100->SetActorLocationTile({ 4, 35 });
		newWater101->SetActorLocationTile({ 4, 36 });
		newWater102->SetActorLocationTile({ 4, 37 });
		newWater103->SetActorLocationTile({ 5, 33 });
		newWater104->SetActorLocationTile({ 5, 34 });
		newWater105->SetActorLocationTile({ 5, 35 });
		newWater106->SetActorLocationTile({ 5, 36 });
		newWater107->SetActorLocationTile({ 5, 37 });
		newWater108->SetActorLocationTile({ 6, 33 });
		newWater109->SetActorLocationTile({ 6, 34 });
		newWater110->SetActorLocationTile({ 6, 35 });
		newWater111->SetActorLocationTile({ 6, 36 });
		newWater112->SetActorLocationTile({ 6, 37 });
		newWater113->SetActorLocationTile({ 7, 33 });
		newWater114->SetActorLocationTile({ 7, 34 });
		newWater115->SetActorLocationTile({ 7, 35 });
		newWater116->SetActorLocationTile({ 7, 36 });
		newWater117->SetActorLocationTile({ 7, 37 });
		newWater118->SetActorLocationTile({ 8, 33 });
		newWater119->SetActorLocationTile({ 8, 34 });
		newWater120->SetActorLocationTile({ 8, 35 });
		newWater121->SetActorLocationTile({ 8, 36 });
		newWater122->SetActorLocationTile({ 8, 37 });
		newWater123->SetActorLocationTile({ 9, 33 });
		newWater124->SetActorLocationTile({ 9, 34 });
		newWater125->SetActorLocationTile({ 9, 35 });
		newWater126->SetActorLocationTile({ 9, 36 });
		newWater127->SetActorLocationTile({ 9, 37 });
		newWater128->SetActorLocationTile({ 10, 33 });
		newWater129->SetActorLocationTile({ 10, 34 });
		newWater130->SetActorLocationTile({ 10, 35 });
		newWater131->SetActorLocationTile({ 10, 36 });
		newWater132->SetActorLocationTile({ 10, 37 });
		newWater133->SetActorLocationTile({ 11, 33 });
		newWater134->SetActorLocationTile({ 11, 34 });
		newWater135->SetActorLocationTile({ 11, 35});
		newWater136->SetActorLocationTile({ 11, 36 });
		newWater137->SetActorLocationTile({ 11, 37 });
		newWater138->SetActorLocationTile({ 2, 24 });
		newWater139->SetActorLocationTile({ 2, 25 });
		newWater140->SetActorLocationTile({ 2, 26 });
		newWater141->SetActorLocationTile({ 2, 27 });
		newWater142->SetActorLocationTile({ 2, 28 });
		newWater143->SetActorLocationTile({ 2, 29 });
		newWater144->SetActorLocationTile({ 2, 30 });
		newWater145->SetActorLocationTile({ 2, 31 });
		newWater146->SetActorLocationTile({ 2, 32 });
		newWater147->SetActorLocationTile({ 3, 24 });
		newWater148->SetActorLocationTile({ 3, 25 });
		newWater149->SetActorLocationTile({ 3, 26 });
		newWater150->SetActorLocationTile({ 3, 27 });
		newWater151->SetActorLocationTile({ 3, 28 });
		newWater152->SetActorLocationTile({ 3, 29 });
		newWater153->SetActorLocationTile({ 3, 30 });
		newWater154->SetActorLocationTile({ 3, 31 });
		newWater155->SetActorLocationTile({ 3, 32 });
		newWater156->SetActorLocationTile({ 4, 24 });
		newWater157->SetActorLocationTile({ 4, 25 });
		newWater158->SetActorLocationTile({ 4, 26 });
		newWater159->SetActorLocationTile({ 4, 27 });
		newWater160->SetActorLocationTile({ 4, 28 });
		newWater161->SetActorLocationTile({ 4, 29 });
		newWater162->SetActorLocationTile({ 4, 30 });
		newWater163->SetActorLocationTile({ 4, 31 });
		newWater164->SetActorLocationTile({ 4, 32 });
		newWater165->SetActorLocationTile({ 5, 24 });
		newWater166->SetActorLocationTile({ 5, 25 });
		newWater167->SetActorLocationTile({ 5, 26 });
		newWater168->SetActorLocationTile({ 5, 27 });
		newWater169->SetActorLocationTile({ 5, 28 });
		newWater170->SetActorLocationTile({ 5, 29 });
		newWater171->SetActorLocationTile({ 5, 30 });
		newWater172->SetActorLocationTile({ 5, 31 });
		newWater173->SetActorLocationTile({ 5, 32 });
		newWater174->SetActorLocationTile({ 6, 24 });
		newWater175->SetActorLocationTile({ 6, 25 });
		newWater176->SetActorLocationTile({ 6, 26 });
		newWater177->SetActorLocationTile({ 6, 27 });
		newWater178->SetActorLocationTile({ 6, 28 });
		newWater179->SetActorLocationTile({ 6, 29 });
		newWater180->SetActorLocationTile({ 6, 30 });
		newWater181->SetActorLocationTile({ 6, 31 });
		newWater182->SetActorLocationTile({ 6, 32 });	
	}



	
		NewActor = GetWorld()->SpawnActor<APokemonMap>();
		Map = NewActor->GetCurMap();
		Chat = NewActor->GetChatRender();
	



	TimeEventer.PushEvent(3.5f, [this]() {
		RenderChatAbovePlayer();
		});

	
	
}

void APokemonMapMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	LevelChange();

	TimeEventManager.Update(_DeltaTime);
	ChatText->PrintTextUpdate(_DeltaTime);
	ChatText->SetText("shit!");

	
}


void APokemonMapMode::LevelChange()
{
	
	FVector2D MainPlayerLocation = UEngineAPICore::GetCore()->GetCurLevel()->GetPawn()->GetActorLocation();
	
	FTileVector TargetPos1 = { 85, 68 };
	FTileVector TargetPos1NextLevelPos = { 8, 8 }; // house1 免备

	FTileVector TargetPos2 = { 94, 68 };
	FTileVector TargetPos2NextLevelPos = { 3, 8 }; // house2 免备

	FTileVector TargetPos3 = { 87, 76 };
	FTileVector TargetPos3NextLevelPos = { 6, 12 }; // 楷备家 免备

	if (MainPlayerLocation == TargetPos1.ToFVector())
	{
		UEngineAPICore::GetCore()->OpenLevel("PlayerHouse1Floor");
		APlayerHouse1FloorMode::APlayerHouse1FloorModeChangePos = { 9, 8 };
		APlayerHouse1FloorMode::APlayerHouse1FloorModePlayerDir = APlayer::EPlayerDir::UP_Left_Arm;
		NewTruck->GetRender()->SetActive(false);
		Player->SetColImage("PokemonMapCollision.png");
		Fade->FadeOut();
	}

	if (MainPlayerLocation == TargetPos2.ToFVector())
	{
		UEngineAPICore::GetCore()->OpenLevel("PlayerHouse2Floor");
		APlayerHouse2FloorMode::PlayerHouse2FloorMapModeChangePos = { 3, 8 };
		APlayerHouse2FloorMode::APlayerHouse2FloorModePlayerDir = APlayer::EPlayerDir::UP_Left_Arm;
		Fade->FadeOut();
	}
	
	if (MainPlayerLocation == TargetPos3.ToFVector())
	{
		UEngineAPICore::GetCore()->OpenLevel("LaborProfessorBirch");
		ALaborProfessorBirchMode::LaborProfessorBirchModeChangePos = { 7, 12 };
		ALaborProfessorBirchMode::ALaborProfessorBirchModePlayerDir = APlayer::EPlayerDir::UP_Left_Arm;
		Fade->FadeOut();
	}
}


void APokemonMapMode::LevelChangeStart()
{
	AActor* Actor = GetWorld()->GetPawn();

	FTileVector StartPos = { PokemonMapModeChangePos.X, PokemonMapModeChangePos.Y };

	Actor->SetActorLocation(StartPos.ToFVector());
}

void APokemonMapMode::RenderChatAbovePlayer()
{
	if (Player == nullptr || Chat == nullptr)
	{
		return; 
	}

	FVector2D PlayerLocation = Player->GetActorLocation();

	FVector2D ChatLocation = PlayerLocation + FVector2D(0.0f, 260.0f);

	Chat->SetComponentLocation(ChatLocation);

	Chat->SetOrder(ERenderOrder::CHAT);
	Chat->SetActive(true);
}