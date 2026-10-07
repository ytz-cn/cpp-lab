#include <iostream>
#include <iomanip>
#include "book.h"
using namespace std;

// 辅助函数：输入一本书的信息
Book InputBook() {
    Book b;
    cout << "请输入ISBN: ";
    cin.getline(b.isbn, MAX_ISBN);

    cout << "请输入书名: ";
    cin.getline(b.title, MAX_TITLE);

    cout << "请输入作者: ";
    cin.getline(b.author, MAX_AUTHOR);

    cout << "请输入价格: ";
    cin >> b.price;

    cout << "请输入库存: ";
    cin >> b.stock;
    cin.ignore();   // 清除换行符

    b.next = nullptr;
    return b;
}

int main() {
    BookList L;
    InitList(&L);

    int choice;
    do {
        cout << "\n========= 图书管理系统 =========\n";
        cout << "1. 添加图书\n";
        cout << "2. 查找图书 (按ISBN)\n";
        cout << "3. 删除图书\n";
        cout << "4. 显示全部图书\n";
        cout << "5. 修改图书信息\n";
        cout << "6. 按书名模糊查找\n";
        cout << "7. 按价格排序\n";
        cout << "0. 退出系统\n";
        cout << "==============================\n";
        cout << "请输入你的选择：";

        cin >> choice;
        cin.ignore();   // 清除换行，后面 getline 才能正常读

        switch (choice) {
        case 1: {
            Book b = InputBook();
            if (AddBook(&L, b)) {
                cout << "添加成功" << endl;
            }
            // 失败时 AddBook 内部已提示"该图书已存在"
            break;
        }
        case 2: {
            char isbn[MAX_ISBN];
            cout << "请输入要查找的ISBN: ";
            cin.getline(isbn, MAX_ISBN);

            Book* p = FindByIsbn(&L, isbn);
            if (p == nullptr) {
                cout << "该图书不存在" << endl;
            }
            else {
                cout << "ISBN: " << p->isbn << endl;
                cout << "书名: " << p->title << endl;
                cout << "作者: " << p->author << endl;
                cout << "价格: " << fixed << setprecision(2) << p->price << endl;
                cout << "库存: " << p->stock << endl;
            }
            break;
        }
        case 3: {
            char isbn[MAX_ISBN];
            cout << "请输入要删除的ISBN: ";
            cin.getline(isbn, MAX_ISBN);

            if (DeleteBook(&L, isbn)) {
                cout << "删除成功" << endl;
            }
            // 失败时 DeleteBook 内部已提示"该图书不存在"
            break;
        }
        case 4:
            ShowAll(&L);
            break;
        case 5: {
            char isbn[MAX_ISBN];
            cout << "请输入要修改的ISBN: ";
            cin.getline(isbn, MAX_ISBN);
            ModifyBook(&L, isbn);
            break;
        }
        case 6: {
            char keyword[MAX_TITLE];
            cout << "请输入书名关键字: ";
            cin.getline(keyword, MAX_TITLE);
            SearchByTitle(&L, keyword);
            break;
        }
        case 7:
            SortByPrice(&L);
            ShowAll(&L);   // 排序后直接显示
            break;
        case 0:
            cout << "退出系统" << endl;
            break;
        default:
            cout << "无效选择，请重新输入" << endl;
            break;
        }
    } while (choice != 0);

    DestroyList(&L);
    return 0;
}