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
	explicit Message(const string &s = "") :contents(s) {};//��folders��ʽ�س�ʼ��Ϊ�ռ� ��������ʽ�ع���message
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
	void add_to_Folders(const Message &);//������Ӻ�ɾ������
	void remove_from_Folders();
};

Message::Message(const Message &rhs) {
	folders = rhs.folders;
	contents = rhs.contents;
	add_to_Folders(rhs);
}

inline Message::Message(Message &&m):contents(std::move(m.contents)){//�ƶ����캯��
	move_Folders(&m);
}

Message& Message::operator=(const Message &rhs) {//�Ƿ������Ϊ =��ʵ�����������ٿ�������
	remove_from_Folders();
	folders = rhs.folders;
	contents = rhs.contents;
	add_to_Folders(rhs);
}

inline Message & Message::operator=(Message &&m){
	if (this != &m) {
		//����������ƺ����������پ�״̬�����ǿ���ֱ������
		remove_from_Folders();//������������������ƶ������Ҳ����Ҫ�����ٶ�������ľ�״̬
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
	folders = std::move(m->folders);//ʹ��set���ƶ���ֵ�����
	for (auto f : folders) {
		f->remMsg(m);//��folders��ɾ����m
		f->addMsg(this);
	}
	m->folders.clear();//���ԭmessage��set ȷ������m�ǰ�ȫ��
}

void Message::add_to_Folders(const Message &m) {//��this����ÿһ������m��folder��
	for (auto &f : m.folders) {
		f->addMsg(this);
	}
}

void Message::remove_from_Folders() {
	for (auto &f : folders) {
		f->remMsg(this);
	}
}

void swap(Message &lhs, Message &rhs) {//���swapͦ�Ƶ� ��Ҫ��һ��
	for (auto &f : lhs.folders) f->remMsg(&lhs);//������message��folder��ɾ��message
	for (auto &f : rhs.folders) f->remMsg(&rhs);
	swap(lhs.contents, rhs.contents);
	swap(lhs.folders, rhs.folders);//����set
	for (auto &f : lhs.folders) f->addMsg(&lhs);//��message����folder ��Ϊfolder�д�ŵ���ָ�� Ҫǧ��ע��
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

void Folder::addMsg(Message *msg) {//Ϊɶ�ò���const
	messages.insert(msg);
}

void Folder::remMsg(Message *msg) {
	messages.erase(msg);
}

inline void Folder::add_to_Messages(const Folder &f)//��folder��ӽ���ÿһ������f��message ���㿽��
{
	for (auto msg : f.messages) {
		msg->addFolder(this);
	}
}

inline void Folder::remove_from_Messages() {//�����а���this��message��ɾ��this
	for (auto msg : messages) {
		msg->remFolder(this);
	}
}

#endif
