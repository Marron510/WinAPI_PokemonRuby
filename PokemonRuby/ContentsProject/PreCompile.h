#pragma once
class PreCompile
{
public:
	// ������ �Ҹ���
	PreCompile();
	~PreCompile();

	// delete funcion

	PreCompile(const PreCompile& _Other) = delete;
	PreCompile(PreCompile&& _Other) noexcept = delete;
	PreCompile& operator=(const PreCompile& _Other) = delete;
	PreCompile& operator=(PreCompile&& _Other) noexcept = delete;


protected:

private:

};

