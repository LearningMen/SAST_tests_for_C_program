/*
    The program tries to demonstrate that a user could drop a SQL table 
    through SQLite injection.

    It first creates a table, and the asks for user input.
    The user applies an injection and drops the table.
    The instruction will be executed without sanitization.

    The program is meant to be flagged by SAST tool for possible SQL injection.

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

/*
    This callback function is tailor made for what SQLite expects.
*/
int callback(void *data, int argc, char **argv, char **azColName) {
    int *count = (int*)data;
    *count = atoi(argv[0]);
    return 0;
}


int main() {
    sqlite3 *db;
    char *err_msg = 0;
    int rc;

// Create a table and insert one row. For simplicity, error handling is sloopy.

    // Open an in-memory SQLite database
    rc = sqlite3_open(":memory:", &db);
    // Create a dummy table and insert a row
    char *sql = "CREATE TABLE Users(Id INT, Name TEXT);";
    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    // Insert one row
    sql = "INSERT INTO Users(Id, Name) VALUES(1, 'Alice')";
    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    // Print row number in USERS
    int rowCount = 0;
    sql = "SELECT COUNT(*) FROM Users;";
    rc = sqlite3_exec(db, sql, callback, &rowCount, &err_msg);
    // very basic error handling, not advisible in production code.
    if (rowCount !=1) exit(1);     



// Now asks for user input and execute it without sanitization (SQL injection)
    char user_input[256];
    printf("Enter a SQL command: ");
    // Example user input:INSERT INTO Users(Id, Name) VALUES(1, 'Alice'); DROP TABLE Users;
    fgets(user_input, 256, stdin);
    user_input[strcspn(user_input, "\n")] = 0; // Remove newline character
    rc = sqlite3_exec(db, user_input, 0, 0, &err_msg);

// Check that the table was dropped by user, SQL injection was successful.
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    } else {
        printf("Executed SQL command successfully\n");
        // Check if a table was dropped and the table user no longer exists
        if (sqlite3_table_column_metadata(db, NULL, "Users", NULL, NULL, NULL, NULL, NULL, NULL) == SQLITE_ERROR) {
            printf("The table was dropped successfully.\n");
        }
    }

    sqlite3_close(db);
    return 0;
}
