#include "mailList.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
static MailList list;
void mailListInit(MailList* list)  {
    if(list == NULL)
		return;
	list->currCount = 0;
	memset(list->contact,0,sizeof(list->contact));
}
int findContactByName(MailList* list,const char* name) {
    if(name == NULL || list == NULL)
		return -1;
	if(list->currCount == 0) {
	    return -1;
	}
	int i;
	for(i = 0; i < list->currCount; ++i) {
	    if(strcmp(list->contact[i].name,name) == 0)
			return i;
	}
	return -1;
}
int findContactByTel(MailList* list,const char* tel) {
     if(list == NULL || tel == NULL)
		 return -1;
	 if(list->currCount == 0)
		 return -1;
	 int i;
	 for(i = 0; i < list->currCount; ++i) {
	     if(strcmp(list->contact[i].tel,tel) == 0)
			 return i;
	 }
	 return -1;
}
resultCode updateContactsByIndex(MailList* list,int index,const char* name,const char* tel) {
    if(list == NULL || name == NULL || tel == NULL)
		return RESULT_FAILD;
	if(index < 0 || index > CONTACTS_MAX_COUNT || index >= list->currCount) {
	    return RESULT_FAILD;
	}
	if(strcmp(name,"") != 0) {
	   strncpy(list->contact[index].name,name,CONTACT_NAME_LENGTH);
	}
	if(strcmp(tel,"") != 0) {
	   strncpy(list->contact[index].tel,tel,CONTACT_TEL_LENGTH);
	}
	return RESULT_SUCCESS;
}
resultCode addContacts(MailList* list,MailListContacts* contact) {
    if(list == NULL || contact == NULL)
		return RESULT_FAILD;
	if(list->currCount == CONTACTS_MAX_COUNT) {
	   printf("联系人已满，请删除一部分不用的联系人");
	   return RESULT_FAILD;
	}
	list->contact[list->currCount] = *contact;
	list->currCount++;
	return RESULT_SUCCESS;
}
resultCode delContactByName(MailList* list,const char* name) {
    if(list == NULL || name == NULL)
		return RESULT_FAILD;
    if(list->currCount == 0)
		return RESULT_FAILD;
	int i,j;
	for(i = 0; i < list->currCount; ++i) {
	    if(strcmp(list->contact[i].name,name) == 0) {
		   for(j = i; j < list->currCount - 1; ++j) {
		       list->contact[j] = list->contact[j + 1];
		   }
		   list->currCount--;
		   return RESULT_SUCCESS;
		}
	}
	return RESULT_FAILD;
}
resultCode delContactByTel(MailList* list,const char* tel) {
    if(list == NULL || tel == NULL)
		return RESULT_FAILD;
	if(list->currCount == 0)
		return RESULT_FAILD;
	int i,j;
	for(i = 0; i < list->currCount; ++i) {
	    if(strcmp(list->contact[i].tel,tel) == 0) {
		   for(j = i; j < list->currCount - 1; ++j) {
		      list->contact[j] = list->contact[j + 1];
		   }
		   list->currCount--;
		   return RESULT_SUCCESS;
		}
	}
	return RESULT_FAILD;
}
void showContacts(MailList* list) {
    if(list == NULL)
		return;
	if(list->currCount == 0) 
		return;
	int i;
	printf("name--------------------tel--------------------date--------------------addr\n");
	for(i = 0; i < list->currCount; ++i) {
		printf("%-24s%-23s%-24s%-24s\n",list->contact[i].name,list->contact[i].tel,list->contact[i].date,list->contact[i].addr);
	}
	printf("\n\n");
}
int main() {
   mailListInit(&list);
   MailListContacts contact1;
   strncpy(contact1.name,"zhao",CONTACT_NAME_LENGTH);
   strncpy(contact1.tel,"12345607813",CONTACT_TEL_LENGTH);
   strncpy(contact1.date,"19360615",CONTACT_DATE_LENGTH);
   strncpy(contact1.addr,"xxxxxx1",CONTACT_ADDR_LENGTH);
   addContacts(&list,&contact1);
   MailListContacts contact2;
   strncpy(contact1.name,"qian",CONTACT_NAME_LENGTH);
   strncpy(contact1.tel,"12390607813",CONTACT_TEL_LENGTH);
   strncpy(contact1.date,"19071230",CONTACT_DATE_LENGTH);
   strncpy(contact1.addr,"xxxxxx2",CONTACT_ADDR_LENGTH);
   addContacts(&list,&contact1);
   showContacts(&list);
   int ret = -1;
   const char * str = "zhao";
   ret = findContactByName(&list,str);
   if(ret == -1) {
     printf("not find %s\n",str);
   }
   else {
     printf("find %s,index is %d\n",str,ret);
   }
   str = "qian";
   ret = findContactByName(&list,str);
   if(ret == -1) {
     printf("not find %s\n",str);
   }
   else {
     printf("find %s,index is %d\n",str,ret);
	 printf("update %s to qian2\n",str);
	 updateContactsByIndex(&list,ret,"qian2","");
	 showContacts(&list);
   }
   str = "xxx";
   ret = findContactByName(&list,str);
   if(ret == -1) {
     printf("not find %s\n",str);
   }
   else {
     printf("find %s,index is %d\n",str,ret);
   }
   str = "zhao";
   if(delContactByName(&list,str) == RESULT_SUCCESS) {
      printf("del %s success\n",str);
	  showContacts(&list);
   }
   else {
      printf("del %s faild\n",str);
   }
   if(delContactByTel(&list,NULL) == RESULT_FAILD) {
      printf("del faild\n");
   }
   else {
      printf("del success\n");
   }
   str = "xxxxx";
   if(delContactByTel(&list,str) == RESULT_FAILD) {
      printf("del %s faild\n",str);
   }
   else {
      printf("del %s success\n",str);
   }
   return 0;
}
