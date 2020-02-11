#ifndef _GLOBAL_H
#define _GLOBAL_H

// Khoảng cách thu nhỏ đến Mặt Trời
const float distanceScale = 0.00000001f;

// Kích thước thu nhỏ của bán kính hành tinh
extern float planetSizeScale;

// Cấu trúc dùng để điều khiển camera hay điểm nhìn
struct Control {
	bool forward, backward, left, right, up, down;
};

#endif