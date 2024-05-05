#include <iostream>
#include <sqlite3.h>

using namespace std;

int main() {
    sqlite3 *db;
    int rc = sqlite3_open("sj.db", &db);

    if (rc != SQLITE_OK) {
        cerr << "데이터베이스 열기 실패: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return 1;
    }

    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, "SELECT * FROM 성적;", -1, &stmt, NULL);

    if (rc != SQLITE_OK) {
        cerr << "쿼리 준비 실패: " << sqlite3_errmsg(db) << endl;
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 1;
    }

    double totalScore1 = 0, totalScore2 = 0;
    int numStudents = 0;

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        const char *name = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));
        int score1 = sqlite3_column_int(stmt, 3);
        int score2 = sqlite3_column_int(stmt, 4);
        double totalScore = score1 + score2;

        totalScore1 += score1;
        totalScore2 += score2;
        numStudents++;

        cout << "학생 이름: " << name << endl;
        cout << "과목1: " << sqlite3_column_text(stmt, 1) << ", 점수: " << score1 << endl;
        cout << "과목2: " << sqlite3_column_text(stmt, 2) << ", 점수: " << score2 << endl;
        cout << "총점: " << totalScore << endl << endl;
    }

    if (numStudents > 0) {
        double averageScore1 = totalScore1 / numStudents;
        double averageScore2 = totalScore2 / numStudents;

        cout << "과목1 평균: " << averageScore1 << endl;
        cout << "과목2 평균: " << averageScore2 << endl;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}
