#include <stdio.h>
#include <string.h>

#define MAX_VE 50

struct VeSuKien {
    int maVe;
    char tenSuKien[50];
    char loaiVe[20];
    float giaGoc;
    int isEarlyBird;
    int daCheckIn;
};

int timVeTheoMa(const struct VeSuKien dsVe[], int soLuongVe, int maVe) {
    for (int i = 0; i < soLuongVe; i++) {
        if (dsVe[i].maVe == maVe) {
            return i;
        }
    }
    return -1;
}

int phatHanhVe(struct VeSuKien dsVe[], int soLuongVe, struct VeSuKien veMoi) {
    if (soLuongVe >= MAX_VE) {
        printf("[LỖI]: Mảng đã đầy, không thể phát hành thêm vé mới!\n");
        return soLuongVe;
    }

    if (veMoi.isEarlyBird == 1) {
        veMoi.giaGoc = veMoi.giaGoc * 0.85f;
    }
    veMoi.daCheckIn = 0;

    dsVe[soLuongVe] = veMoi;
    printf("[THÀNH CÔNG]: Phát hành vé %d (%s) thành công.\n", veMoi.maVe, veMoi.loaiVe);
    return soLuongVe + 1;
}

int checkInQR(struct VeSuKien dsVe[], int soLuongVe, int maVe) {
    int idx = timVeTheoMa(dsVe, soLuongVe, maVe);
    if (idx == -1) {
        printf("[LỖI]: Không tìm thấy mã vé %d trong hệ thống!\n", maVe);
        return 0;
    }

    if (dsVe[idx].daCheckIn == 1) {
        printf("[CẢNH BÁO GIAN LẬN]: Vé %d đã được check-in trước đó từ hệ thống!\n", maVe);
        return 0;
    }

    dsVe[idx].daCheckIn = 1;
    printf("[THÀNH CÔNG]: Check-in vé %d hợp lệ qua cổng.\n", maVe);
    return 1;
}

int huyVe(struct VeSuKien dsVe[], int soLuongVe, int maVe) {
    if (soLuongVe <= 0) {
        printf("[LỖI]: Danh sách vé đang trống, không thể thực hiện hủy!\n");
        return soLuongVe;
    }

    int idx = timVeTheoMa(dsVe, soLuongVe, maVe);
    if (idx == -1) {
        printf("[LỖI]: Không tìm thấy mã vé %d để hủy!\n", maVe);
        return soLuongVe;
    }

    for (int i = idx; i < soLuongVe - 1; i++) {
        dsVe[i] = dsVe[i + 1];
    }

    printf("[THÀNH CÔNG]: Đã hủy thành công vé mã %d.\n", maVe);
    return soLuongVe - 1;
}

void hienThiDanhSach(const struct VeSuKien dsVe[], int soLuongVe) {
    if (soLuongVe == 0) {
        printf("[THÔNG BÁO]: Danh sách vé hiện tại trống!\n");
        return;
    }

    printf("\n--- DANH SÁCH VÉ SỰ KIỆN HIỆN TẠI (%d vé) ---\n", soLuongVe);
    for (int i = 0; i < soLuongVe; i++) {
        printf("STT: %d | Mã: %d | Sự kiện: %s | Loại: %s | Giá thanh toán: %.0f VND | Check-in: %s\n",
            i + 1,
            dsVe[i].maVe,
            dsVe[i].tenSuKien,
            dsVe[i].loaiVe,
            dsVe[i].giaGoc,
            dsVe[i].daCheckIn == 1 ? "Đã check-in" : "Chưa");
    }
    printf("------------------------------------------------------------------------------------\n");
}

int main() {
    struct VeSuKien dsVe[MAX_VE];
    int soLuongVe = 0;

    printf("=== DEMO HỆ THỐNG QUẢN LÝ VÉ TICKETBOX ===\n\n");

    struct VeSuKien v1 = {1001, "Live Concert VIBE 2025", "VIP", 2000000.0f, 1, 0};
    struct VeSuKien v2 = {1002, "Live Concert VIBE 2025", "GA", 1000000.0f, 0, 0};
    struct VeSuKien v3 = {1003, "Live Concert VIBE 2025", "Zone A", 1500000.0f, 1, 0};

    soLuongVe = phatHanhVe(dsVe, soLuongVe, v1);
    soLuongVe = phatHanhVe(dsVe, soLuongVe, v2);
    soLuongVe = phatHanhVe(dsVe, soLuongVe, v3);

    hienThiDanhSach(dsVe, soLuongVe);

    struct VeSuKien v4 = {1004, "Live Concert VIBE 2025", "VIP", 2000000.0f, 0, 0};
    soLuongVe = phatHanhVe(dsVe, soLuongVe, v4);

    checkInQR(dsVe, soLuongVe, 1002);

    checkInQR(dsVe, soLuongVe, 1002);

    soLuongVe = huyVe(dsVe, soLuongVe, 1001);

    checkInQR(dsVe, soLuongVe, 9999);

    hienThiDanhSach(dsVe, soLuongVe);

    return 0;
}