//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{


	TStringList *dr = new TStringList();
	TStringList *depots = new TStringList();

	D->Parameters->ParamByName("DT")->Value = MonthCalendar1->Date.FormatString("yyyy-mm-dd");
	D->Open();

	while (! D->Eof )
		{
			AnsiString CleanStr = StringReplace( DMessage->AsAnsiString , "[", "", TReplaceFlags() << rfReplaceAll ) ;

			AnsiString Depot;      	// DEPOT
			AnsiString Parent;      // PARENT

			CleanStr = StringReplace( CleanStr , "]", "", TReplaceFlags() << rfReplaceAll ) ;


//            UNIT [0066] OPID [00621471] PARENT [0106861314] DEPOT [92]

			dr->CommaText = CleanStr ;

			int d = 0;
			Parent = "";
			Depot = "";
			while ( d < dr->Count )
				{
					 if (dr->Strings[d].Trim().UpperCase() == "PARENT" ) {
						if ( d+1 < dr->Count  ) {
							Parent = dr->Strings[d+1].Trim();
						}
					 }
					 if (dr->Strings[d].Trim().UpperCase() == "DEPOT" ) {
						if ( d+1 < dr->Count  ) {
							Depot = dr->Strings[d+1].Trim();
						}
					 }


					d++;
				}
				if ( !Parent.IsEmpty() && !Depot.IsEmpty() ) {
					depots->Values[Parent] = Depot;
				}

			Memo1->Lines->Add ( DMessage->AsAnsiString );
			D->Next() ;
		}

	D->Close();

	Memo1->Lines->AddStrings(depots);
	delete dr;








	TStringList *depotsummary = new TStringList();

	depotsummary->Clear();




	Q->Parameters->ParamByName("DT")->Value = MonthCalendar1->Date.FormatString("yyyy-mm-dd");


	Q->Open();

	TStringList *r = new TStringList();
	TStringList *csv = new TStringList();

	csv->Clear();

	csv->Add ( "\"Barcode\",\"Date\",\"Time\",\"Personnel ID\"" );
	Memo1->Lines->Clear();


	while (!Q->Eof )
	{
		AnsiString CleanStr = StringReplace( QMessage->AsAnsiString , "[", "", TReplaceFlags() << rfReplaceAll ) ;

		AnsiString Barcode;       // CHILD
		AnsiString Operator;      // OPID
		AnsiString Parent;        // PARENT

		CleanStr = StringReplace( CleanStr , "]", "", TReplaceFlags() << rfReplaceAll ) ;

		r->CommaText = CleanStr ;

		int ri = 0;
		Barcode = "";       // CHILD
		Operator = "";      // OPID
		Parent = "";        // PARENT
		while ( ri < r->Count )
			{
				if ( r->Strings[ri].Trim().UpperCase() == "PARENT" ) {
					if ( ri+1 < r->Count ) {
						Parent = r->Strings[ri+1].Trim();
					}
				}
				if ( r->Strings[ri].Trim().UpperCase() == "CHILD" ) {
					if ( ri+1 < r->Count ) {
						Barcode = r->Strings[ri+1].Trim();
					}
				}
				if ( r->Strings[ri].Trim().UpperCase() == "OPID" ) {
					if ( ri+1 < r->Count ) {
						Operator = r->Strings[ri+1].Trim();
					}
				}


				ri++;
			}
			AnsiString rowstr = "";

				rowstr = "\"" + Barcode + "\",\"" + QLogTime->AsDateTime.FormatString("dd/mm/yyyy") + "\",\"" +
					QLogTime->AsDateTime.FormatString("hh:nn") + "\",\"" + Operator + "\",\"" + Parent + "\"";
				Memo1->Lines->Add ( rowstr );
			AnsiString depot = depots->Values[Parent];



			AnsiString depotSummaryKey = Operator.Trim()+" "+depot.Trim();
			AnsiString currTotal = depotsummary->Values[depotSummaryKey];
			if ( currTotal.IsEmpty() ) {
				currTotal = "0";
			}
			currTotal = IntToStr(currTotal.ToInt() + 1);
			depotsummary->Values[depotSummaryKey] = currTotal;



//		Memo1->Lines->Add ( QMessage->AsAnsiString );

		csv->Add ( rowstr );

//		Memo1->Lines->AddStrings(r);

		Q->Next();

	}
	Q->Close();

	csv->SaveToFile("I:\\whseapps\\bonus\\" + MonthCalendar1->Date.FormatString("ddmm") +  "scand.txt");
	Memo1->Lines->Add ( "Count : " + IntToStr(csv->Count) );

	csv->Clear();
	csv->Add ("\"Date\",\"Centre\",\"Operator\",\"Depot\",\"Quantity\"");

	int sd = 0;
	TStringList *splitter = new TStringList();

	while ( sd < depotsummary->Count )
		{
			AnsiString key = depotsummary->Names[sd];
			AnsiString value = depotsummary->Values[key];

			splitter->CommaText = key;
			if ( splitter->Count > 1) {
				csv->Add (
					"\"" + MonthCalendar1->Date.FormatString("dd/mm/yyyy") + "\""
					+ ","
					+ "\"02\""
					+ ","
					+ "\"" + splitter->Strings[0] + "\""
					+ ","
					+ "\"" + splitter->Strings[1] + "\""
					+ ","
					+ "\"" + value.Trim() + "\"" );
			}


			sd++;
		}
	delete splitter;

	csv->SaveToFile ( "I:\\whseapps\\bonus\\" + MonthCalendar1->Date.FormatString("ddmm") +  "scans.txt");


	delete csv;
	delete r;
	delete depots ;
	delete depotsummary ;



}
//---------------------------------------------------------------------------
