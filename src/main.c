#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "credentials/credentials.h"

#include <sqlite3.h>

#define STATEMENT_MAX_LENGTH 120

int main(int argc, char **argv) {

  // Credentials manager
  printf("Welcome to VulnerableCredentialsManager v1.0.0!\n");

  // Check arguments
  if (argc != 2) {
    fprintf(stderr, "Requires database as argument");
    return EXIT_FAILURE;
  }

  // Open the database
  sqlite3 *database = NULL;
  if (sqlite3_open(argv[1], &database) != SQLITE_OK) {
    perror("Database error");
    return EXIT_FAILURE;
  }

  // Load credentials from database
  sqlite3_stmt *statementHandle = NULL;
  if (sqlite3_prepare_v2(database, "SELECT COUNT(*) FROM users u;", -1,
                         &statementHandle, NULL) != SQLITE_OK) {
    fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(database));
    sqlite3_close(database);
    return EXIT_FAILURE;
  }

  if (sqlite3_step(statementHandle) != SQLITE_ROW) {
    fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(database));
    sqlite3_close(database);
    return EXIT_FAILURE;
  }

  // Get amount of users
  int numberOfUsers = sqlite3_column_int(statementHandle, 0);

  // Fetch every user
  statementHandle = NULL;
  if (sqlite3_prepare_v2(database, "SELECT * FROM users u;", -1,
                         &statementHandle, NULL) != SQLITE_OK) {
    fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(database));
    sqlite3_close(database);
    return EXIT_FAILURE;
  }

  // Create user list
  UserCredentials *users =
      (UserCredentials *)malloc(sizeof(UserCredentials) * numberOfUsers);

  // Iterate over users
  for (int i = 0; i < numberOfUsers; i++) {

    // Retrieve row
    if (sqlite3_step(statementHandle) != SQLITE_ROW) {
      fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(database));
      sqlite3_close(database);
      free(users);
      return EXIT_FAILURE;
    }

    // Retrieve data
    const char *username =
        (const char *)sqlite3_column_text(statementHandle, 0);
    const char *password =
        (const char *)sqlite3_column_text(statementHandle, 1);

    // Fill data
    Init_UserCredentials(&users[i]);
    Fill_UserCredentials(&users[i], username, password);
  }

  // Create credentials
  UserCredentials credentials;
  Init_UserCredentials(&credentials);

  // Ask for credentials
  printf("Enter your credentials (25 characters max)\n");
  printf("Username: ");
  scanf("%s", credentials.username);
  printf("Password: ");
  scanf("%s", credentials.password);

  // Try to login
  for (int i = 0; i < numberOfUsers; i++) {
    Login_UserCredentials(&credentials, users[i]);
  }

  // Signin
  if (Check_UserCredentials(credentials)) {
    printf("\nWelcome `%s`!\n", credentials.username);
  } else {
    printf("Invalid credentials!\nFailed to sign in\n");
    // Close the database
    free(users);
    sqlite3_close(database);
    return EXIT_FAILURE;
  }

  // Get all the passwords and show them
  statementHandle = NULL;
  char statement[STATEMENT_MAX_LENGTH];
  sprintf(statement, "SELECT * FROM passwords p WHERE p.user = '%s'",
          credentials.username);

  if (sqlite3_prepare_v2(database, statement, -1, &statementHandle, NULL) !=
      SQLITE_OK) {
    fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(database));
    sqlite3_close(database);
    free(users);
    return EXIT_FAILURE;
  }

  fprintf(stdout, "Your passwords are (KEY -> VALUE)\n\n");
  while (sqlite3_step(statementHandle) == SQLITE_ROW) {
    const char *key = (const char *)sqlite3_column_text(statementHandle, 1);
    const char *value = (const char *)sqlite3_column_text(statementHandle, 2);
    fprintf(stdout, "%s -> %s\n", key, value);
  }

  // Close the database
  free(users);
  sqlite3_close(database);
  printf("\nGoodbye!\n");
  return EXIT_SUCCESS;
}