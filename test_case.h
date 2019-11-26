#ifndef TEST_CASE_H
#define TEST_CASE_H

class TestCase
{
public:
    TestCase();
    virtual ~TestCase();

public:
    void test_lane_01();
    void test_lane_02(int n);

};

#endif // TEST_CASE_H
