#pragma once

#include <stdio.h>

#include <Data.DB.hpp>
#include <FireDAC.Comp.Client.hpp>
#include <FireDAC.Comp.DataSet.hpp>
#include <FireDAC.DApt.hpp>
#include <FireDAC.DApt.Intf.hpp>
#include <FireDAC.DatS.hpp>
#include <FireDAC.Phys.hpp>
#include <FireDAC.Phys.Intf.hpp>
#include <FireDAC.Phys.MSSQL.hpp>
#include <FireDAC.Phys.MSSQLDef.hpp>
#include <FireDAC.Stan.Async.hpp>
#include <FireDAC.Stan.Def.hpp>
#include <FireDAC.Stan.Error.hpp>
#include <FireDAC.Stan.Intf.hpp>
#include <FireDAC.Stan.Option.hpp>
#include <FireDAC.Stan.Param.hpp>
#include <FireDAC.Stan.Pool.hpp>
#include <FireDAC.UI.Intf.hpp>
#include <FireDAC.VCLUI.Wait.hpp>


class DataBase
{
private:
	   AnsiString senhaBD ;

public:


	TFDQuery *Query;
	TDataSource *DataSource;
	TFDConnection *FDConnection;
	TFDTransaction *FDTransaction;
	TLabel *LComandoSQL;

	bool mostroMensagemErro;
	bool fechoSistemaAposMensagem;

	int tentativasReconexao;
	AnsiString ipServidor;
	AnsiString bdConfigurado;
	AnsiString bdConfiguradoCloud;
	AnsiString usuarioBD;

	AnsiString dnsCloudAWS;
	AnsiString modulo;

	bool deuErro;


	DataBase(AnsiString modulo, TFDConnection *Database1,TFDQuery *Query1,TDataSource *DataSource1,TFDTransaction *FDTransaction,bool mostroMensagemErro1,bool fechoSistemaAposMensagem1,AnsiString ipServidor,AnsiString bdConfigurado,AnsiString bdConfiguradoCloud,AnsiString usuarioBD,AnsiString dnsCloud,bool allFoodReport,AnsiString versao,bool conectandoAServidorAllFoodReport,TLabel *LComandoSQL2);

	~DataBase(){};


	void Consulta(AnsiString);
	void Executar(AnsiString);
	void FecharQuery();

	AnsiString RetornarLinhaStr(int linha);
	AnsiString ToString(int linha);

	double RetornarLinhaFloat(int linha);
	double ToFloat(int linha);

	int RetornarLinhaInt(int linha);
	int ToInt(int linha);

	int QtdeLinhas();
	int QtdeColunas();
	void GerarArquivoLog_ErroSQL(AnsiString mensagemErro,AnsiString comandoSQL);
	bool VerificarConexao();
	void FecharConexao();

	void PrimeiraLinha();
	void UltimaLinha();
	void ProximaLinha();

	bool VerificarExistenciaStringDentroDeOutra(AnsiString stringCompleta,AnsiString stringVerificar);


};
 //---------------------------------------------------------------------------------------------------------

