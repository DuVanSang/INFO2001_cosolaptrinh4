#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct SinhVien {
    char ten[50];
    char maSV[10];
    float diem;
};

void themSinhVien(FILE *file, struct SinhVien sv) {
    fwrite(&sv, sizeof(struct SinhVien), 1, file);
}

void xoaSinhVien(FILE *file, char maSV[]) {
    FILE *tempFile = fopen("temp.txt", "wb");
    struct SinhVien sv;

    while (fread(&sv, sizeof(struct SinhVien), 1, file) == 1) {
        if (strcmp(sv.maSV, maSV) != 0) {
            fwrite(&sv, sizeof(struct SinhVien), 1, tempFile);
        }
    }

    fclose(file);
    fclose(tempFile);

    remove("sinhvien.txt"); // Ðoi tên tep tin goc
    rename("temp.txt", "sinhvien.txt");
}

void capNhatDiem(FILE *file, char maSV[], float diemMoi) {
    struct SinhVien sv;

    FILE *tempFile = fopen("temp.txt", "wb");

    while (fread(&sv, sizeof(struct SinhVien), 1, file) == 1) {
        if (strcmp(sv.maSV, maSV) == 0) {
            sv.diem = diemMoi;
        }
        fwrite(&sv, sizeof(struct SinhVien), 1, tempFile);
    }

    fclose(file);
    fclose(tempFile);

    remove("sinhvien.txt");
    rename("temp.txt", "sinhvien.txt");
}

void hienThiDanhSach(FILE *file) {
    struct SinhVien sv;

    rewind(file);

    while (fread(&sv, sizeof(struct SinhVien), 1, file) == 1) {
        printf("Ten: %s\n", sv.ten);
        printf("Ma sinh vien: %s\n", sv.maSV);
        printf("Diem: %.2f\n", sv.diem);
        printf("----------------------\n");
    }
}

int main() {
    FILE *file = fopen("sinhvien.txt", "ab+");

    if (file == NULL) {
        printf("Khong the mo hoac tao file.\n");
        return 1;
    }

    int choice;
    struct SinhVien sv;

    do {
        printf("1. Them sinh vien\n");
        printf("2. Xoa sinh vien\n");
        printf("3. Cap nhat diem\n");
        printf("4. Hien thi danh sach\n");
        printf("0. Thoat\n");

        printf("Nhap lua chon cua ban: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Nhap ten sinh vien: ");
                getchar(); 
                fgets(sv.ten, sizeof(sv.ten), stdin);
                sv.ten[strlen(sv.ten) - 1] = '\0'; 
                printf("Nhap ma sinh vien: ");
                scanf("%s", sv.maSV);
                printf("Nhap diem sinh vien: ");
                scanf("%f", &sv.diem);

                themSinhVien(file, sv);
                break;

            case 2:
                printf("Nhap ma sinh vien can xoa: ");
                char maSV[10];
                scanf("%s", maSV);

                xoaSinhVien(file, maSV);
                break;

            case 3:
                printf("Nhap ma sinh vien can cap nhat diem: ");
                char maSVCapNhat[10];
                scanf("%s", maSVCapNhat);

                printf("Nhap diem moi: ");
                float diemMoi;
                scanf("%f", &diemMoi);

                capNhatDiem(file, maSVCapNhat, diemMoi);
                break;

            case 4:
                hienThiDanhSach(file);
                break;

            case 0:
                break;

            default:
                printf("Lua chon khong hop le. Vui long thu lai.\n");
        }
    } while (choice != 0);

    fclose(file);

    return 0;
}

