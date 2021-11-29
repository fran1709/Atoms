#if !defined(_REPORT_)
#define _REPORT_

class Report {
    private:
    int cantAtomos = 0;
    int cantMoleculas = 0;
    int cantOrganismos = 0;

    public:
    Report();
    int getCantAtomos();
    void setCantAtomos(int pCant);
    void addAtomos(int pCant);
    int getCantMoleculas();
    void setCantMoleculas(int pCant);
    void addMoleculas(int pCant);
    int getCantOrganismos();
    void setCantOrganismos(int pCant);
    void addOrganismos(int pCant);
};

Report::Report() {
    ;
}
int Report::getCantAtomos() {
    return this->cantAtomos;
}
void Report::setCantAtomos(int pCant) {
    this->cantAtomos = pCant;
}
void Report::addAtomos(int pCant) {
   this->cantAtomos += pCant; 
}
int Report::getCantMoleculas() {
    return this->cantMoleculas;
}
void Report::setCantMoleculas(int pCant){
    this->cantMoleculas = pCant;
}
void Report::addMoleculas(int pCant) {
    this->cantMoleculas += pCant;
}
int Report::getCantOrganismos() {
    return this->cantOrganismos;
}
void Report::setCantOrganismos(int pCant) {
    this->cantOrganismos = pCant;
}
void Report::addOrganismos(int pCant) {
    this->cantOrganismos += pCant;
}

#endif // _REPORT_