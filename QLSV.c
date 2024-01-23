#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Định nghĩa cấu trúc SinhVien
typedef struct {
    char mssv[20];
    char ten[50];
    int diem;
} SinhVien;

// Định nghĩa cấu trúc Node cho danh sách liên kết đơn
typedef struct Node {
    SinhVien data;
    struct Node *next;
} Node;

// Khai báo các hàm
Node* themSinhVien(Node *head);
Node* xoaSinhVien(Node *head, char mssv[]);
void suaThongTinSinhVien(Node *head, char mssv[]);
void xuatDanhSach(Node *head);
void xuatFile(Node *head);
Node* docFile();

int main() {
    Node *danhSach = NULL;
    int choice;
    char mssv[20];

    do {
        printf("\n===== QUAN LY SINH VIEN =====\n");
        printf("1. Them sinh vien\n");
        printf("2. Xoa sinh vien\n");
        printf("3. Sua thong tin sinh vien\n");
        printf("4. Xuat danh sach sinh vien\n");
        printf("5. Xuat file\n");
        printf("6. Doc file\n");
        printf("0. Thoat\n");
        printf("Nhap lua chon cua ban: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                danhSach = themSinhVien(danhSach);
                break;
            case 2:
                printf("Nhap MSSV can xoa: ");
                scanf("%s", mssv);
                danhSach = xoaSinhVien(danhSach, mssv);
                break;
            case 3:
                printf("Nhap MSSV can sua: ");
                scanf("%s", mssv);
                suaThongTinSinhVien(danhSach, mssv);
                break;
            case 4:
                xuatDanhSach(danhSach);
                break;
            case 5:
                xuatFile(danhSach);
                break;
            case 6:
                danhSach = docFile();
                break;
            case 0:
                printf("Ket thuc chuong trinh.\n");
                break;
            default:
                printf("Lua chon khong hop le. Vui long nhap lai.\n");
        }
    } while (choice != 0);

    // Giải phóng bộ nhớ khi kết thúc chương trình
    Node *current = danhSach;
    Node *next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    return 0;
}

Node* themSinhVien(Node *head) {
    SinhVien sv;
    printf("Nhap MSSV: ");
    scanf("%s", sv.mssv);
    printf("Nhap ten: ");
    scanf("%s", sv.ten);
    printf("Nhap diem: ");
    scanf("%f", &sv.diem);

    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->data = sv;
    newNode->next = head;
    head = newNode;

    printf("Them sinh vien thanh cong.\n");
    return head;
}

Node* xoaSinhVien(Node *head, char mssv[]) {
    Node *current = head;
    Node *prev = NULL;

    while (current != NULL) {
        if (strcmp(current->data.mssv, mssv) == 0) {
            if (prev == NULL) {
                // Xóa nút đầu danh sách
                head = current->next;
            } else {
                // Xóa nút ở giữa hoặc cuối danh sách
                prev->next = current->next;
            }

            printf("Xoa sinh vien thanh cong.\n");
            free(current);
            return head;
        }

        prev = current;
        current = current->next;
    }

    printf("Khong tim thay sinh vien co MSSV = %s.\n", mssv);
    return head;
}

void suaThongTinSinhVien(Node *head, char mssv[]) {
    Node *current = head;

    while (current != NULL) {
        if (strcmp(current->data.mssv, mssv) == 0) {
            printf("Nhap ten moi: ");
            scanf("%s", current->data.ten);
            printf("Nhap diem moi: ");
            scanf("%f", &current->data.diem);
            printf("Sua thong tin sinh vien thanh cong.\n");
            return;
        }

        current = current->next;
    }

    printf("Khong tim thay sinh vien co MSSV = %s.\n", mssv);
}

void xuatDanhSach(Node *head) {
    Node *current = head;

    printf("\nDanh sach sinh vien:\n");
    while (current != NULL) {
        printf("MSSV: %s\tTen: %s\tDiem: %.2f\n", current->data.mssv, current->data.ten, current->data.diem);
        current = current->next;
    }
}

void xuatFile(Node *head) {
    FILE *file = fopen("sinhvien.txt", "w");
    if (file == NULL) {
        printf("Khong mo duoc file de ghi.\n");
        return;
    }

    Node *current = head;
    while (current != NULL) {
        fprintf(file, "%s %s %.2f\n", current->data.mssv, current->data.ten, current->data.diem);
        current = current->next;
    }

    fclose(file);
    printf("Xuat file thanh cong.\n");
}

Node* docFile() {
    Node *head = NULL;
    FILE *file = fopen("sinhvien.txt", "r");
    if (file == NULL) {
        printf("Khong mo duoc file de doc.\n");
        return head;
    }

    while (!feof(file)) {
        SinhVien sv;
        if (fscanf(file, "%s %s %f", sv.mssv, sv.ten, &sv.diem) == 3) {
            Node *newNode = (Node*)malloc(sizeof(Node));
            newNode->data = sv;
            newNode->next = head;
            head = newNode;
        }
    }

    fclose(file);
    printf("Doc file thanh cong.\n");
    return head;
}
