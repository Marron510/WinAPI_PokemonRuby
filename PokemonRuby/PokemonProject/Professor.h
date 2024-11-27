#pragma once
class Professor
{
public:
	// 持失切 社瑚切
	Professor();
	~Professor();

	// delete funcion

	Professor(const Professor& _Other) = delete;
	Professor(Professor&& _Other) noexcept = delete;
	Professor& operator=(const Professor& _Other) = delete;
	Professor& operator=(Professor&& _Other) noexcept = delete;


protected:

private:

};

