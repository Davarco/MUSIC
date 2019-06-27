BIN = bin
SRC1 = src/pinger_simulation
SRC2 = src/pinger_localization

all: pinger_simulation pinger_localization 

pinger_simulation:
	cd $(SRC1) && make 
	cp $(SRC1)/$(BIN)/* $(BIN)
	
pinger_localization:
	cd $(SRC2) && make 
	cp $(SRC2)/$(BIN)/* $(BIN)

clean: 
	cd $(SRC1) && make clean
	cd $(SRC2) && make clean
	rm $(BIN)/*
