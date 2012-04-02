
/*Author Feiyi Su  Qingju Luo   This is for testing data conversion from pressure*/

#include <stdio.h>
#include <check.h>
#include "../../src/conversion.h"




void setup (void) {
	
printf("Test Set up\n");

}

void teardown (void) {
printf("Test tear down\n");
}



START_TEST(testConversionPtbUnit) {
  printf("Test case 1\n");
  float test_value = 29.1;
  fail_if(("%f",&test_value)==1);
  fail_if(conversion_ptb(test_value)==0,"wrong result,the ptb=0!");

}END_TEST


START_TEST(testConversionPtkUnit) {
  printf("Test case 2\n");
  float test_value = 29.1;
  fail_if(("%f",&test_value)==1);
  fail_if(conversion_ptk(test_value)==0,"wrong result,the ptk=0!");

}END_TEST


START_TEST(testConversionKtpUnit) {

  printf("Test case 3\n");
  fail_if(conversion_ktp()==0,"wrong result,the ktp=0!");

}END_TEST

START_TEST(testConversionKtpLessThan) {

  printf("Test case 4\n");
  fail_if(conversion_ktp()<=14.5,"wrong result,the convertion more than 14.5!");

}END_TEST



START_TEST(testConversionKtbUnit) {
  printf("Test case 5\n");
  fail_if(conversion_ktb()==0,"wrong result,the ktb=0!");

}END_TEST

START_TEST(testConversionKtbLessThan) {
  printf("Test case 6\n");
  fail_if(conversion_ktb()<=1.02,"wrong result,the convertion more than 1.02!");

}END_TEST



START_TEST(testConversionBtkUnit) {
  printf("Test case 7\n");
  float test_value = 30.2;
  fail_if(("%f",&test_value)==1);
  fail_if(conversion_btk(test_value)==0,"wrong result,the btk=0!");

}END_TEST

START_TEST(testConversionBtpUnit) {
  printf("Test case 8\n");
  float test_value = 30.2;
  fail_if(conversion_btp(test_value)==0,"wrong result,the btp=0!");

}END_TEST




Suite * conversion_suite(void) {
  Suite *s = suite_create("conversion value");
  TCase *tc = tcase_create("returnvalure");
  tcase_add_checked_fixture(tc,setup,teardown);
  tcase_add_test(tc,testConversionPtbUnit);
  tcase_add_test(tc,testConversionPtkUnit);
  tcase_add_test(tc,testConversionKtpUnit);
  tcase_add_test(tc,testConversionKtpLessThan);
  tcase_add_test(tc,testConversionKtbUnit);
  tcase_add_test(tc,testConversionKtbLessThan);
  tcase_add_test(tc,testConversionBtkUnit);
  tcase_add_test(tc,testConversionBtpUnit);

  suite_add_tcase(s,tc);
  return s;
}

