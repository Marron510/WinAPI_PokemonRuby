#pragma once
class AActor
{
public:
	// ������ �Ҹ���
	AActor();
	~AActor();

	// delete funcion

	AActor(const AActor& _Other) = delete;
	AActor(AActor&& _Other) noexcept = delete;
	AActor& operator=(const AActor& _Other) = delete;
	AActor& operator=(AActor&& _Other) noexcept = delete;


protected:

private:

};

