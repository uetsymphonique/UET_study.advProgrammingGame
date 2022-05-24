# Mini-Golf
> Bài tập lớn môn "_Lập trình nâng cao_"(INT2215_24)  
> Thực hiện bởi: Trần Quang Minh - MSV: 21020471.  
> Game được thực hiện dựa trên ý tưởng của trò chơi đánh golf và phương thức điều khiển chính là sử dụng chuột để thao tác.  
> Game được code bằng ngôn ngữ C++ có tích hợp sử dụng thư viện đồ hoạ SDL. 
## Điều kiện tiên quyết:  
Trước khi tải hoặc clone project về, hãy lưu ý:  
* Hướng dẫn sau chỉ dành cho hệ điều hành Windows và game hỗ trợ chỉ với hệ điều hành Windows
* Nếu bạn chỉ quan tâm đến việc tải game về và chơi, sẽ không có lưu ý gì cả, bạn chỉ việc tải về và trải nghiệm
* Nếu bạn quan tâm và muốn phát triển dự án hoặc đơn giản là chỉ chạy thử trên IDE, hãy đảm bảo rằng IDE của bạn có phục vụ cho ngôn ngữ C++ và có cài đặt thêm thư viện đồ hoạ SDL phục vụ cho C++ (Cách cài đặt SDL: https://lazyfoo.net/tutorials/SDL/01_hello_SDL/windows/index.php)
## Cách cài đặt
Để tải game về chơi, hãy download file zip về
![image](https://user-images.githubusercontent.com/89717384/170001630-6e0aef9c-eb44-455a-8b03-0fe87cfc9b22.png)
Sau khi đã tải được file zip về, giải nén bạn hãy chạy file projectgame.exe và bắt đầu trải nghiệm game
![image](https://user-images.githubusercontent.com/89717384/170001996-d13d5987-d18c-41fc-bd11-6922c575488d.png)
Và đây là màn chơi sẽ được hiển thị: 
![image](https://user-images.githubusercontent.com/89717384/170002126-58684ae4-2f57-444f-8311-858aa5d1c996.png)
## Cách chơi game
Sau khi mở game lên chơi bạn sẽ thấy hiện lên màn hình như sau:
![image](https://user-images.githubusercontent.com/89717384/170002747-34876afe-64d9-409f-bd64-f99c0a4dab99.png)
- Nếu ấn "SPACE" bạn sẽ được dẫn đến Instruction(Phần Hướng dẫn game) như sau:
![image](https://user-images.githubusercontent.com/89717384/170002999-ef9fc021-6c26-4dd3-9956-c7beb31e9d24.png)
- Như bạn đã thấy nhiệm vụ của game này là bạn phải đánh được quả bóng vào lỗ bằng cách kéo thả chuột từ hai vị trí bất kì trên màn hình
- Ngoài ra ấn "ESC" khi muốn trở lại menu và ấn "m" để tắt nhạc của game
Trở lại menu, sử dụng phím "ARROW_UP" và "ARROW_DOWN" để tuỳ chỉnh được menu, bên cạnh "Instruction" ta có hay tuỳ chọn khác là:
![image](https://user-images.githubusercontent.com/89717384/170004402-c9eb1ada-762f-4ce0-b808-2da1e076abd7.png)  
![image](https://user-images.githubusercontent.com/89717384/170004458-b770fd10-8920-46a6-9e74-a65774d78146.png)  
- Để chọn một tính năng hãy ấn "SPACE", sau khi vào game, màn chơi hiện ra như sau:
![image](https://user-images.githubusercontent.com/89717384/170005029-1e443df6-ca7e-43ca-af96-84970b6ae2d6.png)
- Cụ thể hơn chúng ta có:
+ Bóng, mũi tên chỉ hướng và thanh đo lực (Hướng và dộ lớn lực sẽ được hiện ra khi và chỉ khi bạn giữ chuột và kéo đi trên màn hình, độ lớn thanh lực và hướng mũi tên sẽ tuỳ chỉnh theo hướng và độ dài quãng đường kéo chuột của bạn tính từ điểm bạn nhấp chuột đến vị trí hiện tại):  
![image](https://user-images.githubusercontent.com/89717384/170005476-33407eff-0fb2-4963-ac63-f7cdf8b11508.png)
+ Lỗ:  
![image](https://user-images.githubusercontent.com/89717384/170005907-19befec2-3404-4e05-9754-663a2dfcf7a8.png)  
+ Các vật cản:   
![image](https://user-images.githubusercontent.com/89717384/170006070-6bae5228-51fe-4d04-a2f2-4e4e3e075f7b.png)  
+ Số gậy đã đánh: 
![image](https://user-images.githubusercontent.com/89717384/170006359-acbbc69e-7f07-4d02-aea5-098f06afa31d.png)
- Ngoài ra trong các level sau ta có các tính năng khác như: 
+ Đầm lầy (Swamp): Nếu bóng của bạn rơi vào đó, sẽ có hiện tượng mất bóng và bạn phải bắt đầu lại ở vị trí đánh bóng ngay trước đó  
![image](https://user-images.githubusercontent.com/89717384/170007138-47e4ea23-e113-4547-bef6-18e0dbfe5b98.png) 
+ Băng (Ice):  Bóng đi trên băng sẽ bị trôi  
![image](https://user-images.githubusercontent.com/89717384/170007662-93f087c2-874e-444b-958a-703035c6ec40.png)
+ Cổng Không gian (Teleport):  Bóng đi qua cổng không gian, sẽ đến với cổng không gian cùng cặp  
![image](https://user-images.githubusercontent.com/89717384/170007305-7a4cdb80-cc2e-4f1b-9475-9949e2749723.png)
+ Vùng gió (Wind):  Bóng đi và vùng gió sẽ bị tác động theo hướng của mũi tên gió  
![image](https://user-images.githubusercontent.com/89717384/170007508-21548a6b-d09c-455c-bc13-e937c3db3b7b.png)
- Sau khi đã đưa được bóng vào lỗ và hoàn thành từng level bạn sẽ được báo rằng đã hoàn thành màn chơi đó  
![image](https://user-images.githubusercontent.com/89717384/170008469-0da1314d-1d1c-41e4-9e19-a09a54aa8e97.png)
- Nếu bạn đã chơi qua hết tất cả level, sẽ có một màn hình để lưu tên người chơi, hãy nhập tên để được lưu lại trên bảng điểm "High Scores" (chức năng chỉ nhận các phím trên bảng chữ cái a-z, bảng số 0-9, phím "SPACE" cùng phím "Backspace" và nhận tối đa 12 kí tự , ấn Enter để lưu nhé!)     
![image](https://user-images.githubusercontent.com/89717384/170008940-a24a23fc-a8f1-4d80-8350-0687c85c2f05.png)
- Với chức năng "High Scores", danh sách top 10 best scores hiện ra với tên và điểm số:  
![image](https://user-images.githubusercontent.com/89717384/170009915-2904feca-b861-4202-81c7-f427e584dc40.png)
- Link video demo: 
## Các vấn đề chính trong game
Để có thể hoàn thành game, cần giải quyết một số vấn đề chính sau:
- Nhận sự kiện chuột sau đó cung cấp cho quả bóng một vận tốc để quả bóng có thể di chuyển theo hướng ta mong muốn. Tuỳ theo cách người dùng kéo thả chuột trên màn chơi từ vị trí A đến vị trí B, độ lớn của vận tốc và hướng của vận tốc sẽ thay đổi.
- Trong di chuyển, quả bóng cần đáp ứng một vài yêu cầu:
  + Vận tốc giảm dần qua thời gian do ma sát.
  + Có phản xạ khi gặp vật cản hoặc khi di chuyển chạm vào khung màn hình.
  + Rơi xuống lỗ khi gặp lỗ.
- Ngoài ra game còn có một số các tính năng đặc biệt khác để tạo hứng thú cho người chơi ví dụ như địa hình gió làm thay đổi vận tốc, địa hình băng làm bóng trôi hay địa hình đầm lầy khiến bóng bị chìm.
## Tài liệu tham khảo
- [Hướng dẫn sử dụng SDL của lazyfoo](https://lazyfoo.net/tutorials/SDL/index.php)
- Ý tưởng của game có lấy một phần từ project game ["_Twini-Golf_"](https://github.com/PolyMarsDev/Twini-Golf), game sử dụng lại một số hình ảnh và sound effect của project nói trên chứ hoàn toàn không sao chép code hay modify project này.
- Xin gửi lời cảm ơn đến tác giả của project game nói trên về sự giúp đỡ về mặt tài nguyên hình ảnh và sound effect, đồng thời gửi lời cảm ơn đến hai giảng viên [Trần Thị Minh Châu](https://github.com/chauttm) và Kiều Hải Đăng của Trường Đại học Công nghệ, ĐHQGHN đã cung cấp những kiến thức cần có để tôi có thể hoàn thành project này.
