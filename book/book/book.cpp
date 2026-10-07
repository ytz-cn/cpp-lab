#include<iostream>
#include"book.h"
#include<cstring>
#include<iomanip>
#include<string>
#include <cstdlib>
using namespace std;

void InitList(BookList* L) {  //初始化
	L->head = new Book;
	L->head->next = nullptr;
	L->count = 0;
}

int AddBook(BookList* L, Book b) {
	Book* p = L->head->next;//头节点无数据
	bool ok = true;  //定义布尔常量做判断
	while (p) {
		if (strcmp(p->isbn, b.isbn) == 0) //isbn相同
		{
			ok = false;
		}
		p = p->next;
	}
	if (ok) {
		Book* s = new Book;
		strcpy(s->isbn, b.isbn);
		strcpy(s->title, b.title);
		strcpy(s->author, b.author);
		s->price = b.price;
		s->stock = b.stock;
		s->next = nullptr;
		Book* tail = L->head;
		while (tail->next) {
			tail = tail->next;
		}
		tail->next = s;
		L->count++;  //图书数量同步增加
		return 1;
	}
	else {
		cout << "该图书已存在" << endl;
		return 0;  //异常
	}
}

Book* FindByIsbn(BookList* L, const char* isbn) {
	Book* p = L->head->next;
	while (p != nullptr) {
		if (strcmp(p->isbn, isbn) == 0) {
			return p;          // 找到直接返回
		}
		p = p->next;
	}
	return nullptr;            // 循环结束还没找到
}

int DeleteBook(BookList* L, const char* isbn) {
	Book* pre = L->head;          // 前驱结点，从头结点开始
	Book* p = L->head->next;
	while (p) {
		if (strcmp(p->isbn, isbn) == 0) {
			pre->next = p->next;
			delete p;
			L->count--;  //数量同步减少
			return 1;
		}
		pre = p;
		p = p->next;
	}
	cout << "该图书不存在" << endl;
	return 0;
}

void ShowAll(BookList* L) {
	if (L->count == 0) {
		cout << "暂无图书" << endl;
		return;
	}
	cout << left
		<< setw(18) << "ISBN"
		<< setw(26) << "书名"
		<< setw(18) << "作者"
		<< setw(10) << "价格"
		<< setw(8) << "库存" << endl;  //表格形式输出
	cout << "--------------------------------------------------------------------------------------------\n";
	Book* p = L->head->next;
	while (p != nullptr) {
		cout << left
			<< setw(18) << p->isbn
			<< setw(26) << p->title
			<< setw(18) << p->author
			<< setw(10) << fixed << setprecision(2) << p->price
			<< setw(8) << p->stock << endl;
		p = p->next;
	}
}

void DestroyList(BookList* L) {
	Book* p = L->head;
	while (p != nullptr) {
		Book* q = p->next;
		delete p;
		p = q;
	}
	L->head = nullptr;
	L->count = 0;
}

void ModifyBook(BookList* L, const char* isbn) {
	// 1. 先按 ISBN 查找
	Book* p = FindByIsbn(L, isbn);

	if (p == nullptr) {
		cout << "未找到该图书" << endl;
		return;
	}

	// 2. 显示原信息
	cout << "当前图书信息：\n";
	cout << "ISBN: " << p->isbn << endl;
	cout << "书名: " << p->title << endl;
	cout << "作者: " << p->author << endl;
	cout << "价格: " << fixed << setprecision(2) << p->price << endl;
	cout << "库存: " << p->stock << endl;

	char buf[MAX_TITLE];   // 临时缓冲区，读用户输入

	// 3. 修改书名，直接回车不改
	cout << "请输入新书名(直接回车不改): ";
	cin.getline(buf, MAX_TITLE);
	if (strlen(buf) > 0) {
		strncpy(p->title, buf, MAX_TITLE - 1);
		p->title[MAX_TITLE - 1] = '\0';
	}

	// 4. 修改作者
	cout << "请输入新作者(直接回车不改): ";
	cin.getline(buf, MAX_AUTHOR);
	if (strlen(buf) > 0) {
		strncpy(p->author, buf, MAX_AUTHOR - 1);
		p->author[MAX_AUTHOR - 1] = '\0';
	}

	// 5. 修改价格
	cout << "请输入新价格(直接回车不改): ";
	cin.getline(buf, MAX_TITLE);
	if (strlen(buf) > 0) {
		p->price = (float)atof(buf);
	}

	// 6. 修改库存
	cout << "请输入新库存(直接回车不改): ";
	cin.getline(buf, MAX_TITLE);
	if (strlen(buf) > 0) {
		p->stock = atoi(buf);
	}

	cout << "修改成功" << endl;
}

void SearchByTitle(BookList* L, const char* keyword) {
	int found = 0;
	Book* p = L->head->next;

	while (p != nullptr) {
		// strstr 返回第一次出现的位置，找不到返回 nullptr
		if (strstr(p->title, keyword) != nullptr) {
			if (found == 0) {
				// 第一次找到时才打印表头
				cout << left
					<< setw(18) << "ISBN"
					<< setw(26) << "书名"
					<< setw(18) << "作者"
					<< setw(10) << "价格"
					<< setw(8) << "库存" << endl;
				cout << "--------------------------------------------------------------------------------------------\n";
			}

			cout << left
				<< setw(18) << p->isbn
				<< setw(26) << p->title
				<< setw(18) << p->author
				<< setw(10) << fixed << setprecision(2) << p->price
				<< setw(8) << p->stock << endl;

			found++;
		}
		p = p->next;
	}

	if (found == 0) {
		cout << "未找到匹配图书" << endl;
	}
	else {
		cout << "共找到 " << found << "本" << endl;
	}
}

void SwapBookData(Book* a, Book* b) {
	char tmpIsbn[MAX_ISBN];
	char tmpTitle[MAX_TITLE];
	char tmpAuthor[MAX_AUTHOR];
	float tmpPrice;
	int tmpStock;

	// 备份 a 的数据
	strcpy(tmpIsbn, a->isbn);
	strcpy(tmpTitle, a->title);
	strcpy(tmpAuthor, a->author);
	tmpPrice = a->price;
	tmpStock = a->stock;

	// 把 b 的数据复制给 a
	strcpy(a->isbn, b->isbn);
	strcpy(a->title, b->title);
	strcpy(a->author, b->author);
	a->price = b->price;
	a->stock = b->stock;

	// 把备份的 a 数据复制给 b
	strcpy(b->isbn, tmpIsbn);
	strcpy(b->title, tmpTitle);
	strcpy(b->author, tmpAuthor);
	b->price = tmpPrice;
	b->stock = tmpStock;
}

void SortByPrice(BookList* L) {
	if (L->count < 2) return;
	//冒泡排序
	for (Book* p = L->head->next; p != nullptr; p = p->next) {
		for (Book* q = L->head->next; q->next != nullptr; q = q->next) {
			if (q->price > q->next->price) {
				SwapBookData(q, q->next);  // 交换相邻两个结点的数据
			}
		}
	}
}