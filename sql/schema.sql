DROP TABLE IF EXISTS users;
CREATE TABLE users (
	username TEXT PRIMARY KEY NOT NULL,
	password TEXT NOT NULL
);

DROP TABLE IF EXISTS passwords;
CREATE TABLE passwords (
	user TEXT NOT NULL,
	key TEXT NOT NULL,
	value TEXT NOT NULL,
	PRIMARY KEY (user, key),
	FOREIGN KEY (value) REFERENCES users(username)
);