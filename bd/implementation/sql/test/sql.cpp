#include "sql/sql.h"

#include "gtest/gtest.h"

TEST(psTest,successfulErrorCallingWriteWithoutConnect) {
    SQL db;
    ASSERT_EQ(db.writeUserFile("",""),Error::failedWrite);
}
TEST(psTest,successfulWrite) {
    SQL db;
    db.connect();
    ASSERT_EQ(db.writeUserFile("Saveliy","/home/saveliy/Рабочий стол/пароль github.txt"),Error::successWriteToFile);
}
TEST(psTest,successfulRead) {
    SQL db;
    db.connect();
    ASSERT_EQ(db.readUserFile("Saveliy"),Error::successRead);
}
TEST(psTest,failedCallingReadWithoutConnect) {
    SQL db;
    ASSERT_EQ(db.readUserFile(""),Error::errorRead);
}
TEST(psTest,successfulConnectUseIsConnecting) {
    SQL db;
    db.connect();
    ASSERT_EQ(db.isconnected(),true);
}
TEST(psTest,successfulDissconectUseIsConnecting) {
    SQL db;
    db.connect();
    db.disconnect();
    ASSERT_EQ(db.isconnected(),false);
}
TEST(psTest,successConnectAndDisconnect) {
    SQL db;
    ASSERT_EQ(db.connect(),Error::successConnect);
    ASSERT_EQ(db.disconnect(),Error::successDisconnect);
}