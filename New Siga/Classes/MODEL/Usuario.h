

class Usuario

{
private:
	AnsiString nome;
	int codigo;
	int matricula;
	bool adm;
	bool admFin;
	bool admMat;


public:
	 // Getters e Setters
	 AnsiString getNome(){return nome;}

	 void setNome(AnsiString Nome){nome = Nome;}

		 int getCodigo(){return codigo;}

	 void setCodigo(int dado){codigo = dado;}

		 int getMatricula(){return matricula;}

	 void setMatricula(int dado){nome = dado;}

		 bool getAdm(){return adm;}

	 void setADM(bool dado){dado = adm;}

		 bool getAdmFin(){return admFin;}

	 void setAdmFin(bool dado){admFin = dado;}

		 bool getAdmMat(){return admMat;}

	 void setAdmMat(bool dado){admMat = dado;}





};
