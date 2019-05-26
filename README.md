## Chương trình mô tả cây ATM với CSDL là tệp nhị phân

* Project 4 - CPP101x
* IDE: Microsoft Visual Studio 2019
* Version 16.1.0 Preview 2.0
* Date: May 26 2019
---

## Các chức năng chính


1. Tạo tài khoản
 * Nhập vào thông tin: Số tài khoản, tên chủ tài khoản, loại tài khoản và số dư ban đầu
 * Mỗi số tài khoản là duy nhất. Nếu tạo số tài khoản đã tồn tại, yêu cầu nhập lại số khác
 * Các thông tin nhập vào được kiểm soát:
	- Số tài khoản và số dư chỉ nhập được số nguyên dương, nếu nhập không đúng yêu cầu nhập lại
	- Số dư được giới hạn maximum là kiểu dữ liệu int
	- Loại tài khoản chỉ nhập được ký tự 'N' và 'V', nếu nhập sai yêu cầu nhập lại
	- Các thông tin tài khoản được lưu vào file "account.dat"
2. Nộp tiền, rút tiền
 * Giới hạn nộp tiền không quá giá trị maximum
 * Số dư tài khoản nhỏ hơn 50000 thì không thực hiện rút tiền.
3. Tra cứu tài khoản
4. Hiển thị danh sách tài khoản
5. Xóa tài khoản
6. Sửa tài khoản
7. Các hàm viết thêm
 * Hàm kiểm tra dữ liệu nhập vào là kiểu int: NumberInput()