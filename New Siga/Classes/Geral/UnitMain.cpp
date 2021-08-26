//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UnitMain.h"
#include "UnitMenuPrincipal.h"

#include "Usuario.h"
#include "DataBase.h"
#include "funcoes.h"


//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormMain *FormMain;
 Usuario *usuario;
 DataBase *bancoDados;
 Funcoes funcoes;
//---------------------------------------------------------------------------
__fastcall TFormMain::TFormMain(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::SBEntrarClick(TObject *Sender)
{
	//CODCAIXA=0;
	//DT_CAIXA="";

	if(EMatricula->Text =="")
		{
		 EMatricula->Focused();
		 return;
		}

	else if(ESenha->Text=="")
		{
		ESenha->Focused();
		return;
		}

	if(ESenha->Text.Length()<4)
		{
		//MessageBox(this->Handle,"Senha de no mínimo 4 caracteres!","Aviso",MB_OK+MB_ICONEXCLAMATION);
		return;
		}
		 AnsiString codUsuario = "";

		AnsiString sql = "SELECT U.CODUSUARIO,SUBSTRING(NOME,0,CHARINDEX(' ',LTRIM(RTRIM([NOME]))))AS NOME,ADMINISTRADOR,U.TROCA, U.SEDE FROM Geral.dbo.FUN_FUNCIONARIO F,GERAL.DBO.USR_USUARIOS U WHERE F.MATRICULA = U.MATRICULA AND F.SITUACAO='A' AND U.STATUS<>'E' AND F.MATRICULA = "+EMatricula->Text;
		bancoDados->Consulta(sql);

		if(bancoDados->QtdeLinhas()>0)
			{
			bancoDados->PrimeiraLinha();
			AnsiString nome = bancoDados->ToString(1);
			usuario->setNome(nome);
			LNome->Caption = nome;
			int codUsuario =  bancoDados->ToInt(0);
			usuario->setCodigo(codUsuario);
			}
		else
			{
			EMatricula->Focused();
			return;
			}


		 bool ADM = false;

		sql = "exec Geral.dbo.USR_VALIDA_ACESSO :MATRICULA, :SENHA ";
		Query->SQL->Text = "exec Geral.dbo.USR_VALIDA_ACESSO :MATRICULA, :SENHA ";
		Query->ParamByName("MATRICULA")->Value=StrToInt(EMatricula->Text);
		Query->ParamByName("SENHA")->Value=ESenha->Text;
		Query->Open();
		if(Query->RecordCount>0)
			{
			Application->CreateForm(__classid(TFormMenuPrincipal),&FormMenuPrincipal);
			if(Query->FieldByName("ADMINISTRADOR")->AsString=="S")
				{

				usuario->setADM(true);
				funcoes.LiberaMenuAdm(FormMenuPrincipal->MainMenu);
				}
			else
				{
				usuario->setADM(false);
				FormMenuPrincipal->MontaMenu_Ado(FormMenuPrincipal->MainMenu,usuario->getCodigo(),29,ADOConn);
				}
			if (Query->FieldByName("ADM_FIN")->AsString=="S")
				{
				usuario->setAdmFin(true);
				}
			else
				{
				usuario->setAdmFin(false);
				}
			if (Query->FieldByName("ADM_MAT")->AsString=="S")
				{
				usuario->setAdmMat(true);
				}
			else
				{
				usuario->setAdmMat(false);
				}


			 Application->CreateForm(__classid(TFormMenuPrincipal),&FormMenuPrincipal);
			 FormMenuPrincipal->ShowModal();
			 FormMenuPrincipal->Free();

			 Query->Close();

			}
		else
			 ShowMessage("Login Invalido");
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::FormActivate(TObject *Sender)
{

bancoDados = new DataBase("Financeiro",FDConecxao,Query,DataSource1,FDTransacao,true,true,"TI_PC01\CCDEVELOPER","Associados_11_08_2021","","sa","",false,"1",false,LConeaxao);
usuario = new Usuario();
}
//---------------------------------------------------------------------------
