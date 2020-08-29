#pragma once
class Bitmap
{
public:
	std::map<int, HBITMAP> map_Images;

	HBITMAP hBackImage;
	BITMAP bitBack;

	Bitmap();
	~Bitmap();

	void CreateBitmap();
	void DrawBitmap(HWND hWnd, HDC hdc);
	void DeleteBitmap();
};