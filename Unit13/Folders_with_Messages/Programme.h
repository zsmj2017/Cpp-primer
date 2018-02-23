#ifndef PROGRAMME_H
#define PROGRAMME_H

#include<string>
#include<set>
#include<memory>

using namespace::std;

class Folder;

class Message {
friend class Folder;
friend void swap(Message &, Message &);
public:
	explicit Message(const string &s = "") :contents(s) {};//将folders隐式地初始化为空集 不允许隐式地构造message
	Message(const Message &);
	Message(Message &&);
	Message& operator=(const Message &);
	Message& operator=(Message &&);
	~Message();
	void save(Folder &);
	void remove(Folder &);
	void addFolder(Folder *);
	void remFolder(Folder *);
	void move_Folders(Message *m);
private:
	set<Folder*> folders;
	string contents;
	void add_to_Folders(const Message &);//批量添加和删除操作
	void remove_from_Folders();
};

Message::Message(const Message &rhs) {
	folders = rhs.folders;
	contents = rhs.contents;
	add_to_Folders(rhs);
}

inline Message::Message(Message &&m):contents(std::move(m.contents)){//移动构造函数
	move_Folders(&m);
}

Message& Message::operator=(const Message &rhs) {//是否可以认为 =其实就是先析构再拷贝构造
	remove_from_Folders();
	folders = rhs.folders;
	contents = rhs.contents;
	add_to_Folders(rhs);
}

inline Message & Message::operator=(Message &&m){
	if (this != &m) {
		//拷贝运算符似乎并非是销毁旧状态，而是可以直接析构
		remove_from_Folders();//类似于其他运算符，移动运算符也必须要先销毁对左侧对象的旧状态
		contents = std::move(m.contents);
		move_Folders(&m);
	}
	return *this;
}

Message::~Message() {
	remove_from_Folders();
}

void Message::save(Folder &f) {
	f.addMsg(this);
}

void Message::remove(Folder &f) {
	f.remMsg(this);
}

inline void Message::addFolder(Folder *f)
{
	folders.insert(f);
}

inline void Message::remFolder(Folder *f)
{
	folders.erase(f);
}

inline void Message::move_Folders(Message * m){
	folders = std::move(m->folders);//使用set的移动赋值运算符
	for (auto f : folders) {
		f->remMsg(m);//从folders中删除旧m
		f->addMsg(this);
	}
	m->folders.clear();//清空原message的set 确保销毁m是安全的
}

void Message::add_to_Folders(const Message &m) {//将this加入每一个包含m的folder中
	for (auto &f : m.folders) {
		f->addMsg(this);
	}
}

void Message::remove_from_Folders() {
	for (auto &f : folders) {
		f->remMsg(this);
	}
}

void swap(Message &lhs, Message &rhs) {//这个swap挺绕的 需要想一想
	for (auto &f : lhs.folders) f->remMsg(&lhs);//将包含message的folder中删除message
	for (auto &f : rhs.folders) f->remMsg(&rhs);
	swap(lhs.contents, rhs.contents);
	swap(lhs.folders, rhs.folders);//交换set
	for (auto &f : lhs.folders) f->addMsg(&lhs);//将message加入folder 因为folder中存放的是指针 要千万注意
	for (auto &f : rhs.folders) f->addMsg(&rhs);
}


class Folder {
friend class Message;
public:
	Folder() = default;
	Folder(const Folder &);
	Folder& operator=(const Folder &);
	~Folder();
	void addMsg(Message *);
	void remMsg(Message *);
private:
	set<Message*> messages;
	void add_to_Messages(const Folder &);
	void remove_from_Messages();
};

inline Folder::Folder(const Folder &f)
{
	messages = f.messages;
	add_to_Messages(f);
}

inline Folder & Folder::operator=(const Folder &rhs)
{
	remove_from_Messages();
	messages = rhs.messages;
	add_to_Messages(rhs);
	return *this;
}

inline Folder::~Folder()
{
	remove_from_Messages();
}

void Folder::addMsg(Message *msg) {//为啥用不了const
	messages.insert(msg);
}

void Folder::remMsg(Message *msg) {
	messages.erase(msg);
}

inline void Folder::add_to_Messages(const Folder &f)//将folder添加进入每一个包含f的message 方便拷贝
{
	for (auto msg : f.messages) {
		msg->addFolder(this);
	}
}

inline void Folder::remove_from_Messages() {//从所有包含this的message中删除this
	for (auto msg : messages) {
		msg->remFolder(this);
	}
}

#endif
