#include <stdio.h>
#include <stdlib.h>

// Ðinh nghia cau trúc du li?u
struct Data {
    int id;
    float value;
};

int main() {
    // Ghi du lieu vào tep tin nhi phân
    FILE *file = fopen("data.bin", "wb");

    if (file == NULL) {
        printf("Khong the mo hoac tao file.\n");
        return 1;
    }

    struct Data data1 = {1, 3.15};
    struct Data data2 = {2, 3.06};

    // Ghi du lieu vào tep tin
    fwrite(&data1, sizeof(struct Data), 1, file);
    fwrite(&data2, sizeof(struct Data), 1, file);

    // Ðóng tep tin
    fclose(file);

    // Ðoc du lieu tu tep tin nhi phân và hien thi ra màn hình
    file = fopen("data.bin", "rb");

    if (file == NULL) {
        printf("Khong the mo file.\n");
        return 1;
    }

    struct Data readData;

    // Ðoc du lieu tu tep tin
    while (fread(&readData, sizeof(struct Data), 1, file) == 1) {
        // Hien thi du lieu ra màn hình
        printf("ID: %d, Value: %.2f\n", readData.id, readData.value);
    }

    // Ðóng tep tin
    fclose(file);

    return 0;
}

