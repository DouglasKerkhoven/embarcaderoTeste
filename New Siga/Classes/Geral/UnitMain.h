//---------------------------------------------------------------------------

#ifndef UnitMainH
#define UnitMainH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
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
#include <Vcl.Buttons.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.pngimage.hpp>
#include <Data.Win.ADODB.hpp>
//---------------------------------------------------------------------------
class TFormMain : public TForm
{
__published:	// IDE-managed Components
	TFDConnection *FDConecxao;
	TFDQuery *Query;
	TDataSource *DataSource1;
	TPanel *Panel1;
	TPanel *Panel2;
	TImage *Image1;
	TEdit *EMatricula;
	TEdit *ESenha;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TPanel *Panel3;
	TSpeedButton *SBEntrar;
	TLabel *LNome;
	TFDTransaction *FDTransacao;
	TLabel *LConeaxao;
	TADOConnection *ADOConn;
	void __fastcall SBEntrarClick(TObject *Sender);
	void __fastcall FormActivate(TObject *Sender);
private:	// User declarations

	/*int USER=0;
	bool ADM=false;
	bool ADM_FIN=false;
	bool ADM_MAT=false;
	bool ADM_EVE=false;
	int cont=0;
	bool login=false;
	int CODCAIXA=0;
	String DT_CAIXA=""; */
public:		// User declarations
	__fastcall TFormMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormMain *FormMain;
//---------------------------------------------------------------------------
#endif
