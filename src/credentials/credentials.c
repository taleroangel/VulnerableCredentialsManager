#include "credentials.h"

void Init_UserCredentials(UserCredentials *self) {
  memset(self->username, 0, CREDENTIAL_SIZE);
  memset(self->password, 0, CREDENTIAL_SIZE);
  self->signedin = 0U;
}

void Fill_UserCredentials(UserCredentials *self, const char *username,
                          const char *password) {
  strcpy(self->username, username);
  strcpy(self->password, password);
  self->signedin = 0U;
}

bool Check_UserCredentials(UserCredentials self) {
  if (self.signedin == 0U)
    return false;
  else
    return true;
}

void Login_UserCredentials(UserCredentials *self, UserCredentials other) {
  if (strcmp(self->username, other.username) == 0 &&
      strcmp(self->password, other.password) == 0) {
    self->signedin = 1U;
  }
}

void Print_UserCredentials(UserCredentials self) {
  printf("UserCredentials(\n\tusername=%s\n\tpassword=%s\n\tsignedin=%d\n)\n",
         self.username, self.password, self.signedin);
}