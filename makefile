# cmake wrapper

BUILDFDR = build
EXEC = SpiritRender

default:
	make -C $(BUILDFDR)/

run:
	./$(BUILDFDR)/$(EXEC)

debug:
	gdb -tui $(BUILDFDR)/$(EXEC)

cmake:
	mkdir -p $(BUILDFDR)/Config/shaders
	cp Config/*.txt $(BUILDFDR)/Config/
	cmake -B $(BUILDFDR)
