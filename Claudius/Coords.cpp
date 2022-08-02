#include "Constants.h"

int GridCoords::top() const noexcept
{
	return y * SQUARE_SIZE - 1;
}

int GridCoords::bottom() const noexcept
{
	return top() + SQUARE_SIZE + 1;
}

int GridCoords::left() const noexcept
{
	return x * SQUARE_SIZE - 1;
}

int GridCoords::right() const noexcept
{
	return left() + SQUARE_SIZE + 1;
}

int GridCoords::middle_x() const noexcept
{
	return SQUARE_SIZE / 2 + left();
}

int GridCoords::middle_y() const noexcept
{
	return SQUARE_SIZE / 2 + top();
}

PixelCoords GridCoords::top_left() const noexcept
{
	return PixelCoords{ left(), top() };
}

PixelCoords GridCoords::top_right() const noexcept
{
	return PixelCoords{ right(), top() };
}

PixelCoords GridCoords::bottom_left() const noexcept
{
	return PixelCoords{ left(), bottom() };
}

PixelCoords GridCoords::bottom_right() const noexcept
{
	return PixelCoords{ right(), bottom() };
}

PixelCoords GridCoords::middle_top() const noexcept
{
	return PixelCoords{ middle_x(), top() };
}

PixelCoords GridCoords::middle_bottom() const noexcept
{
	return PixelCoords{ middle_x(), bottom() };
}

PixelCoords GridCoords::middle_left() const noexcept
{
	return PixelCoords{ left(), middle_y() };
}

PixelCoords GridCoords::middle_right() const noexcept
{
	return PixelCoords{ right(), middle_y() };
}

PixelCoords GridCoords::middle() const noexcept
{
	return PixelCoords{ middle_x(), middle_y() };
}
