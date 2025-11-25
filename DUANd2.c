#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Account {
    char accountId[20];
    char fullName[50];
    char phone[15];
    double balance;
    int status;
};

struct Transaction {
    char transId[20];
    char senderId[20];
    char receiverId[20];
    double amount;
    char type[10];
    char date[20];
};

int isDuplicateId(struct Account accounts[], int n, char id[]);
void input(struct Account accounts[], int *n);
void update(struct Account accounts[], int n);

int main() {
    struct Account accounts[1000];
    int n = 0;
    char choice[9];
    do {
        printf("\n+===========================MENU===========================+");
        printf("\n|1 . Them tai khoan                                        |");
        printf("\n|2 . Cap nhat thong tin                                    |");
        printf("\n|3 . Quan ly trang thai (Khoa / Xoa)                       |");
        printf("\n|4 . Tra cuu (Tim Kiem)                                    |");
        printf("\n|5 . Danh sach (Phan Trang)                                |");
        printf("\n|6 . Sap xep danh sach                                     |");
        printf("\n|7 . Giao dich Chuyen Khoan                                |");
        printf("\n|8 . Lich su giao dich                                     |");
        printf("\n|9 . THOAT                                                 |");
        printf("\n+==========================================================+");
        printf("\n==> Nhap lua chon chuc nang trong MENU : ");
        fgets(choice, sizeof(choice), stdin);
        choice[strcspn(choice, "\n")] = '\0';
        if (strlen(choice) == 0) {
            printf("KHONG DUOC NHAP RONG\n");
            continue;
        }
        if (atoi(choice) < 1 || atoi(choice) > 9) {
            printf("LOI. VUI LONG CHON CHUC NANG PHU HOP\n");
            continue;
        }
        switch (atoi(choice)) {
            case 1:
                input(accounts, &n);
                break;
            case 2:
                update(accounts, n);
                break;
            case 9:
                printf("CAM ON VI DA DEN\n");
                break;
        }
    } while (atoi(choice) != 9);
    return 0;
}

int isDuplicateId(struct Account accounts[], int n, char id[]) {
    for (int i = 0; i < n; i++) {
        if (strcmp(accounts[i].accountId, id) == 0) {
            return 1;
        }
    }
    return 0;
}

void input(struct Account accounts[], int *n) {
    char buffer[50];
    int soLuong;
    printf("\nNhap so luong tai khoan muon them: ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    soLuong = atoi(buffer);
    if (soLuong <= 0) {
        printf("So luong khong hop le\n");
        return;
    }
    for (int i = 0; i < soLuong; i++) {
        struct Account acc;
        printf("\n--- Tai khoan thu %d ---\n", i + 1);
        while (1) {
            printf("Nhap ID: ");
            fgets(acc.accountId, sizeof(acc.accountId), stdin);
            acc.accountId[strcspn(acc.accountId, "\n")] = '\0';
            if (strlen(acc.accountId) == 0) {
                printf("ID khong duoc de trong\n");
                continue;
            }
            if (isDuplicateId(accounts, *n, acc.accountId)) {
                printf("ID da ton tai\n");
                continue;
            }
            break;
        }
        printf("Nhap ho ten: ");
        fgets(acc.fullName, sizeof(acc.fullName), stdin);
        acc.fullName[strcspn(acc.fullName, "\n")] = '\0';
        printf("Nhap so dien thoai: ");
        fgets(acc.phone, sizeof(acc.phone), stdin);
        acc.phone[strcspn(acc.phone, "\n")] = '\0';
        acc.balance = 0;
        acc.status = 1;
        accounts[*n] = acc;
        (*n)++;
        printf("Them tai khoan thanh cong\n");
    }
    printf("\nTong so tai khoan hien co: %d\n", *n);
}

void update(struct Account accounts[], int n) {
    if (n == 0) {
        printf("Chua co tai khoan nao\n");
        return;
    }
    char id[20];
    printf("\nNhap ID tai khoan can cap nhat: ");
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = '\0';
    if (strlen(id) == 0) {
        printf("ID khong duoc de trong\n");
        return;
    }
    int found = -1;
    for (int i = 0; i < n; i++) {
        if (strcmp(accounts[i].accountId, id) == 0) {
            found = i;
            break;
        }
    }
    if (found == -1) {
        printf("Khong tim thay tai khoan\n");
        return;
    }
    printf("\nThong tin hien tai:\n");
    printf("ID: %s\n", accounts[found].accountId);
    printf("Ho ten: %s\n", accounts[found].fullName);
    printf("So dien thoai: %s\n", accounts[found].phone);
    printf("So du: %.2lf\n", accounts[found].balance);
    printf("Trang thai: %s\n", accounts[found].status == 1 ? "Hoat dong" : "Bi khoa");
    printf("\nCap nhat thong tin:\n");
    char newName[50];
    char newPhone[15];
    printf("Nhap ho ten moi (bo trong neu giu nguyen): ");
    fgets(newName, sizeof(newName), stdin);
    newName[strcspn(newName, "\n")] = '\0';
    if (strlen(newName) > 0) {
        strcpy(accounts[found].fullName, newName);
    }
    printf("Nhap so dien thoai moi (bo trong neu giu nguyen): ");
    fgets(newPhone, sizeof(newPhone), stdin);
    newPhone[strcspn(newPhone, "\n")] = '\0';
    if (strlen(newPhone) > 0) {
        strcpy(accounts[found].phone, newPhone);
    }
    printf("\nCap nhat thanh cong\n");
    printf("ID: %s\n", accounts[found].accountId);
    printf("Ho ten: %s\n", accounts[found].fullName);
    printf("So dien thoai: %s\n", accounts[found].phone);
    printf("So du: %.2lf\n", accounts[found].balance);
    printf("Trang thai: %s\n", accounts[found].status == 1 ? "Hoat dong" : "Bi khoa");
}


