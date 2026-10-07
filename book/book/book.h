#ifndef BOOK_H
#define BOOK_H

#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

// 定义常量
const int MAX_ISBN = 30;
const int MAX_TITLE = 100;
const int MAX_AUTHOR = 50;

typedef struct node {  //单个节点
	char isbn[MAX_ISBN];
	char title[MAX_TITLE];
	char author[MAX_AUTHOR];
	float price;
	int stock;
	struct node* next;
} Book;

// 链表定义
typedef struct {  //图书链表
	Book* head;  // 头结点，不存数据
	int count;  // 图书总数
} BookList;

// 函数声明
void InitList(BookList* L);
int AddBook(BookList* L, Book b);
Book* FindByIsbn(BookList* L, const char* isbn);
int DeleteBook(BookList* L, const char* isbn);
void ShowAll(BookList* L);
void DestroyList(BookList* L);
void ModifyBook(BookList* L, const char* isbn);
void SearchByTitle(BookList* L, const char* keyword);
void SortByPrice(BookList* L);
#endif
