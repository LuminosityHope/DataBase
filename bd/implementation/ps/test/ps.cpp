#include "ps/ps.h"

#include "gtest/gtest.h"

TEST(psTest,successfulErrorCallingWriteWithoutConnect) {
    PS db;
    ASSERT_EQ(db.writeUserFile("",""),Error::failedWrite);
}
TEST(psTest,successfulWrite) {
    PS db;
    db.connect();
    ASSERT_EQ(db.writeUserFile("Saveliy","/home/saveliy/Рабочий стол/пароль github.txt"),Error::successWriteToFile);
}
TEST(psTest,successfulRead) {
    PS db;
    db.connect();
    ASSERT_EQ(db.readUserFile("Saveliy"),Error::successRead);
}
TEST(psTest,failedCallingReadWithoutConnect) {
    PS db;
    ASSERT_EQ(db.readUserFile(""),Error::errorRead);
}
TEST(psTest,failedCallingReadWithIncorrectName) {
    PS db;
    db.connect();
    ASSERT_EQ(db.readUserFile("dkaskdskakl"),Error::errorRead);
}
TEST(psTest,successfulConnectUseIsConnecting) {
    PS db;
    db.connect();
    ASSERT_EQ(db.isconnected(),true);
}
TEST(psTest,successfulDissconectUseIsConnecting) {
    PS db;
    db.connect();
    db.disconnect();
    ASSERT_EQ(db.isconnected(),false);
}
TEST(psTest,successConnectAndDisconnect) {
    PS db;
    ASSERT_EQ(db.connect(),Error::successConnect);
    ASSERT_EQ(db.disconnect(),Error::successDisconnect);
}
