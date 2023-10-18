# 🔐 VulnerableCredentialsManager
Stop forgetting your passwords!, store them "securely" and access them with a single password.
*__Disclaimer:__ This is not a real credentials manager, is meant to be exploited* 

### 🏗️ Compilation
Requires a C compiler and Meson build system\
**Dependencies:** SQLite3-dev
```sh
meson setup build
meson compile -C build
```

### 🗃️ Database
Requires SQLite3 command line

```sh
sqlite3 credentials.sqlite3 < sql/schema.sql
sqlite3 credentials.sqlite3 < sql/values.sql
```

### 🛠️ Usage
Requires SQLite database as argument
```sh
./build/credentials_manager credentials.sqlite3
```