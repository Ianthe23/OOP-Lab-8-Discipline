#ifndef TESTS_H_
#define TESTS_H_

#include "domain.h"
#include "repo.h"
#include "validator.h"
#include "service.h"
#include <assert.h>

class Tests {
	void testDomain();
	void testConstructor_Getters();
	void testCopyConstructor();
	void testSetters();
	void testToString();
	void testOperatori();
	void testComparatori();
	void testDTO();
	void testCopyDTO();
	void testGetDTO();

	void testRepo();
	void testAdaugaRepo();
	void testModificaRepo();
	void testCautaRepo();
	void testStergeRepo();
	void testGet_disciplina();

	void testValidator();

	void testService();
	void testAdaugaSrv();
	void testModificaSrv();
	void testStergeSrv();
	void testCautaSrv();
	void testFiltrare();
	void testSortare();
	void testContract();
	void testAdaugaContract();
	void testCautaContract();
	void testGenereazaContract();
	void testExportaContract();
	void testEmptyContract();
	void testGetAllContract();
	void test_genereaza_contract();
	void test_exporta_contract();
	void test_empty_contract();
	void test_adauga_la_contract();
	void test_getContractsize();
	void testRaport();
	void testFilterDenumire();


public:
	Tests() noexcept{};
	void testAll();
	~Tests() {

	};
};


#endif /* TESTS_H_ */
