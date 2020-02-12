SOURCES = amiibo.cpp amiitool.cpp nfchandler.cpp nfc-amiibo.cpp

all: nfc-amiibo amiitoolsubmodule

nfc-amiibo: $(SOURCES)
	$(CXX) $(CXXFlags) $(SOURCES) -o $@ -lnfc

amiitoolsubmodule:
	cd amiitool && $(MAKE) amiitool

clean:
	rm nfc-amiibo
	cd amiitool && $(MAKE) clean
