#ifndef __CREDENTIALS_H__
#define __CREDENTIALS_H__

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define CREDENTIAL_SIZE 25

typedef struct {
  char username[CREDENTIAL_SIZE];
  char password[CREDENTIAL_SIZE];
  uint8_t signedin;
} UserCredentials;

void Init_UserCredentials(UserCredentials *self);

void Fill_UserCredentials(UserCredentials *self, const char *username,
                          const char *password);

bool Check_UserCredentials(UserCredentials self);

void Login_UserCredentials(UserCredentials *self, UserCredentials other);

void Print_UserCredentials(UserCredentials self);

#endif //__CREDENTIALS_H__