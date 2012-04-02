default:
	@echo "--- Normal compilation ----------------------------------"
	@echo "make conversion     produces binary in src/"
	@echo " "
	@echo "--- Cleaning up -----------------------------------------"
	@echo "make clean    recursively clean up subdirs"
	@echo " "
	@echo "--- Verification and debugging --------------------------"
	@echo "make check         run unit tests"
	@echo "make gcovcheck     run unit tests with gcov (statement coverage)"
	@echo "make gcovcheckb    run unit tests with gcov (branch coverage)"
	@echo "make memcheck      run unit tests with valgrind"

conversion:
	cd src && $(MAKE) conversion

clean:
	cd src && $(MAKE) clean
	cd tests/check && $(MAKE) clean

check:  
	cd src && $(MAKE) testobjs
	cd tests/check && $(MAKE) check 

gcovcheck: clean
	cd src && $(MAKE) testobjscov
	cd tests/check && $(MAKE) gcovcheck

gcovcheck: clean
	cd src && $(MAKE) testobjscov
	cd tests/check && $(MAKE) gcovcheck


gcovcheckb: clean
	cd src && $(MAKE) testobjscov
	cd tests/check && $(MAKE) gcovcheck

memcheck: clean
	cd src && $(MAKE) testobjsgdb
	cd tests/check && $(MAKE) memcheck

