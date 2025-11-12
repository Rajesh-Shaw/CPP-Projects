#include <iostream>
#include <mysql/mysql.h>
#include <string>
#include <iomanip>
using namespace std;

class StudentDB
{
        MYSQL* conn;
    public:
        StudentDB() 
        {
            conn = mysql_init(0);
            if (conn == nullptr) 
            {
                cout << "MySQL Initialization failed!" << endl;
                exit(1);
            }

            // Connect to MySQL
            conn = mysql_real_connect(conn, "localhost", "root", "root", "student_db", 3306, NULL, 0);
            if (conn)
                cout << "Connected to MySQL successfully!\n";
            else 
            {
                cout << "Connection Error: " << mysql_error(conn) << endl;
                exit(1);
            }
        }

        ~StudentDB() 
        {
            mysql_close(conn);
        }
   
};


int main()
{
    StudentDB db;
    return 0;
}