//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Data.DB.hpp>
#include <Data.Win.ADODB.hpp>
#include <Vcl.ComCtrls.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TADOConnection *ADOConnection1;
	TADOQuery *Q;
	TDataSource *DataSource1;
	TMemo *Memo1;
	TButton *Button1;
	TLargeintField *QID;
	TDateTimeField *QLogTime;
	TWideStringField *QMessage;
	TSmallintField *QMessageType;
	TMonthCalendar *MonthCalendar1;
	TADOQuery *D;
	TLargeintField *DID;
	TDateTimeField *DLogTime;
	TWideStringField *DMessage;
	TSmallintField *DMessageType;
	void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
