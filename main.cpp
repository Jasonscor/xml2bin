#include "xml_data.h"
#include "test_case.h"

int main(int argc, char *argv[])
{

    TestCase tc;
    tc.test_lane_01();
    tc.test_lane_02(2);

    return 0;
}
