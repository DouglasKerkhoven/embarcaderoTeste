//---------------------------------------------------------------------------

#ifndef UnitMenuPrincipalH
#define UnitMenuPrincipalH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.Imaging.GIFImg.hpp>
#include <System.ImageList.hpp>
#include <Vcl.ImgList.hpp>
//---------------------------------------------------------------------------
class TFormMenuPrincipal : public TForm
{
__published:	// IDE-managed Components
	TMainMenu *MainMenu;
	TMenuItem *mnSocios;
	TMenuItem *mnSocCadastro;
	TMenuItem *mnSocCadastroCPF;
	TMenuItem *mnALibPort;
	TMenuItem *mnASenha;
	TMenuItem *mnSocConsultaOld;
	TMenuItem *mnSocConsulta;
	TMenuItem *mnBuscaCpf;
	TMenuItem *mnCDirBarao;
	TMenuItem *mnGED;
	TMenuItem *mnBuscaRestricoes;
	TMenuItem *Email1;
	TMenuItem *Financeiro1;
	TMenuItem *mnAssocIsentos;
	TMenuItem *mnArmario;
	TMenuItem *mnCaixas;
	TMenuItem *mnCAlteraPgto;
	TMenuItem *mnCAlteraSaldo;
	TMenuItem *mnCData;
	TMenuItem *mnCExtornar;
	TMenuItem *mnCCadastro;
	TMenuItem *mnFCarnes;
	TMenuItem *mnFCEmissaoGeralBra;
	TMenuItem *mnFCEmissaoGeralC;
	TMenuItem *mnFCEmissaoGeral;
	TMenuItem *mnFCConf;
	TMenuItem *mnCalculo;
	TMenuItem *mnCParcelamento;
	TMenuItem *mnCQuitacao;
	TMenuItem *mnCargaBanco;
	TMenuItem *mnFCheques;
	TMenuItem *mnDebA;
	TMenuItem *mnDebACadastro;
	TMenuItem *mnDebACancela;
	TMenuItem *mnDebAEmissao;
	TMenuItem *mnDebAProcessa;
	TMenuItem *mnDebARel;
	TMenuItem *mnDebitos;
	TMenuItem *mnDebConsulta;
	TMenuItem *mnDebEsporadicos;
	TMenuItem *mnDebSemestre;
	TMenuItem *mnDebRotinas;
	TMenuItem *mnDebMensalidades;
	TMenuItem *mnDebParcelamento;
	TMenuItem *mnDebSMS;
	TMenuItem *mnHist1;
	TMenuItem *mnHistCon;
	TMenuItem *mnHist;
	TMenuItem *mnHistRel;
	TMenuItem *mnProcessos;
	TMenuItem *mnProtocolo;
	TMenuItem *mnCadastro;
	TMenuItem *mnTerceiros;
	TMenuItem *mnCobrancaRegistrada;
	TMenuItem *Contabilidade1;
	TMenuItem *mnImporta;
	TMenuItem *mnImpBanco;
	TMenuItem *mnImpClube;
	TMenuItem *mnImpDebAut;
	TMenuItem *mnCRelCom;
	TMenuItem *mnCRelEve;
	TMenuItem *mnCRelGer;
	TMenuItem *Relatrios1;
	TMenuItem *mnRDA;
	TMenuItem *mnFRArmarios;
	TMenuItem *Mensalidades1;
	TMenuItem *fRFDemons;
	TMenuItem *fRFConciliacao;
	TMenuItem *fRFMensC;
	TMenuItem *fRFInad;
	TMenuItem *fRFMensA;
	TMenuItem *fRFMensP;
	TMenuItem *fRFParcelamentos;
	TMenuItem *mnFRTemp;
	TMenuItem *mnFRPendFinanceira;
	TMenuItem *Cadastro1;
	TMenuItem *mnFCadBanco;
	TMenuItem *mnFContas;
	TMenuItem *mnFContasMsg;
	TMenuItem *mnEtiqExp;
	TMenuItem *mnFFeriados;
	TMenuItem *mnTemp;
	TMenuItem *mnDA;
	TMenuItem *mnDAEmissao;
	TMenuItem *mnFCnrExc;
	TMenuItem *mnDAConsUsuarios;
	TMenuItem *mnDaconsulta;
	TMenuItem *mnDaCadastro;
	TMenuItem *mnDaCadastroItem;
	TMenuItem *mnDaRelatorios;
	TMenuItem *mnRrelItensDA;
	TMenuItem *Login1;
	TMenuItem *configuracao;
	TMenuItem *Cadastros1;
	TMenuItem *mnDominios;
	TMenuItem *Parmetros1;
	TMenuItem *Ajuda;
	TMenuItem *Sobre;
	TMenuItem *picosdeAjuda1;
	TMenuItem *mnAltSenha;
	TMenuItem *Sair;
	TPanel *PPrincipal;
	TPanel *Panel1;
	TLabel *LVersao;
	TLabel *Label2;
	TLabel *Label1;
	TLabel *LUsuario;
	TImage *Image1;
	TLabel *LServer;
	TImageList *ImageList2;
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall SairClick(TObject *Sender);
private:	// User declarations
public:		// User declarations

	bool close;
	int modalidade;
	int tipo_produto;
	int sistema;
	int rotina;
	String rotdep;
	String rotsocio;
	AnsiString rotina_temp_conv;
	AnsiString baixa_debito;

	void MontaMenu_Ado(TMainMenu *Menu,int cod_usr,int cod_sistema,TADOConnection *ADOConn);
	__fastcall TFormMenuPrincipal(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormMenuPrincipal *FormMenuPrincipal;
//---------------------------------------------------------------------------
#endif
