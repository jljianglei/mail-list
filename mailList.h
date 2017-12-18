#ifndef _MAIL_LIST_H
#define _MAIL_LIST_H
#ifdef __cplusplus
extern "C" {
#endif/*__cplusplus*/
#define CONTACTS_MAX_COUNT 1000
#define CONTACT_NAME_LENGTH 40
#define CONTACT_TEL_LENGTH 20
#define CONTACT_DATE_LENGTH 30
#define CONTACT_ADDR_LENGTH 100
typedef struct contacts {
    char name[CONTACT_NAME_LENGTH];
	char tel[CONTACT_TEL_LENGTH];
	char date[CONTACT_DATE_LENGTH];
	char addr[CONTACT_ADDR_LENGTH];
}MailListContacts;
typedef struct mailList {
    MailListContacts contact[CONTACTS_MAX_COUNT];
	int currCount;
}MailList;
typedef enum resultCode {
   RESULT_UNKNOWN,
   RESULT_SUCCESS,
   RESULT_FAILD
}resultCode;
void mailListInit(MailList* list);
/*成功返回数据的索引，失败返回-1*/
int findContactByName(MailList * list,const char* name);
int findContactByTel(MailList * list,const char* tel);
/*可以先用find接口找到index，再调用这个接口，如果不想跟新姓名或者电话，传空串*/
resultCode updateContactsByIndex(MailList* list,int index,const char* name,const char* tel);
resultCode addContacts(MailList* list,MailListContacts* contact);
resultCode delContactByName(MailList* list,const char* name);
resultCode delContactByTel(MailList * list,const char* tel);
void showContacts(MailList* list);
#ifdef __cplusplus
}
#endif
#endif/*_MAIL_LIST_H*/
