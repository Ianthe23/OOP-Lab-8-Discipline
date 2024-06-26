#include "service.h"


const vector<Disciplina>& Service::getAllContract() noexcept {
	return contract.get_contract();
}

void Service::genereaza_contract(int nr_discipline) {
	contract.genereazaContract(nr_discipline, repo.getAll());
}

void Service::exporta_contract(const string& nume) {
	contract.exportContract(nume);
}

void Service::empty_contract() {
	contract.emptyContract();
}

void Service::adauga_la_contract(const string& denumire, const string& profesor, const vector<Disciplina>& filtered) {
	auto gasit = repo.cautaRepo(denumire, profesor);
	if (gasit >= 0) {
		auto disciplina = repo.get_disciplina(denumire, profesor);
		contract.adaugaContract(disciplina);
	}
	else if (gasit == -1) {
		auto to_add = filtered;
		std::shuffle(to_add.begin(), to_add.end(), std::default_random_engine(time(0)));
		if (filtered.size() >= 1) {
			contract.adaugaContract(to_add.back());
		}
		else {
			throw RepoException("Disciplina nu exista!\n");
		}
	}
}

int Service::getContractsize() {
	return contract.get_contract().size();
}

map<string, DTO> Service::raport() noexcept {
	map<string, DTO> raport;
	auto discipline = repo.getAll();

	for (const auto& disciplina : discipline) {
		DTO tip(disciplina.get_tip());
		raport[disciplina.get_tip()] = tip;
	}

	for (const auto& disciplina : discipline) {
		int nr = raport[disciplina.get_tip()].get_count() + 1;
		DTO val(disciplina.get_tip(), nr);
		raport[disciplina.get_tip()] = val;
	}
	return raport;
}

void Service::adaugaSrv(const string& denumire, int ore, const string& tip, const string& profesor) {
	Disciplina disciplina{ denumire, ore, tip, profesor };

	validator.valideazaDisciplina(disciplina);
	repo.adaugaRepo(disciplina);
}


void Service::modificaSrv(const string& denumire, int ore, const string& tip, const string& profesor) {
	Disciplina disciplina{ denumire, ore, tip, profesor };

	validator.valideazaDisciplina(disciplina);
	repo.modificaRepo(disciplina);
}


void Service::stergeSrv(const string& denumire, const string& profesor) {
	repo.stergeRepo(denumire, profesor);
}


const Disciplina& Service::cautaSrv(const string& denumire, const string& profesor) {
	return repo.get_disciplina(denumire, profesor);
}


const vector<Disciplina>& Service::getAll() noexcept {
	return this->repo.getAll();
}


vector<Disciplina> Service::filterOre(int ore) {
	vector<Disciplina> filtered;

	copy_if(repo.getAll().begin(), repo.getAll().end(), std::back_inserter(filtered),
		[ore](const Disciplina& disciplina) noexcept{
		return disciplina.get_ore() == ore;
		});
	
	return filtered;
}


vector<Disciplina> Service::filterProfesor(const string& profesor) {
	vector<Disciplina> filtered;

	copy_if(repo.getAll().begin(), repo.getAll().end(), std::back_inserter(filtered),
		[profesor](const Disciplina& disciplina) noexcept{
			return disciplina.get_profesor() == profesor;
		});

	return filtered;
}

vector<Disciplina> Service::filterDenumire(const string& denumire) {
	vector<Disciplina> filtered;

	copy_if(repo.getAll().begin(), repo.getAll().end(), std::back_inserter(filtered),
		[denumire](const Disciplina& disciplina) noexcept {
			return disciplina.get_denumire() == denumire;
		});

	return filtered;
}


vector<Disciplina> Service::sortDenumire() {
	auto sorted = repo.getAll();
	std::sort(sorted.begin(), sorted.end(), cmpDenumire);
	return sorted;
}


vector<Disciplina> Service::sortOre() {
	auto sorted = repo.getAll();
	std::sort(sorted.begin(), sorted.end(), cmpOre);
	return sorted;
}


vector<Disciplina> Service::sortProfTip() {
	auto sorted = repo.getAll();
	std::sort(sorted.begin(), sorted.end(), cmpProfTip);
	return sorted;
}


