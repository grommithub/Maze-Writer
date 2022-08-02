#pragma once

struct PixelCoords //just for clarity
{
	int x, y;
	constexpr bool operator== (const PixelCoords& other) const noexcept = default;
};

struct GridCoords
{
	int x{}, y{};
	bool operator== (const GridCoords& other) const noexcept = default;
	int top() const noexcept;
	int bottom() const noexcept;
	int left() const noexcept;
	int right() const noexcept;
	int middle_x() const noexcept;
	int middle_y() const noexcept;
	PixelCoords top_left() const noexcept;
	PixelCoords top_right() const noexcept;
	PixelCoords bottom_left() const noexcept;
	PixelCoords bottom_right() const noexcept;
	PixelCoords middle_top() const noexcept;
	PixelCoords middle_bottom() const noexcept;
	PixelCoords middle_left() const noexcept;
	PixelCoords middle_right() const noexcept;
	PixelCoords middle() const noexcept;
};