DataBase::DataBase(AnsiString modulo2, TFDConnection *FDConnection1,TFDQuery *Query1,TDataSource *DataSource1,TFDTransaction *FDTransaction1,bool mostroMensagemErro1,bool fechoSistemaAposMensagem1,AnsiString ipServidor2,AnsiString bdConfigurado2,AnsiString bdConfiguradoCloud2,AnsiString usuarioBD2,AnsiString dnsCloud2,bool allFoodReport,AnsiString versao,bool conectandoAServidorAllFoodReport,TLabel *LComandoSQL2)
	{
	/*
	senhaBD = "cc@261912";

	modulo=modulo2;
    SystemParametersInfo(SPI_SETBEEP, 0, NULL, SPIF_SENDWININICHANGE);

	dnsCloudAWS=dnsCloud2;
	if(dnsCloudAWS.Trim()!="")
		{
		ipServidor2=dnsCloudAWS;  //aws
		if(bdConfiguradoCloud2!="" && bdConfiguradoCloud2!=bdConfigurado2)
			{
			bdConfigurado2=bdConfiguradoCloud2;
            }
		}

	bdConfiguradoCloud=bdConfiguradoCloud2;

    Query=Query1;
	DataSource=DataSource1;
	FDConnection=FDConnection1;
	FDTransaction=FDTransaction1;
	LComandoSQL=LComandoSQL2;

	FDConnection->Params->DriverID = "MSSQL";
	FDConnection->LoginPrompt= false;
	ipServidor=ipServidor2;
	bdConfigurado=bdConfigurado2;
	usuarioBD=usuarioBD2;

	FDConnection->Params->Values["Server"] = ipServidor;
	FDConnection->Params->Values["Database"] = bdConfigurado;

	if(dnsCloudAWS.Trim()!="" && allFoodReport == false)
		usuarioBD=""; //aws

	FDConnection->Params->Values["user name"] = usuarioBD;

	int versaoInt=StrToInt(versao);


	FDConnection->Params->Values["Password"] = senhaBD; */
	try
		{
		Query=Query1;
		DataSource=DataSource1;
		FDConnection=FDConnection1;
		FDTransaction=FDTransaction1;
		LComandoSQL=LComandoSQL2;
		FDConnection->ResourceOptions->KeepConnection=true;
		FDConnection->Connected=true;
		}
	catch (EFDDBEngineException *ErrosNoBD)
			{
			ShowMessage(ErrosNoBD[0].Message.c_str());
            }
	//FDConnection->Params->Values["Pool Maximum Items"] = 100;
	mostroMensagemErro=mostroMensagemErro1;
	fechoSistemaAposMensagem=fechoSistemaAposMensagem1;
	deuErro=false;
	tentativasReconexao=0;
    bool conexaoOK=FDConnection->Connected;
	}


//--------------------------------------------------------------------------

void DataBase::Consulta(AnsiString comandoSQLConsulta)
	{
	//tentar colocar sql_no_cache
	bool conexaoOK=VerificarConexao();
	if(conexaoOK==true)
		{
		deuErro=false;
		Query->Close();
		Query->SQL->Clear();

		if(LComandoSQL!=NULL)
			{
			LComandoSQL->Caption=comandoSQLConsulta;
			Application->ProcessMessages();
			}

		comandoSQLConsulta=comandoSQLConsulta.LowerCase();   //nao lembro porque estava assim ja

		//if(comandoSQL.SubString(1,6)=="select")
		//	comandoSQL="SELECT sql_no_cache "+comandoSQL.SubString(7,comandoSQL.Length()-6);   //tentativa de ficar mais rapido

		Query->SQL->Add(comandoSQLConsulta);
		try
			{
			Query->Open();
			tentativasReconexao=0;
			}
		catch (EFDDBEngineException *ErrosNoBD)
			{
			deuErro=true;
			AnsiString mensagem = ErrosNoBD[0].Message.c_str();

			//DataParaBanco manipularData;
			/*
			bool teveHasGoneAway=manipularData.VerificarExistenciaStringDentroDeOutra(mensagem,"has gone away");
			bool teveLostConnection=manipularData.VerificarExistenciaStringDentroDeOutra(mensagem,"Lost connection");
			bool teveSenhaErrada=manipularData.VerificarExistenciaStringDentroDeOutra(mensagem,"Access denied for user");

			if(teveHasGoneAway==true || teveLostConnection==true)
				{
				FDConnection->Connected=false;
				Sleep(2000);
				FDConnection->Connected=true;
				Consulta(comandoSQLConsulta);
				}
			else if(teveSenhaErrada==true)
				{
				senhaBD="cc@261912";
				FDConnection->Params->Values["Password"] = senhaBD;
				Consulta(comandoSQLConsulta);
				}
			else if(ErrosNoBD[0].Kind == ekServerGone)
				{
				mensagem = "N�o foi poss�vel estabelecer uma conex�o com o servidor '"+ipServidor+"'.Tente novamente mais tarde.";
				//Application->CreateForm(__classid(TFormMensagemServidorIndisponivel),&FormMensagemServidorIndisponivel);
				//FormMensagemServidorIndisponivel->LIpServidor->Caption=ipServidor;
				//FormMensagemServidorIndisponivel->ShowModal();
				//FormMensagemServidorIndisponivel->Free();
				exit(0);
				}
			else if(mostroMensagemErro==true)
				{
				//Application->CreateForm(__classid(TFormMensagemErroSQL),&FormMensagemErroSQL);
				//FormMensagemErroSQL->LMensagemBanco->Caption=mensagem;
				//FormMensagemErroSQL->LComandoSQL->Caption=comandoSQLConsulta;
				//FormMensagemErroSQL->ShowModal();
				//FormMensagemErroSQL->Free();
				}
			  */
			GerarArquivoLog_ErroSQL(mensagem,comandoSQLConsulta);

			/*if(fechoSistemaAposMensagem==true && teveHasGoneAway==false && dnsCloudAWS=="")
				{
				exit(0);
				}
			else
				{
				throw ;
				}*/
			}
		}
	}

