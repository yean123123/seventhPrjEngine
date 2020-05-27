
#include "Precompiled.h"
#include "Windows/WindowsRSI.h"
#include "Windows/WindowsGDI.h"

WindowsRSI::~WindowsRSI()
{
}

bool WindowsRSI::Init(const ScreenPoint& InScreenSize)
{
	return InitializeGDI(InScreenSize);
}

void WindowsRSI::Shutdown()
{
	ReleaseGDI();
}

void WindowsRSI::Clear(const LinearColor & InClearColor)
{
	FillBuffer(InClearColor.ToColor32());
	ClearDepthBuffer();
}

void WindowsRSI::BeginFrame()
{
}

void WindowsRSI::EndFrame()
{
	SwapBuffer();
}

void WindowsRSI::DrawFullVerticalLine(int InX, const LinearColor & InColor)
{
	if (InX < 0 || InX >= _ScreenSize.X)
	{
		return;
	}

	for (int y = 0; y < _ScreenSize.Y; ++y)
	{
		SetPixel(ScreenPoint(InX, y), InColor);
	}
}

void WindowsRSI::DrawFullHorizontalLine(int InY, const LinearColor & InColor)
{
	if (InY < 0 || InY >= _ScreenSize.Y)
	{
		return;
	}

	for (int x = 0; x < _ScreenSize.X; ++x)
	{
		SetPixel(ScreenPoint(x, InY), InColor);
	}
}

void WindowsRSI::DrawPoint(const Vector2& InVectorPos, const LinearColor& InColor)
{
	SetPixel(ScreenPoint::ToScreenCoordinate(_ScreenSize, InVectorPos), InColor);
}

void WindowsRSI::DrawLine(const Vector2& InStartPos, const Vector2& InEndPos, const LinearColor& InColor)
{
	ScreenPoint startPosition = ScreenPoint::ToScreenCoordinate(_ScreenSize, InStartPos);
	ScreenPoint endPosition = ScreenPoint::ToScreenCoordinate(_ScreenSize, InEndPos);

	int width = endPosition.X - startPosition.X;
	int height = endPosition.Y - startPosition.Y;

	// ���⼭ ���� ����
	//SetPixel(startPosition, InColor);

	//int x = startPosition.X;
	//int y = startPosition.Y;

	//int det = 2 * height - width;

	//for (int i = 0; i < endPosition.X; i++) {
	//	x++;
	//	if (det < 0) {
	//		det += 2 * height;
	//	}
	//	else {
	//		y += 1;
	//		det += (2 * height - 2 * width);
	//	}
	//	SetPixel(ScreenPoint(x + 1, y), InColor);
	//}


	//int x2 = startPosition.X;
	//int y2 = startPosition.Y;

	//int det2 =  height - 2* width;

	//for (int i = 0; i < endPosition.Y; i++) {
	//	y2++;
	//	if (det2 < 0) {
	//		det2 += 2 * width;
	//	}
	//	else {
	//		x2 += 1;
	//		det2 += (2 * height - 2 * width);
	//	}
	//	SetPixel(ScreenPoint(x2, y2 + 1), InColor);
	//}
	//4�Ⱥи�
	//SetPixel(startPosition, InColor);

	//int x = startPosition.X;
	//int y = startPosition.Y;

	//int det = -2 * height + width;

	//for (int i = 0; i < endPosition.X; i++) {
	//	x--;
	//	if (det < 0) {
	//		det += 2 * height;
	//	}
	//	else {
	//		y += 1;
	//		det += (2 * height - 2 * width);
	//	}
	//	SetPixel(ScreenPoint(x - 1, y), InColor);
	//}


	//8�Ⱥи�
	//int x2 = startPosition.X;
	//int y2 = startPosition.Y;

	//int det2 =  2*-height + width;

	//for (int i = 0; i < endPosition.Y; i++) {
	//	y2--;
	//	if (det2 > 0) {
	//		det2 -= 2 * height;
	//	}
	//	else {
	//		x2 -= 1;
	//		det2 += (-2 * height + 2 * width);
	//	}
	//	SetPixel(ScreenPoint(x2-1, y2), InColor);
	//}

	SetPixel(startPosition, InColor);

	int x = startPosition.X;
	int y = startPosition.Y;

	int det =  2*height + width;

	for (int i = 0; i < endPosition.X; i++) {
		y++;
		if (det < 0) {
			det += 2 * height;
		}
		else {
			x -= 1;
			det -= (2 * height + 2 * width);
		}
		SetPixel(ScreenPoint(x, y + 1), InColor);
	}

}

void WindowsRSI::PushStatisticText(std::string && InText)
{
	_StatisticTexts.emplace_back(InText);
}

void WindowsRSI::PushStatisticTexts(std::vector<std::string> && InTexts)
{
	std::move(InTexts.begin(), InTexts.end(), std::back_inserter(_StatisticTexts));
}
