#pragma once
class Buffer
{
public:
	Buffer():Buffer(0,0){}
	Buffer(int width, int height);
	~Buffer();
	Buffer(Buffer&) = delete;
	unsigned int clearColor;
	int width, height, len;

	bool coordCheck(int x, int y) const;
	void ClearColor(unsigned int color);
	void SetColor(unsigned int pos, unsigned int color);

protected:
	unsigned int* colorBuffer;
	
};
