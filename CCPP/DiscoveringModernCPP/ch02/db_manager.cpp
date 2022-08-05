#include <iostream>

using namespace std;

class ResultSet {

};

class Statement {
public:
    ResultSet *executeQuery(const string &query) {
        return new ResultSet;
    }

    void terminateResultSet(ResultSet *rs) {
        cout << "terminate resultset" << endl;
    }
};

class Connection {
public:
    Connection(const string &u, const string &un, const string &p) : url(u), username(un), password(p) {}

    Statement *createStatement() {
        return new Statement;
    }

    void terminateStatement(Statement *stmt) {
        cout << "terminate statement" << endl;
    }

    friend ostream &operator<<(ostream &out, const Connection &conn) {
        out << "Connection:[" << conn.url << ", " << conn.username << ", " << conn.password << "]";
        return out;
    }

private:
    string username;
    string password;
    string url;
};

class Environment {
public:
    static Environment *createEnvrionment() {
        return new Environment();
    }

    static void terminateEnvironment(Environment *env) {
        cout << "terminate environment" << endl;
    }

    Connection *createConnection(const string &url, const string &username, const string &password) {
        return new Connection(url, username, password);
    }

    void terminateConnection(Connection *conn) {
        cout << "terminate connection:" << *conn << endl;
    }
};

struct EnvironmentDeleter {
    void operator()(Environment *env) {
        Environment::terminateEnvironment(env);
    }
};

struct ConnectionDeleter {
    ConnectionDeleter(shared_ptr<Environment> env) : env(env) {}

    void operator()(Connection *conn) {
        env->terminateConnection(conn);
    }

    shared_ptr<Environment> env;
};

struct ResultSetDeleter {
    ResultSetDeleter(shared_ptr<Connection> conn, Statement *stmt) : conn(conn), stmt(stmt) {};

    void operator()(ResultSet *rs) {
        stmt->terminateResultSet(rs);
        conn->terminateStatement(stmt);
    }

    shared_ptr<Connection> conn;
    Statement *stmt;
};

class DBManager {
public:
    using ResultSetSharedPtr = shared_ptr<ResultSet>;

    DBManager(const string &url, const string &username, const string &password) :
            environment(Environment::createEnvrionment(), EnvironmentDeleter{}),
            connection({environment->createConnection(url, username, password),
                        ConnectionDeleter{environment}}) {
    }

    ResultSetSharedPtr query(const string &query) {
        Statement *stmt = connection->createStatement();
        ResultSet *rs = stmt->executeQuery(query);
        auto deleter = ResultSetDeleter({connection, stmt});
        return ResultSetSharedPtr{rs, deleter};
    }

public:
    shared_ptr<Environment> environment;
    shared_ptr<Connection> connection;
};

int main() {
    DBManager db("127.0.0.1", "username", "password");
    db.query("hello world");
    return 0;
}