//---------------------------------------------------------------------------------------------------------

void DataBase::GerarArquivoLog_ErroSQL(AnsiString mensagemErro,AnsiString comandoSQL)
	{
    FILE *fp;

	AnsiString diretorio=L"C:\\ErroSQL_.txt";

	AnsiString mensagemFinal = comandoSQL +" *** "+mensagemErro;

	fp = fopen(diretorio.c_str(),"wt");
	fputs(mensagemFinal.c_str(),fp);
	fclose(fp);
	fputs("\n",fp);
	fclose(fp);
	}


//---------------------------------------------------------------
bool DataBase::VerificarExistenciaStringDentroDeOutra(AnsiString stringCompleta,AnsiString stringVerificar)
{
int i;
bool teveDado=false;
for(i=1;i<stringCompleta.Length();i++)
	{
	AnsiString verificacao=stringCompleta.SubString(i,stringVerificar.Length());
	if(verificacao==stringVerificar)
		{
		teveDado=true;
		break;
		}
	}

return teveDado;
}


bool DataBase::VerificarConexao()
	{
	bool conexaoOK=FDConnection->Connected;

	if(FDConnection->Connected==false)
		{
		try
			{
			FDConnection->ResourceOptions->KeepConnection=true;
			FDConnection->Connected=true;
			conexaoOK=true;
			tentativasReconexao=0;
			}
		catch (EFDDBEngineException *ErrosNoBD) //catch (EMySQLNativeException *ErrosNoBD)  EFDDBEngineException
			{
			tentativasReconexao++;
			AnsiString mensagem = ErrosNoBD[0].Message.c_str();

			//DataParaBanco manipularData;
			bool naoTemMemoria=VerificarExistenciaStringDentroDeOutra(mensagem,"initialize the Borland Database");
			//bool teveAccessDenied=manipularData.VerificarExistenciaStringDentroDeOutra(mensagem,"Access denied");
			bool teveQuedaCloud=VerificarExistenciaStringDentroDeOutra(mensagem,"Unknown MySQL server host");
			bool teveSenhaErrada=VerificarExistenciaStringDentroDeOutra(mensagem,"Access denied for user");
			bool teveTooManyConnection=VerificarExistenciaStringDentroDeOutra(mensagem,"Too many connections");
			bool nomeBdErrado=VerificarExistenciaStringDentroDeOutra(mensagem,"Unknown database");

            if(ErrosNoBD[0].Kind == ekServerGone)
				{ /*
				mensagem = "N�o foi poss�vel estabelecer uma conex�o com o servidor '"+ipServidor+"'.Tente novamente mais tarde.";
				Application->CreateForm(__classid(TFormMensagemServidorIndisponivel),&FormMensagemServidorIndisponivel);
				FormMensagemServidorIndisponivel->LIpServidor->Caption=ipServidor;
				FormMensagemServidorIndisponivel->ShowModal();
				FormMensagemServidorIndisponivel->Free();
				exit(0);     */
				}
			else if(nomeBdErrado==true)
				{  /*
				//mensagem = "N�o foi poss�vel estabelecer uma conex�o com o servidor '"+ipServidor+"'.Tente novamente mais tarde.";
				Application->CreateForm(__classid(TFormMensagemServidorIndisponivel),&FormMensagemServidorIndisponivel);
				FormMensagemServidorIndisponivel->LIpServidor->Caption="Nome do banco de dados inexistente.";
				FormMensagemServidorIndisponivel->Label4->Caption="Verifique qual � o nome certo do banco de dados CLOUD.";
				FormMensagemServidorIndisponivel->Label5->Caption="Coloque o nome certo do banco no arquivo bancodadoscloud.txt";
                FormMensagemServidorIndisponivel->Label6->Caption="Ap�s fazer isso, tente abrir o AllFood novamente.";
				FormMensagemServidorIndisponivel->ShowModal();
				FormMensagemServidorIndisponivel->Free();         */
				exit(0);
                }
			else if(naoTemMemoria==true)
				{
				mensagem="Sua memoria RAM n�o � suficiente para rodar o sistema AllFood ERP. Feche programas desnecess�rios e tente novamente.";
				//tentativasReconexao=3;

				if(mostroMensagemErro==true)
					{        /*
					Application->CreateForm(__classid(TFormMensagemErroSQL),&FormMensagemErroSQL);
					FormMensagemErroSQL->LMensagemBanco->Caption=mensagem;
					FormMensagemErroSQL->LFechado->Visible=false;
					FormMensagemErroSQL->LComandoSQL->Caption="Tentando novamente conetar com o Banco de Dados";
					FormMensagemErroSQL->ShowModal();
					FormMensagemErroSQL->Free();    */
					}
				}
			else if(teveSenhaErrada==true)
				{
				senhaBD="dalca1154";
				FDConnection->Params->Values["Password"] = senhaBD;
				VerificarConexao();
                return false;
				}
			else if(teveTooManyConnection==true)
				{
				FDConnection->CloneConnection();

                exit(0);
                }

			if(mostroMensagemErro==true)
				{
				if(tentativasReconexao==0)
					{ /*
					Application->CreateForm(__classid(TFormMensagemErroSQL),&FormMensagemErroSQL);
					FormMensagemErroSQL->LMensagemBanco->Caption=mensagem;
					FormMensagemErroSQL->LFechado->Visible=false;
					FormMensagemErroSQL->LComandoSQL->Caption="Tentativa de conex�o com o Banco de Dados";
					FormMensagemErroSQL->ShowModal();
					FormMensagemErroSQL->Free();  */
					}
				}

			if(fechoSistemaAposMensagem==true && tentativasReconexao==3)
				{
				if(dnsCloudAWS=="")
					{
					if(mostroMensagemErro==true)
						{  /*
						Application->CreateForm(__classid(TFormMensagemErroSQL),&FormMensagemErroSQL);
						FormMensagemErroSQL->LMensagemBanco->Caption="O sistema n�o conseguiu se conectar com o banco de dados.";
						FormMensagemErroSQL->LComandoSQL->Caption="Verifique sua conex�o de rede e tente novamente em alguns minutos.";
						FormMensagemErroSQL->LFechado->Visible=true;
						FormMensagemErroSQL->ShowModal();
						FormMensagemErroSQL->Free();        */
						}

					exit(0);
					}
				else
					{
					if(mostroMensagemErro==true)
						{   /*
						Application->CreateForm(__classid(TFormMensagemErroSQL),&FormMensagemErroSQL);
						FormMensagemErroSQL->LMensagemBanco->Caption="O sistema n�o conseguiu se conectar com o SERVIDOR CLOUD AWS.";
						FormMensagemErroSQL->LComandoSQL->Caption="Verifique sua conex�o de internet e tente novamente em alguns minutos.";
						FormMensagemErroSQL->LFechado->Visible=true;
						FormMensagemErroSQL->ShowModal();
						FormMensagemErroSQL->Free();         */
						}

					exit(0);
					}
				}

			if(tentativasReconexao<3)
				{
                if(teveQuedaCloud==true)
					{
					mensagem="O AllFood n�o conseguiu se conectar com seu servidor Cloud AWS, por favor verifique sua conex�o de rede e tente novamente.\nTentativas de reconex�o: "+IntToStr(tentativasReconexao);
					}

				if(mostroMensagemErro==true)
					{ /*
					Application->CreateForm(__classid(TFormMensagemErroSQL),&FormMensagemErroSQL);
					FormMensagemErroSQL->LFechado->Visible=false;
					FormMensagemErroSQL->LMensagemBanco->Caption=mensagem;
					FormMensagemErroSQL->LComandoSQL->Caption="Tentando reconectar com o banco de dados.\nO processo poder� levar alguns segundos, aguarde .....";
					FormMensagemErroSQL->ShowModal();
					FormMensagemErroSQL->Free();       */
                    }

				Sleep(2000);
				conexaoOK=VerificarConexao();
				}
			}
		}

	return conexaoOK;
	}

