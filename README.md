# DINOJUMP
- Game khủng long dựa trên cảm hứng từ game khủng long của Google
- Mã nguồn được viết bằng ngôn ngữ C++ đồ họa SDL 2.0.

* Nhiệm vụ Nhảy qua các đối tượng quái và tích lũy điểm và dành lấy điểm số cao nhất để ghi danh.

Các đối tượng trong game
- Nhân vật
- Đối tượng quái dơi nhỏ, xương rồng
- Điểm số, điểm cao nhất

Sử dụng SDL_Image, SDL_TTF, SDL_Mixer

Các class trong game
- Một lớp chứa các thuộc tính chung, các hàm khởi tạo ban đầu (Common_Function.h)
- Đối tượng tổng, các đối tượng sau đều kế thừa từ đối tượng này (BaseObject)
- Nhân vật chính - máy bay (MainObject)
- Các đối tượng quái vật (ThreatsObject)
- Lớp đạn của máy bay và quái vật (AmoObject)
- Lớp thể hiện sự kiện va chạm (ExplosionObject)
- Lớp thể hiện máu, mạng của người chơi (HealthObject)
- Lớp có chức năng load text lên screen (LTecture)
---------
Các tính năng đặc biệt
- Background chuyển sau mỗi thời gian nhất định
- Có thể tăng tốc hay giảm tốc chạy của nhân vật
- Điều chỉnh được độ cao khi nhảy

Demo
httpsyoutu.beadblKXqgKAQ
