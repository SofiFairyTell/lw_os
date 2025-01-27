//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "RecieveUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TRecieverForm *RecieverForm;
TMemoryStream *Stream = new TMemoryStream ;
int fileSize ;
bool isReceive ;
AnsiString fileName ;

//---------------------------------------------------------------------------
__fastcall TRecieverForm::TRecieverForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void Write( AnsiString Text )
{
if(Stream->Size<fileSize)
 Stream->Write(Text.c_str(), Text.Length());

if(Stream->Size==fileSize)
 {
 isReceive=false;

 Stream->Position=false;
 RecieverForm->Client->Socket->SendText("Ready!");
 CreateDir("Downloads");
 Stream->SaveToFile("Downloads\\" + fileName);
 Stream->Clear();
 fileSize=0;
 }
}

void __fastcall TRecieverForm::ClientRead(TObject *Sender,
      TCustomWinSocket *Socket)
{
AnsiString recieveText=Client->Socket->ReceiveText();

if(isReceive)
 Write(recieveText);
else
 {
 if(recieveText.SubString(0,recieveText.Pos("#")-1)=="file")
  {
  recieveText.Delete(1,recieveText.Pos("#"));
  name=recieveText.SubString(0,recieveText.Pos("#")-1);
  fileName=name.SubString(name.LastDelimiter("\\")+1,name.Length());
  recieveText.Delete(1,recieveText.Pos("#"));
  fileSize=StrToInt(recieveText.SubString(0,recieveText.Pos("#")-1));
  recieveText.Delete(1,recieveText.Pos("#"));
  isReceive=true;
  }
 }
}
//---------------------------------------------------------------------------

void __fastcall TRecieverForm::ConnectButtonClick(TObject *Sender)
{
Client->Open();
}
//---------------------------------------------------------------------------

