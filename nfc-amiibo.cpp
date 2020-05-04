#include "amiibo.h"
#include "amiitool.h"
#include "nfchandler.h"

#include <stdio.h>

void printUsage() {
  printf("nfc-amiibo keyfile binfile\n");
}

int main(int argc, char** argv) {
  if (argc != 3) {
    fprintf(stderr, "Incorrect number of arguments\n");
    printUsage();
    exit(1);
  }

  Amiitool::setKeyPath(argv[1]);

  Amiibo *amiibo = new Amiibo(argv[2]);
  NFCHandler *nfc = new NFCHandler();

  nfc->writeAmiibo(amiibo);

  delete nfc;
  delete amiibo;
}