//---------------------------------------------------------------------------------------------------------

AnsiString DataBase::ToString(int linha)
	{
	AnsiString retorno=DataSource->DataSet->Fields->Fields[linha]->AsString.Trim();
	return retorno;
	}

//---------------------------------------------------------------------------------------------------------
/*
AnsiString DataBase::BuscarNomeColuna(int coluna)
	{
	AnsiString nomeCol=DataSource->DataSet->Fields->Fields[coluna]->DisplayName;
	return nomeCol;
    }  */

//---------------------------------------------------------------------------------------------------------

double DataBase::RetornarLinhaFloat(int linha)
	{
	double retorno=DataSource->DataSet->Fields->Fields[linha]->AsFloat;
	return retorno;
	}

//---------------------------------------------------------------------------------------------------------

double DataBase::ToFloat(int linha)
	{
	double retorno=DataSource->DataSet->Fields->Fields[linha]->AsFloat;
	return retorno;
	}

//---------------------------------------------------------------------------------------------------------

int DataBase::RetornarLinhaInt(int linha)
	{
	int retorno=DataSource->DataSet->Fields->Fields[linha]->AsInteger;
	return retorno;
	}

//---------------------------------------------------------------------------------------------------------

int DataBase::ToInt(int linha)
	{
	int retorno=DataSource->DataSet->Fields->Fields[linha]->AsInteger;
	return retorno;
	}

//---------------------------------------------------------------------------------------------------------

int DataBase::QtdeLinhas()
	{
	DataSource->DataSet->Last();
	int valor=DataSource->DataSet->RecordCount;
	PrimeiraLinha();
	return valor;
	}

//---------------------------------------------------------------------------------------------------------

int DataBase::QtdeColunas()
	{
	int valor=DataSource->DataSet->FieldCount;
	return valor;
	}

//---------------------------------------------------------------------------------------------------------

void DataBase::PrimeiraLinha()
	{
	DataSource->DataSet->First();
	}

//---------------------------------------------------------------------------------------------------------

void DataBase::UltimaLinha()
	{
	DataSource->DataSet->Last();
	}

//---------------------------------------------------------------------------------------------------------

void DataBase::ProximaLinha()
	{
	DataSource->DataSet->Next();
	}

