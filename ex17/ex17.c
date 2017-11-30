#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

struct Address {
	int id;
	int set;
	char *name;
	char *email;
};

struct Database {
	int max_data;
	int max_rows;
	struct Address *rows;
};

struct Connection {
	FILE *file;
	struct Database *db;
};

void die(const char *message, struct Connection *conn);
void Address_print(struct Address *addr);
void Database_load(struct Connection *conn);
struct Connection *Database_open(const char *filename, char mode);
void Database_close(struct Connection *conn);
void Database_write(struct Connection *conn);
void Datbase_create(struct Connection *conn);
void Database_set(struct Connection *conn, int id, const char *name, const char *email);
void Database_get(struct Connection *conn, int id);
void Database_delete(struct Connection *conn, int id);
void Database_list(struct Connection *conn);

void die(const char *message, struct Connection *conn) {
	if(errno) {
		perror(message);
	} else {
		printf("ERROR: %s\n", message);
	}

	Database_close(conn);
	exit(1);
}

void Address_print(struct Address *addr) {
	printf("%d %s %s\n", addr->id, addr->name, addr->email);
}

void Database_load(struct Connection *conn) {
	// we point our file reader to the start of the file
	fseek(conn->file, 0);

	//we read our general database struct with the size of max_rows and max_data
	int rc = fread(conn->db, sizeof(struct Database), 1, conn->file);	
	if(rc != 1) die("Failed to load database.", conn);

	//we query some useful vars
	int max_rows = conn->db->max_rows;
	int max_data = conn->db->max_data;

	// we read our rows
	rc = fread(con->db->rows, sizeof(struct Address), max_rows, conn->file);
	if(rc != max_rows) die("Failed to load rows.", conn);

	//then we need to read our names and emails load them to 
	char **data;
	rc = fread(con->db->rows, sizeof(char) * max_data, max_rows * 2, conn->file);
	if( rc != max_rows*2) die("Failed to load data of rows.", conn);


}

struct Connection *Database_open(const char *filename, char mode) {
	struct Connection *conn = malloc(sizeof(struct Connection));
	if(!conn)
		die("Memory error", conn);
	
	conn->db = malloc(sizeof(struct Database));
	if(!conn->db) die("memory error", conn);

	if (mode == 'c' ){
		conn->file = fopen(filename, "w");
	} else {
		conn->file = fopen(filename, "r+");

		if( conn->file ){
			Database_load(conn);
		}
	}

	if (!conn->file) die("Failed to open the datbase file", conn);

	return conn;
}

void Database_close(struct Connection *conn) {
	if(conn) {
		if(conn->file) fclose(conn->file);
		if(conn->db) free(conn->db);
		free(conn);
	}
}

void Database_write(struct Connection *conn) {
	rewind(conn->file);

	int rc = fwrite(conn->db, sizeof(struct Database), 1, conn->file);
	if( rc != 1 ) die("Failed to write datbases.", conn);

	rc = fflush(conn->file);
	if( rc == -1) die("Cannot flush database.", conn);
}

void Database_create(struct Connection *conn) {
	int i=0;
	int max_rows = conn->db->max_rows;
	for(i=0; i<max_rows; i++){
		//make a prototype to initialize it
		struct Address addr = {.id = i, .set = 0};
		conn->db->rows[i]=addr;
	}
}

void Database_set(struct Connection *conn, int id, const char *name, const char *email) {
	struct Address *addr = &conn->db->rows[id];
	if(addr->set) die("Aready set, delete it first", conn);


	//we set the check variable
	addr->set = 1;

	//we set some useful vars
	int max_data = conn->db->max_data;

	//allocation of memory
	addr->name = malloc(sizeof(char) * max_data);
	if(addr->name) die("Memory allocation for name failed");
	addr->email = malloc(sizeof(char) * max_data);
	if(addr->email) die("Memory allocation for email failed");

	//string copy operations
	char *res =  strncpy(addr->name, name, max_data);
	char *res2 = strncpy(addr->email, email, max_data);

	//verification
	if(!res) die("Name copy failed", conn);
	if(!res2) die("Email copy failed", conn);

	//some extra initialization
	addr->email[max_data-1] = '\0';
	addr->name[max_data-1] = '\0';
	
}

void Database_get(struct Connection *conn, int id) {
	struct Address *addr = &conn->db->rows[id];

	if( addr->set) {
		Address_print(addr);
	} else {
		die("ID is not set", conn);
	};
}

void Database_delete(struct Connection *conn, int id) {
	struct Address addr = {.id = id, .set = 0};
	conn->db->rows[id] = addr;
}

void Database_list(struct Connection *conn) {
	int i = 0;
	struct Database *db = conn->db;

	for(i=0; i< MAX_ROWS; i++) {
		struct Address *cur = &db->rows[i];

		if(cur->set) {
			Address_print(cur);
		}
	}
}

int main(int argc, char *argv[]){
	if(argc < 3)
		die("USAGE: ex17 <dbfile> <action> [action params]", NULL);
	
	char *filename = argv[1];
	char action = argv[2][0];
	struct Connection *conn = Database_open(filename, action);
	int id = 0;

	if(argc > 3) id = atoi(argv[3]);
	if(id >= MAX_ROWS) die("There's not that many records.", conn);

	switch (action) {
		case 'c':
			int max_data = id;
			if(max_data==0) die("The minimum value for max_data is 1",conn);
			int max_rows = atoi(argv[4];
			if(max_rows==0) die("The minimum value for max_rows is 1",conn);
			Database_create(conn);
			Database_write(conn);
			break;
		case 'g':
			if( argc != 4 )
				die("Need an id to get", conn);

			Database_get(conn, id);
			break;

		case 's':
			if( argc != 6)
				die("Need id, name, email to set", conn);

			Database_set(conn, id, argv[4], argv[5]);
			Database_write(conn);
			break;

		case 'd':
			if( argc != 4 )
				die("Need id to delete", conn);

			Database_delete(conn, id);
			Database_write(conn);
			break;

		case 'l':
			Database_list(conn);
			break;
		default:
			die("Invalid action: c=create, g=get, s=set, d=del, l=list", conn);
			break;
	}

	Database_close(conn);

	return 0;
}











