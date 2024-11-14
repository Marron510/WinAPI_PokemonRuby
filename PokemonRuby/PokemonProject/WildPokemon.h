#pragma once
#include <EngineCore/Actor.h>
#include "Map.h"


// 야생 포켓몬을 관리하는 클래스
// map으로 야생 포켓몬 데이터를 넣을것임
// map 은 포켓몬 이름 / 포켓몬 데이터 (벡터) 로 구성
// 포켓몬은 포켓몬 이름을 야생 포켓몬 enum으로 만들어 야생에서 숫자 incounter 를 만들예정
// 각 개체는 레벨에 따른 종족값이 존재
// 지역에 따라 다른 레벨의 객체가 나오도록 지정


class AWildPokemon : public AActor
{
public:



	// 생성자 소멸자
	AWildPokemon();
	~AWildPokemon();

	// delete funcion

	AWildPokemon(const AWildPokemon& _Other) = delete;
	AWildPokemon(AWildPokemon&& _Other) noexcept = delete;
	AWildPokemon& operator=(const AWildPokemon& _Other) = delete;
	AWildPokemon& operator=(AWildPokemon&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;





protected:
	
private:
	// 맵으로 포켓몬 이름에 따른 렌더를 가져오게 설정
	// 포켓몬 이름은 enum class EWildPokemonEnum를 따를것임
	USpriteRenderer* WildPokemon;



};

