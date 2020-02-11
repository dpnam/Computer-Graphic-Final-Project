#ifndef _CAMERA_H
#define _CAMERA_H

class Camera {
private:
	// Vị trí của Camera trong không gian
	float position[3];

	// Điểm nhìn của Camera
	float pointView[3];

	// Tốc độ di chuyển của Camera hay điểm nhìn
	float speedMove;

	// Bán kính, tốc độ, góc khi di chuyển camera xung quanh điểm nhìn 
	float radius;
	float speedRotate;
	float angle;

public:
	Camera(); // Contructer

	void set(); // Đặt Camera vào không gian

	void update();// Cập nhật góc quay, bánh kính quay
	void speedUp();	// Tăng tốc độ
	void speedDown(); // Giảm tốc độ

	void forwardCamera();	// Camera tiến về trước
	void backwardCamera(); // Camera lùi về sau
	void rightCamera(); // Camera dịch sang phải
	void leftCamera(); // Camera dịch sang trái
	void upCamera(); // Camera dịch lên trên
	void downCamera(); // Camera dịch xuống dưới

	void forwardPointView();	// Dịch điểm nhìn tiến về trước
	void backwardPointView(); // Dịch điểm nhìn lùi về sau
	void rightPointView(); // Dịch điểm nhìn sang phải
	void leftPointView(); // Dịch điểm nhìn sang trái
	void upPointView(); // Dịch điểm nhìn lên trên
	void downPointView(); // Dịch điểm nhìn xuống dưới
};

#endif