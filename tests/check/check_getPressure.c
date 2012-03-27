/*author Yuwei chen, Qingju Luo */
    
#include <check.h>
#include "../../src/pressure.h"


void setup (void) {
  ;
}

void teardown (void) {
     ;
}


START_TEST(testGetPressure) {

  fail_if(getPressure()==0,"wrong result,the pressure=0!");

}END_TEST

START_TEST(testPressureLessThan100) {
  fail_if(getPressure()<100, "the pressure is less than 100!");
}END_TEST

Suite * calc_suite(void) {
  Suite *s = suite_create("pressure");
  
  TCase *tc = tcase_create("returnvalure");
  tcase_add_checked_fixture(tc,setup,teardown);
  tcase_add_test(tc,testGetPressure);
  tcase_add_test(tc,testPressureLessThan100);
  suite_add_tcase(s,tc);
  return s;
}
