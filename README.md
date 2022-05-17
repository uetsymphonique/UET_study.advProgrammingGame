# Mini-Golf
## Mô tả:
Đây là bài tập lớn môn "_Lập trình nâng cao_"(INT2215_24) thực hiện bởi sinh viên Trần Quang Minh - MSV: 21020471.
Game được thực hiện dựa trên ý tưởng của trò chơi đánh golf và phương thức điều khiển chính là sử dụng chuột để thao tác.
Game được code bằng ngôn ngữ C++ có tích hợp sử dụng thư viện đồ hoạ SDL.
## Các vấn đề chính trong game
Để có thể hoàn thành game, cần giải quyết một số vấn đề chính sau:
- Nhận sự kiện chuột sau đó cung cấp cho quả bóng một vận tốc để quả bóng có thể di chuyển theo hướng ta mong muốn. Tuỳ theo cách người dùng kéo thả chuột trên màn chơi từ vị trí A đến vị trí B, độ lớn của vận tốc và hướng của vận tốc sẽ thay đổi.
- Trong di chuyển, quả bóng cần đáp ứng một vài yêu cầu:
  + Vận tốc giảm dần qua thời gian do ma sát.
  + Có phản xạ khi gặp vật cản hoặc khi di chuyển chạm vào khung màn hình.
  + Rơi xuống lỗ khi gặp lỗ.
- Ngoài ra game còn có một số các tính năng đặc biệt khác để tạo hứng thú cho người chơi ví dụ như địa hình gió làm thay đổi vận tốc, địa hình băng làm bóng trôi hay địa hình đầm lầy khiến bóng bị chìm.
## Tài liệu tham khảo
Ý tưởng của game có lấy một phần từ project game "_Twini-Golf_" (https://github.com/PolyMarsDev/Twini-Golf), game sử dụng lại một số hình ảnh và sound effect của project nói trên chứ hoàn toàn không sao chép code hay modify project này.
Xin gửi lời cảm ơn đến tác giả của project game nói trên về sự giúp đỡ về mặt tài nguyên hình ảnh và sound effect, đồng thời gửi lời cảm ơn đến hai giảng viên Trần Thị Minh Châu (https://github.com/chauttm) và Kiều Hải Đăng của Trường Đại học Công nghệ, ĐHQGHN đã cung cấp những kiến thức cần có để tôi có thể hoàn thành project này.
