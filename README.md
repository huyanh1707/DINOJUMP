# DINOJUMP

Game khủng long dựa trên cảm hứng từ game khủng long của Google

Mã nguồn được viết bằng ngôn ngữ C++ đồ họa SDL 2.0.

  * Nhiệm vụ Nhảy qua các đối tượng quái và tích lũy điểm và dành lấy điểm số cao nhất để ghi danh với cách chơi đơn giản bạn gồm các nút:
      - esc để tạm dừng trò chơi
      - nhấn và giữ mũi tên lên để căn chỉnh lực nhảy sao cho hợp lý nhất
      - mũi tên sang trái phải dùng để điều chỉnh tốc độ tiến đến của các chướng ngại vật

  * Các đối tượng trong game
      - Nhân vật
      - Đối tượng quái dơi nhỏ, xương rồng
      - Điểm số, điểm cao nhất
      - Âm thanh
      - Sử dụng SDL_Image, SDL_TTF, SDL_Mixer

  * Các class trong game
      - Một lớp để khai báo các biến nền tảng được tự định nghĩa (Game_Base.h)
      - Một lớp báo lỗi thư viện gốc (Game_Base.cpp)
      - Các đặc điểm của đối tượng game (Game_Utils)
      - Lớp tạo ra các nút bấm (Button)
      - Các đối tượng vật cản (Enemy)
      - Lớp hoạt ảnh và chức năng nhân vật (Character)
      - Lớp có chức năng load text lên screen (LTexture)

  * Các tính năng đặc biệt
      - Background chuyển sau mỗi 200 điểm nhất định
      - Có thể tăng tốc hay giảm tốc chạy của nhân vật
      - Điều chỉnh được độ cao khi nhảy
      - Độ khó game tăng theo thời gian chơi
      - Lưu được thành tích kể cả khi đã thoát game

* Demo:
https://drive.google.com/file/d/1X_Q5baqibKyFYIGpezjzHe5T3erwpLBW/view?usp=sharing
