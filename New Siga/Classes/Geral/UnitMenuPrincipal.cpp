//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <ADODB.hpp>

#include "UnitMenuPrincipal.h"
#include "Usuario.h"
#include "DataBase.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormMenuPrincipal *FormMenuPrincipal;


extern Usuario *usuario;
extern DataBase *bancoDados;
//---------------------------------------------------------------------------
__fastcall TFormMenuPrincipal::TFormMenuPrincipal(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormMenuPrincipal::FormActivate(TObject *Sender)
{
try
	{
	Image1->Picture->LoadFromFile("brasao_fundo.gif");
	}
catch(...)
	{

	}
AnsiString teste;

LUsuario->Caption = usuario->getNome();

	bancoDados->Consulta("SELECT CONVERT(VARCHAR(35),@@servername) 'SERVER', CONVERT(VARCHAR,DB_NAME()) AS 'DB'");
	LServer->Caption="SERVER: "+bancoDados->ToString(0)+"\\"+UpperCase(bancoDados->ToString(1));
     if (LServer->Caption!="SERVER: SERVIDOR-BD01\\CLUBECURITIBANO\\ASSOCIADOS"	&& LServer->Caption!="SERVER: 192.168.0.3\\CLUBECURITIBANO\\ASSOCIADOS")
		{
		LServer->Font->Color=clRed;
		}

	sistema=29;
	modalidade=29;

}
//---------------------------------------------------------------------------



void TFormMenuPrincipal::MontaMenu_Ado(TMainMenu *Menu,int cod_usr,int cod_sistema,TADOConnection *ADOConn)
{
	/*
	A FUN��O TRABALHA COM MENU DE 3 N�VES
	 0      0    0
	----  ---- ----
	  1    2
	----|----
		   2    3
		 ----|----

	HAVENDO NECESSIDADE DE CRIAR MAIS UM SUBMENU
	� S� ADICIONAR IF VERIFICANDO O COUNT

	*/
   /*
	TStoredProc *SpMenu=new TStoredProc(0);
	SpMenu->DatabaseName="DBGERAL";
	SpMenu->Close();
	SpMenu->StoredProcName="USR_MONTA_MENU";
	SpMenu->Prepare();
	SpMenu->ParamByName("@CODUSUARIO")->AsInteger=cod_usr;
	SpMenu->ParamByName("@CODSISTEMA")->AsInteger=cod_sistema;
	SpMenu->Open();  */

	TADOStoredProc *SpMenu=new TADOStoredProc(0);
	SpMenu->Connection=ADOConn;
	SpMenu->Close();
	SpMenu->Prepared=true;
	SpMenu->ProcedureName="USR_MONTA_MENU";
	SpMenu->Parameters->Refresh();
	SpMenu->Parameters->ParamByName("@CODUSUARIO")->Value=cod_usr;
	SpMenu->Parameters->ParamByName("@CODSISTEMA")->Value=cod_sistema;
	SpMenu->Open();

	for(int i=0; i < Menu->Items->Count; i++){
		//N�VEL 0
		if(Menu->Items->Items[i]->Tag!=1) //n�o esconder o menu Ajuda e Sair ou qualquer um
			Menu->Items->Items[i]->Visible=false; // que esteja no n�vel 0 com propriedade Tag=1
		for(int j=0; j < Menu->Items->Items[i]->Count; j++){
			//N�VEL 1
			if(Menu->Items->Items[i]->Items[j]->Tag!=1)
				Menu->Items->Items[i]->Items[j]->Visible=false;
			if(Menu->Items->Items[i]->Items[j]->Count>0){
				for(int w=0; w < Menu->Items->Items[i]->Items[j]->Count; w++){
					//N�VEL 2
					Menu->Items->Items[i]->Items[j]->Items[w]->Visible=false;
					if(Menu->Items->Items[i]->Items[j]->Items[w]->Count>0){
						for(int y=0; y < Menu->Items->Items[i]->Items[j]->Items[w]->Count; y++){
							//N�VEL 3
							Menu->Items->Items[i]->Items[j]->Items[w]->Items[y]->Visible=false;
						}
					}
				}
			}
		}
	}

	while (!SpMenu->Eof){
		for(int i=0; i < Menu->Items->Count; i++){
			for(int j=0; j < Menu->Items->Items[i]->Count; j++){
				//N�VEL 1
				if (Menu->Items->Items[i]->Items[j]->Name==SpMenu->FieldByName("MENU_SISTEMA")->AsString){
					Menu->Items->Items[i]->Items[j]->Visible=true;
					Menu->Items->Items[i]->Visible=true;
					break;
				}
				if(Menu->Items->Items[i]->Items[j]->Count>0){
					for(int w=0; w < Menu->Items->Items[i]->Items[j]->Count; w++){
					//N�VEL 2
						if (Menu->Items->Items[i]->Items[j]->Items[w]->Name==SpMenu->FieldByName("MENU_SISTEMA")->AsString){
							Menu->Items->Items[i]->Items[j]->Items[w]->Visible=true;
							Menu->Items->Items[i]->Items[j]->Visible=true;
							Menu->Items->Items[i]->Visible=true;
							break;
						}
						if(Menu->Items->Items[i]->Items[j]->Items[w]->Count>0){
							for(int y=0; y < Menu->Items->Items[i]->Items[j]->Items[w]->Count; y++){
								//N�VEL 3
									if (Menu->Items->Items[i]->Items[j]->Items[w]->Items[y]->Name==SpMenu->FieldByName("MENU_SISTEMA")->AsString){
										Menu->Items->Items[i]->Items[j]->Items[w]->Items[y]->Visible=true;
										Menu->Items->Items[i]->Items[j]->Items[w]->Visible=true;
										Menu->Items->Items[i]->Items[j]->Visible=true;
										Menu->Items->Items[i]->Visible=true;
										break;
									}
							}
						}
					}
				}
			}
		}
		SpMenu->Next();
	}
	delete SpMenu;
}


void __fastcall TFormMenuPrincipal::SairClick(TObject *Sender)
{
Close();
}
//---------------------------------------------------------------------------
