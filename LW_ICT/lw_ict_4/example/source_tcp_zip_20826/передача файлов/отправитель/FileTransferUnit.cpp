//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "FileTransferUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TTransferForm *TransferForm;
TMemoryStream *Stream=new TMemoryStream;
bool isRecieve=false;
//---------------------------------------------------------------------------
__fastcall TTransferForm::TTransferForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TTransferForm::StartButtonClick(TObject *Sender)
{
Server->Active=true;
Server->Open();
}
//---------------------------------------------------------------------------
void __fastcall TTransferForm::SendButtonClick(TObject *Sender)
{
void *filePointer;
int fileSize;

if(OpenDialog->Execute())
 Stream->LoadFromFile(OpenDialog->FileName);

Server->Socket->Connections[0]->SendText("file#" + OpenDialog->FileName + "#" + IntToStr(Stream->Size) + "#");

Stream->Position=0;

filePointer=Stream->Memory;
fileSize =Server->Socket->Connections[0]->SendBuf(filePointer, Stream->Size);
}
//---------------------------------------------------------------------------
void __fastcall TTransferForm::ServerClientRead(TObject *Sender,
      TCustomWinSocket *Socket)
{
if(Server->Socket->Connections[0]->ReceiveText()=="Ready!")
 {
 Stream->Clear();
 isRecieve=true;
 }
}
//---------------------------------------------------------------------------
